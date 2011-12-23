//******************************************************************************
//   MSP430TC0701 Demo - Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
//
//   Description: This program generates six PWM outputs on P3/P5/P7 using
//   Timer_B configured for up mode. The value in CCR0, 512-1, defines the PWM
//   period and the values in CCR1-6 the PWM duty cycles. Using ~1048kHz SMCLK
//   as TBCLK, the timer period is ~488us.
//   ACLK = 32kHz, SMCLK = MCLK = TBCLK = default DCO ~1048kHz.
//
//                MSP430TC0701 
//             -----------------
//         /|\|              XIN|-
//          | |                 |  32kHz
//          --|RST          XOUT|-
//            |                 |
//            |         P5.7/TB1|--> CCR1 - 75% PWM
//            |         P7.4/TB2|--> CCR2 - 25% PWM
//            |         P7.5/TB3|--> CCR3 - 12.5% PWM
//            |         P7.6/TB4|--> CCR4 - 6.26% PWM
//            |         P3.5/TB5|--> CCR5 - 3.13% PWM
//            |         P3.6/TB6|--> CCR6 - 1.566% PWM
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  
  P3SEL |= BIT5+BIT6;                       // P3.5-7.6 option select
  P3DIR |= BIT5+BIT6;                       // P3.5-7.6 outputs 
  P5SEL |= BIT7;                            // P5.7 option select
  P5DIR |= BIT7;                            // P5.7 outputs
  P7SEL |= BIT4+BIT5+BIT6;                  // P7.4-7.6 option select
  P7DIR |= BIT4+BIT5+BIT6;                  // P7.4-7.6 outputs  

  TBCCR0 = 512-1;                           // PWM Period
  TBCCTL1 = OUTMOD_7;                       // CCR1 reset/set
  TBCCR1 = 383;                             // CCR1 PWM Duty Cycle	
  TBCCTL2 = OUTMOD_7;                       // CCR2 reset/set
  TBCCR2 = 128;                             // CCR2 PWM duty cycle	
  TBCCTL3 = OUTMOD_7;                       // CCR3 reset/set
  TBCCR3 = 64;                              // CCR3 PWM duty cycle	
  TBCCTL4 = OUTMOD_7;                       // CCR4 reset/set
  TBCCR4 = 32;                              // CCR4 PWM duty cycle	
  TBCCTL5 = OUTMOD_7;                       // CCR5 reset/set
  TBCCR5 = 16;                              // CCR5 PWM duty cycle	
  TBCCTL6 = OUTMOD_7;                       // CCR6 reset/set
  TBCCR6 = 8;                               // CCR6 PWM duty cycle	
  TBCTL = TBSSEL_2+MC_1;                    // SMCLK, upmode

  _BIS_SR(LPM0_bits + GIE);                 // CPU off
}
