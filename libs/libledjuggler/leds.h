#ifndef __LEDS_H__
#define __LEDS_H__

#include "stdint.h"

typedef struct LED_DISPDEF {
	uint8_t rows; // Number of rows
	uint8_t cols; // Number of cols
	uint8_t bpp; // Normally 2

	uint8_t* buffer;

	uint8_t hw_sreg_width; // Number of shift registers (cols, 8 per ic)
	uint8_t hw_rdec_count; // Number of decoder channels (rows, 8 per ic, multiplexable)
} LED_DISPDEF;

int ledjuggler_init(LED_DISPDEF& juggler);
int ledjuggler_close(LED_DISPDEF& juggler);
void ledjuggler_update(LED_DISPDEF& juggler);

#endif // __LEDS_H__
