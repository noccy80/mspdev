//*****************************************************************************
//  MSP430xG46x Demo - OA1, Unity-Gain Buffer Mode
//
//  Description: Configure OA1 for Unity-Gain Buffer mode.
//  ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                MSP430xG461x
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P6.4/OA1I0         |
//            |                   |
//            |          P6.3/OA1O|--> OA1 Output
//            |                   |
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
  OA1CTL0 = OAPM_1 + OAADC1;                // Select inputs, power mode
  OA1CTL1 = OAFC_1 + OARRIP;                // Unity gain buffer mode,
                                            // limited range (see datasheet)

  __bis_SR_register(LPM3_bits + GIE);       // LPM3
}
