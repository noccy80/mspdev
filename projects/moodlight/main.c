/**
 * @file main.c
 * @brief msp430 Mood Lamp
 *
 * This is a working demo, but also work in progress. The final version of this
 * tool will be able to read input from three photoresistors to produce a
 * matching colors.
 *
 * It is set to support 262144 colors with 64 intensities for each of the
 * primaries red, green and blue. This can be tweaked with the max constant
 * below.
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
#include "bcd.h"
#include "moodlight.h"
#include "inputs.h"

// This is the main "sketch", if we are to borrow the words from the aurduino.
#define ARDUINO_MAIN
#include <arduino.h>

// Output pins
#define OUT_RED 2
#define OUT_GREEN 1
#define OUT_BLUE 3

volatile int ovr_on = 0;
volatile int ovr_red = 0;
volatile int ovr_green = 0;
volatile int ovr_blue = 0;
int power = 0;

// Max is a bad name, but this is how many intensity levels exist
const int max = 64;

// Volatile variables to store the red, green and blue values.
volatile int red_val = 0;
volatile int green_val = 0;
volatile int blue_val = 0;

volatile int display = 0;
volatile int global_program = 0;
volatile int delay_base = 30;

// Function prototypes
void demo();
void ambient();

void set_color(int r, int g, int b);


void set_power_mode(int powermode) {
	power = powermode;
	if (!power) {
		digitalWrite(OUT_RED, LOW);
		digitalWrite(OUT_GREEN, LOW);
		digitalWrite(OUT_BLUE, LOW);
		TACCTL0 = ~CCIE;
	} else {
		//Set ACLK to use internal VLO (12 kHz clock)
		BCSCTL3 |= LFXT1S_2;

		//Set TimerA to use auxiliary clock in UP mode
		TACTL = TASSEL_1 | MC_1;
		//Enable the interrupt for TACCR0 match
		TACCTL0 = CCIE;

		// Set TACCR0 which also starts the timer. At 12 kHz, counting to 12000
		// should output an LED change every 1 second. Try this out and see how
		// inaccurate the VLO can be
		TACCR0 = 2;
	}
}

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

	//pinMode(IN_RED, INPUT);
	//pinMode(IN_GREEN, INPUT);
	//pinMode(IN_BLUE, INPUT);

	set_power_mode(1);
	inputs_init();

	//Enable global interrupts
	WRITE_SR(GIE);

}

void override_color(int r, int g, int b) {
	ovr_on = 100;
	ovr_red = r;
	ovr_green = g;
	ovr_blue = b;
	set_color(r, g, b);
}

void set_program(int program) {
	global_program = program;
}

void set_delay(int delaybase) {
	delay_base = delaybase;

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
	if (ovr_on-- > 0) {
		red_val = ovr_red;
		green_val = ovr_green;
		blue_val = ovr_blue;
		return;
	}
	red_val = r;
	green_val = g;
	blue_val = b;
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
 * @brief Future loop reading input from photoresistors
 *
 * The photoresistors should be covered with colored filters.
 * The red input should be covered with blue and green filters,
 * The green input should be covered with red and blue filters
 * and the blue input should be covered with red and green
 * filters.
 */
void ambient() {

	int r, g, b;
	r = analogRead(9);
	g = analogRead(10);
	b = analogRead(11);

	// This is bogus, the value should be scaled properly!
	set_color(r/10, g/10, b/10);

}

/**
 * @brief Demo program
 *
 * Fades through a preset pattern
 */
void demo() {

	// Our counter
	int n, m, i;
	// Multipliers for each step (a) and between changes (b).
	// Note that multiplier a is used TWICE, so set it accordingly.
	int delaya = 500;
	int delayb = 30000;

	display = 0;

	while(1) {

		// Green to Red
		for (m = 0; m < 6; m++) {
			for (n = 0; n < max; n++) {
				switch(m) {
					case 0:
						set_color(n,0,0); break;
					case 1:
						set_color(max,n,0); break;
					case 2:
						set_color(max-n,max,0); break;
					case 3:
						set_color(0,max -n,n); break;
					case 4:
						set_color(n,0,max); break;
					case 5:
						set_color(max - n,0,max -n); break;
				}
				for (i = 0; i < delay_base; i++) __delay_cycles(delaya);
			}
			for (i = 0; i < delay_base; i++) __delay_cycles(delayb);
		}

	}

}


/**
 * @brief ISR for TIMER0_A0, does the pwm stuff.
 *
 */
interrupt(TIMER0_A0_VECTOR) timer_isr(void) {

	static int step = 0;
	P1OUT = 0xFF;
	digitalWrite(OUT_RED,(step<red_val)?HIGH:LOW);
	digitalWrite(OUT_GREEN,(step<green_val)?HIGH:LOW);
	digitalWrite(OUT_BLUE,(step<blue_val)?HIGH:LOW);
	step++;
	if (step>max) step = 0;

}
