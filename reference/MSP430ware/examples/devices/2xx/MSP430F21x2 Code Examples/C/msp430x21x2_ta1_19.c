//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, PWM TA1-1, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates PWM output P3.7 using
//  Timer1_A2 configured for up/down mode. The value in TA1CCR0, 128, defines the
//  PWM period/2 and the value in TA1CCR1 the PWM duty cycle. Using
//  ~1.2MHz SMCLK as TA1CLK, the timer period is ~212us with a 75% duty cycle
//  on P3.7
//  SMCLK = MCLK = TACLK = default DCO ~1.2MHz
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |       P3.7/TA1_1|--> TACCR1 - 75% PWM
//           |                 |
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2008
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.10A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3DIR |= 0x80;                            // P1.2 and P1.3 output
  P3SEL |= 0x80;                            // P1.2 and P1.3 TA1/2 otions
  TA1CCR0 = 128;                            // PWM Period/2
  TA1CCTL1 = OUTMOD_6;                      // TA1CCR1 toggle/set
  TA1CCR1 = 32;                             // TA1CCR1 PWM duty cycle
  TA1CTL = TASSEL_2 + MC_3;                 // SMCLK, up-down mode

  __bis_SR_register(LPM0_bits);             // Enter LPM0
}

