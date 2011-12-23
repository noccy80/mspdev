//******************************************************************************
//  MSP430F22x4 Demo - OA1, Inverting PGA Mode
//
//  Description: Configure OA1 for Inverting PGA mode. In this mode, the
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
//    "-" --||-->|P2.4/A4/OA1I0      |
//    offset  -->|P3.7/A7/OA1I2      |
//               |      P4.4/A13/OA1O|-->  OA1 Output
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
  OA1CTL0 = OAP_2 + OAPM_1 + OAADC0;        // "+" connected to OA1I2,
                                            // "-" connected to OA1I0 (default),
                                            // Slow slew rate,
                                            // Output connected to A13/OA1O
  OA1CTL1 = OAFBR_6 + OAFC_6;               // Amplifier gain is -7,
                                            // Inverting PGA mode
  ADC10AE0 = 0x88;                          // P3.7/P2.4 analog function select
  ADC10AE1 = 0x20;                          // P4.4 analog function select
  LPM3;                                     // Enter LPM3
}
