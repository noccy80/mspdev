//******************************************************************************
//   MSP430xG46x Demo - 3-Amp Differential Amplifier with OA1, OA2, and OA0
//
//   Description: Configure OA1, OA2, and OA0 as a 3-Amp Differential Amp.
//   In this configuration, the R2/R1 ratio sets the gain. The R ladders for
//   OA1 and OA0 form the R2/R1 dividers. The OAFBRx settings for both OA1
//   and OA0 must be equal.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                |\
//                | \ OA1
//   V2-----------|+ \           R1             R2
//                |   |----+---/\/\/\/---+----/\/\/\/----|
//            ----|- /     |             |               |
//            |   | /      |             |  |\          GND
//            |   |/       |             |  | \ OA0
//            |____________|             ---|+ \
//                                          |   |--------+--------->
//                                       ---|- /         |
//                |\                     |  | /          | Vout = (V2-V1)xR2/R1
//                | \ OA2                |  |/           |        (Gain is 3)
//   V1-----------|+ \           R1      |      R2       |
//                |   |----+---/\/\/\/---+----/\/\/\/----|
//            ----|- /     |
//            |   | /      |
//            |   |/       |
//            |____________|
//
//
//                 MSP430xG461x
//              -------------------
//          /|\|                XIN|-
//           | |                   |
//           --|RST            XOUT|-
//             |                   |
//       V2 -->|P6.4/OA1I0         |
//       V1 -->|P6.6/OA2I0         |
//             |                   |
//             |          P6.1/OA0O|--> Diff Amp Output
//
//   K. Quiring / A. Dannenberg
//   Texas Instruments Inc.
//   June 2007
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  OA0CTL0 = OAN_3+OAP_3+OAPM_1+OAADC1;      // Select inputs, output
  OA0CTL1 = OAFC_6+OAFBR_4+OARRIP;          // Inverting PGA mode,
                                            // OAFBRx sets gain
                                            // limited range (see datasheet)

  OA1CTL0 = OAPM_1;                         // Select inputs, power mode
  OA1CTL1 = OAFC_1+OAFBR_4+OARRIP;          // Unity gain mode,
                                            // OAFBRx sets gain
                                            // limited range (see datasheet)

  OA2CTL0 = OAPM_1;                         // Select inputs, power mode
  OA2CTL1 = OAFC_7+OARRIP;                  // Differential amp mode
                                            // limited range (see datasheet)

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3
}
