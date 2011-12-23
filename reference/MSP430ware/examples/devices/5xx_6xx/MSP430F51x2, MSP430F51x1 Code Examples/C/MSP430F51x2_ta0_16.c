//*******************************************************************************
//  MSP430F51x2 Demo - Timer0_A3, PWM TA0.1-2, Up Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P3.6,P3.7 using
//  Timer0_A configured for up mode. The value in CCR0, 512-1, defines the PWM
//  period and the values in CCR1 and CCR2 the PWM duty cycles. Using ~1.045MHz
//  SMCLK as TACLK, the timer period is ~500us with a 75% duty cycle on P3.6
//  and 25% on P3.5
//  ACLK = n/a, SMCLK = MCLK = TACLK = default DCO ~1.045MHz.
//
//                MSP430F51x2
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |      P3.6/PM_TA0.1|--> CCR1 - 75% PWM
//           |      P3.5/PM_TA0.2|--> CCR2 - 25% PWM
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  P3DIR |= BIT6+BIT5;                       // P3.6 and P3.7 output
  P3SEL |= BIT6+BIT5;                       // P3.6 and P3.7 options select
  
  // Configure TA0
  TA0CCR0 = 512-1;                          // PWM Period
  TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
  TA0CCR1 = 384;                            // CCR1 PWM duty cycle
  TA0CCTL2 = OUTMOD_7;                      // CCR2 reset/set
  TA0CCR2 = 128;                            // CCR2 PWM duty cycle
  
  TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR

  __bis_SR_register(LPM0_bits);             // Enter LPM0
  __no_operation();                         // For debugger
}

