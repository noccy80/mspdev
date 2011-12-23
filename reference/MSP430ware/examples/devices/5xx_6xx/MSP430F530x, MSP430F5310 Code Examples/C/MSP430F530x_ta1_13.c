//******************************************************************************
//  MSP430F530x Demo - Timer1_A3, Toggle P1.7/TA1.0, Up/Down Mode, DCO SMCLK
//
//  Description: Toggle P1.7 using hardware TA1.0 output. Timer1_A is configured
//  for up/down mode with CCR0 defining period, TA1.0 also output on P1.7. In
//  this example, CCR0 is loaded with 250 and TA1.0 will toggle P1.7 at
//  TACLK/2*250. Thus the output frequency on P1.7 will be the TACLK/1000.
//  No CPU or software resources required.
//  As coded with TACLK = SMCLK, P1.7 output frequency is ~1.045M/1000.
//  SMCLK = MCLK = TACLK = default DCO ~1.045MHz
//
//                MSP430F530x
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P1.7/TA1.0|--> SMCLK/1000
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT7;                            // P1.7 output
  P1SEL |= BIT7;                            // P1.7 option select
  TA1CCTL0 = OUTMOD_4;                      // CCR0 toggle mode
  TA1CCR0 = 250;
  TA1CTL = TASSEL_2 + MC_3 + TACLR;         // SMCLK, up-downmode, clear TAR

  __bis_SR_register(LPM0_bits);             // Enter LPM0
  __no_operation();                         // For debugger
}
