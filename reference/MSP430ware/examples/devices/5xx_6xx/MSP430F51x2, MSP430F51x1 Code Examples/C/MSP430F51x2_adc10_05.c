//******************************************************************************
//  MSP430F51x2 Demo - ADC10, Sample A11, Lo_Batt, Clear P1.0 if AVcc < 2.3V
//
//  Description: A single sample is made on A11 (AVcc/2) with reference to
//  internal 1.5V Vref. Software sets ADC10SC to start sample and conversion
//  - ADC10SC automatically cleared at EOC. ADC10 internal oscillator times
//  sample (16x) and conversion. ADC10BUSY flag is polled for EOC. If A11
//  (AVcc/2) < 0311h (1.15V) indicating AVcc is less 2.3V, P1.0 reset indicating
//  a lo_Batt condition, else set.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz, ADC10CLK = ADC10OSC
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A11 (AVcc/2) P1.0|-->LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  // Configure ADC10 - Pulse sample mode; ADC10SC trigger
  ADC10CTL0 = ADC10SHT_2 + ADC10ON;         // 16 ADC10CLKs; ADC ON
  ADC10CTL1 = ADC10SHP + ADC10CONSEQ_0;     // s/w trig, single ch/conv
  ADC10CTL2 = ADC10RES;                     // 10-bit conversion results
  ADC10MCTL0 = ADC10SREF_1 + ADC10INCH_11;  // AVcc/2  
  
  // Configure internal reference
  while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT
  REFCTL0 |= REFVSEL_0+REFON;               // Select internal ref = 1.5V 
                                            // Internal Reference ON   
  __delay_cycles(75);                       // Delay (~75us) for Ref to settle
  
  P1DIR |= BIT0;                            // Set P1.0 to output direction
  P1OUT &= ~BIT0;                           // Clear P1.0

  while(1)
  {
    ADC10CTL0 |= ADC10ENC + ADC10SC;        // Sampling and conversion start
    while (ADC10CTL1 & ADC10BUSY);          // ADC10BUSY?
    __no_operation();                       // For debug only
    if (ADC10MEM0 < 0x311)                  // is ADC10MEM = A11 > 1.15V?
      P1OUT &= ~BIT0;                       // Clear P1.0 LED off
    else
      P1OUT |= BIT0;                         // Set P1.0 LED on
  }
}

