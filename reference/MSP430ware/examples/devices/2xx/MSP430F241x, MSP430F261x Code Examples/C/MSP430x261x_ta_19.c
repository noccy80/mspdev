//*******************************************************************************
//  MSP430x26x Demo - Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P1.2,3 using
//  Timer_A configured for up/down mode. The value in CCR0, 128, defines the
//  PWM period/2 and the values in CCR1 and CCR2 the PWM duty cycles. Using
//  ~1.045MHz SMCLK as TACLK, the timer period is ~233us with a 75% duty cycle
//  on P1.2 and 25% on P1.3.
//  SMCLK = MCLK = TACLK = default DCO ~1.045MHz.
//
//               MSP430F261x/241x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> CCR1 - 75% PWM
//           |         P1.3/TA2|--> CCR2 - 25% PWM
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
  P1DIR |= 0x0C;                            // P1.2 and P1.3 output
  P1SEL |= 0x0C;                            // P1.2 and P1.3 TA1/2 otions
  CCR0 = 128;                               // PWM Period/2
  CCTL1 = OUTMOD_6;                         // CCR1 toggle/set
  CCR1 = 32;                                // CCR1 PWM duty cycle
  CCTL2 = OUTMOD_6;                         // CCR2 toggle/set
  CCR2 = 96;                                // CCR2 PWM duty cycle
  TACTL = TASSEL_2 + MC_3;                  // SMCLK, up-down mode

  _BIS_SR(CPUOFF);                          // Enter LPM0
}

