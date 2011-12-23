//******************************************************************************
//  MSP430G2xx1 Demo - Software Poll P1.4, Set P1.0 if P1.4 = 1
//
//  Description: Poll P1.4 in a loop, if hi P1.0 is set, if low, P1.0 reset.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430G2xx1
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//     /|\   |                 |
//      --o--|P1.4         P1.0|-->LED
//     \|/
//
//  D. Dang
//  Texas Instruments, Inc
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include  <msp430g2231.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  while (1)                                 // Test P1.4
  {
    if ((0x10 & P1IN)) P1OUT |= 0x01;       // if P1.4 set, set P1.0
    else P1OUT &= ~0x01;                    // else reset
  }
}


