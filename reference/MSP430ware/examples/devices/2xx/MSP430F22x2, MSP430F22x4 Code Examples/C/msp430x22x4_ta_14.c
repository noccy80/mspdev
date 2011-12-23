//******************************************************************************
//  MSP430F22x4 Demo - Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
//
//  Description: Toggle P1.1 using hardware TA0 output. Timer_A is configured
//  for up/down mode with TACCR0 defining period, TA0 also output on P1.1. In
//  this example, TACCR0 is loaded with 5 and TA0 will toggle P1.1 at TACLK/2*5.
//  Thus the output frequency on P1.1 will be the TACLK/20. No CPU or software
//  resources required. Normal operating mode is LPM3.
//  ACLK = TACLK = 32kHz, MCLK = default DCO ~1.2MHz
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//
//  As coded with TACLK = ACLK, P1.1 output frequency = 32768/20 = 1.6384kHz.
//
//           MSP430F22x4
//         -----------------
//     /|\|              XIN|-
//      | |                 | 32kHz
//      --|RST          XOUT|-
//        |                 |
//        |         P1.1/TA0|--> ACLK/20
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x02;                            // P1.1 output
  P1SEL |= 0x02;                            // P1.1 option select
  TACCTL0 = OUTMOD_4;                       // TACCR0 toggle mode
  TACCR0 = 5;
  TACTL = TASSEL_1 + MC_3;                  // ACLK, up-downmode

  __bis_SR_register(LPM3_bits);             // Enter LPM3
}
