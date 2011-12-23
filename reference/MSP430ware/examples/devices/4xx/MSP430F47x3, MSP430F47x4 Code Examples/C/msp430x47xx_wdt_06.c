//******************************************************************************
//  MSP430x47xx Demo - WDT+ Failsafe Clock, 32kHz ACLK
//
//  Description; Allow WDT+ in watchdog to timeout sourced by ACLK. LPM3 is
//  entered, this example will demonstrate WDT+ feature by automatically
//  re-enabling WDT+ clock source as DCO if external XTAL fails. This can be
//  seen as a continued, though faster as clocked by DCO, watchdog timeout
//  which will toggle on P5.1 in main function.
//  ACLK = 32kHz, MCLK = SMCLK = default DCO ~1.2MHz
//
//               MSP430x47xx
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//  P. Thanigai / K.Venkat
//  Texas Instruments Inc.
//  November 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x47x4.h"

void main(void)
{
  WDTCTL = WDT_ARST_1000;                   // Set Watchdog Timer timeout 1s
  P5DIR |= BIT1;                            // Set P5.1 to output
  P5OUT ^= BIT1;                            // Toggle P5.1
  __bis_SR_register(LPM3_bits);             // Enter LPM3
}
