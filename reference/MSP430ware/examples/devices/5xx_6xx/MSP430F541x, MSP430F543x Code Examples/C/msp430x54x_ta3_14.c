//******************************************************************************
//  MSP430F54x Demo - Timer_A3, Toggle P2.1/TA1.0, Up/Down Mode, 32kHz ACLK
//
//  Description: Toggle P2.1 using hardware TA1.0 output. Timer1_A is configured
//  for up/down mode with CCR0 defining period, TA1.0 also output on P2.1. In
//  this example, CCR0 is loaded with 5 and TA1.0 will toggle P2.1 at TACLK/2*5.
//  Thus the output frequency on P2.1 will be the TACLK/20. No CPU or software
//  resources required. Normal operating mode is LPM3.
//  As coded with TACLK = ACLK, P2.1 output frequency = 32768/20 = 1.6384kHz
//  ACLK = TACLK = 32kHz, MCLK = default DCO ~1.045MHz
//
//                MSP430F5438
//            -------------------
//        /|\|                   |
//         | |                   |
//         --|RST                |
//           |                   |
//           |         P2.1/TA1.0|-->ACLK/20
//
//   M Smertneck / W. Goh
//   Texas Instruments Inc.
//   September 2008
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P2DIR |= 0x02;                            // P2.1 output
  P2SEL |= 0x02;                            // P2.1 option select
  TA1CCTL0 = OUTMOD_4;                      // CCR0 toggle mode
  TA1CCR0 = 5;
  TA1CTL = TASSEL_1 + MC_3 + TACLR;         // ACLK, up-downmode, clear TAR

  __bis_SR_register(LPM3_bits);             // Enter LPM3
  __no_operation();                         // For debugger
}
