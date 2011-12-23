//******************************************************************************
//   MSP430x471xx Demo - Saturation mode overflow test
//
//   Description: The example illustrates a special case showing overflow.
//   The addition result of 2 positive numbers may exceed the highest positive 
//   number (0x7FFF FFFF for 32 bit result) due to overflow indicaing a negative
//   result. By having the saturation mode enabled, this result can be truncated 
//   off to this highest positive number. Results with and without saturation mode 
//   are shown. 
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                MSP430x471xx
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>
unsigned int Result_lower16_sat;
unsigned int Result_upper16_sat;
unsigned int Result_lower16_unsat;
unsigned int Result_upper16_unsat;

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  
  MPY32CTL0 = MPYSAT;                       // Enable saturation mode
  
  RES3 = 0;
  RES2 = 0;
//------32-bit Result of a multiply operation (not shown) in RES0 and RES1------
  RES1 = 0x7FFF;                            // Pre-load result registers   
  RES0 = 0xFFFD;
 
  MACS = 0x05;                              // Add 5 to previous result
  OP2 = 0x01;                            
  
  Result_upper16_sat = RESHI;               // Saturated result_upper15 = 0x7FFF
  Result_lower16_sat = RESLO;               // Saturated result_lower15 = 0xFFFF
  
  MPY32CTL0 &= ~MPYSAT;                     // Clear saturation mode to get
                                            // roll over result
  
  Result_upper16_unsat = RESHI;             // Unsaturated result_upper15 = 0x7FFF
  Result_lower16_unsat = RESLO;             // Unsaturated result_lower15 = 0xFFFF

  _BIS_SR(LPM4_bits);                       // LPM4
}
