/**
 * Skeleton for MSP430-based projects
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */
 
#include <msp430.h>
#include <legacymsp430.h>
#include <uart.h>

typedef struct _TRIGGER {
	void* next;
	int channel;
	int rising;
} TRIGGER;
TRIGGER trigger* = malloc(sizeof(TRIGGER));

void write_buffer() {
	
}

void main() {

	//trigger
	// uart_init(9600,8,'N',1);

}

void set_trigger(int channel, int rising) {
	TRIGGER* temp;
	temp = trigger;
	while(temp->next != 0) {
		temp* = temp->next;
	}
}
