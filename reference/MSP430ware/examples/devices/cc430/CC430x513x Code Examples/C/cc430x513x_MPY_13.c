//******************************************************************************
//   CC430F513x Demo - Saturation mode overflow test
//
//   Description: The example illustrates a special case showing overflow.
//   The addition result of 2 positive numbers may exceed the highest positive
//   number (0x7FFF FFFF for 32 bit result) due to overflow indicating a negative
//   result. By having the saturation mode enabled, this result can be truncated
//   off to this highest positive number. Results with and without saturation
//   mode are shown.
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                CC430F5137
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include <cc430x513x.h>

unsigned int Result_lower16;
unsigned int Result_upper16;

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  MPY32CTL0 = MPYSAT;                       // Enable saturation mode

  RES3 = 0;
  RES2 = 0;
//------32-bit Result of a multiply operation (not shown) in RES0 and RES1------
  RES1 = 0x7FFF;                            // Pre-load result registers
  RES0 = 0xFFFD;

  MACS = 0x05;                              // Add 5 to previous result
  OP2 = 0x01;

  Result_upper16 = RESHI;                   // Result_upper15 = 0x7FFF
  Result_lower16 = RESLO;                   // Result_lower15 = 0xFFFF

  MPY32CTL0 &= ~MPYSAT;                     // Clear saturation mode

  __bis_SR_register(LPM4_bits);             // LPM4
  __no_operation();                         // For debugger  
}
