/**
 * Skeleton for MSP430-based projects
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */
 
#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>
#include "midi.h"
#include "flash.h"

#define MAX_CONTROLLERS 32
#define PADTYPE_SLIDER 0 // Slider (min-max)
#define PADTYPE_KNOB 1 // Knob (min-max)
#define PADTYPE_ROTARY 2 // Rotary encoder (rotates freely)
#define PADTYPE_JOG 3 // Jog (falls back to center)
#define PADTYPE_BUTTON 4 // Button

typedef struct pad_config {
	uint8_t portpin;
	uint8_t midicc;
	uint8_t padtype;
	uint16_t calmin; // Calibration minimum value
	uint16_t calmax; // Calibration maximum value
} pad_config;
pad_config padconfig[MAX_CONTROLLERS];

void read_config(void);

int main(void) {

	padconfig[0].portpin = (1 << 4) | (1); // PortA1
	padconfig[0].midicc = 1; // Midi CC 1
	padconfig[0].padtype = PADTYPE_SLIDER;

	// Halt the watchdog timer - According to the datasheet the watchdog timer
	// starts automatically after powerup. It must be configured or halted at
	// the beginning of code execution to avoid a system reset. Furthermore,
	// the watchdog timer register (WDTCTL) is password protected, and requires
	// the upper byte during write operations to be 0x5A, which is the value
	// associated with WDTPW.
	WDTCTL = WDTPW + WDTHOLD;

	

	// lcd_init();
	read_config();

	while(1) {
		//Loop forever, interrupts take care of the rest
	}

}

void read_config(void) {

	flash_write(0x1000, &padconfig, sizeof(pad_config)*MAX_CONTROLLERS);
	// Read configuration block from flash

}

void write_config(void) {

	// Write configuration block to flash

}
