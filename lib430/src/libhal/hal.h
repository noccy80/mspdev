#ifndef __HAL_H__
#define __HAL_H__
#include <stdint.h>

#define HAL_MAP uint16_t

/**
 * NoccyLabs Hardware Abstraction Library for the MSP430
 *
 * This library abstracts the actual hardware and pinouts required to perform
 * IO over SUART/UART/USCI/USI as well as regular GPIO. Very experimental but
 * the goal is to have a standardized way of passing around references to pins
 * and modules without really having to bother with where or what they are.
 */

enum hal_class {
	HAL_CLASS_NULL1 = 0x0100,
	HAL_CLASS_NULL2 = 0x0200,
	HAL_CLASS_NULL3 = 0x0400,
	HAL_CLASS_NULL4 = 0x0800,
	HAL_CLASS_USCI  = 0x1000,
	HAL_CLASS_USI   = 0x2000,
	HAL_CLASS_GPIO  = 0x4000,
	HAL_CLASS_OTHER = 0x8000
};

enum hal_device {
	HAL_DEVICE_0    = 0x0010,
	HAL_DEVICE_1    = 0x0020,
	HAL_DEVICE_2    = 0x0030,
	HAL_DEVICE_3    = 0x0040
};

enum gpio_port {
	GPIO_PORT_1     = 0x0010,
	GPIO_PORT_2     = 0x0020,
	GPIO_PORT_3     = 0x0030,
	GPIO_PORT_4     = 0x0040
};

enum gpio_pin {
	GPIO_PIN_0      = 0x0001,
	GPIO_PIN_1      = 0x0002,
	GPIO_PIN_2      = 0x0003,
	GPIO_PIN_3      = 0x0004,
	GPIO_PIN_4      = 0x0005,
	GPIO_PIN_5      = 0x0006,
	GPIO_PIN_6      = 0x0007,
	GPIO_PIN_7      = 0x0008
};

enum gpio_offsets {
	GPIO_OFFS_IN    = 0,
	GPIO_OFFS_OUT   = 1,
	GPIO_OFFS_DIR   = 2,
	GPIO_OFFS_IE    = 3,
	GPIO_OFFS_RES   = 7
};

const uint8_t _PBADDR[] = { P1IN_, P2IN_, P3IN_ };

inline uint8_t gpio_decode_port(HAL_MAP halmap) { return ((halmap & 0x00F0) >> 4); };
inline uint8_t gpio_decode_pin(HAL_MAP halmap) { return (halmap & 0x000F); };

void gpio_makeinput(HAL_MAP pin);
void gpio_makeoutput(HAL_MAP pin);
void gpio_setstate(HAL_MAP pin, uint8_t state);

/**
 * Arduino-ish-ness
 *
 * Implemented as macros calling on msplibs native methods. Difference is in
 * how it is invoked:
 *
 *   bool v = digital_read(HAL_CLASS_GPIO | GPIO_PORT_1 | GPIO_PIN_0);
 */
#define digital_read(P) gpio_getstate(P)
#define digital_write(P,D) gpio_setstate(P,D)

// HAL_MAP led = HAL_DEVICE_GPIO | GPIO_PORT_0 | GPIO_PIN_1;
// gpio_makeoutput(led); gpio_setstate(led, 1);

// gpio_setstate( HAL_DEVICE_GPIO | GPIO_PORT_0 | GPIO_PIN_0 , 1);

#endif // __HAL_H__
