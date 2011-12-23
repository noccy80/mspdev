//******************************************************************************
//  MSP430F22x4 Demo - OA0, General-Purpose Mode
//
//  Description: Configure OA0 for General-Purpose mode. In this mode, all
//  OA connections are available externally.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F22x4
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P2.0/A0/OA0I0      |
//     "-" -->|P2.2/A2/OA0I1      |
//            |                   |
//            |       P2.1/A1/OA0O|--> OA0 Output
//            |                   |
//            |                   |
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  March 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.40B
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  OA0CTL0 = OAN_1 + OAPM_1;                 // "+" connected to OA1I0 (default),
                                            // "-" connected to OA1I1,
                                            // Slow slew rate,
                                            // Output connected to A1/OA0A
  ADC10AE0 = 0x07;                          // P2.2/1/0 analog function select
  LPM3;                                     // Enter LPM3
}
