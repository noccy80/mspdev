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
#include "driverlib/5xx_6xx/i2c.h"
#include "driverlib/5xx_6xx/ucs.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//*****************************************************************************
//! This example shows how to configure the I2C module as a master for
//! single byte transmission in interrupt mode. The address of the slave
//! module that the master is communicating with also set in this example.
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - I2C peripheral
//! - GPIO Port peripheral (for I2C pins)
//! - SCL2
//! - SDA
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - USCI_B0_VECTOR.
//!
//
//*****************************************************************************
//*****************************************************************************
//
//Set the address for slave module. This is a 7-bit address sent in the
//following format:
//[A6:A5:A4:A3:A2:A1:A0:RS]
//
//A zero in the "RS" position of the first byte means that the master
//transmits (sends) data to the selected slave, and a one in this position
//means that the master receives data from the slave.
//
//*****************************************************************************
#define SLAVE_ADDRESS 0x48

unsigned char transmitData;

void main (void)
{
    //Stop WDT
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Assign I2C pins to USCI_B0
    GPIO_setAsPeripheralModuleFunctionInputPin(__MSP430_BASEADDRESS_PORT3_R__,
        GPIO_PORT_P3,
        GPIO_PIN1 + GPIO_PIN2
        );

    //Initialize transmit data packet
    transmitData = 0x01;

    //Initialize Master
    I2C_masterInit(__MSP430_BASEADDRESS_USCI_B0__,
        I2C_CLOCKSOURCE_SMCLK,
        UCS_getSMCLK(__MSP430_BASEADDRESS_UCS__),
        I2C_SET_DATA_RATE_400KBPS
        );

    //Specify slave address
    I2C_setSlaveAddress(__MSP430_BASEADDRESS_USCI_B0__,
        SLAVE_ADDRESS
        );

    //Set in transmit mode
    I2C_setMode(__MSP430_BASEADDRESS_USCI_B0__,
        I2C_TRANSMIT_MODE
        );

    //Enable I2C Module to start operations
    I2C_enable(__MSP430_BASEADDRESS_USCI_B0__);

    //Enable TX interrupt
    I2C_enableInterrupt(__MSP430_BASEADDRESS_USCI_B0__,
        I2C_TRANSMIT_INTERRUPT
        );

    while (1)
    {
        //Send single byte data.
        I2C_masterSendSingleByte(__MSP430_BASEADDRESS_USCI_B0__,
            transmitData
            );

        //Delay until transmission completes
        while (I2C_isBusBusy(__MSP430_BASEADDRESS_USCI_B0__)) ;

        //Delay between each transaction
        __delay_cycles(50);

        //Increment transmit data counter
        transmitData++;
    }
}

//******************************************************************************
//
//This is the USCI_B0 interrupt vector service routine.
//
//******************************************************************************
#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR (void)
{
    switch (__even_in_range(UCB0IV,12)){
        //Vector 12: Transmit buffer empty - TXIF
        case USCI_I2C_UCTXIFG:
        {
            __no_operation();
            break;
        }
        default:  break;
    }
}

