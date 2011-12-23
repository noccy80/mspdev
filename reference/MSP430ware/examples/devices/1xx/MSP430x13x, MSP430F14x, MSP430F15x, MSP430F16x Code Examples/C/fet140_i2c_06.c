//******************************************************************************
//   MSP-FET430P140 Demo - I2C, Master Transmits to MSP430 Slave RX
//
//   Description: This demo connects two MSP430's via the I2C bus. The master
//   transmits to the slave. This is the master code. The slave code is called
//   fet140_i2c_07.c. Master continuously transmits 0x5A inside
//   the TX ISR
//   Run the code in Slave device before starting the Master device for proper
//   communication
//   The TXRDYIFG interrupt is used to know when to TX
//   ACLK = n/a, MCLK = SMCLK = I2CCLOCK = DCO ~ 800kHz
//  //* MSP430F169 Device Required *//
//
//                                 /|\  /|\
//                  MSP430F169     10k  10k     MSP430F169
//                    slave         |    |        master
//              -----------------|  |    |  -----------------
//             |             P3.1|<-|---+->|P3.1             |
//             |                 |  |      |                 |
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

void main (void)
{

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0x0A;                            // Select I2C pins

  U0CTL |= I2C + SYNC;                      // Recommended init procedure
  U0CTL &= ~I2CEN;                          // Recommended init procedure
  I2CTCTL |= I2CSSEL1;                      // SMCLK
  I2CNDAT = 0x01;                           // Write one byte
  I2CSA = 0x0048;                           // Slave Address is 048h
  I2CIE = TXRDYIE;                          // Enable RXRDYIFG interrupt
  U0CTL |= I2CEN;                           // Enable I2C

  _EINT();                                  // Enable interrupts

  while (1)
  {
    U0CTL |= MST;                           // Master mode
    I2CTCTL |= I2CSTT + I2CSTP + I2CTRX;    // Initiate transfer
    _BIS_SR(CPUOFF);                        // Enter LPM0
  }

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
   case 10: break;                          // Receive Ready
   case 12:
     I2CDRB = 0x5A;                         // TX data
     while (I2CBUSY & I2CDCTL);             // I2C ready?
     _BIC_SR_IRQ(CPUOFF);                   // Clear LPM0
     break;                                 // Transmit Ready

   case 14: break;                          // General Call
   case 16: break;                          // Start Condition
 }
}