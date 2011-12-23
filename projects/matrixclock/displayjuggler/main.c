
#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>
#include <hal.h>

#define LED_ROWS 8
#define LED_COLS 16

volatile uint8_t display[LED_ROWS * LED_COLS] = 0;

void main() {

	wdt_stop();

	gpio_makeoutput(GPIO_CLASS_PORT | GPIO_PORT_0 | GPIO_PIN_ALL);

}
