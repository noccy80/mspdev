#include "midi.h"

volatile uint8_t midi_txbuffer[MIDI_TXBUFSIZE] = {0};
volatile uint8_t midi_rxbuffer[MIDI_RXBUFSIZE] = {0};
volatile uint8_t midi_txbufptr = 0;
volatile uint8_t midi_rxbufptr = 0;

void midi_txbyte(uint8_t byte) {

	// Push the bytes on the buffer and increase the pointer
	midi_txbuffer[midi_txbufptr] = byte;
	midi_txbufptr++;

}

uint8_t midi_rxbyte(void) {

	// Pop a byte off the buffer if there is one
	if (midi_rxbufptr > 0) {
		midi_rxbufptr--;
		return( midi_rxbuffer[midi_rxbufptr]);
	}
	return 0;

}
