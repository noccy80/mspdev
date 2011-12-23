//*******************************************************************************
//  MSP430x24x Demo - Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
//
//  Description: This program generates six PWM outputs on P4.1-6 using
//  Timer_B configured for up mode. The value in CCR0, 512-1, defines the PWM
//  period and the values in CCR1-6 the PWM duty cycles. Using ~1.045Mhz SMCLK
//  as TBCLK, the timer period is = (512/1.1M) ~ 465us.
//  ACLK = na, SMCLK = MCLK = TBCLK = default DCO ~1.045Mhz.
//
//               MSP430F249
//            -----------------
//        /|\|              XIN|-
//         | |                 |
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

#include  <msp430x24x.h>

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
  TBCTL = TBSSEL_2 + MC_1;                  // SMCLK, up mode

  _BIS_SR(CPUOFF);                          // Enter LPM0
}

