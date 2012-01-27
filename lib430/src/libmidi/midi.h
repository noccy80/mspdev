#ifndef __MIDI_H__
#define __MIDI_H__

#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>

#define MIDI_MODE_USI       1
#define MIDI_MODE_USCI      2

#define MIDI_DIR_IN         1
#define MIDI_DIR_OUT        2
#define MIDI_DIR_BOTH       MIDI_DIR_IN | MIDI_DIR_OUT

// Bit 7 set for messages, upper nibble message type
#define MIDI_MESSAGE_MASK   0xF0
// MIDI message types
#define MIDI_MSG_NOTEOFF    0x80
#define MIDI_MSG_NOTEON     0x90
#define MIDI_MSG_AFTERTOUCH 0xA0
#define MIDI_MSG_CONTROL    0xB0
#define MIDI_MSG_PROGRAM    0xC0
#define MIDI_MSG_PRESSURE   0xD0
#define MIDI_MSG_WHEEL      0xE0

// Size of transmit and receive buffers in BYTES -- not messages!
#define MIDI_TXBUFSIZE      16
#define MIDI_RXBUFSIZE      16

// Stock handlers for USI/USCI interrupts.
#define USI_HANDLER interrupt(USI_VECTOR) midi_usi_isr(void) { midi_handleusimsg(); }
#define USCI_HANDLER interrupt(USCIAB0RX_VECTOR) midi_usi_isr(void) { midi_handleusimsg(); }


/**
 * @brief Initialize the MIDI subsystem 
 *
 * @param uint8_t mode MIDI_MODE_USI or MIDI_MODE_USCI
 * @param uint8_t dir The direction (MIDI_DIR_IN, _OUT or _BOTH)
 */
void midi_init(uint8_t mode, uint8_t dir);

/**
 * @brief Set the channel mask
 *
 *
 */
uint8_t midi_set_channel_mask(uint8_t newmask);

///////////////////////////////////////////////////////////////////////////////
//
//  midimessage.c methods
//

uint8_t midi_poll();

/**
 * @brief Read a MIDI message, indirectly, by examining the buffer
 *
 */
void midi_read();

/**
 * @brief Write a MIDI message
 *
 */
void midi_sendmessage(uint8_t channel, uint8_t message, uint8_t* data, uint8_t len);

///////////////////////////////////////////////////////////////////////////////
//
//  buffer.c methods
//

/**
 * @brief Transmit a byte by pushing it on the buffer
 * 
 * @param uint8_t byte The byte to transmit
 */
void midi_txbyte(uint8_t byte);

/**
 * @brief Receive a byte from the buffer 
 *
 * @return uint8_t The received byte
 */
uint8_t midi_rxbyte(void);

#endif // __MIDI_H__
