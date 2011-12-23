//******************************************************************************
//  MSP-FET430P440 Demo - Timer_A, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
//
//  Description: Toggle P5.1 using software and TA_0 ISR. Timer_A is
//  configured for up mode, thus the timer overflows when TAR counts
//  to CCR0. In this example, CCR0 is loaded with 20000.
//  ACLK = n/a, MCLK = SMCLK = TACLK = Default DCO
//
//           MSP430F449
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
//******************************************************************************
#include <msp430x44x.h>

void main(void)
{

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P5DIR |= 0x02;                            // P5.1 output
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 20000;
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, up mode
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P5OUT ^= 0x02;                            // Toggle P5.1 using exclusive-OR
}

