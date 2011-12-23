//*****************************************************************************
//  MSP430xG46x Demo - OA1, Inverting PGA Mode
//
//  Description: Configure OA1 for Inverting PGA mode. In this mode, the
//  "+" terminal must be supplied with an offset, since the OA is a
//  single-supply opamp, and the input must be positive. If an offset is
//  not supplied, the opamp will try to drive its output negative, which
//  cannot be done. In this example, the offset is provided by DAC120
//  and is 1.5V. The "-" terminal is connected to the R ladder tap and
//  the OAFBRx bits select the gain. The input signal should be AC coupled.
//  ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                   MSP430xG461x
//                -------------------
//            /|\|                XIN|-
//             | |                   |
//             --|RST            XOUT|-
//               |                   |
//    "-" --||-->|P6.4/OA1I0         |
//               |                   |
//               |          P6.3/OA1O|-->  OA1 Output
//               |                   |     Gain is -7
//
// K. Quiring / A. Dannenberg
// Texas Instruments Inc.
// June 2007
// Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//*****************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  ADC12CTL0 = REFON + REF2_5V;              // Reference = 2.5V for DAC0
  DAC12_0CTL = DAC12IR + DAC12AMP_2 + DAC12ENC;
  DAC12_0DAT = 0x099A;                      // Offset level = 1.5V

  OA1CTL0 = OAP_2+OAPM_1+OAADC1;            // Select inputs, power mode
  OA1CTL1 = OAFC_6+OAFBR_6 + OARRIP;        // Inverting PGA mode,
                                            // amplifier gain is -7,
                                            // limited range (see datasheet)

  __bis_SR_register(LPM3_bits + GIE);       // LPM3
}
