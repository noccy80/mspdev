//*****************************************************************************
//  MSP-FET430P140 Demo - ADC12, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
//
//  Description: Use ADC12 and the integrated temperature sensor to detect
//  temperature gradients. The temperature sensor output voltage is sampled
//  ~ every 80ms and compared with the defined delta values using an ISR.
//  (ADC12OSC/256)/ determines sample time which needs to be greater than
//  30us for temperature sensor.
//  ADC12 is operated in repeat-single channel mode with the sample and
//  convert trigger sourced from Timer_A CCR1. The ADC12MEM0_IFG at the end
//  of each converstion will trigger an ISR.
//  ACLK = n/a, MCLK = SMCLK = default DCO ~ 800k, ADC12CLK = ADC12OSC
//
//                MSP430Fx49
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |A10          P1.0|-->LED
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

#define ADCDeltaOn       12                 // ~2 Deg C delta

static unsigned int FirstADCVal;            // holds 1st ADC result

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  P1OUT = 0x00;                             // Clear P1
  P1DIR = 0x01;                             // P1.0 as output
  ADC12CTL1 = SHS_1 + SHP + CONSEQ_2;       // TA trig., rpt conv.
  ADC12MCTL0 = SREF_1 + INCH_10;            // Channel A10, Vref+
  ADC12IE = 0x01;                           // Enable ADC12IFG.0
  ADC12CTL0 = SHT0_8 + REF2_5V + REFON + ADC12ON + ENC; // Config ADC12
  TACCTL1 = OUTMOD_4;                       // Toggle on EQU1 (TAR = 0)
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, cont-mode
  while (!(0x01 & ADC12IFG));               // First conversion?
  FirstADCVal = ADC12MEM0;                  // Read out 1st ADC value
  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  if (ADC12MEM0 <= FirstADCVal + ADCDeltaOn)
      P1OUT &= ~0x01;                       // LED off
  else P1OUT |= 0x01;                       // LED on
}
