//******************************************************************************
//    MSP430x47xx Demo - Fractional mode, Q15 multiplication
//
//   Description: The example illustrates multiplication of 2 Q15 numbers in
//   fractional mode. The result is a Q15 (15 bit) number stored in the RES1
//   register. It can be viewed in the debugger window. 
//   
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
unsigned int Result_Q15;

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  
  MPY32CTL0 = MPYFRAC;                      // Set fractional mode
 
  MPYS = 0x7D70;                            // Load first operand
  OP2 = 0x1000;                             // Load second operand
  
  Result_Q15 = RESHI;                       // Q15 result
  
  MPY32CTL0 &= ~MPYFRAC;
  _BIS_SR(LPM4_bits);                       // LPM4
}
