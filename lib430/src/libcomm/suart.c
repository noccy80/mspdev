#include "suart.h"
#include "fifo.h"
#include <libhal/hal.h>

FIFO* _uart_inq;
FIFO* _uart_outq;
HAL_MAP _uart_drecv;
HAL_MAP _uart_dsend;

// Buffers and state for transmitting and receiving data. 
unsigned char BitCnt;		// Bit count, used when transmitting byte
unsigned int RXByte;		// Value recieved once hasRecieved is set
unsigned int TXByte;		// Value sent over UART when Transmit() is called
volatile bool _uart_isReceiving;		// Status for when the device is receiving

/**
 * @brief Initialize the software uart code
 *
 * This method will enable global interrupts and configure the timers.
 */
void suart_init(FIFO* inq, FIFO* outq, HAL_MAP drecv, HAL_MAP dsend) {

	_uart_inq = inq;
	_uart_outq = outq;
	_uart_drecv = drecv;
	_uart_dsend = dsend;

	fifo_init(&_uart_inq,16);
	fifo_init(&_uart_outq,16);

	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
  
	BCSCTL1 = CALBC1_1MHZ; // Set range
	DCOCTL = CALDCO_1MHZ; // SMCLK = DCO = 1MHz  

	P1SEL |= TXD;
	P1DIR |= TXD;

	P1IES |= RXD; // RXD Hi/lo edge interrupt
	P1IFG &= ~RXD; // Clear RXD (flag) before enabling interrupt
	P1IE |= RXD; // Enable RXD interrupt
  
	_uart_isReceiving = false; // Set initial values

	__bis_SR_register(GIE); // interrupts enabled
	
}

/**
 * @brief Transmit a character in a blocking fashion.
 *
 * @param int character The character to write
 */
int putchar(int character) {
	fifo_push(&_uart_outq,(uint8_t)character);
	suart_flush();
	return 1;

}

/**
 * @brief Return the number of bytes waiting in the buffer
 *
 * @todo Map against ring buffer
 * @return bool True if data is waiting
 */
bool suart_datawaiting() {
	return fifo_peek(&_uart_inq);
}

/**
 * @brief Receive a character from the buffer.
 *
 * @return unsigned char The received byte
 */
unsigned char suart_receive() {

	return fifo_pop(&_uart_inq);

}

void suart_flush() {
	while (fifo_peek(&_uart_outq)) { suart_transmit(fifo_pop(&_uart_outq)); }
}

/**
 * @brief Transmit a character.
 *
 * @param unsigned int byte The byte to transfer
 */
void suart_transmit(unsigned int byte) { 

	TXByte = byte;
	while(_uart_isReceiving);			// Wait for RX completion
  	CCTL0 = OUT;				// TXD Idle as Mark
  	TACTL = TASSEL_2 + MC_2;		// SMCLK, continuous mode

  	BitCnt = 0xA;				// Load Bit counter, 8 bits + ST/SP
  	CCR0 = TAR;				// Initialize compare register
  
  	CCR0 += Bit_time;			// Set time till first bit
  	TXByte |= 0x100;			// Add stop bit to TXByte (which is logical 1)
  	TXByte = TXByte << 1;			// Add start bit (which is logical 0)
  
  	CCTL0 =  CCIS0 + OUTMOD0 + CCIE;	// Set signal, intial value, enable interrupts
  	while ( CCTL0 & CCIE );			// Wait for previous TX completion
  	
}

/**
 * @brief Port 1 Interrupt Service Routine (ISR)
 *
 */
interrupt(PORT1_VECTOR) PORT1_ISR(void) {  	

	_uart_isReceiving = true;

	P1IE &= ~RXD;			// Disable RXD interrupt
	P1IFG &= ~RXD;			// Clear RXD IFG (interrupt flag)

  	TACTL = TASSEL_2 + MC_2;	// SMCLK, continuous mode
  	CCR0 = TAR;			// Initialize compare register
  	CCR0 += Bit_time_5;		// Set time till first bit
	CCTL0 = OUTMOD1 + CCIE;		// Dissable TX and enable interrupts

	RXByte = 0;			// Initialize RXByte
	BitCnt = 0x9;			// Load Bit counter, 8 bits + ST
	
}

/**
 * @brief Timer A0 Interrupt Service Routine (ISR)
 *
 */
interrupt(TIMER0_A0_VECTOR) TIMERA0_ISR(void) {

	if(!_uart_isReceiving) {
	
		CCR0 += Bit_time;			// Add Offset to CCR0  
		if ( BitCnt == 0) {			// If all bits TXed
  			TACTL = TASSEL_2;		// SMCLK, timer off (for power consumption)
			CCTL0 &= ~ CCIE ;		// Disable interrupt
		} else {
			CCTL0 |=  OUTMOD2;		// Set TX bit to 0
			if (TXByte & 0x01)
				CCTL0 &= ~ OUTMOD2;	// If it should be 1, set it to 1
			TXByte = TXByte >> 1;
			BitCnt --;
		}

	} else {

		CCR0 += Bit_time;				// Add Offset to CCR0  
		if ( BitCnt == 0) {
  			TACTL = TASSEL_2;			// SMCLK, timer off (for power consumption)
			CCTL0 &= ~ CCIE ;			// Disable interrupt

			_uart_isReceiving = false;

			P1IFG &= ~RXD;				// clear RXD IFG (interrupt flag)
			P1IE |= RXD;				// enabled RXD interrupt

			if ( (RXByte & 0x201) == 0x200) {	// Validate the start and stop bits are correct
				RXByte = RXByte >> 1;		// Remove start bit
				RXByte &= 0xFF;			// Remove stop bit
				fifo_push(&_uart_inq,RXByte);
			}
  			__bic_SR_register_on_exit(CPUOFF);	// Enable CPU so the main while loop continues
		} else {
			if ( (P1IN & RXD) == RXD)		// If bit is set?
				RXByte |= 0x400;		// Set the value in the RXByte 
			RXByte = RXByte >> 1;			// Shift the bits down
			BitCnt --;
		}
		
	}
	
}

