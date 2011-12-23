//******************************************************************************
//  MSP430x41x2 Demo - WDT+ Failsafe Clock, WDT mode, DCO SMCLK
//
//  Description; Allow WDT+ in watchdog mode to timeout. Toggle P5.1 in main
//  function. LPM4 is entered, this example will demonstrate WDT+ feature
//  of preventing WDT+ clock to be disabled.
//  The WDT+ will not allow active WDT+ clock to be disabled by software, the
//  LED continues to Flash because the WDT times out normally (in 32768 DCOCLK 
//  cycles) even though software has attempted to disable WDT+ clock source.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.045MHz
//
//              MSP430x41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
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
  P5DIR |= 0x02;                            // Set P5.1 to output - SET BREAKPOINT HERE
  P5OUT ^= 0x02;                            // Toggle P5.1
  __bis_SR_register(LPM4_bits + GIE);       // Stop all clocks
}
