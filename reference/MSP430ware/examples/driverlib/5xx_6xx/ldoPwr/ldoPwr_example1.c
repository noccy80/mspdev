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
//!   MSP430F530x Demo - Internal LDO powering device VCC and PortU
//!
//!   Description: This example code shows the device can be automatically
//!   powered up by the internal LDO when sufficicnt is present at the LDOI pin
//!   and how the external connection between LDOO and VCC can be used to power
//!   the device VCC.
//!
//!   Note:
//!    1.To power the MSP430 device VCC via the internal LDO, connect  LDOO to
//!      VCC externally. If using TI target board (MSP-TS430RGC64B), jumper pin
//!      header JP4
//!    2.Ensure current drawn by device VCC is < ILDOO spec
//!
//!   ACLK = 32.768kHz, MCLK = SMCLK = default DCO~1MHz
//!
//!                MSP430F530x
//!             -----------------
//!        /|\|              VCC|<-
//!         | |                 |  |(jumper JP4 on MSP-TS430RGC64B)
//!         --|RST          LDOO|--
//!           |                 |
//!           |             LDOI|<-- LDO Input Voltage (3.76V to 5.5V -
//!           |                 |   refer to the d/s specs for actual range)
//!           |             PU.0|--> Toggle
//!           |             PU.1|--> Toggle (complementary to PU.0)
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - LDO-PWR module
//! - GPIO Port peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - LDO_PWR_VECTOR.
//!
//******************************************************************************

#include "inc/hw_memmap.h"
#include "driverlib/5xx_6xx/ldoPwr.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

void main (void)
{
    volatile unsigned int i;

    //Stop WDT
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Enable access to config registers
    LDOPWR_unLockConfiguration(__MSP430_BASEADDRESS_PU__);

    //Configure PU.0 as output pins
    LDOPWR_enablePort_U_outputs(__MSP430_BASEADDRESS_PU__);

    //Set PU.1 = high
    LDOPWR_setPort_U1_outputData(__MSP430_BASEADDRESS_PU__,
        LDOPWR_PORTU_PIN_HIGH
        );

    //Set PU.0 = low
    LDOPWR_setPort_U0_outputData(__MSP430_BASEADDRESS_PU__,
        LDOPWR_PORTU_PIN_LOW
        );

    //Enable LDO overload indication interrupt
    LDOPWR_enableInterrupt(__MSP430_BASEADDRESS_PU__,
        LDOPWR_LDO_OVERLOAD_INDICATION_INTERRUPT
        );

    //Disbale access to config registers
    LDOPWR_lockConfiguration(__MSP430_BASEADDRESS_PU__);

    //continuous loop
    while (1)
    {
        //Delay
        for (i = 50000; i > 0; i--){}

        //Enable access to config registers
        LDOPWR_unLockConfiguration(__MSP430_BASEADDRESS_PU__);

        //XOR PU.0/1
        LDOPWR_togglePort_U1_outputData(__MSP430_BASEADDRESS_PU__);
        LDOPWR_togglePort_U0_outputData(__MSP430_BASEADDRESS_PU__);

        //Disbale access to config registers
        LDOPWR_lockConfiguration(__MSP430_BASEADDRESS_PU__);
    }
}

//******************************************************************************
//
//This is the LDO_PWR_VECTOR interrupt vector service routine.
//
//******************************************************************************
#pragma vector=LDO_PWR_VECTOR
__interrupt void LDOInterruptHandler (void)
{
    if (LDOPWR_getInterruptStatus(__MSP430_BASEADDRESS_PU__,
            LDOPWR_LDO_OVERLOAD_INDICATION_INTERRUPT
            )){
        //Enable access to config registers
        LDOPWR_unLockConfiguration(__MSP430_BASEADDRESS_PU__);

        //Software clear IFG
        LDOPWR_clearInterruptStatus(__MSP430_BASEADDRESS_PU__,
            LDOPWR_LDO_OVERLOAD_INDICATION_INTERRUPT
            );

        //Disable access to config registers
        LDOPWR_lockConfiguration(__MSP430_BASEADDRESS_PU__);

        //Over load indication; take necessary steps in application firmware
        while (1) ;
    }
}

