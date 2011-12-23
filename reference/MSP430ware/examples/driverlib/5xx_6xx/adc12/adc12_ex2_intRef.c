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
#include "driverlib/5xx_6xx/adc12.h"
#include "driverlib/5xx_6xx/ref.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//******************************************************************************
//!
//! ADC12 - Sample A0 Input, 2.5V Internal Ref
//!  MSP430F552x Demo
//!
//!  This example shows how to use the internal reference of REF module using
//!  the REF control registers. The ADC12 uses the internal 2.5V reference
//!  and performs a single conversion on channel A0. The conversion results are
//!  stored in ADC12MEM0. Test by applying a voltage to channel A0, then setting
//!  and running to a break point at the "__no_operation()" instruction. To view
//!  the conversion results, open an ADC12 register window in debugger and view
//!  the contents of ADC12MEM0.
//!
//!                 MSP430F552x
//!             -----------------
//!         /|\|                 |
//!          | |                 |
//!          --|RST       P6.0/A0|<- Vin
//!            |                 |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - ADC12 peripheral
//! - GPIO Port peripheral
//! - A0
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//!
//******************************************************************************

void main (void)
{
    volatile unsigned int i;

    //Stop Watchdog Timer
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Enable A/D channel A0
    GPIO_setAsPeripheralModuleFunctionInputPin(__MSP430_BASEADDRESS_PORT6_R__,
        GPIO_PORT_P6,
        GPIO_PIN0
        );

    //Initialize the ADC12 Module
    /*
     * Base address of ADC12 Module
     * Use internal ADC12 bit as sample/hold signal to start conversion
     * USE MODOSC 5MHZ Digital Oscillator as clock source
     * Use default clock divider of 1
     */
    ADC12_init(__MSP430_BASEADDRESS_ADC12_PLUS__,
        ADC12_SAMPLEHOLDSOURCE_SC,
        ADC12_CLOCKSOURCE_ADC12OSC,
        ADC12_CLOCKDIVIDER_1);
    
    ADC12_enable(__MSP430_BASEADDRESS_ADC12_PLUS__);
        
    /*
     * Base address of ADC12 Module
     * For memory buffers 0-7 sample/hold for 64 clock cycles
     * For memory buffers 8-15 sample/hold for 4 clock cycles (default)
     * Disable Multiple Sampling
     */
    ADC12_setupSamplingTimer(__MSP430_BASEADDRESS_ADC12_PLUS__,
        ADC12_CYCLEHOLD_64_CYCLES,
        ADC12_CYCLEHOLD_4_CYCLES,
        ADC12_MULTIPLESAMPLESDISABLE);

    //Configure Memory Buffer
    /*
     * Base address of the ADC12 Module
     * Configure memory buffer 0
     * Map input A0 to memory buffer 0
     * Vr+ = Vref+ (int)
     * Vr- = AVss
     * Memory buffer 0 is not the end of a sequence
     */
    ADC12_memoryConfigure(__MSP430_BASEADDRESS_ADC12_PLUS__,
        ADC12_MEMORY_0,
        ADC12_INPUT_A0,
        ADC12_VREFPOS_INT,
        ADC12_VREFNEG_AVSS,
        ADC12_NOTENDOFSEQUENCE);

    //Configure internal reference
    //If ref generator busy, WAIT
    while ( REF_ACTIVE == REF_isRefGenBusy(__MSP430_BASEADDRESS_REF__) ) ;
    //Select internal ref = 1.5V
    REF_setReferenceVoltage(__MSP430_BASEADDRESS_REF__,
        REF_VREF1_5V);
    //Internal Reference ON
    REF_enableReferenceVoltage(__MSP430_BASEADDRESS_REF__);

    //Delay (~75us) for Ref to settle
    __delay_cycles(75);


    while (1)
    {
        //Enable/Start first sampling and conversion cycle
        /*
         * Base address of ADC12 Module
         * Start the conversion into memory buffer 0
         * Use the single-channel, single-conversion mode
         */
        ADC12_startConversion(__MSP430_BASEADDRESS_ADC12_PLUS__,
            ADC12_MEMORY_0,
            ADC12_SINGLECHANNEL);

        //Poll for interrupt on memory buffer 0
        while (!ADC12_getInterruptStatus(__MSP430_BASEADDRESS_ADC12_PLUS__,
                   ADC12IFG0)) ;

        //SET BREAKPOINT HERE
        __no_operation();
    }
}

