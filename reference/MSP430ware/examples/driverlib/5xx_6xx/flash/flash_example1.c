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
//*****************************************************************************
//!   Dummy calibration data is written to infoB.
//!   16 locations are written with char data, 8 locations with int data and
//!   4 locations with word data.  LED toggles upon completion.
//!
//!   Check infoB location @ 0x1900 on execution of program.
//!
//!                MSP430F54xA
//!             -----------------
//!         /|\|                 |
//!          | |             P1.0|-LED
//!          --|RST              |
//!            |                 |
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
//********************************************************************************

#include "inc/hw_memmap.h"
#include "driverlib/5xx_6xx/flash.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//*****************************************************************************
//
//INFOB address in flash into which calibration data would be written
//
//*****************************************************************************
#define INFOB_START   (0x1900)

//*****************************************************************************
//
//Dummy char array of 'calibration data' - to be stored in flash
//
//*****************************************************************************
unsigned char calibration_data_char[16] = {0x00,
                                           0x01,
                                           0x02,
                                           0x03,
                                           0x04,
                                           0x05,
                                           0x06,
                                           0x07,
                                           0x08,
                                           0x09,
                                           0x10,
                                           0x11,
                                           0x12,
                                           0x13,
                                           0x14,
                                           0x15};
//*****************************************************************************
//
//Dummy int array of 'calibration data' - to be stored in flash
//
//*****************************************************************************
unsigned int calibration_data_int[8] = {0x1617,
                                        0x1819,
                                        0x2021,
                                        0x2223,
                                        0x2425,
                                        0x2627,
                                        0x2829,
                                        0x3031};
//*****************************************************************************
//
//Dummy long array of 'calibration data' - to be stored in flash
//
//*****************************************************************************
unsigned long calibration_data_long[4] = {0x35343332,
                                          0x39383736,
                                          0x43424140,
                                          0x47464544};

void main (void)
{
    unsigned int status;

    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //Write calibration data to INFOB

    do
    {
        //Erase INFOB
        Flash_segmentErase(__MSP430_BASEADDRESS_FLASH__,
            (unsigned char *)INFOB_START
            );
        status = Flash_eraseCheck(__MSP430_BASEADDRESS_FLASH__,
            (unsigned char *)INFOB_START,
            128
            );
    } while (status == STATUS_FAIL);

    //Write calibration data to INFOB
    Flash_write8(__MSP430_BASEADDRESS_FLASH__,
        calibration_data_char,
        (unsigned char *)INFOB_START,
        16
        );
    Flash_write16(__MSP430_BASEADDRESS_FLASH__,
        calibration_data_int,
        (unsigned int *)(INFOB_START + 16),
        8
        );
    Flash_write32(__MSP430_BASEADDRESS_FLASH__,
        calibration_data_long,
        (unsigned long *)(INFOB_START + 32),
        4
        );
    Flash_memoryFill32(__MSP430_BASEADDRESS_FLASH__,
        0xBEEFBEEF,
        (unsigned long *)(INFOB_START + 48),
        (128 - 48) >> 2
        );

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
