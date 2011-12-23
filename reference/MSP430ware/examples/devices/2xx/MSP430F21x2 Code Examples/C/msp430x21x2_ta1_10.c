//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, Toggle P3.6/TA0_1, Up Mode, DCO SMCLK
//
//  Description: Toggle P3.6 using hardware TA0_1 output. Timer1_A2 is configured
//  for up mode with TA1CCR0 defining period. In this
//  example, TA1CCR0 is loaded with 500-1 and TA0_1 will toggle P3.6 at TA1CLK/500.
//  Thus the output frequency on P3.6 will be TA1CLK/1000. No CPU or software
//  resources required.
//  As coded with TA1CLK = SMCLK, P3.6 output frequency is ~1200000/1000.
//  SMCLK = MCLK = TA1CLK = default DCO ~1.2MHz
//
//            MSP430F21x2
//         -----------------
//     /|\|              XIN|-
//      | |                 |
//      --|RST          XOUT|-
//        |                 |
//        |       P3.6/TA0_1|--> SMCLK/1000
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
  TA1CCTL0 = OUTMOD_4;                      // TACCR0 toggle mode
  TA1CCR0 = 500 - 1;
  TA1CTL = TASSEL_2 + MC_1;                 // SMCLK, upmode

  __bis_SR_register(CPUOFF);                // CPU off
}
