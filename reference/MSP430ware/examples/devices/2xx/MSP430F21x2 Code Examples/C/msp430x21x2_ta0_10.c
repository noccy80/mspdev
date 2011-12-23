//******************************************************************************
//  MSP430F21x2 Demo - Timer0_A3, Toggle P1.1/TA0_0, Up Mode, DCO SMCLK
//
//  Description: Toggle P1.1 using hardware TA0_0 output. Timer0_A3 is configured
//  for up mode with TA0CCR0 defining period, TA1_0 also output on P1.1. In this
//  example, TA0CCR0 is loaded with 500-1 and TA0_0 will toggle P1.1 at TA0CLK/500.
//  Thus the output frequency on P1.1 will be TACLK/1000. No CPU or software
//  resources required.
//  As coded with TA0CLK = SMCLK, P1.1 output frequency is ~1200000/1000.
//  SMCLK = MCLK = TA0CLK = default DCO ~1.2MHz
//
//            MSP430F21x2
//         -----------------
//     /|\|              XIN|-
//      | |                 |
//      --|RST          XOUT|-
//        |                 |
//        |       P1.1/TA0_0|--> SMCLK/1000
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
  TA0CCTL0 = OUTMOD_4;                      // TA0CCR0 toggle mode
  TA0CCR0 = 500 - 1;
  TA0CTL = TASSEL_2 + MC_1;                 // SMCLK, upmode

  __bis_SR_register(CPUOFF);                // CPU off
}
