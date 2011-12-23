//******************************************************************************
//   MSP430F534x Demo - Write a Word to Port A (Port1+Port2.7)
//
//   Description: Writes a Word(0x80FF) to Port A and stays in LPM4. All PA pins 
//      available on this device are made to drive a logic high
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                MSP430F534x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST          PA.x|-->HI
//            |                 |
//            |                 |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5342.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  PADIR |= 0xFFFF;                          // PA.x output (P1.x+P2.7)
  PAOUT = 0x80FF;                           // Write to Port A

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupts enabled
  __no_operation();                         // Place BREAKPOINT HERE and check register PAOUT, P1OUT and P2OUT
}
