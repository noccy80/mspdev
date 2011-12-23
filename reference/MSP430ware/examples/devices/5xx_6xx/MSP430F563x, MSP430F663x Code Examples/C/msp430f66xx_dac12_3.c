//******************************************************************************
//  MSP430F66x Demo - DAC12_0, Output Voltage Ramp on DAC0
//
//  Description: Using DAC12_0 and AVcc reference with a gain of 1,
//  output positive ramp on DAC0. Normal mode is LPM0 with CPU off.  WDT used
//  to provide ~61us interrupt used to wake up the CPU and update the DAC
//  with software. 
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F66x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |        P6.6/DAC0|--> Ramp_positive
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
  WDTCTL = WDT_MDLY_0_064;                  // WDT ~61us interval timer
  SFRIE1 = WDTIE;                           // Enable WDT interrupt

  DAC12_0CTL0 = DAC12IR + DAC12SREF_0 + DAC12AMP_5 + DAC12ENC + DAC12CALON; 

  for (;;)
  {
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0
    DAC12_0DAT++;                           // Positive ramp
    DAC12_0DAT &= 0xFFF;                    // Modulo 4096
  }
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer (void)
{
   __bic_SR_register_on_exit(CPUOFF);       // Clear LPM0 bits from 0(SR)
}
