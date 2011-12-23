//******************************************************************************
//  MSP-FET430P140 Demo - I2C, Slave Writes to MSP430 Master RX in Repeat Mode
//
//  Description: This demo connects two MSP430's via the I2C bus.  The master
//  reads from the slave in repeat mode. This is the slave code. The master
//  code is called fet140_i2c_09.c. The TX data begins at 0 and is
//  incremented each time it is sent. The master checks the data it receives
//  for validity. If it is incorrect, it stops communicating and the P1.0 LED
//  will stay on.
//  The TXRDYIFG interrupt is used to know when to TX.
//  The Slave has a delay in data transmission and so holds the SCL low until
//  the byte is transmited
//  ACLK = n/a, MCLK = SMCLK = I2CCLOCK = DCO ~ 800kHz
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
//  H. Grewal/A. Dannenberg
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x16x.h>

char TXData = 0;

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0x0A;                            // Select I2C pins
  U0CTL |= I2C + SYNC;                      // Recommended init procedure
  U0CTL &= ~I2CEN;                          // Recommended init procedure
  I2CTCTL |= I2CSSEL1;                      // SMCLK
  I2COA = 0x0048;                           // Own Address is 048h
  I2CIE = TXRDYIE;                          // Enable TXRDYIFG interrupt
  U0CTL |= I2CEN;                           // Enable I2C

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}


// Common ISR for I2C Module
#pragma vector=USART0TX_VECTOR
__interrupt void I2C_ISR(void)
{
 volatile unsigned int i = 0;
 switch( I2CIV )
 {
   case  2: break;                          // Arbitration lost
   case  4: break;                          // No Acknowledge
   case  6: break;                          // Own Address
   case  8: break;                          // Register Access Ready
   case 10: break;                          // Receive Ready
   case 12:                                 // Transmit Ready
     for(i=0;i<50;i++);                     // Delay Data, Hold SCL Low
     I2CDRB = TXData++;                     // Load I2CDRB and increment
     break;
   case 14: break;                          // General Call
   case 16: break;                          // Start Condition
 }
}




