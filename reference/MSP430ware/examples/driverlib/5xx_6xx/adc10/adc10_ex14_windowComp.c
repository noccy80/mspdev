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
#include "driverlib/5xx_6xx/adc10.h"
#include "driverlib/5xx_6xx/ref.h"
#include "driverlib/5xx_6xx/timer.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//******************************************************************************
//!
//! ADC10 - Sample A1 Input, Window Comparator, 2.5V Internal Ref, TB0 Trigger
//!
//!  MSP430F550x Demo
//!  A1 is sampled in every 0.5s using the TA0.0 trigger in single ch/conversion
//!  mode. Window comparator is used to generate interrupts to indicate when the
//!  input voltage goes above the High_Threshold or below the Low_Threshold or
//!  is in between the high and low thresholds. TimerB0 is used as an interval
//!  timer used to control the LED at P1.0 to toggle slow/fast or turn off
//!  according to the ADC10 Hi/Lo/IN interupts. ADC10 is configured in pulse
//!  sample mode and is triggered by the TA0.0
//!
//!               MSP430F550x
//!            -----------------
//!        /|\|              XIN|-
//!         | |                 |
//!         --|RST          XOUT|-
//!           |          P6.1/A1|<- Sample Signal
//!           |             P1.0|-> LED [toggle slow/fast or turn off]
//!           |                 |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - ADC10 peripheral
//! - REF peripheral
//! - Timer_B peripheral
//! - GPIO Port peripheral
//! - A1
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - ADC10_VECTOR
//! - TIMER0_B0_VECTOR
//!
//******************************************************************************

//~2.0V Input
#define High_Threshold 818
//~1.0V Input
#define Low_Threshold 409

#define SlowToggle_Period  20000 - 1
#define FastToggle_Period  1000 - 1

void main (void)
{
    //Stop Watchdog Timer
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Initialize the ADC10 Module
    /*
     * Base Address for the ADC10 Module
     * Use Timer_A0 to signal a sample/hold-and-convert
     * USE MODOSC 5MHZ Digital Oscillator as clock source
     * Use default clock divider of 1
     */
    ADC10_init(__MSP430_BASEADDRESS_ADC10_A__,
        ADC10_SAMPLEHOLDSOURCE_1,
        ADC10_CLOCKSOURCE_ADC10OSC,
        ADC10_CLOCKDIVIDER_1);
    
    ADC10_enable(__MSP430_BASEADDRESS_ADC10_A__);
    
    /*
     * Base Address for the ADC10 Module
     * Sample/hold for 16 clock cycles
     * Do not enable Multiple Sampling
     */
    ADC10_setupSamplingTimer(__MSP430_BASEADDRESS_ADC10_A__,
        ADC10_CYCLEHOLD_16_CYCLES,
        ADC10_MULTIPLESAMPLESDISABLE);

    //Configure Memory Buffer
    /*
     * Base Address for the ADC10 Module
     * Use input A1
     * Use positive reference of Internally generated Vref
     * Use negative reference of AVss
     */
    ADC10_memoryConfigure(__MSP430_BASEADDRESS_ADC10_A__,
        ADC10_INPUT_A1,
        ADC10_VREFPOS_INT,
        ADC10_VREFNEG_AVSS);

    //Configure Window Comparator
    /*
     * Base Address for the ADC10 Module
     * Set the high threshold of the window comparator
     * Set the low threshold of the window comparator
     */
    ADC10_setWindowComp(__MSP430_BASEADDRESS_ADC10_A__,
        High_Threshold,
        Low_Threshold);

    //Enable all window comparator interrupts
    ADC10_enableInterrupt(__MSP430_BASEADDRESS_ADC10_A__,
        ADC10HIIE + ADC10LOIE + ADC10INIE);

    //Configure internal reference
    //If ref generator busy, WAIT
    while ( REF_BUSY == REF_isRefGenBusy(__MSP430_BASEADDRESS_REF__) ) ;
    //Select internal ref = 1.5V
    REF_setReferenceVoltage(__MSP430_BASEADDRESS_REF__,
        REF_VREF2_5V);
    //Internal Reference ON
    REF_enableReferenceVoltage(__MSP430_BASEADDRESS_REF__);

    //Delay (~75us) for Ref to settle
    __delay_cycles(75);


    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //Clear P1.0 LED off
    GPIO_setOutputLowOnPin(
        __MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //Configure TB0 period-timer
    Timer_startUpMode(__MSP430_BASEADDRESS_T0B7__,
        TIMER_CLOCKSOURCE_ACLK,
        TIMER_CLOCKSOURCE_DIVIDER_1,
        0,
        TIMER_TAIE_INTERRUPT_DISABLE,
        TIMER_CCIE_CCR0_INTERRUPT_ENABLE,
        TIMER_DO_CLEAR);

    //Configure ADC10 timer trigger TA0.1
    Timer_initCompare(__MSP430_BASEADDRESS_T0A5__,
        TIMER_CAPTURECOMPARE_REGISTER_1,
        TIMER_CAPTURECOMPARE_INTERRUPT_DISABLE,
        TIMER_OUTPUTMODE_TOGGLE,
        8192 - 1);

    Timer_startUpMode(__MSP430_BASEADDRESS_T0A5__,
        TIMER_CLOCKSOURCE_ACLK,
        TIMER_CLOCKSOURCE_DIVIDER_1,
        16384 - 1,
        TIMER_TAIE_INTERRUPT_DISABLE,
        TIMER_CCIE_CCR0_INTERRUPT_DISABLE,
        TIMER_DO_CLEAR);

    //Enable and Start the conversion
    //in Repeated Single-Channel Conversion Mode
    ADC10_startConversion(__MSP430_BASEADDRESS_ADC10_A__,
        ADC10_REPEATED_SINGLECHANNEL);

    //Enter LPM3 w/ interrupts
    __bis_SR_register(LPM3_bits + GIE);
    //for debugger
    __no_operation();
}

//ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
    switch (__even_in_range(ADC10IV,12)){
        case  0: break; //No interrupt
        case  2: break; //conversion result overflow
        case  4: break; //conversion time overflow
        case  6:        //ADC10HIIFG
            //Turn off Timer
            Timer_stop(__MSP430_BASEADDRESS_T0B7__);

            //Set Timer Period for slow LED toggle
            Timer_startUpMode(__MSP430_BASEADDRESS_T0B7__,
            TIMER_CLOCKSOURCE_ACLK,
            TIMER_CLOCKSOURCE_DIVIDER_1,
            FastToggle_Period,
            TIMER_TAIE_INTERRUPT_DISABLE,
            TIMER_CCIE_CCR0_INTERRUPT_ENABLE,
            TIMER_SKIP_CLEAR);
            break;

        case  8:        //ADC10LOIFG
            //Turn off Timer
            Timer_stop(__MSP430_BASEADDRESS_T0B7__);

            //Clear P1.0 LED off
            GPIO_setOutputLowOnPin(
            __MSP430_BASEADDRESS_PORT1_R__,
            GPIO_PORT_P1,
            GPIO_PIN0
            );
            break;

        case 10:        //ADC10INIFG
            //Turn off Timer
            Timer_stop(__MSP430_BASEADDRESS_T0B7__);

            //Set Timer Period for slow LED toggle
            Timer_startUpMode(__MSP430_BASEADDRESS_T0B7__,
            TIMER_CLOCKSOURCE_ACLK,
            TIMER_CLOCKSOURCE_DIVIDER_1,
            SlowToggle_Period,
            TIMER_TAIE_INTERRUPT_DISABLE,
            TIMER_CCIE_CCR0_INTERRUPT_ENABLE,
            TIMER_SKIP_CLEAR);
            break;
        case 12: break; //ADC10IFG0
        default: break;
    }
}

//Timer1 B0 interrupt service routine
#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMER0_B0_ISR (void)
{
    //Toggle P1.0
    GPIO_toggleOutputOnPin(
        __MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );
}

