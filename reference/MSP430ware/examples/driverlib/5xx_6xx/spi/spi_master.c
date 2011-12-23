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
#include "driverlib/5xx_6xx/spi.h"
#include "driverlib/5xx_6xx/ucs.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//*****************************************************************************
//! This example shows how SPI master talks to SPI slave using 3-wire mode.
//! Incrementing data is sent by the master starting at 0x01. Received data is
//! expected to be same as the previous transmission.  USCI RX ISR is used to
//! handle communication with the CPU, normally in LPM0. If high, P1.0 indicates
//! valid data reception.  Because all execution after LPM0 is in ISRs,
//! initialization waits for DCO to stabilize against ACLK.
//! ACLK = ~32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz.  BRCLK = SMCLK/2
//!
//! Use with SPI Slave Data Echo code example.  If slave is in debug mode, P1.1
//! slave reset signal conflicts with slave's JTAG; to work around, use IAR's
//! "Release JTAG on Go" on slave device.  If breakpoints are set in
//! slave RX ISR, master must stopped also to avoid overrunning slave
//! RXBUF.
//!
//!                  MSP430F5438A
//!                 -----------------
//!            /|\ |                 |
//!             |  |                 |
//!    Master---+->|RST              |
//!                |                 |
//!                |             P3.4|-> Data Out (UCA0SIMO)
//!                |                 |
//!                |             P3.5|<- Data In (UCA0SOMI)
//!                |                 |
//!                |             P3.0|-> Serial Clock Out (UCA0CLK)
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - SPI peripheral
//! - GPIO Port peripheral (for SPI pins)
//! - UCA0SIMO
//! - UCA0SOMI
//! - UCA0CLK
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - USCI_A0_VECTOR
//!
//*****************************************************************************

//*****************************************************************************
//
//Specify desired frequency of SPI communication
//
//*****************************************************************************
#define SPICLK                          500000

unsigned char transmitData = 0x00, receiveData = 0x00;
unsigned short returnValue = 0x00;

void main (void)
{
    //Stop watchdog timer
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set P1.1 for slave reset
    GPIO_setOutputHighOnPin(
        __MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN1
        );

    //Set P1.1 for slave reset
    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //P3.5,4,0 option select
    GPIO_setAsPeripheralModuleFunctionInputPin(__MSP430_BASEADDRESS_PORT3_R__,
        GPIO_PORT_P3,
        GPIO_PIN5 + GPIO_PIN4 + GPIO_PIN0
        );

    //Initialize Master
    returnValue = SPI_masterInit(__MSP430_BASEADDRESS_USCI_A0__,
        SPI_CLOCKSOURCE_SMCLK,
        UCS_getSMCLK(__MSP430_BASEADDRESS_UCS__),
        SPICLK,
        SPI_MSB_FIRST,
        SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
        SPI_CLOCKPOLARITY_INACTIVITY_HIGH
        );

    if (STATUS_FAIL == returnValue){
        return;
    }

    //Enable SPI module
    SPI_enable(__MSP430_BASEADDRESS_USCI_A0__);

    //Enable Receive interrupt
    SPI_enableInterrupt(__MSP430_BASEADDRESS_USCI_A0__, SPI_RECEIVE_INTERRUPT);

    //Now with SPI signals initialized, reset slave
    GPIO_setOutputLowOnPin(
        __MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN1
        );

    //LED On
    GPIO_setOutputHighOnPin(
        __MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //Wait for slave to initialize
    __delay_cycles(100);

    //Initialize data values
    transmitData = 0x00;

    //USCI_A0 TX buffer ready?
    while (!SPI_getInterruptStatus(__MSP430_BASEADDRESS_USCI_A0__,
               SPI_TRANSMIT_INTERRUPT)) ;

    //Transmit Data to slave
    SPI_transmitData(__MSP430_BASEADDRESS_USCI_A0__, transmitData);

    //CPU off, enable interrupts
    __bis_SR_register(LPM0_bits + GIE);
}

//******************************************************************************
//
//This is the USCI_B0 interrupt vector service routine.
//
//******************************************************************************
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR (void)
{
    switch (__even_in_range(UCA0IV,4)){
        //Vector 2 - RXIFG
        case 2:
            //USCI_A0 TX buffer ready?
            while (!SPI_getInterruptStatus(__MSP430_BASEADDRESS_USCI_A0__,
                       SPI_TRANSMIT_INTERRUPT)) ;

            receiveData = SPI_receiveData(__MSP430_BASEADDRESS_USCI_A0__);

            //Increment data
            transmitData++;

            //Send next value
            SPI_transmitData(__MSP430_BASEADDRESS_USCI_A0__,
            transmitData
            );

            //Delay between transmissions for slave to process information
            __delay_cycles(40);

            break;
        default: break;
    }
}

