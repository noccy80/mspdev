//******************************************************************************
//   MSP430x47xx Demo - Saturation mode overflow test
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
//                MSP430x47xx
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |                 |
//
//  P. Thanigai / K.Venkat
//  Texas Instruments Inc.
//  November 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x47x4.h>
unsigned int Result_lower16;
unsigned int Result_upper16;

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
  
  Result_upper16 = RESHI;                   // Result_upper15 = 0x7FFF
  Result_lower16 = RESLO;                   // Result_lower15 = 0xFFFF
  
  MPY32CTL0 &= ~MPYSAT;                     // Clear saturation mode
  _BIS_SR(LPM4_bits);                       // LPM4
}
