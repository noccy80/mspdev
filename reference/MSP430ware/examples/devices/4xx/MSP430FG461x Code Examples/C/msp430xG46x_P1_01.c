//******************************************************************************
//   MSP430xG46x Demo - Software Poll P1.4, Set P5.1 if P1.4 = 1
//
//   Description: Poll P1.4 in a loop, if HI, P5.1 is set, if LOW, P5.1 reset.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                MSP430xG461x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//      /|\   |                 |
//       --o--|P1.4         P5.1|-->LED
//      \|/
//
//   K. Quiring/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P5DIR |= 0x002;                           // P5.1 output

  while(1)
    if (P1IN&0x10)                          // P1.4 hi/low?
      P5OUT |= 0x002;                       // P5.1 = 1 / LED ON
    else
      P5OUT &= ~0x002;                      // P5.1 = 0 / LED OFF
}
