

#ifndef __ADC_H__
#define __ADC_H__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <msp430.h>
#include <legacymsp430.h>


/**
* Reads ADC 'chan' once using AVCC as the reference.
**/
uint16_t adc_single_measure(uint16_t chan);
uint16_t adc_single_measure_ref(uint16_t chan, uint16_t ref);



#endif // __ADC_H__
