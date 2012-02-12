#include "gpio.h"

const int _pin_in = 0;
const int _pin_out = 1;
const int _pin_dir = 2;
const int _pin_sel1 = 6;


void _gpio_apply_pinmode(GPIOPIN* gpiopin) {
	char* port = (char*)(gpiopin->port);
	int pin = (1 << gpiopin->pin);
	switch(gpiopin->mode) {
		case PIN_INPUT:
			port[_pin_dir] |= pin;
			break;
		case PIN_OUTPUT:
			port[_pin_dir] &= ~(pin);
			break;
		case PIN_PERIPHERAL:
			port[_pin_sel1] |= pin;
			break;
	}
}

void gpio_initPin(GPIOPIN* gpiopin, int port, int pin) {
	gpiopin->port = port;
	gpiopin->pin = pin;
	gpiopin->mode = PIN_INPUT;
	_gpio_apply_pinmode(gpiopin);
}

GPIOBUTTONSTATE gpio_getButtonState(GPIOPIN* gpiopin) {

	return 0;
}

void gpio_clearButtonState(GPIOPIN* gpiopin) {

}

GPIOPINMODE gpio_getPinMode(GPIOPIN* gpiopin) {

	return 0;

}

void gpio_setPinMode(GPIOPIN* gpiopin, GPIOPINMODE pinmode) {

}

void gpio_initButton(GPIOPIN* gpiopin, uint16_t portbase, uint8_t pin) {

}
