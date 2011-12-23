//*******************************************************************************
//  MSP430x11x1 Demo - Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
//
//  Description: This program generates two PWM outputs on P1.2,3 using
//  Timer_A configured for up mode. The value in CCR0, 512-1, defines the PWM
//  period and the values in CCR1 and CCR2 the PWM duty cycles. Using 32kHz ACLK
//  as TACLK, the timer period is 15.6ms with a 75% duty cycle on P1.2
//  and 25% on P1.3. Normal operating mode is LPM3.
//  ACLK = TBCLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO ~800kHz.
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//
//               MSP430F1121
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
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
  CCR0 = 512-1;                             // PWM Period
  CCTL1 = OUTMOD_7;                         // CCR1 reset/set
  CCR1 = 384;                               // CCR1 PWM duty cycle
  CCTL2 = OUTMOD_7;                         // CCR2 reset/set
  CCR2 = 128;                               // CCR2 PWM duty cycle
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up mode

  _BIS_SR(LPM3_bits);                       // Enter LPM3
}

