#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <msp430.h>
#include <legacymsp430.h>

#define FW_MAJOR 1
#define FW_MINOR 0
#define FW_REVISION 1

#include "suart.h"

// Buffer to store commands, and pointer to the first character index
unsigned char cmdbuf[256];
unsigned char cmdptr = 0;
void cmdhandler();

int main(void) {

	suart_init();
	while(1) {
		cmdhandler();
		if (!suart_datawaiting()) // Loop again if another value has been received
				__bis_SR_register(CPUOFF + GIE);        
		// LPM0, the ADC interrupt will wake the processor up. This is so that
		// it does not endlessly loop when no value has been Received.
	}

}

void cmdhandler() {

	unsigned char byte;

	// If the device has recieved a value
	if (suart_datawaiting()) {
		byte = suart_receive();

		if (byte == 13) {
		
			// Evaluate command
			//cmdbuf[cmdptr] = 0;
			printf("\r\n");

			// help command
			if (0 == strncmp((const char*)cmdbuf,"help\0",5)) {
				printf("Valid commands: help settime gettime\r\n");
				printf("This is firmware %d.%d.%d built for %s\r\n", FW_MAJOR, FW_MINOR, FW_REVISION, "(mcu)");

			// empty command
			} else if (cmdptr == 0) {
				// Nada

			// settime command
			} else if (0 == strncmp((const char*)cmdbuf,"settime\0",8)) {
				#ifdef HAS_RTC
				printf("RTC: %02d:%02d:%02d\r\n", RTCHOUR, RTCMIN, RTCSEC);
				#else
				printf("This device does not have an on-board RTC\r\n");
				#endif

			// gettime command
			} else if (0 == strncmp((const char*)cmdbuf,"gettime\0",8)) {
				printf("Get RTC time/date\r\n");

			// rest is invalid
			} else {
				printf("Bad command!\r\n");
			}

			printf("cmd> ");
			cmdbuf[0] = 0;
			cmdptr = 0;
			
		} else if (byte==127) {
		
			if (cmdptr > 0) {
				// Move back one step, output a space, and move back again.
				// This should erase a character on most terminals.
				printf("\x08 \x08");
				cmdbuf[cmdptr--] = 0;
			}
			
		} else if (byte>=32) {
		
			cmdbuf[cmdptr++] = byte;
			cmdbuf[cmdptr] = 0;
			// TXByte = byte;	// Load the recieved byte into the byte to be transmitted
			suart_transmit(byte);
			
		}
		
	}

}
