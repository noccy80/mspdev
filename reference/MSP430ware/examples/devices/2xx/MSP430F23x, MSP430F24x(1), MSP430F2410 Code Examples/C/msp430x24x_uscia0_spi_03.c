//******************************************************************************
//   MSP430x24x Demo - USCI_A0, SPI Interface to HC165/164 Shift Registers
//
//   Description: Demonstrate USCI_A0 in two-way SPI mode. Data are read from
//   an HC165, and same data written back to the HC164.
//   ACLK = n/a  MCLK = SMCLK = DCOCLK = ~1.045Mhz, BRCLK = SMCLK/2
//
//                            MSP430F249
//                       --------------------
//                   /|\|                 XIN|-
//                    | |                    |     ^      HC164
//          HC165     --|RST             XOUT|-    |  -------------
//        ----------    |                    |     |-|/CLR,B       |  8
//    8  |      /LD|<---|P3.6   UCA0SIMO/P3.4|------>|A          Qx|--\->
//   -\->|A-H   CLK|<---|P3.0/UCA0CLK -- P3.0|------>|CLK          |
//     |-|INH    QH|--->|P3.5/UCA0SOMI       |       |             |
//     |-|SER      |    |                    |       |             |
//     - |         |    |                    |       |             |
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x24x.h"

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P3SEL |= 0x31;                            // P3.0,4,5 USCI_A0 option select
  P3DIR |= 0x40;                            // P3.6 output direction
  UCA0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 |= 0x02;
  UCA0BR1 = 0;
  UCA0MCTL = 0;
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

  while(1)                                  //
  {
    while (!(IFG2 & UCA0TXIFG));            // USCI_A0 TX buffer ready?
    P3OUT &= ~0x40;                         // Latch data into 'HC165
    P3OUT |= 0x40;                          //
    UCA0TXBUF = UCA0RXBUF;                  // Previous data to TX, RX next
    for(i = 0xFFFF; i > 0; i--);            // Delay
  }
}
