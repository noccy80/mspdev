#include "irdecoder.h"

void ir_initialize(IrDecoderStruct* irds, uint16_t in_pin) {
	irds->in_pin = in_pin;
	irds->out_pin = GPIO_PIN_NULL;
	irds->pulse_iv = 0;
	irds->pulse_len = 0;
	gpio_configure_pin(in_pin,
		GPIO_DIR_IN | GPIO_TYPE_DIGITAL | GPIO_CALLBACK);
	hooks
}

void ir_initialize_bidir(IrDecoderStruct* irds, uint16_t in_pin, uint16_t out_pin, uint16_t pulse_iv) {
	irds->in_pin = in_pin;
	irds->out_pin = out_pin;
	irds->pulse_iv = pulse_iv;
	irds->pulse_len = 0;
	gpio_configure_pin(in_pin,
		GPIO_DIR_IN | GPIO_TYPE_DIGITAL);
	gpio_configure_pin(out_pin,
		GPIO_DIR_OUT | GPIO_TYPE_DIGITAL);
	hooks_assign(irds->in_pin, HOOKS_TRIGGER_RISING | HOOKS_TRIGGER_FALLING, &_ir_inthandler);
}

void ir_calibrate(IrDecoderStruct* irds) {
	uint16_t calvals;
	uint16_t tick;
	irds->pulse_len = 0xFFFF;
	while(true) {
		// If we read a binary one on the input pin we move on with the
		// calibrationprocedure.
		if (gpio_read(irds->in_pin)) {
			// First, we check if we can increase the silence
			// threshold. Hold the button on the IR for this
			// to work.
			if (tick > irds->silence) irds->silence = tick;
			// If the current number of elapsed cycles is lower
			// than the current lowest value or
			if ((tick > IR_THRESHOLD_LOW) && (tick < irds->pulse_iv)) {
				// Store the new values and reset the counter
				irds->pulse_iv = tick;
				calvals++;
			}
			tick = 0;
		}
		tick++;
		if (calvals > IR_CALIBRATION_HITS) {
			irds->silence = irds->silence * 0.7;
			return;
		}
	}
}

uint8_t ir_receive_packet(IrDecoderStruct* irds) {
	uint16_t calvals;
	uint16_t tick;
	while(tick < irds->pulse_silence) {
		if (gpio_read(irds->in_pin)) {
			if ((tick > IR_THRESHOLD_LOW) && (tick < irds->pulse_iv)) {
				irds->pulse_iv = tick;
				tick = 0;
				calvals++;
			}
		}
		tick++;
		if (calvals > IR_CALIBRATION_HITS) return;
	};
}

void ir_send_byte(IrDecoderStruct* irds, uint8_t byte) {
	for (n = 0; n < 8; n++) {
		gpio_write(irds->out_pin,byte & 1);
		sleep(irds->pulse_len
	}
}

void _ir_inthandler() {
	
}
