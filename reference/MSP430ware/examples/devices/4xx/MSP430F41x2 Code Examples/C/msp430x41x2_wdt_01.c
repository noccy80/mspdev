//******************************************************************************
//  MSP430x41x2 Demo - WDT, Toggle P5.1, Interval Overflow ISR, DCO SMCLK
//
//  Description: Toggle P5.1 using WDT configured for Interval Timer mode.
//  Interrupt toggles LED every 31ms when using default FLL+ register
//  settings and an external 32kHz watch crystal.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//
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
//*****************************************************************************
#include  <msp430x41x2.h>

void main(void)
{
  WDTCTL = WDT_MDLY_32;                     // ~31ms interval timer
  FLL_CTL0 |= XCAP18PF;                     // Set load capacitance for xtal
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P5DIR |= 0x02;                            // Set P5.1 to output direction

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P5OUT ^= 0x02;                            // Toggle P5.1using exclusive-OR
}

