//******************************************************************************
//  MSP430F66x Demo - Timer1_A3, Toggle P1.7/TA1.0, Up/Down Mode, DCO SMCLK
//
//  Description: Toggle P3.1 using hardware TA1.0 output. Timer1_A is configured
//  for up/down mode with CCR0 defining period, TA1.0 also output on P3.1. In
//  this example, CCR0 is loaded with 250 and TA1.0 will toggle P3.1 at
//  TACLK/2*250. Thus the output frequency on P3.1 will be the TACLK/1000.
//  No CPU or software resources required.
//  As coded with TACLK = SMCLK, P3.1 output frequency is ~1.045M/1000.
//  SMCLK = MCLK = TACLK = default DCO ~1.045MHz
//
//                MSP430F66x
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P3.1TA1.0|--> SMCLK/1000
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   Nov 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************
#include <msp430f6638.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3DIR |= BIT1;                            // P3.1 output
  P3SEL |= BIT1;                            // P3.1 option select
  TA1CCTL0 = OUTMOD_4;                      // CCR0 toggle mode
  TA1CCR0 = 250;
  TA1CTL = TASSEL_2 + MC_3 + TACLR;         // SMCLK, up-downmode, clear TAR

  __bis_SR_register(LPM0_bits);             // Enter LPM0
  __no_operation();                         // For debugger
}
