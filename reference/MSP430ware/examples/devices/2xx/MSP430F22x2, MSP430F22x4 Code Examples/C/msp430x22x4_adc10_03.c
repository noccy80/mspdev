//******************************************************************************
//  MSP430F22x4 Demo - ADC10, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
//
//  Description: Set ADC10 and the integrated temperature sensor to detect
//  temperature gradients. The temperature sensor output voltage is sampled
//  ~ every 120ms and compared with the defined delta values using an ISR.
//  (ADC10OSC/4)/64 determines sample time which needs to be greater than
//  30us for temperature sensor.
//  ADC10 is operated in repeat-single channel mode with the sample and
//  convert trigger sourced from Timer_A CCR1. The ADC10IFG at the end
//  of each converstion will trigger an ISR.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz, ADC10CLK = ADC10OSC
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A10 (Temp)   P1.0|-->LED
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

static unsigned int FirstADCVal;            // holds 1st ADC result

#define ADCDeltaOn       3                  // ~ 2 Deg C delta for LED on

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  ADC10CTL1 = ADC10DIV_3 + INCH_10 + SHS_1 + CONSEQ_2;  // TA trig., rpt, A10
  ADC10CTL0 = SREF_1 + ADC10SHT_3 + REF2_5V + ADC10IE + REFON + ADC10ON;
  TACCR0 = 30;                              // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt
  TACTL = TASSEL_2 + MC_1;                  // TACLK = SMCLK, Up mode
  __bis_SR_register(CPUOFF + GIE);          // LPM0, TA0_ISR will force exit
  TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
  ADC10CTL0 |= ENC;
  TACCTL1 = OUTMOD_4;                       // Toggle on EQU1 (TAR = 0)
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, cont-mode
  while (!(ADC10IFG & ADC10CTL0));          // First conversion?
  FirstADCVal = ADC10MEM;                   // Read out 1st ADC value
  P1OUT = 0x00;                             // Clear P1
  P1DIR = 0x01;                             // P1.0 as output
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  if (ADC10MEM >= FirstADCVal + ADCDeltaOn)
    P1OUT |= 0x01;                          // LED on
  else
    P1OUT &= ~0x01;                         // LED off
}

#pragma vector=TIMERA0_VECTOR
__interrupt void TA0_ISR(void)
{
  TACTL = 0;
  LPM0_EXIT;                                // Exit LPM0 on return
}
