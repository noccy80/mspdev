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

#ifndef __MSP430_HAS_USCI__
#warning Device does not have USCI! Emulation will be used!
#endif

void i2c_begin(unsigned char addr);
void i2c_end();
void i2c_send(const char* data, unsigned char datalen);
void i2c_receive(const char* buffer, unsigned char* datalen);

#endif // __i2c_h__
