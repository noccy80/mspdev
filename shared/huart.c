#include "huart.h"

// Receive buffer. It is implemented as a ring buffer of the specified size.
// Any write operations to the buffer will wrap around at the end of the buffer
// and restart from the beginning. If the write buffer stretch across the read
// buffer we have a buffer overflow. Any read operation will also wrap around
// in a similar fashion. When the read and write buffer point to the same
// index the len should be 0.
volatile unsigned char huart_rcvbuf[HUART_RCVBUFSIZE]; // Size of receive buffer
volatile unsigned char huart_rcvbufrptr = 0; 
volatile unsigned char huart_rcvbufwptr = 0; 
volatile unsigned char huart_rcvbuflen = 0;

/**
 * @brief Transmit a character in a blocking fashion.
 *
 * @param int character The character to write
 */
int putchar(int character) {

	huart_transmit(character);
	return 1;

}

/**
 *
 *
 */
void huart_transmit(unsigned int c) {

	// USCI_A0 TX buffer ready?
	while (!(IFG2&UCA0TXIFG)); 
	UCA0TXBUF = c; 
	
}

/**
 *
 *
 */
void huart_init(void) {

	P1SEL |= (BIT1 + BIT2); // P1.1 = RXD, P1.2=TXD
	P1SEL2 |= (BIT1 + BIT2); // P1.1 = RXD, P1.2=TXD

	UCA0CTL1 |= UCSSEL_2; // SMCLK

	// UCOS16 = 1
	// 8,000,000Hz, 9600Baud, UCBRx=52, UCBRSx=0, UCBRFx=1
	UCA0BR0 = 52; // 8MHz, OSC16, 9600
	UCA0BR1 = 0; // 8MHz, OSC16, 9600
	// UCA0MCTL = UCBRFx | UCBRSx | UCOS16
	UCA0MCTL = 0x10|UCOS16; // UCBRFx=1,UCBRSx=0, UCOS16=1
	UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**

	// Enable USCI_A0 RX interrupt
	IE2 |= UCA0RXIE;

}

/**
 *
 *
 */
bool huart_datawaiting(void) {

	return (huart_rcvbuflen != 0);

}

/**
 *
 *
 */
unsigned char huart_receive(void) {

	unsigned char c;

	if (huart_rcvbuflen > 0) {
		// If there is a byte in the buffer, pop it off
		c = huart_rcvbuf[huart_rcvbufrptr];
		huart_rcvbufrptr = (huart_rcvbufrptr + 1) % HUART_RCVBUFSIZE;
		huart_rcvbuflen--;
	} else {
		// Return 0 if no byte in buffer
		c = 0;
	}
	
	return c;

}

/**
 *
 *
 */
interrupt(USCIAB0RX_VECTOR) USCI0RX_ISR(void) {

	unsigned char c;
	c = UCA0RXBUF;
	
	// Receive the byte and push it on the buffer
	huart_rcvbuf[huart_rcvbufwptr] = c;
	huart_rcvbufwptr = (huart_rcvbufwptr + 1) % HUART_RCVBUFSIZE;
	
	// Increment buffer length
	huart_rcvbuflen++;
	
}
