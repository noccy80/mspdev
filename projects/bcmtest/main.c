/**
 * Binary Code Modulation (BCM) test, will pulse the LEDs on the Launchpad
 * at levels between 0 and 255, giving 256 levels of brightness.
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */

#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>

#define  LED0      BIT0
#define  LED1      BIT6
#define  LED_DIR   P1DIR
#define  LED_OUT   P1OUT

// Timeslice (0 to 7), to be incremented by the interrupt vector
volatile unsigned char slice = 0;
// Delay, or more precisely how many interrupts to skip
volatile unsigned char delay = 0; 

volatile unsigned char state = 0;

const unsigned char slicemask[] = { BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7 };
const unsigned char slicedelay[] = { 0, 1, 2, 4, 8, 16, 32, 64 };

void init_leds(void) {

	LED_DIR |= LED0 + LED1;	//Set LED pins as outputs
	LED_OUT &= ~(LED0 + LED1);	//Turn off both LEDs

}

int main(void) {

	unsigned char dir = 0;
	unsigned char trig = 0;

	// Halt the watchdog timer - According to the datasheet the watchdog timer
	// starts automatically after powerup. It must be configured or halted at
	// the beginning of code execution to avoid a system reset. Furthermore,
	// the watchdog timer register (WDTCTL) is password protected, and requires
	// the upper byte during write operations to be 0x5A, which is the value
	// associated with WDTPW.
	WDTCTL = WDTPW + WDTHOLD;

	init_leds();

	//Set ACLK to use internal VLO (12 kHz clock)
	BCSCTL3 |= LFXT1S_2;

	//Set TimerA to use auxiliary clock in UP mode
	TACTL = TASSEL_1 | MC_1;
	//Enable the interrupt for TACCR0 match
	TACCTL0 = CCIE;

	// Set TACCR0 which also starts the timer. At 12 kHz, counting to 12000
	// should output an LED change every 1 second. Try this out and see how
	// inaccurate the VLO can be
	TACCR0 = 1;

	//Enable global interrupts
	WRITE_SR(GIE);
	
	while(1) {

		/*
		if (!(P1IN & BIT3)) {
			LED_OUT |= LED1;
			trig = 1;
		} else {
			LED_OUT &= ~LED1;
			if (trig == 1) {
				state++;
				if (state == 255) state = 0;
			}
			trig = 0;
		}
		*/
		if (dir == 0) {
			state++;
			if (state == 15) dir = 1;
		} else {
			state--;
			if (state == 0) dir = 0;
		}
		
		__delay_cycles(20000);
		__delay_cycles(20000);
		__delay_cycles(20000);
		__delay_cycles(20000);
	}

}

interrupt(TIMER0_A0_VECTOR) timer0_isr(void) {

	static unsigned char in_isr = 0;
	if (in_isr) return;
	in_isr = 1;

	if (delay == 0) {
		slice++;
		if (slice > 4) slice = 0;
		delay = slicedelay[slice];

		if (state & slicemask[slice]) {
			LED_OUT |= LED0;
		} else {
			LED_OUT &= ~LED0;
		}

	} else {
		delay--;
	}
	in_isr = 0;

}
