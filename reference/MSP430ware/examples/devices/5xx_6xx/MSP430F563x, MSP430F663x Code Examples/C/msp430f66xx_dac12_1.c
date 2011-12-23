//*******************************************************************************
//  MSP430F66x Demo - DAC12_0, Output 1.5V on DAC0
//
//  Description: Using DAC12_0 and AVcc reference with a gain of 1,
//  output 1.5V on DAC0. 
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F66x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |        P6.6/DAC0|--> 1.5V
//           |                 |
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   Nov 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************
#include <msp430f6638.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  
  // AVcc is used as reference, calibration on, DAC on
  DAC12_0CTL0 = DAC12IR + DAC12SREF_1 + DAC12AMP_5 + DAC12CALON; 
  DAC12_0CTL0 |= DAC12ENC;                  // Enable DAC12
  DAC12_0DAT = 0x7FF;                       // ~1.5V
	
  __bis_SR_register(LPM4_bits);             // Enter LPM4
}
