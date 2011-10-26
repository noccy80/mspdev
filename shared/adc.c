#include "adc.h"

uint16_t _adc10_value = 0;
bool _adc10_done = false;

/**
* Reads ADC 'chan' once using AVCC as the reference.
**/
uint16_t adc_single_measure(uint16_t chan) {

	_adc10_done = false;
	ADC10CTL0 &= ~ENC;				// Disable ADC
	ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE;	// 16 clock ticks, ADC On, enable ADC interrupt
	ADC10CTL1 = ADC10SSEL_3 + chan;				// Set 'chan', SMCLK
	ADC10CTL0 |= ENC + ADC10SC;             	// Enable and start conversion

	// while (!_adc10_done);
	__delay_cycles (64);
	return(_adc10_value);

}

/**
* Reads ADC 'chan' once using an internal reference, 'ref' determines if the
*   2.5V or 1.5V reference is used.
**/
uint16_t adc_single_measure_ref(uint16_t chan, uint16_t ref) {

	_adc10_done = false;
	ADC10CTL0 &= ~ENC;							// Disable ADC
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ref + ADC10IE;	// Use reference,
													//   16 clock ticks, internal reference on
													//   ADC On, enable ADC interrupt, Internal  = 'ref'
	ADC10CTL1 = ADC10SSEL_3 + chan;				// Set 'chan', SMCLK
	__delay_cycles (128);					// Delay to allow Ref to settle
	ADC10CTL0 |= ENC + ADC10SC; 				// Enable and start conversion

	// while (!_adc10_done);
	__delay_cycles (64);
	return(_adc10_value);

}

/**
* ADC interrupt routine. Pulls CPU out of sleep mode for the main loop.
**/
interrupt(ADC10_VECTOR) ADC10_ISR(void) {

	_adc10_value = ADC10MEM;			// Saves measured value.
	_adc10_done = true;  			// Sets flag for main loop.
	__bic_SR_register_on_exit(CPUOFF);	// Enable CPU so the main while loop continues
	
}
