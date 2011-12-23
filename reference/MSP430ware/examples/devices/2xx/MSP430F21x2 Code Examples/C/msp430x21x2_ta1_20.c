//*******************************************************************************
//   MSP430F21x2 Demo - Timer1_A2, PWM TA1_1, Up/Down Mode, 32kHz ACLK
//
//   Description: This program generates one PWM outputs on P3.7 using
//   Timer1_A2 configured for up/down mode. The value in TA1CCR0, 128, defines the
//   PWM period/2 and the values in TA1CCR1 and TA1CCR2 the PWM duty cycles. Using
//   32kHz ACLK as TA1CLK, the timer period is 7.8ms with a 75% duty cycle on
//   P3.7. Normal operating mode is LPM3.
//   ACLK = TA1CLK = LFXT1 = 32768Hz, MCLK = default DCO ~1.2MHz
//   /* External watch crystal on XIN XOUT is required for ACLK */
//
//                MSP430F21x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |       P3.7/TA1_1|--> TAC1CCR1 - 75% PWM
//            |                 |
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   January 2008
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//*******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3DIR |= 0x80;                            // P3.7 output
  P3SEL |= 0x80;                            // P3.7 TA1_1 otions
  TA1CCR0 = 128;                            // PWM Period/2
  TA1CCTL1 = OUTMOD_6;                      // TACCR1 toggle/set
  TA1CCR1 = 32;                             // TACCR1 PWM duty cycle
  TA1CTL = TASSEL_1 + MC_3;                 // ACLK, up-down mode

  __bis_SR_register(LPM3_bits);             // Enter LPM3
}

