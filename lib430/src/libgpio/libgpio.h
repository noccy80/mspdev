#ifndef __LIBGPIO_H__
#define __LIBGPIO_H__

#include <msplib.h>

typedef struct _GPIOPIN {
	uint16_t portbase;
	uint8_t pin;
	uint8_t _state;
} GPIOPIN;

enum GPIOBUTTONSTATE {
	GBS_DEPRESSED = 0,
	GBS_PRESSED = 1,
	GBS_RELEASED = 2,
	GBS_HELD = 3,
};

GPIOBUTTONSTATE gpio_getButtonState(GPIOPIN* pin);
void gpio_initButton(GPIOPIN* pin, uint16_t portbase, uint8_t pin);



#endif // __LIBGPIO_H__
