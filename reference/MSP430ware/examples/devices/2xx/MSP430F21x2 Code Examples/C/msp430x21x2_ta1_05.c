//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, Toggle P1.0, TA1CCR0 Up Mode ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using software and the Timer1_A0 ISR. Timer1_A2 is
//  configured for up mode, thus the the timer overflows when TA1R counts
//  to TA1CCR0. In this example TA1CCR0 is loaded with 1000-1.
//  ACLK = TA1CLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO ~1.2MHz
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |             P1.0|-->LED
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2008
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.10A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TA1CCTL0 = CCIE;                           // TACCR0 interrupt enabled
  TA1CCR0 = 1000 - 1;
  TA1CTL = TASSEL_1 + MC_1;                  // ACLK, upmode

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt
}

// Timer1_A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0 (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}

