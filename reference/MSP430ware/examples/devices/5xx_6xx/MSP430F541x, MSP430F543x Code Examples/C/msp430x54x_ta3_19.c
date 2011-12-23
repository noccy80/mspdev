//*******************************************************************************
//  MSP430F54x Demo - Timer_A3, PWM TA1.1-2, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P2.2,3 using
//  Timer1_A configured for up/down mode. The value in CCR0, 128, defines the
//  PWM period/2 and the values in CCR1 and CCR2 the PWM duty cycles. Using
//  ~1.045MHz SMCLK as TACLK, the timer period is ~233us with a 75% duty cycle
//  on P2.2 and 25% on P2.3.
//  SMCLK = MCLK = TACLK = default DCO ~1.045MHz.
//
//                MSP430F5438
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P2.2/TA1.1|--> CCR1 - 75% PWM
//           |         P2.3/TA1.2|--> CCR2 - 25% PWM
//
//   M Smertneck / W. Goh
//   Texas Instruments Inc.
//   September 2008
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P2DIR |= 0x0C;                            // P2.2 and P2.3 output
  P2SEL |= 0x0C;                            // P2.2 and P2.3 options select
  TA1CCR0 = 128;                            // PWM Period/2
  TA1CCTL1 = OUTMOD_6;                      // CCR1 toggle/set
  TA1CCR1 = 32;                             // CCR1 PWM duty cycle
  TA1CCTL2 = OUTMOD_6;                      // CCR2 toggle/set
  TA1CCR2 = 96;                             // CCR2 PWM duty cycle
  TA1CTL = TASSEL_2 + MC_3 + TACLR;         // SMCLK, up-down mode, clear TAR

  __bis_SR_register(LPM0_bits);             // Enter LPM0
  __no_operation();                         // For debugger
}

