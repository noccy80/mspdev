/**
 * Reads and decodes signals from an infra-red remote controller via a TSOP1738
 * IC. Pulses are detected via port1 interrupts, and timer a0 is used to count
 * the elapsed duration between the pulses.
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */
 
#include <msp430.h>
#include <legacymsp430.h>

// Input, this is the signal from the TSOP1738 IC
#define IN_TRIG BIT4 // port1.4 is input

// Outputs, this is led 1 and 2 on the Launchpad
#define LED_STAT BIT6 // port1.0 is our trigger led
#define LED_TRIG BIT0 // port1.6 is our status led

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
	P1DIR |= LED_TRIG + LED_STAT;
	P1DIR &= ~IN_TRIG;

	// Enable interrupts, and set the interrupt to be triggered on the falling
	// edge since the TSOP1738 is normal low.
	P1IE |= IN_TRIG; 
	P1IES |= IN_TRIG; // Falling edge
	
	// Light up the status led to show that we are alive.
	P1OUT = LED_STAT;
	
	// Finally, enable global interrupts
	__bis_SR_register(GIE);

	while(1) {
		//Loop forever, interrupts take care of the rest
	}

}

// This is our ISR for the port1 interrupt
interrupt(PORT1_VECTOR) port1_isr(void) {

	// Light the trigger led
	P1OUT |= LED_TRIG;
	// Clear the interrupt flag
	P1IFG &= ~IN_TRIG;
	// Munch some cycles
	__delay_cycles(150);
	// And reset the trigger led
	P1OUT &= ~LED_TRIG;

}
