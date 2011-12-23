//******************************************************************************
//  MSP430F21x2 Demo - Timer0_A3, Toggle P1.0, TA0CCR0 Up Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and Timer0_A0 ISR. Timer0_A is
//  configured for up mode, thus the timer overflows when TA0R counts to
//  TA0CCR0. In this example, TA0CCR0 is loaded with 20000.
//  ACLK = n/a, MCLK = SMCLK = TA0CLK = default DCO ~1.2MHz
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
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TA0CCTL0 = CCIE;                           // TA0CCR0 interrupt enabled
  TA0CCR0 = 20000;
  TA0CTL = TASSEL_2 + MC_1;                  // SMCLK, upmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer0_A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}

