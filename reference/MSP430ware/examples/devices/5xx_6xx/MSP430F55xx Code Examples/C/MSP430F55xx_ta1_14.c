//******************************************************************************
//  MSP430F552x Demo - Timer1_A3, Toggle P1.7/TA1.0, Up/Down Mode, 32kHz ACLK
//
//  Description: Toggle P1.7 using hardware TA1.0 output. Timer1_A is configured
//  for up/down mode with CCR0 defining period, TA1.0 also output on P1.7. In
//  this example, CCR0 is loaded with 5 and TA1.0 will toggle P1.7 at TACLK/2*5.
//  Thus the output frequency on P1.7 will be the TACLK/20. No CPU or software
//  resources required. Normal operating mode is LPM3.
//  As coded with TACLK = ACLK, P1.7 output frequency = 32768/20 = 1.6384kHz
//  ACLK = TACLK = 32kHz, MCLK = default DCO ~1.045MHz
//
//                MSP430F552x
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P1.7/TA1.0|-->ACLK/20
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT7;                            // P1.7 output
  P1SEL |= BIT7;                            // P1.7 option select
  TA1CCTL0 = OUTMOD_4;                      // CCR0 toggle mode
  TA1CCR0 = 5;
  TA1CTL = TASSEL_1 + MC_3 + TACLR;         // ACLK, up-downmode, clear TAR

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}
