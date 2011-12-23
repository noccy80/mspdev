//******************************************************************************
//  MSP430G2x21/G2x31 Demo - I2C Master Transmitter, single byte
//
//  Description: I2C Master communicates with I2C Slave using
//  the USI. Master data is sent and increments from 0x00 with each transmitted
//  byte which is verified by the slave.
//  LED off for address or data Ack; LED on for address or data NAck.
//  ACLK = n/a, MCLK = SMCLK = Calibrated 1MHz
//
//  ***THIS IS THE MASTER CODE***
//
//                  Slave                      Master
//          (msp430g2x21_usi_08.c)
//             MSP430G2x21/G2x31          MSP430G2x21/G2x31
//             -----------------          -----------------
//         /|\|              XIN|-    /|\|              XIN|-
//          | |                 |      | |                 |
//          --|RST          XOUT|-     --|RST          XOUT|-
//            |                 |        |                 |
//      LED <-|P1.0             |        |                 |
//            |                 |        |             P1.0|-> LED
//            |         SDA/P1.7|<-------|P1.7/SDA         |
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

char MST_Data = 0;                     // Variable for transmitted data
char SLV_Addr = 0x90;                  // Address is 0x48 << 1 bit + 0 for Write
int I2C_State = 0;                     // State variable

void main(void)
{
  volatile unsigned int i;             // Use volatile to prevent removal

  WDTCTL = WDTPW + WDTHOLD;            // Stop watchdog
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                          // If calibration constants erased
                                       // do not load, trap CPU!!
  }   
  BCSCTL1 = CALBC1_1MHZ;               // Set DCO
  DCOCTL = CALDCO_1MHZ;

  P1OUT = 0xC0;                        // P1.6 & P1.7 Pullups, others to 0
  P1REN |= 0xC0;                       // P1.6 & P1.7 Pullups
  P1DIR = 0xFF;                        // Unused pins as outputs
  P2OUT = 0;
  P2DIR = 0xFF;

  USICTL0 = USIPE6+USIPE7+USIMST+USISWRST; // Port & USI mode setup
  USICTL1 = USII2C+USIIE;              // Enable I2C mode & USI interrupt
  USICKCTL = USIDIV_3+USISSEL_2+USICKPL; // Setup USI clocks: SCL = SMCLK/8 (~125kHz)
  USICNT |= USIIFGCC;                  // Disable automatic clear control
  USICTL0 &= ~USISWRST;                // Enable USI
  USICTL1 &= ~USIIFG;                  // Clear pending flag
  _EINT();

  while(1)
  {
    USICTL1 |= USIIFG;                 // Set flag and start communication
    LPM0;                              // CPU off, await USI interrupt
    _NOP();                            // Used for IAR
    for (i = 0; i < 5000; i++);        // Dummy delay between communication cycles
  }
}

/******************************************************
// USI interrupt service routine
******************************************************/
#pragma vector = USI_VECTOR
__interrupt void USI_TXRX (void)
{
  switch(I2C_State)
    {
      case 0: // Generate Start Condition & send address to slave
              P1OUT |= 0x01;           // LED on: sequence start
              USISRL = 0x00;           // Generate Start Condition...
              USICTL0 |= USIGE+USIOE;
              USICTL0 &= ~USIGE;
              USISRL = SLV_Addr;       // ... and transmit address, R/W = 0
              USICNT = (USICNT & 0xE0) + 0x08; // Bit counter = 8, TX Address
              I2C_State = 2;           // Go to next state: receive address (N)Ack
              break;

      case 2: // Receive Address Ack/Nack bit
              USICTL0 &= ~USIOE;       // SDA = input
              USICNT |= 0x01;          // Bit counter = 1, receive (N)Ack bit
              I2C_State = 4;           // Go to next state: check (N)Ack
              break;

      case 4: // Process Address Ack/Nack & handle data TX
              USICTL0 |= USIOE;        // SDA = output
              if (USISRL & 0x01)       // If Nack received...
              { // Send stop...
                USISRL = 0x00;
                USICNT |=  0x01;       // Bit counter = 1, SCL high, SDA low
                I2C_State = 10;        // Go to next state: generate Stop
                P1OUT |= 0x01;         // Turn on LED: error
              }
              else
              { // Ack received, TX data to slave...
                USISRL = MST_Data;     // Load data byte
                USICNT |=  0x08;       // Bit counter = 8, start TX
                I2C_State = 6;         // Go to next state: receive data (N)Ack
                P1OUT &= ~0x01;        // Turn off LED
              }
              break;

      case 6: // Receive Data Ack/Nack bit
              USICTL0 &= ~USIOE;       // SDA = input
              USICNT |= 0x01;          // Bit counter = 1, receive (N)Ack bit
              I2C_State = 8;           // Go to next state: check (N)Ack
              break;

      case 8: // Process Data Ack/Nack & send Stop
              USICTL0 |= USIOE;
              if (USISRL & 0x01)       // If Nack received...
                P1OUT |= 0x01;         // Turn on LED: error
              else                     // Ack received
              {
                MST_Data++;            // Increment Master data
                P1OUT &= ~0x01;        // Turn off LED
              }
              // Send stop...
              USISRL = 0x00;
              USICNT |=  0x01;         // Bit counter = 1, SCL high, SDA low
              I2C_State = 10;          // Go to next state: generate Stop
              break;

      case 10:// Generate Stop Condition
              USISRL = 0x0FF;          // USISRL = 1 to release SDA
              USICTL0 |= USIGE;        // Transparent latch enabled
              USICTL0 &= ~(USIGE+USIOE);// Latch/SDA output disabled
              I2C_State = 0;           // Reset state machine for next transmission
              LPM0_EXIT;               // Exit active for next transfer
              break;
    }

  USICTL1 &= ~USIIFG;                  // Clear pending flag
}
