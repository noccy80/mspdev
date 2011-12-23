//*****************************************************************************
//   MSP430x42x0 Demo - DAC0 1V output with AVcc (3V) ref
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

  DAC12_0CTL = DAC12OPS + DAC12SREF_1 + DAC12IR + DAC12AMP_5 + DAC12ENC;
                                            // DAC o/p external, Ref Voltage = AVcc,
                                            // O/p Voltage range = 1x ref, Enable conversion 1
  DAC12_0DAT = 0x555;                       // 1V

  _BIS_SR(LPM4_bits);                       // Enter LPM4

} // main
