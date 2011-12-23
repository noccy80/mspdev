//******************************************************************************
//  MSP430x24x Demo - USCI_B1 I2C Master TX single bytes to MSP430 Slave
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  transmits to the slave. This is the master code. It continuously
//  transmits 00h, 01h, ..., 0ffh and demonstrates how to implement an I2C
//  master transmitter sending a single byte using the USCI_B1 TX interrupt.
//  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.045Mhz
//
//                                /|\  /|\
//               MSP430F249      10k  10k     MSP430F249
//                   slave         |    |        master
//             -----------------   |    |  -----------------
//           -|XIN  P5.1/UCB1SDA|<-|---+->|P5.1/UCB1SDA  XIN|-
//            |                 |  |      |                 |
//           -|XOUT             |  |      |             XOUT|-
//            |     P5.2/UCB1SCL|<-+----->|P5.2/UCB1SCL     |
//            |                 |         |                 |
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x24x.h"

unsigned char TXData;
unsigned char TXByteCtr;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P5SEL |= 0x06;                            // Assign I2C pins to USCI_B1
  UCB1CTL1 |= UCSWRST;                      // Enable SW reset
  UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
  UCB1CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCB1BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
  UCB1BR1 = 0;
  UCB1I2CSA = 0x48;                         // Slave Address is 048h
  UCB1CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UC1IE |= UCB1TXIE;                        // Enable TX interrupt

  TXData = 0x01;                            // Holds TX data

  while (1)
  {
    TXByteCtr = 1;                          // Load TX byte counter
    while (UCB1CTL1 & UCTXSTP);             //Ensure stop condition got sent
    UCB1CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
                                            // Remain in LPM0 until all data
                                            // is TX'd
    TXData++;                               // Increment data byte
  }
}

//------------------------------------------------------------------------------
// The USCIAB1TX_ISR is structured such that it can be used to transmit any
// number of bytes by pre-loading TXByteCtr with the byte count.
//------------------------------------------------------------------------------
#pragma vector = USCIAB1TX_VECTOR
__interrupt void USCIAB1TX_ISR(void)
{
  if (TXByteCtr)                            // Check TX byte counter
  {
    UCB1TXBUF = TXData;                     // Load TX buffer
    TXByteCtr--;                            // Decrement TX byte counter
  }
  else
  {
    UCB1CTL1 |= UCTXSTP;                    // I2C stop condition
    UC1IFG &= ~UCB1TXIFG;                   // Clear USCI_B1 TX int flag
    __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
  }
}
