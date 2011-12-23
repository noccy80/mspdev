//******************************************************************************
//  MSP430FR57xx Demo - ADC10, Sample A1, 1.5V Shared Ref, Set P1.0 if A1 > 0.5V
//
//  Description: A single sample is made on A1 with reference to internal
//  1.5V Vref. Software sets ADC10SC to start sample and conversion - ADC10SC
//  automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
//  and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
//  conversion complete, ADC10_ISR will force exit from LPM0 in Mainloop on
//  reti. If A1 > 0.5V, P1.0 set, else reset.
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
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT0;                            // P1.0 output
  // Configure ADC pins
  P1SEL1 |= BIT1; 
  P1SEL0 |= BIT1;   

  // By default, REFMSTR=1 => REFCTL is used to configure the internal reference
  while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT                                          
  REFCTL0 |= REFVSEL_0+REFON;               // Select internal ref = 1.5V 
                                            // Internal Reference ON  

  ADC10CTL0 = ADC10SHT_2 + ADC10ON;
  ADC10CTL1 |= ADC10SHP;                    // ADCCLK = MODOSC; sampling timer
  ADC10CTL2 |= ADC10RES;                    // 10-bit conversion results  
  ADC10IE |= ADC10IE0;                      // Enable ADC conv complete interrupt
  ADC10MCTL0 |= ADC10INCH_1 + ADC10SREF_1;  // A0 ADC input select; Vref=1.5V
  
  // Configure TA0 to provide delay for reference settling ~75us
  TA0CCR0 = 80;                              // Delay to allow Ref to settle
  TA0CCTL0 |= CCIE;                          // Compare-mode interrupt.
  TA0CTL = TASSEL_2 + MC_1;                  // TACLK = SMCLK, Up mode.
  __bis_SR_register(CPUOFF + GIE);           // LPM0, TA0_ISR will force exit
  TA0CCTL0 &= ~CCIE;                         // Disable timer Interrupt

  for (;;)
  {
    __delay_cycles(5000);                    // Delay between conversions  
    ADC10CTL0 |= ADC10ENC + ADC10SC;         // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);         // LPM0, ADC10_ISR will force exit
    __no_operation();                        // For debug only
    if (ADC_Result < 0x155)                  // ADC10MEM = A0 > 0.5V?
      P1OUT &= ~0x01;                        // Clear P1.0 LED off
    else
      P1OUT |= 0x01;                         // Set P1.0 LED on
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

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
  TA0CTL = 0;
  LPM0_EXIT;                                // Exit LPM0 on return
}

