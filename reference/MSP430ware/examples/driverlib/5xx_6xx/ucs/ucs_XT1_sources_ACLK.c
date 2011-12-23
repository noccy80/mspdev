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
//******************************************************************************
//!  XT1 sources ACLK. Toggles P1.0
//!
//!  This program demonstrates using XT1 to source ACLK
//!  ACLK = LFXT1 = 32,768Hz
//!  An external watch crystal between XIN & XOUT is required for ACLK
//!
//!               MSP430F5438A
//!             -----------------
//!        /|\ |              XIN|-
//!         |  |                 | 32kHz
//!         ---|RST          XOUT|-
//!            |                 |
//!            |            P11.0|--> ACLK = ~32kHz
//!            |                 |
//!            |             P1.0|-->LED
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - UCS module
//! - GPIO Port peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//!
//******************************************************************************

#include "inc/hw_memmap.h"
#include "driverlib/5xx_6xx/ucs.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"
#include "driverlib/5xx_6xx/sfr_sys.h"

//*****************************************************************************
//
//Variable to store status of Oscillator fault flags
//
//*****************************************************************************
unsigned int status;

void main (void)
{
    //Stop watchdog timer
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //Set P11.0 to output direction
    //P11.0 to output ACLK
    //Select XT1
    GPIO_setAsPeripheralModuleFunctionOutputPin(__MSP430_BASEADDRESS_PORT11_R__,
        GPIO_PORT_P11,
        GPIO_PIN0
        );

    //Initializes the XT1 crystal oscillator with no timeout
    //In case of failure, code hangs here.
    //For time-out instead of code hang use UCS_LFXT1StartWithTimeout()
    UCS_LFXT1Start(
        __MSP430_BASEADDRESS_UCS__,
        UCS_XT1_DRIVE0,
        UCS_XCAP_3
        );


    // Enable global oscillator fault flag
    SFR_enableInterrupt(__MSP430_BASEADDRESS_SFR__,
                        SFR_OSCILLATOR_FAULT_INTERRUPT
                        );
    
    // Enable global interrupt
    __bis_SR_register(GIE);   
    
    //Enter LPM3 w/ interrupts
    __bis_SR_register(LPM3_bits + GIE);

    //For debugger
    __no_operation();
}

#pragma vector=UNMI_VECTOR
__interrupt void NMI_ISR(void)
{
  do {
    // If it still can't clear the oscillator fault flags after the timeout, 
    // trap and wait here.
    status = UCS_clearAllOscFlagsWithTimeout(__MSP430_BASEADDRESS_UCS__,
                                             1000
                                             );
  } while(status != 0);
}
