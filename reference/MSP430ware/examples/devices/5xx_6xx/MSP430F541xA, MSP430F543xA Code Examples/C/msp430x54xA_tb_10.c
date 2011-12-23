//******************************************************************************
//   MSP430F543xA Demo - Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
//
//   Description: This program generates six PWM outputs on P2/P3 using
//   Timer_B configured for up mode. The value in CCR0, 512-1, defines the PWM
//   period and the values in CCR1-6 the PWM duty cycles. Using ~1048kHz SMCLK
//   as TBCLK, the timer period is ~488us.
//   ACLK = 32kHz, SMCLK = MCLK = TBCLK = default DCO ~1048kHz.
//
//                MSP430F5438A
//             -----------------
//         /|\|              XIN|-
//          | |                 |  32kHz
//          --|RST          XOUT|-
//            |                 |
//            |         P4.1/TB1|--> CCR1 - 75% PWM
//            |         P4.2/TB2|--> CCR2 - 25% PWM
//            |         P4.3/TB3|--> CCR3 - 12.5% PWM
//            |         P4.4/TB4|--> CCR4 - 6.26% PWM
//            |         P4.5/TB5|--> CCR5 - 3.13% PWM
//            |         P4.6/TB6|--> CCR6 - 1.566% PWM
//
//   M. Morales
//   Texas Instruments Inc.
//   June 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54xA.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  P4SEL |= 0x7E;                            // P4 option select
  P4DIR |= 0x7E;                            // P4 outputs

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
  TBCTL = TBSSEL_2 + MC_1 + TBCLR;          // SMCLK, upmode, clear TBR

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  __no_operation();                         // For debugger  
}
