//******************************************************************************
//  MSP430G2x21/G2x31 Demo - USI SPI Interface with HC165/164 Shift Registers
//
//  Description: Demonstrate USI in two-way SPI mode. Data are read from
//  an HC165, and same data written back to the HC164.
//  ACLK = n/a  MCLK = SMCLK = default DCO, USICLK = SMCLK/2
//  //*USART0 control bits are in different SFR's from other MSP430's//
//
//                       MSP430G2x21/G2x31
//                       -----------------
//                   /|\|              XIN|-
//                    | |                 |     ^      HC164
//          HC165     --|RST          XOUT|-    |  -------------
//        ----------    |                 |     |-|/CLR,B       |  8
//    8  |      /LD|<---|P1.1   SIMO0/P1.6|------>|A          Qx|--\->
//   -\->|A-H   CLK|<---|P1.5/SCLK0 - P1.5|------>|CLK          |
//     |-|INH    QH|--->|P1.7/SOMI0       |       |             |
//     |-|SER      |    |                 |       |             |
//     - |         |    |                 |       |             |
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include <msp430g2221.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  P1OUT = 0;
  P1OUT |= 0x02;
  P1DIR |= 0x02;
  USICTL0 |= USIPE7 + USIPE6 + USIPE5 + USIMST + USIOE; // Port, SPI Master
  USICTL1 |= USICKPH + USIIE;               // Counter interrupt, flag remains set
  USICKCTL = USIDIV_1 + USISSEL_2;          // /2 SMCLK
  USICTL0 &= ~USISWRST;                     // USI released for operation
  USICNT = 8;                               // init-load counter

  while (1)                                 // Loop
  {
    unsigned i;
    for (i = 0xFFFF; i > 0; i--);           // Delay
    while (!(USIIFG & USICTL1));            // Counter clear?
    P1OUT &= ~0x02;                         // Latch data into 'HC165
    P1OUT |= 0x02;
//  ********************                    // Read data are ready to be written
    USICNT = 8;                             // re-load counter
  }
}
