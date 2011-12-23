//******************************************************************************
//  MSP430F22x4 Demo - Software Poll P1.2, Set P1.0 if P1.2 = 1
//
//  Description: Poll P1.2 in a loop, if hi P1.0 is set, if low, P1.0 reset.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--|P1.2         P1.0|-->LED
//     \|/
//
//  A. Dannenberg / W. Goh
//  Texas Instruments Inc.
//  November 2008
//  Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  while (1)                                 // Test P1.2
  {
    if (0x04 & P1IN)
      P1OUT |= 0x01;                        // if P1.2 set, set P1.0
    else
      P1OUT &= ~0x01;                       // else reset
  }
}


