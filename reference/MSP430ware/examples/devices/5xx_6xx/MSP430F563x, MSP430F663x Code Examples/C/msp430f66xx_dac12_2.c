//*******************************************************************************
//  MSP430F66x Demo - DAC12_1, Output 0.75V on DAC1
//
//  Description: Using DAC12_1 and 1.5V reference with a gain of 1,
//  output 0.75V on DAC1. 
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F66x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |        P6.7/DAC1|--> 0.75V
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
  // Refernce is autmatically turned on from the REF module on DAC request
  // REF module default 1.5V is used
  DAC12_1CTL0 = DAC12IR + DAC12SREF_0 + DAC12AMP_5 + DAC12ENC + DAC12CALON; 
  __delay_cycles(100);                      // Tsettle = 75us
  DAC12_1DAT = 0x7FF;                      			
	
  __bis_SR_register(LPM4_bits);             // Enter LPM4
}
