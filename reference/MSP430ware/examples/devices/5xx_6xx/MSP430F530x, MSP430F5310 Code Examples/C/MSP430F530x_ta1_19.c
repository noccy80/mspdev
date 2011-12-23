//*******************************************************************************
//  MSP430F530x Demo - Timer1_A3, PWM TA1.1-2, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P2.0,1 using
//  Timer1_A configured for up/down mode. The value in CCR0, 128, defines the
//  PWM period/2 and the values in CCR1 and CCR2 the PWM duty cycles. Using
//  ~1.045MHz SMCLK as TACLK, the timer period is ~233us with a 75% duty cycle
//  on P2.0 and 25% on P2.1.
//  SMCLK = MCLK = TACLK = default DCO ~1.045MHz.
//
//                MSP430F530x
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P2.0/TA1.1|--> CCR1 - 75% PWM
//           |         P2.1/TA1.2|--> CCR2 - 25% PWM
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

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
  TA1CTL = TASSEL_2 + MC_3 + TACLR;         // SMCLK, up-down mode, clear TAR

  __bis_SR_register(LPM0_bits);             // Enter LPM0
  __no_operation();                         // For debugger
}

