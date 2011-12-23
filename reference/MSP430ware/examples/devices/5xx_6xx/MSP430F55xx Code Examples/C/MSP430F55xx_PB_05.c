//******************************************************************************
//   MSP430TC0701 Demo - Write a Word to Port B (Port3+Port4)
//
//   Description: Writes a Word(1234h) to Port B and stays in LPM4
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//               MSP430TC0701
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  PBDIR |= 0x0FFFF;                         // PB.x output
  PBOUT = 0x1234;                           // Write to PortB

  __bis_SR_register(LPM4_bits + GIE);     // Enter LPM4 w/interrupt
  __no_operation();                         // Place BREAKPOINT HERE and check register PBOUT, P3OUT and P4OUT
}
