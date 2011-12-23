//******************************************************************************
//  MSP430F21x2 Demo - Software Poll P1.3, Set P1.0 if P1.3 = 1
//
//  Description: Poll P1.3 in a loop, if hi P1.0 is set, if low, P1.0 reset.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F21x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--|P1.3         P1.0|-->LED
//     \|/
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x21x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  while (1)                                 // Test P1.3
  {
    if (0x08 & P1IN)
      P1OUT |= 0x01;                        // if P1.3 set, set P1.0
    else
      P1OUT &= ~0x01;                       // else reset
  }
}


