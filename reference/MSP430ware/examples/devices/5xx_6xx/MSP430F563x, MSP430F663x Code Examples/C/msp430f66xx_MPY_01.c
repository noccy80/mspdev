//******************************************************************************
//    MSP430F66x Demo - 16x16 Unsigned Multiply
//
//   Description: Hardware multiplier is used to multiply two numbers.
//   The calculation is automatically initiated after the second operand is
//   loaded. Results are stored in RESLO and RESHI.
//
//   ACLK = REFO, MCLK = SMCLK = default DCO
//
//                MSP430F66x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   Nov 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************
#include <msp430f6638.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  MPY = 0x1234;                             // Load first operand -unsigned mult
  OP2 = 0x5678;                             // Load second operand
  
  __bis_SR_register(LPM4_bits);             // Enter LPM4 
  __no_operation();                         // For debugger  
}
