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
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//*****************************************************************************
//!   SPI slave talks to SPI master using 3-wire mode. Data received
//!   from master is echoed back.  USCI RX ISR is used to handle communication,
//!   CPU normally in LPM4.  Prior to initial data exchange, master pulses
//!   slaves RST for complete reset.
//!   ACLK = ~32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz
//!
//!   Use with SPI Master Incremented Data code example.  If the slave is in
//!   debug mode, the reset signal from the master will conflict with slave's
//!   JTAG; to work around, use IAR's "Release JTAG on Go" on slave device.  If
//!   breakpoints are set in slave RX ISR, master must stopped also to avoid
//!   overrunning slave RXBUF.
//!
//!                   MSP430F5438A
//!                 -----------------
//!            /|\ |                 |
//!             |  |                 |
//!    Master---+->|RST              |
//!                |                 |
//!                |             P3.4|-> Data Out (UCA0SIMO)
//!                |                 |
//!                |             P3.5|<- Data In (UCA0SOMI)
//!                |                 |
//!                |             P3.0|<- Serial Clock Out (UCA0CLK)
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
//
//*****************************************************************************

unsigned char transmitData = 0x01, receiveData = 0x00;
unsigned short returnValue = STATUS_FAIL;

void main (void)
{
    //Stop watchdog timer
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //If clock signal from master stays low, it is not yet in SPI mode
    while ( GPIO_INPUT_PIN_LOW ==
            GPIO_getInputPinValue(__MSP430_BASEADDRESS_PORT3_R__,
                GPIO_PORT_P3,
                GPIO_PIN0
                )) ;

    //P3.5,4,0 option select
    GPIO_setAsPeripheralModuleFunctionInputPin(__MSP430_BASEADDRESS_PORT3_R__,
        GPIO_PORT_P3,
        GPIO_PIN0 + GPIO_PIN4 + GPIO_PIN5
        );

    //Initialize slave to MSB first, inactive high clock polarity and 3 wire SPI
    returnValue = SPI_slaveInit(__MSP430_BASEADDRESS_USCI_A0__,
        SPI_MSB_FIRST,
        SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
        SPI_CLOCKPOLARITY_INACTIVITY_HIGH
        );

    if (STATUS_FAIL == returnValue){
        return;
    }

    //Enable SPI Module
    SPI_enable(__MSP430_BASEADDRESS_USCI_A0__);

    //Enable Receive interrupt
    SPI_enableInterrupt(__MSP430_BASEADDRESS_USCI_A0__,
        SPI_RECEIVE_INTERRUPT
        );

    //Enter LPM4, enable interrupts
    __bis_SR_register(LPM4_bits + GIE);
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
                       SPI_TRANSMIT_INTERRUPT
                       )) ;

            //Transmit data to master
            SPI_transmitData(__MSP430_BASEADDRESS_USCI_A0__,
            transmitData
            );

            //Receive data from master
            receiveData = SPI_receiveData(__MSP430_BASEADDRESS_USCI_A0__);

            //Increment data to be transmitted
            transmitData++;

            break;

        default: break;
    }
}

