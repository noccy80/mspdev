#include <msp430.h>
#include <legacymsp430.h>
#include "communication.h"

void sccom_init() {

}

int sccom_data_waiting() {

}

int sccom_read() {

}

interrupt(PORT1_VECTOR) port1_isr(void) {

	// If it is the clock pin, shift one bit in.

}
