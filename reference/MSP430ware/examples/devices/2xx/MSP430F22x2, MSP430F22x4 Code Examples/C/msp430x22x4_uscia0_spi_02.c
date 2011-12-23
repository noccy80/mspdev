//******************************************************************************
//   MSP430F22x4 Demo - USCI_A0, SPI Interface to HC165 Shift Register
//
//   Description: This program demonstrate a USCI_A0 in SPI mode interface to a
//   an 'HC165 shift register.  Read 8-bit Data from H-A into Data.
//   ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz, BRCLK = SMCLK/2
//
//                          MSP430F22x4
//                       -----------------
//                   /|\|              XIN|-
//                    | |                 |
//          HC165     --|RST          XOUT|-
//        ----------    |                 |
//    8  |      /LD|<---|P3.6             |
//   -\->|A-H   CLK|<---|P3.0/UCA0CLK     |
//     |-|INH    QH|--->|P3.5/UCA0SOMI    |
//     |-|SER      |    |                 |
//     v
//
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

volatile unsigned char Data;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P3SEL |= 0x21;                            // P3.0,5 USCI_A0 option select
  P3DIR |= 0x40;                            // P3.6 output direction
  UCA0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC; // 3-pin, 8-bit SPI master
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 |= 0x02;
  UCA0BR1 = 0;                              //
  UCA0MCTL = 0;
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

  while(1)
  {
    // Load HC165 value into Rx buffer
    P3OUT &= ~0x40;                         // Trigger low edge on HC165 /LD
    P3OUT |= 0x40;                          // Return /LD to high
    IFG2 &= ~UCA0RXIFG;                     // Clear int flag
    UCA0TXBUF = 0x00;                       // Dummy write to start SPI
    while (!(IFG2 & UCA0RXIFG));            // RXBUF ready?
    Data = UCA0RXBUF;                       // Move value
  }
}
