//*******************************************************************************
//  MSP430x24x Demo - Timer_B, PWM TB1-2, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P4.1-6 using
//  Timer_B configured for up/down mode. The value in CCR0, 128, defines the
//  PWM period/2 and values in CCR1-6 the PWM duty cycles. Using ~1.045Mhz SMCLK
//  as TBCLK, the timer period is ~ 232us. Normal operating mode: LPM0.
//  SMCLK = MCLK = TBCLK = default DCO ~1.045Mhz.
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
  TBCCR0 = 128;                             // PWM Period/2
  TBCCTL1 = OUTMOD_6;                       // CCR1 toggle/set
  TBCCR1 = 32;                              // CCR1 PWM duty cycle
  TBCCTL2 = OUTMOD_6;                       // CCR2 toggle/set
  TBCCR2 = 96;                              // CCR2 PWM duty cycle
  TBCCTL3 = OUTMOD_6;
  TBCCR3 = 112;
  TBCCTL4 = OUTMOD_6;
  TBCCR4 = 120;
  TBCCTL5 = OUTMOD_6;
  TBCCR5 = 124;
  TBCCTL6 = OUTMOD_6;
  TBCCR6 = 126;
  
  TBCTL = TBSSEL_2 + MC_3;                  // SMCLK, up-down mode

  _BIS_SR(CPUOFF);                          // Enter LPM0
}

