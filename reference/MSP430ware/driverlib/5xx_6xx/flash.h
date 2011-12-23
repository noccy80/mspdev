/* --COPYRIGHT--,BSD
 * Copyright (c) 2011, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
#ifndef __MSP430WARE_FLASH_H__
#define __MSP430WARE_FLASH_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_FLASH__


//*****************************************************************************
//
//The following are values that can be passed to the Flash_status()
//API as the mask parameter.
//
//*****************************************************************************
#define FLASH_READY_FOR_NEXT_WRITE              WAIT_L
#define FLASH_ACCESS_VIOLATION_INTERRUPT_FLAG   ACCVIFG_L
#define FLASH_PASSWORD_WRITTEN_INCORRECTLY      KEYV_L
#define FLASH_BUSY                              BUSY_L

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************
extern void Flash_segmentErase (unsigned int baseAddress,
    unsigned char *Flash_ptr);

extern void Flash_bankErase (unsigned int baseAddress, 
                             unsigned char *Flash_ptr);

extern unsigned short Flash_eraseCheck (unsigned int baseAddress,
    unsigned char *Flash_ptr,
    unsigned int numberOfBytes
    );
extern void Flash_write8 (unsigned int baseAddress,
    unsigned char *Data_ptr,
    unsigned char *Flash_ptr,
    unsigned int numberOfBytes
    );
extern void Flash_write16 (unsigned int baseAddress,
    unsigned int *Data_ptr,
    unsigned int *Flash_ptr,
    unsigned int numberOfBytes
    );
extern void Flash_write32 (unsigned int baseAddress,
    unsigned long *Data_ptr,
    unsigned long *Flash_ptr,
    unsigned int numberOfBytes
    );
extern void Flash_memoryFill32 (unsigned int baseAddress,
    unsigned long value,
    unsigned long *Flash_ptr,
    unsigned int count
    );
extern unsigned char Flash_status (unsigned int baseAddress,
    unsigned char mask
    );
#endif
