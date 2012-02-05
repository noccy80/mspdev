/**
 * usci_serial.cpp - simple example using USCI UART + ringbuffer + command line monitor
 *
 * This code was written to test the new uniarch version of msp430-gcc. I wanted
 * to make sure it could generate code for the msp430g2553 running on the TI
 * launchpad.
 *
 * This code mplements a command line interface over the USB-CDC serial at
 * 9600-8-N-1. To test you must swap the RX/TX pins on your launchpad to use
 * the hardware USCI UART.  I disconnected those jumpers on my launchpad and used
 * a couple of F-M jumper wires to run the msp430g2553 from a breadboard.
 * P1.1=RXD and P1.2=TXD ( this is the opposite of the msp430g2231 default setup )
 *
 * * License: Do with this code what you want. However, don't blame
 * me if you connect it to a heart pump and it stops.  This source
 * is provided as is with no warranties. It probably has bugs!!
 * You have been warned!
 *
 * Author: Rick Kimball
 * email: rick@kimballsoftware.com
 * Version: 1.00 Initial version 05-12-2011
 */

#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>
#include "config.h"
#include "ringbuffer.h"
#include "usci.h"

/**
 *  create a ring buffer that holds up to 16 uint8_t bytes
 *
 *  Note: you could change the ringbuffer_ui8_16 typedef to
 *  make it smaller or larger, just be consistent with what
 *  you provide the Serial template
 */

ringbuffer_ui8_16 usci_buffer = { 0, 0, { 0 } };

Serial<ringbuffer_ui8_16> usci0 = { usci_buffer };

/**
 * USCI0RX_ISR - USCI UART receive character ISR handler
 *
 * we get an interrupt when a new character arrives via
 * the USCI UART receive pin. We just stuff it into
 * our buffer and let the main routine consume it.
 */

interrupt(USCIAB0RX_VECTOR) USCI0RX_ISR(void) {
    /**
     * Note: a side effect of reading UCA0RXBUF
     * is the rx interrupt flag is cleared
     */

    usci_buffer.push_back(UCA0RXBUF);
}

/**
 * main - echo back to the user whatever they type
 */
int usci_main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT

    BCSCTL1 = CALBC1_16MHZ; // set DCO clock for MCLK and SMCLK
    DCOCTL = CALDCO_16MHZ;

    usci0.init();

    __bis_SR_register(GIE); // interrupts enabled

    usci0.xmit("\r\nMSP430G2553 Monitor\r\n$ ");

    while (true) {
        while (!usci0.empty()) {
            volatile int c;

            c = usci0.recv();
            usci0.xmit((uint8_t) c);
        }
    }
    
    return 0;
}

int putchar(int character) {
	usci0.xmit(character);
	return 1;
}

