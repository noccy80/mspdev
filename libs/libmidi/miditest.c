#include <msp430.h>
#include <legacymsp430.h>
#include "midi.h"

USCI_HANDLER;

int main(void) {

	MidiMessage* msg;

	// Halt the watchdog timer - According to the datasheet the watchdog timer
	// starts automatically after powerup. It must be configured or halted at
	// the beginning of code execution to avoid a system reset. Furthermore,
	// the watchdog timer register (WDTCTL) is password protected, and requires
	// the upper byte during write operations to be 0x5A, which is the value
	// associated with WDTPW.
	WDTCTL = WDTPW + WDTHOLD;

	// Initialize MIDI using USCI for input only
	midi_init(MIDI_MODE_USCI, MIDI_DIR_IN);

	// Listen to channel 0-15 (first nibble) with a mask including all 
	// channels (second nibble)
	midi_set_channel_mask(0xFF);

	while(1) {
		// Poll for a message, if true we go ahead and read the
		// prepared MIDI message
		if (midi_poll()) {
			msg = (MidiMessage*)midi_read();
		}
	}

}

