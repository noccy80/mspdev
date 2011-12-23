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
#include "driverlib/5xx_6xx/dma.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//******************************************************************************
//!
//! \addtogroup dma_examples_list
//! DMA - Repeated Block Transfer to-and-from RAM, Software Trigger.
//!
//!  A 16 word block from 1C00-1C1Fh is transfered to 1C20h-1C3fh using DMA0 in
//!  a burst block using software DMAREQ trigger. After each transfer, source,
//!  destination and DMA size are reset to inital software setting because DMA
//!  transfer mode 5 is used. P1.0 is toggled durring DMA transfer only for
//!  demonstration purposes.
//!  ** RAM location 0x1C00 - 0x1C3F used - make sure no compiler conflict **
//!  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//!
//!                 MSP430x552x
//!             -----------------
//!         /|\|              XIN|-
//!          | |                 | 32kHz
//!          --|RST          XOUT|-
//!            |                 |
//!            |             P1.0|-> LED
//!            |                 |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - DMA peripheral
//! - GPIO Port peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//!
//******************************************************************************

#include <msp430f5529.h>

void main (void)
{
    //Stop Watchdog Timer
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //Initialize and Setup DMA Channel 0
    /*
     * Base Address of the DMA Module
     * Configure DMA channel 0
     * Configure channel for repeated block transfers
     * DMA interrupt flag will be set after every 16 transfers
     * Use DMA_startTransfer() function to trigger transfers
     * Transfer Word-to-Word
     * Trigger upon Rising Edge of Trigger Source Signal
     */
    DMA_init(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_0,
        DMA_TRANSFER_REPEATED_BLOCK,
        16,
        DMA_TRIGGERSOURCE_0,
        DMA_SIZE_SRCWORD_DSTWORD,
        DMA_TRIGGER_RISINGEDGE);
    /*
     * Base Address of the DMA Module
     * Configure DMA channel 0
     * Use 0x1C00 as source
     * Increment source address after every transfer
     */
    DMA_setSrcAddress(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_0,
        0x1C00,
        DMA_DIRECTION_INCREMENT);
    /*
     * Base Address of the DMA Module
     * Configure DMA channel 0
     * Use 0x1C20 as destination
     * Increment destination address after every transfer
     */
    DMA_setDstAddress(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_0,
        0x1C20,
        DMA_DIRECTION_INCREMENT);

    //Enable transfers on DMA channel 0
    DMA_enableTransfers(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_0);

    while (1)
    {
        //set P1.0
        GPIO_setOutputHighOnPin(
            __MSP430_BASEADDRESS_PORT1_R__,
            GPIO_PORT_P1,
            GPIO_PIN0
            );

        //Start block tranfer on DMA channel 0
        DMA_startTransfer(__MSP430_BASEADDRESS_DMAX_3__,
            DMA_CHANNEL_0);

        //Clear P1.0 LED off
        GPIO_setOutputLowOnPin(
            __MSP430_BASEADDRESS_PORT1_R__,
            GPIO_PORT_P1,
            GPIO_PIN0
            );
    }
}

