//******************************************************************************
//  MSP430F22x4 Demo - Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
//
//  Description: Toggle P1.1 using hardware TA0 output. Timer_A is configured
//  for up/down mode with TACCR0 defining period, TA0 also output on P1.1.
//  In this example, TACCR0 is loaded with 250 and TA0 will toggle P1.1 at
//  TACLK/2*250. Thus the output frequency on P1.1 will be the TACLK/1000.
//  No CPU or software resources required.
//  ACLK = MCLK = TACLK = HF XTAL
//  //* HF XTAL REQUIRED AND NOT INSTALLED ON FET *//
//  //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//  As coded with TACLK = ACLK, P1.1 output frequency = HF XTAL/1000
//
//            MSP430F22x4
//         -----------------
//     /|\|              XIN|-
//      | |                 | HF XTAL (3 – 16MHz crystal or resonator)
//      --|RST          XOUT|-
//        |                 |
//        |         P1.1/TA0|--> ACLK/1000
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 |= XTS;                           // ACLK= LFXT1 = HF XTAL
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
  TACCTL0 = OUTMOD_4;                       // TACCR0 toggle mode
  TACCR0 = 250;
  TACTL = TASSEL_1 + MC_3;                  // ACLK, up-downmode

  __bis_SR_register(CPUOFF);                // CPU off
}
