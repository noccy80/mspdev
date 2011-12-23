//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, PWM TA1_1, Up Mode, 32kHz ACLK
//
//  Description: This program generates one PWM outputs on P3.7 using
//  Timer1_A2 configured for up mode. The value in TA1CCR0, 512-1, defines the PWM
//  period and the value in TACCR1 define the PWM duty cycle. Using 32kHz
//  ACLK as TACLK, the timer period is 15.6ms with a 75% duty cycle on P3.7.
//  Normal operating mode is LPM3.
//  ACLK = TA1CLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO ~1.2MHz
//  //* External watch crystal on XIN XOUT is required for ACLK *//
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P3.7/TA1|--> TACCR1 - 75% PWM
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
  TA1CCR0 = 512 - 1;                         // PWM Period
  TA1CCTL1 = OUTMOD_7;                       // TACCR1 reset/set
  TA1CCR1 = 384;                             // TACCR1 PWM duty cycle
  TA1CTL = TASSEL_1 + MC_1;                  // ACLK, up mode

  __bis_SR_register(LPM3_bits);             // Enter LPM3
}

