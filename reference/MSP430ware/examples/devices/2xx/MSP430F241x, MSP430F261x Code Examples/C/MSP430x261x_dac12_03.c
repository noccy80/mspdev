//******************************************************************************
//   MSP430x26x Demo - DAC12_0, Output Voltage Ramp on DAC0
//
//   Description: Using DAC12_0 and 2.5V ADC12REF reference with a gain of 1,
//   output positive ramp on P6.6. Normal mode is LPM0 with CPU off.  WDT used
//   to provide ~0.5ms interrupt used to wake up the CPU and update the DAC
//   with software. Use internal 2.5V Vref.
//   ACLK = 32kHz, SMCLK = MCLK = WDTCLK = default DCO 1048576Hz
//
//
//                MSP430F261x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |        DAC0/P6.6|--> Ramp_positive
//            |                 |
//
//   B. Nisarga
//   Texas Instruments Inc.
//   September 2007
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"

void main(void)
{
  WDTCTL = WDT_MDLY_0_064;                  // WDT ~0.064ms interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt
  ADC12CTL0 = REF2_5V + REFON;              // Internal 2.5V ref on
  TACCR0 = 13600;                           // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TACLR + MC_1 + TASSEL_2;          // up mode, SMCLK
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  TACCTL0 &= ~CCIE;                         // Disable timer interrupt
  __disable_interrupt();                    // Disable Interrupts
  DAC12_0CTL = DAC12IR + DAC12AMP_5 + DAC12ENC; // Int ref gain 1

  while (1)
  {
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0, interrupts enabled
    DAC12_0DAT++;                           // Positive ramp
    DAC12_0DAT &= 0x0FFF;
  }
}

// DELAY ISR
#pragma vector = TIMERA0_VECTOR
__interrupt void TA0_ISR(void)
{
  TACTL = 0;                                // Clear Timer_A control registers
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPMx, interrupts enabled
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
  __bic_SR_register_on_exit(LPM0_bits);      // TOS = clear LPM0
}
