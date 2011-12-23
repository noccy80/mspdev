//******************************************************************************
//   MSP430F54x Demo - 16x16 Signed Multiply Accumulate
//
//   Description: Hardware multiplier is used to multiply two numbers.
//   The calculation is automatically initiated after the second operand is
//   loaded.  A second multiply-accumulate operation is performed after that.
//   Results are stored in RESLO and RESHI.  SUMEXT contains the extended sign
//   of the result.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//               MSP430F5438
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//   M Smertneck / W. Goh
//   Texas Instruments Inc.
//   September 2008
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "msp430x54x.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  MPY = 0x1234;                             // Load first operand -unsigned mult
  OP2 = 0x5678;                             // Load second operand

  MACS = 0x1234;                            // Load first operand -signed MAC
  OP2 = 0x5678;                             // Load second operand

  __bis_SR_register(LPM4_bits);             // Enter LPM4
  __no_operation();                         // For debugger  
}
