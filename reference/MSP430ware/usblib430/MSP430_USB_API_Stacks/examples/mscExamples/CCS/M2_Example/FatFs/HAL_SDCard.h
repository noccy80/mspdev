/*******************************************************************************
    Filename:       HAL_SDCard.h

    Copyright 2010 Texas Instruments, Inc.
*******************************************************************************/

#ifndef HAL_SDCARD_H
#define HAL_SDCARD_H

#include <stdint.h>
#include <descriptors.h>

extern void SDCard_init(void);
extern void SDCard_fastMode(void);
extern void SDCard_readFrame(uint8_t *pBuffer, uint16_t size);
extern void SDCard_sendFrame(uint8_t *pBuffer, uint16_t size);
extern void SDCard_setCSHigh(void);
extern void SDCard_setCSLow(void);

#endif /* HAL_SDCARD_H */
