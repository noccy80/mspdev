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
//! Software Toggle P1.0 with ~12MHz DCO
//!
//!   Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//!   ACLK is brought out on pin P11.0, SMCLK on P11.2, and MCLK on P11.1.
//!   PMMCOREV = 1 to support up to 12MHz clock
//!
//!   ACLK = REFO = ~32kHz, MCLK = SMCLK = 12MHz
//!
//!                 MSP430F5438A
//!             -----------------
//!         /|\|                 |
//!          | |            P11.0|-->ACLK
//!          --|RST         P11.1|-->MCLK
//!            |            P11.2|-->SMCLK
//!            |                 |
//!            |             P1.0|-->LED
//!   Note:
//!   In order to run the system at up to 12MHz, VCore must be set at 1.6V
//!   or higher. This is done by invoking function SetVCore()
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
#include "driverlib/5xx_6xx/pmm.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"
#include "driverlib/5xx_6xx/sfr_sys.h"

//*****************************************************************************
//
//Target frequency for MCLK in kHz
//
//*****************************************************************************
#define UCS_MCLK_DESIRED_FREQUENCY_IN_KHZ   12000

//*****************************************************************************
//
//MCLK/FLLRef Ratio
//
//*****************************************************************************
#define UCS_MCLK_FLLREF_RATIO   366

//*****************************************************************************
//
//Variable to store current Clock values
//
//*****************************************************************************
unsigned long clockValue = 0;

//*****************************************************************************
//
//Variable to store status of Oscillator fault flags
//
//*****************************************************************************
unsigned int status;

void main (void)
{
    //Stop WDT
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

    //Set VCore = 1 for 12MHz clock
    PMM_setVCore(__MSP430_BASEADDRESS_PMM__,
        PMM_CORE_LEVEL_1
        );

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(__MSP430_BASEADDRESS_PORT1_R__,
        GPIO_PORT_P1,
        GPIO_PIN0
        );

    //ACLK, MCLK, MCLK set out to pins
    GPIO_setAsPeripheralModuleFunctionOutputPin(__MSP430_BASEADDRESS_PORT11_R__,
        GPIO_PORT_P11,
        GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2
        );

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
    
    // Enable global oscillator fault flag
    SFR_enableInterrupt(__MSP430_BASEADDRESS_SFR__,
                        SFR_OSCILLATOR_FAULT_INTERRUPT
                        );
    
    // Enable global interrupt
    __bis_SR_register(GIE);   

    //Verify if the Clock settings are as expected
    clockValue = UCS_getSMCLK(__MSP430_BASEADDRESS_UCS__);
    clockValue = UCS_getMCLK(__MSP430_BASEADDRESS_UCS__);
    clockValue = UCS_getACLK(__MSP430_BASEADDRESS_UCS__);

    while (1)
    {
        //Toggle P1.0
        GPIO_toggleOutputOnPin(
            __MSP430_BASEADDRESS_PORT1_R__,
            GPIO_PORT_P1,
            GPIO_PIN0
            );

        //Delay
        __delay_cycles(1000000);
    }
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
