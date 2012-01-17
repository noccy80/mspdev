#ifndef __LIBGPIO_H__
#define __LIBGPIO_H__

#include <hal.h>
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

inline uint8_t gpio_decode_port(HAL_MAP halmap) { return ((halmap & 0x00F0) >> 4); };
inline uint8_t gpio_decode_pin(HAL_MAP halmap) { return (halmap & 0x000F); };

void gpio_makeinput(HAL_MAP pin);
void gpio_makeoutput(HAL_MAP pin);
void gpio_setstate(HAL_MAP pin, uint8_t state);

GPIOBUTTONSTATE gpio_get_button_state(GPIOPIN* pin);
void gpio_init_button(GPIOPIN* pin, uint16_t portbase, uint8_t pin);

int gpio_shift_in(GPIOPIN* clk, GPIOPIN* data);
void gpio_shift_out(GPIOPIN* clk, GPIOPIN* data, int state);

#endif // __LIBGPIO_H__
