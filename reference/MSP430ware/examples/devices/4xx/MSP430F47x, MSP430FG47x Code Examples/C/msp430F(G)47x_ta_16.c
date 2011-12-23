//*******************************************************************************
//  MSP430F(G)47x Demo - Timer_A, PWM TA1-2 Up Mode, DCO SMCLK
//
//  Description: This program outputs two PWM signals on P1.2 and P2.0
//  using Timer_A configured for up mode. The value in CCR0 defines the PWM
//  period and the values in CCR1 and CCR2 the PWM duty cycles. Using SMCLK as
//  TACLK, the timer period is 488us with a 75% duty cycle on P1.2 and 25%
//  on P2.0.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//               MSP430F(G)47x
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P1.2/TA1|--> CCR1 - 75% PWM
//           |         P2.0/TA2|--> CCR2 - 25% PWM
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//*****************************************************************************
#include "msp430xG47x.h"

void main(void)
{
  WDTCTL = WDTPW +WDTHOLD;                  // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  P1DIR |= 0x04;                            // P1.2 output
  P1SEL |= 0x04;                            // P1.2 TA1 option
  P2DIR |= 0x01;                            // P2.0 output
  P2SEL |= 0x01;                            // P2.0 TA2 option
  CCR0 = 512-1;                             // PWM Period
  CCTL1 = OUTMOD_7;                         // CCR1 reset/set
  CCR1 = 384;                               // CCR1 PWM duty cycle
  CCTL2 = OUTMOD_7;                         // CCR2 reset/set
  CCR2 = 128;                               // CCR2 PWM duty cycle
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, up mode

  __bis_SR_register(LPM0_bits);                       // Enter LPM0
}

