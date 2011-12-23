//******************************************************************************
//  MSP430F22x4 Demo - ADC10, Sample A7, 1.5V, TA1 Trig, Ultra-Low Pwr
//
//  Description: A7 is sampled 1024/second (32xACLK) with reference to 1.5V.
//  All activity is interrupt driven with proper usage of MSP430 low-power
//  modes, ADC10 and Vref demonstrated. Timer_A with both TA1/TA0 used in
//  upmode to drive ADC10 conversion (continuous mode can also be used).
//  Inside of TA0_ISR software will enable ADC10 and internal reference and
//  allow > 30us delay for Vref to stabilize prior to sample start. Sample
//  start is automatically triggered by TA1 every 32 ACLK cycles. ADC10_ISR
//  will disable ADC10 and Vref and compare ADC10 conversion code. Internal
//  oscillator times sample (16x) and conversion (13x). If A7 > 0.2Vcc,
//  P1.0 is set, else reset. Normal Mode is LPM3.
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//                    +-----(0.9766us)---------\\------------------>+
//    TA0_ISR        TA1      ADC10_ISR             TA0_ISR        TA1
//  -----+------------+------------+-----------\\------+------------+----->
//   Enable ADC    Trigger ADC  Disable ADC
//   and Vref                   Compare
//       +-( >30us--->+
//
//
//               MSP430F22x4
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//       >---|P3.7/A7     P1.0 |--> LED
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
  P1DIR = 0xFF;                             // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2DIR = 0xFF;                             // All P2.x outputs
  P2OUT = 0;                                // All P2.x reset
  P3DIR = 0xFF;                             // All P3.x outputs
  P3OUT = 0;                                // All P3.x reset
  P4DIR = 0xFF;                             // All P4.x outputs
  P4OUT = 0;                                // All P4.x reset
  ADC10CTL1 = INCH_7 + SHS_1;               // P3.7, TA1 trigger sample start
  ADC10AE0 = 0x80;                          // P3.7 ADC10 option select
  TACCTL0 = CCIE;                           // Enable interrupt
  TACCR0 = 32-1;                            // PWM Period
  TACCTL1 = OUTMOD_3;                       // TACCR1 set/reset
  TACCR1 = 2;                               // TACCR1 PWM Duty Cycle
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up mode
  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, enable interrupts
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  ADC10CTL0 &= ~ENC;                        // ADC10 disabled
  ADC10CTL0 = 0;                            // ADC10, Vref disabled completely
  if (ADC10MEM < 0x88)                      // ADC10MEM = A7 > 0.2V?
    P1OUT &= ~0x01;                         // Clear P1.0 LED off
  else
    P1OUT |= 0x01;                          // Set P1.0 LED on
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A(void)
{
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON + ADC10IE;
  ADC10CTL0 |= ENC;                         // ADC10 enable set
}
