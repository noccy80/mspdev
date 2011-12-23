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
//! MSP430F5529 Demo - Port Mapping Port4; Single runtime configuration
//!
//! Port4 is port mapped to output TimerB digital signals. TBCCR1-6
//! generate different PWM DutyCycles and have been output on Port4 pins. TBCCR0
//! generates a square wave of freq ACLK/2^10 ~32Hz.
//! MCLK = SMCLK = default DCO; ACLK = REFO~32kHz;
//!
//!                 MSP430F5529
//!             ------------------
//!         /|\|                  |
//!          | |                  |
//!          --|RST               |
//!            |     P4.0(TB0CCR0)|--> ACLK/2^10 ~ 32Hz
//!            |     P4.1(TB0CCR1)|--> 25%
//!            |     P4.2(TB0CCR2)|--> 50%
//!            |     P4.3(TB0CCR3)|--> 62.5%
//!            |     P4.4(TB0CCR4)|--> 75%
//!            |     P4.5(TB0CCR5)|--> 87.5%
//!            |     P4.6(TB0CCR6)|--> 94%
//!            |     P4.7(PM_None)|--> DVSS
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - PMAP module
//! - GPIO Port peripheral
//! - UCS module
//! - Timer module
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//!
//******************************************************************************
#include "inc/hw_memmap.h"
#include "driverlib/5xx_6xx/pmap.h"
#include "driverlib/5xx_6xx/ucs.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/timer.h"
#include "driverlib/5xx_6xx/gpio.h"

//*****************************************************************************
//
//Refer Datasheet for Port4 Port Mapping definitions
//
//*****************************************************************************

const unsigned char port_mapping[] = {
    //Port P4:
    PM_TB0CCR0A,
    PM_TB0CCR1A,
    PM_TB0CCR2A,
    PM_TB0CCR3A,
    PM_TB0CCR4A,
    PM_TB0CCR5A,
    PM_TB0CCR6A,
    PM_NONE
};

void main (void)
{
    //Stop WDT
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set DCO FLL reference = REFO
    UCS_clockSignalInit(
        __MSP430_BASEADDRESS_UCS__,
        UCS_FLLREF,
        UCS_REFOCLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );

    //VLO Clock Sources ACLK
    UCS_clockSignalInit(
        __MSP430_BASEADDRESS_UCS__,
        UCS_ACLK,
        UCS_REFOCLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );


    //Set Ratio and Desired MCLK Frequency  and initialize DCO
    UCS_initFLLSettle(
        __MSP430_BASEADDRESS_UCS__,
        1048,
        32
        );

    //Setup Port Pins
    //P4.0 - P4.7 output
    //P4.0 - P4.7 Port Map functions
    GPIO_setAsPeripheralModuleFunctionOutputPin(__MSP430_BASEADDRESS_PORT4_R__,
        GPIO_PORT_P4,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2 +
        GPIO_PIN3 + GPIO_PIN4 + GPIO_PIN5 +
        GPIO_PIN6 + GPIO_PIN7 + GPIO_PIN8 +
        GPIO_PIN9 + GPIO_PIN10 + GPIO_PIN11 +
        GPIO_PIN12 + GPIO_PIN13 + GPIO_PIN14 +
        GPIO_PIN15
        );

    //CONFIGURE PORTS- pass the port_mapping array, start @ P4MAP01, initialize
    //a single port, do not allow run-time reconfiguration of port mapping
    PMAP_configurePorts(__MSP430_BASEADDRESS_PORT_MAPPING__,
        (const unsigned char  *)port_mapping,
        (unsigned char  *)&P4MAP01,
        1,
        PMAP_DISABLE_RECONFIGURATION
        );

    //Start Up Down Timer
    Timer_startUpDownMode( __MSP430_BASEADDRESS_T0B7__,
        TIMER_CLOCKSOURCE_ACLK,
        TIMER_CLOCKSOURCE_DIVIDER_1,
        256,
        TIMER_TAIE_INTERRUPT_DISABLE,
        TIMER_CCIE_CCR0_INTERRUPT_DISABLE,
        TIMER_SKIP_CLEAR
        );

    //Generate PWM 1
    Timer_initCompare(__MSP430_BASEADDRESS_T0B7__,
        TIMER_CAPTURECOMPARE_REGISTER_1,
        TIMER_CAPTURECOMPARE_INTERRUPT_DISABLE,
        TIMER_OUTPUTMODE_TOGGLE_SET,
        192
        );

    //Generate PWM 2
    Timer_initCompare(__MSP430_BASEADDRESS_T0B7__,
        TIMER_CAPTURECOMPARE_REGISTER_2,
        TIMER_CAPTURECOMPARE_INTERRUPT_DISABLE,
        TIMER_OUTPUTMODE_TOGGLE_SET,
        128
        );

    //Generate PWM 3
    Timer_initCompare(__MSP430_BASEADDRESS_T0B7__,
        TIMER_CAPTURECOMPARE_REGISTER_3,
        TIMER_CAPTURECOMPARE_INTERRUPT_DISABLE,
        TIMER_OUTPUTMODE_TOGGLE_SET,
        96
        );

    //Generate PWM 4
    Timer_initCompare(__MSP430_BASEADDRESS_T0B7__,
        TIMER_CAPTURECOMPARE_REGISTER_4,
        TIMER_CAPTURECOMPARE_INTERRUPT_DISABLE,
        TIMER_OUTPUTMODE_TOGGLE_SET,
        64
        );

    //Generate PWM 5
    Timer_initCompare(__MSP430_BASEADDRESS_T0B7__,
        TIMER_CAPTURECOMPARE_REGISTER_5,
        TIMER_CAPTURECOMPARE_INTERRUPT_DISABLE,
        TIMER_OUTPUTMODE_TOGGLE_SET,
        32
        );

    //Generate PWM 6
    Timer_initCompare(__MSP430_BASEADDRESS_T0B7__,
        TIMER_CAPTURECOMPARE_REGISTER_6,
        TIMER_CAPTURECOMPARE_INTERRUPT_DISABLE,
        TIMER_OUTPUTMODE_TOGGLE_SET,
        16
        );

    //Enter LPM3
    __bis_SR_register(LPM3_bits);

    //For debugger
    __no_operation();
}

