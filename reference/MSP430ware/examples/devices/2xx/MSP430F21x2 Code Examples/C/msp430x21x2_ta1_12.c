//******************************************************************************
//  MSP430F21x2 Demo - Timer1_A2, Toggle P3.6/TA1_1, Up Mode, HF XTAL ACLK
//
//  Description: Toggle P3.6 using hardware TA0_1 output. Timer1_A2 is configured
//  for up mode with TA1CCR0 defining period. In this
//  example, TA1CCR0 is loaded with 500-1 and TA0_1 will toggle P3.6 at TA1CLK/500.
//  Thus the output frequency on P3.6 will be the TA1CLK/1000. No CPU or
//  software resources required.
//  ACLK = MCLK = TA1CLK = HF XTAL
//  //* HF XTAL REQUIRED AND NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//  As coded with TA1CLK = ACLK, P3.6 output frequency = HF XTAL/1000
//
//           MSP430F21x2
//         -----------------
//     /|\|              XIN|-
//      | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//      --|RST          XOUT|-
//        |                 |
//        |       P3.6/TA0_1|--> ACLK/1000
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2008
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.10A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 |= XTS;                           // ACLK = LFXT1 = HF XTAL
  BCSCTL3 |= LFXT1S1;                       // LFXT1S1 = 3-16Mhz

  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0xFF; i > 0; i--);             // Time for flag to set
  }
  while (IFG1 & OFIFG);                     // OSCFault flag still set?
  BCSCTL2 |= SELM_3;                        // MCLK = LFXT1 (safe)

  P3DIR |= 0x40;                            // P3.6 output
  P3SEL |= 0x40;                            // P3.6 option select
  TA1CCTL0 = OUTMOD_4;                       // TA1CCR0 toggle mode
  TA1CCR0 = 500 - 1;
  TA1CTL = TASSEL_1 + MC_1;                  // ACLK, in upmode

  __bis_SR_register(CPUOFF);                // CPU off
}
