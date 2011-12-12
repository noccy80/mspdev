//******************************************************************************
//  MSP430F20xx Demo - WDT+ Failsafe Clock, 32kHz ACLK
//
//  Description; Allow WDT+ in watchdog to timeout sourced by ACLK. LPM3 is
//  entered, this example will demonstrate WDT+ feature by automatically
//  re-enabling WDT+ clock source as DCO if external XTAL fails. This can be
//  seen as a continued, though faster as clocked by DCO, watchdog timeout
//  which will toggle on P1.0 in main function.
//  ACLK = 32kHz, MCLK = SMCLK = default DCO
//
//		  MSP430F20xx
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  M.Buccini / L. Westlund
//  Texas Instruments, Inc
//  October 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.40A
//******************************************************************************

#include  <msp430x20x3.h>

void main(void)
{
  WDTCTL = WDT_ARST_1000;                   // Set Watchdog Timer timeout 1s
  P1DIR |= 0x01;                            // Set P1.0 to output
  P1OUT ^= 0x01;                            // Toggle P1.0
  _BIS_SR(LPM3_bits);
}
