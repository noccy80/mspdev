/**
 *  @file Flash.h
 */
#ifndef __MCU_MSP430_FLASH_H
#define __MCU_MSP430_FLASH_H

#include "../../Architecture.h"

// FLASH MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_FLASH)

//#define FLASH_UNLOCK()    FCTL3 = FWKEY; FCTL1 = FWKEY + WRT;
//#define FLASH_LOCK()      FCTL1 = FWKEY; FCTL3 = FWKEY | LOCK;
#define FLASH_UNLOCK()                    FCTL3 = FWKEY;
#define FLASH_LOCK()                      FCTL3 = FWKEY | LOCK;
#define FLASH_WRITE_BYTE(address,value)   FCTL1 = FWKEY | WRT;    if(*address != value) *address = value;
#define FLASH_ERASE(address)              FCTL1 = FWKEY | ERASE;  *address = 0;

#endif  // FLASH MODULE

#endif  // __MCU_MSP430_FLASH_H