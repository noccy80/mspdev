#include <stdint.h>
#include "hal.h"

uint8_t* hal_get_port_base(uint8_t port, uint8_t offset) {
	return (_PBADDR[port] + offset);
}

uint8_t hal_get_pin(HAL_MAP pin) {
	return 2^(pin & 0xF);
}


