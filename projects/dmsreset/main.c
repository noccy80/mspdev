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
#include "relay.h"
#include "pins.h"

int state = 0;
int laststate = 0;
int is_alert = 0;
volatile int alert_cycles = 0;
volatile int resetting = 0;

int main(void) {

    // Halt the watchdog timer - According to the datasheet the watchdog timer
    // starts automatically after powerup. It must be configured or halted at
    // the beginning of code execution to avoid a system reset. Furthermore,
    // the watchdog timer register (WDTCTL) is password protected, and requires
    // the upper byte during write operations to be 0x5A, which is the value
    // associated with WDTPW.
    WDTCTL = WDTPW + WDTHOLD;

    // Initialize clock to 8MHz DCO
    BCSCTL1 = CALBC1_8MHZ;    // Set range
    DCOCTL = CALDCO_8MHZ;     // Set DCO step + modulation

    //Set ACLK to use internal VLO (12 kHz clock)
    BCSCTL3 |= LFXT1S_2;

    //Set TimerA to use auxiliary clock in UP mode
    TACTL = TASSEL_1 | MC_1;
    TACCTL0 = CCIE;

    // Set TACCR0 which also starts the timer. At 12 kHz, counting to 12000
    // should output an LED change every 1 second. Try this out and see how
    // inaccurate the VLO can be
    TACCR0 = 12000;

    //Enable global interrupts
    WRITE_SR(GIE);
        relaySetState(1);

    // We just keep reading. Not efficient but effective.
    while(1) {
        // Read GPIO from device power led
        state = (PORT_SENSE & BIT_SENSE)?1:0;
        // If the state does toggle, reset TACCR0
        if (state != laststate) {
            laststate = state;
            if ((is_alert) && (!resetting)) {
                relaySetState(1);
                is_alert = 0;
                alert_cycles = 0;
            }
        }
        // Reflect the state of the power led
        if (state) {
            PORT_STATUSLED |= BIT_STATUSLED;
        } else {
            PORT_STATUSLED &= ~BIT_STATUSLED;
        }
    }

}

// Interrupt Service Routine for Timer A0. We need to use preprocessor
// directives in order to place the interrupt at the correct address for
// the current mcu.
interrupt(TIMER0_A0_VECTOR) TIMERA0_ISR(void) {

    // increase the alert cycles
    alert_cycles++;
    PORT_ALERTLED |= BIT_ALERTLED;

    if (alert_cycles > 15) {
        resetting = 0;
        PORT_STATUSLED &= ~BIT_STATUSLED;
        relaySetState(1);
        alert_cycles = 0;
    } else if (alert_cycles > 10) {
        resetting = 1;
        relaySetState(0);
        P1OUT |= BIT1;
    } 

}


