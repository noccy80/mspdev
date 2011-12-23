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
//!   MSP430F530x Demo  - Software Poll PU.0, Set P1.0 if PU.0 = 1
//!
//!  Description: Poll PU.0 in a loop, if hi P1.0 is set, if low, P1.0 reset.
//!  ACLK = n/a, MCLK = SMCLK = default DCO
//!
//!              MSP430F530x
//!            -----------------
//!        /|\|              VCC|--
//!         | |                 |  |
//!         --|RST          LDOO|<-
//!     /|\   |                 |
//!      --o--|PU.0         P1.0|-->LED
//!     \|/
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - LDO-PWR module
//! - GPIO Port peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//!
//******************************************************************************
#include "inc/hw_memmap.h"
#include "driverlib/5xx_6xx/ldoPwr.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

void main (void)
{
    //Stop WDT
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Enable access to config registers
    LDOPWR_unLockConfiguration(__MSP430_BASEADDRESS_PU__);

    //Configure PU.0 as input pin
    //PortU input enable
    LDOPWR_enablePort_U_inputs(__MSP430_BASEADDRESS_PU__);


    //Disbale access to config registers
    LDOPWR_lockConfiguration(__MSP430_BASEADDRESS_PU__);

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    while (1)
    {
        //Test P1.4
        if (LDOPWR_PORTU_PIN_HIGH == LDOPWR_getPort_U0_inputData(
                __MSP430_BASEADDRESS_PU__
                ) ){
            //if P1.4 set, set P1.0
            GPIO_setOutputHighOnPin(
                __MSP430_BASEADDRESS_PORT1_R__,
                GPIO_PORT_P1,
                GPIO_PIN0
                );
        } else   {
            //else reset
            //Clear P1.0 LED off
            GPIO_setOutputLowOnPin(
                __MSP430_BASEADDRESS_PORT1_R__,
                GPIO_PORT_P1,
                GPIO_PIN0
                );
        }
    }
}

