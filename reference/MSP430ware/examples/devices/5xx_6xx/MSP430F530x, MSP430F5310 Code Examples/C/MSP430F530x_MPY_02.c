//******************************************************************************
//   MSP430F530x Demo - 8x8 Unsigned Multiply
//
//   Description: Hardware multiplier is used to multiply two numbers.
//   The calculation is automatically initiated after the second operand is
//   loaded. Results are stored in RESLO and RESHI.
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//               MSP430F530x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
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
  MPY = 0x12;                               // Load first operand -unsigned mult
  OP2 = 0x56;                               // Load second operand
  
  __bis_SR_register(LPM4_bits);             // Enter LPM4
  __no_operation();                         // For debugger
}
