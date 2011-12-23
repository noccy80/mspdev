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
#include "inc/hw_memmap.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"
#include "driverlib/5xx_6xx/crc.h"

//******************************************************************************
//!
//! CRC - Build Signature and Rebuild to test.
//!
//!  The CRC is first used to build a signature using a seed and multiple data
//!  values. This signature is considered as the checksum and can be sent by a
//!  UART connection along with the data to verify the correct data has been
//!  sent. The second half of this program is used to test the CRC checksum of
//!  the data that has been created, by recreating the same checksum and
//!  comparing it to the first checksum. If the two checksum are equal, then
//!  P1.0 is set and the LED is turned on. Breakpoints can be set before the
//!  CRC_setData() funtion to observe the CRC register values and see the
//!  subsequent signatures before/after each data set.
//!
//!                 MSP430F552x
//!             -----------------
//!         /|\|                 |
//!          | |                 |
//!          --|RST              |
//!            |             P1.0|--> LED
//!            |                 |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - CRC peripheral
//! - GPIO Port peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - NONE
//!
//******************************************************************************

void main (void)
{
    unsigned int crcSeed = 0xBEEF;
    unsigned int data[] = {0x0123,
                           0x4567,
                           0x8910,
                           0x1112,
                           0x1314};
    unsigned int crcResult;
    int i;

    //Stop WDT
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set P1.0 as an output
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0);

    //Set the CRC seed
    CRC_setSeed(__MSP430_BASEADDRESS_CRC__,
        crcSeed);

    for (i = 0; i < 5; i++)
    {
        //Add all of the values into the CRC signature
        CRC_setData(__MSP430_BASEADDRESS_CRC__,
            data[i]);
    }

    //Save the current CRC signature checksum to be compared for later
    crcResult = CRC_getResult(__MSP430_BASEADDRESS_CRC__);


    //*** Test the CRC ***//

    //Reset the CRC Signature and set the same seed
    CRC_setSeed(__MSP430_BASEADDRESS_CRC__,
        crcSeed);

    for (i = 0; i < 5; i++)
    {
        //Add all of the values into the CRC signature
        CRC_setData(__MSP430_BASEADDRESS_CRC__,
            data[i]);
    }

    //Compare the 2 CRC Resulting Signature Checksums
    if (crcResult == CRC_getResult(__MSP430_BASEADDRESS_CRC__)){
        //set P1.0
        GPIO_setOutputHighOnPin(__MSP430_BASEADDRESS_PORT1_R__,
            GPIO_PORT_P1,
            GPIO_PIN0);
    }

    //Enter LPM4, interrupts enabled
    __bis_SR_register(LPM4_bits);
    __no_operation();
}

