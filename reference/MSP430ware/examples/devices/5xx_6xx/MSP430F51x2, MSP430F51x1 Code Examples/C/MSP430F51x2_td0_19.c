//*******************************************************************************
//  MSP430F51x2 Demo - TimerD0, PWM TD0.1-2, Up/Down Mode, DCO SMCLK
//
//  Description: This program generates two PWM outputs on P1.7 and P2.0 using
//  TimerD0 configured for up/down mode. The value in CCR0, 128, defines the
//  PWM period/2 and the values in CCR1 and CCR2 the PWM duty cycles. Using
//  ~1.045MHz SMCLK as TDCLK, the timer period is ~233us with a 75% duty cycle
//  on P1.7 and 25% on P2.0. PWM freq = 4kHz. 
//  SMCLK = MCLK = TDCLK = default DCO ~1.045MHz.
//
//                MSP430F51x2
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P1.7/TD0.1|--> CCR1 - 75% PWM
//           |         P2.0/TD0.2|--> CCR2 - 25% PWM
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
  // configure ports
  P1SEL |= BIT7;                            // P1.7, option select
  P1DIR |= BIT7;                            // P1.7 output
  P2SEL |= BIT0;                            // P2.0 options select
  P2DIR |= BIT0;                            // P2.0 output
  
  // Configure TD0
  TD0CCR0 = 128;                            // PWM Period/2
  TD0CCTL1 = OUTMOD_6;                      // CCR1 toggle/set
  TD0CCR1 = 32;                             // CCR1 PWM duty cycle
  TD0CCTL2 = OUTMOD_6;                      // CCR2 toggle/set
  TD0CCR2 = 96;                             // CCR2 PWM duty cycle
  TD0CTL0 = TDSSEL_2 + MC_3 + TDCLR;        // SMCLK, up-down mode, clear TDR

  __bis_SR_register(LPM0_bits);             // Enter LPM0
  __no_operation();                         // For debugger
}

