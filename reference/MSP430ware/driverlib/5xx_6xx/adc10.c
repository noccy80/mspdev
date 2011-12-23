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
//adc10.c - Driver for the ADC10 Module.
//
//*****************************************************************************
#include "driverlib/5xx_6xx/adc10.h"
#include "inc/hw_types.h"
#include "msp430xgeneric.h"
#include "driverlib/5xx_6xx/debug.h"

//*****************************************************************************
//
//! Initializes the ADC10 Module.
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param sampleHoldSignalSourceSelect is the signal that will trigger a
//!       sample-and-hold for an input signal to be converted.
//!        Valid values are
//!        \b ADC10_SAMPLEHOLDSOURCE_SC
//!        \b ADC10_SAMPLEHOLDSOURCE_1
//!        \b ADC10_SAMPLEHOLDSOURCE_2
//!        \b ADC10_SAMPLEHOLDSOURCE_3
//!        This parameter is device specific and sources should be found in the
//!        device's datasheet.
//!        Modified bits are \b ADC10SHSx of \b ADC10CTL1 register.
//! \param clockSourceSelect selects the clock that will be used by the ADC10
//!       core and the sampling timer if a sampling pulse mode is enabled.
//!        Valid values are
//!        \b ADC10_CLOCKSOURCE_ADC10OSC - MODOSC 5 MHz oscillator from the UCS
//!            [Default]
//!        \b ADC10_CLOCKSOURCE_ACLK     - The Auxilary Clock
//!        \b ADC10_CLOCKSOURCE_MCLK     - The Master Clock
//!        \b ADC10_CLOCKSOURCE_SMCLK    - The Sub-Master Clock
//!        Modified bits are \b ADC10SSELx of \b ADC10CTL1 register.
//! \param clockSourceDivider selects the amount that the clock will be divided.
//!        Valid values are
//!        \b ADC10_CLOCKDIVIDER_1 [Default]
//!        \b ADC10_CLOCKDIVIDER_2
//!        \b ADC10_CLOCKDIVIDER_3
//!        \b ADC10_CLOCKDIVIDER_4
//!        \b ADC10_CLOCKDIVIDER_5
//!        \b ADC10_CLOCKDIVIDER_6
//!        \b ADC10_CLOCKDIVIDER_7
//!        \b ADC10_CLOCKDIVIDER_8
//!        \b ADC10_CLOCKDIVIDER_12
//!        \b ADC10_CLOCKDIVIDER_16
//!        \b ADC10_CLOCKDIVIDER_20
//!        \b ADC10_CLOCKDIVIDER_24
//!        \b ADC10_CLOCKDIVIDER_28
//!        \b ADC10_CLOCKDIVIDER_32
//!        \b ADC10_CLOCKDIVIDER_64
//!        \b ADC10_CLOCKDIVIDER_128
//!        \b ADC10_CLOCKDIVIDER_192
//!        \b ADC10_CLOCKDIVIDER_256
//!        \b ADC10_CLOCKDIVIDER_320
//!        \b ADC10_CLOCKDIVIDER_384
//!        \b ADC10_CLOCKDIVIDER_448
//!        \b ADC10_CLOCKDIVIDER_512
//!        Modified bits are \b ADC10DIVx of \b ADC10CTL1 register and
//!         \b ADC10PDIVx of \b ADC10CTL2 register.
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
unsigned short ADC10_init (unsigned int baseAddress,
    unsigned int sampleHoldSignalSourceSelect,
    unsigned char clockSourceSelect,
    unsigned int clockSourceDivider)
{
    //Make sure the ENC bit is cleared before initializing the ADC10
    ASSERT( !(HWREG(baseAddress + OFS_ADC10CTL0) & ADC10ENC) );

    ASSERT(sampleHoldSignalSourceSelect <= ADC10_SAMPLEHOLDSOURCE_3);
    ASSERT(clockSourceSelect <= ADC10_CLOCKSOURCE_SMCLK);
    ASSERT(clockSourceDivider <= ADC10_CLOCKDIVIDER_512);

    unsigned char retVal = STATUS_SUCCESS;

    //Turn OFF ADC10 Module & Clear Interrupt Registers
    HWREG(baseAddress + OFS_ADC10CTL0) &= ~(ADC10ON + ADC10ENC + ADC10SC);
    HWREG(baseAddress + OFS_ADC10IE)   &= 0x0000; //Reset ALL interrupt enables
    HWREG(baseAddress + OFS_ADC10IFG)  &= 0x0000; //Reset ALL interrupt flags

    //Set ADC10 Control 1
    HWREG(baseAddress + OFS_ADC10CTL1) =
        sampleHoldSignalSourceSelect //Setup the Sample-and-Hold Source
        + (clockSourceDivider & ADC10DIV_7) //Set Clock Divider
        + clockSourceSelect; //Setup Clock Source

    //Set ADC10 Control 2
    HWREG(baseAddress + OFS_ADC10CTL2) =
        (clockSourceDivider & ADC10PDIV_3) //Set Clock Pre-Divider
        + ADC10RES; //Default resolution to 10-bits

    return ( retVal) ;
}

//*****************************************************************************
//
//! Enables the ADC10 block.
//!
//! \param baseAddress is the base address of the ADC10 module.
//!
//! This will enable operation of the ADC10 block.
//! Modified bits are \b ADC10ON of \b ADC10CTL0 register.
//!
//! \return None.
//
//*****************************************************************************
void ADC10_enable (unsigned int baseAddress)
{
    //Reset the ADC10ON bit to enable the ADC10 Module
    HWREG(baseAddress + OFS_ADC10CTL0) |= ADC10ON;
}

//*****************************************************************************
//
//! Disables the ADC10 block.
//!
//! \param baseAddress is the base address of the ADC10 module.
//!
//! This will disable operation of the ADC10 block.
//! Modified bits are \b ADC10ON of \b ADC10CTL0 register.
//!
//! \return None.
//
//*****************************************************************************
void ADC10_disable (unsigned int baseAddress)
{
    //Set the ADC10ON bit to disable the ADC10 Module
    HWREG(baseAddress + OFS_ADC10CTL0) &= ~ADC10ON;
}

//*****************************************************************************
//
//! Sets up and enables the Sampling Timer Pulse Mode.
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param clockCycleHoldCount sets the amount of clock cycles to
//!       sample-and-hold for the memory buffer.
//!        Valid values are
//!        \b ADC10_CYCLEHOLD_4_CYCLES [Default]
//!        \b ADC10_CYCLEHOLD_8_CYCLES
//!        \b ADC10_CYCLEHOLD_16_CYCLES
//!        \b ADC10_CYCLEHOLD_32_CYCLES
//!        \b ADC10_CYCLEHOLD_64_CYCLES
//!        \b ADC10_CYCLEHOLD_96_CYCLES
//!        \b ADC10_CYCLEHOLD_128_CYCLES
//!        \b ADC10_CYCLEHOLD_192_CYCLES
//!        \b ADC10_CYCLEHOLD_256_CYCLES
//!        \b ADC10_CYCLEHOLD_384_CYCLES
//!        \b ADC1 0_CYCLEHOLD_512_CYCLES
//!        \b ADC10_CYCLEHOLD_768_CYCLES
//!        \b ADC10_CYCLEHOLD_1024_CYCLES
//!        Modified bits are \b ADC10SHTx of \b ADC10CTL0 register.
//! \param multipleSamplesEnabled allows multiple conversions to start
//!       without a trigger signal from the sample/hold signal
//!        Valid values are
//!        \b ADC10_MULTIPLESAMPLESDISABLE - a timer trigger will be needed to
//!                  start every ADC conversion.
//!        \b ADC10_MULTIPLESAMPLESENABLE  - during a sequenced and/or repeated
//!                  conversion mode, after the first conversion, no sample/hold
//!                  signal is necessary to start subsequent samples.
//!        Modified bits are \b ADC10MSC of \b ADC10CTL0 register.
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
void ADC10_setupSamplingTimer (unsigned int baseAddress,
    unsigned int clockCycleHoldCount,
    unsigned short multipleSamplesEnabled)
{
    //Make sure the ENC bit is cleared before setting up sampling pulse mode
    ASSERT( !(HWREG(baseAddress + OFS_ADC10CTL0) & ADC10ENC) );

    ASSERT(clockCycleHoldCount <= ADC10_CYCLEHOLD_1024_CYCLES);

    HWREG(baseAddress + OFS_ADC10CTL1) |= ADC10SHP;

    //Reset and Set CB Control 0 Bits
    HWREG(baseAddress + OFS_ADC10CTL0) &= ~(ADC10SHT_15 + ADC10MSC);
    HWREG(baseAddress + OFS_ADC10CTL0) |= clockCycleHoldCount
                                          + multipleSamplesEnabled;
}

//*****************************************************************************
//
//! Disables Sampling Timer Pulse Mode.
//!
//! \param baseAddress is the base address of the ADC10 module.
//!
//! Disables the Sampling Timer Pulse Mode. Note that if a conversion has been
//! started with the startConversion() function, then a call to
//! disableConversions() is required before this function may be called.
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_disableSamplingTimer (unsigned int baseAddress)
{
    //Make sure the ENC bit is cleared before disabling sampling pulse mode
    ASSERT( ~(HWREG(baseAddress + OFS_ADC10CTL0) & ADC10ENC) );

    HWREG(baseAddress + OFS_ADC10CTL1) &= ~(ADC10SHP);
}

//*****************************************************************************
//
//! Configures the controls of the selected memory buffer.
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param inputSourceSelect is the input that will store the converted data
//!       into the specified memory buffer.
//!        Valid values are
//!        \b ADC10_INPUT_A0 [Default]
//!        \b ADC10_INPUT_A1
//!        \b ADC10_INPUT_A2
//!        \b ADC10_INPUT_A3
//!        \b ADC10_INPUT_A4
//!        \b ADC10_INPUT_A5
//!        \b ADC10_INPUT_A6
//!        \b ADC10_INPUT_A7
//!        \b ADC10_INPUT_A8
//!        \b ADC10_INPUT_A9
//!        \b ADC10_INPUT_TEMPSENSOR
//!        \b ADC10_INPUT_BATTERYMONITOR
//!        \b ADC10_INPUT_A12
//!        \b ADC10_INPUT_A13
//!        \b ADC10_INPUT_A14
//!        \b ADC10_INPUT_A15
//!        Modified bits are \b ADC10INCHx of \b ADC10MCTL0 register.
//! \param positiveRefVoltageSourceSelect is the reference voltage source to set
//!       as the upper limit for the conversion that is to be stored in the
//!       specified memory buffer.
//!        Valid values are
//!        \b ADC10_VREFPOS_AVCC [Default]
//!        \b ADC10_VREFPOS_EXT
//!        \b ADC10_VREFPOS_INT
//!        Modified bits are \b ADC10SREF of \b ADC10MCTL0 register.
//! \param negativeRefVoltageSourceSelect is the reference voltage source to set
//!       as the lower limit for the conversion that is to be stored in the
//!       specified memory buffer.
//!        Valid values are
//!        \b ADC10_VREFPOS_AVSS [Default]
//!        \b ADC10_VREFPOS_EXT
//!        Modified bits are \b ADC10SREF of \b ADC10CTL0 register.
//!
//! Maps an input signal conversion into the memory buffer, as
//! well as the positive and negative reference voltages for each conversion
//! being stored into the memory buffer. If the internal reference is used for
//! the positive reference voltage, the internal REF module has to control
//! the voltage level. Note that if a conversion has been started with the
//! startConversion() function, then a call to disableConversions() is required
//! before this function may be called.
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_memoryConfigure (unsigned int baseAddress,
    unsigned char inputSourceSelect,
    unsigned char positiveRefVoltageSourceSelect,
    unsigned char negativeRefVoltageSourceSelect)
{
    //Make sure the ENC bit is cleared before configuring a Memory Buffer Control
    ASSERT( !(HWREG(baseAddress + OFS_ADC10CTL0) & ADC10ENC) );

    ASSERT(inputSourceSelect <= ADC10_INPUT_A15);
    ASSERT(positiveRefVoltageSourceSelect <= ADC10_VREFPOS_INT);
    ASSERT(negativeRefVoltageSourceSelect <= ADC10_VREFNEG_EXT);

    //Reset and Set the Memory Buffer Control Bits
    HWREGB(baseAddress + OFS_ADC10MCTL0) = inputSourceSelect
                                           + positiveRefVoltageSourceSelect +
                                           negativeRefVoltageSourceSelect;
}

//*****************************************************************************
//
//! Enables selected ADC10 interrupt sources.
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param interruptMask is the bit mask of the memory buffer interrupt
//!       sources to be enabled.
//!        Mask Value is the logical OR of any of the following
//!        \b ADC10OVIE - Interrupts when a new conversion is about to overwrite
//!                 the previous one
//!        \b ADC10TOVIE - Interrupts when a new conversion is starting befor
//!                 the previous one has finished
//!        \b ADC10HIIE - Interrups when the input signal has gone above the
//!                 high threshold of the window comparator
//!        \b ADC10LOIE - Interrupts when the input signal has gone below the
//!                 low threshold of the low window comparator
//!        \b ADC10INIE - Interrupts when the input signal is in between the
//!                 high and low thresholds of the window comparator
//!        \b ADC10IE0 - Interrupt for new conversion data in the memory buffer
//!
//! Enables the indicated ADC10 interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//! Modified registers are  \b ADC10IFG and \b ADC10IE.
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_enableInterrupt (unsigned int baseAddress,
    unsigned char interruptMask)
{
    HWREG(baseAddress + OFS_ADC10IFG) &= ~interruptMask;
    HWREG(baseAddress + OFS_ADC10IE) |= interruptMask;
}

//*****************************************************************************
//
//! Disables selected ADC10 interrupt sources.
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param interruptMask is the bit mask of the memory buffer interrupt
//!       sources to be disabled.
//!        Mask Value is the logical OR of any of the following
//!        \b ADC10OVIE - Interrupts when a new conversion is about to overwrite
//!                 the previous one
//!        \b ADC10TOVIE - Interrupts when a new conversion is starting befor
//!                 the previous one has finished
//!        \b ADC10HIIE - Interrups when the input signal has gone above the
//!                 high threshold of the window comparator
//!        \b ADC10LOIE - Interrupts when the input signal has gone below the
//!                 low threshold of the low window comparator
//!        \b ADC10INIE - Interrupts when the input signal is in between the
//!                 high and low thresholds of the window comparator
//!        \b ADC10IE0 - Interrupt for new conversion data in the memory buffer
//!
//! Disables the indicated ADC10 interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//! Modified registers are ADC10IE.
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_disableInterrupt (unsigned int baseAddress,
    unsigned char interruptMask)
{
    HWREG(baseAddress + OFS_ADC10IE) &= ~(interruptMask);
}

//*****************************************************************************
//
//! Clears ADC10 selected interrupt flags.
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param interruptFlagMask is a bit mask of the interrupt flags to be cleared.
//!        Mask Value is the logical OR of any of the following
//!        \b ADC10OVIFG - Interrupt flag for when a new conversion is about to
//!                  overwrite the previous one
//!        \b ADC10TOVIFG - Interrupt flag for when a new conversion is starting
//!                 before the previous one has finished
//!        \b ADC10HIIFG - Interrup flag for when the input signal has gone
//!                 above the high threshold of the window comparator
//!        \b ADC10LOIFG - Interrupt flag for when the input signal has gone
//!                 below the low threshold of the window comparator
//!        \b ADC10INIFG - Interrupt flag for when the input signal is in
//!                 between the high and low thresholds of the window comparator
//!        \b ADC10IFG0 - Interrupt flag for new conversion data in the memory
//!                 buffer
//!
//! The selected ADC10 interrupt flags are cleared, so that it no longer asserts.
//! The memory buffer interrupt flags are only cleared when the memory buffer is
//! accessed.
//! Modified registers are  \b ADC10IFG
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_clearInterrupt (unsigned int baseAddress,
    unsigned char interruptFlagMask)
{
    HWREG(baseAddress + OFS_ADC10IFG) &= ~(interruptFlagMask);
}

//*****************************************************************************
//
//! Returns the status of the selected memory interrupt flags.
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param interruptFlagMask is a bit mask of the interrupt flags status
//!       to be returned.
//!        Mask Value is the logical OR of any of the following
//!        \b ADC10OVIFG - Interrupt flag for when a new conversion is about to
//!                  overwrite the previous one
//!        \b ADC10TOVIFG - Interrupt flag for when a new conversion is starting
//!                 before the previous one has finished
//!        \b ADC10HIIFG - Interrup flag for when the input signal has gone
//!                 above the high threshold of the window comparator
//!        \b ADC10LOIFG - Interrupt flag for when the input signal has gone
//!                 below the low threshold of the window comparator
//!        \b ADC10INIFG - Interrupt flag for when the input signal is in
//!                 between the high and low thresholds of the window comparator
//!        \b ADC10IFG0 - Interrupt flag for new conversion data in the memory
//!                 buffer
//!
//! Returns the status of the selected interrupt flags.
//!
//! \return The current interrupt flag status for the corresponding mask.
//
//*****************************************************************************
unsigned char ADC10_getInterruptStatus (unsigned int baseAddress,
    unsigned char interruptFlagMask)
{
    return ( HWREG(baseAddress + OFS_ADC10IFG) & interruptFlagMask );
}

//*****************************************************************************
//
//! Enables/Starts an Analog-to-Digital Conversion.
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param conversionSequenceModeSelect determines the ADC operating mode.
//!        Valid values are
//!        \b ADC10_SINGLECHANNEL - one-time conversion of a single channel into
//!           a single memory buffer [Default]
//!        \b ADC10_SEQOFCHANNELS - one time conversion of multiple channels
//!           into the specified starting memory buffer and each subsequent
//!           memory buffer up until the conversion is stored in a memory buffer
//!           dedicated as the end-of-sequence by the memory's control register
//!        \b ADC10_REPEATED_SINGLECHANNEL - repeated conversions of one channel
//!           into a single memory buffer
//!        \b ADC10_REPEATED_SEQOFCHANNELS - repeated conversions of multiple
//!           channels into the specified starting memory buffer and each
//!           subsequent memory buffer up until the conversion is stored in a
//!           memory buffer dedicated as the end-of-sequence by the memory's
//!           control register
//!        Modified bits are \b ADC10CONSEQx of \b ADC10CTL1 register.
//!
//! This function  enables/starts the conversion process of the ADC.
//! If the sample/hold signal source chosen during initialization was
//! ADC10OSC, then the conversion is started immediately, otherwise the chosen
//! sample/hold signal source starts the conversion by a rising edge of the
//! signal. Keep in mind when selecting conversion modes, that for sequenced
//! and/or repeated modes, to keep the sample/hold-and-convert process
//! continuing without a trigger from the sample/hold signal source, the
//! multiple samples must be enabled using the ADC10_setupSamplingTimer()
//! function. Also note that when a sequence conversion mode is selected, the
//! first input channel is the one mapped to the memory buffer, the next input
//! channel selected for conversion is one less than the input channel just
//! converted (i.e. A1 comes after A2), until A0 is reached, and if in repeating
//! mode, then the next input channel will again be the one mapped to the memory
//! buffer. Note that after this function is called, the ADC10_stopConversions()
//! has to be called to re-initialize the ADC, reconfigure a memory buffer
//! control, enable/disable the sampling timer, or to change the internal
//! reference voltage.
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_startConversion (unsigned int baseAddress,
    unsigned char conversionSequenceModeSelect)
{
    ASSERT(conversionSequenceModeSelect <= ADC10_REPEATED_SEQOFCHANNELS);

    //Reset the ENC bit to set the conversion mode sequence
    HWREG(baseAddress + OFS_ADC10CTL0) &= ~(ADC10ENC);

    HWREG(baseAddress + OFS_ADC10CTL1) |= conversionSequenceModeSelect;
    HWREG(baseAddress + OFS_ADC10CTL0) |= ADC10ENC + ADC10SC;
}

//*****************************************************************************
//
//! Disables the ADC from converting any more signals.
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param preempt specifies if the current conversion should be preemptly
//!       stopped before the end of the conversion
//!        Valid values are
//!        \b ADC10_COMPLETECONVERSION - Allows the ADC10 to end the current
//!                  conversion before disabling conversions.
//!        \b ADC10_PREEMPTCONVERSION - Stops the ADC10 immediatly, with
//!                  unpredicatble results of the current conversion. Cannot be
//!                  used with repeated conversion.
//!
//! Disables the ADC from converting any more signals.
//! If there is a conversion in progress, this function can stop it immediatly
//! if the preempt parameter is set as ADC10_PREEMPTCONVERSION, by changing the
//! conversion mode to single-channel, single-conversion and disabling
//! conversions. If the conversion mode is set as single-channel,
//! single-conversion and this function is called without preemption, then the
//! ADC core conversion status is polled until the conversion is complete before
//! disabling conversions to prevent unpredictable data. If the
//! ADC10_startConversion() has been called, then this function has to be called
//! to re-initialize the ADC, reconfigure a memory buffer control,
//! enable/disable the sampling pulse mode, or change the internal reference
//! voltage.
//! Modified registers are  \b ADC10CTL1 and \b ADC10CTL0
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_disableConversions (unsigned int baseAddress, unsigned short preempt)
{
    if (ADC10_PREEMPTCONVERSION == preempt){
        HWREG(baseAddress + OFS_ADC10CTL1) &= ~(ADC10CONSEQ_3);
        //Reset conversion sequence mode to single-channel, single-conversion
    } else if ( ~(HWREG(baseAddress + OFS_ADC10CTL1) & ADC10CONSEQ_3) ){
        //To prevent preemoption of a single-channel, single-conversion we must
        //wait for the ADC core to finish the conversion.
        while (HWREG(baseAddress + OFS_ADC10CTL1) & ADC10BUSY) ;
    }

    HWREG(baseAddress + OFS_ADC10CTL0) &= ~(ADC10ENC);
}

//*****************************************************************************
//
//! Returns the raw contents of the specified memory buffer.
//!
//! \param baseAddress is the base address of the ADC10 module.
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
int ADC10_getResults (unsigned int baseAddress)
{
    return ( HWREG(baseAddress + OFS_ADC10MEM0) );
}

//*****************************************************************************
//
//! Use to change the resolution of the converted data.
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param resolutionSelect determines the resolution of the converted data.
//!        Valid values are
//!        \b ADC10_RESOLUTION_8BIT
//!        \b ADC10_RESOLUTION_10BIT [Default]
//!        Modified bits are \b ADC10RES of \b ADC10CTL2 register.
//!
//! This function can be used to change the resolution of the converted data
//! from the default of 12-bits.
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_setResolution (unsigned int baseAddress,
    unsigned char resolutionSelect)
{
    ASSERT(resolutionSelect <= ADC10_RESOLUTION_10BIT);

    HWREG(baseAddress + OFS_ADC10CTL2) &= ~(ADC10RES);
    HWREG(baseAddress + OFS_ADC10CTL2) |= resolutionSelect;
}

//*****************************************************************************
//
//! Use to invert or un-invert the sample/hold signal
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param invertedSignal set if the sample/hold signal should be inverted
//!        Valid values are
//!        \b ADC10_NONINVERTEDSIGNAL - a sample-and-hold of an input signal for
//!                  conversion will be started on a rising edge of the
//!                  sample/hold signal. [Default]
//!        \b ADC10_INVERTEDSIGNAL  - a sample-and-hold of an input signal for
//!                  conversion will be started on a falling edge of the
//!                  sample/hold signal.
//!        Modified bits are \b ADC10ISSH of \b ADC10CTL1 register.
//!
//! This function can be used to invert or un-invert the sample/hold signal.
//! Note that if a conversion has been started with the startConversion()
//! function, then a call to disableConversions() is required before this
//! function may be called.
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_setSampleHoldSignalInversion (unsigned int baseAddress,
    unsigned int invertedSignal)
{
    //Make sure the ENC bit is cleared before using this function
    ASSERT( !(HWREG(baseAddress + OFS_ADC10CTL0) & ADC10ENC) );

    HWREG(baseAddress + OFS_ADC10CTL1) &= ~(ADC10ISSH);
    HWREG(baseAddress + OFS_ADC10CTL1) |= invertedSignal;
}

//*****************************************************************************
//
//! Use to set the read-back format of the converted data
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param readBackFormat is the specified format to store the conversions in
//!       the memory buffer.
//!        Valid values are
//!        \b ADC10_UNSIGNED_BINARY [Default]
//!        \b ADC10_SIGNED_2SCOMPLEMENT
//!        Modified bits are \b ADC10DF of \b ADC10CTL2 register.
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
void ADC10_setDataReadBackFormat (unsigned int baseAddress,
    unsigned short readBackFormat)
{
    ASSERT(readBackFormat <= ADC10_SIGNED_2SCOMPLEMENT);

    HWREG(baseAddress + OFS_ADC10CTL2) &= ~(ADC10DF);
    HWREG(baseAddress + OFS_ADC10CTL2) |= readBackFormat;
}

//*****************************************************************************
//
//! Enables the reference buffer's burst ability.
//!
//! \param baseAddress is the base address of the ADC10 module.
//!
//! Enables the reference buffer's burst ability, allowing the reference buffer
//! to turn off while the ADC is not converting, and automatically turning on
//! when the ADC needs the generated reference voltage for a conversion.
//!
//! Modified bits are \b ADC10REFBURST of \b ADC10CTL2 register.
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_enableReferenceBurst (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_ADC10CTL2) |= ADC10REFBURST;
}

//*****************************************************************************
//
//! Disables the reference buffer's burst ability.
//!
//! \param baseAddress is the base address of the ADC10 module.
//!
//! Disables the reference buffer's burst ability, forcing the reference buffer
//! to remain on continuously.
//!
//! Modified bits are \b ADC10REFBURST of \b ADC10CTL2 register.
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_disableReferenceBurst (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_ADC10CTL2) &= ~(ADC10REFBURST);
}

//*****************************************************************************
//
//! Use to set the reference buffer's sampling rate.
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param samplingRateSelect is the specified maximum sampling rate.
//!        Valid values are
//!        \b ADC10_MAXSAMPLINGRATE_200KSPS [Default]
//!        \b ADC10_MAXSAMPLINGRATE_50KSPS
//!        Modified bits are \b ADC10SR of \b ADC10CTL2 register.
//!
//! Sets the reference buffer's sampling rate to the selected sampling rate. The
//! default sampling rate is maximum of 200-ksps, and can be reduced to a
//! maximum of 50-ksps to conserve power.
//!
//! Modified regsiters are \b ADC10CTL2.
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_setReferenceBufferSamplingRate (unsigned int baseAddress,
    unsigned short samplingRateSelect)
{
    ASSERT(samplingRateSelect <= ADC10_MAXSAMPLINGRATE_50KSPS);

    HWREG(baseAddress + OFS_ADC10CTL2) &= ~(ADC10SR);
    HWREG(baseAddress + OFS_ADC10CTL2) |= samplingRateSelect;
}

//*****************************************************************************
//
//! Sets the high and low threshold for the window comparator feature.
//!
//! \param baseAddress is the base address of the ADC10 module.
//! \param highThreshold is the upper bound  that could trip an interrupt for
//!       the window comparator.
//! \param lowThreshold is the lower bound that could trip on interrupt for the
//!       window comparator.
//!
//! Sets the high and low threshold for the window comparator feature. Use the
//! ADC10HIIE, ADC10INIE, ADC10LOIE interrupts to utilize this feature.
//!
//! Modified regsiters are \b ADC10HI and \b ADC10LO.
//!
//! \return NONE
//
//*****************************************************************************
void ADC10_setWindowComp (unsigned int baseAddress,
    unsigned int highThreshold,
    unsigned int lowThreshold)
{
    HWREG(baseAddress + OFS_ADC10HI) = highThreshold;
    HWREG(baseAddress + OFS_ADC10LO) = lowThreshold;
}

//*****************************************************************************
//
//! Returns the address of the memory buffer for the DMA module.
//!
//! \param baseAddress is the base address of the ADC10 module.
//!
//! Returns the address of the memory buffer. This can be used in conjunction
//! with the DMA to store the converted data directly to memory.
//!
//! \return NONE
//
//*****************************************************************************
unsigned long ADC10_getMemoryAddressForDMA (unsigned int baseAddress)
{
    return ( baseAddress + OFS_ADC10MEM0 );
}

//*****************************************************************************
//
//! Returns the busy status of the ADC10 core.
//!
//! \param baseAddress is the base address of the ADC10 module.
//!
//! Returns the status of the ADC core if there is a conversion currently taking
//! place.
//!
//! \return ADC10_BUSY or ADC10_NOTBUSY dependent if there is a conversion
//!        currently taking place.
//
//*****************************************************************************
unsigned short ADC10_isBusy (unsigned int baseAddress)
{
    if (HWREG(baseAddress + OFS_ADC10CTL1) & ADC10BUSY){
        return ( ADC10_BUSY) ;
    } else   {
        return ( ADC10_NOTBUSY) ;
    }
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************

