//******************************************************************************
//   MSP430F530x Demo - Write a Word to Port A (Port1+Port2)
//
//   Description: Writes a Word(1234h) to Port A and stays in LPM4
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                MSP430F530x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST          PA.x|-->HI
//            |                 |
//            |                 |
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  PADIR |= 0xFFFF;                          // PA.x output
  PAOUT = 0x1234;                           // Write to Port A

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupts enabled
  __no_operation();                         // Place BREAKPOINT HERE and check register PAOUT, P1OUT and P2OUT
}
