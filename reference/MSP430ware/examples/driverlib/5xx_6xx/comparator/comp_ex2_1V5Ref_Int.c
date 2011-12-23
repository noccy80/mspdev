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
//! COMPB - CB Interrupt, Input compared against 1.5V Internal Reference
//!
//!  Use CompB and internal reference to determine if input 'Vcompare' is high
//!  of low.  For the first time, when Vcompare exceeds the 1.5V internal
//!  reference, CBIFG is set and device enters the CompB ISR. In the ISR CBIES
//!  is toggled such that when Vcompare is less than 1.5V internal reference,
//!  CBIFG is set. LED is toggled inside the CompB ISR
//!
//!                 MSP430x552x
//!             ------------------
//!         /|\|                  |
//!          | |                  |
//!          --|RST       P6.0/CB0|<- Vcompare
//!            |              P1.0|-> LED 'ON'(Vcompare>1.5V); 'OFF'(Vcompare<1.5V)
//!            |                  |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - COMPB peripheral
//! - GPIO Port peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - COMPB_B_VECTOR
//!
//******************************************************************************

void main (void)
{
    //Stop WDT
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //Initialize the Comparator B module
    /*
     * Base Address of Comparator B,
     * Pin CB0 to Positive(+) Terminal
     * Reference Voltage to Negative(-) Terminal
     * Normal Power Mode
     * Output Filter On with minimal delay
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
     * Reference Voltage of 1.5 V,
     * Upper Limit of 1.5*(32/32) = 1.5V,
     * Lower Limit of 1.5*(32/32) = 1.5V
     */
    COMPB_setReferenceVoltage(__MSP430_BASEADDRESS_COMPB__,
        COMPB_VREFBASE1_5V,
        32,
        32
        );
    //Enable Interrupts
    /*
     * Base Address of Comparator B,
     * Enable CompB Interrupt on default rising edge for CBIFG
     */

    COMPB_enableInterrupt(__MSP430_BASEADDRESS_COMPB__,
        CBIE
        );

    //Allow power to Comparator module
    COMPB_enable(__MSP430_BASEADDRESS_COMPB__);

    //Enter LPM4 with inetrrupts enabled
    __bis_SR_register(LPM4_bits + GIE);

    //For debug
    __no_operation();
}

//******************************************************************************
//
//This is the COMP_B_VECTOR interrupt vector service routine.
//
//******************************************************************************
#pragma vector=COMP_B_VECTOR
__interrupt void COMPB_B_ISR (void)
{
    //Toggle the edge at which an interrupt is generated
    COMPB_interruptToggleEdgeDirection(__MSP430_BASEADDRESS_COMPB__);

    //Clear Interrupt flag
    COMPB_clearInterrupt(__MSP430_BASEADDRESS_COMPB__, CBIFG);

    //Toggle P1.0
    GPIO_toggleOutputOnPin(
        __MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );
}

