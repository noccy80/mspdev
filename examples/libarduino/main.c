/**
 * Blink example for MSP430
 *
 * Snatched from hackaday.com and rewritten to compile for a number of
 * different MCUs in the MSP430 series.
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */

#include <msp430.h>
#include <legacymsp430.h>
#define ARDUINO_MAIN
#include <arduino.h>

#define  LED0      0
#define  LED1      6

volatile unsigned char twink = 0;

void setup(void) {

	pinMode(LED0,OUTPUT);
	digitalWrite(LED0,HIGH);
	delay(2000);

}

void loop(void) {

	pinMode(LED1,OUTPUT);
	digitalWrite(LED0,LOW);
	digitalWrite(LED1,HIGH);
	delay(1000);
	digitalWrite(LED1,LOW);
	delay(1000);

}

