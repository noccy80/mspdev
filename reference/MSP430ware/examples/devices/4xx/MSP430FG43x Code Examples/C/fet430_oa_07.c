//*****************************************************************************
//  MSP-FET430P430 Demo - OA1, Comparator Mode
//
//  Description: Configure OA1 for Comparator mode. In this example, OA1
//  is configured as a comparator. The comparator reference is on the "-"
//  input and comes from the integrated R ladder. The reference level is
//  selected with the OAFBR bits. The "+" terminal is connected to OA1I0.
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
//            |                   |    Output goes high when
//            |                   |    Input > (0.25 * AVcc)
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
  OA1CTL1 = OAFC_3 + OAFBR_1 + OARRIP;      // Mode, OAFBRx sets level

  LPM3;                                     // LPM3
}

