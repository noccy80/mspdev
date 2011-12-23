//******************************************************************************
//   MSP430x26x Demo - Write a byte to Port 1
//
//   Description: Writes a byte(0xFF) to Port 1 and stays in LPM4 mode
//   ACLK = n/a, MCLK = SMCLK = default DCO
//
//              MSP430F261x/241x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//            |                 |
//
//   B. Nisarga
//   Texas Instruments Inc.
//   September 2007
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include "msp430x26x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR = 0x0FF;                            // Set P1.x to output direction  
  P1OUT = 0x0FF;                            // Set all P1 pins HI
  
  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}

