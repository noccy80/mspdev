//******************************************************************************
//  MSP-FET430P120 Demo - USART0, SPI Interface with HC165/164 Shift Registers
//
//  Description: Demonstrate USART0 in two-way SPI mode. Data are read from
//  an HC165, and same data written back to the HC164.
//  ACLK = n/a  MCLK = SMCLK = defaul DCO = UCLK0 = DCO/2
//  // **SWRST** please see MSP430x1xx Users Guide for complete description //
//  //* USART0 interrupt flags may be in different SFR's from other MSP430's *//
//
//                         MSP430F123(2)
//                       -----------------
//                   /|\|              XIN|-
//                    | |                 |     ^      HC164
//          HC165     --|RST          XOUT|-    |  -------------
//        ----------    |                 |     |-|/CLR,B       |  8
//    8  |      /LD|<---|P3.0   SIMO0/P3.1|------>|A          Qx|--\->
//   -\->|A-H   CLK|<---|P3.3/UCLK0 - P3.3|------>|CLK          |
//     |-|INH    QH|--->|P3.2/SOMI0       |       |             |
//     |-|SER      |    |                 |       |             |
//     - |         |    |                 |       |             |
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x12x2.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ME2 |= USPIE0;                            // Enable USART0 SPI mode
  UCTL0 |= CHAR+SYNC+MM;                    // 8-bit SPI Master
  UTCTL0 |= CKPH+SSEL1+SSEL0+STC;           // SMCLK, 3-pin mode
  UBR00 = 0x02;                             // UCLK/2
  UBR10 = 0x00;                             // 0
  UMCTL0 = 0x00;                            // no modulation
  UCTL0 &= ~SWRST;                          // Initalise USART state machine
  P3SEL |= 0x0E;                            // P3.1-3 SPI option select
  P3DIR |= 0x01;                            // P3.0 output direction

  while (1)
  {
    volatile unsigned int i;
    for (i = 0xFFFF; i > 0; i--);             // Delay
    while ((IFG2 & UTXIFG0) == 0);            // USART0 TX buffer ready?
    P3OUT &= ~0x01;                           // Latch data into 'HC165
    P3OUT |= 0x01;
    TXBUF0 = RXBUF0;                          // RXBUF0 to TXBUF0
  }
}
