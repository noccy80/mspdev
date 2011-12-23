//******************************************************************************
//  MSP-FET430P140 Demo - I2C, Master Reads from MSP430 Slave in Repeat Mode
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  reads from the slave in repeat mode. This is the master code. The slave
//  code is called fet140_i2c_10.c. The data from the slave TX
//  begins at 0 and is incremented with each transfer. The received data is in
//  RXData and is checked for validity. If the received data is incorrect, the
//  CPU is trapped and the P1.0 LED will stay on. The RXRDYIFG interrupt is
//  used to know when new data has been received.
//  A Stop is issued after Master receives 6 bytes and then a new Start is
//  issued.
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

char RXData = 0;
unsigned int i = 0;
char TestData = 0;

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0x0A;                            // Select I2C pins
  P1OUT = 0;                                // Clear P1.0
  P1DIR |= 0x01;                            // P1.0 output

  U0CTL |= I2C + SYNC;                      // Recommended init procedure
  U0CTL &= ~I2CEN;                          // Recommended init procedure
  I2CTCTL = I2CSSEL1 + I2CRM;               // SMCLK, repeat Mode
  I2CSA = 0x0048;                           // Slave Address is 048h
  I2CIE = RXRDYIE;                          // Enable RXRDYIFG interrupt
  U0CTL |= I2CEN;                           // Enable I2C

  _EINT();                                  // Enable interrupts

  U0CTL |= MST;                             // Master mode
  I2CTCTL |= I2CSTT;                        // Initiate transfer

  while (1)
  {
    if (i == 6)
    {
     i = 0;
     TestData++;
     I2CTCTL |= I2CSTP;
     while (I2CTCTL & I2CSTP);              // Check Stop Condition
     U0CTL |= MST;
     I2CTCTL |= I2CSTT;

    }
    i++;
    _BIS_SR(CPUOFF);                        // Enter LPM0
    P1OUT |= 0x01;                          // Set P1.0
    if (TestData++ != RXData) break;        // Test received data
    P1OUT &= ~0x01;                         // Clear P1.0
  }

  while (1);                                // Trap CPU

}

// Common ISR for I2C Module
#pragma vector=USART0TX_VECTOR
__interrupt void I2C_ISR(void)
{
 switch(I2CIV)
 {
   case  0: break;                          // No interrupt
   case  2: break;                          // Arbitration lost
   case  4: break;                          // No Acknowledge
   case  6: break;                          // Own Address
   case  8: break;                          // Register Access Ready
   case 10:                                 // Receive Ready
     RXData = I2CDRB;                       // RX data
     _BIC_SR_IRQ(CPUOFF);                   // Clear LPM0
     break;
   case 12: break;                          // Transmit Ready
   case 14: break;                          // General Call
   case 16: break;                          // Start Condition
 }
}
