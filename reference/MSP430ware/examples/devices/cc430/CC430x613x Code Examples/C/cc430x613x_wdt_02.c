//******************************************************************************
//   CC430F613x Demo - WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using software timed by WDT ISR. Toggle rate is
//  exactly 250ms based on 32kHz ACLK WDT clock source. In this example the
//  WDT is configured to divide 32768 watch-crystal(2^15) by 2^13 with an ISR
//  triggered @ 4Hz = [WDT CLK source/32768].
//  ACLK = REFO , MCLK = SMCLK = default DCO ~1.045MHz
//
//
//                CC430F6137
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x613x.h"

void main(void)
{
  WDTCTL = WDT_ADLY_250;                    // WDT 250ms, ACLK, interval timer
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, enable interrupts
  __no_operation();                         // For debugger
}

// Watchdog Timer interrupt service routine
#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 using exclusive-OR
}

