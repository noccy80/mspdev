//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, Toggle P3.6/TA0_1, Up/Down Mode, DCO SMCLK
//
//  Description: Toggle P3.6 using hardware TA0_1 output. Timer1_A2 is configured
//  for up/down mode with TA1CCR0 defining period. In
//  this example, TA1CCR0 is loaded with 250 and TA0_1 will toggle P3.6 at
//  TA1CLK/2*250. Thus the output frequency on P3.6 will be the TA1CLK/1000.
//  No CPU or software resources required.
//  ACLK = n/a, SMCLK = MCLK = TA1CLK = default DCO ~1.2MHz
//  As coded with TACLK = SMCLK, P3.6 output frequency is ~1200000/1000
//
//           MSP430F21x2
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
  TA1CCTL0 = OUTMOD_4;                       // TACCR0 toggle mode
  TA1CCR0 = 250;
  TA1CTL = TASSEL_2 + MC_3;                  // SMCLK, up-downmode

  __bis_SR_register(CPUOFF);                // CPU off
}
