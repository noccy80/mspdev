//*****************************************************************************
//  MSP-FET430P140 Demo - Timer_B, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using software and the TB_0 ISR. Timer_B is
//  configured for up mode, thus the timer overflows when TBR counts
//  to CCR0. In this example, CCR0 is loaded with 1000-1.
//  Toggle rate = 32768Hz/(2*1000) = 16.384Hz
//  ACLK = TBCLK = 32kHz, MCLK = SMCLK = default DCO ~800kHz
//  //* An external watch crystal on XIN XOUT is required for ACLK *//	
//
//           MSP430F149
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************

#include  <msp430x14x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  TBCTL = TBSSEL_1 + TBCLR;                 // ACLK, clear TBR
  TBCCTL0 = CCIE;                           // TRCCR0 interrupt enabled
  TBCCR0 = 1000-1;
  TBCTL = TBSSEL_1 + MC_1;                  // ACLK, upmode

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
    P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR
}

