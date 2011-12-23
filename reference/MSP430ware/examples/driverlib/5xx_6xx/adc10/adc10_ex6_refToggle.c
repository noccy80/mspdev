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
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//******************************************************************************
//!
//! ADC10 - Sample A1 Input, Toggle Internal Reference
//!
//!  MSP430F550x Demo
//!  Sample and convert analog voltage at ADC i/p ch A1 in single channel single
//!  conversion mode. Internal reference is toggled between 1.5V and 2.5V and
//!  the ADC measurements are made. With 1V input at A1, Vref+ of 1.5V and 2.5V
//!  gives ADC conv result of ~682 and ~409 respectively. LED at P1.0 is turned
//!  on when ADC conv result >500 (that is with Vref=1.5V) and turned off
//!  otherwise (when Vref=2.5V) Basically with an input between 0.8V and 1.3V
//!  the LED will toggle consistently, with an input below 0.8V the LED will
//!  stay off, and an input above 1.3V the LED will remain on.
//!  ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz, ADC10CLK = ADC10OSC
//!
//!               MSP430F550x
//!            -----------------
//!        /|\|              XIN|-
//!         | |                 |
//!         --|RST          XOUT|-
//!           |                 |
//!           |          P6.1/A1|<- 1V
//!           |             P1.0|-> LED
//!           |                 |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - ADC10 peripheral
//! - GPIO Port peripheral
//! - A1
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//!
//******************************************************************************

//Software delay function definition
void delay (void);

void main (void)
{
    unsigned short vRefStatus;

    //Stop Watchdog Timer
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Initialize the ADC10 Module
    /*
     * Base Address for the ADC10 Module
     * Use internal ADC10 bit as sample/hold signal to start conversion
     * USE MODOSC 5MHZ Digital Oscillator as clock source
     * Use default clock divider of 1
     */
    ADC10_init(__MSP430_BASEADDRESS_ADC10_A__,
        ADC10_SAMPLEHOLDSOURCE_SC,
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

    //Configure internal reference
    //If ref generator busy, WAIT
    while ( REF_BUSY == REF_isRefGenBusy(__MSP430_BASEADDRESS_REF__) ) ;
    //Select internal ref = 1.5V
    REF_setReferenceVoltage(__MSP430_BASEADDRESS_REF__,
        REF_VREF1_5V);
    //Internal Reference ON
    REF_enableReferenceVoltage(__MSP430_BASEADDRESS_REF__);
    //vRefStatus == 1 for Vref == 1.5V
    vRefStatus = 1;

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

    while (1)
    {
        //Enable and Start the conversion
        //in Single-Channel, Single-Conversion Mode
        ADC10_startConversion(__MSP430_BASEADDRESS_ADC10_A__,
            ADC10_SINGLECHANNEL);

        //Toggle internal reference voltage
        //If ref generator busy, WAIT
        while ( REF_BUSY == REF_isRefGenBusy(__MSP430_BASEADDRESS_REF__) ) ;

        //Toggle Internal Ref between 1.5V/2.5V
        if (vRefStatus){  //Vref == 1.5V
            //Select internal ref = 2.5V
            REF_setReferenceVoltage(__MSP430_BASEADDRESS_REF__,
                REF_VREF2_5V);
            //vRefStatus == 0 for Vref == 2.5V
            vRefStatus = 0;
        } else   { //Vref == 2.5V
            //Select internal ref = 1.5V
            REF_setReferenceVoltage(__MSP430_BASEADDRESS_REF__,
                REF_VREF1_5V);
            //vRefStatus == 1 for Vref == 1.5V
            vRefStatus = 1;
        }

        //Conversion complete?
        while (!(ADC10_getInterruptStatus(__MSP430_BASEADDRESS_ADC10_A__,
                     ADC10IFG0))) ;

        //Is ADC10MEM0 = A1 > 500
        if (ADC10_getResults(__MSP430_BASEADDRESS_ADC10_A__) > 500){
            //Set P1.0 LED on
            GPIO_setOutputHighOnPin(
                __MSP430_BASEADDRESS_PORT1_R__,
                GPIO_PORT_P1,
                GPIO_PIN0
                );
        } else   {
            //Clear P1.0; LED off; Vref=2.5V used
            GPIO_setOutputLowOnPin(
                __MSP430_BASEADDRESS_PORT1_R__,
                GPIO_PORT_P1,
                GPIO_PIN0
                );
        }

        //Delay between conversions
        delay();
    }
}

void delay (void)
{
    volatile unsigned long i;

    for (i = 0x7FFF; i > 0; i--){}
}

