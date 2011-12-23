//******************************************************************************
//  MSP430F20x2 Demo - ADC10, Sample A1, 1.5V Ref, Set P1.0 if > 0.2V
//
//  Description: A single sample is made on A1 with reference to internal
//  1.5V Vref. Software sets ADC10SC to start sample and conversion - ADC10SC
//  automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
//  and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
//  conversion complete, ADC10_ISR will force exit from any LPMx in Mainloop on
//  reti. If A1 > 0.2V, P1.0 set, else reset.
//
//                MSP430F20x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|P1.1/A1      P1.0|-->LED
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

/*
 *  ======== main ========
 */

static unsigned int FirstADCVal;            // holds 1st ADC result

#define ADCDeltaOn       3                  // ~ 2 Deg C delta for LED on

int main(int argc, char *argv[])
{
    CSL_init();                     // Activate Grace-generated configuration
    
	__disable_interrupt();
	ADC10CTL0 |= ENC;
	while (!(ADC10IFG & ADC10CTL0));          // First conversion?
	FirstADCVal = ADC10MEM;                   // Read out 1st ADC value
	P1OUT = 0x00;                             // Clear P1
	P1DIR = 0x01;                             // P1.0 as output
	__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt

}
void ADC10_ISR(void)
{
	  if (ADC10MEM >= FirstADCVal + ADCDeltaOn)
	    P1OUT |= 0x01;                          // LED on
	  else
	    P1OUT &= ~0x01;                         // LED off
}

