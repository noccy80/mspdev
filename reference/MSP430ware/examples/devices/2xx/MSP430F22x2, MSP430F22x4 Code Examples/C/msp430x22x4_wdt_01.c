//******************************************************************************
//  MSP430F22x4 Demo - WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software timed by the WDT ISR. Toggle rate
//  is approximately 27ms based on default DCO/SMCLK clock source
//  used in this example for the WDT.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDT_MDLY_32;                     // Set Watchdog interval to ~27ms
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 using exclusive-OR
}

