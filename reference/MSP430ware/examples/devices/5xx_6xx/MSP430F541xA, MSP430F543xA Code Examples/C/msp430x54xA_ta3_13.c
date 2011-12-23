//******************************************************************************
//  MSP430F543xA Demo - Timer_A3, Toggle P2.1/TA1.0, Up/Down Mode, DCO SMCLK
//
//  Description: Toggle P2.1 using hardware TA1.0 output. Timer1_A is configured
//  for up/down mode with CCR0 defining period, TA1.0 also output on P1.1. In
//  this example, CCR0 is loaded with 250 and TA1.0 will toggle P1.1 at
//  TACLK/2*250. Thus the output frequency on P1.1 will be the TACLK/1000.
//  No CPU or software resources required.
//  As coded with TACLK = SMCLK, P2.1 output frequency is ~1.045M/1000.
//  SMCLK = MCLK = TACLK = default DCO ~1.045MHz
//
//                MSP430F5438A
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P2.1/TA1.0|--> SMCLK/1000
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
  TA1CCR0 = 250;
  TA1CTL = TASSEL_2 + MC_3 + TACLR;         // SMCLK, up-downmode, clear TAR

  __bis_SR_register(LPM0_bits);             // Enter LPM0
  __no_operation();                         // For debugger
}
