//******************************************************************************
//  MSP430F66x Demo - WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software timed by the WDT ISR. Toggle rate
//  is approximately 30ms = {(default DCO 1.045MHz) / 32768} based on default
//  DCO = SMCLK clock source used in this example for the WDT.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.045MHz
//
//                MSP430F66x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   Nov 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************

#include <msp430f6638.h>

void main(void)
{
  WDTCTL = WDT_MDLY_32;                     // WDT 32ms, SMCLK, interval timer 
  SFRIE1 |= WDTIE;                          // Enable WDT interrupt
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  __no_operation();                         // For debugger
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 (LED)
}
