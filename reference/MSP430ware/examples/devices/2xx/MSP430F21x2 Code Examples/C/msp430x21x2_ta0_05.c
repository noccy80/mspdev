//******************************************************************************
//  MSP430F21x2 Demo - Timer0_A3, Toggle P1.0, TA0CCR0 Up Mode ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using software and the Timer0_A0 ISR. Timer_A is
//  configured for up mode, thus the the timer overflows when TA0R counts
//  to TA0CCR0. In this example TA0CCR0 is loaded with 1000-1.
//  ACLK = TA0CLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO ~1.2MHz
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
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  TA0CCTL0 = CCIE;                           // TA0CCR0 interrupt enabled
  TA0CCR0 = 1000 - 1;
  TA0CTL = TASSEL_1 + MC_1;                  // ACLK, upmode

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt
}

// Timer0_A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}

