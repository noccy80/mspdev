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
#ifndef __MSP430WARE_ADC12_H__
#define __MSP430WARE_ADC12_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_ADC12_PLUS__

//*****************************************************************************
//
//The following are values that can be passed to ADC12_init() in the
//sampleTimerSourceSelect parameter.
//
//*****************************************************************************
#define ADC12_SAMPLEHOLDSOURCE_SC (ADC12SHS_0)
#define ADC12_SAMPLEHOLDSOURCE_1  (ADC12SHS_1)
#define ADC12_SAMPLEHOLDSOURCE_2  (ADC12SHS_2)
#define ADC12_SAMPLEHOLDSOURCE_3  (ADC12SHS_3)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_init() in the
//clockSourceSelect parameter.
//
//*****************************************************************************
#define ADC12_CLOCKSOURCE_ADC12OSC (ADC12SSEL_0)
#define ADC12_CLOCKSOURCE_ACLK     (ADC12SSEL_1)
#define ADC12_CLOCKSOURCE_MCLK     (ADC12SSEL_2)
#define ADC12_CLOCKSOURCE_SMCLK    (ADC12SSEL_3)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_init() in the
//clockSourceDivider parameter.
//Note: Bit 1 determines if the pre-divider is 1 (0x00) or 4 (0x01)
//Bits 5-7 determine the the post-divider 1-8 (0x00 - 0xE0)
//
//*****************************************************************************
#define ADC12_CLOCKDIVIDER_1  (ADC12DIV_0)
#define ADC12_CLOCKDIVIDER_2  (ADC12DIV_1)
#define ADC12_CLOCKDIVIDER_3  (ADC12DIV_2)
#define ADC12_CLOCKDIVIDER_4  (ADC12DIV_3)
#define ADC12_CLOCKDIVIDER_5  (ADC12DIV_4)
#define ADC12_CLOCKDIVIDER_6  (ADC12DIV_5)
#define ADC12_CLOCKDIVIDER_7  (ADC12DIV_6)
#define ADC12_CLOCKDIVIDER_8  (ADC12DIV_7)
#define ADC12_CLOCKDIVIDER_12 (ADC12DIV_2 + ADC12PDIV)
#define ADC12_CLOCKDIVIDER_16 (ADC12DIV_3 + ADC12PDIV)
#define ADC12_CLOCKDIVIDER_20 (ADC12DIV_4 + ADC12PDIV)
#define ADC12_CLOCKDIVIDER_24 (ADC12DIV_5 + ADC12PDIV)
#define ADC12_CLOCKDIVIDER_28 (ADC12DIV_6 + ADC12PDIV)
#define ADC12_CLOCKDIVIDER_32 (ADC12DIV_7 + ADC12PDIV)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_setResolution() in the
//resolutionSelect parameter.
//
//*****************************************************************************
#define ADC12_RESOLUTION_8BIT  (ADC12RES_0)
#define ADC12_RESOLUTION_10BIT (ADC12RES_1)
#define ADC12_RESOLUTION_12BIT (ADC12RES_2)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_setupSamplingTimer() in
//the clockCycleHoldCountLowMem and clockCycleHoldCountHighMem parameters.
//
//*****************************************************************************
#define ADC12_CYCLEHOLD_4_CYCLES    (ADC12SHT0_0)
#define ADC12_CYCLEHOLD_8_CYCLES    (ADC12SHT0_1)
#define ADC12_CYCLEHOLD_16_CYCLES   (ADC12SHT0_2)
#define ADC12_CYCLEHOLD_32_CYCLES   (ADC12SHT0_3)
#define ADC12_CYCLEHOLD_64_CYCLES   (ADC12SHT0_4)
#define ADC12_CYCLEHOLD_96_CYCLES   (ADC12SHT0_5)
#define ADC12_CYCLEHOLD_128_CYCLES  (ADC12SHT0_6)
#define ADC12_CYCLEHOLD_192_CYCLES  (ADC12SHT0_7)
#define ADC12_CYCLEHOLD_256_CYCLES  (ADC12SHT0_8)
#define ADC12_CYCLEHOLD_384_CYCLES  (ADC12SHT0_9)
#define ADC12_CYCLEHOLD_512_CYCLES  (ADC12SHT0_10)
#define ADC12_CYCLEHOLD_768_CYCLES  (ADC12SHT0_11)
#define ADC12_CYCLEHOLD_1024_CYCLES (ADC12SHT0_12)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_setupSamplingTimer() in
//the multipleSamplesEnabled parameter.
//
//*****************************************************************************
#define ADC12_MULTIPLESAMPLESDISABLE ( !(ADC12MSC) )
#define ADC12_MULTIPLESAMPLESENABLE  (ADC12MSC)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_memoryConfigure(),
//ADC12_startConversion(), and ADC12_readResults() in the memoryIndex and
//startingMemoryIndex parameters.
//
//*****************************************************************************
#define ADC12_MEMORY_0  (0x0)
#define ADC12_MEMORY_1  (0x1)
#define ADC12_MEMORY_2  (0x2)
#define ADC12_MEMORY_3  (0x3)
#define ADC12_MEMORY_4  (0x4)
#define ADC12_MEMORY_5  (0x5)
#define ADC12_MEMORY_6  (0x6)
#define ADC12_MEMORY_7  (0x7)
#define ADC12_MEMORY_8  (0x8)
#define ADC12_MEMORY_9  (0x9)
#define ADC12_MEMORY_10 (0xA)
#define ADC12_MEMORY_11 (0xB)
#define ADC12_MEMORY_12 (0xC)
#define ADC12_MEMORY_13 (0xD)
#define ADC12_MEMORY_14 (0xE)
#define ADC12_MEMORY_15 (0xF)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_memoryConfigure() in the
//inputSourceSelect parameter.
//
//*****************************************************************************
#define ADC12_INPUT_A0              (ADC12INCH_0)
#define ADC12_INPUT_A1              (ADC12INCH_1)
#define ADC12_INPUT_A2              (ADC12INCH_2)
#define ADC12_INPUT_A3              (ADC12INCH_3)
#define ADC12_INPUT_A4              (ADC12INCH_4)
#define ADC12_INPUT_A5              (ADC12INCH_5)
#define ADC12_INPUT_A6              (ADC12INCH_6)
#define ADC12_INPUT_A7              (ADC12INCH_7)
#define ADC12_INPUT_A8              (ADC12INCH_8)
#define ADC12_INPUT_A9              (ADC12INCH_9)
#define ADC12_INPUT_TEMPSENSOR      (ADC12INCH_10)
#define ADC12_INPUT_BATTERYMONITOR  (ADC12INCH_11)
#define ADC12_INPUT_A12             (ADC12INCH_12)
#define ADC12_INPUT_A13             (ADC12INCH_13)
#define ADC12_INPUT_A14             (ADC12INCH_14)
#define ADC12_INPUT_A15             (ADC12INCH_15)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_memoryConfigure() in the
//positiveRefVoltageSourceSelect parameter.
//
//*****************************************************************************
#define ADC12_VREFPOS_AVCC ( !(ADC12SREF0 + ADC12SREF1) )
#define ADC12_VREFPOS_INT  (ADC12SREF0)
#define ADC12_VREFPOS_EXT  (ADC12SREF1)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_memoryConfigure() in the
//negativeRefVoltageSourceSelect parameter.
//
//*****************************************************************************
#define ADC12_VREFNEG_AVSS ( !(ADC12SREF2) )
#define ADC12_VREFNEG_EXT  (ADC12SREF2)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_memoryConfigure() in the
//endOfSequence parameter.
//
//*****************************************************************************
#define ADC12_NOTENDOFSEQUENCE ( !(ADC12EOS) )
#define ADC12_ENDOFSEQUENCE    (ADC12EOS)

//*****************************************************************************
//
//The following are mask values that can be passed to ADC12_enableInterrupt()
//or ADC12_disableInterrupt in the interruptMask parameter.
//
//*****************************************************************************
#define ADC12OVIE0  ADC12OVIE
#define ADC12TOVIE0 ADC12TOVIE

//*****************************************************************************
//
//The following are values that can be passed to ADC12_startConversion() in the
//conversionSequenceModeSelect parameter.
//
//*****************************************************************************
#define ADC12_SINGLECHANNEL          (ADC12CONSEQ_0)
#define ADC12_SEQOFCHANNELS          (ADC12CONSEQ_1)
#define ADC12_REPEATED_SINGLECHANNEL (ADC12CONSEQ_2)
#define ADC12_REPEATED_SEQOFCHANNELS (ADC12CONSEQ_3)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_disableConversions() in
//the preempt parameter.
//
//*****************************************************************************
#define ADC12_COMPLETECONVERSION (0x0)
#define ADC12_PREEMPTCONVERSION  (0x1)

//*****************************************************************************
//
//The following are values that can be passed to
//ADC12_setSampleHoldSignalInversion() in the invertedSignal parameter.
//
//*****************************************************************************
#define ADC12_NONINVERTEDSIGNAL ( !(ADC12ISSH) )
#define ADC12_INVERTEDSIGNAL    (ADC12ISSH)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_setDataReadBackFormat()
//in the readBackFormat parameter.
//
//*****************************************************************************
#define ADC12_UNSIGNED_BINARY     ( !(ADC12DF) )
#define ADC12_SIGNED_2SCOMPLEMENT (ADC12DF)

//*****************************************************************************
//
//The following are values that can be passed to
//ADC12_setReferenceBufferSamplingRate() in the samplingRateSelect parameter.
//
//*****************************************************************************
#define ADC12_MAXSAMPLINGRATE_200KSPS ( !(ADC12SR) )
#define ADC12_MAXSAMPLINGRATE_50KSPS  (ADC12SR)

//*****************************************************************************
//
//The following are values that are returned by ADC12_isBusy().
//
//*****************************************************************************
#define ADC12_NOTBUSY (0x0)
#define ADC12_BUSY    (0x1)

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************

extern unsigned short ADC12_init (unsigned int baseAddress,
    unsigned int sampleHoldSourceSelect,
    unsigned char clockSourceSelect,
    unsigned int clockSourceDivider);

void ADC12_enable (unsigned int baseAddress);

void ADC12_disable (unsigned int baseAddress);

extern void ADC12_setupSamplingTimer (unsigned int baseAddress,
    unsigned int clockCycleHoldCountLowMem,
    unsigned int clockCycleHoldCountHighMem,
    unsigned short multipleSamplesEnabled);

extern void ADC12_disableSamplingTimer (unsigned int baseAddress);

extern void ADC12_memoryConfigure (unsigned int baseAddress,
    unsigned char memoryBufferControlIndex,
    unsigned char inputSourceSelect,
    unsigned char positiveRefVoltageSourceSelect,
    unsigned char negativeRefVoltageSourceSelect,
    unsigned short endOfSequence);

extern void ADC12_enableInterrupt (unsigned int baseAddress,
    unsigned long interruptMask);

extern void ADC12_disableInterrupt (unsigned int baseAddress,
    unsigned long interruptMask);

extern void ADC12_clearInterrupt (unsigned int baseAddress,
    unsigned int memoryBufferInterruptFlagMask);

extern unsigned char ADC12_getInterruptStatus (unsigned int baseAddress,
    unsigned int memoryBufferInterruptFlagMask);

extern void ADC12_startConversion (unsigned int baseAddress,
    unsigned int startingMemoryBufferIndex,
    unsigned char conversionSequenceModeSelect);

void ADC12_disableConversions (unsigned int baseAddress,
    unsigned short preempt);

int ADC12_getResults (unsigned int baseAddress,
    unsigned char memoryBufferIndex);

void ADC12_setResolution (unsigned int baseAddress,
    unsigned char resolutionSelect);

extern void ADC12_setSampleHoldSignalInversion (unsigned int baseAddress,
    unsigned int invertedSignal);

extern void ADC12_setDataReadBackFormat (unsigned int baseAddress,
    unsigned short readBackFormat);

extern void ADC12_enableReferenceBurst (unsigned int baseAddress);

extern void ADC12_disableReferenceBurst (unsigned int baseAddress);

extern void ADC12_setReferenceBufferSamplingRate (unsigned int baseAddress,
    unsigned short samplingRateSelect);

extern unsigned long ADC12_getMemoryAddressForDMA (unsigned int baseAddress,
    unsigned char memoryIndex);

extern unsigned short ADC12_isBusy (unsigned int baseAddress);

#endif
