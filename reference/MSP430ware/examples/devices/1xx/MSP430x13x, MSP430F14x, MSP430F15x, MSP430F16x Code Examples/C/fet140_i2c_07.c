//******************************************************************************
//   MSP-FET430P140 Demo - I2C, Slave Reads from MSP430 Master
//
//   Description: This demo connects two MSP430's via the I2C bus.  The master
//   transmits to the slave. This is the slave code. The master code is called
//   fet140_i2c_08.c. The TX data begins at 0 and is incremented
//   each time it is sent.
//   Run the code in Slave device before starting the Master device for proper
//   communication
//   The RXRDYIFG interrupt is used to know when new data has been received.
//   ACLK = n/a, MCLK = SMCLK = I2CCLOCK = DCO ~ 800kHz
//  //* MSP430F169 Device Required *//
//
//                                 /|\  /|\
//                  MSP430F169     10k  10k     MSP430F169
//                    slave         |    |        master
//              -----------------|  |    |  -----------------
//             |             P3.1|<-|---+->|P3.1             |
//             |                 |  |      |             P1.0|-->LED
//             |                 |  |      |                 |
//             |             P3.3|<-+----->|P3.3             |
//             |                 |         |                 |
//
//
//  H. Grewal
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x16x.h>

char RXData = 0;

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0x0A;                            // Select I2C pins
  U0CTL |= I2C + SYNC;                      // Recommended init procedure
  U0CTL &= ~I2CEN;                          // Recommended init procedure
  I2CTCTL |= I2CSSEL1;                      // SMCLK
  I2COA = 0x0048;                           // Own Address is 048h
  I2CIE = RXRDYIE;                          // Enable RXRDYIFG interrupt
  U0CTL |= I2CEN;                           // Enable I2C

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}


// Common ISR for I2C Module
#pragma vector=USART0TX_VECTOR
__interrupt void I2C_ISR(void)
{
 switch( I2CIV )
 {
   case  2: break;                          // Arbitration lost
   case  4: break;                          // No Acknowledge
   case  6: break;                          // Own Address
   case  8: break;                          // Register Access Ready
   case 10:                                 // Receive Ready
      RXData = I2CDRB;                      // RX data
     _BIC_SR_IRQ(CPUOFF);                   // Clear LPM0
     break;
   case 12:  break;                         // Transmit Ready
   case 14: break;                          // General Call
   case 16: break;                          // Start Condition
 }
}




