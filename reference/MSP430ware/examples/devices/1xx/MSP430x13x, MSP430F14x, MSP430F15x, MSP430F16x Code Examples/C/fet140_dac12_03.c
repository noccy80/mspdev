//******************************************************************************
//  MSP-FET430P140 Demo - DAC12_0, Output Voltage Ramp on DAC0
//
//  Description: Using DAC12.0 and 2.5V ADC12REF reference with a gain of 1,
//  output positive ramp on P6.6. Normal mode is LPM0 with CPU off.  WDT used
//  to provide ~0.064ms interrupt used to wake up the CPU and update the DAC
//  with software. Use internal 2.5V Vref.
//  ACLK= n/a, SMCLK= MCLK= WDTCLK= default DCO ~ 800kHz.
//  //* MSP430F169 Device Required *//
//
//               MSP430F169
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |        DAC0/P6.6|--> Ramp_positive
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
  WDTCTL = WDT_MDLY_0_064;                  // WDT ~0.064ms interval timer
  IE1 = WDTIE;                              // Enable WDT interrupt
  ADC12CTL0 = REF2_5V + REFON;              // Internal 2.5V ref on
  DAC12_0CTL = DAC12IR + DAC12AMP_5 +DAC12ENC;  // Internal ref gain 1

  for (;;)
  {
    _BIS_SR(CPUOFF + GIE);                  // Enter LPM0, Enable interrupts
    DAC12_0DAT++;                           // Positive ramp
    DAC12_0DAT &= 0xFFF;                    //
  }
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer (void)
{
    _BIC_SR_IRQ(CPUOFF);                    // Clear LPM0 bits from 0(SR)
}
