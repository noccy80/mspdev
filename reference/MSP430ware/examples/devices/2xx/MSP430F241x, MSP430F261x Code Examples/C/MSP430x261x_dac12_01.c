//******************************************************************************
//   MSP430x26x Demo - DAC12_0, Output 1.0V on DAC0
//
//   Description: Using DAC12_0 and 2.5V ADC12REF reference with a gain of 1,
//   output 1V on P6.6.
//
//
//                MSP430x261x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |        DAC0/P6.6|--> 1V
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
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC12CTL0 = REF2_5V + REFON;              // Internal 2.5V ref on
  TACCR0 = 13600;                           // DELAY to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TACLR + MC_1 + TASSEL_2;          // up mode, SMCLK
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  TACCTL0 &= ~CCIE;                         // Disable timer interrupt
  __disable_interrupt();                    // Disable Interrupts
  DAC12_0CTL = DAC12IR + DAC12AMP_5 + DAC12ENC; // Int ref gain 1
  DAC12_0DAT = 0x0666;                      // 1.0V (2.5V = 0x0FFFh)
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0
}

//DELAY to allow Ref to settle
#pragma vector = TIMERA0_VECTOR
__interrupt void TA0_ISR(void)
{
  TACTL = 0;                                // Clear Timer_A control registers
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPMx, interrupts enabled
}



