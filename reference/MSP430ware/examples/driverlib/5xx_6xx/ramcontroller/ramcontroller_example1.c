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
//!  MSP430F543xA Demo - RAM controller turn off RAM sector
//!
//!  Description: Switch RAM sector off instead of retention state during low
//!  low power modes.
//!
//!           MSP430F5438A
//!         ---------------
//!        |               |
//!        |               |
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - Timer peripheral
//! - GPIO Port peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - Timer B0
//!
//
//*****************************************************************************

#include "inc/hw_memmap.h"
#include "driverlib/5xx_6xx/ramcontroller.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"
#include "driverlib/5xx_6xx/timer.h"

unsigned char returnValue;

void main (void)
{
    //Stop WDT
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );
    //Start timer
    Timer_startUpMode(   __MSP430_BASEADDRESS_T0B7__,
        TIMER_CLOCKSOURCE_ACLK,
        TIMER_CLOCKSOURCE_DIVIDER_1,
        25000,
        TIMER_TAIE_INTERRUPT_DISABLE,
        TIMER_CAPTURECOMPARE_INTERRUPT_ENABLE,
        TIMER_DO_CLEAR
        );

    //RAM controller sector off
    ramController_setSectorOff(__MSP430_BASEADDRESS_RC__,
        RAMCONTROL_SECTOR2
        ) ;


    //Enter LPM0, enable interrupts
    __bis_SR_register(LPM3_bits + GIE);

    //For debugger
    __no_operation();
}

//******************************************************************************
//
//This is the Timer B0 interrupt vector service routine.
//
//******************************************************************************
#pragma vector=TIMERB0_VECTOR
__interrupt void TIMERB0_ISR (void)
{
    returnValue = ramController_getSectorState(__MSP430_BASEADDRESS_RC__,
        RAMCONTROL_SECTOR0 +
        RAMCONTROL_SECTOR1 +
        RAMCONTROL_SECTOR2 +
        RAMCONTROL_SECTOR3);

    //Toggle P1.0 using exclusive-OR
    GPIO_toggleOutputOnPin(
        __MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );
}

