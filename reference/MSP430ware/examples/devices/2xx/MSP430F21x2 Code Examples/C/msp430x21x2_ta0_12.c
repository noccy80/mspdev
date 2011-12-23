//******************************************************************************
//  MSP430F21x2 Demo - Timer0_A3, Toggle P1.1/TA0_0, Up Mode, HF XTAL ACLK
//
//  Description: Toggle P1.1 using hardware TA0_0 output. Timer0_A3 is configured
//  for up mode with TA0CCR0 defining period, TA0_0 also output on P1.1. In this
//  example, TA0CCR0 is loaded with 500-1 and TA0_0 will toggle P1.1 at TA0CLK/500.
//  Thus the output frequency on P1.1 will be the TA0CLK/1000. No CPU or
//  software resources required.
//  ACLK = MCLK = TA0CLK = HF XTAL
//  //* HF XTAL REQUIRED AND NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//  As coded with TA0CLK = ACLK, P1.1 output frequency = HF XTAL/1000
//
//           MSP430F21x2
//         -----------------
//     /|\|              XIN|-
//      | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//      --|RST          XOUT|-
//        |                 |
//        |       P1.1/TA0_0|--> ACLK/1000
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2008
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
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

  P1DIR |= 0x02;                            // P1.1 output
  P1SEL |= 0x02;                            // P1.1 option select
  TA0CCTL0 = OUTMOD_4;                       // TA0CCR0 toggle mode
  TA0CCR0 = 500 - 1;
  TA0CTL = TASSEL_1 + MC_1;                  // ACLK, in upmode

  __bis_SR_register(CPUOFF);                // CPU off
}
