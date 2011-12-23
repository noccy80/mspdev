//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, Toggle P3.6/TA0_1, Up Mode, 32kHz ACLK
//
//  Description: Toggle P3.6 using hardware TA0_1 output. Timer_A is configured
//  for up mode with TA1CCR0 defining period. In this
//  example, TA1CCR0 is loaded with 10-1 and TA0_1 will toggle P3.6 at TA1CLK/10.
//  Thus the output frequency on P3.6 will be the TA1CLK/20. No CPU or software
//  resources required. Normal operating mode is LPM3.
//  ACLK = TA1CLK = 32kHz, MCLK = default DCO ~1.2MHz
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//
//  As coded with TA1CLK = ACLK, P1.1 output frequency = 32768/20 = 1.6384kHz
//
//           MSP430F21x2
//         -----------------
//     /|\|              XIN|-
//      | |                 | 32kHz
//      --|RST          XOUT|-
//        |                 |
//        |       P3.6/TA0_1|--> ACLK/20
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2008
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.10A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3DIR |= 0x40;                            // P1.1 output
  P3SEL |= 0x40;                            // P1.1 option select
  TA1CCTL0 = OUTMOD_4;                       // TACCR0 toggle mode
  TA1CCR0 = 10 - 1;
  TA1CTL = TASSEL_1 + MC_1;                  // ACLK, upmode

  __bis_SR_register(LPM3_bits);             // Enter LPM3
}
