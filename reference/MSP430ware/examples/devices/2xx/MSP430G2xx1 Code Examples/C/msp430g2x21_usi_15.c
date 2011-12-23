//******************************************************************************
//  MSP430G2x21/G2x31 - I2C Slave Receiver / Slave Transmitter, multiple bytes
//
//  Description: I2C Master communicates with I2C Slave using
//  the USI. Master data should increment from 0x55 with each transmitted byte.
//  ACLK = n/a, MCLK = SMCLK = Calibrated 1MHz
//
//  ***THIS IS THE SLAVE CODE***
//
//                  Slave                      Master
//                                    (msp430g2x21_usi_12.c)
//            MSP430G2x21/G2x31          MSP430G2x21/G2x31
//             -----------------          -----------------
//         /|\|              XIN|-    /|\|              XIN|-
//          | |                 |      | |                 |
//          --|RST          XOUT|-     --|RST          XOUT|-
//            |                 |        |                 |
//      LED <-|P1.0             |        |                 |
//            |                 |        |             P1.0|-> LED
//            |         SDA/P1.7|------->|P1.6/SDA         |
//            |         SCL/P1.6|<-------|P1.7/SCL         |
//
//  Note: internal pull-ups are used in this example for SDA & SCL
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include <msp430g2221.h>

#define Number_of_Bytes  5                  // **** How many bytes?? ****

void Setup_USI_Slave(void);

char MST_Data = 0;                          // Variable for received data
char SLV_Data = 0x55;
char SLV_Addr = 0x90;                       // Address is 0x48<<1 for R/W
int I2C_State, Bytecount, transmit = 0;     // State variables

void Data_RX(void);
void TX_Data(void);
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  } 
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
  Setup_USI_Slave();
  
  LPM0;                                     // CPU off, await USI interrupt
  _NOP();
}

//******************************************************************************
// USI interrupt service routine
// Rx bytes from master: State 2->4->6->8 
// Tx bytes to Master: State 2->4->10->12->14
//******************************************************************************
#pragma vector = USI_VECTOR
__interrupt void USI_TXRX (void)
{
  if (USICTL1 & USISTTIFG)                  // Start entry?
  {
    P1OUT |= 0x01;                          // LED on: sequence start
    I2C_State = 2;                          // Enter 1st state on start
  }

  switch(__even_in_range(I2C_State,14))
    {
      case 0:                               // Idle, should not get here
              break;

      case 2: // RX Address
              USICNT = (USICNT & 0xE0) + 0x08; // Bit counter = 8, RX address
              USICTL1 &= ~USISTTIFG;        // Clear start flag
              I2C_State = 4;                // Go to next state: check address
              break;

      case 4: // Process Address and send (N)Ack
              if (USISRL & 0x01){            // If master read...
                SLV_Addr = 0x91;             // Save R/W bit
                transmit = 1;}
              else{transmit = 0;
                  SLV_Addr = 0x90;}
              USICTL0 |= USIOE;             // SDA = output
              if (USISRL == SLV_Addr)       // Address match?
              {
                USISRL = 0x00;              // Send Ack
                P1OUT &= ~0x01;             // LED off
                if (transmit == 0){ 
                  I2C_State = 6;}           // Go to next state: RX data
                if (transmit == 1){  
                  I2C_State = 10;}          // Else go to next state: TX data
              }
              else
              {
                USISRL = 0xFF;              // Send NAck
                P1OUT |= 0x01;              // LED on: error
                I2C_State = 8;              // next state: prep for next Start
              }
              USICNT |= 0x01;               // Bit counter = 1, send (N)Ack bit
              break;

    case 6: // Receive data byte
              Data_RX();
              break;  

      case 8:// Check Data & TX (N)Ack
              USICTL0 |= USIOE;             // SDA = output
              if (Bytecount <= (Number_of_Bytes-2))          
                                            // If not last byte
              {
                USISRL = 0x00;              // Send Ack
                I2C_State = 6;              // Rcv another byte
                Bytecount++;
                USICNT |= 0x01;             // Bit counter = 1, send (N)Ack bit
              }
              else                          // Last Byte
              {
                USISRL = 0xFF;              // Send NAck
              USICTL0 &= ~USIOE;            // SDA = input
              SLV_Addr = 0x90;              // Reset slave address
              I2C_State = 0;                // Reset state machine
              Bytecount =0;                 // Reset counter for next TX/RX
              }
              
              
              break;

     case 10: // Send Data byte
              TX_Data();
              break;

      case 12:// Receive Data (N)Ack
              USICTL0 &= ~USIOE;            // SDA = input
              USICNT |= 0x01;               // Bit counter = 1, receive (N)Ack
              I2C_State = 14;               // Go to next state: check (N)Ack
              break;

      case 14:// Process Data Ack/NAck
           if (USISRL & 0x01)               // If Nack received...
              {
              USICTL0 &= ~USIOE;            // SDA = input
              SLV_Addr = 0x90;              // Reset slave address
              I2C_State = 0;                // Reset state machine
               Bytecount = 0;
             // LPM0_EXIT;                  // Exit active for next transfer
              }
              else                          // Ack received
              {
                P1OUT &= ~0x01;             // LED off
                TX_Data();                  // TX next byte
               }
	       break;
    
      }
  USICTL1 &= ~USIIFG;                       // Clear pending flags
}

void Data_RX(void){
  
              USICTL0 &= ~USIOE;            // SDA = input
              USICNT |=  0x08;              // Bit counter = 8, RX data
              I2C_State = 8;                // next state: Test data and (N)Ack
}

void TX_Data(void){
              USICTL0 |= USIOE;             // SDA = output
              USISRL = SLV_Data++;
              USICNT |=  0x08;              // Bit counter = 8, TX data
              I2C_State = 12;               // Go to next state: receive (N)Ack
}

void Setup_USI_Slave(void){
  P1OUT = 0xC0;                             // P1.6 & P1.7 Pullups
  P1REN |= 0xC0;                            // P1.6 & P1.7 Pullups
  P1DIR = 0xFF;                             // Unused pins as outputs
  P2OUT = 0;
  P2DIR = 0xFF;
  
  USICTL0 = USIPE6+USIPE7+USISWRST;         // Port & USI mode setup
  USICTL1 = USII2C+USIIE+USISTTIE;          // Enable I2C mode & USI interrupts
  USICKCTL = USICKPL;                       // Setup clock polarity
  USICNT |= USIIFGCC;                       // Disable automatic clear control
  USICTL0 &= ~USISWRST;                     // Enable USI
  USICTL1 &= ~USIIFG;                       // Clear pending flag
  
  transmit = 0;
  _EINT();

}


