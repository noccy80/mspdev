//******************************************************************************
//  MSP430G2xx1 Demo - Poll P1 With Software with Internal Pull-up
//
//  Description: Poll P1.4 in a loop, if hi P1.0 is set, if low, P1.0 reset.
//  Internal pullup enabled on P1.4.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430G2xx1
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |      R          |
//      --o--| P1.4-o      P1.0|-->LED
//     \|/
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************


#include  <msp430g2231.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR = 0x01;                             // P1.0 output, else input
  P1OUT = 0x10;                             // P1.4 set, else reset
  P1REN |= 0x10;                            // P1.4 pullup

  while (1)                                 // Test P1.4
  {
    if (0x10 & P1IN) P1OUT |= 0x01;         // if P1.4 set, set P1.0
    else P1OUT &= ~0x01;                    // else reset
  }
}


