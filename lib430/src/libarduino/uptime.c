#include "arduino.h"

#include <msp430.h>
#include <legacymsp430.h>

volatile unsigned long mcu_ms = 0;

void uptime_init() {

	// Get the controller clock
	// Set up the timer
	WDTCTL = WDTPW | WDTHOLD;
	// TODO: Start the timer

}

interrupt(TIMER0_A0_VECTOR) clockctl_isr(void) {

	mcu_ms++;

}

unsigned long micros() {

	return (mcu_ms * 10);

}

unsigned long millis() {

	return (mcu_ms / 100);

}
