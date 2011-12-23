//******************************************************************************
//  MSP430x471xx Demo - Timer_B, Toggle P5.1, CCR0 Up Mode ISR, 32kHz ACLK
//
//  Description: Toggle P5.1 using software and the TB_0 ISR. Timer_B is
//  configured for up mode, thus the the timer overflows when TBR counts
//  to TBCCR0. In this example, TBCCR0 is loaded with 1000-1. LED toggles every
//  30.5 ms.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//          MSP430x471xx
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P5.1|-->LED
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  P5DIR |= BIT1;                            // Set P5.1 to output direction
  TBCCTL0 = CCIE;                           // TRCCR0 interrupt enabled
  TBCCR0 = 1000-1;
  TBCTL = TBSSEL_1 + MC_1;                  // ACLK, up mode

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
    P5OUT ^= BIT1;                          // Toggle P5.1 using exclusive-OR
}

