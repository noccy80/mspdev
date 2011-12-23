//*****************************************************************************
//  MSP430F(G)47x Demo - OA0, General-Purpose Mode
//
//  Description: Configure OA0 for General-Purpose mode.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F(G)47x
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P1.6/OA0I0         |
//     "-" -->|P6.2/OA0I1         |
//            |                   |
//            |          P6.0/OA0O|--> OA0 Output
//            |                   |
//            |                   |
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//*****************************************************************************
#include "msp430xG47x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  OA0CTL0 = OAN_0 + OAP_0 + OAPM_1;         // Select inputs, power mode

  LPM3;                                     // LPM3
}
