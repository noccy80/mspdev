#include "hal.h"

inline void gpio_decode_port(HAL_MAP halmap) { 
	return ((halmap & 0x00F0) >> 4); 
}

inline void gpio_decode_pin(HAL_MAP halmap) { 
	return ((halmap & 0x000F);
}

void gpio_makeinput(HAL_MAP pin) {

}

void gpio_makeoutput(HAL_MAP pin) {

}

void gpio_setstate(HAL_MAP pin, uint8_t state) {

}


