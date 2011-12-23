//******************************************************************************
//  MSP430F21x2 Demo - Timer0_A3, Toggle P1.1/TA0_0, Up/Down Mode, 32kHz ACLK
//
//  Description: Toggle P1.1 using hardware TA0_0 output. Timer0_A3 is configured
//  for up/down mode with TA0CCR0 defining period, TA0_0 also output on P1.1. In
//  this example, TA0CCR0 is loaded with 5 and TA0_0 will toggle P1.1 at TA0CLK/2*5.
//  Thus the output frequency on P1.1 will be the TA0CLK/20. No CPU or software
//  resources required. Normal operating mode is LPM3.
//  ACLK = TA0CLK = 32kHz, MCLK = default DCO ~1.2MHz
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//
//  As coded with TA0CLK = ACLK, P1.1 output frequency = 32768/20 = 1.6384kHz.
//
//           MSP430F21x2
//         -----------------
//     /|\|              XIN|-
//      | |                 | 32kHz
//      --|RST          XOUT|-
//        |                 |
//        |       P1.1/TA0_0|--> ACLK/20
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2008
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x02;                            // P1.1 output
  P1SEL |= 0x02;                            // P1.1 option select
  TA0CCTL0 = OUTMOD_4;                       // TA0CCR0 toggle mode
  TA0CCR0 = 5;
  TA0CTL = TASSEL_1 + MC_3;                  // ACLK, up-downmode

  __bis_SR_register(LPM3_bits);             // Enter LPM3
}
