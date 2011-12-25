#include <stdint.h>
#include "hal.h"

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
		uint8_t port = (uint8_t*)hal_get_port_base(gpio_decode_port(pin));
		if (port) { 
			// Set port input 
		}
	}
}

void gpio_makeoutput(HAL_MAP pin) {
	if (pin & HAL_DEVICE_GPIO) {
		uint8_t port = (uint8_t*)hal_get_port_base(gpio_deocde_port(pin));
		if (port) { 
			// Set port output
		}
	}
}

void gpio_setstate(HAL_MAP pin, uint8_t state) {
	if (pin & HAL_DEVICE_GPIO) {
		uint8_t port = (uint8_t*)hal_get_port_base(pin & HAL_MASK_PORT);
		if (port) { 
			uint8_t pin = hal_get_pin
			// Set port state
		}
	}
}

/*
HAL_MAP led = HAL_DEVICE_GPIO | GPIO_PORT_0 | GPIO_PIN_1;
gpio_makeoutput(led); gpio_setstate(led, 1);

gpio_setstate( HAL_DEVICE_GPIO | GPIO_PORT_0 | GPIO_PIN_0 , 1);

*/
