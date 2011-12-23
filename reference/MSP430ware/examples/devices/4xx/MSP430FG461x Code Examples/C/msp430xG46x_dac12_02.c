//******************************************************************************
//   MSP430xG461x Demo - DAC12_1, Output 2.0V on DAC1
//
//   Description: Using DAC12_1 and 2.5V ADC12REF reference with a gain of 1,
//   output 2V on P6.7.
//
//
//                MSP430xG461x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |        DAC1/P6.7|--> 2V
//            |                 |
//
//   A. Dannenberg/ M. Mitchell
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430xG46x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC12CTL0 = REF2_5V + REFON;              // Internal 2.5V ref on
  TACCR0 = 13600;                           // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TACLR + MC_1 + TASSEL_2;          // up mode, SMCLK
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  TACCTL0 &= ~CCIE;                         // Disable timer interrupt
  __disable_interrupt();                    // Disable Interrupts
  DAC12_1CTL = DAC12IR + DAC12AMP_5 + DAC12ENC; // Int ref gain 1
  DAC12_1DAT = 0x0CCC;                      // 2.0V
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0
}

#pragma vector = TIMERA0_VECTOR
__interrupt void TA0_ISR(void)
{
  TACTL = 0;                                // Clear Timer_A control registers
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPMx, interrupts enabled
}
