//*****************************************************************************
//  MSP-FET430P430 Demo - OA1, Non-Inverting PGA Mode
//
//  Description: Configure OA1 for Non-Inverting PGA mode. In this mode,
//  the "-" terminal is connected to the R ladder tap and the OAFBRx bits
//  select the gain.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430FG439
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P6.4/OA1I0         |
//            |                   |
//            |          P6.3/OA1O|--> OA1 Output
//            |                   |    Gain is 8
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

  OA1CTL0 = OAPM_1 + OAADC1;                // Select inputs, power mode
  OA1CTL1 = OAFC_4 + OAFBR_6 + OARRIP;      // Mode, OAFBRx sets gain

  LPM3;                                     // LPM3;
}
