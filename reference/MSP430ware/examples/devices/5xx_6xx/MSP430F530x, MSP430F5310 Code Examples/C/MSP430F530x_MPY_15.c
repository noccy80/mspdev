//******************************************************************************
//   MSP430F530x Demo - Fractional mode, Q15 multiplication
//
//   Description: The example illustrates multiplication of 2 Q15 numbers in
//   fractional mode. The result is a Q15 (15 bit) number stored in the RES1
//   register. It can be viewed in the debugger window.
//
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                MSP430F530x
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

unsigned int Result_Q15;

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  MPY32CTL0 = MPYFRAC;                      // Set fractional mode

  MPYS = 0x7D70;                            // Load first operand
  OP2 = 0x1000;                             // Load second operand

  Result_Q15 = RESHI;                       // Q15 result

  MPY32CTL0 &= ~MPYFRAC;
  
  __bis_SR_register(LPM4_bits);             // Enter LPM4
  __no_operation();                         // For debugger
}
