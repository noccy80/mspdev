#include "relay.h"
#include <msp430.h>
#include "pins.h"

void relaySetState(int state) {

    if (state == 1) {
        // Turn off the alert led and activate the relay
        PORT_ALERTLED &= ~BIT_ALERTLED;
        PORT_RELAYCTL |= BIT_RELAYCTL;
    } else {
        PORT_ALERTLED |= BIT_ALERTLED;
        PORT_RELAYCTL &= ~BIT_RELAYCTL;
    }

}

