//******************************************************************************
//   MSP430x47xx Demo - 16x16 Signed Multiply
//
//   Description: Hardware multiplier is used to multiply two numbers.
//   The calculation is automatically initiated after the second operand is
//   loaded. Results are stored in RESLO, RESHI and SUMEXT = FFFF if result is
//   negative, SUMEXT = 0 otherwise.
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                 MSP430x47xx
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//  P. Thanigai / K.Venkat
//  Texas Instruments Inc.
//  November 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x47x4.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  MPYS = 0x01234;                           // Load first operand -signed mult
  OP2 = 0x05678;                            // Load second operand
  _BIS_SR(LPM4_bits + GIE);                 // LPM4
}
