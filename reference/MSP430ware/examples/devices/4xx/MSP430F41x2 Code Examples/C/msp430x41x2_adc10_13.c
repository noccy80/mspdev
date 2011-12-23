//******************************************************************************
//  MSP430F41x2 Demo - ADC10, DTC Sample A1 32x, AVcc, TA1 Trig, DCO
//
//  Description; A1 is sampled in 32x burst using DTC 16 times per second
//  (ACLK/2048) with reference to AVcc. Activity is interrupt driven.
//  Timer_A in upmode uses TA1 toggle to drive ADC10 conversion. Sample burst
//  is automatically triggered by TA1.OUT0 rising edge every 2048 ACLK cycles.
//  ADC10_ISR will exit from LPM3 mode and return CPU active. Internal ADC10OSC
//  times sample (16x) and conversion (13x). DTC transfers conversion code to
//  RAM 200h - 240h. In the Mainloop P5.1 is toggled. Normal Mode is LPM3.
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//               MSP430F41x2
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//       >---|P7.5/A1     P5.1 |--> LED
//
//  P. Thanigai
//  Texas Instruments Inc.
//  January 2009
//  Built with CCE Version: 3.1 and IAR Embedded Workbench Version: 4.11
//******************************************************************************
#include "msp430x41x2.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = INCH_1 + SHS_2 + CONSEQ_2;    // TA1 trigger
  ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE;
  ADC10DTC1 = 0x20;                         // 32 conversions
  P5DIR |= 0x02;                            // Set P5.1 output
  ADC10AE0 |= 0x02;                         // P7.5 ADC10 option select
  TA1CCR0 = 1024-1;                         // PWM Period
  TA1CCTL0 = OUTMOD_4;                      // TA1CCR0 toggle
  TA1CTL = TASSEL_1 + MC_1;                 // ACLK, up mode

  for (;;)
  {
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x200;                        // Data buffer start
    ADC10CTL0 |= ENC;                       // Sampling and conversion ready
    __bis_SR_register(LPM3_bits + GIE);     // Enter LPM3, enable interrupts
    P5OUT ^= 0x02;                          // Toggle P1.0 using exclusive-OR
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(LPM3_bits);     // Clear LPM3 bits from 0(SR)
}

