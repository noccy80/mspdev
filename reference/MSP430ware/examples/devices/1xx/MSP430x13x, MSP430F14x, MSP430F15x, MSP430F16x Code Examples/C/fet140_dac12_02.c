//******************************************************************************
//  MSP-FET430P140 Demo - DAC12_1, Output 2.0V on DAC1
//
//  Description: Using DAC12.1 and 2.5V ADC12REF reference with a gain of 1,
//  output 2V on P6.7. Output accuracy is specified by that of the ADC12REF.
//  //* MSP430F169 Device Required *//
//
//               MSP430F169
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |        DAC1/P6.7|--> 2V
//           |                 |
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x16x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  ADC12CTL0 = REF2_5V + REFON;              // Internal 2.5V ref on
  DAC12_1CTL = DAC12IR + DAC12AMP_5 + DAC12ENC;// Internal ref gain 1
  DAC12_1DAT = 0x0CCC;                      // 2V

  _BIS_SR(LPM4_bits);                       // Enter LPM4
}
