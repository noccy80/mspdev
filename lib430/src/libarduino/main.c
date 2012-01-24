#include <arduino.h>
#include <wdt.h>
#include <msplib.h>


void setup(void);
void loop(void);

int main(void) {

	// Halt the watchdog timer - According to the datasheet the watchdog timer
	// starts automatically after powerup. It must be configured or halted at
	// the beginning of code execution to avoid a system reset.
	WDTCTL = WDTPW + WDTHOLD;;
	
	setup();
	for(;;){ loop(); }

}

