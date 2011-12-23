//******************************************************************************
//  MSP430F22x4 Demo - OA1, Unity-Gain Buffer Mode
//
//  Description: Configure OA1 for Unity-Gain Buffer mode.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F22x4
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P2.4/A4/OA1I0      |
//            |                   |
//            |       P2.3/A3/OA1O|--> OA1 Output
//            |                   |    Gain is 1
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  March 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  OA1CTL0 = OAPM_1 + OAADC1;                // "+" connected to OA1IO (default),
                                            // Slow slew rate,
                                            // Output connected to A3/OA1O
  OA1CTL1 = OAFC_2;                         // Unity gain buffer mode
  ADC10AE0 = 0x18;                          // P2.4/3 analog function select
  LPM3;                                     // Enter LPM3
}
