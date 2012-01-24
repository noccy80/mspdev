#ifndef __LIBGPIO_H__
#define __LIBGPIO_H__

#include <hal.h>
#include <msplib.h>
#include <stdint.h>
#include <hooks.h>

typedef struct _GpioPin {
	uint16_t portbase;
	uint8_t pin;
	uint8_t _state;
} GpioPin;

enum GpioButtonState {
	GBS_DEPRESSED = 0,
	GBS_PRESSED = 1,
	GBS_RELEASED = 2,
	GBS_HELD = 3,
};

enum GpioFlags {
	GPIO_DIR_IN = 0x01,
	GPIO_DIR_OUT = 0x02,
	GPIO_TYPE_DIGITAL = 0x04,
	GPIO_TYPE_ANALOG = 0x08,
	GPIO_CALLBACK = 0x10,
};

inline uint8_t gpio_decode_port(HAL_MAP halmap) { return ((halmap & 0x00F0) >> 4); };
inline uint8_t gpio_decode_pin(HAL_MAP halmap) { return (halmap & 0x000F); };

typedef GpioPin uint16_t;

void gpio_makeinput(HAL_MAP pin);
void gpio_makeoutput(HAL_MAP pin);
void gpio_setstate(HAL_MAP pin, uint8_t state);

void gpio_configure_pin(GpioPin* pin, uint16_t flags);

uint8_t gpio_get_button_state(GpioPin* pin);
void gpio_init_button(GpioPin* gpiopin, uint16_t portbase, uint8_t pin);

int gpio_shift_in(GpioPin* clk, GpioPin* data);
void gpio_shift_out(GpioPin* clk, GpioPin* data, int state);

#endif // __LIBGPIO_H__
