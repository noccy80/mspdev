//*****************************************************************************
//  MSP-FET430P430 Demo - OA0, Inverting PGA Mode
//
//  Description: Configure OA0 for Inverting PGA mode. In this mode, the
//  "+" terminal must be supplied with an offset, since the OA is a
//  single-supply opamp, and the input must be positive. If an offset is
//  not supplied, the opamp will try to drive its output negative, which
//  cannot be done. In this example, the offset is provided by DAC0 and
//  is 1.5V. The "-" terminal is connected to the R ladder tap and the
//  OAFBRx bits select the gain. The input signal should be AC coupled.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                    MSP430FG439
//                -------------------
//            /|\|                XIN|-
//             | |                   |
//             --|RST            XOUT|-
//               |                   |
//    "-" --||-->|P6.0/OA0I0         |
//               |                   |
//               |          P6.1/OA0O|->  OA0 Output
//               |                   |    Gain is -7
//
//  M. Mitchell
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430xG43x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  ADC12CTL0 = REFON + REF2_5V;              // Reference = 2.5V for DAC0
  DAC12_0CTL = DAC12IR + DAC12AMP_2 + DAC12ENC;
  DAC12_0DAT = 0x099A;                      // Offset level = 1.5V

  OA0CTL0 = OAP_2 + OAPM_1 + OAADC1;        // Select inputs, power mode
  OA0CTL1 = OAFC_6 + OAFBR_6 + OARRIP;      // Mode, OAFBRx sets gain

  LPM3;                                     // LPM3
}
