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
//dma.c - Driver for the DMA Module.
//
//*****************************************************************************
#include "driverlib/5xx_6xx/dma.h"
#include "inc/hw_types.h"
#include "msp430xgeneric.h"
#include "driverlib/5xx_6xx/debug.h"

//*****************************************************************************
//
//! Initializes the specified DMA channel.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to initialize.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//! \param transferModeSelect is the transfer mode of the selected channel.
//!        Valid values are
//!        \b DMA_TRANSFER_SINGLE - Single transfer, transfers disabled after
//!             transferAmount of transfers. [Default]
//!        \b DMA_TRANSFER_BLOCK - Multiple transfers of transferAmount,
//!             transfers disabled once finished.
//!        \b DMA_TRANSFER_BURSTBLOCK - Multiple transfers of transferAmount
//!             interleaved with CPU activity, transfers disabled once finished.
//!        \b DMA_TRANSFER_REPEATED_SINGLE - Repeated single transfer by trigger.
//!        \b DMA_TRANSFER_REPEATED_BLOCK - Multiple transfers of transferAmount
//!             by trigger.
//!        \b DMA_TRANSFER_REPEATED_BURSTBLOCK - Multiple transfers of
//!             transferAmount by trigger interleaved with CPU activity.
//!        Modified bits are \b DMADT of \b DMAxCTL register.
//! \param transferSize is the amount of transfers to complete in a block
//!       transfer mode, as well as how many transfers to complete before the
//!       interrupt flag is set. Valid value is between 1-65535, if 0, no
//!       transfers will occur.
//!        Modified bits are \b DMAxSZ of \b DMAzSZ register.
//! \param triggerSourceSelect is the source that will trigger the start of each
//!       transfer, note that the sources are device specific.
//!        Valid values are
//!        \b DMA_TRIGGERSOURCE_0 [Default]
//!        \b DMA_TRIGGERSOURCE_1
//!        \b DMA_TRIGGERSOURCE_2
//!        \b DMA_TRIGGERSOURCE_3
//!        \b DMA_TRIGGERSOURCE_4
//!        \b DMA_TRIGGERSOURCE_5
//!        \b DMA_TRIGGERSOURCE_6
//!        \b DMA_TRIGGERSOURCE_7
//!        \b DMA_TRIGGERSOURCE_8
//!        \b DMA_TRIGGERSOURCE_9
//!        \b DMA_TRIGGERSOURCE_10
//!        \b DMA_TRIGGERSOURCE_11
//!        \b DMA_TRIGGERSOURCE_12
//!        \b DMA_TRIGGERSOURCE_13
//!        \b DMA_TRIGGERSOURCE_14
//!        \b DMA_TRIGGERSOURCE_15
//!        \b DMA_TRIGGERSOURCE_16
//!        \b DMA_TRIGGERSOURCE_17
//!        \b DMA_TRIGGERSOURCE_18
//!        \b DMA_TRIGGERSOURCE_19
//!        \b DMA_TRIGGERSOURCE_20
//!        \b DMA_TRIGGERSOURCE_21
//!        \b DMA_TRIGGERSOURCE_22
//!        \b DMA_TRIGGERSOURCE_23
//!        \b DMA_TRIGGERSOURCE_24
//!        \b DMA_TRIGGERSOURCE_25
//!        \b DMA_TRIGGERSOURCE_26
//!        \b DMA_TRIGGERSOURCE_27
//!        \b DMA_TRIGGERSOURCE_28
//!        \b DMA_TRIGGERSOURCE_29
//!        \b DMA_TRIGGERSOURCE_30
//!        \b DMA_TRIGGERSOURCE_31
//!        This parameter is device specific and trigger sources should be
//!        found in device's datasheet.
//!        Modified bits are \b DMAxTSEL of \b DMACTLx register.
//! \param transferUnitSelect is the specified size of transfers.
//!        Valid values are
//!        \b DMA_UNIT_SRCWORD_DSTWORD [Default]
//!        \b DMA_UNIT_SRCBYTE_DSTWORD
//!        \b DMA_UNIT_SRCWORD_DSTBYTE
//!        \b DMA_UNIT_SRCBYTE_DSTBYTE
//!        Modified bits are \b DMADSTBYTE and \b DMASRCBYTE of \b DMAxCTL register.
//! \param triggerTypeSelect is the type of trigger that the trigger signal
//!       needs to be to start a transfer.
//!        Valid values are
//!        \b DMA_TRIGGER_RISINGEDGE [Default]
//!        \b DMA_TRIGGER_HIGH - A trigger would be a high signal from the
//!             trigger source, to be held high through the length of the
//!             transfer(s).
//!        Modified bits are \b DMALEVEL of \b DMAxCTL register.
//!
//! This function initializes the specified DMA channel. Upon successful
//! completion of initializtion of the selected channel the control registers
//! will be cleared and the given variables will be set. Please note, if
//! tranfers have been enabled with the enableTransfers() function, then a call
//! to disableTransfers() is necessary before re-initialization. Also note, that
//! the trigger sources are device dependent and can be found in the device
//! family data sheet. The amount of DMA channels available are also device
//! specific.
//!
//! \return STATUS_SUCCESS or STATUS_FAILURE of the initialization process.
//
//*****************************************************************************
unsigned short DMA_init (unsigned int baseAddress,
    unsigned char channelSelect,
    unsigned int transferModeSelect,
    unsigned int transferSize,
    unsigned char triggerSourceSelect,
    unsigned char transferUnitSelect,
    unsigned char triggerTypeSelect)
{
    ASSERT(channelSelect <= DMA_CHANNEL_7);
    ASSERT(transferModeSelect <= DMA_TRANSFER_REPEATED_BURSTBLOCK);
    ASSERT(triggerSourceSelect <= DMA_TRIGGERSOURCE_31);
    ASSERT(transferUnitSelect <= DMA_SIZE_SRCBYTE_DSTBYTE);
    ASSERT(triggerTypeSelect <= DMA_TRIGGER_HIGH);

    unsigned char retVal = STATUS_SUCCESS;
    unsigned char triggerOffset = (channelSelect >> 4);

    //Reset and Set DMA Control 0 Register
    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) =
        transferModeSelect //Set Transfer Mode
        + transferUnitSelect //Set Transfer Unit Size
        + triggerTypeSelect; //Set Trigger Type

    //Set Transfer Size Amount
    HWREG(baseAddress + channelSelect + OFS_DMA0SZ) = transferSize;

    if (triggerOffset & 0x01){   //Odd Channel
        HWREG(baseAddress + (triggerOffset & 0x0E)) &= 0x00FF; //Reset Trigger Select
        HWREG(baseAddress +
            (triggerOffset & 0x0E)) |= (triggerSourceSelect << 8);
    } else   { //Even Channel
        HWREG(baseAddress + (triggerOffset & 0x0E)) &= 0xFF00; //Reset Trigger Select
        HWREG(baseAddress + (triggerOffset & 0x0E)) |= triggerSourceSelect;
    }

    return ( retVal) ;
}

//*****************************************************************************
//
//! Sets the specified amount of transfers for the selected DMA channel.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to set source address
//!       direction for.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//! \param transferSize is the amount of transfers to complete in a block
//!       transfer mode, as well as how many transfers to complete before the
//!       interrupt flag is set. Valid value is between 1-65535, if 0, no
//!       transfers will occur.
//!        Modified bits are \b DMAxSZ of \b DMAxSZ register.
//!
//! This function sets the specified amount of transfers for the selected DMA
//! channel without having to reinitialize the DMA channel.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_setTransferSize (unsigned int baseAddress,
    unsigned char channelSelect,
    unsigned int transferSize)
{
    //Set Transfer Size Amount
    HWREG(baseAddress + channelSelect + OFS_DMA0SZ) = transferSize;
}

//*****************************************************************************
//
//! Sets source address and the direction that the source address will move
//! after a transfer.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to set source address
//!       direction for.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//! \param srcAddress is the address of where the data will be transfered from.
//!        Modified bits are \b DMAxSA of \b DMAxSA register.
//! \param directionSelect is the specified direction of the source address
//!       after a transfer.
//!        Valid values are
//!        \b DMA_DIRECTION_UNCHANGED
//!        \b DMA_DIRECTION_DECREMENT
//!        \b DMA_DIRECTION_INCREMENT
//!        Modified bits are \b DMASRCINCR of \b DMAxCTL register.
//!
//! This function sets the source address and the direction that the source
//! address will move after a transfer is complete. It may be incremented,
//! decremented, or unchanged.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_setSrcAddress (unsigned int baseAddress,
    unsigned char channelSelect,
    unsigned long srcAddress,
    unsigned int directionSelect)
{
    ASSERT(channelSelect <= DMA_CHANNEL_7);
    ASSERT(directionSelect <= DMA_DIRECTION_INCREMENT);

    //Set the Source Address
    __data16_write_addr((unsigned short)(baseAddress + channelSelect + DMA0SA_O),
        srcAddress);

    //Reset bits before setting them
    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) &= ~(DMASRCINCR_3);
    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) |= directionSelect;
}

//*****************************************************************************
//
//! Sets the destination address and the direction that the destination address
//! will move after a transfer.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to set the destination address
//!       direction for.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//! \param dstAddress is the address of where the data will be transfered to.
//!        Modified bits are \b DMAxDA of \b DMAxDA register.
//! \param directionSelect is the specified direction of the destination address
//!       after a transfer.
//!        Valid values are
//!        \b DMA_DIRECTION_UNCHANGED
//!        \b DMA_DIRECTION_DECREMENT
//!        \b DMA_DIRECTION_INCREMENT
//!        Modified bits are \b DMADSTINCR of \b DMAxCTL register.
//!
//! This function sets the destination address and the direction that the
//! destination address will move after a transfer is complete. It may be
//! incremented, decremented, or unchanged.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_setDstAddress (unsigned int baseAddress,
    unsigned char channelSelect,
    unsigned long dstAddress,
    unsigned int directionSelect)
{
    ASSERT(channelSelect <= DMA_CHANNEL_7);
    ASSERT(directionSelect <= DMA_DIRECTION_INCREMENT);

    //Set the Destination Address
    __data16_write_addr((unsigned short)(baseAddress + channelSelect + DMA0DA_O),
        dstAddress);

    //Reset bits before setting them
    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) &= ~(DMADSTINCR_3);
    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) |= (directionSelect << 2);
}

//*****************************************************************************
//
//! Enables transfers to be triggered.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to enable transfer for.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//!
//! This function enables transfers upon appropriate trigger of the selected
//! trigger source for the selected channel.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_enableTransfers (unsigned int baseAddress,
    unsigned char channelSelect)
{
    ASSERT(channelSelect <= DMA_CHANNEL_7);

    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) |= DMAEN;
}

//*****************************************************************************
//
//! Disables transfers from being triggered.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to disable transfers for.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//!
//! This function disables transfer from being triggered for the selected
//! channel. This function should be called before any re-initialization of the
//! selected DMA channel.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_disableTransfers (unsigned int baseAddress,
    unsigned char channelSelect)
{
    ASSERT(channelSelect <= DMA_CHANNEL_7);

    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) &= ~(DMAEN);
}

//*****************************************************************************
//
//! Starts a transfer if using the default trigger source selected in
//! initialization.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to start transfers for.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//!
//! Thgis functions triggers a transfer of data from source to destination if
//! the trigger source chosen from initialization is the DMA_TRIGGERSOURCE_0.
//! Please note, this function needs to be called for each (repeated-)single
//! tranfser, and when transferAmount of transfers have been complete in
//! (repeated-)block transfers.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_startTransfer (unsigned int baseAddress,
    unsigned char channelSelect)
{
    ASSERT(channelSelect <= DMA_CHANNEL_7);

    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) |= DMAREQ;
}

//*****************************************************************************
//
//! Enables the DMA interrupt for the selected channel.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to enable the interrupt for.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//!
//! Enables the DMA interrupt source.  Only the sources that are enabled can be
//! reflected to the processor interrupt; disabled sources have no effect on the
//! processor.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_enableInterrupt (unsigned int baseAddress,
    unsigned char channelSelect)
{
    ASSERT(channelSelect <= DMA_CHANNEL_7);

    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) &= ~(DMAIFG);
    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) |= DMAIE;
}

//*****************************************************************************
//
//! Disables the DMA interrupt for the selected channel.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to disable the interrupt for.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//!
//! Disables the DMA interrupt source.  Only the sources that are enabled can be
//! reflected to the processor interrupt; disabled sources have no effect on the
//! processor.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_disableInterrupt (unsigned int baseAddress,
    unsigned char channelSelect)
{
    ASSERT(channelSelect <= DMA_CHANNEL_7);

    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) &= ~(DMAIE);
}

//*****************************************************************************
//
//! Returns the status of the interrupt flag for the selected channel.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to return the interrupt flag
//!       status from.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//!
//! Returns the status of the interrupt flag for the selected channel.
//!
//! \return The current interrupt flag status for the selected DMA channel,
//!        DMA_INT_ACTIVE if the interrupt flag is asserted, DMA_INT_INACTIVE
//!        otherwise.
//
//*****************************************************************************
unsigned short DMA_getInterruptStatus (unsigned int baseAddress,
    unsigned char channelSelect)
{
    ASSERT(channelSelect <= DMA_CHANNEL_7);

    if (HWREG(baseAddress + channelSelect + OFS_DMA0CTL) & DMAIFG){
        return ( DMA_INT_ACTIVE) ;
    } else   {
        return ( DMA_INT_INACTIVE) ;
    }
}

//*****************************************************************************
//
//! Clears the interrupt flag for the selected channel.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to clear the interrupt flag
//!       for.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//!
//! This function clears the DMA interrupt flag is cleared, so that it no longer
//! asserts.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_clearInterrupt (unsigned int baseAddress,
    unsigned char channelSelect)
{
    ASSERT(channelSelect <= DMA_CHANNEL_7);

    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) &= ~(DMAIFG);
}

//*****************************************************************************
//
//! Returns the status of the NMIAbort for the selected channel.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to return the status of the
//!       NMI Abort flag for.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//!
//! This function returns the status of the NMI Abort flag for the selected
//! channel. If this flag has been set, it is because a transfer on this channel
//! was aborted due to a interrupt from an NMI.
//!
//! \return The status of the NMI Abort flag, DMA_ABORTED if channel was aborted
//!        by an NMI, DMA_NOTABORTED if not.
//
//*****************************************************************************
unsigned short DMA_NMIAbortStatus (unsigned int baseAddress,
    unsigned char channelSelect)
{
    ASSERT(channelSelect <= DMA_CHANNEL_7);

    if (HWREG(baseAddress + channelSelect + OFS_DMA0CTL) & DMAABORT){
        return ( DMA_ABORTED) ;
    } else   {
        return ( DMA_NOTABORTED) ;
    }
}

//*****************************************************************************
//
//! Clears the status of the NMIAbort to proceed with transfers for the selected
//! channel.
//!
//! \param baseAddress is the base address of the DMA module.
//! \param channelSelect is the specified channel to clear the NMI Abort flag
//!       for.
//!        Valid values are
//!        \b DMA_CHANNEL_0
//!        \b DMA_CHANNEL_1
//!        \b DMA_CHANNEL_2
//!        \b DMA_CHANNEL_3
//!        \b DMA_CHANNEL_4
//!        \b DMA_CHANNEL_5
//!        \b DMA_CHANNEL_6
//!        \b DMA_CHANNEL_7
//!
//! This function clears the status of the NMI Abort flag for the selected
//! channel to allow for transfers on the channel to continue.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_clearNMIAbort (unsigned int baseAddress,
    unsigned char channelSelect)
{
    ASSERT(channelSelect <= DMA_CHANNEL_7);

    HWREG(baseAddress + channelSelect + OFS_DMA0CTL) &= ~(DMAABORT);
}

//*****************************************************************************
//
//! Disables the DMA from stopping the CPU during a Read-Modify-Write Operation
//! to start a transfer.
//!
//! \param baseAddress is the base address of the DMA module.
//!
//! This function allows the CPU to finish any read-modify-write operations it
//! may be in the middle of before transfers of and DMA channel stop the CPU.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_disableTransferDuringReadModifyWrite (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_DMACTL4) |= DMARMWDIS;
}

//*****************************************************************************
//
//! Enables the DMA to stop the CPU during a Read-Modify-Write Operation
//! to start a transfer.
//!
//! \param baseAddress is the base address of the DMA module.
//!
//! This function allows the DMA to stop the CPU in the middle of a
//! read-modify-write operation to transfer data. (default)
//!
//! \return NONE
//
//*****************************************************************************
void DMA_enableTransferDuringReadModifyWrite (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_DMACTL4) &= ~(DMARMWDIS);
}

//*****************************************************************************
//
//! Enables Round Robin prioritzation.
//!
//! \param baseAddress is the base address of the DMA module.
//!
//! This function enables Round Robin Prioritization of DMA channels. In the
//! case of Round Robin Prioritization, the last DMA channel to have transfered
//! data then has the last priority, which comes into play when multiple DMA
//! channels are ready to transfer at the same time.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_enableRoundRobinPriority (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_DMACTL4) |= ROUNDROBIN;
}

//*****************************************************************************
//
//! Disables Round Robin prioritzation.
//!
//! \param baseAddress is the base address of the DMA module.
//!
//! This function disables Round Robin Prioritization, enabling static
//! prioritization of the DMA channels. In static prioritization, the DMA
//! channels are prioritized with the lowest DMA channel index having the
//! highest priority (i.e. DMA Channel 0 has the highest priority). (default)
//!
//! \return NONE
//
//*****************************************************************************
void DMA_disableRoundRobinPriority (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_DMACTL4) &= ~(ROUNDROBIN);
}

//*****************************************************************************
//
//! Enables a NMI to interrupt a DMA transfer.
//!
//! \param baseAddress is the base address of the DMA module.
//!
//! This function allow NMI's to interrupting any DMA transfer currently in
//! progress and stops any future transfers to begin before the NMI is done
//! processing.
//!
//! \return NONE
//
//*****************************************************************************
void DMA_enableNMIAbort (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_DMACTL4) |= ENNMI;
}

//*****************************************************************************
//
//! Disables any NMI from interrupting a DMA transfer.
//!
//! \param baseAddress is the base address of the DMA module.
//!
//! This function disables NMI's from interrupting any DMA transfer currently in
//! progress. (default)
//!
//! \return NONE
//
//*****************************************************************************
void DMA_disableNMIAbort (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_DMACTL4) &= ~(ENNMI);
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
