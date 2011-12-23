//*****************************************************************************
//  MSP-FET430P430 Demo - OA0, General-Purpose Mode
//
//  Description: Configure OA0 for General-Purpose mode.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430FG439
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P6.0/OA0I0         |
//     "-" -->|P6.2/OA0I1         |
//            |                   |
//            |          P6.1/OA0O|--> OA0 Output
//            |                   |
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
  OA0CTL0 = OAN_1 + OAPM_1;                 // Select inputs, power mode
  OA0CTL1 = OARRIP;                         // Rail-to-rail inputs

  LPM3;                                     // LPM3
}
