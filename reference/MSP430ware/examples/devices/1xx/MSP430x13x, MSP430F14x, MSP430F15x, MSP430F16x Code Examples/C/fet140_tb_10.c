//*******************************************************************************
//  MSP-FET430P140 Demo - Timer_B, PWM TB1-2, Up/Down Mode, 32kHz ACLK
//
//  Description: This program generates two PWM outputs on P4.1,2 using
//  Timer_B configured for up/down mode. The value in CCR0, 128, defines the
//  PWM period/2 and the values in CCR1 and CCR2 the PWM duty cycles. Using
//  32kHz ACLK as TBCLK, the timer period is 7.8ms with a 75% duty cycle on
//  P4.1 and 25% on P4.2. Normal operating mode is LPM3.
//  ACLK = TBCLK = LFXT1 = 32768Hz, MCLK = default DCO ~800kHz.
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//
//               MSP430F149
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P4.1/TB1|--> CCR1 - 75% PWM
//           |         P4.2/TB2|--> CCR2 - 25% PWM
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P4DIR |= 0x06;                            // P4.1 and P4.2 output
  P4SEL |= 0x06;                            // P4.1 and P4.2 TB1/2 otions
  TBCCR0 = 128;                             // PWM Period/2
  TBCCTL1 = OUTMOD_6;                       // CCR1 toggle/set
  TBCCR1 = 32;                              // CCR1 PWM duty cycle
  TBCCTL2 = OUTMOD_6;                       // CCR2 toggle/set
  TBCCR2 = 96;                              // CCR2 PWM duty cycle
  TBCTL = TBSSEL_1 + MC_3;                  // ACLK, up-down mode

  _BIS_SR(LPM3_bits);                       // Enter LPM3
}

