//*******************************************************************************
//  MSP430x41x2 Demo - Software Toggle P5.1
//
//  Description: Toggle P5.1 by xor'ing P5.1 inside of a software loop.
//  ACLK= n/a, MCLK= SMCLK= default DCO ~1.045MHz
//
//               MSP430x41x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************

#include  <msp430x41x2.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P5DIR |= 0x02;                            // Set P5.1 to output direction

  for (;;)
  {
    volatile unsigned int i;

    P5OUT ^= 0x02;                          // Toggle P5.1 using exclusive-OR

    i = 10000;                              // Delay
    do (i--);
    while (i != 0);
  }
}
