//******************************************************************************
//  MSP-FET430P120 Demo - Timer_A, Toggle P1.1/TA0, Up Mode, HF XTAL ACLK
//
//  Description: Toggle P1.1 using hardware TA0 output. Timer_A is configured
//  for up mode with CCR0 defining period, TA0 also output on P1.1. In this
//  example, CCR0 is loaded with 500-1 and TA0 will toggle P1.1 at TACLK/500.
//  Thus the output frequency on P1.1 will be the TACLK/1000. No CPU or software
//  resources required.
//  MCLK = ACLK = TACLK = HF XTAL
//  As coded with TACLK = ACLK, P1.1 output frequency = HF XTAL/1000
//  //* HF XTAL REQUIRED AND NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//           MSP430F123(2)
//         -----------------
//     /|\|              XIN|-
//      | |                 | HF XTAL (455k - 8MHz)
//      --|RST          XOUT|-
//        |                 |
//        |         P1.1/TA0|--> ACLK/1000
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x12x2.h>

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 |= XTS;                           // ACLK = LFXT1 = HF XTAL

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);               // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  BCSCTL2 |= SELM_3;                        // MCLK = LFXT1 (safe)
  P1DIR |= 0x02;                            // P1.1 output
  P1SEL |= 0x02;                            // P1.1 option select
  CCTL0 = OUTMOD_4;                         // CCR0 toggle mode
  CCR0 = 500-1;
  TACTL = TASSEL_1 + MC_1;                  // ACLK, in upmode

  _BIS_SR(CPUOFF);                          // CPU off
}
