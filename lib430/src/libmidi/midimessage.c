#include "midi.h"

uint8_t midi_getmsgchannel(uint8_t message) {

	return ( message & 0x0F );

}

uint8_t midi_getmsgtype(uint8_t message) {

	return ( message >> 4 );

}

void midi_sendmessage(uint8_t channel, uint8_t message, uint8_t* data, uint8_t len) {

	uint8_t msgbyte;
	uint8_t n;
	
	// Assemble the byte to transmit for the actual message
	msgbyte = channel | ( message << 4 );
	
	midi_txbyte( msgbyte );
	for( n = 0; n < len; n++) {
		midi_txbyte( data[n] );
	}

}


