#include "i2c.h"

void i2c_master_init(I2C_INIT_STRUCT* init_struct) {
	// Initialize clock pin 
	uint8_t clkport = init_struct->clk_port;
	clkport |= init_struct->clk_pin;

}
void i2c_slave_init(unsigned char addr) { }

void i2c_send(unsigned char addr, const char* data, unsigned char datalen) { }
void i2c_receive(unsigned char addr, const char* buffer, unsigned char* datalen) { }

