#ifndef __FLASH_H__
#define __FLASH_H__

#include <msp430.h>
#include <legacymsp430.h>
#include <string.h>
#include <stdint.h>

#define FLASH_SIZE 256

#ifndef __MSP430_HAS_FLASH2__
#warning Target MCU does not have flash memory!
#endif
void flash_clear(char* addr);
void flash_write(char* addr,void* sdata, uint16_t size);
void flash_read(char* addr,void* sdata, uint16_t size);

#endif // __FLASH_H__
