#ifndef __HOOKS_H__
#define __HOOKS_H__

#include <msp430.h>
#include <legacymsp430.h>
#include <gpio.h>

enum HookFlags {
	// Trigger on rising edge, falling edge, or on adc completion
	HOOK_TRIGGER_RISING = 0x01,
	HOOK_TRIGGER_FALLING = 0x02,
	HOOK_ADCCOMPLETE = 0x04,
	// Watchdog timer
	HOOK_WDT = 0x08,
	// The two onboard timers
	HOOK_TIMER1 = 0x10,
	HOOK_TIMER2 = 0x20,
};

void hooks_assign(GPIOPIN* pin, uint16_t flags, void* cb);

interrupt(PORT1_VECTOR) port0_hook_isr(void) {
	// Clear interrupt flag
}
interrupt(PORT2_VECTOR) port1_hook_isr(void) {
	// Clear interrupt flag
}

#endif // __HOOKS_H__
