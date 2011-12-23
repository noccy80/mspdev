//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, Toggle P3.6/TA0_1, Up/Down Mode, 32kHz ACLK
//
//  Description: Toggle P1.1 using hardware TA0_1 output. Timer1_A2 is configured
//  for up/down mode with TA1CCR0 defining period, Timer1_A2 also output on P3.6. In
//  this example, TA1CCR0 is loaded with 5 and TA1 will toggle P3.6 at TA1CLK/2*5.
//  Thus the output frequency on P1.1 will be the TA1CLK/20. No CPU or software
//  resources required. Normal operating mode is LPM3.
//  ACLK = TA1CLK = 32kHz, MCLK = default DCO ~1.2MHz
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//
//  As coded with TA1CLK = ACLK, P3.6 output frequency = 32768/20 = 1.6384kHz.
//
//           MSP430F21x2
//         -----------------
//     /|\|              XIN|-
//      | |                 | 32kHz
//      --|RST          XOUT|-
//        |                 |
//        |         P1.1/TA1|--> ACLK/20
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
  P3DIR |= 0x40;                            // P3.6 output
  P3SEL |= 0x40;                            // P3.6 option select
  TA1CCTL0 = OUTMOD_4;                       // TACCR0 toggle mode
  TA1CCR0 = 5;
  TA1CTL = TASSEL_1 + MC_3;                  // ACLK, up-downmode

  __bis_SR_register(LPM3_bits);             // Enter LPM3
}
