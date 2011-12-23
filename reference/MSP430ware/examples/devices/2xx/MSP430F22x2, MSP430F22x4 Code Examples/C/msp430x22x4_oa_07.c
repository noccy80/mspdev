//******************************************************************************
//  MSP430F22x4 Demo - OA1, General-Purpose Mode
//
//  Description: Configure OA1 for General-Purpose mode. In this mode, all
//  OA connections are available externally.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F22x4
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P2.4/A4/OA1I0      |
//     "-" -->|P2.3/A3/OA1I1      |
//            |                   |
//            |      P4.4/A13/OA1O|--> OA1 Output
//            |                   |
//            |                   |
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
  OA1CTL0 = OAN_1 + OAPM_1 + OAADC0;        // "+" connected to OA1I0 (default),
                                            // "-" connected to OA1I1,
                                            // Slow slew rate,
                                            // Output connected to A13/OA1O
  ADC10AE0 = 0x18;                          // P2.4/3 analog function select
  ADC10AE1 = 0x20;                          // P4.4 analog function select
  LPM3;                                     // Enter LPM3
}
