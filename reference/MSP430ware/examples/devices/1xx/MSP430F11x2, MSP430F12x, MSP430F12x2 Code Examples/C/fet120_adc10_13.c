//******************************************************************************
//  MSP-FET430P120 Demo - ADC10, DTC Sample A1 32x, AVcc, TA0 Trig, DCO
//
//  Description; A1 is sampled in 32x burst using DTC 16 times per second
//  (ACLK/2048) with reference to Avcc. Activity is interrupt driven.
//  Timer_A in upmode uses TA0 toggle to drive ADC10 conversion. Sample burst
//  is automatically triggered by TA0 rising edge every 2048 ACLK cycles.
//  ADC10_ISR will exit from LPM3 mode and return CPU active. Internal ADC10OSC
//  times sample (16x) and conversion (13x). DTC transfers conversion code to
//  RAM 200h - 240h. In the Mainloop P1.0 is toggled. Normal Mode is LPM3.
//  //* An external watch crystal on XIN XOUT is required for ACLK *//	
//  //* MSP430F1232 or MSP430F1132 Device Required *//
//
//               MSP430F1232
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//       >---|A1          P1.0 |--> LED
//
//  M. Buccini/A. Dannenberg
//  Texas Instruments Inc.
//  November 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//******************************************************************************

#include  <msp430x12x2.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = INCH_1 + SHS_2 + CONSEQ_2;    // TA0 trigger
  ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE;
  ADC10DTC1 = 0x20;                         // 32 conversions
  P1DIR |= 0x01;                            // Set P1.0 output
  ADC10AE |= 0x02;                          // P2.1 ADC10 option select
  CCR0 = 1024-1;                            // PWM Period
  CCTL0 = OUTMOD_4;                         // CCR0 toggle
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up mode

  for (;;)
  {
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x200;                        // Data buffer start
    ADC10CTL0 |= ENC;                       // Sampling and conversion ready
    _BIS_SR(LPM3_bits + GIE);               // Enter LPM3, enable interrupts
    P1OUT ^= 0x01;                          // Toggle P1.0 using exclusive-OR
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
    _BIC_SR_IRQ(LPM3_bits);                 // Clear LPM3 bits from 0(SR)
}
