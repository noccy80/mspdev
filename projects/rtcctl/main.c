/**
 * Skeleton for MSP430-based projects
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */
 
#include <msp430.h>
#include <legacymsp430.h>
#include "suart.h"

#define CMD_COMMAND 0
#define CMD_INPUT 1

// Buffer to store commands, and pointer to the first character index
unsigned char cmdbuf[256];
unsigned char cmdptr = 0;
unsigned char cmdmode = CMD_COMMAND;
void cmdhandler();

int main(void) {

	// Halt the watchdog timer - According to the datasheet the watchdog timer
	// starts automatically after powerup. It must be configured or halted at
	// the beginning of code execution to avoid a system reset. Furthermore,
	// the watchdog timer register (WDTCTL) is password protected, and requires
	// the upper byte during write operations to be 0x5A, which is the value
	// associated with WDTPW.
	WDTCTL = WDTPW + WDTHOLD;

	suart_init();

	while(1) {
		cmdhandler();
		if (!suart_datawaiting()) // Loop again if another value has been received
				__bis_SR_register(CPUOFF + GIE);        
		// LPM0, the ADC interrupt will wake the processor up. This is so that
		// it does not endlessly loop when no value has been Received.
	}

}

void cmdprompt() {

	switch(cmdmode) {

		case CMD_COMMAND:
			printf("cmd> ");
			break;
		case CMD_INPUT:
			printf("enter> ");
			break;
	}


}

void cmdeval() {

	printf("\r\n");

	if (cmdmode == CMD_INPUT) {
		cmdmode = CMD_COMMAND;

	} else {

		// Evaluate commands
		// help command
		if (0 == strncmp((const char*)cmdbuf,"help\0",5)) {
			printf("Valid commands: help settime gettime action\r\n");
		// empty command
		} else if (cmdptr == 0) {
			// Nada
			} else if (0 == strncmp((const char*)cmdbuf,"action\0",7)) {
			cmdmode = CMD_INPUT;
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
	}
}

void cmdhandler() {

	unsigned char byte;

	// If the device has recieved a value
	if (suart_datawaiting()) {
		byte = suart_receive();

		if (byte == 13) {

			cmdeval();
			cmdprompt();
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
