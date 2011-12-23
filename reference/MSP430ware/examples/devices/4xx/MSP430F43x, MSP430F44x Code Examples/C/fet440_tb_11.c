//*******************************************************************************
//  MSP-FET430P140 Demo - Timer_B, PWM TB1-6 Up Mode, 32kHz ACLK
//
//  Description; This program outptus six PWM signals on P2.2,3 and P3.4-7
//  using Timer_B configured for up mode. The value in CCR0 defines the PWM
//  period and the values in CCR1-6 the PWM duty cycles. Using 32kHz ACLK
//  as TBCLK, the timer period is 15.6ms. Normal operating mode is LPM3.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//               MSP430F449
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P2.2/TB1|--> CCR1 - 75% PWM
//           |         P2.3/TB2|--> CCR2 - 25% PWM
//           |         P3.4/TB3|--> CCR3 - 12.5% PWM
//           |         P3.5/TB4|--> CCR4 - 6.25% PWM
//           |         P3.6/TB5|--> CCR5 - 3.125% PWM
//           |         P3.7/TB6|--> CCR6 - 1.5625% PWM
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include <msp430x44x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP18PF;                     // Configure load caps
  P2DIR |= 0x0c;                            // P2.2 - P2.3 output
  P2SEL |= 0x0c;                            // P2.3 - P2.3 TBx options
  P3DIR |= 0xF0;                            // P3.4 - P3.7 output
  P3SEL |= 0xF0;                            // P3.4 - P3.7 TBx options
  TBCCR0 = 512-1;                           // PWM Period
  TBCCTL1 = OUTMOD_7;                       // CCR1 reset/set
  TBCCR1 = 384;                             // CCR1 PWM duty cycle
  TBCCTL2 = OUTMOD_7;
  TBCCR2 = 128;
  TBCCTL3 = OUTMOD_7;
  TBCCR3 = 64;
  TBCCTL4 = OUTMOD_7;
  TBCCR4 = 32;
  TBCCTL5 = OUTMOD_7;
  TBCCR5 = 16;
  TBCCTL6 = OUTMOD_7;
  TBCCR6 = 8;

  TBCTL = TBSSEL_1 + MC_1;                  // ACLK, up mode

  _BIS_SR(LPM3_bits);                       // Enter LPM3
}

