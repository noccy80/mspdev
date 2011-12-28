/**
 * MSP430 Persistence of Visition Display, Storage back-end
 *
 * This is a simple POV display for the MSP430, capable of outputting text (for
 * now at least) in any direction. It can be extended with a tilt sensor to
 * change the direction.
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */

#include "database.h"
#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>

DbMessage database[NUM_PRESETS];
volatile unsigned char* current_display;
uint8_t current_len = 0;

void database_loadMessage(uint8_t index) {

	// Load and decode the current message
	// 

}

void database_saveMessage(uint8_t index) {

}

void pov_getColumn(uint16_t index) {

}
