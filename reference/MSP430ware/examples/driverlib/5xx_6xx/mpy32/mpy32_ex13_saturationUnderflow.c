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
#include "driverlib/5xx_6xx/mpy32.h"
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/gpio.h"

//******************************************************************************
//!
//! MPY - Saturation Mpode Underflow Test
//!
//!  Description: The example illustrates a special case showing underflow.
//!  Underflow occurs when adding 2 negative numbers yields a positive result.
//!  By having the saturation mode enabled, the result if rounded off to the
//!  highest negative number (0x8000.0000 for 16 bit). Results can be viewed
//!  in the debugger window.
//!
//!  ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//!
//!                MSP430F5438A
//!             -----------------
//!         /|\|                 |
//!          | |                 |
//!          --|RST              |
//!            |                 |
//!            |                 |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - MPY peripheral
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - NONE
//!
//******************************************************************************

unsigned long Result;
unsigned int Result_lower16;
unsigned int Result_upper16;

void main (void)
{
    //Stop Watchdog Timer
    WDT_hold(__MSP430_BASEADDRESS_WDT_A__);

//------Pre-Multiply to setup RES0 and RES1 ------------------------

    MPY32_setOperandOne16Bit(__MSP430_BASEADDRESS_MPY32__,
        MPY32_MULTIPLY_UNSIGNED,
        0x8000);
    MPY32_setOperandTwo8Bit(__MSP430_BASEADDRESS_MPY32__,
        0x1);

//------32-bit Result of a multiply operation in RES0 and RES1------
//RES1 == 0x0000
//RES0 == 0x8000

    MPY32CTL0 = MPYC; //Explicity Set MPY Carry Bit.
    //Enable Saturation Mode.
    MPY32_setSaturationMode(__MSP430_BASEADDRESS_MPY32__);

    //Set a 16-bit Operand into the specific Operand 1 register to specify
    //signed multiplication added to the current result
    MPY32_setOperandOne16Bit(__MSP430_BASEADDRESS_MPY32__,
        MPY32_MULTIPLYACCUMULATE_SIGNED,
        0x8000);
    //Set 16-bit Operand 2 to begin the multiplication operation
    MPY32_setOperandTwo16Bit(__MSP430_BASEADDRESS_MPY32__,
        0x0005);

    //Wait for the result to become ready
    __no_operation();
    __no_operation();
    __no_operation();
    __no_operation();
    __no_operation();

    //Read out Result
    Result = MPY32_getResult32Bit(__MSP430_BASEADDRESS_MPY32__);

    //Result_upper16 == 0x8000
    //Result_lower16 == 0x0000

    Result_upper16 = Result;
    Result_lower16 = (Result >> 16);

    //Disable Saturation Mode
    MPY32_resetSaturationMode(__MSP430_BASEADDRESS_MPY32__);

    //Enter LPM4
    __bis_SR_register(LPM4_bits);
    __no_operation();
}

