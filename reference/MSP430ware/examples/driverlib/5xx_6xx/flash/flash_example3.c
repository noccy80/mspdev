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
//******************************************************************************
//!  MSP430F54xA Demo - Flash In-System Programming w/ Long-Word write at 0x1800
//!
//!  Description: This program first erases flash seg D, then it writes a 32-bit
//!  value to memory location 0x1800 using BLK write mode. BLK write
//!  provides faster write times than byte/word mode. LED toggles upon
//!  completion.
//!  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//!
//!                MSP430F54xA
//!            -----------------
//!        /|\|                 |
//!         | |             P1.0|-LED
//!         --|RST              |
//!           |                 |
//!
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - Flash module
//! - GPIO Port peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//******************************************************************************

#include "inc/hw_memmap.h"
#include "driverlib/5xx_6xx/flash.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//*****************************************************************************
//
//Calibration data to be written into flash
//
//*****************************************************************************
unsigned long calibration_data[] = {0x12345678};

//*****************************************************************************
//
//INFO address in flash to which data is written into
//
//*****************************************************************************
#define INFOD_START   (0x1800)


void main (void)
{
    unsigned short status;

    //Stop WDT
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //Erase INFOD
    do {
        Flash_segmentErase(__MSP430_BASEADDRESS_FLASH__,
            (unsigned char *)INFOD_START
            );
        status = Flash_eraseCheck(__MSP430_BASEADDRESS_FLASH__,
            (unsigned char *)INFOD_START,
            128
            );
    } while (status == STATUS_FAIL);

    //Flash write
    Flash_write32(__MSP430_BASEADDRESS_FLASH__,
        calibration_data,
        (unsigned long *)(INFOD_START),1);

    while (1)
    {
        //Toggle P1.0
        GPIO_toggleOutputOnPin(
            __MSP430_BASEADDRESS_PORT1_R__,
            GPIO_PORT_P1,
            GPIO_PIN0
            );

        //Delay
        __delay_cycles(1000000);
    }
}

