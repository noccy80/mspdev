#include <stdint.h>
#include "hal.h"

uint8_t* hal_get_port_base(uint8_t port, uint8_t offset) {
	return (_PBADDR[port] + offset);
}

uint8_t hal_get_pin(HAL_MAP pin) {
	return 2^(pin & 0xF);
}

/**
 * NoccyLabs Hardware Abstraction Library for the MSP430
 *
 * This library abstracts the actual hardware and pinouts required to perform
 * IO over SUART/UART/USCI/USI as well as regular GPIO. Very experimental but
 * the goal is to have a standardized way of passing around references to pins
 * and modules without really having to bother with where or what they are.
 */

inline void gpio_decode_port(HAL_MAP halmap) { return ((halmap & 0x00F0) >> 4); };
inline void gpio_decode_pin(HAL_MAP halmap) { return ((halmap & 0x000F); };

void gpio_makeinput(HAL_MAP pin) {
	if (pin & HAL_DEVICE_GPIO) {
		uint8_t port = (uint8_t*)hal_get_port_base(gpio_decode_port(pin),GPIO_OFFS_DIR);
		uint8_t pinval = hal_get_pin_value(pin);
		if (port) { 
			// Set port input 
			port |= pinval;
		}
	}
}

void gpio_makeoutput(HAL_MAP pin) {
	if (pin & HAL_DEVICE_GPIO) {
		uint8_t port = (uint8_t*)hal_get_port_base(gpio_decode_port(pin),GPIO_OFFS_DIR);
		uint8_t pinval = hal_get_pin_value(pin);
		if (port) { 
			// Set port output
			port &= ~pinval;
		}
	}
}

void gpio_setstate(HAL_MAP pin, bool state) {
	if (pin & HAL_DEVICE_GPIO) {
		uint8_t port = (uint8_t*)hal_get_port_base(gpio_decode_port(pin),GPIO_OFFS_OUT);
		uint8_t pinval = hal_get_pin_value(pin);
		if (port) { 
			if (state) { 
				port |= pinval;
			} else {
				port &= ~pinval;
			}
		}
	}
}

bool gpio_getstate(HAL_MAP pin) {
	if (pin & HAL_DEVICE_GPIO) {
		uint8_t port = (uint8_t*)hal_get_port_base(gpio_decode_port(pin),GPIO_OFFS_OUT);
		uint8_t pinval = hal_get_pin_value(pin);
		return (port & pinval);
	}
}

/*
HAL_MAP led = HAL_DEVICE_GPIO | GPIO_PORT_0 | GPIO_PIN_1;
gpio_makeoutput(led); gpio_setstate(led, 1);

gpio_setstate( HAL_DEVICE_GPIO | GPIO_PORT_0 | GPIO_PIN_0 , 1);

*/
