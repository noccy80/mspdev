//******************************************************************************
//  MSP430F22x4 Demo - OA1, Comparator Mode
//
//  Description: Configure OA1 for Comparator mode. In this example, OA1
//  is configured as a comparator. The comparator reference is connected to
//  the "-" input and comes from the integrated R ladder. The reference level
//  is selected with the OAFBR bits. The "+" terminal is connected to OA1I0.
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
//            |                   |    Output goes high when
//            |                   |    Input > (0.25 * AVcc)
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
  OA1CTL0 = OAPM_1 + OAADC1;                // Slow slew rate,
                                            // "+" connected to OA1I0 (default),
                                            // Output connected to A3/OA1O
  OA1CTL1 = OAFBR_4 + OAFC_3 + OARRIP;      // "-" connected to AVcc * 4/16,
                                            // Comparator mode,
                                            // Reverse resistor connection

  ADC10AE0 = 0x18;                          // P2.4/3 analog function select
  LPM3;                                     // Enter LPM3
}
