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
#include "driverlib/5xx_6xx/sfr_sys.h"
#include "driverlib/5xx_6xx/spi.h"
#include "driverlib/5xx_6xx/ucs.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//******************************************************************************
//!
//! \addtogroup dma_examples_list
//! DMA - Single Transfer using SPI, TX on DMA Channel 0, RX on DMA Channel 1
//!
//!  This is the SPI Master.
//!  This code has to be used with spi_slave.c (slave SPI). DMA channel 0 is
//!  used to transfer a single byte while DMA channel 1 is used to RX from slave
//!  SPI at the same time. This code will set P1.0 if RX character is correct
//!  and clears P1.0 if received character is wrong. Watchdog in interval mode
//!  triggers block transfer every 1000ms.
//!  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
//!
//!                MSP430F552x
//!             -----------------
//!         /|\|              XIN|-
//!          | |                 | 32kHz
//!          --|RST          XOUT|-
//!            |                 |
//!            |             P1.0|-> LED
//!            |    P3.3/UCA0SIMO|-> Data Out
//!            |    P3.4/UCA0SOMI|<- Data In
//!            |     P2.7/UCA0CLK|-> Serial Clock Out
//!            |                 |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - DMA peripheral
//! - SPI peripheral
//! - GPIO Port peripheral
//! - UCA0SIMO
//! - UCA0SOMI
//! - UCA0CLK
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - WDT_VECTOR
//!
//******************************************************************************

char TxString;
char RxString;

void main (void)
{
    //Initialize Watchdog in Interval Timer Mode
    /*
     * Base Address of WDT module
     * Use ACLK as clock source to WDT module
     * Divide ACLK by 32k to assert interval every 1 second
     */
    WDT_intervalTimerInit(__MSP430_BASEADDRESS_WDT_A__,
        WDT_CLOCKSOURCE_ACLK,
        WDT_CLOCKDIVIDER_32K);

    //Enable Watchdog Interupt
    SFR_enableInterrupt(__MSP430_BASEADDRESS_SFR__,
        WDTIE);

    //Clear P1.0 LED off
    GPIO_setOutputLowOnPin(
        __MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //P3.4,3 & P2.7 option select
    GPIO_setAsPeripheralModuleFunctionInputPin(__MSP430_BASEADDRESS_PORT3_R__,
        GPIO_PORT_P3,
        GPIO_PIN4 + GPIO_PIN3
        );
    GPIO_setAsPeripheralModuleFunctionInputPin(__MSP430_BASEADDRESS_PORT2_R__,
        GPIO_PORT_P2,
        GPIO_PIN7
        );

    //Initialize Master
    SPI_masterInit(__MSP430_BASEADDRESS_USCI_A0__,
        SPI_CLOCKSOURCE_ACLK,
        UCS_getACLK(__MSP430_BASEADDRESS_UCS__),
        500000, //Desired SPI CLOCK
        SPI_MSB_FIRST,
        SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
        SPI_CLOCKPOLARITY_INACTIVITY_HIGH
        );

    //Enable SPI module
    SPI_enable(__MSP430_BASEADDRESS_USCI_A0__);

    //Wait for slave to initialize
    __delay_cycles(100);

    //USCI_A0 TX buffer ready?
    while (!SPI_getInterruptStatus(__MSP430_BASEADDRESS_USCI_A0__, UCTXIFG)) ;


    //Initialize and Setup DMA Channel 0
    /*
     * Base Address of the DMA Module
     * Configure DMA channel 0
     * Configure channel for single transfer
     * DMA transfers will be disabled and interrupt flag will be set after every
     *   1 transfer
     * Use DMA Trigger Source 17 (UCA0TXIFG)
     * Transfer Byte-to-byte
     * Trigger transfer on signal held high
     */
    DMA_init(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_0,
        DMA_TRANSFER_SINGLE,
        1,
        DMA_TRIGGERSOURCE_17,
        DMA_SIZE_SRCBYTE_DSTBYTE,
        DMA_TRIGGER_HIGH);
    /*
     * Base Address of the DMA Module
     * Configure DMA channel 0
     * Use TxString as source
     * Increment source address after every transfer
     */
    DMA_setSrcAddress(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_0,
        (unsigned long)&TxString,
        DMA_DIRECTION_INCREMENT);
    /*
     * Base Address of the DMA Module
     * Configure DMA channel 0
     * Use SPI TX Buffer as destination
     * Don't move the destination address after every transfer
     */
    DMA_setDstAddress(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_0,
        SPI_getTransmitBufferAddressForDMA(__MSP430_BASEADDRESS_USCI_A0__),
        DMA_DIRECTION_UNCHANGED);

    //Initialize and Setup DMA Channel 1
    /*
     * Base Address of the DMA Module
     * Configure DMA channel 1
     * Configure channel for single transfer
     * DMA transfers will be disabled and interrupt flag will be set after every
     *   1 transfer
     * Use DMA Trigger Source 16 (UCA0RXIFG)
     * Transfer Byte-to-byte
     * Trigger transfer on signal held high
     */
    DMA_init(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_1,
        DMA_TRANSFER_SINGLE,
        1,
        DMA_TRIGGERSOURCE_16,
        DMA_SIZE_SRCBYTE_DSTBYTE,
        DMA_TRIGGER_HIGH);
    /*
     * Base Address of the DMA Module
     * Configure DMA channel 1
     * Use SPI RX Buffer as source
     * Don't move the source address after every transfer
     */
    DMA_setSrcAddress(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_1,
        SPI_getReceiveBufferAddressForDMA(__MSP430_BASEADDRESS_USCI_A0__),
        DMA_DIRECTION_UNCHANGED);
    /*
     * Base Address of the DMA Module
     * Configure DMA channel 1
     * Use RxString as destination
     * Increment destination address after every transfer
     */
    DMA_setDstAddress(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_1,
        (unsigned long)&RxString,
        DMA_DIRECTION_INCREMENT);

    //Clear TxString && RxString
    TxString = RxString = 0;

    //Enter LPM3 w/ interrupts
    __bis_SR_register(LPM3_bits + GIE);
    //For Debugger
    __no_operation();
}

//------------------------------------------------------------------------------
//Trigger DMA0 & DMA1 block transfer.
//------------------------------------------------------------------------------
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR (void)
{
    if (TxString - 1 == RxString){
        //set P1.0
        GPIO_setOutputHighOnPin(
            __MSP430_BASEADDRESS_PORT1_R__,
            GPIO_PORT_P1,
            GPIO_PIN0
            );
    } else   {
        //Clear P1.0 LED off
        GPIO_setOutputLowOnPin(
            __MSP430_BASEADDRESS_PORT1_R__,
            GPIO_PORT_P1,
            GPIO_PIN0
            );
    }

    //Increment TxString counter
    TxString++;

    //Enable DMA transfers on channel 1
    DMA_enableTransfers(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_1);

    //Enable DMA transfers on channel 0
    DMA_enableTransfers(__MSP430_BASEADDRESS_DMAX_3__,
        DMA_CHANNEL_0);
}

