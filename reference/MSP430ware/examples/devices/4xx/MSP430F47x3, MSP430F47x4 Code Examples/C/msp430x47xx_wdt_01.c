//******************************************************************************
//  MSP430x47xx Demo - WDT, Toggle P5.1, Interval Overflow ISR, DCO SMCLK
//
//  Description: Toggle P5.1 using software timed by the WDT ISR. Toggle rate
//  is approximately 27ms based on default DCO/SMCLK clock source
//  used in this example for the WDT.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
//
//                MSP430x47xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//  P. Thanigai / K.Venkat
//  Texas Instruments Inc.
//  November 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x47x4.h"

void main(void)
{
  WDTCTL = WDT_MDLY_32;                     // Set Watchdog interval to ~27ms
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P5DIR |= 0x02;                            // P5.1 outputs

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P5OUT ^= 0x02;                            // Toggle P5.1 using exclusive-OR
}

