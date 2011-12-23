//******************************************************************************
//  MSP430G2x31 Demo - ADC10, Sample A11, Lo_Batt, Set P1.0 if < 2.3V
//
//  Description: A single sample is made on A11 (AVcc/2) with reference to
//  internal 1.5V Vref. Software sets ADC10SC to start sample and conversion
//  - ADC10SC automatically cleared at EOC. ADC10 internal oscillator times
//  sample (16x) and conversion. ADC10BUSY flag is polled for EOC. If A11
//  (AVcc/2) < 0311h (0.65V) indicating AVcc is less 2.3V, P1.0 set indicating
//  a lo_Batt condition, else reset.
//
//                MSP430G2x31
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A11          P1.0|-->LED
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
  ADC10CTL1 = INCH_11;                      // AVcc/2
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON;
  P1DIR |= 0x01;                            // Set P1.0 to output direction

  for (;;)
  {
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    while (ADC10CTL1 & ADC10BUSY);          // ADC10BUSY?
    if (ADC10MEM < 0x311)                   // ADC10MEM = A11 > 0.65?
      P1OUT |= 0x01;                        // Set P1.0 LED on
    else
      P1OUT &= ~0x01;                       // Clear P1.0 LED off
  }
}
