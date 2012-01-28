#ifndef __IRDECODER_H__
#define __IRDECODER_H__

#include <stdint.h>
#include <gpio.h>

#define IR_THRESHOLD_LOW 50
#define IR_CALIBRATION_HITS 40

typedef struct _IrDecoderStruct {
	uint16_t in_pin;
	uint16_t out_pin;
	uint16_t pulse_iv;
	uint16_t pulse_len;
	uint16_t pulse_silence;
} IrDecoderStruct;

/**
 * @brief Initialize the infra-red decoder.
 *
 * The calibration data will be reset after calling this method. The actual
 * pin will be properly configured and interrupts enabled.
 *
 * @param IrDecoderStruct* irds The infra-red decoder structure
 * @param GpioPin* in_pin The input pin
 */
void ir_initialize(IrDecoderStruct* irds, uint16_t in_pin);

/**
 * @brief Initialize the infra-red decoder and transmitter.
 *
 * Initializes the library in bidirectional mode. This includes an input pin
 * and an outpout pin, connected to an IR receiver (or optoresistor) and an
 * infra-red LED (or normal led). The pins will be configured accordingly and
 * interrupts enabled.
 *
 * @param IrDecoderStruct* irds The infra-red decoder structure
 * @param GpioPin* in_pin The input pin
 */
void ir_initialize_bidir(IrDecoderStruct* irds, uint16_t in_pin, uint16_t out_pin, uint16_t pulse_iv);

/**
 * @brief Calibrate the infra-red decoder.
 *
 * This method will block until the infra-red decoder has been properly
 * calibrated. This will be completed once the receiver has seen enough
 * packets to reliably detect the patterns used.
 *
 * Note that you just need to calibrate the receiver when operating in packet
 * mode, as you specify the rates manually in bidirectional mode.
 *
 * @param IrDecoderStruct* irds The infra-red decoder structure
 */
void ir_calibrate(IrDecoderStruct* irds);

/**
 * @brief Receive a packet.
 *
 * The value of the packet is limited to 16 bits. The number of bits that
 * will be received depends on the transmitter. If you want to send data
 * between two devices using a receiver and a transmitter, you should use
 * the ir_send_byte() and ir_receive_byte() methods instead.
 *
 * @param IrDecoderStruct* irds The infra-red decoder structure
 */
uint16_t ir_receive_packet(IrDecoderStruct* irds);

/**
 * @brief Send a byte via the LED.
 *
 * For this you need to have a dedicated transmitter led. You therefore
 * need to specify the other pin (holding the LED as opposed to the input
 * from the IR receiver by calling ir_initialize_bidir() rather than
 * ir_initialize()
 *
 * @param IrDecoderStruct* irds The infra-red decoder structure
 */
void ir_send_byte(IrDecoderStruct* irds, uint8_t byte);

/**
 * @brief Send a byte via the LED.
 *
 * For this you need to have a dedicated transmitter led. You therefore
 * need to specify the other pin (holding the LED as opposed to the input
 * from the IR receiver by calling ir_initialize_bidir() rather than
 * ir_initialize()
 *
 * @param IrDecoderStruct* irds The infra-red decoder structure
 */
void ir_receive_byte(IrDecoderStruct* irds, uint8_t* byte);

#endif // __IRDECODER_H__
