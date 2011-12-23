//*******************************************************************************
//  MSP430FR57x Demo - Timer0_A3, PWM TA0.1-2, Up Mode, 32KHz ACLK
//
//  Description: This program generates two PWM outputs on P1.0,P1.1 using
//  Timer0_A configured for up mode. The value in CCR0, 100-1, defines the PWM
//  period and the values in CCR1 and CCR2 the PWM duty cycles. Using 32768Hz
//  ACLK as TACLK, the timer period is ~3ms with a 75% duty cycle on P1.0
//  and 25% on P1.1.
//  ACLK = TACLK =32768Hz, SMCLK = MCLK = 4MHz
//
//
//           MSP430FR5739
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |     P1.0/TA0.1|--> CCR1 - 75% PWM
//        |     P1.1/TA0.2|--> CCR2 - 25% PWM
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
  
  
  P1DIR |= BIT0+BIT1;                       // P1.0 and P1.1 output
  P1SEL0 |= BIT0+BIT1;                      // P1.0 and P1.1 options select
  TA0CCR0 = 100-1;                          // PWM Period
  TA0CCTL1 = OUTMOD_7;                      // CCR1 reset/set
  TA0CCR1 = 75;                             // CCR1 PWM duty cycle
  TA0CCTL2 = OUTMOD_7;                      // CCR2 reset/set
  TA0CCR2 = 25;                             // CCR2 PWM duty cycle
  TA0CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, up mode, clear TAR

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}


