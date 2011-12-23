//******************************************************************************
//  MSP430x26x Demo - WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software timed by the WDT ISR. Toggle rate
//  is approximately 30ms = {(default DCO 1.045MHz) / 32768} based on default 
//  DCO/SMCLK clock source used in this example for the WDT.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.045MHz
//
//                MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"

void main(void)
{
  // Set Watchdog interval to ~30ms
  WDTCTL = WDT_MDLY_32;                     // WDT SMCLK Delay Interval specify                  
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

