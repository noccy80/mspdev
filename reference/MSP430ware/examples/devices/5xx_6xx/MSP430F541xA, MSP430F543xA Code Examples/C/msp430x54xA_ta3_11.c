//******************************************************************************
//  MSP430F543xA Demo - Timer_A3, Toggle P2.1/TA1.0, Up Mode, 32kHz ACLK
//
//  Description: Toggle P2.1 using hardware TA1.0 output. Timer1_A is configured
//  for up mode with CCR0 defining period, TA1.0 also output on P2.1. In this
//  example, CCR0 is loaded with 10-1 and TA1.0 will toggle P1.1 at TACLK/10.
//  Thus the output frequency on P1.1 will be the TACLK/20. No CPU or software
//  resources required. Normal operating mode is LPM3.
//  As coded with TACLK = ACLK, P2.1 output frequency = 32768/20 = 1.6384kHz.
//  ACLK = TACLK = 32kHz, MCLK = default DCO ~1.045MHz
//
//                MSP430F5438A
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P2.1/TA1.0|--> ACLK/20
//
//   M. Morales
//   Texas Instruments Inc.
//   June 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54xA.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P2DIR |= 0x02;                            // P2.1 output
  P2SEL |= 0x02;                            // P2.1 option select
  TA1CCTL0 = OUTMOD_4;                      // CCR0 toggle mode
  TA1CCR0 = 10-1;
  TA1CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, upmode, clear TAR

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}
