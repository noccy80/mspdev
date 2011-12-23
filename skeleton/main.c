/**
 * Skeleton for MSP430-based projects
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */
 
#include <msp430.h>
#include <legacymsp430.h>
#include <msplib/main.c>

void setup() {
	GPIO_setPinDirection(HAL_PORT_0 + 0xFF, GPIO_OUTPUT);
}

void loop() {
	// Blink the leds
	
}
