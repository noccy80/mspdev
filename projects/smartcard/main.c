#include "smartcard.h"
#include <msp430.h>
#include <legacymsp430.h>
#include "communication.h"
#include <wdt.h>

#define CMDBUF_LEN 64
unsigned char cmdbuf[CMDBUF_LEN] = {0};
unsigned char cmdptr = 0;

int main(void) {

	wdt_hold();
	sccom_init();

	// Set up two pins to shift data in from host
	do {

		if (sccom_data_waiting()) {
			cmdbuf[cmdptr++] = sccom_read();
			if (cmdbuf[cmdptr-1]== "\n") {
				// Evaluate buffer
			}
		}


	} while(1);

}
