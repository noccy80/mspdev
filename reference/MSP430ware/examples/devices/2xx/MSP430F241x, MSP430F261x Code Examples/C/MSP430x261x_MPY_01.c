//******************************************************************************
//   MSP430x26x Demo - 16x16 Unsigned Multiply
//
//   Description: Hardware multiplier is used to multiply two numbers.
//   The calculation is automatically initiated after the second operand is
//   loaded. Results are stored in RESLO and RESHI.
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//             MSP430F261x/241x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x26x.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  MPY = 0x1234;                             // Load first operand -unsigned mult
  OP2 = 0x5678;                             // Load second operand
  _BIS_SR(LPM4_bits);                       // LPM4
}
