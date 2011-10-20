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
#include "ta0compat.h"

#define  LED0      BIT0
#define  LED1      BIT6
#define  LED_DIR   P1DIR
#define  LED_OUT   P1OUT

unsigned char twink = 0;

void initLEDs(void) {

	LED_DIR |= LED0 + LED1;	//Set LED pins as outputs
	LED_OUT |= LED0 + LED1;	//Turn on both LEDs

}

int main(void) {

	// Halt the watchdog timer - According to the datasheet the watchdog timer
	// starts automatically after powerup. It must be configured or halted at
	// the beginning of code execution to avoid a system reset. Furthermore,
	// the watchdog timer register (WDTCTL) is password protected, and requires
	// the upper byte during write operations to be 0x5A, which is the value
	// associated with WDTPW.
	WDTCTL = WDTPW + WDTHOLD;

	//Setup LEDs
	initLEDs();

	//Set ACLK to use internal VLO (12 kHz clock)
	BCSCTL3 |= LFXT1S_2;

	//Set TimerA to use auxiliary clock in UP mode
	TACTL = TASSEL_1 | MC_1;
	//Enable the interrupt for TACCR0 match
	TACCTL0 = CCIE;

	// Set TACCR0 which also starts the timer. At 12 kHz, counting to 12000
	// should output an LED change every 1 second. Try this out and see how
	// inaccurate the VLO can be 
	TACCR0 = 3000;

	//Enable global interrupts
	WRITE_SR(GIE);

	while(1) {
		//Loop forever, interrupts take care of the rest
	}

}

// Interrupt Service Routine for Timer A0. We need to use preprocessor
// directives in order to place the interrupt at the correct address for
// the current mcu.
#ifdef TIMER0_A0_VECTOR
interrupt(TIMER0_A0_VECTOR) TIMERA0_ISR(void) {
#else
interrupt(TIMERA0_VECTOR) TIMERA0_ISR(void) {
#endif
	twink = !twink;
	LED_OUT = (twink)?LED0:LED1;

}


