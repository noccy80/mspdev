//******************************************************************************
//   MSP430F530x Demo - 8x8 Signed Multiply
//
//   Description: Hardware multiplier is used to multiply two numbers.
//   The calculation is automatically initiated after the second operand is
//   loaded. Results are stored in RESLO, RESHI and SUMEXT = FFFF if result is
//   negative, SUMEXT = 0 otherwise.
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
  unsigned char value1,value2;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  
  value1 = 0x04;                            // Assign operands for signed mult
  value2 = 0x84;
  
  MPYS_B = value1;                          // Load MPYS_B to denote signed 8-bit operand one
  OP2_B = value2;                           // Load OP2 with byte access to avoid
                                            // the need for sign extension

  __bis_SR_register(LPM4_bits);             // Enter LPM4
  __no_operation();                         // For debugger
}
