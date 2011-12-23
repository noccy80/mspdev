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
//! MSP430F55x Demo - Port Map single function to multiple pins;
//!		Multiple runtime configurations
//!
//! Description:  The port mapping of TIMERB0 is changed with each WDT interrupt.
//!               TimerB0 provides 4 PWMs with 4 different duty cycles.
//!               TimerB0 is sourced from ACLK.  ACLK is REFO, 32kHz
//!
//!                 MSP430F5528
//!             ------------------------
//!         /|\|                        |
//!          | |                        |
//!          --|RST                     |
//!            |     P4.0(TB0CCR1,2,3,4)|--> 25,50,75,87.5%
//!            |     P4.1(TB0CCR2,3,4,1)|--> 50,75,87.5,25%
//!            |     P4.2(TB0CCR3,4,1,2)|--> 75,87.5,25,50%
//!            |     P4.3(TB0CCR4,1,2,3)|--> 87.5,25,50,75%
//!            |     P4.4(TB0CCR1,2,3,4)|--> 25,50,75,87.5%
//!            |     P4.5(TB0CCR2,3,4,1)|--> 50,75,87.5,25%
//!            |     P4.6(TB0CCR3,4,1,2)|--> 75,87.5,25,50%
//!            |     P4.7(TB0CCR4,1,2,3)|--> 87.5,25,50,75%
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
//! - WDT_VECTOR
//!
//******************************************************************************
#include "inc/hw_memmap.h"
#include "driverlib/5xx_6xx/pmap.h"
#include "driverlib/5xx_6xx/sfr_sys.h"
#include "driverlib/5xx_6xx/ucs.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/timer.h"
#include "driverlib/5xx_6xx/gpio.h"

//*****************************************************************************
//
//Refer Datasheet for Port4 Port Mapping definitions
//
//*****************************************************************************
unsigned char port_mapping[] = {
    //Port 4
    PM_TB0CCR1A,
    PM_TB0CCR2A,
    PM_TB0CCR3A,
    PM_TB0CCR4A,
    PM_TB0CCR1A,
    PM_TB0CCR2A,
    PM_TB0CCR3A,
    PM_TB0CCR4A
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

    //REFO Clock Sources ACLK
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
    //P4.0 - P4.6 Port Map functions
    GPIO_setAsPeripheralModuleFunctionOutputPin(__MSP430_BASEADDRESS_PORT4_R__,
        GPIO_PORT_P4,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2 +
        GPIO_PIN3 + GPIO_PIN4 + GPIO_PIN5 +
        GPIO_PIN6 + GPIO_PIN7 + GPIO_PIN8 +
        GPIO_PIN9 + GPIO_PIN10 + GPIO_PIN11 +
        GPIO_PIN12 + GPIO_PIN13 + GPIO_PIN14 +
        GPIO_PIN15
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
        64
        );

    //Generate PWM 4
    Timer_initCompare(__MSP430_BASEADDRESS_T0B7__,
        TIMER_CAPTURECOMPARE_REGISTER_4,
        TIMER_CAPTURECOMPARE_INTERRUPT_DISABLE,
        TIMER_OUTPUTMODE_TOGGLE_SET,
        32
        );

    //Initialize WDT module in timer interval mode,
    //with ACLK as source at an interval of 1sec.
    WDT_intervalTimerInit(__MSP430_BASEADDRESS_WDT_A__,
        WDT_CLOCKSOURCE_ACLK,
        WDT_CLOCKDIVIDER_32K);

    //Enable Watchdog Interupt
    SFR_enableInterrupt(__MSP430_BASEADDRESS_SFR__,
        WDTIE);

    while (1)
    {
        //CONFIGURE PORTS- pass the port_mapping array, start @ P4MAP01, initialize
        //a single port, allow run-time reconfiguration of port mapping
        PMAP_configurePorts(__MSP430_BASEADDRESS_PORT_MAPPING__,
            (const unsigned char *)port_mapping,
            (unsigned char *)&P4MAP01,
            1,
            PMAP_ENABLE_RECONFIGURATION
            );

        //Enter LPM3 w/interrupt
        __bis_SR_register(LPM3_bits + GIE);

        //For debugger
        __no_operation();

        //Rotate the port map sequence
        unsigned char tempVariable = port_mapping[0];
        unsigned int i = 0;
        for (i = 0; i < 7; i++)
        {
            //Rotate port map array
            port_mapping[i] = port_mapping[i + 1];
        }
        port_mapping[7] = tempVariable;
    }
}

//******************************************************************************
//
//This is the Watchdog Timer interrupt service routine
//
//******************************************************************************
#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer (void)
{
    __delay_cycles(100);

    //Exit LPM3
    __bic_SR_register_on_exit(LPM3_bits);
}

