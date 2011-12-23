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
//! ADC12 - Sample A0-3 Input, AVcc Ref, Non-Repeated Sequence of Conversions
//!
//!  This example shows how to perform A/D conversions on a sequence of
//!  channels. A single sequence of conversions is performed - one conversion
//!  each on channels A0, A1, A2, and A3. Each conversion uses AVcc and AVss for
//!  the references. The conversion results are stored in ADC12MEM0, ADC12MEM1,
//!  ADC12MEM2, and ADC12MEM3 respectively and are moved to 'results[]' upon
//!  completion of the sequence. Test by applying voltages to pins A0, A1, A2,
//!  and A3, then setting and running to a break point at the "_BIC..."
//!  instruction in the ISR. To view the conversion results, open a watch window
//!  in debugger and view 'results' or view ADC12MEM0, ADC12MEM1, ADC12MEM2, and
//!  ADC12MEM3 in an ADC12 SFR window.
//!  This can run even in LPM4 mode as ADC has its own clock
//!  Note that a sequence has no restrictions on which channels are converted.
//!  For example, a valid sequence could be A0, A3, A2, A4, A2, A1, A0, and A7.
//!  See the MSP430x5xx User's Guide for instructions on using the ADC12.
//!
//!                MSP430F552x
//!             -----------------
//!         /|\|                 |
//!          | |          P6.0/A0|<- Vin0
//!          --|RST       P6.1/A1|<- Vin1
//!            |          P6.2/A2|<- Vin2
//!            |          P6.3/A3|<- Vin3
//!            |                 |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - ADC12 peripheral
//! - GPIO Port peripheral
//! - A0
//! - A1
//! - A2
//! - A3
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - ADC12_VECTOR
//!
//******************************************************************************

//Needs to be global in this example
//Otherwise, the compiler removes it
//because it is not used for anything.
volatile unsigned int results[4];

void main (void)
{
    //Stop Watchdog Timer
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Enable A/D channel inputs
    GPIO_setAsPeripheralModuleFunctionInputPin(__MSP430_BASEADDRESS_PORT6_R__,
        GPIO_PORT_P6,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2 +
        GPIO_PIN3 + GPIO_PIN4 + GPIO_PIN5 +
        GPIO_PIN6 + GPIO_PIN7
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
     * For memory buffers 0-7 sample/hold for 16 clock cycles
     * For memory buffers 8-15 sample/hold for 4 clock cycles (default)
     * Enable Multiple Sampling
     */
    ADC12_setupSamplingTimer(__MSP430_BASEADDRESS_ADC12_PLUS__,
        ADC12_CYCLEHOLD_16_CYCLES,
        ADC12_CYCLEHOLD_4_CYCLES,
        ADC12_MULTIPLESAMPLESENABLE);

    //Configure Memory Buffers
    /*
     * Base address of the ADC12 Module
     * Configure memory buffer 0
     * Map input A0 to memory buffer 0
     * Vref+ = AVcc
     * Vref- = AVss
     * Memory buffer 0 is not the end of a sequence
     */
    ADC12_memoryConfigure(__MSP430_BASEADDRESS_ADC12_PLUS__,
        ADC12_MEMORY_0,
        ADC12_INPUT_A0,
        ADC12_VREFPOS_AVCC,
        ADC12_VREFNEG_AVSS,
        ADC12_NOTENDOFSEQUENCE);
    /*
     * Base address of the ADC12 Module
     * Configure memory buffer 1
     * Map input A1 to memory buffer 1
     * Vref+ = AVcc
     * Vref- = AVss
     * Memory buffer 1 is not the end of a sequence
     */
    ADC12_memoryConfigure(__MSP430_BASEADDRESS_ADC12_PLUS__,
        ADC12_MEMORY_1,
        ADC12_INPUT_A1,
        ADC12_VREFPOS_AVCC,
        ADC12_VREFNEG_AVSS,
        ADC12_NOTENDOFSEQUENCE);
    /*
     * Base address of the ADC12 Module
     * Configure memory buffer 2
     * Map input A2 to memory buffer 2
     * Vref+ = AVcc
     * Vref- = AVss
     * Memory buffer 2 is not the end of a sequence
     */
    ADC12_memoryConfigure(__MSP430_BASEADDRESS_ADC12_PLUS__,
        ADC12_MEMORY_2,
        ADC12_INPUT_A2,
        ADC12_VREFPOS_AVCC,
        ADC12_VREFNEG_AVSS,
        ADC12_NOTENDOFSEQUENCE);
    /*
     * Base address of the ADC12 Module
     * Configure memory buffer 3
     * Map input A3 to memory buffer 3
     * Vr+ = AVcc
     * Vr- = AVss
     * Memory buffer 3 IS the end of a sequence
     */
    ADC12_memoryConfigure(__MSP430_BASEADDRESS_ADC12_PLUS__,
        ADC12_MEMORY_3,
        ADC12_INPUT_A3,
        ADC12_VREFPOS_AVCC,
        ADC12_VREFNEG_AVSS,
        ADC12_ENDOFSEQUENCE);

    //Enable memory buffer 3 interrupt
    ADC12_enableInterrupt(__MSP430_BASEADDRESS_ADC12_PLUS__,
        ADC12IE3);

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
         * Use the repeated sequence of channels
         */
        ADC12_startConversion(__MSP430_BASEADDRESS_ADC12_PLUS__,
            ADC12_MEMORY_0,
            ADC12_SEQOFCHANNELS);

        //Enter LPM4, Enable interrupts
        __bis_SR_register(LPM4_bits + GIE);
        //For debugger
        __no_operation();
    }
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
    switch (__even_in_range(ADC12IV,34)){
        case  0: break;   //Vector  0:  No interrupt
        case  2: break;   //Vector  2:  ADC overflow
        case  4: break;   //Vector  4:  ADC timing overflow
        case  6: break;   //Vector  6:  ADC12IFG0
        case  8: break;   //Vector  8:  ADC12IFG1
        case 10: break;   //Vector 10:  ADC12IFG2
        case 12:          //Vector 12:  ADC12IFG3
            //Move results, IFG is cleared
            results[0] =
                ADC12_getResults(__MSP430_BASEADDRESS_ADC12_PLUS__,
                    ADC12_MEMORY_0);
            //Move results, IFG is cleared
            results[1] =
                ADC12_getResults(__MSP430_BASEADDRESS_ADC12_PLUS__,
                    ADC12_MEMORY_1);
            //Move results, IFG is cleared
            results[2] =
                ADC12_getResults(__MSP430_BASEADDRESS_ADC12_PLUS__,
                    ADC12_MEMORY_2);
            //Move results, IFG is cleared
            results[3] =
                ADC12_getResults(__MSP430_BASEADDRESS_ADC12_PLUS__,
                    ADC12_MEMORY_3);

            //Exit active CPU, SET BREAKPOINT HERE
            __bic_SR_register_on_exit(LPM4_bits);
        case 14: break;   //Vector 14:  ADC12IFG4
        case 16: break;   //Vector 16:  ADC12IFG5
        case 18: break;   //Vector 18:  ADC12IFG6
        case 20: break;   //Vector 20:  ADC12IFG7
        case 22: break;   //Vector 22:  ADC12IFG8
        case 24: break;   //Vector 24:  ADC12IFG9
        case 26: break;   //Vector 26:  ADC12IFG10
        case 28: break;   //Vector 28:  ADC12IFG11
        case 30: break;   //Vector 30:  ADC12IFG12
        case 32: break;   //Vector 32:  ADC12IFG13
        case 34: break;   //Vector 34:  ADC12IFG14
        default: break;
    }
}

