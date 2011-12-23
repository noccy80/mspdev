//******************************************************************************
//  MSP430x41x2 Demo - WDT, Toggle P5.1, Interval Overflow ISR, 32kHz ACLK
//
//  Description: Toggle P5.1 using software timed by WDT ISR. Toggle rate is
//  exactly 250ms based on 32kHz ACLK WDT clock source. In this example the
//  WDT is configured to divide 32768 watch-crystal(2^15) by 2^13 with an ISR
//  triggered @ 4Hz = [WDT CLK source/32768].
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO ~1.045MHz
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//
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
  WDTCTL = WDT_ADLY_250;                    // WDT 250ms, ACLK, interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P5DIR |= 0x02;                            // Set P5.1 to output direction

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P5OUT ^= 0x02;                            // Toggle P5.1 using exclusive-OR
}

