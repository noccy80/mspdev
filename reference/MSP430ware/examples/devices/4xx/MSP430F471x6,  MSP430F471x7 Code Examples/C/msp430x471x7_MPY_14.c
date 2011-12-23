//******************************************************************************
//    MSP430x471xx Demo - Saturation mode underflow test
//
//   Description: The example illustrates a special case showing underflow.
//   Underflow occurs when adding 2 negative numbers to yield a positive result. 
//   By having the saturation mode enabled, the result if rounded off to the 
//   highest negative number (0x8000.0000 for 16 bit). Results can be viewed
//   in the debugger window.
//   
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                  MSP430x471xx
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
  
  MPY32CTL0 = MPYSAT+MPYC;                  // Saturation mode enable,
                                            // Carry bit set
  RES3 = 0;
  RES2 = 0;
  RES1 = 0x0000;                            // Pre-load first negative value
  RES0 = 0x8000;
 
  MACS = 0x8000;                            // Add to second negative value
  OP2 = 0x05;                            
  
  Result_upper16_sat = RESHI;               // Saturated Result_upper15 = 0x8000
  Result_lower16_sat = RESLO;               // Saturated Result_lower15 = 0x0000
  
  MPY32CTL0 &= ~MPYSAT;                     // Clear saturation mode
  
  Result_upper16_unsat = RESHI;             // Unsaturated Result_upper15 = 0x8000
  Result_lower16_unsat = RESLO;             // UnsaturatedResult_lower15 = 0x0000
  
  _BIS_SR(LPM4_bits);                       // LPM4
}
