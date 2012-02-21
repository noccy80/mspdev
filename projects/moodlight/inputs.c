#include <legacymsp430.h>
#include "moodlight.h"
#include "inputs.h"
#define MAX_PROGRAMS 6

#define IN_MENU_DOWN 1
#define IN_MENU_UP 2
#define IN_MENU_PROGRAM 4
#define IN_MENU_POWER 8

void inputs_init() {
	int pins = IN_MENU_UP|IN_MENU_DOWN|IN_MENU_PROGRAM|IN_MENU_POWER;
	P2SEL &= ~pins; // IO funct
	P2SEL2 &= ~pins; // IO Funct
	P2DIR &= ~pins;	// Direction: In
	P2REN |= pins; // Resistors enable
	P2IES |= pins; // Falling edge
	P2IE |= pins; // Enable interrupts
	P2IFG = 0; // Clear interrupt flag
}

interrupt(PORT2_VECTOR) input_isr(void) {
	static int delaybase = 5;
	static int power = 0;
	if (P2IFG & IN_MENU_DOWN) {
		delaybase--;
		if (delaybase<1) delaybase = 1;
		set_delay(delaybase);
	}
	if (P2IFG & IN_MENU_UP) {
		delaybase++;
		if (delaybase>20) delaybase = 20;
		set_delay(delaybase);
	}
	if (P2IFG & IN_MENU_PROGRAM) {
		override_color(0,0,30);
	}
	if (P2IFG & IN_MENU_POWER) {
		power = !power;
		set_power_mode(power);
	}
	P2IFG = 0;
}
