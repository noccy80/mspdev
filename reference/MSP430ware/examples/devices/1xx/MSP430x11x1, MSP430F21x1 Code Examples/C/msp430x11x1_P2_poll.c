//******************************************************************************
//  MSP430x11x1 Demo - Software Poll P2.0, Set P1.0 if P2.0 = 1
//
//  Description: Poll P2.0 in a loop, if hi P1.0 is set, if low, P1.0 reset.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~ 800k
//
//                MSP430F1121
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--| P2.0        P1.0|-->LED
//     \|/
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************

#include <msp430x11x1.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  while (1)                                 // Test P2.0
  {
    if ((0x01 & P2IN)) P1OUT |= 0x01;       // if P2.0 set, set P1.0
    else P1OUT &= ~0x01;                    // else reset
  }
}


