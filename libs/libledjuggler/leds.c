#include "leds.h"

uint8_t buf[(8*16*2)/8];

LED_DISPDEF juggler;

void main() {

	juggler->rows = 8;
	juggler->cols = 16;
	juggler->bpp = 2;
	juggler->buffer = &buf;

	if (!ledjuggler_init(&juggler)) {

	}

}
