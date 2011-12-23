//*******************************************************************************
//  MSP430FR57x Demo - TimerB, PWM TB0.1-2, Up Mode, 32KHz ACLK
//
//  Description: This program generates two PWM outputs on P1.4,P1.5 using
//  TimerB configured for up mode. The value in CCR0, 100-1, defines the PWM
//  period and the values in CCR1 and CCR2 the PWM duty cycles. Using 32768Hz
//  ACLK as TACLK, the timer period is ~3ms with a 75% duty cycle on P1.4
//  and 25% on P1.5.
//  ACLK = TACLK =32768Hz, SMCLK = MCLK = 4MHz
//
//
//           MSP430FR5739
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |     P1.4/TA0.1|--> CCR1 - 75% PWM
//        |     P1.5/TA0.2|--> CCR2 - 25% PWM
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************

#include "msp430fr5739.h"


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT  
  // XT1 Setup 
  PJSEL0 |= BIT4 + BIT5; 
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;            // Set max. DCO setting
  CSCTL2 = SELA_0 + SELS_3 + SELM_3;        // set ACLK = XT1; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_1 + DIVM_1;        // set all dividers 
  CSCTL4 |= XT1DRIVE_0; 
  CSCTL4 &= ~XT1OFF;
  
  do
  {
    CSCTL5 &= ~XT1OFFG;
                                            // Clear XT1 fault flag
    SFRIFG1 &= ~OFIFG; 
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  
  
  P1DIR |= BIT4+BIT5;                       // P1.4 and P1.5 output
  P1SEL0 |= BIT4+BIT5;                      // P1.4 and P1.5 options select
  TB0CCR0 = 100-1;                          // PWM Period
  TB0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
  TB0CCR1 = 75;                             // CCR1 PWM duty cycle
  TB0CCTL2 = OUTMOD_7;                      // CCR2 reset/set
  TB0CCR2 = 25;                             // CCR2 PWM duty cycle
  TB0CTL = TBSSEL_1 + MC_1 + TBCLR;         // ACLK, up mode, clear TAR

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}


