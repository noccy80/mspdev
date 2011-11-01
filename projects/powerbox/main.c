/**
 * 
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */
 
#include <msp430.h>
#include <legacymsp430.h>
#include "utils.h"

// Input, the buttons we are using
#define BTN_POWER    BIT4   // port1.4 is power button
#define BTN_RESET    BIT5   // port1.5 is reset button

// Outputs for leds on port1
#define LED_STATUS   BIT0 // port1.0 is our status led
#define LED_POWER    BIT1 // port1.1 is our power led
#define LED_ERROR    BIT2 // port1.2 is our error led
// NOTE: These are on port2
#define LED_LINE1    BIT3 // port2.3 is the status led for line1
#define LED_LINE2    BIT4 // port2.4 is the status led for line2

// Output for power control
#define CTL_LINE1    BIT0 // port2.0 is control for line1 +5/+12V
#define CTL_LINE2    BIT1 // port2.1 is control for line2 +5/+12V

// Power state definitions
#define STA_OFF 0
#define STA_ON 1
#define STA_ERROR 2

#define LIN_OFF 0 // Line is off
#define LIN_5V 1 // Line is at +5V
#define LIN_12V 2 // Line is at +12V

int main(void) {

	// Halt the watchdog timer - According to the datasheet the watchdog timer
	// starts automatically after powerup. It must be configured or halted at
	// the beginning of code execution to avoid a system reset. Furthermore,
	// the watchdog timer register (WDTCTL) is password protected, and requires
	// the upper byte during write operations to be 0x5A, which is the value
	// associated with WDTPW.
	WDTCTL = WDTPW + WDTHOLD;

	// Select the direction of the pins, we want to make the leds outputs and
	// the TSOP pin input
	P1DIR |= LED_POWER + LED_STATUS + LED_ERROR;
	P2DIR |= CTL_LINE1 + CTL_LINE2;
	P1DIR &= ~(BTN_POWER + BTN_RESET);

	// Enable interrupts, and set the interrupt to be triggered on the falling
	// edge since the TSOP1738 is normal low.
	P1IE |= BTN_POWER + BTN_RESET; 
	P1IES |= ~(BTN_POWER + BTN_RESET); // Rising
	
	// Light up the status led to show that we are alive.
	P1OUT |= LED_POWER;
	
	// Finally, enable global interrupts
	__bis_SR_register(GIE);

	while(1) {
		//Loop forever, interrupts take care of the rest
	}

}

// This is our ISR for the port1 interrupt
interrupt(PORT1_VECTOR) port1_isr(void) {

	// Light the trigger led
	P1OUT |= LED_POWER;
	// Clear the interrupt flag
	P1IFG &= ~(BTN_POWER + BTN_RESET);
	// Munch some cycles
	__delay_cycles(150);
	// And reset the trigger led
	P1OUT &= ~LED_POWER;

}
