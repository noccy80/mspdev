//******************************************************************************
//  MSP430G2x31 Demo - ADC10, Sample A1, 1.5V, TA1 Trig, Set P1.0 if > 0.5V
//
//  Description: A1 is sampled 16/second (ACLK/2048) with reference to 1.5V.
//  Timer_A is run in upmode and TA1 is used to automatically trigger
//  ADC10 conversion, TA0 defines the period. Internal oscillator times sample
//  (16x) and conversion (13x). Inside ADC10_ISR if A1 > 0.5Vcc, P1.0 is set,
//  else reset. Normal mode is LPM3.
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//               MSP430G2x31
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//       >---|P1.1/A1     P1.0 |--> LED
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
#include  "msp430g2231.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = SHS_1 + CONSEQ_2 + INCH_1;    // TA1 trigger sample start
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON + ADC10IE;
  __enable_interrupt();                     // Enable interrupts.
  TACCR0 = 30;                              // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TASSEL_2 + MC_1;                  // TACLK = SMCLK, Up mode.
  LPM0;                                     // Wait for delay.
  TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
  __disable_interrupt();
  ADC10CTL0 |= ENC;                         // ADC10 Enable
  ADC10AE0 |= 0x02;                         // P1.1 ADC10 option select
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
  if (ADC10MEM < 0x155)                     // ADC10MEM = A1 > 0.5V?
    P1OUT &= ~0x01;                         // Clear P1.0 LED off
  else
    P1OUT |= 0x01;                          // Set P1.0 LED on
}

#pragma vector=TIMERA0_VECTOR
__interrupt void ta0_isr(void)
{
  TACTL = 0;
  LPM0_EXIT;                                // Exit LPM0 on return
}
