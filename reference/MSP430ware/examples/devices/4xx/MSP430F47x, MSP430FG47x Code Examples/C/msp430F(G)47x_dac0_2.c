//*******************************************************************************
//  MSP430F(G)47x Demo - DAC12_1, Output 0.6V on DAC1
//
//  Description: Using DAC12_1 and 1.2V ADC12REF reference with a gain of 1,
//  output 0.6V on DAC1. Output accuracy is specified by that of the SD16REF.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F(G)47x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |        P1.4/DAC1|--> 0.6V
//           |                 |
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//******************************************************************************
#include "msp430xG47x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 			// Stop watchdog timer
  SD16CTL = SD16REFON;				              	    // Internal 1.2V ref on
  DAC12_1CTL = DAC12IR + DAC12SREF_3 + DAC12AMP_5 + 	// SD16 Ref, 
  			   DAC12OPS + DAC12ENC + DAC12CALON; 
  DAC12_1DAT = 0x7FF;                      				// 0.6V
	
  __bis_SR_register(LPM4_bits);                       	// Enter LPM4
}
