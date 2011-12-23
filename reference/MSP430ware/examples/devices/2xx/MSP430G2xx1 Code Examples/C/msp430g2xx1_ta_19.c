//******************************************************************************
//  MSP430G2xx1 Demo - Timer_A, PWM TA1, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates one PWM output on P1.2 using
//  Timer_A configured for up/down mode. The value in CCR0, 128, defines the PWM
//  period/2 and the value in CCR1 the PWM duty cycles.
//  A 75% duty cycle is on P1.2.
//  SMCLK = MCLK = TACLK = default DCO
//
//               MSP430G2xx1
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> CCR1 - 75% PWM
//
//  D. Dang
//  Texas Instruments, Inc
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include  <msp430g2231.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x0C;                            // P1.2 and P1.3 output
  P1SEL |= 0x0C;                            // P1.2 and P1.3 TA1/2 options
  CCR0 = 128;                               // PWM Period/2
  CCTL1 = OUTMOD_6;                         // CCR1 toggle/set
  CCR1 = 32;                                // CCR1 PWM duty cycle
  TACTL = TASSEL_2 + MC_3;                  // SMCLK, up-down mode

  _BIS_SR(LPM0_bits);                       // Enter LPM0
}

