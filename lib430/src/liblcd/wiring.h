#ifndef WIRING_H_
#define WIRING_H_

#ifndef WORD
	#define WORD unsigned int
	#define byte unsigned char
	#define uint8_t unsigned char
#endif


// ----- Constants 
	#define LOW 0
	#define HIGH 1
	
	#define INPUT 0
	#define OUTPUT 1	
	
	// --- Declare a "main()" that  demands a single call to "startup()"
	//     and an infinite "loop()" routine
	void setup(void);
	void loop(void);
	int main(){
		WDTCTL = WDTPW|WDTHOLD; // Stop watchdog timer
		setup(); 
		for(;;){ loop(); }
		}
	
// digital I/O 	
	inline void pinMode(int pin, int isOutput){ 			
		if(isOutput){
			P1DIR |= (1 << pin);
		} 
		else{
			P1DIR &= (~(1 << pin));
		} 
	}
	
	inline void digitalWrite(WORD pin, WORD setOrReset)
	{
		if (setOrReset) 
			P1OUT |= ( 1 << pin);
		else
			P1OUT &= (~(1 << pin));
	}
	
	inline int digitalRead(WORD pin)
	{
		return (P1OUT & (1 << pin)) > 0;
	}


	
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

interrupt(TIMER0_A0_VECTOR) TA0ISR(void) {
	// __low_power_mode_off_on_exit(); // Restore Active Mode on return
}	

	
	
	
#endif /*WIRING_H_*/
