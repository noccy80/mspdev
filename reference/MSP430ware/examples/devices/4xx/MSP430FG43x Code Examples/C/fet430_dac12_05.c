//******************************************************************************
//  MSP-FET430P430 Demo - DAC0 Output Voltage Ramp, DAC1 Constant, DAC ISR
//
//  Description: Using DAC12.0 outputs a 16 Step Ramp with 1 sample/sec
//  using Timer_B2 trigger. Ramp is output on VeRef+. Normal mode is LPM3.
//  DAC1 outputs a constant 1.5V on P6.7
//  Use internal 2.5V Vref.
//
//               MSP430FG439
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |      DAC0/VeRef+|--> Ramp_positive
//           |        DAC1/P6.7|--> 1.5V
//
//  H. Grewal / L. Westlund
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//******************************************************************************

#include  <msp430xG43x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  TBCCTL2 = OUTMOD_7;                       // Reset/set
  TBCCR2 = 16384;                           // PWM Duty Cycle	
  TBCCR0 = 32767;                           // 1Hz Clock period
  TBCTL = TBSSEL_1 + MC_1;                  // ACLK, up mode
  ADC12CTL0 = REF2_5V + REFON;              // Internal 2.5V ref on
  DAC12_1CTL = DAC12IR + DAC12AMP_5 + DAC12ENC; // Output range, Amp setting
  DAC12_1DAT = 0x099A;                      // 1.5V
  DAC12_0CTL = DAC12IR + DAC12AMP_5 + DAC12ENC + DAC12LSEL_3 + DAC12IE + DAC12OPS;
                                            // Internal ref gain 1
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
