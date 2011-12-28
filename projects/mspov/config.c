/**
 * MSP430 Persistence of Visition Display
 *
 * This is a simple POV display for the MSP430, capable of outputting text (for
 * now at least) in any direction. It can be extended with a tilt sensor to
 * change the direction.
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */

#include <msp430.h>
#include <legacymsp430.h>
#include "config.h"

#define BTN_DIR P2DIR
#define BTN_IN P2IN

#define LED_MENU BIT0
#define SENSE_DATA BIT3
#define SENSE_CLOCK BIT4
#define BTN_MENU BIT1
#define BTN_NEXT BIT2

/**
 * @brief UI initialization.
 *
 * This will set the interrupt enable and interrupt edge for the UI to work.
 *
 *
 */
void ui_initialize(void) { }

/**
 *
 *
 *
 */
void ui_menumode(void) {
	P2OUT |= LED_MENU; // Light up the green led
	
}

/**
 * @brief Interrupt handler for PORT2.
 *
 * As port2 is very flexible (it holds a led, as well as two buttons, not to
 * forget the IR programmer pins. Both of them.
 *
 * Initially it will be set to trigger on interrupts on the rising edge of the
 * trigger. We then record the duration of the key being pressed and set the
 * interrupts on the falling edge. That way we can cause events to be time-
 * based such as holding a button. This is volatile since it has to be checked
 * by the timer maintenance interrupt.
 *
 *
 */
interrupt(PORT2_VECTOR) PORT2_ISR(void) {

	int source = 0;
	
	// Detect the edge as appropriate. After push event, make trigger on falling
	// edge.

	// Determine what caused the interrupt
	switch(source) {
		case BTN_MENU:
			// Enter menu mode
			break;
		case BTN_NEXT:
			// Go to next mode or next menu item
			break;
	}

}


