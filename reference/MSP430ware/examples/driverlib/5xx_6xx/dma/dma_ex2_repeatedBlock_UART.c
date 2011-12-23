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
#include "driverlib/5xx_6xx/uart.h"
#include "driverlib/5xx_6xx/ucs.h"
#include "driverlib/5xx_6xx/timer.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//******************************************************************************
//!
//! \addtogroup dma_examples_list
//! DMA - Repeated Single Transfer using UART 9600, Timer_A, and ACLK
//!
//!  DMA channel 0 is used to transfer a string byte-by-byte as a repeating
//!  block to UCA1TXBUF. Timer_A operates continuously at 32768Hz with CCR2IFG
//!  triggering DMA channel 0. "Hello World" is TX'd via 9600 baud UART1.
//!  ACLK= TACLK 32768Hz, MCLK= SMCLK= default DCO ~ 1048576Hz
//!  Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (000Dh 4Ah)
//!  //* An external watch crystal on XIN XOUT is required for ACLK *//
//!
//!              MSP430x552x
//!            -----------------
//!        /|\|              XIN|-
//!         | |                 | 32kHz
//!         --|RST          XOUT|-
//!           |                 |
//!           |     P4.4/UCA0TXD|-----------> "Hello World"
//!           |                 | 9600 - 8N1
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - DMA peripheral
//! - UART peripheral
//! - GPIO Port peripheral
//! - UCA0TXD
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//!
//******************************************************************************

static char String1[] = { "Hello World\r\n" };

void main (void)
{
    //Stop Watchdog Timer
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //P3.4 = USCI_A0 TXD
    GPIO_setAsPeripheralModuleFunctionInputPin(__MSP430_BASEADDRESS_PORT3_R__,
        GPIO_PORT_P3,
        GPIO_PIN3
        );

    if ( STATUS_FAIL == UART_init(__MSP430_BASEADDRESS_USCI_A0__,
             UART_CLOCKSOURCE_SMCLK,
             UCS_getSMCLK(__MSP430_BASEADDRESS_UCS__),
             9600, //BAUD RATE
             UART_NO_PARITY,
             UART_LSB_FIRST,
             UART_ONE_STOP_BIT,
             UART_MODE,
             UART_OVERSAMPLING_BAUDRATE_GENERATION) ){
        return;
    }

    //Enable UART module for operation
    UART_enable(__MSP430_BASEADDRESS_USCI_A0__);


    //Initialize and Setup DMA Channel 0
    /*
     * Base Address of the DMA Module
     * Configure DMA channel 0
     * Configure channel for repeated single transfers
     * DMA interrupt flag will be set after every 12 transfers
     * Use DMA Trigger Source 1 (TA0CCR0IFG)
     * Transfer Byte-to-byte
     * Trigger Upon Rising Edge of Trigger Source Signal
     */
    DMA_init(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_0,
        DMA_TRANSFER_REPEATED_SINGLE,
        (sizeof String1 - 1),
        DMA_TRIGGERSOURCE_1,
        DMA_SIZE_SRCBYTE_DSTBYTE,
        DMA_TRIGGER_RISINGEDGE);
    /*
     * Base Address of the DMA Module
     * Configure DMA channel 0
     * Use String1 as source
     * Increment source address after every transfer
     */
    DMA_setSrcAddress(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_0,
        (unsigned long)String1,
        DMA_DIRECTION_INCREMENT);
    /*
     * Base Address of the DMA Module
     * Configure DMA channel 0
     * Use UART TX Buffer as destination
     * Don't move the destination address after every transfer
     */
    DMA_setDstAddress(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_0,
        UART_getTransmitBufferAddressForDMA(__MSP430_BASEADDRESS_USCI_A0__),
        DMA_DIRECTION_UNCHANGED);

    //Enable transfers on DMA channel 0
    DMA_enableTransfers(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_0);

    //For DMA0 trigger
    Timer_initCompare(__MSP430_BASEADDRESS_T0A5__,
        TIMER_CAPTURECOMPARE_REGISTER_2,
        TIMER_CAPTURECOMPARE_INTERRUPT_DISABLE,
        TIMER_OUTPUTMODE_OUTBITVALUE,
        1);

    //Timer sourced by SMCLK, starts in up-mode
    Timer_startUpMode(__MSP430_BASEADDRESS_T0A5__,
        TIMER_CLOCKSOURCE_SMCLK,
        TIMER_CLOCKSOURCE_DIVIDER_1,
        0x8192, //Char freq = TACLK/CCR0
        TIMER_TAIE_INTERRUPT_DISABLE,
        TIMER_CAPTURECOMPARE_INTERRUPT_DISABLE,
        TIMER_SKIP_CLEAR);

    //Enter LPM3
    _BIS_SR(LPM3_bits);
}

