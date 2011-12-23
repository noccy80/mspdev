//*****************************************************************************
//  MSP-FET430P430 Demo - OA0, Unity-Gain Buffer Mode
//
//  Description: Configure OA0 for Unity-Gain Buffer mode.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430FG439
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P6.0/OA0I0         |
//            |                   |
//            |          P6.1/OA0O|--> OA0 Output
//            |                   |
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
  OA0CTL0 = OAPM_1 + OAADC1;                // Select inputs, power mode
  OA0CTL1 = OAFC_1 + OARRIP;                // Mode, rail-to-rail inputs

  LPM3;                                     // LPM3
}
