#ifndef __ARDUINO_H__
#define __ARDUINO_H__

#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>

/**
 * @brief Arduino style setup function
 */
void setup();

/**
 * @brief Arduino style loop function
 */
void loop();

#include <uart.h>

#ifndef WORD
#define WORD unsigned int
#endif

#ifndef byte
#define byte unsigned char
#endif

///@const Low pin state
#define LOW 0
///@const High pin state
#define HIGH 1

///@const Input pin
#define INPUT 0
///@const Output pin
#define OUTPUT 1 

// digital I/O
/**
 * @brief Set the pin mode to INPUT or OUTPUT
 *
 * This will set the pin mode. Very inefficient for multiple assignments.
 *
 * @param int pin The pin
 * @param int isOutput Either OUTPUT or INPUT
 */
inline void pinMode(WORD pin, WORD isOutput){
	if(isOutput){
		P1DIR |= (1 << pin);
	}
	else{
		P1DIR &= (~(1 << pin));
	}
}

/**
 * @brief Set the state of an output pin
 *
 * @param WORD pin The pin
 * @param WORD setOrReset Either HIGH or LOW
 */
inline void digitalWrite(WORD pin, WORD setOrReset) {
	if (setOrReset)
		P1OUT |= ( 1 << pin);
	else
		P1OUT &= (~(1 << pin));
}

/**
 * @brief Read the digital input state of a pin
 *
 * @param WORD pin The pin
 */
inline int digitalRead(WORD pin) {
	return (P1OUT & (1 << pin)) > 0;
}

/**
 * @brief Read analog input via ADC10
 * @todo Write me!
 * @param WORD pin The pin
 * @return int The analog value
 */
inline int analogRead(WORD pin) {
	// Do dac conversion here
	return 0;
}

/**
 * @brief Write analog (pwm) output to pin
 * @todo Write me!
 * @param WORD pin The pin
 * @param int value The value
 */
inline void analogWrite(WORD pin, int value) {
	// Setup pin for PWM via WDT.
}

int constrain(int val, int min, int max);
int map(int val, int amin, int amax, int bmin, int bmax);

/**
 * @brief Serial IO begin function
 */
void Serial_begin(int baud);
/**
 * @brief Arduino style function mappings
 */
/*
typedef struct _Serial {
	void (*begin)(int baud);
} Serial;
Serial.begin = Serial_begin;
*/
/**
 * @brief Enable interrupts.
 */
inline void interrupts() {
	eint();
}

/**
 * @brief Disable interrupts
 */
inline void noInterrupts() {
	dint();
}

/**
 * @brief Timer-based implementation for sleeping.
 *
 * Warning! Don't use this if you depend on TIMER0_A0
 *
 * @param unsigned int time The time to sleep
 */
void delayMicroseconds(unsigned int time){
	TACCR0 = time-1; // Upper limit of count for TAR
	TACTL = MC_1|ID_0|TASSEL_2|TACLR; // Set up and start Timer A
	while ((TACTL & TAIFG) == 0){ // Wait for overflow
	} // doing nothing
	TACTL &= (~TAIFG); // Clear overflow flag
}

void delayMicrosecondszz(unsigned int time){
	TACCR0 = time; // Upper limit of count for TAR
	TACTL = MC_1|ID_0|TASSEL_2|TACLR; // Set up and start Timer A
	// __low_power_mode_3 ();
	//__delay_cycles
}

inline void delayMilliseconds(unsigned int delay){
	while(delay > 60){
		delayMicroseconds(60000);
		delay -= 60;
	}
	if (delay) delayMicroseconds((delay << 10) - (delay << 4) - (delay << 3));
}

///@define Delay function. You should use __delay_cycles instead.
#define delay(N) delayMilliseconds(N)

/**
 * @brief Initialize the uptime routines.
 */
void uptime_init();

/**
 * @brief Return thu number of milliseconds elapsed since startup.
 *
 * @return unsigned long The number of milliseconds
 */
unsigned long millis();

/**
 * @brief Return thu number of milliseconds elapsed since startup.
 *
 * @return unsigned long The number of milliseconds
 */
unsigned long micros();

#ifdef ARDUINO_MAIN
/**
 * @brief Arduino main function.
 *
 * @note Only included if ARDUINO_MAIN is defined!
 * @return int Function doesn't return.
 */
int main(void) {

	// Halt the watchdog timer - According to the datasheet the watchdog timer
	// starts automatically after powerup. It must be configured or halted at
	// the beginning of code execution to avoid a system reset.
	WDTCTL = WDTPW + WDTHOLD;;

	setup();
	// uptime_init();
	for(;;){ loop(); }

}
#endif // ARDUINO_MAIN

#endif // __ARDUINO_H__

