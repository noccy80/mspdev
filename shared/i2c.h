/**
 * I2C Communication Routines
 *
 * This module is to deliver I2C support using the on-chip serial communication
 * modules.
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */

#ifndef __i2c_h__
#define __i2c_h__

#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>

#ifndef __MSP430_HAS_USCI__
#warning Device does not have USCI! Emulation will be used!
#endif

typedef struct i2c_init_struct {
	uint16_t clk_port;
	uint8_t clk_pin;
	uint16_t sda_port;
	uint8_t sda_pin;
	void (*cbfunc) (char*,int);
} I2C_INIT_STRUCT;

void i2c_master_init(I2C_INIT_STRUCT* init_struct);
void i2c_slave_init(unsigned char addr);

void i2c_send(unsigned char addr, const char* data, unsigned char datalen);
void i2c_receive(unsigned char addr, const char* buffer, unsigned char* datalen);

#endif // __i2c_h__
