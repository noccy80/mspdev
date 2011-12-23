//******************************************************************************
//  MSP430F(G)47x Demo - Timer_B, Toggle P4.6, CCR0 Up Mode ISR, DCO SMCLK
//
//  Description: Toggle P4.6 using software and TB_0 ISR. Timer_B is
//  configured for up mode, thus the timer overflows when TBR counts
//  to TBCCR0. In this example, CCR0 is loaded with 20000.
//  ACLK = n/a, MCLK = SMCLK = TACLK = DCO = 32xACLK = 1.048576Mhz
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
  P4DIR |= 0x40;                            // Set P4.6 to output direction
  TBCCTL0 = CCIE;                           // TBCCR0 interrupt enabled
  TBCCR0 = 20000;
  TBCTL = TBSSEL_2 + MC_1;                  // SMCLK, up mode

  __bis_SR_register(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
  P4OUT ^= 0x40;                            // Toggle P4.6 using exclusive-OR
}

