//******************************************************************************
//    MSP430x47xx Demo - Software Poll P1.4, Set P5.1 if P1.4 = 1
//
//   Description: Poll P1.4 in a loop, if HI, P5.1 is set, if LOW, P5.1 reset.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                 MSP430x47xx
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//      /|\   |                 |
//       --o--|P1.4         P5.1|-->LED
//      \|/
//
//  P. Thanigai / K.Venkat
//  Texas Instruments Inc.
//  November 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x47x4.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P5DIR |= BIT1;                            // P5.1 output

  while(1)
    if (P1IN&BIT4)                          // P1.4 hi/low?
      P5OUT |= BIT1;                        // P5.1 = 1 / LED ON
    else
      P5OUT &= ~BIT1;                       // P5.1 = 0 / LED OFF
}
