//*******************************************************************************
//  MSP430x11x1 Demo - Timer_A, PWM TA1-2, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P1.2,3 using
//  Timer_A configured for up/down mode. The value in CCR0, 128, defines the PWM
//  period/2 and the values in CCR1 and CCR2 the PWM duty cycles. Using ~800kHz
//  SMCLK as TACLK, the timer period is ~320us with a 75% duty cycle on P1.2 and
//  25% on P1.3.
//  SMCLK = MCLK = TACLK = default DCO ~800kHz.
//
//               MSP430F1121
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> CCR1 - 75% PWM
//           |         P1.3/TA2|--> CCR2 - 25% PWM
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************

#include <msp430x11x1.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x0C;                            // P1.2 and P1.3 output
  P1SEL |= 0x0C;                            // P1.2 and P1.3 TA1/2 options
  CCR0 = 128;                               // PWM Period/2
  CCTL1 = OUTMOD_6;                         // CCR1 toggle/set
  CCR1 = 32;                                // CCR1 PWM duty cycle
  CCTL2 = OUTMOD_6;                         // CCR2 toggle/set
  CCR2 = 96;                                // CCR2 PWM duty cycle
  TACTL = TASSEL_2 + MC_3;                  // SMCLK, up-down mode

  _BIS_SR(LPM0_bits);                       // Enter LPM0
}

