//*******************************************************************************
//  MSP430F552x Demo - Timer1_A3, PWM TA1.1-2, Up/Down Mode, 32kHz ACLK
//
//  Description: This program generates two PWM outputs on P2.0, P2.1 using
//  Timer1_A configured for up/down mode. The value in CCR0, 128, defines the
//  PWM period/2 and the values in CCR1 and CCR2 the PWM duty cycles. Using
//  32kHz ACLK as TACLK, the timer period is 7.8ms with a 75% duty cycle
//  on P2.0 and 25% on P2.1. Normal operating mode is LPM3
//  ACLK = TACLK = LFXT1 = 32768Hz, MCLK = default DCO ~1.045MHz.
//
//                MSP430F552x
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P2.0/TA1.1|--> CCR1 - 75% PWM
//           |         P2.1/TA1.2|--> CCR2 - 25% PWM
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P2DIR |= BIT0+BIT1;                       // P2.0 and P2.1 output
  P2SEL |= BIT0+BIT1;                       // P2.0 and P2.1 options select
  TA1CCR0 = 128;                            // PWM Period/2
  TA1CCTL1 = OUTMOD_6;                      // CCR1 toggle/set
  TA1CCR1 = 32;                             // CCR1 PWM duty cycle
  TA1CCTL2 = OUTMOD_6;                      // CCR2 toggle/set
  TA1CCR2 = 96;                             // CCR2 PWM duty cycle
  TA1CTL = TASSEL_1 + MC_3;                 // ACLK, up-down mode

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}

