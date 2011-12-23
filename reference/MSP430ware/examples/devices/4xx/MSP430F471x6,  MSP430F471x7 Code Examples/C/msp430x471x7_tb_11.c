//*******************************************************************************
//  MSP430x471xx Demo - Timer_B, PWM TB1-2 Up Mode, 32kHz ACLK
//
//  Description: This program outputs two PWM signals on P3.6 & P3.7 using
//  Timer_B configured for up mode. The value in CCR0 defines the PWM period
//  and the values in CCR1 and CCR2 the PWM duty cycles. Using 32kHz ACLK as
//  TBCLK, the timer period is 15.6ms. Normal operating mode is LPM3.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//              MSP430x471xx
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P3.6/TB1|--> CCR1 - 75% PWM
//           |         P3.7/TB2|--> CCR2 - 25% PWM
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP18PF;                     // Set load capacitance for xtal  
  P3DIR |= BIT6+BIT7;                       // P2.2 - P2.3 output
  P3SEL |= BIT6+BIT7;                       // P2.3 - P2.3 TBx options
  TBCCR0 = 512-1;                           // PWM Period
  TBCCTL1 = OUTMOD_7;                       // CCR1 reset/set
  TBCCR1 = 384;                             // CCR1 PWM duty cycle
  TBCCTL2 = OUTMOD_7;
  TBCCR2 = 128;

  TBCTL = TBSSEL_1 + MC_1;                  // ACLK, up mode
  _BIS_SR(LPM3_bits);                       // Enter LPM3
}

