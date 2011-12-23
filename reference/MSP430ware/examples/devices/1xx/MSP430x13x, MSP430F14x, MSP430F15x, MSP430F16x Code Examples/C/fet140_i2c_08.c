//************************************************************************************
//   MSP-FET430P140 Demo - I2C, Master Writes Multiple Bytes to MSP430 Slave
//
//   Description: This demo connects two MSP430's via the I2C bus. The master
//   writes 3 bytes to the slave. This is the master code. The slave code is called
//   fet140_i2c_07.c. The TX data is incremented each time it is sent.
//
//
//                                 /|\  /|\
//                  MSP430F169     10k  10k     MSP430F169
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
void delay (void);
char TXData = 0;

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= 0x0A;                            // Select I2C pins
  U0CTL |= I2C + SYNC;                      // Recommended init procedure
  U0CTL &= ~I2CEN;                          // Recommended init procedure
  I2CTCTL |= I2CSSEL1 + I2CTRX;             // SMCLK, transmit
  I2CNDAT = 0x03;                           // Write Three bytes
  I2CSA = 0x0048;                           // Slave Address is 048h
  U0CTL |= I2CEN;                           // Enable I2C

  U0CTL |= MST;                             // Master mode
  I2CTCTL |= I2CSTT + I2CSTP;               // Initiate transfer
  while ((I2CIFG & TXRDYIFG) == 0);         // Wait for transmitter to be ready
  I2CDRB = TXData;                          // Load  I2CDRB
  while ((I2CIFG & TXRDYIFG) == 0);         // Wait for transmitter to be ready
  TXData++;                                 // Increment TX data
  I2CDRB = TXData;                          // Load  I2CDRB
  while ((I2CIFG & TXRDYIFG) == 0);         // Wait for transmitter to be ready
  TXData++;                                 // Increment TX data
  I2CDRB = TXData;                          // Load  I2CDRB

  while(1);

}
