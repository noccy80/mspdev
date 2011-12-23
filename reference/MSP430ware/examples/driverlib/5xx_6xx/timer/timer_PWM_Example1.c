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
//*******************************************************************************
//!  MSP430F543xA Demo - Timer_A3, PWM TA1.1-2, Up Mode, DCO SMCLK
//!
//!  Description: This program generates PWM outputs on P2.2 using
//!  Timer1_A configured for up mode. The value , TIMER_PERIOD, defines the PWM
//!  period and the value DUTY_CYCLE the PWM duty cycle. Using ~1.045MHz
//!  SMCLK as TACLK, the timer period is ~500us with a 75% duty cycle on P2.2
//!   ACLK = n/a, SMCLK = MCLK = TACLK = default DCO ~1.045MHz.
//!
//!                MSP430F5438A
//!            -------------------
//!        /|\|                   |
//!         | |                   |
//!         --|RST                |
//!           |                   |
//!           |         P2.2/TA1.1|--> CCR1 - 75% PWM
//!           |                   |
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - Timer peripheral
//! - GPIO Port peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - NONE
//******************************************************************************

#include "inc/hw_memmap.h"
#include "driverlib/5xx_6xx/timer.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

#define TIMER_PERIOD 511
#define DUTY_CYCLE  350


void main (void)
{
    //Stop WDT
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //P2.2 and P2.3 output
    //P2.2 and P2.3 options select
    GPIO_setAsPeripheralModuleFunctionOutputPin(__MSP430_BASEADDRESS_PORT2_R__,
        GPIO_PORT_P2,
        GPIO_PIN2 + GPIO_PIN3
        );


    //Generate PWM - Timer runs in Up-Down mode
    Timer_generatePWM(  __MSP430_BASEADDRESS_T1A3__,
        TIMER_CLOCKSOURCE_SMCLK,
        TIMER_CLOCKSOURCE_DIVIDER_1,
        TIMER_PERIOD,
        TIMER_CAPTURECOMPARE_REGISTER_1,
        TIMER_OUTPUTMODE_RESET_SET,
        DUTY_CYCLE
        );

    //Enter LPM0
    __bis_SR_register(LPM0_bits);

    //For debugger
    __no_operation();
}

