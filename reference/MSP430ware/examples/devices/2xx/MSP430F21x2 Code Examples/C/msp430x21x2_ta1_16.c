//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, PWM TA1_1, Up Mode, DCO SMCLK
//
//  Description: This program generates one PWM outputs on P3.7 using
//  Timer1_A2 configured for up mode. The value in TA1CCR0, 512-1, defines the PWM
//  period and the value in TA1CCR1 defines the PWM duty cycle.
//  Using ~1.2MHz SMCLK as TACLK, the timer period is ~425us with
//  a 75% duty cycle on P3.7
//  ACLK = n/a, SMCLK = MCLK = TA1CLK = default DCO ~1.2MHz
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |       P3.7/TA1_1|--> TA1CCR1 - 75% PWM
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
  P3DIR |= 0x80;                            // 3.7 output
  P3SEL |= 0x80;                            // 3.7 TA1_1 otion
  TA1CCR0 = 512 - 1;                        // PWM Period
  TA1CCTL1 = OUTMOD_7;                      // TA1CCR1 reset/set
  TA1CCR1 = 384;                            // TA1CCR1 PWM duty cycle
  TA1CTL = TASSEL_2 + MC_1;                 // SMCLK, up mode

  __bis_SR_register(CPUOFF);                // Enter LPM0
}

