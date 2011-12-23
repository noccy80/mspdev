//******************************************************************************
//  MSP430F41x2 Demo - ADC10, DTC Sample A1-0 32x, AVcc, Repeat Seq, DCO
//
//  Description: Use DTC to sample A1/A0 repeat sequence 32x(64 total samples)
//  with reference to AVcc.  Software sets ADC10SC to trigger sample burst.
//  In Mainloop MSP430 waits in LPM0 to save power until ADC10 conversion
//  complete, ADC10_ISR will force exit from LPM0 in Mainloop on reti.
//  ADC10 internal oscillator times sample period (16x) and conversion (13x).
//  DTC transfers conversion code to RAM 200h - 280h.  ADC10(DTC) interrupt
//  will return system active. P5.1 set at start of conversion burst, reset
//  on completion.
//
//               MSP430F41x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//       >---|P7.5/A1      P5.1|-->LED
//       >---|P7.4/A0          |
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
  ADC10CTL1 = INCH_1 + CONSEQ_3;            // A1/A0, repeat multi channel
  ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE;
  ADC10AE0 = 0x03;                          // P7.4,5 ADC option select
  ADC10DTC1 = 0x40;                         // 64 conversions
  P5DIR |= 0x02;                            // Set P5.1 output

  for (;;)
  {
    P5OUT |= 0x02;                          // Set P5.1 LED on
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x200;                        // Data buffer start
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion ready
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    P5OUT &= ~0x02;                         // Clear P5.1 LED off
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}
