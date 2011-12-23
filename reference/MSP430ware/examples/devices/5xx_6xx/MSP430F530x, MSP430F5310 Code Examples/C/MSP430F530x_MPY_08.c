//******************************************************************************
//  MSP430F530x Demo - 8x8 Signed Multiply Accumulate
//
//   Description: Hardware multiplier is used to multiply two numbers.
//   The calculation is automatically initiated after the second operand is
//   loaded.  A second multiply accumulate operation is performed after that.
//   Results are stored in RESLO and RESHI.  SUMEXT contains the extended sign of
//   result.
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

  MPY = 0x1234;                             // Load 1st operand - unsigned mult
  OP2 = 0x5678;                             // Load second operand

  value1 = 0x12;                            // Load first operand - signed MAC
  value2 = 0x16;                            // Load second operand

  MACS_B = value1;                          // Signed multiplication
  OP2_B = value2;                           // Byte access removes the need for
                                            // ... sign extension

  __bis_SR_register(LPM4_bits);             // Enter LPM4
  __no_operation();                         // For debugger  
}
