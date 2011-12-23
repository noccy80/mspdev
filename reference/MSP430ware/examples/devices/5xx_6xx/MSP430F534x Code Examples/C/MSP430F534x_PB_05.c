//******************************************************************************
//   MSP430F534x Demo - Write a Word to Port B (P3.0-P3.4+P4.x)
//
//   Description: Writes a Word(0xFF1F) to Port B and stays in LPM4. All PB pins 
//      available on this device are made to drive a logic high
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//               MSP430F534x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST          PB.x|-->HI
//            |                 |
//            |                 |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   Jun 2011
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5342.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  PBDIR |= 0x0FFFF;                         // PB.x output (P3.0-P3.4+P4.x)
  PBOUT = 0xFF1F;                           // Write to PortB

  __bis_SR_register(LPM4_bits + GIE);     // Enter LPM4 w/interrupt
  __no_operation();                         // Place BREAKPOINT HERE and check register PBOUT, P3OUT and P4OUT
}
