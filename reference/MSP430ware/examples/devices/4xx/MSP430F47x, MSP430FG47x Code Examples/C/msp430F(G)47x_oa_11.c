//*****************************************************************************
//  MSP430F(G)47x Demo - OA1, Unity-Gain Buffer Mode
//
//  Description: Configure OA1 for Unity-Gain Buffer mode.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F(G)47x
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P1.4/OA1I0         |
//            |                   |
//            |          P6.3/OA1O|--> OA1 Output
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
  OA1CTL0 = OAP_0 + OAPM_1;		            // Select inputs, power mode
  OA1CTL1 = OAFC_1;                         // Unity gain mode

  LPM3;                                     // LPM3
  _NOP();                                   // Required only for debugger

}
