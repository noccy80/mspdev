//******************************************************************************
//  MSP430F51x2 Demo - ADC10, Internal Reference toggle
//
//  Description: Sample and convert analog voltage at ADC i/p ch A1 in single 
//  channel single conversion mode. Internal reference is toggled between
//  1.5V and 2.5V and the ADC measurements are made. With 1V input at A1, Vref+
//  of 1.5V and 2.5V gives ADC conv result of ~682 and ~409 respectively. LED at 
//  P1.0 is turned on when ADC conv result >500 (that is with Vref=1.5V) and 
//  turned off otherwise (when Vref=2.5V)
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz, ADC10CLK = ADC10OSC 
//
//               MSP430F51x2
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |             P1.0|--> LED 
//           |          P1.1/A1|<-- 1V
//
//  B. Nisarga
//  Texas Instruments Inc.
//  Dec 2009
//  Built with CCS v4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include "msp430f5172.h"

// Function Definition
void delay(void);                           // Software delay

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  
  // Configure ADC10 - Pulse sample mode; ADC10SC trigger
  ADC10CTL0 = ADC10SHT_2 + ADC10ON;         // 16 ADC10CLKs; ADC ON
  ADC10CTL1 = ADC10SHP + ADC10CONSEQ_0;     // s/w trig, single ch/conv
  ADC10CTL2 = ADC10RES;                     // 10-bit conversion results
  ADC10MCTL0 = ADC10SREF_1 + ADC10INCH_1;   // A1, Vref+ 
  
 // Configure internal reference
  while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT
  REFCTL0 |= REFVSEL_0+REFON;               // Select internal ref = 1.5V 
                                            // Internal Reference ON   
  __delay_cycles(75);                       // Delay (~75us) for Ref to settle

  P1DIR |= BIT0;                            // Set P1.0 output direction
  P1OUT &= ~BIT0;                           // Clear P1.0

  ADC10CTL0 &= ~ADC10ENC;                   // ADC10 disable  

  while(1)
  {
    ADC10CTL0 |= ADC10ENC + ADC10SC;        // Sample and conversion start
    // Toggle internal reference voltage
    while(REFCTL0 & REFGENBUSY);            // If ref generator busy, WAIT
    REFCTL0 ^= REFVSEL1;                    // Toggle Internal Ref betn 1.5V/2.5V 
    while (!(ADC10IFG & ADC10IFG0));        // Conversion complete?
    if (ADC10MEM0 > 500)                    // ADC10MEM0 = A1 > 500
      P1OUT |= BIT0;                        // Set P1.0; Vref=1.5V used
    else
      P1OUT &= ~BIT0;                       // Clear P1.0; Vref=2.5V used

    delay();                                // Delay between conversions
  }
}

void delay(void)
{
  volatile unsigned long i;
  for (i = 0x7FFF; i > 0; i--);
}
