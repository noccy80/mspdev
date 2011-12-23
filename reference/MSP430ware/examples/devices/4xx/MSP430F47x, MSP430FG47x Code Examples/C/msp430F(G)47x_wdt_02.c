//******************************************************************************
//   MSP430F(G)47x Demo - WDT, Toggle P4.6, Interval Overflow ISR, 32kHz ACLK
//
//  Description: Toggle P4.6 using software timed by WDT ISR. Toggle rate is
//  exactly 250ms based on 32kHz ACLK WDT clock source. In this example the
//  WDT is configured to divide 32768 watch-crystal(2^15) by 2^13 with an ISR
//  triggered @ 4Hz.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//              MSP430F(G)47x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P4.6|-->LED
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//*****************************************************************************
#include "msp430xG47x.h"

void main(void)
{
  WDTCTL = WDT_ADLY_250;                    // WDT 250ms, ACLK, interval timer
  FLL_CTL0 |= XCAP18PF;                     // Set load capacitance for xtal
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P4DIR |= 0x40;                            // Set P4.6 to output direction

  __bis_SR_register(LPM3_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P4OUT ^= 0x40;                            // Toggle P4.6 using exclusive-OR
}

