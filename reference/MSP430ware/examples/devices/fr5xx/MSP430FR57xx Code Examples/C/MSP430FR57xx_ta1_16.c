//*******************************************************************************
//  MSP430FR57x Demo - Timer1_A3, PWM TA1.1-2, Up Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P1.2,P1.3 using
//  Timer1_A configured for up mode. The value in CCR0, 1000-1, defines the PWM
//  period and the values in CCR1 and CCR2 the PWM duty cycles. Using ~1MHz
//  SMCLK as TACLK, the timer period is ~1ms with a 75% duty cycle on P1.2
//  and 25% on P1.3.
//  ACLK = n/a, SMCLK = MCLK = TACLK = 1MHz
//
//
//           MSP430FR5739
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |     P1.2/TA0.1|--> CCR1 - 75% PWM
//        |     P1.3/TA0.2|--> CCR2 - 25% PWM
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
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;            // Set max. DCO setting =8MHz
  CSCTL2 = SELA_3 + SELS_3 + SELM_3;        // set ACLK = SMCLK = DCO/8
  CSCTL3 = DIVA_3 + DIVS_3 + DIVM_3;        // set all dividers 
  
  P1DIR |= BIT2+BIT3;                       // P1.2 and P1.3 output
  P1SEL0 |= BIT2+BIT3;                      // P1.2 and P1.3 options select
  TA1CCR0 = 1000-1;                         // PWM Period
  TA1CCTL1 = OUTMOD_7;                      // CCR1 reset/set
  TA1CCR1 = 750;                            // CCR1 PWM duty cycle
  TA1CCTL2 = OUTMOD_7;                      // CCR2 reset/set
  TA1CCR2 = 250;                            // CCR2 PWM duty cycle
  TA1CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR

  __bis_SR_register(LPM0_bits);             // Enter LPM0
  __no_operation();                         // For debugger
}


