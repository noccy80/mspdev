#ifndef __LIBGPIO_H__
#define __LIBGPIO_H__

#include <stdint.h>

#ifdef P1IN
#define PORT1 P1IN
#endif
#ifdef P2IN
#define PORT2 P2IN
#endif
#ifdef P3IN
#define PORT3 P3IN
#endif
#ifdef P4IN
#define PORT4 P4IN
#endif

typedef enum _GPIOBUTTONSTATE {
	GBS_DEPRESSED = 0,
	GBS_PRESSED = 1,
	GBS_RELEASED = 2,
	GBS_HELD = 3,
} GPIOBUTTONSTATE;
typedef enum _GPIOPINMODE {
	PIN_INPUT = 0,
	PIN_OUTPUT = 1,
	PIN_PERIPHERAL = 2
} GPIOPINMODE;

typedef struct _GPIOPIN {
	uint16_t port;
	uint8_t pin;
	GPIOPINMODE mode;
	uint8_t _state;
} GPIOPIN;

void gpio_initPin(GPIOPIN* gpiopin, int port, int pin);

GPIOBUTTONSTATE gpio_getButtonState(GPIOPIN* gpiopin);
void gpio_clearButtonState(GPIOPIN* gpiopin);
GPIOPINMODE gpio_getPinMode(GPIOPIN* gpiopin);
void gpio_setPinMode(GPIOPIN* gpiopin, GPIOPINMODE pinmode);

void gpio_initButton(GPIOPIN* gpiopin, uint16_t portbase, uint8_t pin);



#endif // __LIBGPIO_H__
