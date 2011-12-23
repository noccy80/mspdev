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
//*****************************************************************************
//
//adc12.c - Driver for the ADC12 Module.
//
//*****************************************************************************
#include "driverlib/5xx_6xx/adc12.h"
#include "inc/hw_types.h"
#include "msp430xgeneric.h"
#include "driverlib/5xx_6xx/debug.h"

//*****************************************************************************
//
//! Initializes the ADC12 Module.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param sampleHoldSignalSourceSelect is the signal that will trigger a
//!       sample-and-hold for an input signal to be converted.
//!        Valid values are
//!        \b ADC12_SAMPLEHOLDSOURCE_SC [Default]
//!        \b ADC12_SAMPLEHOLDSOURCE_1
//!        \b ADC12_SAMPLEHOLDSOURCE_2
//!        \b ADC12_SAMPLEHOLDSOURCE_3
//!        This parameter is device specific and sources should be found in the
//!        device's datasheet.
//!        Modified bits are \b ADC12SHSx of \b ADC12CTL1 register.
//! \param clockSourceSelect selects the clock that will be used by the ADC12
//!       core, and the sampling timer if a sampling pulse mode is enabled.
//!        Valid values are
//!        \b ADC12_CLOCKSOURCE_ADC12OSC - MODOSC 5 MHz oscillator from the UCS
//!            [Default]
//!        \b ADC12_CLOCKSOURCE_ACLK     - The Auxilary Clock
//!        \b ADC12_CLOCKSOURCE_MCLK     - The Master Clock
//!        \b ADC12_CLOCKSOURCE_SMCLK    - The Sub-Master Clock
//!        Modified bits are \b ADC12SSELx of \b ADC12CTL1 register.
//! \param clockSourceDivider selects the amount that the clock will be divided.
//!        Valid values are
//!        \b ADC12_CLOCKDIVIDER_1 [Default]
//!        \b ADC12_CLOCKDIVIDER_2
//!        \b ADC12_CLOCKDIVIDER_3
//!        \b ADC12_CLOCKDIVIDER_4
//!        \b ADC12_CLOCKDIVIDER_5
//!        \b ADC12_CLOCKDIVIDER_6
//!        \b ADC12_CLOCKDIVIDER_7
//!        \b ADC12_CLOCKDIVIDER_8
//!        \b ADC12_CLOCKDIVIDER_12
//!        \b ADC12_CLOCKDIVIDER_16
//!        \b ADC12_CLOCKDIVIDER_20
//!        \b ADC12_CLOCKDIVIDER_24
//!        \b ADC12_CLOCKDIVIDER_28
//!        \b ADC12_CLOCKDIVIDER_32
//!        Modified bits are \b ADC12DIVx of \b ADC12CTL1 register and
//!         \b ADC12PDIV of \b ADC12CTL2 register.
//!
//! This function initializes the ADC module to allow for analog-to-digital
//! conversions. Specifically this function sets up the sample-and-hold signal
//! and clock sources for the ADC core to use for conversions. Upon successful
//! completion of the initialization all of the ADC control registers will be
//! reset, excluding the memory controls and reference module bits, the given
//! parameters will be set, and the ADC core will be turned on (Note, that the
//! ADC core only draws power during conversions and remains off when not
//! converting).Note that sample/hold signal sources are device dependent. Note
//! that if re-initializing the ADC after starting a conversion with the
//! startConversion() function, the disableConversion() must be called BEFORE
//! this function can be called.
//!
//! \return STATUS_SUCCESS or STATUS_FAILURE of the initialization process.
//
//*****************************************************************************
unsigned short ADC12_init (unsigned int baseAddress,
    unsigned int sampleHoldSignalSourceSelect,
    unsigned char clockSourceSelect,
    unsigned int clockSourceDivider)
{
    //Make sure the ENC bit is cleared before initializing the ADC12
    ASSERT( !(HWREGB(baseAddress + OFS_ADC12CTL0_L) & ADC12ENC) );

    ASSERT(sampleHoldSignalSourceSelect <= ADC12_SAMPLEHOLDSOURCE_3);
    ASSERT(clockSourceSelect <= ADC12_CLOCKSOURCE_SMCLK);
    ASSERT(clockSourceDivider <= ADC12_CLOCKDIVIDER_32);

    unsigned char retVal = STATUS_SUCCESS;

    //Turn OFF ADC10 Module & Clear Interrupt Registers
    HWREG(baseAddress + OFS_ADC12CTL0) &= ~(ADC12ON + ADC12OVIE + ADC12TOVIE
                                            + ADC12ENC + ADC12SC);
    HWREG(baseAddress + OFS_ADC12IE)   &= 0x0000; //Reset ALL interrupt enables
    HWREG(baseAddress + OFS_ADC12IFG)  &= 0x0000; //Reset ALL interrupt flags

    //Set ADC12 Control 1
    HWREG(baseAddress + OFS_ADC12CTL1) =
        sampleHoldSignalSourceSelect //Setup the Sample-and-Hold Source
        + (clockSourceDivider & ADC12DIV_7) //Set Clock Divider
        + clockSourceSelect; //Setup Clock Source

    //Set ADC12 Control 2
    HWREG(baseAddress + OFS_ADC12CTL2) =
        (clockSourceDivider & ADC12PDIV) //Set Clock Pre-Divider
        + ADC12RES_2; //Default resolution to 12-bits

    return ( retVal) ;
}

//*****************************************************************************
//
//! Enables the ADC12 block.
//!
//! \param baseAddress is the base address of the ADC12 module.
//!
//! This will enable operation of the ADC12 block.
//! Modified bits are \b ADC12ON of \b ADC12CTL0 register.
//!
//! \return None.
//
//*****************************************************************************
void ADC12_enable (unsigned int baseAddress)
{
    //Enable the ADC12 Module
    HWREGB(baseAddress + OFS_ADC12CTL0_L) |= ADC12ON;
}

//*****************************************************************************
//
//! Disables the ADC12 block.
//!
//! \param baseAddress is the base address of the ADC12 module.
//!
//! This will disable operation of the ADC12 block.
//! Modified bits are \b ADC12ON of \b ADC12CTL0 register.
//!
//! \return None.
//
//*****************************************************************************
void ADC12_disable (unsigned int baseAddress)
{
    //Disable ADC12 module
    HWREGB(baseAddress + OFS_ADC12CTL0_L) &= ~ADC12ON;
}


//*****************************************************************************
//
//! Sets up and enables the Sampling Timer Pulse Mode.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param clockCycleHoldCountLowMem sets the amount of clock cycles to
//!       sample-and-hold for the higher memory buffers 0-7.
//!        Valid values are
//!        \b ADC12_CYCLEHOLD_4_CYCLES [Default]
//!        \b ADC12_CYCLEHOLD_8_CYCLES
//!        \b ADC12_CYCLEHOLD_16_CYCLES
//!        \b ADC12_CYCLEHOLD_32_CYCLES
//!        \b ADC12_CYCLEHOLD_64_CYCLES
//!        \b ADC12_CYCLEHOLD_96_CYCLES
//!        \b ADC12_CYCLEHOLD_128_CYCLES
//!        \b ADC12_CYCLEHOLD_192_CYCLES
//!        \b ADC12_CYCLEHOLD_256_CYCLES
//!        \b ADC12_CYCLEHOLD_384_CYCLES
//!        \b ADC12_CYCLEHOLD_512_CYCLES
//!        \b ADC12_CYCLEHOLD_768_CYCLES
//!        \b ADC12_CYCLEHOLD_1024_CYCLES
//!        Modified bits are \b ADC12SHT0x of \b ADC12CTL0 register.
//! \param clockCycleHoldCountHighMem sets the amount of clock cycles to
//!       sample-and-hold for the higher memory buffers 8-15.
//!        Valid values are
//!        \b ADC12_CYCLEHOLD_4_CYCLES [Default]
//!        \b ADC12_CYCLEHOLD_8_CYCLES
//!        \b ADC12_CYCLEHOLD_16_CYCLES
//!        \b ADC12_CYCLEHOLD_32_CYCLES
//!        \b ADC12_CYCLEHOLD_64_CYCLES
//!        \b ADC12_CYCLEHOLD_96_CYCLES
//!        \b ADC12_CYCLEHOLD_128_CYCLES
//!        \b ADC12_CYCLEHOLD_192_CYCLES
//!        \b ADC12_CYCLEHOLD_256_CYCLES
//!        \b ADC12_CYCLEHOLD_384_CYCLES
//!        \b ADC12_CYCLEHOLD_512_CYCLES
//!        \b ADC12_CYCLEHOLD_768_CYCLES
//!        \b ADC12_CYCLEHOLD_1024_CYCLES
//!        Modified bits are \b ADC12SHT1x of \b ADC12CTL0 register.
//! \param multipleSamplesEnabled allows multiple conversions to start
//!       without a trigger signal from the sample/hold signal
//!        Valid values are
//!        \b ADC12_MULTIPLESAMPLESDISABLE - a timer trigger will be needed to
//!                  start every ADC conversion. [Default]
//!        \b ADC12_MULTIPLESAMPLESENABLE  - during a sequenced and/or repeated
//!                  conversion mode, after the first conversion, no sample/hold
//!                  signal is necessary to start subsequent sample/hold and
//!                  convert processes.
//!        Modified bits are \b ADC12MSC of \b ADC12CTL0 register.
//!
//! This function sets up the sampling timer pulse mode which allows the
//! sample/hold signal to trigger a sampling timer to sample-and-hold an input
//! signal for a specified number of clock cycles without having to hold the
//! sample/hold signal for the entire period of sampling. Note that if a
//! conversion has been started with the startConversion() function, then a call
//! to disableConversions() is required before this function may be called.
//!
//! \return NONE
//
//*****************************************************************************
void ADC12_setupSamplingTimer (unsigned int baseAddress,
    unsigned int clockCycleHoldCountLowMem,
    unsigned int clockCycleHoldCountHighMem,
    unsigned short multipleSamplesEnabled)
{
    //Make sure the ENC bit is cleared before setting up sampling pulse mode
    ASSERT( !(HWREGB(baseAddress + OFS_ADC12CTL0_L) & ADC12ENC) );

    ASSERT(clockCycleHoldCountLowMem <= ADC12_CYCLEHOLD_1024_CYCLES);
    ASSERT(clockCycleHoldCountHighMem <= ADC12_CYCLEHOLD_1024_CYCLES);

    HWREG(baseAddress + OFS_ADC12CTL1) |= ADC12SHP;

    //Reset clock cycle hold counts and msc bit before setting them
    HWREG(baseAddress + OFS_ADC12CTL0) &=
        ~(ADC12SHT0_15 + ADC12SHT1_15 + ADC12MSC);

    //Set clock cycle hold counts and msc bit
    HWREG(baseAddress + OFS_ADC12CTL0) |= clockCycleHoldCountLowMem
                                          + (clockCycleHoldCountHighMem << 4)
                                          + multipleSamplesEnabled;
}

//*****************************************************************************
//
//! Disables Sampling Timer Pulse Mode.
//!
//! \param baseAddress is the base address of the ADC12 module.
//!
//! Disables the Sampling Timer Pulse Mode. Note that if a conversion has been
//! started with the startConversion() function, then a call to
//! disableConversions() is required before this function may be called.
//!
//! Modified bits are \b ADC12SHP of \b ADC12CTL0 register.
//! \return NONE
//
//*****************************************************************************
void ADC12_disableSamplingTimer (unsigned int baseAddress)
{
    //Make sure the ENC bit is cleared before disabling sampling pulse mode
    ASSERT( !(HWREGB(baseAddress + OFS_ADC12CTL0_L) & ADC12ENC) );

    HWREG(baseAddress + OFS_ADC12CTL1) &= ~(ADC12SHP);
}

//*****************************************************************************
//
//! Configures the controls of the selected memory buffer.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param memoryBufferControlIndex is the selected memory buffer to set the
//!       configuration for.
//!        Valid values are
//!        \b ADC12_MEMORY_0 [Default]
//!        \b ADC12_MEMORY_1
//!        \b ADC12_MEMORY_2
//!        \b ADC12_MEMORY_3
//!        \b ADC12_MEMORY_4
//!        \b ADC12_MEMORY_5
//!        \b ADC12_MEMORY_6
//!        \b ADC12_MEMORY_7
//!        \b ADC12_MEMORY_8
//!        \b ADC12_MEMORY_9
//!        \b ADC12_MEMORY_10
//!        \b ADC12_MEMORY_11
//!        \b ADC12_MEMORY_12
//!        \b ADC12_MEMORY_13
//!        \b ADC12_MEMORY_14
//!        \b ADC12_MEMORY_15
//! \param inputSourceSelect is the input that will store the converted data
//!       into the specified memory buffer.
//!        Valid values are
//!        \b ADC12_INPUT_A0 [Default]
//!        \b ADC12_INPUT_A1
//!        \b ADC12_INPUT_A2
//!        \b ADC12_INPUT_A3
//!        \b ADC12_INPUT_A4
//!        \b ADC12_INPUT_A5
//!        \b ADC12_INPUT_A6
//!        \b ADC12_INPUT_A7
//!        \b ADC12_INPUT_A8
//!        \b ADC12_INPUT_A9
//!        \b ADC12_INPUT_TEMPSENSOR
//!        \b ADC12_INPUT_BATTERYMONITOR
//!        \b ADC12_INPUT_A12
//!        \b ADC12_INPUT_A13
//!        \b ADC12_INPUT_A14
//!        \b ADC12_INPUT_A15
//!        Modified bits are \b ADC12INCHx of \b ADC12MCTLx register.
//! \param positiveRefVoltageSourceSelect is the reference voltage source to set
//!       as the upper limit for the conversion stored in the specified memory.
//!        Valid values are
//!        \b ADC12_VREFPOS_AVCC [Default]
//!        \b ADC12_VREFPOS_EXT
//!        \b ADC12_VREFPOS_INT
//!        Modified bits are \b ADC12SREF of \b ADC12MCTLx register.
//! \param negativeRefVoltageSourceSelect is the reference voltage source to set
//!       as the lower limit for the conversion stored in the specified memory.
//!        Valid values are
//!        \b ADC12_VREFNEG_AVSS [Default]
//!        \b ADC12_VREFNEG_EXT
//!        Modified bits are \b ADC12SREF of \b ADC12MCTLx register.
//! \param endOfSequence indicates that the specified memory buffer will be
//!       the end of the sequence if a sequenced conversion mode is selected
//!        Valid values are
//!        \b ADC12_NOTENDOFSEQUENCE - The specified memory buffer will NOT be the
//!                  end of the sequence OR a sequenced conversion mode is not
//!                  selected. [Default]
//!        \b ADC12_ENDOFSEQUENCE  - The specified memory buffer will be the end
//!                  of the sequence.
//!        Modified bits are \b ADC12EOS of \b ADC12MCTLx register.
//!
//! Maps an input signal conversion into the selected memory buffer, as
//! well as the positive and negative reference voltages for each conversion
//! being stored into this memory buffer. If the internal reference is used for
//! the positive reference voltage, the internal REF module must be used to
//! control the voltage level. Note that if a conversion has been started with
//! the startConversion() function, then a call to disableConversions() is
//! required before this function may be called.
//!
//! \return NONE
//
//*****************************************************************************
void ADC12_memoryConfigure (unsigned int baseAddress,
    unsigned char memoryBufferControlIndex,
    unsigned char inputSourceSelect,
    unsigned char positiveRefVoltageSourceSelect,
    unsigned char negativeRefVoltageSourceSelect,
    unsigned short endOfSequence)
{
    //Make sure the ENC bit is cleared before configuring a Memory Buffer Control
    ASSERT( !(HWREGB(baseAddress + OFS_ADC12CTL0_L) & ADC12ENC) );

    ASSERT(memoryBufferControlIndex <= ADC12_MEMORY_15);
    ASSERT(inputSourceSelect <= ADC12_INPUT_A15);
    ASSERT(positiveRefVoltageSourceSelect <= ADC12_VREFPOS_INT);
    ASSERT(negativeRefVoltageSourceSelect <= ADC12_VREFNEG_EXT);

    //Set the offset in respect to ADC12MCTL0
    unsigned int memoryBufferControlOffset =
        (OFS_ADC12MCTL0 + memoryBufferControlIndex);

    //Reset the memory buffer control and Set the input source
    HWREGB(baseAddress + memoryBufferControlOffset) =
        inputSourceSelect //Set Input Source
        + positiveRefVoltageSourceSelect //Set Vref+
        + negativeRefVoltageSourceSelect //Set Vref-
        + endOfSequence; //Set End of Sequence
}

//*****************************************************************************
//
//! Enables selected ADC12 interrupt sources.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param memoryInterruptMask is the bit mask of the memory buffer and overflow
//!       interrupt sources to be enabled.
//!        Mask values is the logical OR of any of the following
//!        \b ADC12IE0 - new conversion data in the 0th memory buffer
//!        \b ADC12IE1 - new conversion data in the 1st memory buffer
//!        \b ADC12IE2 - new conversion data in the 2nd memory buffer
//!        \b ADC12IE3 - new conversion data in the 3rd memory buffer
//!        \b ADC12IE4 - new conversion data in the 4th memory buffer
//!        \b ADC12IE5 - new conversion data in the 5th memory buffer
//!        \b ADC12IE6 - new conversion data in the 6th memory buffer
//!        \b ADC12IE7 - new conversion data in the 7th memory buffer
//!        \b ADC12IE8 - new conversion data in the 8th memory buffer
//!        \b ADC12IE9 - new conversion data in the 9th memory buffer
//!        \b ADC12IE10 - new conversion data in the 10th memory buffer
//!        \b ADC12IE11 - new conversion data in the 11th memory buffer
//!        \b ADC12IE12 - new conversion data in the 12th memory buffer
//!        \b ADC12IE13 - new conversion data in the 13th memory buffer
//!        \b ADC12IE14 - new conversion data in the 14th memory buffer
//!        \b ADC12IE15 - new conversion data in the 15th memory buffer
//!        \b ADC12OVIE0 - a conversion is about to save to a memory buffer that
//!                  has not been read out yet.
//!        \b ADC12TOVIE0 - a conversion is about to start before the previous
//!                  conversion has been completed.
//!
//! Enables the indicated ADC12 interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! \return NONE
//
//*****************************************************************************
void ADC12_enableInterrupt (unsigned int baseAddress,
    unsigned long interruptMask)
{
    HWREG(baseAddress + OFS_ADC12IFG) &= ~interruptMask;
    HWREG(baseAddress + OFS_ADC12IE) |= interruptMask;
    if (interruptMask & ADC12TOVIE0){
        HWREG(baseAddress + OFS_ADC12CTL0) |= ADC12TOVIE;
    }
    if (interruptMask & ADC12OVIE0){
        HWREG(baseAddress + OFS_ADC12CTL0) |= ADC12OVIE;
    }
}

//*****************************************************************************
//
//! Disables selected ADC12 interrupt sources.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param memoryInterruptMask is the bit mask of the memory buffer and overflow
//!       interrupt sources to be disabled.
//!        Mask values is the logical OR of any of the following
//!        \b ADC12IE0 - new conversion data in the 0th memory buffer
//!        \b ADC12IE1 - new conversion data in the 1st memory buffer
//!        \b ADC12IE2 - new conversion data in the 2nd memory buffer
//!        \b ADC12IE3 - new conversion data in the 3rd memory buffer
//!        \b ADC12IE4 - new conversion data in the 4th memory buffer
//!        \b ADC12IE5 - new conversion data in the 5th memory buffer
//!        \b ADC12IE6 - new conversion data in the 6th memory buffer
//!        \b ADC12IE7 - new conversion data in the 7th memory buffer
//!        \b ADC12IE8 - new conversion data in the 8th memory buffer
//!        \b ADC12IE9 - new conversion data in the 9th memory buffer
//!        \b ADC12IE10 - new conversion data in the 10th memory buffer
//!        \b ADC12IE11 - new conversion data in the 11th memory buffer
//!        \b ADC12IE12 - new conversion data in the 12th memory buffer
//!        \b ADC12IE13 - new conversion data in the 13th memory buffer
//!        \b ADC12IE14 - new conversion data in the 14th memory buffer
//!        \b ADC12IE15 - new conversion data in the 15th memory buffer
//!        \b ADC12OVIE0 - a conversion is about to save to a memory buffer that
//!                  has not been read out yet.
//!        \b ADC12TOVIE0 - a conversion is about to start before the previous
//!                  conversion has been completed.
//!
//! Disables the indicated ADC12 interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! Modified registers are \b ADC12CTL0 and \b ADC12IE.
//!
//! \return NONE
//
//*****************************************************************************
void ADC12_disableInterrupt (unsigned int baseAddress,
    unsigned long interruptMask)
{
    HWREG(baseAddress + OFS_ADC12IE) &= ~(interruptMask);
    if (interruptMask & ADC12TOVIE0){
        HWREG(baseAddress + OFS_ADC12CTL0) &= ~(ADC12TOVIE);
    }
    if (interruptMask & ADC12OVIE0){
        HWREG(baseAddress + OFS_ADC12CTL0) &= ~(ADC12OVIE);
    }
}

//*****************************************************************************
//
//! Clears ADC12 selected interrupt flags.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param memoryInterruptFlagMask is a bit mask of the interrupt flags to be
//!       cleared.
//!        Mask value is the logical OR of any of the following
//!        \b OFS_ADC12IFG0 - Flag the 0th memory buffer interrupt
//!        \b OFS_ADC12IFG1 - Flag the 1st memory buffer interrupt
//!        \b OFS_ADC12IFG2 - Flag the 2nd memory buffer interrupt
//!        \b OFS_ADC12IFG3 - Flag the 3rd memory buffer interrupt
//!        \b OFS_ADC12IFG4 - Flag the 4th memory buffer interrupt
//!        \b OFS_ADC12IFG5 - Flag the 5th memory buffer interrupt
//!        \b OFS_ADC12IFG6 - Flag the 6th memory buffer interrupt
//!        \b OFS_ADC12IFG7 - Flag the 7th memory buffer interrupt
//!        \b OFS_ADC12IFG8 - Flag the 8th memory buffer interrupt
//!        \b OFS_ADC12IFG9 - Flag the 9th memory buffer interrupt
//!        \b OFS_ADC12IFG10 - Flag the 10th memory buffer interrupt
//!        \b OFS_ADC12IFG11 - Flag the 11th memory buffer interrupt
//!        \b OFS_ADC12IFG12 - Flag the 12th memory buffer interrupt
//!        \b OFS_ADC12IFG13 - Flag the 13th memory buffer interrupt
//!        \b OFS_ADC12IFG14 - Flag the 14th memory buffer interrupt
//!        \b OFS_ADC12IFG15 - Flag the 15th memory buffer interrupt
//!
//! The selected ADC12 interrupt flags are cleared, so that it no longer asserts.
//! The memory buffer interrupt flags are only cleared when the memory buffer is
//! accessed. Note that the overflow interrupts do not have an interrupt flag to
//! clear; they must be accessed directly from the interrupt vector.
//!
//! Modified registers are \b ADC12IFG.
//
//! \return NONE
//
//*****************************************************************************
void ADC12_clearInterrupt (unsigned int baseAddress,
    unsigned int memoryInterruptFlagMask)
{
    HWREG(baseAddress + OFS_ADC12IFG) &= ~(memoryInterruptFlagMask);
}

//*****************************************************************************
//
//! Returns the status of the selected memory interrupt flags.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param memoryInterruptFlagMask is a bit mask of the interrupt flags status
//!       to be returned.
//!        Mask value is the logical OR of any of the following
//!        \b OFS_ADC12IFG0 - Flag the 0th memory buffer interrupt
//!        \b OFS_ADC12IFG1 - Flag the 1st memory buffer interrupt
//!        \b OFS_ADC12IFG2 - Flag the 2nd memory buffer interrupt
//!        \b OFS_ADC12IFG3 - Flag the 3rd memory buffer interrupt
//!        \b OFS_ADC12IFG4 - Flag the 4th memory buffer interrupt
//!        \b OFS_ADC12IFG5 - Flag the 5th memory buffer interrupt
//!        \b OFS_ADC12IFG6 - Flag the 6th memory buffer interrupt
//!        \b OFS_ADC12IFG7 - Flag the 7th memory buffer interrupt
//!        \b OFS_ADC12IFG8 - Flag the 8th memory buffer interrupt
//!        \b OFS_ADC12IFG9 - Flag the 9th memory buffer interrupt
//!        \b OFS_ADC12IFG10 - Flag the 10th memory buffer interrupt
//!        \b OFS_ADC12IFG11 - Flag the 11th memory buffer interrupt
//!        \b OFS_ADC12IFG12 - Flag the 12th memory buffer interrupt
//!        \b OFS_ADC12IFG13 - Flag the 13th memory buffer interrupt
//!        \b OFS_ADC12IFG14 - Flag the 14th memory buffer interrupt
//!        \b OFS_ADC12IFG15 - Flag the 15th memory buffer interrupt
//!
//! Returns the status of the selected memory interrupt flags. Note that the
//! overflow interrupts do not have an interrupt flag to clear; they must be
//! accessed directly from the interrupt vector.
//!

//! \return The current interrupt flag status for the corresponding mask.
//
//*****************************************************************************
unsigned char ADC12_getInterruptStatus (unsigned int baseAddress,
    unsigned int memoryInterruptFlagMask)
{
    return ( HWREG(baseAddress + OFS_ADC12IFG) & memoryInterruptFlagMask );
}

//*****************************************************************************
//
//! Enables/Starts an Analog-to-Digital Conversion.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param startingMemoryBufferIndex is the memory buffer that will hold the
//!       first or only conversion.
//!        Valid values are
//!        \b ADC12_MEMORY_0 [Default]
//!        \b ADC12_MEMORY_1
//!        \b ADC12_MEMORY_2
//!        \b ADC12_MEMORY_3
//!        \b ADC12_MEMORY_4
//!        \b ADC12_MEMORY_5
//!        \b ADC12_MEMORY_6
//!        \b ADC12_MEMORY_7
//!        \b ADC12_MEMORY_8
//!        \b ADC12_MEMORY_9
//!        \b ADC12_MEMORY_10
//!        \b ADC12_MEMORY_11
//!        \b ADC12_MEMORY_12
//!        \b ADC12_MEMORY_13
//!        \b ADC12_MEMORY_14
//!        \b ADC12_MEMORY_15
//!        Modified bits are \b ADC12STARTADDx of \b ADC12CTL1 register.
//! \param conversionSequenceModeSelect determines the ADC operating mode.
//!        Valid values are
//!        \b ADC12_SINGLECHANNEL - one-time conversion of a single channel into
//!           a single memory buffer. [Default]
//!        \b ADC12_SEQOFCHANNELS - one time conversion of multiple channels
//!           into the specified starting memory buffer and each subsequent
//!           memory buffer up until the conversion is stored in a memory buffer
//!           dedicated as the end-of-sequence by the memory's control register.
//!        \b ADC12_REPEATED_SINGLECHANNEL - repeated conversions of one channel
//!           into a single memory buffer.
//!        \b ADC12_REPEATED_SEQOFCHANNELS - repeated conversions of multiple
//!           channels into the specified starting memory buffer and each
//!           subsequent memory buffer up until the conversion is stored in a
//!           memory buffer dedicated as the end-of-sequence by the memory's
//!           control register.
//!        Modified bits are \b ADC12CONSEQx of \b ADC12CTL1 register.
//!
//! This function  enables/starts the conversion process of the ADC.
//! If the sample/hold signal source chosen during initialization was
//! ADC12OSC, then the conversion is started immediately, otherwise the chosen
//! sample/hold signal source starts the conversion by a rising edge of the
//! signal. Keep in mind when selecting conversion modes, that for sequenced
//! and/or repeated modes, to keep the sample/hold-and-convert process
//! continuing without a trigger from the sample/hold signal source, the
//! multiple samples must be enabled using the ADC12_setupSamplingTimer()
//! function. Note that after this function is called, the
//! ADC12_stopConversions() has to be called to re-initialize the ADC,
//! reconfigure a memory buffer control, enable/disable the sampling timer, or
//! to change the internal reference voltage.
//!
//! Modified registers are \b ADC12CTL0 and \b ADC12CTL1.
//! \return NONE
//
//*****************************************************************************
void ADC12_startConversion (unsigned int baseAddress,
    unsigned int startingMemoryBufferIndex,
    unsigned char conversionSequenceModeSelect)
{
    ASSERT(startingMemoryBufferIndex <= ADC12_MEMORY_15);
    ASSERT(conversionSequenceModeSelect <= ADC12_REPEATED_SEQOFCHANNELS);

    //Reset the ENC bit to set the starting memory address and conversion mode
    //sequence
    HWREGB(baseAddress + OFS_ADC12CTL0_L) &= ~(ADC12ENC);
    //Reset the bits about to be set
    HWREG(baseAddress + OFS_ADC12CTL0) &= ~(ADC12CSTARTADD_15 + ADC12CONSEQ_3);

    HWREGB(baseAddress + OFS_ADC12CTL1_H) |= (startingMemoryBufferIndex << 4);
    HWREGB(baseAddress + OFS_ADC12CTL1_L) |= conversionSequenceModeSelect;
    HWREGB(baseAddress + OFS_ADC12CTL0_L) |= ADC12ENC + ADC12SC;
}

//*****************************************************************************
//
//! Disables the ADC from converting any more signals.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param preempt specifies if the current conversion should be preemptly
//!       stopped before the end of the conversion.
//!        Valid values are
//!        \b ADC12_COMPLETECONVERSION - Allows the ADC12 to end the current
//!                  conversion before disabling conversions.
//!        \b ADC12_PREEMPTCONVERSION - Stops the ADC12 immediatly, with
//!                  unpredicatble results of the current conversion.
//!
//! Disables the ADC from converting any more signals.
//! If there is a conversion in progress, this function can stop it immediatly
//! if the preempt parameter is set as TRUE, by changing the conversion mode to
//! single-channel, single-conversion and disabling conversions. If the
//! conversion mode is set as single-channel, single-conversion and this
//! function is called without preemption, then the ADC core conversion status
//! is polled until the conversion is complete before disabling conversions to
//! prevent unpredictable data. If the ADC12_startConversion() has been called,
//! then this function has to be called to re-initialize the ADC, reconfigure a
//! memory buffer control, enable/disable the sampling pulse mode, or change the
//! internal reference voltage.
//!
//! Modified registers are \b ADC12CTL0 and \b ADC12CTL1.
//!
//! \return NONE
//
//*****************************************************************************
void ADC12_disableConversions (unsigned int baseAddress, unsigned short preempt)
{
    if (ADC12_PREEMPTCONVERSION == preempt){
        HWREGB(baseAddress + OFS_ADC12CTL1_L) &= ~(ADC12CONSEQ_3);
        //Reset conversion sequence mode to single-channel, single-conversion
    } else if (~(HWREGB(baseAddress + OFS_ADC12CTL1_L) & ADC12CONSEQ_3)){
        //To prevent preemoption of a single-channel, single-conversion we must
        //wait for the ADC core to finish the conversion.
        while (ADC12_isBusy(baseAddress)) ;
    }

    HWREGB(baseAddress + OFS_ADC12CTL0_L) &= ~(ADC12ENC);
}

//*****************************************************************************
//
//! Returns the raw contents of the specified memory buffer.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param memryBufferIndex is the specified Memory Buffer to read.
//!        Valid values are
//!        \b ADC12_MEMORY_0 [Default]
//!        \b ADC12_MEMORY_1
//!        \b ADC12_MEMORY_2
//!        \b ADC12_MEMORY_3
//!        \b ADC12_MEMORY_4
//!        \b ADC12_MEMORY_5
//!        \b ADC12_MEMORY_6
//!        \b ADC12_MEMORY_7
//!        \b ADC12_MEMORY_8
//!        \b ADC12_MEMORY_9
//!        \b ADC12_MEMORY_10
//!        \b ADC12_MEMORY_11
//!        \b ADC12_MEMORY_12
//!        \b ADC12_MEMORY_13
//!        \b ADC12_MEMORY_14
//!        \b ADC12_MEMORY_15
//!
//! Returns the raw contents of the specified memory buffer. The format of the
//! content depends on the read-back format of the data: if the data is in
//! signed 2's complement format then the contents in the memory buffer will be
//! left-justified with the least-siginificant bits as 0's, whereas if the data
//! is in unsigned format then the contents in the memory buffer will be
//! right-justified with the most-significant bits as 0's.
//!
//! \return A Signed Integer of the contents of the specified memory buffer.
//
//*****************************************************************************
int ADC12_getResults (unsigned int baseAddress, unsigned char memoryBufferIndex)
{
    ASSERT(memoryBufferIndex <= ADC12_MEMORY_15);

    return ( HWREG(baseAddress + (0x20 + (memoryBufferIndex * 2))) );
    //(0x20 + (memoryBufferIndex * 2)) == offset of ADC12MEMx
}

//*****************************************************************************
//
//! Use to change the resolution of the converted data.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param resolutionSelect determines the resolution of the converted data.
//!        Valid values are
//!        \b ADC12_RESOLUTION_8BIT
//!        \b ADC12_RESOLUTION_10BIT
//!        \b ADC12_RESOLUTION_12BIT [Default]
//!        Modified bits are \b ADC12RESx of \b ADC12CTL2 register.
//!
//! This function can be used to change the resolution of the converted data
//! from the default of 12-bits.
//!
//! \return NONE
//
//*****************************************************************************
void ADC12_setResolution (unsigned int baseAddress,
    unsigned char resolutionSelect)
{
    ASSERT(resolutionSelect <= ADC12_RESOLUTION_12BIT);

    HWREGB(baseAddress + OFS_ADC12CTL2_L) &= ~(ADC12RES_3);
    HWREGB(baseAddress + OFS_ADC12CTL2_L) |= resolutionSelect;
}

//*****************************************************************************
//
//! Use to invert or un-invert the sample/hold signal.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param invertedSignal set if the sample/hold signal should be inverted
//!        Valid values are
//!        \b ADC12_NONINVERTEDSIGNAL - a sample-and-hold of an input signal for
//!                  conversion will be started on a rising edge of the
//!                  sample/hold signal. [Default]
//!        \b ADC12_INVERTEDSIGNAL  - a sample-and-hold of an input signal for
//!                  conversion will be started on a falling edge of the
//!                  sample/hold signal.
//!        Modified bits are \b ADC12ISSH of \b ADC12CTL1 register.
//!
//! This function can be used to invert or un-invert the sample/hold signal.
//! Note that if a conversion has been started with the startConversion()
//! function, then a call to disableConversions() is required before this
//! function may be called.
//!
//! \return NONE
//
//*****************************************************************************
void ADC12_setSampleHoldSignalInversion (unsigned int baseAddress,
    unsigned int invertedSignal)
{
    //Make sure the ENC bit is cleared before using this function
    ASSERT( !(HWREGB(baseAddress + OFS_ADC12CTL0_L) & ADC12ENC) );

    HWREG(baseAddress + OFS_ADC12CTL1) &= ~(ADC12ISSH);
    HWREG(baseAddress + OFS_ADC12CTL1) |= invertedSignal;
}

//*****************************************************************************
//
//! Use to set the read-back format of the converted data.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param readBackFormat is the specified format to store the conversions in
//!       the memory buffer.
//!        Valid values are
//!        \b ADC12_UNSIGNED_BINARY [Default]
//!        \b ADC12_SIGNED_2SCOMPLEMENT
//!        Modified bits are \b ADC12DF of \b ADC12CTL2 register.
//!
//! Sets the format of the converted data: how it will be stored into the
//! memory buffer, and how it should be read back. The format can be set as
//! right-justified (default), which indicates that the number will be unsigned,
//! or left-justified, which indicates that the number will be signed in
//! 2's complement format. This change affects all memory buffers for subsequent
//! conversions.
//!
//! \return NONE
//
//*****************************************************************************
void ADC12_setDataReadBackFormat (unsigned int baseAddress,
    unsigned short readBackFormat)
{
    ASSERT(readBackFormat <= ADC12_SIGNED_2SCOMPLEMENT);

    HWREGB(baseAddress + OFS_ADC12CTL2_L) &= ~(ADC12DF);
    HWREGB(baseAddress + OFS_ADC12CTL2_L) |= readBackFormat;
}

//*****************************************************************************
//
//! Enables the reference buffer's burst ability.
//!
//! \param baseAddress is the base address of the ADC12 module.
//!
//! Enables the reference buffer's burst ability, allowing the reference buffer
//! to turn off while the ADC is not converting, and automatically turning on
//! when the ADC needs the generated reference voltage for a conversion.
//!
//! \return NONE
//
//*****************************************************************************
void ADC12_enableReferenceBurst (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_ADC12CTL2_L) |= ADC12REFBURST;
}

//*****************************************************************************
//
//! Disables the reference buffer's burst ability.
//!
//! \param baseAddress is the base address of the ADC12 module.
//!
//! Disables the reference buffer's burst ability, forcing the reference buffer
//! to remain on continuously.
//!
//! \return NONE
//
//*****************************************************************************
void ADC12_disableReferenceBurst (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_ADC12CTL2_L) &= ~(ADC12REFBURST);
}

//*****************************************************************************
//
//! Use to set the reference buffer's sampling rate.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param samplingRateSelect is the specified maximum sampling rate.
//!        Valid values are
//!        \b ADC12_MAXSAMPLINGRATE_200KSPS [Default]
//!        \b ADC12_MAXSAMPLINGRATE_50KSPS
//!        Modified bits are \b ADC12SR of \b ADC12CTL2 register.
//!
//! Sets the reference buffer's sampling rate to the selected sampling rate. The
//! default sampling rate is maximum of 200-ksps, and can be reduced to a
//! maximum of 50-ksps to conserve power.
//!
//! \return NONE
//
//*****************************************************************************
void ADC12_setReferenceBufferSamplingRate (unsigned int baseAddress,
    unsigned short samplingRateSelect)
{
    ASSERT(samplingRateSelect <= ADC12_MAXSAMPLINGRATE_50KSPS);

    HWREGB(baseAddress + OFS_ADC12CTL2_L) &= ~(ADC12SR);
    HWREGB(baseAddress + OFS_ADC12CTL2_L) |= samplingRateSelect;
}

//*****************************************************************************
//
//! Returns the address of the specified memory buffer for the DMA module.
//!
//! \param baseAddress is the base address of the ADC12 module.
//! \param memoryIndex is the memory buffer to return the address of.
//!        Valid values are
//!        \b ADC12_MEMORY_0 [Default]
//!        \b ADC12_MEMORY_1
//!        \b ADC12_MEMORY_2
//!        \b ADC12_MEMORY_3
//!        \b ADC12_MEMORY_4
//!        \b ADC12_MEMORY_5
//!        \b ADC12_MEMORY_6
//!        \b ADC12_MEMORY_7
//!        \b ADC12_MEMORY_8
//!        \b ADC12_MEMORY_9
//!        \b ADC12_MEMORY_10
//!        \b ADC12_MEMORY_11
//!        \b ADC12_MEMORY_12
//!        \b ADC12_MEMORY_13
//!        \b ADC12_MEMORY_14
//!        \b ADC12_MEMORY_15
//!
//! Returns the address of the specified  memory buffer. This can be used in
//! conjunction with the DMA to store the converted data directly to memory.
//!
//! \return NONE
//
//*****************************************************************************
unsigned long ADC12_getMemoryAddressForDMA (unsigned int baseAddress,
    unsigned char memoryIndex)
{
    return ( baseAddress + (0x20 + (memoryIndex * 2)) );
}

//*****************************************************************************
//
//! Returns the busy status of the ADC12 core.
//!
//! \param baseAddress is the base address of the ADC12 module.
//!
//! Returns the status of the ADC core if there is a conversion currently taking
//! place.
//!
//! \return ADC12_BUSY or ADC12_NOTBUSY dependent if there is a conversion
//!        currently taking place.
//
//*****************************************************************************
unsigned short ADC12_isBusy (unsigned int baseAddress)
{
    if (HWREGB(baseAddress + OFS_ADC12CTL1_L) & ADC12BUSY){
        return ( ADC12_BUSY) ;
    } else   {
        return ( ADC12_NOTBUSY) ;
    }
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
