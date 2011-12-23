//******************************************************************************
//  MSP430TC0701 Demo - Software Poll P1.4, Set P1.0 if P1.4 = 1
//
//  Description: Poll P1.4 in a loop, if hi P1.0 is set, if low, P1.0 reset.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//              MSP430TC0701
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--|P1.4         P1.0|-->LED
//     \|/
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= BIT0;                            // Set P1.0 to output direction

  while (1)                                 // Test P1.4
  {
    if (P1IN & BIT4)
      P1OUT |= BIT0;                        // if P1.4 set, set P1.0
    else
      P1OUT &= ~BIT0;                       // else reset
  }
}


