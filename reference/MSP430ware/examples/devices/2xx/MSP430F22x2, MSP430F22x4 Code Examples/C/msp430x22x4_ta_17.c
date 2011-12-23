//******************************************************************************
//  MSP430F22x4 Demo - Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
//
//  Description: This program generates two PWM outputs on P1.2,3 using
//  Timer_A configured for up mode. The value in TACCR0, 512-1, defines the PWM
//  period and the values in TACCR1 and TACCR2 the PWM duty cycles. Using 32kHz
//  ACLK as TACLK, the timer period is 15.6ms with a 75% duty cycle on P1.2
//  and 25% on P1.3. Normal operating mode is LPM3.
//  ACLK = TACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO ~1.2MHz
//  //* External watch crystal on XIN XOUT is required for ACLK *//
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> TACCR1 - 75% PWM
//           |         P1.3/TA2|--> TACCR2 - 25% PWM
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x0C;                            // P1.2 and P1.3 output
  P1SEL |= 0x0C;                            // P1.2 and P1.3 TA1/2 otions
  TACCR0 = 512 - 1;                         // PWM Period
  TACCTL1 = OUTMOD_7;                       // TACCR1 reset/set
  TACCR1 = 384;                             // TACCR1 PWM duty cycle
  TACCTL2 = OUTMOD_7;                       // TACCR2 reset/set
  TACCR2 = 128;                             // TACCR2 PWM duty cycle
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up mode

  __bis_SR_register(LPM3_bits);             // Enter LPM3
}

