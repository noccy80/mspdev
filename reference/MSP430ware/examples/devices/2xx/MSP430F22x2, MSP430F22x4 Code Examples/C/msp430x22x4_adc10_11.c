//******************************************************************************
//  MSP430F22x4 Demo - ADC10, Sample A0, 1.5V, TA1 Trig, Set P1.0 if > 0.5V
//
//  Description: A0 is sampled 16/second (ACLK/2048) with reference to 1.5V.
//  Timer_A is run in upmode and TA1 is used to automatically trigger
//  ADC10 conversion, TA0 defines the period. Internal oscillator times sample
//  (16x) and conversion (13x). Inside ADC10_ISR if A0 > 0.5Vcc, P1.0 is set,
//  else reset. Normal mode is LPM3.
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//       >---|P2.0/A0     P1.0 |--> LED
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  October 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = SHS_1 + CONSEQ_2;             // TA1 trigger sample start
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON + ADC10IE;
  TACCR0 = 30;                              // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt
  TACTL = TASSEL_2 + MC_1;                  // TACLK = SMCLK, Up mode
  __bis_SR_register(CPUOFF + GIE);          // LPM0, TA0_ISR will force exit
  TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
  ADC10CTL0 |= ENC;                         // ADC10 Enable
  ADC10AE0 |= 0x01;                         // P2.0 ADC10 option select
  P1DIR |= 0x01;                            // Set P1.0 output
  TACCR0 = 2048-1;                          // PWM Period
  TACCTL1 = OUTMOD_3;                       // TACCR1 set/reset
  TACCR1 = 2047;                            // TACCR1 PWM Duty Cycle
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up mode

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  if (ADC10MEM < 0x155)                     // ADC10MEM = A0 > 0.5V?
    P1OUT &= ~0x01;                         // Clear P1.0 LED off
  else
    P1OUT |= 0x01;                          // Set P1.0 LED on
}

#pragma vector=TIMERA0_VECTOR
__interrupt void TA0_ISR(void)
{
  TACTL = 0;                                // Clear Timer_A control registers
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
