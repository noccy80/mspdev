//*******************************************************************************
//  MSP430F66x Demo - Timer2_A3, PWM TA2.1-2, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P3.6,7 using
//  Timer2_A configured for up/down mode. The value in CCR0, 128, defines the
//  PWM period/2 and the values in CCR1 and CCR2 the PWM duty cycles. Using
//  ~1.045MHz SMCLK as TACLK, the timer period is ~233us with a 75% duty cycle
//  on P2.4 and 25% on P2.5.
//  SMCLK = MCLK = TACLK = default DCO ~1.045MHz.
//
//                MSP430F66x
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P3.6/TA2.1|--> CCR1 - 75% PWM
//           |         P3.7/TA2.2|--> CCR2 - 25% PWM
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   Nov 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************
#include <msp430f6638.h>


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3DIR |= BIT6+BIT7;                       // P3.6,7 output
  P3SEL |= BIT6+BIT7;                       // P3.6,7 options select
  TA2CCR0 = 128;                            // PWM Period/2
  TA2CCTL1 = OUTMOD_6;                      // CCR1 toggle/set
  TA2CCR1 = 32;                             // CCR1 PWM duty cycle
  TA2CCTL2 = OUTMOD_6;                      // CCR2 toggle/set
  TA2CCR2 = 96;                             // CCR2 PWM duty cycle
  TA2CTL = TASSEL_2 + MC_3 + TACLR;         // SMCLK, up-down mode, clear TAR

  __bis_SR_register(LPM0_bits);             // Enter LPM0
  __no_operation();                         // For debugger
}

