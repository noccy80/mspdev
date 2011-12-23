//******************************************************************************
//  MSP430F51x2 Demo - WDT+ Failsafe Clock, 32kHz ACLK
//
//  Description; Allow WDT+ in watchdog to timeout sourced by ACLK. LPM3 is
//  entered, this example will demonstrate WDT+ feature by automatically
//  re-enabling WDT+ clock source as DCO if external XTAL fails. This can be
//  seen as a continued, though faster as clocked by DCO, watchdog timeout
//  which will toggle on P1.0 in main function.
//  ACLK = 32768, MCLK = SMCLK = default DCO
//
//                MSP430F51x2
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   Dec 2009
//   Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include  "msp430f5172.h"

void main(void)
{
  // Watchdog mode -> reset after expired time; WDT is clocked by ACLK
  WDTCTL = WDT_ARST_1000;                   // Set Watchdog Timer timeout 1s - SET BREAKPOINT HERE
  P1DIR |= 0x01;                            // Set P1.0 to output
  P1OUT ^= 0x01;                            // Toggle P1.0
  
  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3
  __no_operation();                         // For debugger
  
}
