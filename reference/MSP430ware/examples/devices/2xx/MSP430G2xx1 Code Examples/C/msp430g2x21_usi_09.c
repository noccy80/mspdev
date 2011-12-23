//******************************************************************************
//  MSP430G2x21/G2x31 Demo - I2C Slave Transmitter, single byte
//
//  Description: I2C Slave communicates with I2C Master using
//  the USI. Slave data is sent and increments from 0x00 with each transmitted
//  byte which is verified by the Master.
//  LED off for address or data Ack; LED on for address or data NAck.
//  ACLK = n/a, MCLK = SMCLK = Calibrated 1MHz
//
//  ***THIS IS THE SLAVE CODE***
//
//                  Slave                      Master
//                                      (msp430g2x21_usi_06.c)
//             MSP430G2x21/G2x31          MSP430G2x21/G2x31
//             -----------------          -----------------
//         /|\|              XIN|-    /|\|              XIN|-
//          | |                 |      | |                 |
//          --|RST          XOUT|-     --|RST          XOUT|-
//            |                 |        |                 |
//      LED <-|P1.0             |        |                 |
//            |                 |        |             P1.0|-> LED
//            |         SDA/P1.7|------->|P1.7/SDA         |
//            |         SCL/P1.6|<-------|P1.6/SCL         |
//
//  Note: internal pull-ups are used in this example for SDA & SCL
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include <msp430g2221.h>


char SLV_Data = 0;                     // Variable for transmitted data
char SLV_Addr = 0x90;                  // Address is 0x48<<1 for R/W
int I2C_State = 0;                     // State variable

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;            // Stop watchdog
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                          // If calibration constants erased
                                       // do not load, trap CPU!!
  }   
  BCSCTL1 = CALBC1_1MHZ;               // Set DCO
  DCOCTL = CALDCO_1MHZ;

  P1OUT = 0xC0;                        // P1.6 & P1.7 Pullups
  P1REN |= 0xC0;                       // P1.6 & P1.7 Pullups
  P1DIR = 0xFF;                        // Unused pins as outputs
  P2OUT = 0;
  P2DIR = 0xFF;

  USICTL0 = USIPE6+USIPE7+USISWRST;    // Port & USI mode setup
  USICTL1 = USII2C+USIIE+USISTTIE;     // Enable I2C mode & USI interrupts
  USICKCTL = USICKPL;                  // Setup clock polarity
  USICNT |= USIIFGCC;                  // Disable automatic clear control
  USICTL0 &= ~USISWRST;                // Enable USI
  USICTL1 &= ~USIIFG;                  // Clear pending flag
  _EINT();

  while(1)
  {
    LPM0;                              // CPU off, await USI interrupt
    _NOP();                            // Used for IAR
  }
}

//******************************************************
// USI interrupt service routine
//******************************************************
#pragma vector = USI_VECTOR
__interrupt void USI_TXRX (void)
{
  if (USICTL1 & USISTTIFG)             // Start entry?
  {
    P1OUT |= 0x01;                     // LED on: Sequence start
    I2C_State = 2;                     // Enter 1st state on start
  }

  switch(I2C_State)
    {
      case 0: //Idle, should not get here
              break;

      case 2: //RX Address
              USICNT = (USICNT & 0xE0) + 0x08; // Bit counter = 8, RX Address
              USICTL1 &= ~USISTTIFG;   // Clear start flag
              I2C_State = 4;           // Go to next state: check address
              break;

      case 4: // Process Address and send (N)Ack
              if (USISRL & 0x01)       // If read...
                SLV_Addr++;            // Save R/W bit
              USICTL0 |= USIOE;        // SDA = output
              if (USISRL == SLV_Addr)  // Address match?
              {
                USISRL = 0x00;         // Send Ack
                P1OUT &= ~0x01;        // LED off
                I2C_State = 8;         // Go to next state: TX data
              }
              else
              {
                USISRL = 0xFF;         // Send NAck
                P1OUT |= 0x01;         // LED on: error
                I2C_State = 6;         // Go to next state: prep for next Start
              }
              USICNT |= 0x01;          // Bit counter = 1, send (N)Ack bit
              break;

      case 6: // Prep for Start condition
              USICTL0 &= ~USIOE;       // SDA = input
              SLV_Addr = 0x90;         // Reset slave address
              I2C_State = 0;           // Reset state machine
              break;

      case 8: // Send Data byte
              USICTL0 |= USIOE;        // SDA = output
              USISRL = SLV_Data;       // Send data byte
              USICNT |=  0x08;         // Bit counter = 8, TX data
              I2C_State = 10;          // Go to next state: receive (N)Ack
              break;

      case 10:// Receive Data (N)Ack
              USICTL0 &= ~USIOE;       // SDA = input
              USICNT |= 0x01;          // Bit counter = 1, receive (N)Ack
              I2C_State = 12;          // Go to next state: check (N)Ack
              break;

      case 12:// Process Data Ack/NAck
              if (USISRL & 0x01)       // If Nack received...
              {
                P1OUT |= 0x01;         // LED on: error
              }
              else                     // Ack received
              {
                P1OUT &= ~0x01;        // LED off
                SLV_Data++;            // Increment Slave data
              }
              // Prep for Start condition
              USICTL0 &= ~USIOE;       // SDA = input
              SLV_Addr = 0x90;         // Reset slave address
              I2C_State = 0;           // Reset state machine
              break;
    }

  USICTL1 &= ~USIIFG;                  // Clear pending flags
}
