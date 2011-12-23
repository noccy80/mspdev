//******************************************************************************
//    MSP430x471xx Demo - Software Poll P2.7, Set P5.1 if P2.7 = 1
//
//   Description: Poll P2.7 in a loop, if HI, P5.1 is set, if LOW, P5.1 reset.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                 MSP430x471xx
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//      /|\   |                 |
//       --o--|P2.7         P5.1|-->LED
//      \|/
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P5DIR |= BIT1;                            // P5.1 output

  while(1)
    if (P2IN&BIT7)                          // P2.7 hi/low?
      P5OUT |= BIT1;                        // P5.1 = 1 / LED ON
    else
      P5OUT &= ~BIT1;                       // P5.1 = 0 / LED OFF
}
