//******************************************************************************
//  MSP430F552x Demo - Timer2_A3, Toggle P2.3/TA2.0, Up/Down Mode, 32kHz ACLK
//
//  Description: Toggle P2.3 using hardware TA2.0 output. Timer2_A is configured
//  for up/down mode with CCR0 defining period, TA2.0 also output on P2.3. In
//  this example, CCR0 is loaded with 5 and TA2.0 will toggle P2.3 at TACLK/2*5.
//  Thus the output frequency on P2.3 will be the TACLK/20. No CPU or software
//  resources required. Normal operating mode is LPM3.
//  As coded with TACLK = ACLK, P2.3 output frequency = 32768/20 = 1.6384kHz
//  ACLK = TACLK = 32kHz, MCLK = default DCO ~1.045MHz
//
//                MSP430F552x
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P2.3/TA2.0|-->ACLK/20
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
  P2DIR |= BIT3;                            // P2.3 output
  P2SEL |= BIT3;                            // P2.3 option select
  TA2CCTL0 = OUTMOD_4;                      // CCR0 toggle mode
  TA2CCR0 = 5;
  TA2CTL = TASSEL_1 + MC_3 + TACLR;         // ACLK, up-downmode, clear TAR

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}
