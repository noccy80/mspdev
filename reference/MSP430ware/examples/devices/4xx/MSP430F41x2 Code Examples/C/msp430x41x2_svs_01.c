//*******************************************************************************
//   MSP430x41x2 Demo - SVS, POR @ 2.5V Vcc
//
//  Description: The SVS POR feature is used to disable normal operation that
//  toggles P5.1 by xor'ing P5.1 inside of a software loop.
//  In the example, when VCC is above 2.5V, the MSP430 toggles P5.1. When VCC is
//  below 2.5V, the SVS resets the MSP430, and no toggle is seen.
//  ACLK= n/a, MCLK= SMCLK= default DCO =32 x ACLK = 1048576Hz
//  
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
#include "msp430x41x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P5DIR |= 0x02;                            // Set P5.1 to output direction
  SVSCTL = 0x60 + PORON;                    // SVS POR enabled @ 2.5V

  for (;;)
  {
    volatile unsigned int i;
    i = 50000;                              // Delay
    do (i--);
    while (i != 0);
    P5OUT ^= 0x02;                          // Toggle P5.1 using exclusive-OR
  }
}
