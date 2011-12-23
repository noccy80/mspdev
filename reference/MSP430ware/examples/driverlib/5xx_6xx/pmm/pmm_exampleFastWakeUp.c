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
//*****************************************************************************
//! PMM @ Core 0, SVSL/SVSH optimized for fast wake up
//!
//!  Description: The PMM is at default core level 0.
//!  The SVS high side (Vcc) is configured for Fast Performance mode.
//!  The SVS low side (Vcore) is disabled.
//!  Specs:
//!  Wake up from interrupt: 5us* (as SVSL  disabled)
//!  Response to SVS event(propogation delay): 2us* (as SVSH enabled in LPM)
//!  Current consumption by SVS: 2uA* (as SVSH enabled in Fast Performance Mode)
//! !Note: Refer to the device D/s for actual values
//!
//!  The timer outputs a PWM with a frequency ~800Hz. The LED at P1.0 is toggled
//!  on entry into the ISR. The time difference between PWM event and LED
//!  toggle =SVS wakeup time + interrupt latency + LED turn on = ~20+us.
//!
//!  NOTE: TERMINATE THE DEBUG SESSION BEFORE TESTING THIS EXAMPLE
//!  Refer section 2.2.8.1 for debug impact on SVS
//!
//!  ACLK = REFO = TACLK = ~32KHz, MCLK = SMCLK = default DCO ~1.045MHz//!
//!
//!           MSP430F54xA
//!         ---------------
//!     /|\|               |
//!      | |               |
//!      --|RST            |
//!        |          TA0.4|--> output from timer
//!        |           P1.0|--> LED
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - PMM peripheral
//! - GPIO Port peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - Timer0_A5.
//*****************************************************************************

#include "inc/hw_memmap.h"
#include "driverlib/5xx_6xx/pmm.h"
#include "driverlib/5xx_6xx/ucs.h"
#include "driverlib/5xx_6xx/timer.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

#define DUTY_CYCLE1     20
#define TIMER_PERIOD    40

void main (void)
{
    //Stop WDT
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set DCO FLL reference = REFO
    UCS_clockSignalInit(__MSP430_BASEADDRESS_UCS__,
        UCS_FLLREF,
        UCS_REFOCLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );

    //Set ACLK = REFO
    UCS_clockSignalInit(__MSP430_BASEADDRESS_UCS__,
        UCS_ACLK,
        UCS_REFOCLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );

    //~ 32*32768 = 1048576
    UCS_initFLLSettle(__MSP430_BASEADDRESS_UCS__,
        1048,
        32
        );

    //SVS Low side is turned off
    PMM_disableSvsL(__MSP430_BASEADDRESS_PMM__);

    //Monitor low side is turned off
    PMM_disableSvmL(__MSP430_BASEADDRESS_PMM__);

    //Monitor high side is turned off
    PMM_disableSvmH(__MSP430_BASEADDRESS_PMM__);

    //SVS High side is turned on
    PMM_enableSvsH(__MSP430_BASEADDRESS_PMM__);

    //Enable POR on SVS Event
    PMM_enableSvsHReset(__MSP430_BASEADDRESS_PMM__);

    //SVS high side Full perf mode,
    PMM_SvsHEnabledInLPMFullPerf(__MSP430_BASEADDRESS_PMM__);

    //stays on in LPM3,enhanced protect
    //Wait until high side, low side settled
    while ( 0 == PMM_getInterruptStatus(__MSP430_BASEADDRESS_PMM__,
                SVSMLDLYIFG + SVSMHDLYIFG )
            ) ;

    PMM_clearPMMIFGS(__MSP430_BASEADDRESS_PMM__);

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

    //P1.5 TA0.4 output 50% duty cycle
    GPIO_setAsPeripheralModuleFunctionOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN5
        );

    //Start timer in upMode sourced by ACLK
    Timer_startUpMode(
        __MSP430_BASEADDRESS_T0A5__,
        TIMER_CLOCKSOURCE_ACLK,
        TIMER_CLOCKSOURCE_DIVIDER_1,
        TIMER_PERIOD,
        TIMER_TAIE_INTERRUPT_ENABLE,
        TIMER_CCIE_CCR0_INTERRUPT_DISABLE,
        TIMER_DO_CLEAR
        );

    //Generate PWM using capture
    Timer_initCompare(__MSP430_BASEADDRESS_T0A5__,
        TIMER_CAPTURECOMPARE_REGISTER_4,
        TIMER_CAPTURECOMPARE_INTERRUPT_ENABLE,
        TIMER_OUTPUTMODE_SET_RESET,
        DUTY_CYCLE1
        );

    //Enter LPM3, enable interrupts
    __bis_SR_register(LPM3_bits + GIE);

    //For debugger
    __no_operation();
}

//******************************************************************************
//
//This is the Timer0_A5 interrupt vector service routine.
//
//******************************************************************************
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR (void)
{
    switch (__even_in_range(TA0IV,14)){
        case  0: break;                          //No interrupt
        case  2: break;                          //CCR1 not used
        case  4: break;                          //CCR2 not used
        case  6: break;                          //reserved
        case  8: break;                          //reserved
        case 10: break;                          //reserved
        case 12: break;                          //reserved
        case 14:                                 //overflow
            //Toggle P1.0
            GPIO_toggleOutputOnPin(
            __MSP430_BASEADDRESS_PORT1_R__,
            GPIO_PORT_P1,
            GPIO_PIN0
            );
            break;
        default: break;
    }
}

