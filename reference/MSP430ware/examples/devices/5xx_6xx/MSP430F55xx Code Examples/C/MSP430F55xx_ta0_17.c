//*******************************************************************************
//  MSP430F552x Demo - Timer0_A5, PWM TA1.1-2, Up Mode, 32kHz ACLK
//
//  Description: This program generates two PWM outputs on P1.2,1.3 using
//  Timer1_A configured for up mode. The value in CCR0, 512-1, defines the PWM
//  period and the values in CCR1 and CCR2 the PWM duty cycles. Using 32kHz
//  ACLK as TACLK, the timer period is ~ (512/32k) ~ 15.6ms with a 75% duty
//  cycle on P1.2 and 25% on P1.3. Normal operating mode is LPM3.
//  ACLK = TACLK = LFXT1 = 32768Hz, MCLK = default DCO ~1.045MHz.
//
//                MSP430F552x
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P1.2/TA0.1|--> CCR1 - 75% PWM
//           |         P1.3/TA0.2|--> CCR2 - 25% PWM
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
  P1DIR |= BIT2+BIT3;                       // P1.2 and P1.3 output
  P1SEL |= BIT2+BIT3;                       // P1.2 and P1.3 options select
  TA0CCR0 = 512-1;                          // PWM Period
  TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
  TA0CCR1 = 384;                            // CCR1 PWM duty cycle
  TA0CCTL2 = OUTMOD_7;                      // CCR2 reset/set
  TA0CCR2 = 128;                            // CCR2 PWM duty cycle
  TA0CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, up mode, clear TAR

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}

