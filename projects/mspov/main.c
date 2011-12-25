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

#define  LED_DIR   P1DIR
#define  LED_OUT   P1OUT

#include "font.h"

unsigned char blank = 0;
unsigned char step = 0;

// The message to display 
const char message[] = "HELLO WORLD!\0";

void initLEDs(void) {

	LED_DIR = 0xFF;
	LED_OUT = 0x00;

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
	TACCR0 = 300;

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
	static unsigned char stepchar = 0;
	blank = !blank;
	if (!blank) {
		stepchar = message[step];
		if (stepchar == 0) {
			LED_OUT = 0;
			step = 0;
		} else {
			LED_OUT = System5x7[((stepchar - FONTOFFSET) * FONTWIDTH) + step];
			step++;
		}
	} else {
		// Blank every 2nd step
		LED_OUT = 0;
	}

}


