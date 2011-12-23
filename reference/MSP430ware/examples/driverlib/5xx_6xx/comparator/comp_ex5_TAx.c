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
#include "driverlib/5xx_6xx/compb.h"
#include "driverlib/5xx_6xx/ucs.h"
#include "driverlib/5xx_6xx/timer.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//******************************************************************************
//! COMPB - TA0.1, TA1.1, Varying duty cycle of input voltage
//!
//!  Use CompB to determine if input, Vcompare has a duty cycle greater than
//!  50%. When Vcompare exceeds Vcc*3/4 then TimerA0 captures the time
//!  (TA0CCR1). When Vcompare is less than Vcc*1/4 then TimerA1 captures the
//!  time (TA1CCR1) and resets the timers for TIMERA0 and TIMERA1. If TA0CCR1
//!  is greater than TA1CCR1/2, then turn on the LED. If TA0CCR1 is less
//!  than TA1CCR1/2, then turn off the LED.
//!  Clocks: ACLK = REFO; MCLK = SMCLK = 12MHz
//!
//!             MSP430x552x
//!         ------------------
//!     /|\|                  |
//!      | |                  |
//!      --|RST       P6.0/CB0|<- Vcompare (200Hz<f<1Mhz) (vary dutycycle)
//!        |              P1.0|-> LED ('ON' if dutycycle > 50%;
//!        |                  |        'OFF' if dutycycle < 50%)
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - COMPB peripheral
//! - GPIO Port peripheral
//! - CB0
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - TIMER1_A1_VECTOR
//!
//******************************************************************************
#define TIMER_PERIOD 0xFFFF
#define UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ 12000
#define UCS_MCLK_FLLREF_RATIO 374

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

    //Set ACLK = REFO
    UCS_clockSignalInit(
        __MSP430_BASEADDRESS_UCS__,
        UCS_ACLK,
        UCS_REFOCLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );

    //Set Ratio and Desired MCLK Frequency  and initialize DCO
    UCS_initFLLSettle(
        __MSP430_BASEADDRESS_UCS__,
        UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ,
        UCS_MCLK_FLLREF_RATIO
        );


    //Initialize the Comparator B module
    /*
     * Base Address of Comparator B,
     * Pin CB0 to Positive(+) Terminal,
     * Reference Voltage to Negative(-) Terminal,
     * Normal Power Mode,
     * Output Filter On with minimal delay,
     * Non-Inverted Output Polarity
     */
    COMPB_init(__MSP430_BASEADDRESS_COMPB__,
        COMPB_INPUT0,
        COMPB_VREF,
        COMPB_POWERMODE_NORMALMODE,
        COMPB_FILTEROUTPUT_DLYLVL1,
        COMPB_NORMALOUTPUTPOLARITY
        );

    //Set the reference voltage that is being supplied to the (-) terminal
    /*
     * Base Address of Comparator B,
     * Reference Voltage of 2.0 V,
     * Upper Limit of Vcc*(8/32) = (1/4)*Vcc,
     * Lower Limit of Vcc*(24/32) = (3/4)*Vcc
     */
    COMPB_setReferenceVoltage(__MSP430_BASEADDRESS_COMPB__,
        COMPB_VREFBASE_VCC,
        8,
        24
        );

    //Allow power to Comparator module
    COMPB_enable(__MSP430_BASEADDRESS_COMPB__);

    //delay for the reference to settle
    __delay_cycles(75);

    //Start timer Timer_A0 in up mode
    Timer_startUpMode(   __MSP430_BASEADDRESS_T0A5__,
        TIMER_CLOCKSOURCE_SMCLK,
        TIMER_CLOCKSOURCE_DIVIDER_1,
        TIMER_PERIOD,
        TIMER_TAIE_INTERRUPT_DISABLE,
        TIMER_CCIE_CCR0_INTERRUPT_DISABLE,
        TIMER_DO_CLEAR
        );

    //Start timer Timer_A1 in up mode
    Timer_startUpMode(   __MSP430_BASEADDRESS_T1A3__,
        TIMER_CLOCKSOURCE_SMCLK,
        TIMER_CLOCKSOURCE_DIVIDER_1,
        TIMER_PERIOD,
        TIMER_TAIE_INTERRUPT_DISABLE,
        TIMER_CCIE_CCR0_INTERRUPT_DISABLE,
        TIMER_DO_CLEAR
        );

    //Capture Falling Edge
    Timer_initCapture(__MSP430_BASEADDRESS_T0A5__,
        TIMER_CAPTURECOMPARE_REGISTER_1,
        TIMER_CAPTUREMODE_FALLING_EDGE,
        TIMER_CAPTURE_INPUTSELECT_CCIxB,
        TIMER_CAPTURE_SYNCHRONOUS,
        TIMER_CAPTURECOMPARE_INTERRUPT_DISABLE,
        TIMER_OUTPUTMODE_OUTBITVALUE
        );

    //Capture Rising Edge, Enable Interrupt
    Timer_initCapture(__MSP430_BASEADDRESS_T1A3__,
        TIMER_CAPTURECOMPARE_REGISTER_1,
        TIMER_CAPTUREMODE_RISING_EDGE,
        TIMER_CAPTURE_INPUTSELECT_CCIxB,
        TIMER_CAPTURE_SYNCHRONOUS,
        TIMER_CAPTURECOMPARE_INTERRUPT_ENABLE,
        TIMER_OUTPUTMODE_OUTBITVALUE
        );

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //Enter LPM0 with global interrupts enabled
    __bis_SR_register(LPM3_bits + GIE);

    //For Debug
    __no_operation();
}

//******************************************************************************
//
//This is the TIMER1_A1_VECTOR interrupt vector service routine.
//
//******************************************************************************
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer_A (void)
{
    unsigned int temp;

    switch ( TA1IV){
        case  2:

            //Re-Start timer Timer_A0
            Timer_startUpMode(   __MSP430_BASEADDRESS_T0A5__,
            TIMER_CLOCKSOURCE_SMCLK,
            TIMER_CLOCKSOURCE_DIVIDER_1,
            TIMER_PERIOD,
            TIMER_TAIE_INTERRUPT_DISABLE,
            TIMER_CCIE_CCR0_INTERRUPT_DISABLE,
            TIMER_DO_CLEAR
            );

            //Re-Start timer Timer_A1
            Timer_startUpMode(   __MSP430_BASEADDRESS_T1A3__,
            TIMER_CLOCKSOURCE_SMCLK,
            TIMER_CLOCKSOURCE_DIVIDER_1,
            TIMER_PERIOD,
            TIMER_TAIE_INTERRUPT_DISABLE,
            TIMER_CCIE_CCR0_INTERRUPT_DISABLE,
            TIMER_DO_CLEAR
            );

            //Compare On and off time of input signal
            temp = (Timer_getCaptureCompareCount(__MSP430_BASEADDRESS_T1A3__,
                        TIMER_CAPTURECOMPARE_REGISTER_1
                        )) >> 1;

            if (Timer_getCaptureCompareCount(__MSP430_BASEADDRESS_T0A5__,
                    TIMER_CAPTURECOMPARE_REGISTER_1
                    ) > temp){
                //set P1.0
                GPIO_setOutputHighOnPin(
                    __MSP430_BASEADDRESS_PORT1_R__,
                    GPIO_PORT_P1,
                    GPIO_PIN0
                    );
            } else   {
                //Clear P1.0 LED off
                GPIO_setOutputLowOnPin(
                    __MSP430_BASEADDRESS_PORT1_R__,
                    GPIO_PORT_P1,
                    GPIO_PIN0
                    );
            }
            break;
        case  4: break;  //CCR2 not used
        case  6: break;  //CCR3 not used
        case  8: break;  //CCR4 not used
        case 10: break;  //CCR5 not used
        case 12: break;  //Reserved not used
        case 14:         //Overflow
            __no_operation();

            //If input frequency < 200Hz, trap here
            while (1) ;
        default: break;
    }
}

