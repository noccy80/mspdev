//******************************************************************************
//  MSP430x41x2 Demo - WDT+ Failsafe Clock, 32kHz ACLK
//
//  Description; Allow WDT+ in watchdog to timeout sourced by ACLK. LPM3 is
//  entered, this example will demonstrate WDT+ feature by automatically
//  re-enabling WDT+ clock source as DCO if external XTAL fails. This can be
//  seen as a continued, though faster as clocked by DCO, watchdog timeout
//  which will toggle on P5.1 in main function.
//  ACLK = 32768, MCLK = SMCLK = default DCO ~1.045MHz
//
//              MSP430x41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include  <msp430x41x2.h>

void main(void)
{
  // Watchdog mode -> reset after expired time; WDT is clocked by ACLK
  WDTCTL = WDT_ARST_1000;                   // Set Watchdog Timer timeout 1s - SET BREAKPOINT HERE
  P5DIR |= 0x02;                            // Set P5.1 to output
  P5OUT ^= 0x02;                            // Toggle P5.1
  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3
}
