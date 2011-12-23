//******************************************************************************
//  MSP430FR57x Demo - Timer0_A3, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TA_0 ISR. Timer0_A is
//  configured for up mode, thus the timer overflows when TAR counts
//  to CCR0. In this example, CCR0 is loaded with 50000.
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO ~666KHz
//
//
//           MSP430FR5739
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************

#include "msp430fr5739.h"


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT  
 
  P1DIR |= BIT0;
  P1OUT |= BIT0;
  
  TA0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
  TA0CCR0 = 50000;
  TA0CTL = TASSEL_2 + MC_1;                 // SMCLK, UP mode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= BIT0;
}