//******************************************************************************
//  MSP430F(G)47x Demo - DAC12_0, Output Voltage Ramp on DAC0
//
//  Description: Using DAC12_0 and 1.2V SD16REF reference with a gain of 1,
//  output positive ramp on DAC0. Normal mode is LPM0 with CPU off.  WDT used
//  to provide ~61us interrupt used to wake up the CPU and update the DAC
//  with software. 
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//               MSP430F(G)47x
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |        P1.6/DAC0|--> Ramp_positive
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
  WDTCTL = WDT_MDLY_0_064;                  // WDT ~61us interval timer
  IE1 = WDTIE;                              // Enable WDT interrupt
  SD16CTL |= SD16REFON;  		            // Internal 1.2V ref on
  DAC12_0CTL = DAC12IR + DAC12SREF_3 + DAC12AMP_5 +  // SD16 Ref, 
  			   DAC12OPS + DAC12ENC + DAC12CALON; 
  _EINT();                                  // Enable interrupts

  for (;;)
  {
    __bis_SR_register(CPUOFF);              // Enter LPM0
    DAC12_0DAT++;                           // Positive ramp
    DAC12_0DAT &= 0xFFF;                    // Modulo 4096
  }
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer (void)
{
    _BIC_SR_IRQ(CPUOFF);                    // Clear LPM0 bits from 0(SR)
}
