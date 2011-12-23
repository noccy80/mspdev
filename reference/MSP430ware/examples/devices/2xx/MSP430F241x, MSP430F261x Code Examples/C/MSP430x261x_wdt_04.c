//******************************************************************************
//  MSP430x26x Demo - WDT+ Failsafe Clock, WDT mode, DCO SMCLK
//
//  Description; Allow WDT+ in watchdog mode to timeout. Toggle P1.0 in main
//  function. LPM4 is entered, this example will demonstrate WDT+ feature
//  of preventing WDT+ clock to be disabled.
//  The WDT+ will not allow active WDT+ clock to be disabled by software, the
//  LED continues to Flash because the WDT times out normally (in 32768 DCOCLK 
//  cycles) even though software has attempted to disable WDT+ clock source.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.045MHz
//
//                MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"

void main(void)
{
  P1DIR |= 0x01;                            // Set P1.0 to output - SET BREAKPOINT HERE
  P1OUT ^= 0x01;                            // Toggle P1.0
  __bis_SR_register(LPM4_bits + GIE);       // Stop all clocks
}
