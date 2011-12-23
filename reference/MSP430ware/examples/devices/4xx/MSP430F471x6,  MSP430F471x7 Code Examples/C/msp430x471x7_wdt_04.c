//******************************************************************************
//  MSP430x471xx Demo - WDT+ Failsafe Clock, DCO SMCLK
//
//  Description; Allow WDT+ in watchdog to timeout. Toggle P5.1 in main
//  function. LPM4 is entered, this example will demonstrate WDT+ feature
//  of preventing WDT+ clock to be disabled.
//  The WDT+ will not allow active WDT+ clock to be disabled by software, the
//  LED continues to Flash because the WDT times out normally even though
//  software has attempted to disable WDT+ clock source.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
//
//               MSP430x471xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include "msp430x471x7.h"

void main(void)
{
  P5DIR |= BIT1;                            // Set P5.1 to output
  P5OUT ^= BIT1;                            // Toggle P5.1
  __bis_SR_register(LPM4_bits + GIE);       // Stop all clocks
}
