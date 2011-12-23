//******************************************************************************
//  MSP430F22x4 Demo - Timer_B, Toggle P1.0, TBCCR0 Up Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TB0 ISR. Timer_B is
//  configured for up mode, thus the timer overflows when TBR counts
//  to TBCCR0. In this example, TBCCR0 is loaded with 20000.
//  ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~1.2MHz
//
//           MSP430F22x4
//         ---------------
//     /|\|            XIN|-
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
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
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  TBCCTL0 = CCIE;                           // TBCCR0 interrupt enabled
  TBCCR0 = 20000;
  TBCTL = TBSSEL_2 + MC_1;                  // SMCLK, upmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 using exclusive-OR
}

