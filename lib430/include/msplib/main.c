#ifndef __MAIN_C__
#define __MAIN_C__

#include <msplib/wdt.h>
#include <msplib/msplib.h>

void setup(void);
void loop(void);

int main(void) {

	// Halt the watchdog timer - According to the datasheet the watchdog timer
	// starts automatically after powerup. It must be configured or halted at
	// the beginning of code execution to avoid a system reset.
	WDT_halt();
	
	setup();
	while(1) loop();

}

#endif // __MAIN_C__
