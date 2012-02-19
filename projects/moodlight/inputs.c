#include <legacymsp430.h>
#include "moodlight.h"
#include "inputs.h"
#define MAX_PROGRAMS 6

#define IN_MENU_DOWN 1
#define IN_MENU_UP 2

void inputs_init() {
	int pins = BIT1|BIT2;
	P2REN |= pins; // Resistors enable
	P2SEL &= ~pins; // IO funct
	P2SEL2 &= ~pins; // IO Funct
	P2DIR &= ~pins;	// Direction: In
	P2IES |= pins; // Falling edge
	P2IE |= pins; // Enable interrupts
	P2IFG = pins; // Clear interrupt flag
}

interrupt(PORT2_VECTOR) input_isr(void) {
	static int delaybase = 5;
	if (P2IFG & IN_MENU_DOWN) {
		delaybase--;
		if (delaybase<1) delaybase = 1;
		set_delay(delaybase);
		P1IFG &= ~IN_MENU_DOWN;
	}
	if (P2IFG & IN_MENU_UP) {
		delaybase++;
		if (delaybase>20) delaybase = 20;
		set_delay(delaybase);
		P1IFG &= ~IN_MENU_UP;
	}
}
