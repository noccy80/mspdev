//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, Toggle P1.0, TACCR0 Up Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and Timer1_A0 ISR. Timer1_A2 is
//  configured for up mode, thus the timer overflows when TA1R counts to
//  TA1CCR0. In this example, TA1CCR0 is loaded with 20000.
//  ACLK = n/a, MCLK = SMCLK = TA1CLK = default DCO ~1.2MHz
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |             P1.0|-->LED
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  December 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.10A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TA1CCTL0 = CCIE;                           // TACCR0 interrupt enabled
  TA1CCR0 = 20000;
  TA1CTL = TASSEL_2 + MC_1;                  // SMCLK, upmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer1_A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0 (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}

