//******************************************************************************
//  MSP430F21x2 Demo - Timer0_A3, PWM TA0_0 - TA0_2, Up/Down Mode, 32kHz ACLK
//
//  Description: This program generates two PWM outputs on P1.2,3 using
//  Timer0_A3 configured for up/down mode. The value in TA0CCR0, 128, defines the
//  PWM period/2 and the values in TA0CCR1 and TA0CCR2 the PWM duty cycles. Using
//  32kHz ACLK as TA0CLK, the timer period is 7.8ms with a 75% duty cycle on
//  P1.2 and 25% on P1.3. Normal operating mode is LPM3.
//  ACLK = TA0CLK = LFXT1 = 32768Hz, MCLK = default DCO ~1.2MHz
//  //* External watch crystal on XIN XOUT is required for ACLK *//
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |       P1.2/TA0_1|--> TA0CCR1 - 75% PWM
//           |       P1.3/TA0_2|--> TA0CCR2 - 25% PWM
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2008
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x0C;                            // P1.2 and P1.3 output
  P1SEL |= 0x0C;                            // P1.2 and P1.3 TA1/2 otions
  TA0CCR0 = 128;                             // PWM Period/2
  TA0CCTL1 = OUTMOD_6;                       // TA0CCR1 toggle/set
  TA0CCR1 = 32;                              // TA0CCR1 PWM duty cycle
  TA0CCTL2 = OUTMOD_6;                       // TA0CCR2 toggle/set
  TA0CCR2 = 96;                              // TA0CCR2 PWM duty cycle
  TA0CTL = TASSEL_1 + MC_3;                  // ACLK, up-down mode

  __bis_SR_register(LPM3_bits);             // Enter LPM3
}

