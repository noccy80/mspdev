//******************************************************************************
//  MSP430F41x2 Demo - USCI_B0 I2C Master RX single bytes from MSP430 Slave
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  reads from the slave. This is the master code. The data from the slave
//  transmitter begins at 0 and increments with each transfer. The received
//  data is in R5 and is checked for validity. If the received data is
//  incorrect, the CPU is trapped and the P5.1 LED will stay on. The USCI_B0
//  RX interrupt is used to know when new data has been received.
//  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.2MHz
//
//                                /|\  /|\
//               MSP430F41x2      10k  10k     MSP430F41x2
//                   slave         |    |        master
//             -----------------   |    |  -----------------
//           -|XIN  P6.2/UCB0SDA|<-|---+->|P6.2/UCB0SDA  XIN|-
//            |                 |  |      |                 | 32kHz
//           -|XOUT             |  |      |             XOUT|-
//            |     P6.1/UCB0SCL|<-+----->|P6.1/UCB0SCL     |
//            |                 |         |             P5.1|--> LED
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include "msp430x41x2.h"

unsigned char RXData;
unsigned char RXCompare;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P5OUT &= ~0x02;                           // P5.1 =0
  P5DIR |= 0x02;                            // P5.1 output
  P6SEL |= BIT1 + BIT2;                     // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
  UCB0BR1 = 0;
  UCB0I2CSA = 0x048;                        // Slave Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  IE2 |= UCB0RXIE;                          // Enable RX interrupt
  RXCompare = 0;                            // Used to check incoming data

  while (1)
  {
    while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
    UCB0CTL1 |= UCTXSTT;                    // I2C start condition
    while (UCB0CTL1 & UCTXSTT);             // Start condition sent?
    UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts

    if (RXData != RXCompare)                // Trap CPU if wrong
    {
      P5OUT |= 0x02;                        // P5.1 = 1
      while (1);                            // Trap CPU
    }

    RXCompare++;                            // Increment correct RX value
  }
}

// USCI_B0 Data ISR
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  RXData = UCB0RXBUF;                       // Get RX data
  __bic_SR_register_on_exit(CPUOFF);        // Exit LPM0
}
