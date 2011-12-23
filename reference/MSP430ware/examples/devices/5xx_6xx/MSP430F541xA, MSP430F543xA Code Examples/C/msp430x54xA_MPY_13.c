//******************************************************************************
//   MSP430F543xA Demo - Saturation mode overflow test
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
//                MSP430F5438A
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//   D. Dang
//   Texas Instruments Inc.
//   December 2009
//   Built with CCS Version: 4.0.2 and IAR Embedded Workbench Version: 4.21.8
//******************************************************************************

#include <msp430x54xA.h>

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
  _nop();                                   // Wait for the result to become ready
  _nop();
  _nop();
  _nop();
  _nop();

  Result_upper16 = RESHI;                   // Result_upper15 = 0x7FFF
  Result_lower16 = RESLO;                   // Result_lower15 = 0xFFFF

  MPY32CTL0 &= ~MPYSAT;                     // Clear saturation mode

  __bis_SR_register(LPM4_bits);             // LPM4
  __no_operation();                         // For debugger  
}
