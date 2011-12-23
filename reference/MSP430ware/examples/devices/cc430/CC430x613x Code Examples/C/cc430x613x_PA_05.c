//******************************************************************************
//   CC430F613x Demo - Write a Word to Port A (Port1+Port2)
//
//   Description: Writes a Word(FFFFh) to Port A and stays in LPM4
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                CC430F6137
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST          PA.x|-->HI
//            |                 |
//            |                 |
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x613x.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  PADIR |= 0xFFFF;                          // PA.x output
  PAOUT |= 0xFFFF;                          // Set all PA pins HI

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupts enabled
  __no_operation();                         // For debugger  
}
