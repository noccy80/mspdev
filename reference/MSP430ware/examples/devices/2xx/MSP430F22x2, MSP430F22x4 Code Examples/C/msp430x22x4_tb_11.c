//******************************************************************************
//  MSP430F22x4 Demo - Timer_B, PWM TB1-2, Up Mode, 32kHz ACLK
//
//  Description: This program generates two PWM outputs on P4.1-2 using
//  Timer_B configured for up mode. The value in TBCCR0, 512-1, defines the PWM
//  period and the values in TBCCR1-2 the PWM duty cycles. Using 32kHz ACLK
//  as TBCLK, the timer period is 15.6ms. Normal operating mode is LPM3.
//  ACLK = TBCLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO ~1.2MHz.
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32k
//         --|RST          XOUT|-
//           |                 |
//           |         P4.1/TB1|--> TBCCR1 - 75% PWM
//           |         P4.2/TB2|--> TBCCR2 - 25% PWM
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P4DIR |= 0x06;                            // P4.1 - P4.2 output
  P4SEL |= 0x06;                            // P4.1 - P4.2 TBx options
  TBCCR0 = 512 - 1;                         // PWM Period
  TBCCTL1 = OUTMOD_7;                       // TBCCR1 reset/set
  TBCCR1 = 384;                             // TBCCR1 PWM duty cycle
  TBCCTL2 = OUTMOD_7;
  TBCCR2 = 128;
  TBCTL = TBSSEL_1 + MC_1;                  // ACLK, up mode

  __bis_SR_register(LPM3_bits);             // Enter LPM3
}

