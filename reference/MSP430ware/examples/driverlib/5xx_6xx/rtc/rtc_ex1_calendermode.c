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
#include "driverlib/5xx_6xx/rtc.h"
#include "driverlib/5xx_6xx/sfr_sys.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"
#include "driverlib/5xx_6xx/ucs.h"

//******************************************************************************
//!
//! RTC - RTC_A in Calendar mode, Interruptions every 1s, 1m, and 5th day of
//!     week at 5:00pm
//!
//!  This program demonstrates the RTC mode by triggering an interrupt every
//!  second and minute. This code toggles P1.0 every second. This code
//!  recommends an external LFXT1 crystal for RTC accuracy.
//!  Note that if XT1 is not present the code loops in an infinite loop.
//!  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//!
//!                MSP430F54xA
//!             -----------------
//!        /|\ |              XIN|-
//!         |  |                 | 32kHz
//!         ---|RST          XOUT|-
//!            |                 |
//!            |            P1.0 |--> Toggles every second
//!            |                 |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - RTC peripheral
//! - UCS peripheral
//! - GPIO Port peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - RTC_VECTOR
//!
//******************************************************************************

volatile Calendar newTime;

void main (void)
{
    Calendar currentTime;

    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );


    GPIO_setAsPeripheralModuleFunctionInputPin(__MSP430_BASEADDRESS_PORT7_R__,
        GPIO_PORT_P7,
        GPIO_PIN0 + GPIO_PIN1
        );

    //Initialize LFXT1
    UCS_LFXT1Start(__MSP430_BASEADDRESS_UCS__,
        UCS_XT1_DRIVE3,
        UCS_XCAP_3
        );

    //Setup Current Time for Calendar
    currentTime.Seconds    = 0x00;
    currentTime.Minutes    = 0x26;
    currentTime.Hours      = 0x13;
    currentTime.DayOfWeek  = 0x03;
    currentTime.DayOfMonth = 0x20;
    currentTime.Month      = 0x07;
    currentTime.Year       = 0x2011;

    //Initialize Calendar Mode of RTC
    /*
     * Base Address of the RTC_A
     * Pass in current time, intialized above
     * Use BCD as Calendar Register Format
     */
    RTC_calendarInit(__MSP430_BASEADDRESS_RTC__,
        currentTime,
        RTC_FORMAT_BCD);

    //Setup Calendar Alarm for 5:00pm on the 5th day of the week.
    //Note: Does not specify day of the week.
    RTC_setCalendarAlarm(__MSP430_BASEADDRESS_RTC__,
        0x00,
        0x17,
        RTC_ALARMCONDITION_OFF,
        0x05);

    //Specify an interrupt to assert every minute
    RTC_setCalendarEvent(__MSP430_BASEADDRESS_RTC__,
        RTC_CALENDAREVENT_MINUTECHANGE);

    //Enable interrupt for RTC Ready Status, which asserts when the RTC
    //Calendar registers are ready to read.
    //Also, enable interrupts for the Calendar alarm and Calendar event.
    RTC_enableInterrupt(__MSP430_BASEADDRESS_RTC__,
        RTCRDYIE + RTCTEVIE + RTCAIE);

    //Start RTC Clock
    RTC_startClock(__MSP430_BASEADDRESS_RTC__);

    //Enter LPM3 mode with interrupts enabled
    __bis_SR_register(LPM3_bits + GIE);
    __no_operation();
}

#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR (void)
{
    switch (__even_in_range(RTCIV,16)){
        case 0: break;  //No interrupts
        case 2:         //RTCRDYIFG
            //Toggle P1.0 every second
            GPIO_toggleOutputOnPin(__MSP430_BASEADDRESS_PORT1_R__,
            GPIO_PORT_P1,
            GPIO_PIN0);
            break;
        case 4:         //RTCEVIFG
            //Interrupts every minute
            __no_operation();

            //Read out New Time a Minute Later BREAKPOINT HERE
            newTime = RTC_getCalendarTime(__MSP430_BASEADDRESS_RTC__);
            break;
        case 6:         //RTCAIFG
            //Interrupts 5:00pm on 5th day of week
            __no_operation();
            break;
        case 8: break;  //RT0PSIFG
        case 10: break; //RT1PSIFG
        case 12: break; //Reserved
        case 14: break; //Reserved
        case 16: break; //Reserved
        default: break;
    }
}

