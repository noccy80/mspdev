//*******************************************************************************
//  MSP-FET430P140 Demo - SVS, POR @ 2.5V Vcc
//
//  Description: The SVS POR feature is used to disable normal operation that
//  toggles P1.0 by xor'ing P1.0 inside of a software loop.
//  In the example, when VCC is above 2.5V, the MSP430 toggles P1.0. When VCC is
//  below 2.5V, the SVS resets the MSP430, and no toggle is seen.
//  ACLK= n/a, MCLK= SMCLK= default DCO ~ 800k
//  //* MSP430F169 Device Required *//
//
//                MSP430F169
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x16x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  SVSCTL = 0x60 + PORON;                    // SVS POR enabled @ 2.5V

  for (;;)
  {
    volatile unsigned int i;
    i = 50000;                              // Delay
    do (i--);
    while (i != 0);
    P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR
  }
}
