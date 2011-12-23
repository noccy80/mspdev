//******************************************************************************
//  MSP430G2xx1 Demo - WDT+ Failsafe Clock, DCO SMCLK
//
//  Description; Allow WDT+ in watchdog to timeout. Toggle P1.0 in main
//  funnction. LPM4 is entered, this example will demonstrate WDT+ feature
//  of preventing WDT+ clock to be disabled.
//  The WDT+ will not allow active WDT+ clock to be disabled by software, the
//  LED continues to Flash because the WDT times out normally even though
//  software has attempted to disable WDT+ clock source.
//  The MSP430F1xx will stop code execution when software disables WDT+ clock
//  source.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//		  MSP430G2xx1
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include  <msp430g2231.h>

void main(void)
{
  P1DIR |= 0x01;                            // Set P1.0 to output
  P1OUT ^= 0x01;                            // Toggle P1.0
  _BIS_SR(LPM4_bits);                       // Stop all clocks
}
