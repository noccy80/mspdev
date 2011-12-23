//******************************************************************************
//  MSP430F51x2 Demo - Timer0_D3, Combining two CCRx register to control one 
//                     PWM channel; Normal Timer mode
//
//  Description: This code example shows how to combine two CCRx registers to 
//  control both the rising and falling edges of one PWM channel (TD0.2, TD1.2). 
//  In up-mode, TDxCCR1 controls the rising edge and TDxCCR2 controls the 
//  falling edge. In this example, since CCR1 registers of TD0/1 have the same 
//  count, the rising edges at TD0.2 and TD1.2 happen almost at the same 
//  time instance. With TD0CCR2=40 and TD1CCR2=96, the dutycycles of the TD0.2 
//  and TD1.2 are 30% and 43.75%. 
//  
//  ACLK = REF0; SMCLK = MCLK = default DCO ~1.045MHz.
//
//                 MSP430F51x2
//             -----------------
//         /|\|              XIN|-
//          | |                 | 
//          --|RST          XOUT|-
//            |                 |
//            |       P2.0/TD0.2|--> CCR2 - 30% duty cycle; 
//            |                 |    ON period=(TD0CCR2-TD0CCR1)/32767 ~ 1.22ms
//            |       P2.3/TD1.2|--> CCR2 - 43.75% duty cycle; 
//            |                 |    ON period=(TD1CCR2-TD1CCR1)/32767 ~ 1.7ms 
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
  
  // Set port pins
  P2SEL |= BIT0+BIT3;                       // P2.0/TD0.2 options select
  P2DIR |= BIT0+BIT3;                       // P2.0 output  
  
  // Configure TimerD0 to combine CCR0/1 block to control TD0CCR2 PWM output
  TD0CTL1 |= TD2CMB + TDCLKM_0;             // Combine TD0CCR1 and TD0CCR2
  TD0CCTL2 |= OUTMOD_7;                     // TD0CCR2, Reset/Set
  TD0CCR0 = 128;
  TD0CCR1 = 40;  
  TD0CCR2 = 80;
  
  // Configure TimerD1 to combine CCR0/1 block to control TD1CCR2 PWM output
  TD1CTL1 |= TD2CMB + TDCLKM_0;             // Combine TD0CCR1 and TD0CCR2
  TD1CCTL2 |= OUTMOD_7;                     // TD1CCR2, Reset/Set
  TD1CCR0 = 128;
  TD1CCR1 = 40;  
  TD1CCR2 = 96;                             // duty cycle = (96-40)/32767 ~ 

  TD0CTL0 |= TDSSEL_1 + MC_1 + TDCLR;       // TD0, ACLK, up mode, clear timer
  TD1CTL0 |= TDSSEL_1 + MC_1 + TDCLR;       // TD1, ACLK, up mode, clear timer

  __bis_SR_register(LPM0_bits);             // Enter LPM0
  __no_operation();                         // For debugger    
  
}