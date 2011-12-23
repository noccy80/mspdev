//*******************************************************************************
//  MSP430F(G)47x Demo - Timer_B, PWM TB1-2 Up Mode, DCO SMCLK
//
//  Description: This program outputs two PWM signals on P2.2 and P2.3
//  using Timer_B configured for up mode. The value in CCR0 defines the PWM
//  period and the values in CCR1 and CCR2 the PWM duty cycles. Using SMCLK
//  as TBCLK, the timer period is 488us.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//
//
//               MSP430F(G)47x
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         P2.2/TB1|--> CCR1 - 75% PWM
//           |         P2.3/TB2|--> CCR2 - 25% PWM
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//*****************************************************************************
#include "msp430xG47x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP18PF;                     // Set load capacitance for xtal
  P2DIR |= 0x0c;                            // P2.2,3 as outputs
  P2SEL |= 0x0c;                            // P2.2,3 TBx options
  TBCCR0 = 512-1;                           // PWM Period
  TBCCTL1 = OUTMOD_7;                       // CCR1 reset/set
  TBCCR1 = 384;                             // CCR1 PWM duty cycle
  TBCCTL2 = OUTMOD_7;
  TBCCR2 = 128;

  TBCTL = TBSSEL_2 + MC_1;                  // SMCLK, up mode

  __bis_SR_register(CPUOFF);                          // Enter LPM0
}

