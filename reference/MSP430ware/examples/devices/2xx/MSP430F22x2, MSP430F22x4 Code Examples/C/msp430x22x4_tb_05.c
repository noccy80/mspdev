//******************************************************************************
//  MSP430F22x4 Demo - Timer_B, Toggle P1.0, TBCCR0 Up Mode ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using software and the TB_0 ISR. Timer_B is
//  configured for up mode, thus the timer overflows when TBR counts
//  to TBCCR0. In this example, TBCCR0 is loaded with 1000-1.
//  Toggle rate = 32768Hz/(2*1000) = 16.384Hz
//  ACLK = TBCLK = 32768Hz, MCLK = SMCLK = default DCO ~1.2MHz
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//           MSP430F22x4
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
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
  TBCTL = TBSSEL_1 + TBCLR;                 // ACLK, clear TBR
  TBCCTL0 = CCIE;                           // TBCCR0 interrupt enabled
  TBCCR0 = 1000 - 1;
  TBCTL = TBSSEL_1 + MC_1;                  // ACLK, upmode

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0 using exclusive-OR
}

