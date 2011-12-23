//******************************************************************************
//  MSP430F530x Demo - ADC10, Sample A10 Temp, TA0.1 Trigger, Set P1.0 if Temp++ ~2C
//
//  Description: Set ADC10 and the integrated temperature sensor to detect
//  temperature gradients. The temperature sensor output voltage is sampled
//  ~ every 62ms and then compared with the defined delta values using an ISR.
//  (ADC10OSC)/32 determines sample time which needs to be greater than
//  ~1us for temperature sensor.
//  ADC10 is operated in repeat-single channel mode with the sample and
//  convert trigger sourced from Timer_A CCR1. The ADC10IFG at the end
//  of each converstion will trigger an ISR.
//  ACLK = REFO, MCLK = SMCLK = default DCO ~1.2MHz, ADC10CLK = ADC10OSC
//
//                MSP430F530x
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A10 (Temp)   P1.0|-->LED
//            |             P1.2|-->TA0.1 (ADC trigger signal)
//
//
//   B. Nisarga
//   Texas Instruments Inc.
//   Dec 2010
//   Built with CCSv4.2 and IAR Embedded Workbench Version: 4.21
//******************************************************************************
#include <msp430f5310.h>

static unsigned int FirstADCVal;            // holds 1st ADC result

#define ADCDeltaOn       6                  // ~ 2 Deg C delta for LED on

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog

  // Configure ADC10 - Pulse Sample Mode, TimerA0.0 Trigger
  ADC10CTL0 = ADC10SHT_3 + ADC10ON;         // 32 ADC10CLKs; ADC ON
  ADC10CTL1 = ADC10SHP + ADC10SHS_1 + ADC10CONSEQ_2; // TA0.1 trig., rpt single ch 
  ADC10CTL2 |= ADC10RES;                    // 10-bit conversion results
  ADC10MCTL0 = ADC10SREF_1 + ADC10INCH_10 ; // A10, internal Vref+
  
  // Configure internal reference
  while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT                                          
  REFCTL0 |= REFVSEL_2+REFON;               // Select internal ref = 2.5V 
                                            // Internal Reference ON   
  // Configure TA0 to provide delay for reference settling ~75us
  TA0CCR0 = 80;                             // Delay to allow Ref to settle
  TA0CCTL0 |= CCIE;                         // Compare-mode interrupt.
  TA0CTL = TASSEL_2 + MC_1;                 // TACLK = SMCLK, Up mode.
  __bis_SR_register(CPUOFF + GIE);          // LPM0, TA0_ISR will force exit
  TA0CCTL0 &= ~CCIE;                        // Disable timer Interrupt
  
  ADC10IE |= ADC10IE0;                      // Enable ADC conv complete interrupt  
  ADC10CTL0 |= ADC10ENC;
  
  // Configure TimerA0.0 as ADC conversion tirgger (period ~ 62ms)
  TA0CCR0 = 1024-1;                          // PWM Period
  TA0CCR1 = 512-1;                           // TA0.1 PWM
  TA0CCTL1 = OUTMOD_4;                       // TA0CCR0 toggle
  TA0CTL = TASSEL_1 + MC_1 + TACLR;          // ACLK, up mode
  
  P1DIR |= BIT2;                             // P1.2/TA0.1 output
  P1SEL |= BIT2;                             // Output TA0.1 ADC trigger signal
  
  while (ADC10CTL1 & ADC10BUSY);             // First conversion?
  FirstADCVal = ADC10MEM0;                   // Read out 1st ADC value
  P1OUT = 0x00;                              // Clear P1
  P1DIR = BIT0;                              // P1.0 as output
  __bis_SR_register(LPM3_bits + GIE);        // Enter LPM3 w/ interrupt
  __no_operation();                          // For debugger
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  switch(__even_in_range(ADC10IV,12))
  {
    case  0: break;                          // No interrupt
    case  2: break;                          // conversion result overflow
    case  4: break;                          // conversion time overflow
    case  6: break;                          // ADC10HI
    case  8: break;                          // ADC10LO
    case 10: break;                          // ADC10IN
    case 12: if (ADC10MEM0 >= FirstADCVal + ADCDeltaOn)          
                P1OUT |= 0x01;               // Set P1.0 LED on
             else
                P1OUT &= ~0x01;              // Clear P1.0 LED off                                             
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

