/**
 *
 * Half Duplex Software UART on the LaunchPad
 *
 * This code provides a simple Bi-Directional Half Duplex Software UART. The
 * timing is dependant on SMCLK, which is set to 1MHz. The transmit function
 * is based off of the example code provided by TI with the LaunchPad. This
 * code was originally created for "NJC's MSP430 LaunchPad Blog".
 *
 * The code has been highly modified to allow it to be compiled separately and
 * be reused in other projects.
 *
 * Do note that this code hooks the TIMER0 A0 interrupt as well as the PORT1
 * interrupt, and requires global interrupts to be enabled. This is done by
 * the suart_init() method.
 *
 * @author Nicholas J. Conn - http://msp430launchpad.com @08-17-10
 * @author Christopher V - http://noccylabs.info @10-19-11
 * @license GNU General Public License (GPL) V2 or later
 *
 */

#ifndef __SUART_H__
#define __SUART_H__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <msp430.h>
#include <legacymsp430.h>
#include "fifo.h"

#define TXD BIT1 // TXD on P1.1
#define RXD BIT2 // RXD on P1.2

#define Bit_time 104 // 9600 Baud, SMCLK=1MHz (1MHz/9600)=104
#define Bit_time_5 52 // Time for half a bit.

// Methods, putchar is implemented here to support printf()
int putchar(int character);
void suart_flush();
void suart_init(FIFO* inq, FIFO* outq, HAL_MAP drecv, HAL_MAP dsend);
void suart_transmit(unsigned int byte);
bool suart_datawaiting();
unsigned char suart_receive();

// Hooked interrupt vectors
interrupt(PORT1_VECTOR) PORT1_ISR(void);
interrupt(TIMER0_A0_VECTOR) TIMERA0_ISR(void);

#endif
