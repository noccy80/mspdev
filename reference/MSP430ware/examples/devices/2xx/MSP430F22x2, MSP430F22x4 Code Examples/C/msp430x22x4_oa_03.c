//******************************************************************************
//  MSP430F22x4 Demo - OA0, Inverting PGA Mode
//
//  Description: Configure OA0 for Inverting PGA mode. In this mode, the
//  "+" terminal must be supplied with an offset, since the OA is a
//  single-supply opamp, and the input must be positive. If an offset is
//  not supplied, the opamp will try to drive its output negative, which
//  cannot be done. In this example, the offset is provided by an external
//  terminal. The "-" terminal is connected to the R ladder tap and the
//  OAFBRx bits select the gain. The input signal is AC coupled.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                   MSP430F22x4
//                -------------------
//            /|\|                XIN|-
//             | |                   |
//             --|RST            XOUT|-
//               |                   |
//    "-" --||-->|P2.0/A0/OA0I0      |
//    offset  -->|P2.2/A2/OA0I1      |
//               |       P2.1/A1/OA0O|-->  OA0 Output
//               |                   |     Gain is -7
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
  OA0CTL0 = OAP_1 + OAPM_1 + OAADC1;        // "+" connected to OA0I1,
                                            // "-" connected to OA0I0 (default)
                                            // Slow slew rate,
                                            // Output connected to A1/OA0O
  OA0CTL1 = OAFBR_6 + OAFC_6;               // Amplifier gain is -7,
                                            // Inverting PGA mode
  ADC10AE0 = 0x07;                          // P2.2/1/0 analog function select
  LPM3;                                     // Enter LPM3
}
