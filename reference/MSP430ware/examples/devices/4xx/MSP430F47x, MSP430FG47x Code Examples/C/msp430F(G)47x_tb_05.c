//******************************************************************************
//  MSP430F(G)47x Demo - Timer_B, Toggle P4.6, CCR0 Up Mode ISR, 32kHz ACLK
//
//  Description: Toggle P4.6 using software and the TB_0 ISR. Timer_B is
//  configured for up mode, thus the the timer overflows when TBR counts
//  to TBCCR0. In this example, TBCCR0 is loaded with 1000-1. LED toggles every
//  30.5 ms.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//           MSP430F(G)47x
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
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
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  P4DIR |= 0x40;                            // Set P4.6 to output direction
  TBCCTL0 = CCIE;                           // TRCCR0 interrupt enabled
  TBCCR0 = 1000-1;
  TBCTL = TBSSEL_1 + MC_1;                  // ACLK, up mode

  __bis_SR_register(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
    P4OUT ^= 0x40;                          // Toggle P4.6 using exclusive-OR
}

