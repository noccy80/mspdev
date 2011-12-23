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
//! ADC10 - Sample A0 input, 1.5V Shared Ref, LED ON if A0 > 0.5V
//!
//!  MSP430F550x Demo
//!  A single sample is made on A0 with reference to internal 1.5V Vref.Software
//!  sets ADC10SC to start sample and conversion - ADC10SC automatically cleared
//!  at EOC. ADC10 internal oscillator times sample (16x) and conversion. In
//!  Mainloop MSP430 waits in LPM0 to save power until ADC10 conversion complete,
//!  ADC10_ISR will force exit from LPM0 in Mainloop on reti. If A0 > 0.5V, P1.0
//!  set, else reset.
//!
//!                MSP430F550x
//!             -----------------
//!         /|\|              XIN|-
//!          | |                 |
//!          --|RST          XOUT|-
//!            |          P6.0/A0|<- Sample Signal
//!            |             P1.0|-> LED
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - ADC10 peripheral
//! - REF peripheral
//! - Timer_A peripheral
//! - GPIO Port peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - ADC10_VECTOR
//! - TIMER0_A0_VECTOR
//!
//******************************************************************************

#define TIMER_PERIOD 80

void main (void)
{
    //Stop Watchdog Timer
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

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
     * Use input A0
     * Use positive reference of Internally generated Vref
     * Use negative reference of AVss
     */
    ADC10_memoryConfigure(__MSP430_BASEADDRESS_ADC10_A__,
        ADC10_INPUT_A0,
        ADC10_VREFPOS_INT,
        ADC10_VREFNEG_AVSS);

    //Enable Memory Buffer interrupt
    ADC10_enableInterrupt(__MSP430_BASEADDRESS_ADC10_A__,
        ADC10IE0);

    //Configure internal reference
    //If ref generator busy, WAIT
    while ( REF_BUSY == REF_isRefGenBusy(__MSP430_BASEADDRESS_REF__) ) ;
    //Select internal ref = 1.5V
    REF_setReferenceVoltage(__MSP430_BASEADDRESS_REF__,
        REF_VREF1_5V);
    //Internal Reference ON
    REF_enableReferenceVoltage(__MSP430_BASEADDRESS_REF__);

    //Configure TA0 to provide delay for reference settling ~75us
    //Start timer in Up Mode with Capture compare interrupt enabled
    Timer_startUpMode(__MSP430_BASEADDRESS_T0A5__,
        TIMER_CLOCKSOURCE_SMCLK,
        TIMER_CLOCKSOURCE_DIVIDER_1,
        TIMER_PERIOD,
        TIMER_TAIE_INTERRUPT_DISABLE,
        TIMER_CAPTURECOMPARE_INTERRUPT_ENABLE,
        TIMER_SKIP_CLEAR);

    //LPM0, TA0_ISR will force exit
    __bis_SR_register(CPUOFF + GIE);

    //Disable timer Interrupt
    Timer_disableCaptureCompareInterrupt(__MSP430_BASEADDRESS_T0A5__,
        TIMER_CAPTURECOMPARE_REGISTER_0);

    for (;;)
    {
        //Delay between conversions
        __delay_cycles(5000);

        //Enable and Start the conversion
        //in Single-Channel, Single Conversion Mode
        ADC10_startConversion(__MSP430_BASEADDRESS_ADC10_A__,
            ADC10_SINGLECHANNEL);

        //LPM0, ADC10_ISR will force exit
        __bis_SR_register(CPUOFF + GIE);
        //For debug only
        __no_operation();

        
    }
}

//ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
	switch (__even_in_range(ADC10IV,12)){
        case  0: break; //No interrupt
        case  2: break; //conversion result overflow
        case  4: break; //conversion time overflow
        case  6: break; //ADC10HI
        case  8: break; //ADC10LO
        case 10: break; //ADC10IN
        case 12:        //ADC10IFG0
           
            //Automatically clears ADC10IFG0 by reading memory buffer
			//ADC10MEM = A0 > 0.5V?
        	if (ADC10_getResults(__MSP430_BASEADDRESS_ADC10_A__) < 0x155){
	            //Clear P1.0 LED off
	            GPIO_setOutputLowOnPin(
	                __MSP430_BASEADDRESS_PORT1_R__,
	                GPIO_PORT_P1,
	                GPIO_PIN0
	                );
	        } else   {
	            //Set P1.0 LED on
	            GPIO_setOutputHighOnPin(
	                __MSP430_BASEADDRESS_PORT1_R__,
	                GPIO_PORT_P1,
	                GPIO_PIN0
	                );
	        }
        
            //Clear CPUOFF bit from 0(SR)
            //Breakpoint here and watch ADC_Result
            __bic_SR_register_on_exit(CPUOFF);
            break;
        default: break;
    }
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR (void)
{
    Timer_stop(__MSP430_BASEADDRESS_T0A5__);
    //Exit LPM0 on return
    LPM0_EXIT;
}

