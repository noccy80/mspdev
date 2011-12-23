//******************************************************************************
//   MSP430F22x4 Demo - USCI_B0, SPI Interface to TLC549 8-Bit ADC
//
//   Description: This program demonstrate USCI_B0 in SPI mode interfaced to a
//   TLC549 8-bit ADC. If AIN > 0.5(REF+ - REF-), P1.0 set, else reset.
//   R15 = 8-bit ADC code.
//   ACLK = n/a, MCLK = SMCLK = DCO ~1.2MHz, BRCLK = SMCLK/2
//   //* VCC must be at least 3v for TLC549 *//
//
//                         MSP430F22x4
//                       -----------------
//                   /|\|              XIN|-
//        TLC549      | |                 |
//    -------------   --|RST          XOUT|-
//   |           CS|<---|P3.0             |
//   |      DATAOUT|--->|P3.2/UCB0SOMI    |
// ~>| IN+  I/O CLK|<---|P3.3/UCB0CLK     |
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
  char data;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // P1.0 output
  P3SEL |= 0x0C;                            // P3.3,2 USCI_B0 option select
  P3DIR |= 0x01;                            // P3.0 output direction
  UCB0CTL0 |= UCMSB + UCMST + UCSYNC;       // 3-pin, 8-bit SPI mstr, MSB 1st
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  UCB0BR0 = 0x02;
  UCB0BR1 = 0;
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

  while(1)
  {
    P3OUT &= ~0x01;                         // Enable TLC549, /CS reset
    UCB0TXBUF = 0x00;                       // Dummy write to start SPI
    while (!(IFG2 & UCB0RXIFG));            // USCI_B0 RX buffer ready?

    data = UCB0RXBUF;                       // data = 00|DATA

    P3OUT |= 0x01;                          // Disable TLC549, /CS set
    P1OUT &= ~0x01;                         // P1.0 = 0

    if (data >= 0x7F)                       // data = AIN > 0.5(REF+ - REF-)?
      P1OUT |= 0x01;                        // P1.0 = 1
  }
}
