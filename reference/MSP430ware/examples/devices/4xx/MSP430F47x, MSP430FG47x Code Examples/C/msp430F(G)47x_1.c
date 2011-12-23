//*******************************************************************************
//  MSP430F(G)47x Demo - Software Toggle P4.6
//
//  Description: Toggle P4.6 by xor'ing P4.6 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F(G)47x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P4.6|-->LED
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//*****************************************************************************
#include "msp430xG47x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P4DIR |= 0x40;                            // Set P4.6 to output direction

  for (;;)
  {
    volatile unsigned int i;

    P4OUT ^= 0x40;                          // Toggle P4.6 using exclusive-OR

    i = 50000;                              // Delay
    do (i--);
    while (i != 0);
  }
}
