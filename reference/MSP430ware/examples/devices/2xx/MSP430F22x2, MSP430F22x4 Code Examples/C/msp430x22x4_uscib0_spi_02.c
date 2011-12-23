//******************************************************************************
//   MSP430F22x4 Demo - USCI_B0, SPI Interface to TLV1549 10-Bit ADC
//
//   Description: This program demonstrate USCI_B0 in SPI mode interfaced to a
//   TLV1549 10-bit ADC. If AIN > 0.5(REF+ - REF-), P1.0 set, else reset.
//   R15 = MSB|LSB, left justified.  R14 also used and not saved.
//   ACLK = n/a, MCLK = SMCLK = DCO ~1.2MHz, BRCLK = SMCLK/2
//   //* VCC must be at least 3v for TLV1549 *//
//
//                         MSP430F22x4
//                       -----------------
//                   /|\|              XIN|-
//       TLV1549      | |                 |
//    -------------   --|RST          XOUT|-
//   |           CS|<---|P3.0             |
//   |      DATAOUT|--->|P3.2/UCB0SOMI    |
// ~>|AIN+  I/O CLK|<---|P3.3/UCB0CLK     |
//   |             |    |             P1.0|--> LED
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   April 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  unsigned int data1, data2;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // P1.0 output
  P3SEL |= 0x0C;                            // P3.2,3 USCI_B0 option select
  P3DIR |= 0x01;                            // P3.0 output direction
  UCB0CTL0 |= UCMSB + UCMST + UCSYNC;       // 3-pin, 8-bit SPI mstr, MSB 1st
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  UCB0BR0 = 0x02;
  UCB0BR1 = 0;
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

  while(1)
  {
    P3OUT &= ~0x01;                         // Enable TLV1549, /CS reset
    UCB0TXBUF = 0x00;                       // Dummy write to start SPI
    UCB0TXBUF = 0x00;

    while (!(IFG2 & UCB0RXIFG));            // USCI_B0 TX buffer ready?
    data1 = UCB0RXBUF;                      // R15 = 00|MSB
    data1 = data1 << 8;
    while (!(IFG2 & UCB0RXIFG));            // USCI_B0 TX buffer ready?
    data2 = UCB0RXBUF;
    data1 = data1 + data2;                  // R14 = 00|LSB

    P3OUT |= 0x01;                          // Disable TLV1549, /CS set
    P1OUT &= ~0x01;                         // P1.0 = 0

    if (data1 > 0x7FE0)                     // Test for correct character RX'd
      P1OUT |= 0x01;                        // P1.0 = 1
  }
}
