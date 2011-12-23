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
#ifndef __MSP430WARE_DAC12_H__
#define __MSP430WARE_DAC12_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_DAC12_2__

//*****************************************************************************
//
//The following are values that can be passed to every function in the
//moduleSelect parameter, serving as baseAddress offsets.
//
//*****************************************************************************
#define DAC12_SUBMODULE_0 (0x00)
#define DAC12_SUBMODULE_1 (0x10)

//*****************************************************************************
//
//The following are values that can be passed to DAC12_init() in the
//outputSelect parameter.
//
//*****************************************************************************
#define DAC12_OUTPUT_1 ( !(DAC12OPS) )
#define DAC12_OUTPUT_2 (DAC12OPS)

//*****************************************************************************
//
//The following are values that can be passed to DAC12_init() in the
//positiveReferenceVoltage parameter.
//
//*****************************************************************************
#define DAC12_VREF_INT  (DAC12SREF_0)
#define DAC12_VREF_AVCC (DAC12SREF_1)
#define DAC12_VREF_EXT  (DAC12SREF_2)

//*****************************************************************************
//
//The following are values that can be passed to DAC12_init() in the
//outputVoltageMultiplier parameter.
//
//*****************************************************************************
#define DAC12_VREFx1 (DAC12IR)
#define DAC12_VREFx2 (DAC12OG)
#define DAC12_VREFx3 (0x0)

//*****************************************************************************
//
//The following are values that can be passed to DAC12_init() and
//DAC12_setAmplifierSetting() in the amplifierSetting parameter.
//
//*****************************************************************************
#define DAC12_AMP_OFF_PINOUTHIGHZ (DAC12AMP_0)
#define DAC12_AMP_OFF_PINOUTLOW   (DAC12AMP_1)
#define DAC12_AMP_LOWIN_LOWOUT    (DAC12AMP_2)
#define DAC12_AMP_LOWIN_MEDOUT    (DAC12AMP_3)
#define DAC12_AMP_LOWIN_HIGHOUT   (DAC12AMP_4)
#define DAC12_AMP_MEDIN_MEDOUT    (DAC12AMP_5)
#define DAC12_AMP_MEDIN_HIGHOUT   (DAC12AMP_6)
#define DAC12_AMP_HIGHIN_HIGHOUT  (DAC12AMP_7)

//*****************************************************************************
//
//The following are values that can be passed to DAC12_init() in the
//conversionTriggerSelect parameter.
//
//*****************************************************************************
#define DAC12_TRIGGER_ENCBYPASS (DAC12LSEL_0)
#define DAC12_TRIGGER_ENC       (DAC12LSEL_1)
#define DAC12_TRIGGER_TA        (DAC12LSEL_2)
#define DAC12_TRIGGER_TB        (DAC12LSEL_3)

//*****************************************************************************
//
//The following are values that can be passed to DAC12_setResolution() in the
//resolutionSelect parameter.
//
//*****************************************************************************
#define DAC12_RESOLUTION_12BIT ( !(DAC12RES) )
#define DAC12_RESOLUTION_8BIT  (DAC12RES)

//*****************************************************************************
//
//The following are values that can be passed to DAC12_setInputDataFormat() in
//the inputJustiifcation parameter.
//
//*****************************************************************************
#define DAC12_JUSTIFICATION_RIGHT ( !(DAC12DFJ) )
#define DAC12_JUSTIFICATION_LEFT  (DAC12DFJ)

//*****************************************************************************
//
//The following are values that can be passed to DAC12_setInputDataFormat() in
//the inputDataFormat parameter.
//
//*****************************************************************************
#define DAC12_UNSIGNED_BINARY     ( !(DAC12DF) )
#define DAC12_SIGNED_2SCOMPLEMENT (DAC12DF)

//*****************************************************************************
//
//The following are values that are returned by DAC12_getInterruptStatus().
//
//*****************************************************************************
#define DAC12_INT_INACTIVE (0x0)
#define DAC12_INT_ACTIVE   (0x1)

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************
extern unsigned short DAC12_init (unsigned int baseAddress,
    unsigned char submoduleSelect,
    unsigned short outputSelect,
    unsigned int positiveReferenceVoltage,
    unsigned int outputVoltageMultiplier,
    unsigned char amplifierSetting,
    unsigned int conversionTriggerSelect);

extern void DAC12_setAmplifierSetting (unsigned int baseAddress,
    unsigned char submoduleSelect,
    unsigned char amplifierSetting);

extern void DAC12_disable (unsigned int baseAddress,
    unsigned char submoduleSelect);

extern void DAC12_enableGrouping (unsigned int baseAddress);

extern void DAC12_disableGrouping (unsigned int baseAddress);

extern void DAC12_enableInterrupt (unsigned int baseAddress,
    unsigned char submoduleSelect);

extern void DAC12_disableInterrupt (unsigned int baseAddress,
    unsigned char submoduleSelect);

extern unsigned short DAC12_getInterruptStatus (unsigned int baseAddress,
    unsigned char submoduleSelect);

extern void DAC12_clearInterrupt (unsigned int baseAddress,
    unsigned char submoduleSelect);

extern void DAC12_calibrateOutput (unsigned int baseAddress,
    unsigned char submoduleSelect);

extern int DAC12_getCalibrationData (unsigned int baseAddress,
    unsigned char submoduleSelect);

extern void DAC12_setCalibrationOffset (unsigned int baseAddress,
    unsigned char submoduleSelect,
    int calibrationOffsetValue);

extern void DAC12_enableConversions (unsigned int baseAddress,
    unsigned char submoduleSelect);

extern void DAC12_setData (unsigned int baseAddress,
    unsigned char submoduleSelect,
    unsigned int data);

extern void DAC12_disableConversions (unsigned int baseAddress,
    unsigned char submoduleSelect);

extern void DAC12_setResolution (unsigned int baseAddress,
    unsigned char submoduleSelect,
    unsigned int resolutionSelect);

extern void DAC12_setInputDataFormat (unsigned int baseAddress,
    unsigned char submoduleSelect,
    unsigned char inputJustification,
    unsigned char inputSign);

extern unsigned long DAC12_getDataBufferMemoryAddressForDMA
    (unsigned baseAddress,
    unsigned char submoduleSelect);

#endif
