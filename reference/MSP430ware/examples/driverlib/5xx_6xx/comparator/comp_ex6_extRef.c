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
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//******************************************************************************
//! COMPB - LED Toggle in LPM4, Vcomp_0 is compared against Vcomp_1 voltage
//!
//!  Use CompB and internal reference to determine if input 'Vcompare' is high
//!  of low.  When Vcomp_0 exceeds Vcomp_1 CBOUT goes high and when Vcomp_0 is
//!  less than Vcomp_1 then CBOUT goes low. Connect P1.6/CBOUT to P1.0
//!  externally to see the LED toggle accordingly.
//!
//!                 MSP430x552x
//!             ------------------
//!         /|\|                  |
//!          | |          P6.0/CB0|<- Vcomp_0
//!          --|RST       P6.1/CB1|<- Vcomp_1
//!            |        P1.6/CBOUT|--> 'high'(Vcomp_0>Vcomp_1);
//!            |                  | |  'low'(Vcomp_0<Vcomp_1)
//!            |                  | |
//!            |              P1.0|_| LED 'ON'(Vcomp_0>Vcomp_1);
//!            |                  |       'OFF'(Vcomp_0<Vcomp_1)
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - COMPB peripheral
//! - GPIO Port peripheral
//! - CB0
//! - CB1
//! - CBOUT
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//!
//******************************************************************************

void main (void)
{
    //Stop WDT
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Select CBOUT function on P1.6/CBOUT and set P1.6 output direction
    GPIO_setAsPeripheralModuleFunctionOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN6
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
        COMPB_INPUT1,
        COMPB_POWERMODE_NORMALMODE,
        COMPB_FILTEROUTPUT_DLYLVL1,
        COMPB_NORMALOUTPUTPOLARITY
        );
    //Allow power to Comparator module
    COMPB_enable(__MSP430_BASEADDRESS_COMPB__);

    //delay for the reference to settle
    __delay_cycles(75);

    //Enter LPM4
    __bis_SR_register(LPM4_bits);

    //For debug
    __no_operation();
}

