//*******************************************************************************
// MSP430x471xx Demo - Timer_A, PWM TA1-2 Up Mode, 32kHz ACLK
//
//  Description: This program outputs two PWM signals on P1.2 and P2.0
//  using Timer_A configured for up mode. The value in CCR0 defines the PWM
//  period and the values in CCR1 and CCR2 the PWM duty cycles. Using 32kHz
//  ACLK as TACLK, the timer period is 15.6ms with a 75% duty cycle on P1.2
//  and 25% on P3.4. Normal operating mode is LPM3.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//               MSP430x47xx
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> CCR1 - 75% PWM
//           |         P3.4/TA2|--> CCR2 - 25% PWM
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>

void main(void)
{
  WDTCTL = WDTPW +WDTHOLD;                  // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  P1DIR |= BIT2;                            // P1.2 output
  P1SEL |= BIT2;                            // P1.2 TA1 option
  P3DIR |= BIT4;                            // P3.4 output
  P3SEL |= BIT4;                            // P3.4 TA2 option
  CCR0 = 512-1;                             // PWM Period
  CCTL1 = OUTMOD_7;                         // CCR1 reset/set
  CCR1 = 384;                               // CCR1 PWM duty cycle
  CCTL2 = OUTMOD_7;                         // CCR2 reset/set
  CCR2 = 128;                               // CCR2 PWM duty cycle
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up mode
  _BIS_SR(LPM3_bits);                       // Enter LPM3
}

