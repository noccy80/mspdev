
#include "utils.h"

void delay_ms(uint16_t n) {
	systick = 0;
	while (systick < n/10) nop();
	systick = 0;
}

void flash(int8_t led, int8_t times, uint16_t duration) {

	int8_t current, c1;
	
	// Get current state of the led
	current = P1OUT & led;
	// And flash it the specified number of times
	for(c1 = 0; c1 < times; c1++) {
		P1OUT |= led;
		delay_ms(duration);
		P1OUT &= ~led;
		delay_ms(duration);
	}
	
	// If it was enabled before, we re-enable it
	P1OUT |= current;

}
