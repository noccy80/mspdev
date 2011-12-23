//*****************************************************************************
//  MSP-FET430P430 Demo - OA0, Comparator Mode
//
//  Description: Configure OA0 for Comparator mode. In this example, OA0 is
//  configured as a comparator. The comparator reference is connected to
//  the "-" input and comes from the integrated R ladder. The reference level
//  is selected with the OAFBR bits. The "+" terminal is connected to OA0I0.
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
  OA0CTL0 = OAPM_1 + OAADC1;                // Select inputs, power mode
  OA0CTL1 = OAFC_3 + OAFBR_1 + OARRIP;      // Mode, OAFBRx sets level

  LPM3;                                     // LPM3
}
