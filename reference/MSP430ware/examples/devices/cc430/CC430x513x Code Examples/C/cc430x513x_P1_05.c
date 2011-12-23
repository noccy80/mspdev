//******************************************************************************
//   CC430F513x Demo - Write a byte to Port 1
//
//   Description: Writes a byte(0xFF) to Port 1 and stays in LPM4 mode
//   ACLK = n/a, MCLK = SMCLK = default DCO
//
//                CC430F5137
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |             P1.x|-->HI
//            |                 |
//            |                 |
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x513x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR = 0xFF;                             // Set P1.x to output direction
  P1OUT = 0xFF;                             // Set all P1 pins HI

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
  __no_operation();                         // For debugger
}

