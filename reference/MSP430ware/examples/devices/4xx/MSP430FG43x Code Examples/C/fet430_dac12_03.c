//******************************************************************************
//  MSP-FET430P430 Demo - DAC12_0, Output Voltage Ramp on DAC0
//
//  Description: Using DAC12_0 and 2.5V ADC12REF reference with a gain of 1,
//  output positive ramp on DAC0. Normal mode is LPM0 with CPU off.  WDT used
//  to provide ~61us interrupt used to wake up the CPU and update the DAC
//  with software. Uses internal 2.5V Vref.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430FG439
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |        P6.6/DAC0|--> Ramp_positive
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
  WDTCTL = WDT_MDLY_0_064;                  // WDT ~61us interval timer
  IE1 = WDTIE;                              // Enable WDT interrupt
  ADC12CTL0 = REF2_5V + REFON;              // Internal 2.5V ref on
  DAC12_0CTL = DAC12IR + DAC12AMP_5 +DAC12ENC; // Internal ref gain 1
  _EINT();                                  // Enable interrupts

  for (;;)
  {
    _BIS_SR(CPUOFF);                        // Enter LPM0
    DAC12_0DAT++;                           // Positive ramp
    DAC12_0DAT &= 0xFFF;                    // Modulo 4096
  }
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer (void)
{
    _BIC_SR_IRQ(CPUOFF);                    // Clear LPM0 bits from 0(SR)
}
