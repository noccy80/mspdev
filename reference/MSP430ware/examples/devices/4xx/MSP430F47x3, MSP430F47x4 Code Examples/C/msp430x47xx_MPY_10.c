//******************************************************************************
//    MSP430x47xx Demo - 32x32 Signed Multiply
//
//   Description: Hardware multiplier is used to multiply two numbers.
//   The calculation is automatically initiated after the second operand is
//   loaded. Results are stored in RES0, RES1, RES2 and RES3.
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
  MPYS32L = 0x1234;                         // Load lower 16 bits of operand 1
  MPYS32H = 0x1234;                         // Load upper 16 bits of operand 1
  
  OP2L = 0x5678;                            // Load lower 16 bits of operand 2
  OP2H = 0x5678;                            // Load upper 16 bits of operand 2
  _BIS_SR(LPM4_bits);                       // LPM4
}
