//******************************************************************************
//  MSP430FR57xx Demo - ADC10, Sample A1, 1.5V Ref, TA0.1 Trig, Set P1.0 if A1>0.5V
//
//  Description: A1 is sampled 16/second (ACLK/1024) with reference to 1.5V.
//  Timer_A is run in upmode and TA0.1 is used to automatically trigger
//  ADC10 conversion. Internal oscillator times sample (16x) and conversion 
//  (13x).Inside ADC10_ISR if A1 > 0.5V, P1.0 is set, else reset. Normal mode 
//  is LPM3.
//  //* An external watch crystal on XIN XOUT is required for ACLK *//
//
//               MSP430FR5739
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//       >---|P1.1/A1     P1.0 |--> LED
//           |                 |
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with IAR Embedded Workbench Version: 5.10 & Code Composer Studio V4.0
//******************************************************************************

#include "msp430fr5739.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P1DIR |= BIT0;                            // Set P1.0 to output direction
  P1OUT &= ~BIT0;                           // Clear P1.0
  
  // XT1 Setup   
  PJSEL0 |= BIT4 + BIT5; 
 
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;             // Set max. DCO setting
  CSCTL2 = SELA_0 + SELS_3 + SELM_3;        // set ACLK = XT1; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_3 + DIVM_3;        // set all dividers 
  CSCTL4 |= XT1DRIVE_0; 
  CSCTL4 &= ~XT1OFF;
  
  do
  {
    CSCTL5 &= ~XT1OFFG;
                                            // Clear XT1 fault flag
    SFRIFG1 &= ~OFIFG; 
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  // Configure ADC pins
  P1SEL1 |= BIT1; 
  P1SEL0 |= BIT1;   

  // Configure ADC10 
  ADC10CTL0 |= ADC10ON + ADC10MSC;          // ADC10ON
  ADC10CTL1 |= ADC10SHS_1 + ADC10CONSEQ_2;  // rpt single ch; TA0.1 trig sample start
  ADC10CTL2 |= ADC10RES;                    // 10-bit conversion results
  ADC10MCTL0 |= ADC10INCH_1 + ADC10SREF_1;  // A0 ADC input select; Vref=1.5V

  // By default, REFMSTR=1 => REFCTL is used to configure the internal reference
  while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT                                          
  REFCTL0 |= REFVSEL_0+REFON;               // Select internal ref = 1.5V 
                                            // Internal Reference ON   
  __delay_cycles(400);                      // ref delay  
  ADC10CTL0 |= ADC10ENC;                     // ADC10 Enable
  ADC10IE |= ADC10IE0;                       // Enable ADC conv complete interrupt
  
  // ADC conversion trigger signal - TimerA0.0 (32ms ON-period)
  TA0CCR0 = 1024-1;                          // PWM Period
  TA0CCR1 = 512-1;                           // TA0.1 ADC trigger
  TA0CCTL1 = OUTMOD_4;                       // TA0CCR0 toggle
  TA0CTL = TASSEL_1 + MC_1 + TACLR;          // ACLK, up mode

  __bis_SR_register(LPM3_bits + GIE);        // Enter LPM3 w/ interrupts
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
    case 12: if (ADC10MEM0 < 0x155)          // ADC10MEM = A0 < 0.5V?
                P1OUT &= ~BIT0;              // Clear P1.0 LED off
             else
                P1OUT |= BIT0;               // Set P1.0 LED on                                           
             break;                          // Clear CPUOFF bit from 0(SR)                         
    default: break; 
  }   
}


