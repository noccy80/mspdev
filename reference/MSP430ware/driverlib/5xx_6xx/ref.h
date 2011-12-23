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
#ifndef __MSP430WARE_REF_H__
#define __MSP430WARE_REF_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_REF__

//*****************************************************************************
//
//The following are values that can be passed to REF_setReferenceVoltage()
//in the referenceVoltageSelect parameter.
//
//*****************************************************************************
#define REF_VREF1_5V (REFVSEL_0)
#define REF_VREF2_0V (REFVSEL_1)
#define REF_VREF2_5V (REFVSEL_2)

//*****************************************************************************
//
//The following are values that can be passed to REF_setReferenceVoltage()
//in the referenceVoltageSelect parameter.
//
//*****************************************************************************
#define REF_NOTBUSY (0x0)
#define REF_BUSY    (0x1)

//*****************************************************************************
//
//The following are values that are returned by REF_isBandgapActive()
//and REF_isRefGenActive().
//
//*****************************************************************************
#define REF_INACTIVE (0x0)
#define REF_ACTIVE   (0x1)

//*****************************************************************************
//
//The following are values that are returned by REF_bandgapMode().
//
//*****************************************************************************
#define REF_STATICMODE (0x0)
#define REF_SAMPLEMODE (0x1)

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************
extern void REF_setReferenceVoltage (unsigned int baseAddress,
    unsigned char referenceVoltageSelect);

extern void REF_disableTempSensor (unsigned int baseAddress);

extern void REF_enableTempSensor (unsigned int baseAddress);

extern void REF_enableReferenceVoltageOutput (unsigned int baseAddress);

extern void REF_disableReferenceVoltageOutput (unsigned int baseAddress);

extern void REF_enableReferenceVoltage (unsigned int baseAddress);

extern void REF_disableReferenceVoltage (unsigned int baseAddress);

extern unsigned short REF_getBandgapMode (unsigned int baseAddress);

extern unsigned short  REF_isBandgapActive (unsigned int baseAddress);

extern unsigned short REF_isRefGenBusy (unsigned int baseAddress);

extern unsigned short REF_isRefGen (unsigned int baseAddress);

#endif
