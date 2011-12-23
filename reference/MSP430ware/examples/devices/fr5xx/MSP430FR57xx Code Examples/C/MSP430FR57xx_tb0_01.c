//******************************************************************************
//  MSP430FR57x Demo - TimerB, Toggle P1.0, CCR0 Cont Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TB_0 ISR. TimerB is
//  configured for continuous mode, thus the timer overflows when TBR counts
//  to CCR0. In this example, CCR0 is loaded with 50000.
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO = ~666KHz
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
  
  TB0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
  TB0CCR0 = 50000;
  TB0CTL = TBSSEL_2 + MC_2;                 // SMCLK, continuous mode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer B0 interrupt service routine
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer_B (void)
{
  P1OUT ^= BIT0;
  TB0CCR0 += 50000;                         // Add Offset to TACCR0
}