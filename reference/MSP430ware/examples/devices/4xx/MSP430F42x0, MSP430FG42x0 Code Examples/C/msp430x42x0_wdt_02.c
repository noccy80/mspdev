//******************************************************************************
//   MSP430x42x0 Demo - WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using WDT configured for Interval Timer mode.
//  Interrupt toggles LED every 250ms based on 32kHz ACLK WDT clock source.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//		  MSP430F4270
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  L. Westlund / S. Karthikeyan
//  Texas Instruments Inc.
//  June 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//*****************************************************************************
#include  <msp430x42x0.h>

void main(void)
{
  WDTCTL = WDT_ADLY_250;                    // WDT 250ms, ACLK, interval timer
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 using exclusive-OR
}

