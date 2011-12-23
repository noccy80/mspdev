//******************************************************************************
//  MSP430x47xx Demo - 32x32 Unsigned Multiply Accumalate
//
//  Description: Hardware multiplier is used to multiply-accumalate a set of 
//  numbers. The first calculation is automatically initiated after the second 
//  operand is loaded. A second multiply-accumulate operation is performed next.
//  Results are stored in RES0, RES1, RES2 and RES3.  
//  SUMEXT contains the extended sign of the result.
//
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                  MSP430x47xx
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

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
                                            // unsigned multiply
  MPY32L = 0x1234;                          // Load lower 16 bits of operand 1
  MPY32H = 0x1234;                          // Load upper 16 bits of operand 1
  
  OP2L = 0x5678;                            // Load lower 16 bits of operand 2
  OP2H = 0x5678;                            // Load upper 16 bits of operand 2
                                            // unsigned MAC
  MAC32L = 0x1234;                          // Load lower 16 bits of operand 1
  MAC32H = 0x1234;                          // Load upper 16 bits of operand 1
  
  OP2L = 0x5678;                            // Load lower 16 bits of operand 2
  OP2H = 0x5678;                            // Load upper 16 bits of operand 2 
  
  _BIS_SR(LPM4_bits);                       // LPM4
}
