//******************************************************************************
//  MSP430FR57xx Demo - ADC10, Sample A1, AVcc Ref, Set P1.0 if A1 > 0.5*AVcc
//
//  Description: A single sample is made on A1 with reference to AVcc.
//  Software sets ADC10SC to start sample and conversion - ADC10SC
//  automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
//  and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
//  conversion complete, ADC10_ISR will force exit from LPM0 in Mainloop on
//  reti. If A1 > 0.5*AVcc, P1.0 set, else reset.
//  
//
//                MSP430FR5739
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|P1.1/A1      P1.0|-->LED
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************
#include "msp430fr5739.h"

unsigned int ADC_Result;

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P1DIR |= BIT0;                            // Set P1.0/LED to output direction
  
  // Configure ADC
  P1SEL1 |= BIT1; 
  P1SEL0 |= BIT1; 
  
  ADC10CTL0 |= ADC10SHT_2 + ADC10ON;        // ADC10ON, S&H=16 ADC clks
  ADC10CTL1 |= ADC10SHP;                    // ADCCLK = MODOSC; sampling timer
  ADC10CTL2 |= ADC10RES;                    // 10-bit conversion results
  ADC10MCTL0 |= ADC10INCH_1;                // A1 ADC input select; Vref=AVCC
  ADC10IE |= ADC10IE0;                      // Enable ADC conv complete interrupt
  
  for (;;)
  {
    __delay_cycles(5000);
    ADC10CTL0 |= ADC10ENC + ADC10SC;        // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    __no_operation();                       // For debug only
    if (ADC_Result < 0x1FF)
      P1OUT &= ~BIT0;                       // Clear P1.0 LED off
    else
      P1OUT |= BIT0;                        // Set P1.0 LED on
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  switch(__even_in_range(ADC10IV,12))
  {
    case  0: break;                          // No interrupt
    case  2: break;                          // conversion result overflow
    case  4: break;                          // conversion time overflow
    case  6: break;                          // ADC10HI
    case  8: break;                          // ADC10LO
    case 10: break;                          // ADC10IN
    case 12: ADC_Result = ADC10MEM0;         
             __bic_SR_register_on_exit(CPUOFF);                                              
             break;                          // Clear CPUOFF bit from 0(SR)                         
    default: break; 
  }  
}

