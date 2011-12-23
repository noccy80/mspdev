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
#include "driverlib/5xx_6xx/wdt.h"
#include "driverlib/5xx_6xx/tlv.h"

//******************************************************************************
//!
//! ADC12 - Sample A10 Internal Temp Sensor as Input, AVcc Ref
//!  
//!  After initialization, the the calibration constants for the 
//!  unit are read in through the TLV. A single sample is made on A10 with 
//!  reference to internal 1.5V Vref. Software sets ADC12SC to start sample and 
//!  conversion - ADC12SC automatically cleared at EOC. ADC12 internal 
//!  oscillator times sample and conversion. In Mainloop MSP430 waits in LPM4 
//!  to save power until ADC10 conversion complete, ADC12_ISR will force exit 
//!  from any LPMx in Mainloop on reti.
//!
//!  ACLK = n/a, MCLK = SMCLK = default DCO ~ 1.045MHz, ADC12CLK = ADC12OSC
//!
//!  Uncalibrated temperature measured from device to device will vary do to
//!  slope and offset variance from device to device - please see datasheet.
//!
//!                MSP430F5438A
//!             -----------------
//!         /|\|                 |
//!          | |                 |
//!          --|RST              |
//!            |Temp Sensor-->A10|
//!            |                 |
//!
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - WDT
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - NONE
//!
//******************************************************************************
void main()
{
  //Stop WDT
  WDT_hold(__MSP430_BASEADDRESS_WDT_A__);
  
  unsigned int status = TLV_getDeviceType();
  while (status != 0x8005);                  // trap

  // Check whether the device has a CPUXV2
  status = TLV_getPeripheral(TLV_PID_MSP430CPUXV2, 0);
  while (status != 0x2300);                 // trap
}
