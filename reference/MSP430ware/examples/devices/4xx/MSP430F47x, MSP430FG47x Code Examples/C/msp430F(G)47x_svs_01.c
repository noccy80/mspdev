//*******************************************************************************
//    MSP430F(G)47x Demo - SVS, POR @ 2.5V Vcc
//
//  Description: The SVS POR feature is used to disable normal operation that
//  toggles P4.6 by xor'ing P4.6 inside of a software loop.
//  In the example, when VCC is above 2.5V, the MSP430 toggles P4.6. When VCC is
//  below 2.5V, the SVS resets the MSP430, and no toggle is seen.
//  ACLK= n/a, MCLK= SMCLK= default DCO =32 x ACLK = 1048576Hz
//  
//
//               MSP430F(G)47x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P4.6|-->LED
//
//  P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//******************************************************************************
#include "msp430xG47x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P4DIR |= BIT6;                            // Set P4.6 to output direction
  SVSCTL = 0x60 + PORON;                    // SVS POR enabled @ 2.5V

  for (;;)
  {
    volatile unsigned int i;
    i = 50000;                              // Delay
    do (i--);
    while (i != 0);
    P4OUT ^= BIT6;                          // Toggle P4.6 using exclusive-OR
  }
}
