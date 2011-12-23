//******************************************************************************
//  MSP-FET430P430 Demo - DAC12_1, Output 2V on DAC1
//
//  Description: Using DAC12_1 and 2.5V ADC12REF reference with a gain of 1,
//  output 2V on DAC1. Output accuracy is specified by that of the ADC12REF.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430FG439
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |        P6.7/DAC1|--> 2V
//           |                 |
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************
#include  <msp430xG43x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  ADC12CTL0 = REF2_5V + REFON;              // Internal 2.5V ref on
  DAC12_1CTL = DAC12IR + DAC12AMP_5 + DAC12ENC; // Internal ref gain 1
  DAC12_1DAT = 0x0CCC;                      // 2V

  _BIS_SR(LPM4_bits);                       // Enter LPM4
}
