//******************************************************************************
//  MSP430F(G)47x Demo - Timer_A, Toggle P4.6, CCR0 Up Mode ISR, DCO SMCLK
//
//  Description: Toggle P4.6 using software and TA_0 ISR. Timer_A is
//  configured for up mode, thus the timer overflows when TAR counts to CCR0.
//  In this example, CCR0 is loaded with 20000.
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO
//
//           MSP430F(G)47x
//         ---------------
//     /|\|            XIN|-
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P4.6|-->LED
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//*****************************************************************************
#include "msp430xG47x.h"

void main(void)
{

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P4DIR |= 0x40;                            // P4.6 output
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 20000;
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, up mode
  __bis_SR_register(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P4OUT ^= 0x40;                            // Toggle P4.6 using exclusive-OR
}

