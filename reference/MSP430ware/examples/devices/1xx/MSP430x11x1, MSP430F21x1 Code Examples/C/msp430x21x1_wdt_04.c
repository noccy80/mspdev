//*******************************************************************************
//   MSP430x21x1 Demo - WDT+ Failsafe Clock, DCO SMCLK
//
//   Description: Allow WDT+ in watchdog mode to timeout. Toggle P1.0 in main
//   function. LPM4 is entered, this example will demonstrate WDT+ feature
//   of preventing WDT+ clock from being disabled. The MSP430F21x1 will not
//   allow active WDT+ clock to be disabled by software. The LED continues to
//   Flash even though software has attempted to disable WDT+ clock source.
//   In contrast, an MSP430F1xx device will stop code execution when software
//   disables WDT clock source.
//   ACLK = n/a, MCLK = SMCLK = default DCO~ 1.16MHz
//
//                MSP430F21x1
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  H. Grewal / A. Dannenberg
//  Texas Instruments Inc.
//  July 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//******************************************************************************

#include  <msp430x21x1.h>

void main(void)
{
  P1DIR |= 0x01;                        // Set P1.0 to output direction
  P1OUT ^= 0x01;                        // Toggle P1.0 using exclusive-OR
  LPM4;                                 // Disable all clocks
  while(1);                             // Loop
}
