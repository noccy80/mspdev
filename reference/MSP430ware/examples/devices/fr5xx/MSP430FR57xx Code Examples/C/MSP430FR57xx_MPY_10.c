//******************************************************************************
//   MSP430FR57xx Demo - 32x32 Signed Multiply
//
//   Description: Hardware multiplier is used to multiply two numbers.
//   The calculation is automatically initiated after the second operand is
//   loaded. Results are stored in RES0, RES1, RES2 and RES3.
//
//    MCLK = SMCLK = default DCO
//
//                MSP430FR5739
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************
#include "msp430fr5739.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  MPYS32L = 0x1234;                         // Load lower 16 bits of operand 1
  MPYS32H = 0x1234;                         // Load upper 16 bits of operand 1

  OP2L = 0x5678;                            // Load lower 16 bits of operand 2
  OP2H = 0x5678;                            // Load upper 16 bits of operand 2
  
  __delay_cycles(50);
  __bis_SR_register(LPM4_bits);             // Enter LPM4
  __no_operation();                         // For debugger
}
