//******************************************************************************
//  MSP430F23x0 Demo - Poll P1 With Software with Internal Pull-up
//
//  Description: Poll P1.3 in a loop, if hi P1.0 is set, if low, P1.0 reset.
//  Internal pullup enabled on P1.3.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F23x0
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |      R          |
//      --o--| P1.3-o      P1.0|-->LED
//     \|/
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  January 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x23x0.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR = 0x01;                             // P1.0 output, else input
  P1OUT = 0x08;                             // P1.3 pullup
  P1REN |= 0x08;                            // P1.3 pullup

  while (1)                                 // Test P1.3
  {
    if (0x08 & P1IN)
      P1OUT |= 0x01;                        // if P1.3 set, set P1.0
    else
      P1OUT &= ~0x01;                       // else reset
  }
}


