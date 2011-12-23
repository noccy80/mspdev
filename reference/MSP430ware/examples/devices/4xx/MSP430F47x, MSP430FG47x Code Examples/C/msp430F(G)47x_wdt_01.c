//******************************************************************************
//  MSP430F(G)47x Demo - WDT, Toggle P4.6, Interval Overflow ISR, DCO SMCLK
//
//  Description: Toggle P4.6 using WDT configured for Interval Timer mode.
//  Interrupt toggles LED every 31ms when using default FLL+ register
//  settings and an external 32kHz watch crystal.
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
  WDTCTL = WDT_MDLY_32;                     // ~31ms interval timer
  FLL_CTL0 |= XCAP18PF;                     // Set load capacitance for xtal
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P4DIR |= 0x40;                            // Set P4.6 to output direction

  __bis_SR_register(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P4OUT ^= 0x40;                            // Toggle P4.6 using exclusive-OR
}

