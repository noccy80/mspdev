//*******************************************************************************
//  MSP430x261x Demo - Timer_B, PWM TB1-6, Up Mode, 32kHz ACLK
//
//  Description: This program generates six PWM outputs on P4.1-6 using
//  Timer_B7 configured for up mode. The value in CCR0, 512-1, defines the PWM
//  period and the values in CCR1-6 the PWM duty cycles. Using 32kHz ACLK
//  as TBCLK, the timer period is (512/32k) 15.6ms. Normal operating mode: LPM3.
//  ACLK = TBCLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO ~1.045MHz.
//  // External watch crystal installed on XIN XOUT is required for ACLK //	
//
//               MSP430F261x/241x
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32k
//         --|RST          XOUT|-
//           |                 |
//           |         P4.1/TB1|--> CCR1 - 75% PWM
//           |         P4.2/TB2|--> CCR2 - 25% PWM
//           |         P4.3/TB3|--> CCR3 - 12.5% PWM
//           |         P4.4/TB4|--> CCR4 - 6.25% PWM
//           |         P4.5/TB5|--> CCR5 - 3.125% PWM
//           |         P4.6/TB6|--> CCR6 - 1.5625% PWM
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include  <msp430x26x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P4DIR |= 0x7e;                            // P4.1 - P4.6 output
  P4SEL |= 0x7e;                            // P4.1 - P4.6 TBx options
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

