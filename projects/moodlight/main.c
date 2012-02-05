/**
 * @file main.c
 * @brief msp430 Mood Lamp
 *
 * This is a working demo, but also work in progress. The final version of this
 * tool will be able to read input from three photoresistors to produce a
 * matching colors.
 *
 * This was all really written as a proof-of-concept that you can use simple
 * and cheap photoresistors with colored filters to construct a mood light
 * that adjusts its color from the ambient color in the environment. Whether
 * this works remains to be seen.
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU GPL Version 3
 */

// Our includes
#include <msp430.h>
#include <legacymsp430.h>

// This is the main "sketch", if we are to borrow the words from the aurduino.
#define ARDUINO_MAIN
#include <arduino.h>

// Output pins
#define OUT_RED 2
#define OUT_GREEN 3
#define OUT_BLUE 1
// Input pins, for reading and adc
#define IN_RED 5
#define IN_GREEN 6
#define IN_BLUE 7

// Max is a bad name, but this is how many intensity levels exist
#define max 10

// Volatile variables to store the red, green and blue values.
volatile int red_val = 0;
volatile int green_val = 0;
volatile int blue_val = 0;

/**
 * @brief Arduino style setup routine
 *
 * Sets the direction of the pins and initializes them to a known state.
 */
void setup() {

	pinMode(OUT_RED, OUTPUT);
	pinMode(OUT_GREEN, OUTPUT);
	pinMode(OUT_BLUE, OUTPUT);
	digitalWrite(OUT_RED, HIGH);
	digitalWrite(OUT_GREEN, HIGH);
	digitalWrite(OUT_BLUE, HIGH);

	pinMode(IN_RED, INPUT);
	pinMode(IN_GREEN, INPUT);
	pinMode(IN_BLUE, INPUT);

	//Set ACLK to use internal VLO (12 kHz clock)
	BCSCTL3 |= LFXT1S_2;

	//Set TimerA to use auxiliary clock in UP mode
	TACTL = TASSEL_1 | MC_1;
	//Enable the interrupt for TACCR0 match
	TACCTL0 = CCIE;

	// Set TACCR0 which also starts the timer. At 12 kHz, counting to 12000
	// should output an LED change every 1 second. Try this out and see how
	// inaccurate the VLO can be
	TACCR0 = 5;

	//Enable global interrupts
	WRITE_SR(GIE);

}

/**
 * @brief Update the displayed color
 *
 * Will assign the red green and blue value to the volatile variables
 *
 * @param int r The red value
 * @param int g The green value
 * @param int b The blue value
 */
void set_color(int r, int g, int b) {
	red_val = r;
	green_val = g;
	blue_val = b;
}

/**
 * @brief Future loop reading input from photoresistors
 *
 * The photoresistors should be covered with colored filters.
 * The red input should be covered with blue and green filters,
 * The green input should be covered with red and blue filters
 * and the blue input should be covered with red and green
 * filters.
 *
void loop2() {

	int r, g, b;
	r = analogRead(IN_RED);
	g = analogRead(IN_GREEN);
	b = analogRead(IN_BLUE);

	// This is bogus, the value should be scaled properly!
	set_color(r/10, g/10, b/10);

}

/**
 * @brief The main loop
 *
 * Currently runs through a demo program
 */
void loop() {
	demo();
}

/**
 * @brief Demo program
 *
 * Fades through a preset pattern
 */
void demo() {

	// Our counter
	int n;
	// The delay constant
	int delay = 1000;
	// Multipliers for each step (a) and between changes (b).
	// Note that multiplier a is used TWICE, so set it accordingly.
	int mula = 5;
	int mulb = 20;

	while(1) {

		// Green to Red
		for (n = 0; n < max; n++) {
			set_color(n,max - n,0);
			__delay_cycles(delay * mula);
			__delay_cycles(delay * mula);
		}
		__delay_cycles(delay * mulb);

		// Red to Blue
		for (n = 0; n < max; n++) {
			set_color(max - n, 0, n);
			__delay_cycles(delay * mula);
			__delay_cycles(delay * mula);
		}
		__delay_cycles(delay * mulb);

		// Blue to White
		for (n = 0; n < max; n++) {
			set_color(n, n, max);
			__delay_cycles(delay * mula);
			__delay_cycles(delay * mula);
		}
		__delay_cycles(delay * mulb);

		// White to Yellow
		for (n = 0; n <max; n++) {
			set_color(max, max, max - n);
			__delay_cycles(delay * mula);
			__delay_cycles(delay * mula);
		}
		__delay_cycles(delay * mulb);

		// Yellow to Cyan
		for (n = 0; n < max; n++) {
			set_color(0, max, n);
			__delay_cycles(delay * mula);
			__delay_cycles(delay * mula);
		}
		__delay_cycles(delay * mulb);

		// Cyan to Purple
		for (n = 0; n < max; n++) {
			set_color(n, max - n, max);
			__delay_cycles(delay * mula);
			__delay_cycles(delay * mula);
		}
		__delay_cycles(delay * mulb);

		// Purple to green
		for (n = 0; n < max; n++) {
			set_color(max - n, n, max -n);
			__delay_cycles(delay * mula);
			__delay_cycles(delay * mula);
		}
		__delay_cycles(delay * mulb);

	}

}

/**
 * @brief ISR for TIMER0_A0, does the pwm stuff.
 *
 */
interrupt(TIMER0_A0_VECTOR) timer_isr(void) {

	int step;
	for (step = 1; step < 11; step++) {
		digitalWrite(OUT_RED,(red_val>step)?LOW:HIGH);
		digitalWrite(OUT_GREEN,(green_val>step)?LOW:HIGH);
		digitalWrite(OUT_BLUE,(blue_val>step)?LOW:HIGH);
		__delay_cycles(10);
	}

}
