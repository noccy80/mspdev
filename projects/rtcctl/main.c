/**
 * Skeleton for MSP430-based projects
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */
 
#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>
#include "suart.h"
#include "rtc.h"
#include "adc.h"

#define CMD_COMMAND 0
#define CMD_INPUT 1
#define CMD_NONE 2

#define KEY_CTRL_C 3

// Buffer to store commands, and pointer to the first character index
uint8_t cmdbuf[256];
uint8_t cmdptr = 0;
uint8_t cmdmode = CMD_COMMAND;
void cmdhandler();

void cmdeval();

/**
 * @brief Main function
 *
 */
int main(void) {

	// Halt the watchdog timer - According to the datasheet the watchdog timer
	// starts automatically after powerup. It must be configured or halted at
	// the beginning of code execution to avoid a system reset. Furthermore,
	// the watchdog timer register (WDTCTL) is password protected, and requires
	// the upper byte during write operations to be 0x5A, which is the value
	// associated with WDTPW.
	WDTCTL = WDTPW + WDTHOLD;

	// Initialize the software UART
	suart_init();

	P1DIR |= BIT6;
	// Initialize I2C support
	I2C_INIT_STRUCT init = {
		(uint16_t)&P1OUT, BIT6,
		(uint16_t)&P1OUT, BIT5	
	};
	i2c_master_init(&init);

	// Initialize real time clock
	rtc_init(RTC_USE_BEST,0);

	// Main loop
	while(1) {
		if (cmdmode == CMD_NONE) {
			__delay_cycles(64000);
			__delay_cycles(64000);
			cmdeval();
		}
		cmdhandler();
		
		if (!suart_datawaiting()) {
			// Loop again if another value has been received
			/*
			__bis_SR_register(CPUOFF + GIE);        
			*/
			// LPM0, the ADC interrupt will wake the processor up. This is so that
			// it does not endlessly loop when no value has been Received.
		}
	}

}

/**
 * @brief Display command prompt
 *
 */
void cmdprompt() {

	// Branch based on the current command mode and display an appropriate
	// prompt.
	switch(cmdmode) {

		case CMD_COMMAND:
			printf("cmd> ");
			break;
		case CMD_INPUT:
			break;
	}


}

/**
 * @brief Evaluate commands and input
 *
 */
void cmdeval() {

	uint16_t temp;
	RTC_TIME_STRUCT t_time;

	if (cmdmode != CMD_NONE) printf("\r\n");

	if (cmdmode == CMD_INPUT) {
		cmdmode = CMD_COMMAND;

	} else {

		// Evaluate commands
		// help command
		if (0 == strncmp((const char*)cmdbuf,"help\0",5)) {
			printf("Available Commands: help settime gettime gettemp action\r\n");
		// empty command
		} else if (cmdptr == 0) {
			// Nada
		} else if (0 == strncmp((const char*)cmdbuf,"action\0",7)) {
			cmdmode = CMD_INPUT;
			// settime command
		} else if (0 == strncmp((const char*)cmdbuf,"settime\0",8)) {
			cmdmode = CMD_INPUT;
			rtc_get_time(&t_time); 
			printf("Year [%02d]: ", t_time.year);
		// gettime command
		} else if (0 == strncmp((const char*)cmdbuf,"gettime\0",8)) {
			rtc_get_time(&t_time); 
			printf("RTC Date: %02d-%02d-%02d (%d)\r\n", t_time.year, t_time.month, t_time.day, t_time.dow);
			printf("RTC Time: %02d:%02d:%02d\r\n", t_time.hour, t_time.minute, t_time.second);
			printf("RTC Mode: %s\r\n", rtc_get_mode());
		} else if (0 == strncmp((const char*)cmdbuf,"gettemp\0",8)) {
			cmdmode = CMD_NONE;
			temp = adc_single_measure(INCH_10);
			printf("Temperature: %d\r\n", temp);
		// rest is invalid
		} else {
			printf("Bad command!\r\n");
		}
	}
}

/**
 * @brief Handler for all text I/O 
 *
 */
void cmdhandler() {

	uint8_t byte;

	// If the device has recieved a value
	if (suart_datawaiting()) {
		byte = suart_receive();

		if (byte == 13) {
			// When the enter key is pressed
			cmdeval();
			if (cmdmode == CMD_NONE) return;
			cmdprompt();
			cmdbuf[0] = 0;
			cmdptr = 0;
			
		} if ((byte == 3) && (cmdmode == CMD_NONE)) {
		
			printf("Abort.\r\n");
			cmdmode = CMD_COMMAND;
			cmdprompt();
			cmdbuf[0] = 0;
			cmdptr = 0;

		} else if (byte==127) {
			// When backspace is pressed
			if (cmdptr > 0) {
				// Move back one step, output a space, and move back again.
				// This should erase a character on most terminals.
				printf("\x08 \x08");
				cmdbuf[cmdptr--] = 0;
			}

		} else if (byte>=32) {
			// Space or any character above ascii 32 should be echoed back to
			// the client. It should also be added to the buffer.

			cmdbuf[cmdptr++] = byte;
			cmdbuf[cmdptr] = 0;
			suart_transmit(byte);
			
		}
		
	}

}
