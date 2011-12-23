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
//******************************************************************************
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace and RTSC related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

/*
 *  ======== main ========
 */

static unsigned int FirstADCVal;            // holds 1st ADC result

#define ADCDeltaOn       3                  // ~ 2 Deg C delta for LED on

void main(int argc, char *argv[])
{
    CSL_init();

    TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
    ADC10CTL0 |= ENC;                         // Enable ADC conversions
    TACCTL1 = OUTMOD_4;                       // Toggle on EQU1 (TAR = 0)
    TACTL = TASSEL_2 + MC_2;                  // SMCLK, cont-mode
    while (!(ADC10IFG & ADC10CTL0));          // First conversion?
    FirstADCVal = ADC10MEM;                   // Read out 1st ADC value
    P1OUT = 0x00;                             // Clear P1
    P1DIR = 0x01;                             // P1.0 as output
    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}
void TimerA_ISR (void)
{
    TACTL = 0;
}
void ADC10_ISR (void)
{
    if (ADC10MEM >= FirstADCVal + ADCDeltaOn)
      P1OUT |= 0x01;                          // LED on
    else
      P1OUT &= ~0x01;                         // LED off
}
