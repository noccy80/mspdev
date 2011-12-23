//******************************************************************************
//   MSP430F51x2 Demo - 16x16 Signed Multiply
//
//   Description: Hardware multiplier is used to multiply two numbers.
//   The calculation is automatically initiated after the second operand is
//   loaded. Results are stored in RESLO, RESHI and SUMEXT = FFFF if result is
//   negative, SUMEXT = 0 otherwise. Result is also stored as Result variable.
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                MSP430F51x2
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   Dec 2009
//   Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include  "msp430f5172.h"

  signed int multiplier = 0x1234;
  signed int operand = -6578;
  signed long result;                       // global variable for multiply
                                            // result

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  MPYS = multiplier;                        // Load first operand -signed mult
  OP2 = operand;                            // Load second operand

  result = RESHI;                           // Load RESHI word result
  result = (result<<16)|RESLO;              // Shift RESHI left and concat with
                                            // RESLO word result
  
  __bis_SR_register(LPM4_bits);             // Enter LPM4
  __no_operation();                         // For debugger 
}
