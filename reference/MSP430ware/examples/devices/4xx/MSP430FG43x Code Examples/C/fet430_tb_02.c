//******************************************************************************
//  MSP-FET430P430 Demo - Timer_B, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
//
//  Description: Toggle P5.1 using software and TB_0 ISR. Timer_B is
//  configured for up mode, thus the timer overflows when TBR counts
//  to TBCCR0. In this example, CCR0 is loaded with 20000.
//  ACLK = n/a, MCLK = SMCLK = TACLK = DCO = 32xACLK = 1.048576Mhz
//
//           MSP430FG439
//         ---------------
//     /|\|            XIN|-
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P5.1|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430xG43x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P5DIR |= 0x02;                            // Set P5.1 to output direction
  TBCCTL0 = CCIE;                           // TBCCR0 interrupt enabled
  TBCCR0 = 20000;
  TBCTL = TBSSEL_2 + MC_1;                  // SMCLK, up mode

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
  P5OUT ^= 0x02;                            // Toggle P5.1 using exclusive-OR
}

