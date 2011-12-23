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
#include "driverlib/5xx_6xx/dac12.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//******************************************************************************
//MSP430F66x Demo - DAC12_0 & DAC12_1 grouped, positive ramp on DAC12_0 and
//negative ramp on DAC12_1, high settling speed/current.
//!
//! \addtogroup dac12_examples_list
//! DAC12 - Grouped, Positive Ramp on DAC12_0, Negative Ramp on DAC12_1,
//!       High Settling Speed/Current
//!
//!  Using DAC12_0 grouped with DAC12_1 and AVcc reference with a gain of 1,
//!  output positive ramp on DAC0, negative ramp on DAC1. Data is not latched
//!  from either data buffers until both data buffers have been set.
//!  ACLK = n/a, MCLK = SMCLK = default DCO
//!
//!                MSP430F66x
//!            -----------------
//!        /|\|              XIN|-
//!         | |                 |
//!         --|RST          XOUT|-
//!           |                 |
//!           |        P7.6/DAC0|-> Ramp_positive
//!           |        P7.7/DAC1|-> Ramp_negative
//!           |                 |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - DAC12 peripheral
//! - GPIO Port peripheral
//! - DAC0
//! - DAC1
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//!
//******************************************************************************

void main (void)
{
    unsigned int dataToConvert = 0;

    //Stop Watchdog Timer
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    /*
     * Initialize DAC12_0
     * Multiply Vout by 1
     * Use high settling speed/current,
     * Auto trigger when data is set as,
     * long as conversions are enabled
     */
    DAC12_init(__MSP430_BASEADDRESS_DAC12_2__,
        DAC12_SUBMODULE_0,
        DAC12_OUTPUT_1,
        DAC12_VREF_AVCC,
        DAC12_VREFx1,
        DAC12_AMP_HIGHIN_HIGHOUT,
        DAC12_TRIGGER_ENC
        );

    /*Initialize DAC12_1
     * Choose P6.7 as output
     * Use AVcc as Vref+
     * Multiply Vout by 1
     * Use high settling speed/current
     * Auto trigger when data is set as long as conversions are enabled
     */
    DAC12_init(__MSP430_BASEADDRESS_DAC12_2__,
        DAC12_SUBMODULE_1,
        DAC12_OUTPUT_1,
        DAC12_VREF_AVCC,
        DAC12_VREFx1,
        DAC12_AMP_HIGHIN_HIGHOUT,
        DAC12_TRIGGER_ENC
        );

    //Group both DAC12's to sync output
    DAC12_enableGrouping(__MSP430_BASEADDRESS_DAC12_2__);

    //Calibrate output buffer for DAC12_0
    DAC12_calibrateOutput(__MSP430_BASEADDRESS_DAC12_2__,
        DAC12_SUBMODULE_0);

    //Calibrate output buffer for DAC12_0
    DAC12_calibrateOutput(__MSP430_BASEADDRESS_DAC12_2__,
        DAC12_SUBMODULE_1);

    //Enable Conversions for both DAC12_0 and DAC12_1
    DAC12_enableConversions(__MSP430_BASEADDRESS_DAC12_2__,
        DAC12_SUBMODULE_0);
    DAC12_enableConversions(__MSP430_BASEADDRESS_DAC12_2__,
        DAC12_SUBMODULE_1);

    for (;;)
    {
        dataToConvert++;

        //Set data for DAC12_0, which will not latch because it is grouped
        DAC12_setData(__MSP430_BASEADDRESS_DAC12_2__,
            DAC12_SUBMODULE_0,
            dataToConvert);

        //Set data for DAC12_1, which will latch both DAC's data buffers
        DAC12_setData(__MSP430_BASEADDRESS_DAC12_2__,
            DAC12_SUBMODULE_1,
            ~(dataToConvert));
        __no_operation();
    }
}

