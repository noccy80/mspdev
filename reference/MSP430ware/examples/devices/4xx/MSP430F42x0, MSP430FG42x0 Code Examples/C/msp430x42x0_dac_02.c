//*****************************************************************************
//   MSP430x42x0 Demo - DAC0 1V output with 3x reference
//
//  Description: Output 1V on DAC0
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F4270
//             -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |        DAC0/P1.4|--> 1V
//           |                 |
//
//  L. Westlund / S. Karthikeyan
//  Texas Instruments Inc.
//  June 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//*****************************************************************************
#include  <msp430x42x0.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  SD16CTL = SD16REFON;                      // 1.2V ref
  DAC12_0CTL = DAC12OPS + DAC12SREF_2 + DAC12AMP_5 + DAC12ENC;
                                           // DAC o/p external, Ref Voltage = internal (SD16),
                                           // Enable conversion
  DAC12_0DAT = 0x471;                      // 1V

  _BIS_SR(LPM4_bits);                       // Enter LPM4

} // main
