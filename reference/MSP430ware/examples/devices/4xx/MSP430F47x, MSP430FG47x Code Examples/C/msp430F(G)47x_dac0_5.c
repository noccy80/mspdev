//******************************************************************************
//  MSP430F(G)47x Demo - DAC12_0, Output Voltage Ramp on DAC0, DAC1 Constant, DAC ISR
//
//  Description: Using DAC12.0 outputs a 16 Step Ramp with 1 sample/sec
//  using Timer_B2 trigger. Ramp is output on P1.6. Normal mode is LPM3.
//  DAC1 outputs a constant ~1.2V on P1.4.
//  Use internal 2.5V Vref.   
//
//               MSP430F(G)47x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |        DAC0/P1.4|--> Ramp_positive
//           |        DAC1/P1.6|--> 1.2V
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//******************************************************************************

#include "msp430xG47x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  TBCCTL2 = OUTMOD_7;                       // Reset/set
  TBCCR2 = 16384;                           // PWM Duty Cycle
  TBCCR0 = 32767;                           // 1Hz Clock period
  TBCTL = TBSSEL_1 + MC_1;                  // ACLK, up mode
  SD16CTL |= SD16REFON;			            // Internal 1.2V ref on
  DAC12_1CTL = DAC12IR + DAC12SREF_3 + DAC12AMP_5  // SD16 Ref, 1.2V
  			   + DAC12OPS + DAC12ENC + DAC12CALON; 
  DAC12_1DAT = 0x0FFF;                      // ~1.2V
  DAC12_0CTL = DAC12IR + DAC12SREF_3 + DAC12AMP_5 
  				+ DAC12ENC + DAC12LSEL_3 + DAC12IE + DAC12OPS; // SD16 Ref, 1.2V                                           
  _EINT();                                  // Enable interrupts
  DAC12_0DAT++;                             // Positive ramp

  LPM3;                                     // Enter LPM3
}


#pragma vector=DAC12_DMA_VECTOR
__interrupt void DACDMA_ISR (void)
{
  DAC12_0CTL &= ~DAC12IFG;                  // Clear DAC12 interrupt flag
  DAC12_0DAT = DAC12_0DAT+256;              // Positive ramp
  DAC12_0DAT &= 0xFFF;                      //
}
