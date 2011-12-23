//******************************************************************************
//  MSP430F22x4 Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
//
//  Description: Buffer ACLK on P2.0, SMCLK(DCO) on P2.1 and MCLK/10 on
//  P2.2.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = CALxxx_8MHZ = 8MHz
//  //* External watch crystal on XIN XOUT is required for ACLK *//
//
//               MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P2.0|-->ACLK = 32kHz
//            |             P2.1|-->SMCLK = 8MHz
//            |             P2.2|-->MCLK/10 = DCO/10
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop Watchdog Timer
  BCSCTL1 = CALBC1_8MHZ;                    // Set DCO to 8MHz
  DCOCTL = CALDCO_8MHZ;
  P2DIR |= 0x07;                            // P2.0,1,2 output direction
  P2SEL |= 0x03;                            // P2.0 = ACLK, P2.1 = SMCLK

  while (1)
  {
    P2OUT |= 0x04;                          // P2.2 = 1
    P2OUT &= ~0x04;                         // P2.2 = 0
  }
}
