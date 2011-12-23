//******************************************************************************
//   MSP430x471xx Demo - 16x16 Signed Multiply
//
//   Description: Hardware multiplier is used to multiply two numbers.
//   The calculation is automatically initiated after the second operand is
//   loaded. Results are stored in RESLO, RESHI and SUMEXT = FFFF if result is
//   negative, SUMEXT = 0 otherwise.
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                 MSP430x471xx
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  MPYS = 0x01234;                           // Load first operand -signed mult
  OP2 = 0x05678;                            // Load second operand
  _BIS_SR(LPM4_bits + GIE);                 // LPM4
}
