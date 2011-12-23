//******************************************************************************
//  MSP430F22x4 Demo - Timer_A, Toggle P1.0, TACCR0 Up Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TA_0 ISR. Timer_A is
//  configured for up mode, thus the timer overflows when TAR counts to
//  TACCR0. In this example, TACCR0 is loaded with 20000.
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO ~1.2MHz
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |             P1.0|-->LED
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TACCTL0 = CCIE;                           // TACCR0 interrupt enabled
  TACCR0 = 20000;
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}

