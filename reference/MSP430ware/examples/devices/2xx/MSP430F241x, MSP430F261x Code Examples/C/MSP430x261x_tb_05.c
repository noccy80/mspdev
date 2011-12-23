//*****************************************************************************
//  MSP430x26x Demo - Timer_B, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using software and the TB_0 ISR. Timer_B is
//  configured for up mode, thus the timer overflows when TBR counts
//  to CCR0. In this example, CCR0 is loaded with 1000-1.
//  Toggle rate = 32768Hz/(2*1000) = 16.384Hz
//  ACLK = TBCLK = 32kHz, MCLK = SMCLK = default DCO ~1.045MHz
//  //* An external watch crystal on XIN XOUT is required for ACLK *//	
//
//           MSP430F261x/241x
//         ---------------
//     /|\|            XIN|-
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//*****************************************************************************

#include  <msp430x26x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  TBCCTL0 = CCIE;                           // TRCCR0 interrupt enabled
  TBCCR0 = 1000-1;
  TBCTL = TBSSEL_1 + MC_1 + TBCLR;          // ACLK, upmode, clear TBR

  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
    P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR
}

