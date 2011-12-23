//*****************************************************************************
//  MSP430xG46x Demo - OA0, Non-Inverting PGA Mode
//
//  Description: Configure OA0 for Non-Inverting PGA mode. In this mode,
//  the "-" terminal is connected to the R ladder tap and the OAFBRx bits
//  select the gain.
//  ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                 MSP430xG461x
//              -------------------
//          /|\|                XIN|-
//           | |                   |
//           --|RST            XOUT|-
//             |                   |
//      "+" -->|P6.0/OA0I0         |
//             |                   |
//             |          P6.1/OA0O|--> OA0 Output
//             |                   |    Gain is 8
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
  OA0CTL0 = OAPM_1 + OAADC1;                // Select inputs, power mode
  OA0CTL1 = OAFC_4 + OAFBR_6 + OARRIP;      // Non-inverting PGA mode,
                                            // gain is 8,
                                            // limited range (see datasheet)

  __bis_SR_register(LPM3_bits + GIE);       // LPM3
}

