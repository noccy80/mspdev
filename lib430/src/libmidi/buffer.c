#include "midi.h"

volatile uint8_t midi_txbuffer[MIDI_TXBUFSIZE] = {0};
volatile uint8_t midi_rxbuffer[MIDI_RXBUFSIZE] = {0};
volatile uint8_t midi_txbufptr = 0;
volatile uint8_t midi_rxbufptr = 0;

/** 
 * @brief Transmit a byte over MIDI.
 *
 * The byte will be added to the end of the transmission buffer. If an error
 * occurs the return value will be non-zero.
 *
 * @return uint8_t 0 on success
 */
uint8_t midi_txbyte(uint8_t byte) {

	// Push the bytes on the buffer and increase the pointer
	midi_txbuffer[midi_txbufptr] = byte;
	midi_txbufptr++;

}

/** 
 * @brief Transmit a byte over MIDI.
 *
 * The byte will be added to the end of the transmission buffer. If an error
 * occurs the return value will be non-zero.
 *
 * @return uint8_t The byte on success, and 0 otherwise.
 */
uint8_t midi_rxbyte(void) {

	// Pop a byte off the buffer if there is one
	if (midi_rxbufptr > 0) {
		midi_rxbufptr--;
		return( midi_rxbuffer[midi_rxbufptr]);
	}
	return 0;

}
