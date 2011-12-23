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
//sfr_sys.c - Driver for the SFR_SYS Module.
//
//*****************************************************************************
#include "driverlib/5xx_6xx/sfr_sys.h"
#include "inc/hw_types.h"
#include "msp430xgeneric.h"
#include "driverlib/5xx_6xx/debug.h"

//*****************************************************************************
//
//! Enables selected SFR interrupt sources.
//!
//! \param baseAddress is the Base Address of the SFR Module.
//! \param interruptMask is the bit mask of interrupts that will be enabled.
//!        Mask Value is the logical OR of any of the following
//!        \b SFR_JTAG_OUTBOX_INTERRUPT - JTAG outbox interrupt enable
//!        \b SFR_JTAG_INBOX_INTERRUPT- JTAG inbox interrupt enable
//!        \b SFR_FLASH_CONTROLLER_ACCESS_VIOLATION_INTERRUPT - Flash 
//!               controller access violation interrupt enable
//!        \b SFR_NMI_PIN_INTERRUPT - NMI pin interrupt enable, 
//!               if NMI function is chosen
//!        \b SFR_VACANT_MEMORY_ACCESS_INTERRUPT - Vacant memory access 
//!               interrupt enable
//!        \b SFR_OSCILLATOR_FAULT_INTERRUPT - Oscillator fault interrupt 
//!               enable
//!        \b SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT - Watchdog interval 
//!               timer interrupt enable
//!
//! This function enables the selected SFR interrupt sources.  Only the sources
//! that are enabled can be reflected to the processor interrupt; disabled
//! sources have no effect on the processor.
//!
//! \return NONE
//
//*****************************************************************************
void SFR_enableInterrupt (unsigned int baseAddress,
    unsigned char interruptMask)
{
    HWREGB(baseAddress + OFS_SFRIFG1_L) &= ~(interruptMask);
    HWREGB(baseAddress + OFS_SFRIE1_L) |= interruptMask;
}

//*****************************************************************************
//
//! Disables selected SFR interrupt sources.
//!
//! \param baseAddress is the Base Address of the SFR Module.
//! \param interruptMask is the bit mask of interrupts that will be disabled.
//!        Mask Value is the logical OR of any of the following
//!        \b SFR_JTAG_OUTBOX_INTERRUPT - JTAG outbox interrupt enable
//!        \b SFR_JTAG_INBOX_INTERRUPT- JTAG inbox interrupt enable
//!        \b SFR_FLASH_CONTROLLER_ACCESS_VIOLATION_INTERRUPT - Flash 
//!               controller access violation interrupt enable
//!        \b SFR_NMI_PIN_INTERRUPT - NMI pin interrupt enable, 
//!               if NMI function is chosen
//!        \b SFR_VACANT_MEMORY_ACCESS_INTERRUPT - Vacant memory access 
//!               interrupt enable
//!        \b SFR_OSCILLATOR_FAULT_INTERRUPT - Oscillator fault interrupt 
//!               enable
//!        \b SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT - Watchdog interval 
//!               timer interrupt enable
//!
//! This function disables the selected SFR interrupt sources.  Only the sources
//! that are enabled can be reflected to the processor interrupt; disabled
//! sources have no effect on the processor.
//!
//! \return NONE
//
//*****************************************************************************
void SFR_disableInterrupt (unsigned int baseAddress,
    unsigned char interruptMask)
{
    HWREGB(baseAddress + OFS_SFRIE1_L) &= ~(interruptMask);
}

//*****************************************************************************
//
//! Returns the status of the selected SFR interrupt flags.
//!
//! \param baseAddress is the Base Address of the SFR Module.
//! \param interruptFlagMask is the bit mask of interrupt flags that the status
//!       of should be returned.
//!        Mask Value is the logical OR of any of the following
//!        \b SFR_JTAG_OUTBOX_INTERRUPT - JTAG outbox interrupt flag
//!        \b SFR_JTAG_INBOX_INTERRUPT- JTAG inbox interrupt flag
//!        \b SFR_FLASH_CONTROLLER_ACCESS_VIOLATION_INTERRUPT - Flash 
//!               controller access violation interrupt flag
//!        \b SFR_NMI_PIN_INTERRUPT - NMI pin interrupt flag
//!        \b SFR_VACANT_MEMORY_ACCESS_INTERRUPT - Vacant memory access 
//!               interrupt flag
//!        \b SFR_OSCILLATOR_FAULT_INTERRUPT - Oscillator fault interrupt 
//!               flag
//!        \b SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT - Watchdog interval 
//!               timer interrupt flag
//!
//! This function returns the status of the selected SFR interrupt flags in a
//! bit mask format matching that passed into the interruptFlagMask parameter.
//!
//! \return A bit mask of the status of the selected interrupt flags.
//
//*****************************************************************************
unsigned char SFR_getInterruptStatus (unsigned int baseAddress,
    unsigned char interruptFlagMask)
{
    return ( HWREGB(baseAddress + OFS_SFRIFG1_L) & interruptFlagMask );
}

//*****************************************************************************
//
//! Clears the selected SFR interrupt flags.
//!
//! \param baseAddress is the Base Address of the SFR Module.
//! \param interruptFlagMask is the bit mask of interrupt flags that will be
//!       cleared.
//!        Mask Value is the logical OR of any of the following
//!        \b SFR_JTAG_OUTBOX_INTERRUPT - JTAG outbox interrupt flag
//!        \b SFR_JTAG_INBOX_INTERRUPT- JTAG inbox interrupt flag
//!        \b SFR_FLASH_CONTROLLER_ACCESS_VIOLATION_INTERRUPT - Flash 
//!               controller access violation interrupt flag
//!        \b SFR_NMI_PIN_INTERRUPT - NMI pin interrupt flag
//!        \b SFR_VACANT_MEMORY_ACCESS_INTERRUPT - Vacant memory access 
//!               interrupt flag
//!        \b SFR_OSCILLATOR_FAULT_INTERRUPT - Oscillator fault interrupt 
//!               flag
//!        \b SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT - Watchdog interval 
//!               timer interrupt flag
//!
//!
//! This function clears the status of the selected SFR interrupt flags.
//!
//! \return NONE
//
//*****************************************************************************
void SFR_clearInterrupt (unsigned int baseAddress,
    unsigned char interruptFlagMask)
{
    HWREGB(baseAddress + OFS_SFRIFG1_L) &= ~(interruptFlagMask);
}

//*****************************************************************************
//
//! Sets the pull-up/down resistor on the ~RST/NMI pin.
//!
//! \param baseAddress is the Base Address of the SFR Module.
//! \param pullResistorSetup is the selection of how the pull-up/down resistor
//!       on the ~RST/NMI pin should be setup or disabled.
//!        Valid values are
//!        \b SFR_RESISTORDISABLE
//!        \b SFR_RESISTORENABLE_PULLUP [Default]
//!        \b SFR_RESISTORENABLE_PULLDOWN
//!        Modified bits are \b SYSRSTRE and \b SYSRSTUP of \b SFRRPCR register.
//!
//! This function sets the pull-up/down resistors on the ~RST/NMI pin to the
//! settings from the pullResistorSetup parameter.
//!
//! \return NONE
//
//*****************************************************************************
void SFR_setResetPinPullResistor (unsigned int baseAddress,
    unsigned int pullResistorSetup)
{
    HWREGB(baseAddress + OFS_SFRRPCR_L) &= ~(SYSRSTRE + SYSRSTUP);
    HWREGB(baseAddress + OFS_SFRRPCR_L) |= pullResistorSetup;
}

//*****************************************************************************
//
//! Sets the edge direction that will assert an NMI from a signal on the
//! ~RST/NMI pin if NMI function is active.
//!
//! \param baseAddress is the Base Address of the SFR Module.
//! \param edgeDirection is the direction that the signal on the ~RST/NMI pin
//!       should go to signal an interrupt, if enabled.
//!        Valid values are
//!        \b SFR_NMI_RISINGEDGE [Default]
//!        \b SFR_NMI_FALLINGEDGE
//!        Modified bits are \b SYSNMIIES of \b SFRRPCR register.
//!
//! This function sets the edge direction that will assert an NMI from a signal
//! on the ~RST/NMI pin if the NMI function is active. To activate the NMI
//! function of the ~RST/NMI use the SFR_setResetNMIPinFunction() passing
//! SFR_RESETPINFUNC_NMI into the resetPinFunction parameter.
//!
//! \return NONE
//
//*****************************************************************************
void SFR_setNMIEdge (unsigned int baseAddress,
    unsigned int edgeDirection)
{
    HWREGB(baseAddress + OFS_SFRRPCR_L) &= ~(SYSNMIIES);
    HWREGB(baseAddress + OFS_SFRRPCR_L) |= edgeDirection;
}

//*****************************************************************************
//
//! Sets the function of the ~RST/NMI pin.
//!
//! \param baseAddress is the Base Address of the SFR Module.
//! \param resetPinFunction is the function that the ~RST/NMI pin should take on.
//!        Valid values are
//!        \b SFR_RESETPINFUNC_RESET [Default]
//!        \b SFR_RESETPINFUNC_NMI
//!        Modified bits are \b SYSNMI of \b SFRRPCR register.
//!
//! This function sets the functionality of the ~RST/NMI pin, whether in reset
//! mode which will assert a reset if a low signal is observed on that pin, or
//! an NMI which will assert an interrupt from an edge of the signal dependent
//! on the setting of the edgeDirection parameter in SFR_setNMIEdge().
//!
//! \return NONE
//
//*****************************************************************************
void SFR_setResetNMIPinFunction (unsigned int baseAddress,
    unsigned char resetPinFunction)
{
    HWREGB(baseAddress + OFS_SFRRPCR_L) &= ~(SYSNMI);
    HWREGB(baseAddress + OFS_SFRRPCR_L) |= resetPinFunction;
}

//*****************************************************************************
//
//! Sets the JTAG pins to be exclusively for JTAG until a BOR occurs.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//!
//! This function sets the JTAG pins to be exclusively used for the JTAG, and
//! not to be shared with the GPIO pins. This setting can only be cleared when a
//! BOR occurs.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_enableDedicatedJTAGPins (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_SYSCTL_L) |= SYSJTAGPIN;
}

//*****************************************************************************
//
//! Returns the indication of a BSL entry sequence from the Spy-Bi-Wire.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//!
//! This function returns the indication of a BSL entry sequence from the
//! Spy-Bi-Wire.
//!
//! \return SYS_BSLENTRY_INDICATED if a BSL entry sequence was detected,
//!        otherwise SYS_BSLENTRY_NOTINDICATED
//
//*****************************************************************************
unsigned short SYS_getBSLEntryIndication (unsigned int baseAddress)
{
    if ( HWREGB(baseAddress + OFS_SYSCTL_L) | SYSBSLIND){
        return ( SYS_BSLENTRY_INDICATED) ;
    } else   {
        return ( SYS_BSLENTRY_NOTINDICATED) ;
    }
}

//*****************************************************************************
//
//! Enables PMM Access Protection.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//!
//! This function enables the PMM Access Protection, which will lock any changes
//! on the PMM control registers until a BOR occurs.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_enablePMMAccessProtect (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_SYSCTL_L) |= SYSPMMPE;
}

//*****************************************************************************
//
//! Enables RAM-based Interrupt Vectors.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//!
//! This function enables RAM-base Interrupt Vectors, which means that interrupt
//! vectors are generated with the end address at the top of RAM, instead of the
//! top of the lower 64kB of flash.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_enableRAMBasedInterruptVectors (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_SYSCTL_L) |= SYSRIVECT;
}

//*****************************************************************************
//
//! Disables RAM-based Interrupt Vectors.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//!
//! This function disables the interrupt vectors from being generated at the top
//! of the RAM.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_disableRAMBasedInterruptVectors (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_SYSCTL_L) &= ~(SYSRIVECT);
}

//*****************************************************************************
//
//! Enables BSL memory protection.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//!
//! This function enables protection on the BSL memory, which prevents any
//! reading, programing, or erasing of the BSL memory.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_enableBSLProtect (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_SYSBSLC) |= SYSBSLPE;
}

//*****************************************************************************
//
//! Disables BSL memory protection.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//!
//! This function disables protection on the BSL memory.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_disableBSLProtect (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_SYSBSLC) &= ~(SYSBSLPE);
}

//*****************************************************************************
//
//! Enables BSL memory.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//!
//! This function enables BSL memory, which allows BSL memory to be addressed
//!
//! \return NONE
//
//*****************************************************************************
void SYS_enableBSLMemory (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_SYSBSLC) &= ~(SYSBSLOFF);
}

//*****************************************************************************
//
//! Disables BSL memory.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//!
//! This function disables BSL memory, which makes BSL memory act like vacant
//! memory.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_disableBSLMemory (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_SYSBSLC) |= SYSBSLOFF;
}

//*****************************************************************************
//
//! Sets RAM assignment to BSL area.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//! \param BSLRAMAssignment is the selection of if the BSL should be placed in
//!       RAM or not.
//!        Valid values are
//!        \b SYS_BSLRAMASSIGN_NORAM [Default]
//!        \b SYS_BSLRAMASSIGN_LOWEST16BYTES
//!        Modified bits are \b SYSBSLR of \b SYSBSLC register
//!
//! This function allows RAM to be assigned to BSL, based on the selection of
//! the BSLRAMAssignment parameter.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_setRAMAssignedToBSL (unsigned int baseAddress,
    unsigned char BSLRAMAssignment)
{
    HWREGB(baseAddress + OFS_SYSBSLC_L) &= ~(SYSBSLR);
    HWREGB(baseAddress + OFS_SYSBSLC_L) &= BSLRAMAssignment;
}

//*****************************************************************************
//
//! Sets the size of the BSL in Flash.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//! \param BSLSizeSelect is the amount of segments the BSL should take.
//!        Valid values are
//!        \b SYS_BSLSIZE_SEG3
//!        \b SYS_BSLSIZE_SEGS23
//!        \b SYS_BSLSIZE_SEGS123
//!        \b SYS_BSLSIZE_SEGS1234 [Default]
//!        Modified bits are \b SYSBSLSIZE of \b SYSBSLC register.
//!
//! This function sets the size of the BSL in Flash memory.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_setBSLSize (unsigned int baseAddress,
    unsigned char BSLSizeSelect)
{
    HWREGB(baseAddress + OFS_SYSBSLC_L) &= ~(SYSBSLSIZE0 + SYSBSLSIZE1);
    HWREGB(baseAddress + OFS_SYSBSLC_L) |= BSLSizeSelect;
}

//*****************************************************************************
//
//! Initializes JTAG Mailbox with selected properties.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//! \param mailboxSizeSelect is the size of the JTAG Mailboxes, whether 16- or
//!       32-bits.
//!        Valid values are
//!        \b SYS_JTAGMBSIZE_16BIT - the JTAG messages will take up only one
//!             JTAG mailbox (i.e. an outgoing message will take up only 1
//!             outbox of the JTAG mailboxes) [Default]
//!        \b SYS_JTAGMBSIZE_32BIT - the JTAG messages will be contained within
//!             both JTAG mailboxes (i.e. an outgoing message will take up both
//!             Outboxes of the JTAG mailboxes)
//!        Modified bits are \b JMBMODE of \b SYSJMBC register.
//! \param autoClearInboxFlagSelect decides how the JTAG inbox flags should be
//!       cleared, whether automatically after the corresponding outbox has been
//!       written to, or manually by software.
//!        Valid values are
//!        \b SYS_JTAGINBOX0AUTO_JTAGINBOX1AUTO - both JTAG inbox flags will be
//!             reset automatically when the corresponding inbox is read from.
//!             [Default]
//!        \b SYS_JTAGINBOX0AUTO_JTAGINBOX1SW - only JTAG inbox 0 flag is reset
//!             automatically, while JTAG inbox 1 is reset with the
//!             SYS_clearJTAGMailboxFlagStatus() function
//!        \b SYS_JTAGINBOX0SW_JTAGINBOX1AUTO - only JTAG inbox 1 flag is reset
//!             automatically, while JTAG inbox 0 is reset with the
//!             SYS_clearJTAGMailboxFlagStatus() function
//!        \b SYS_JTAGINBOX0SW_JTAGINBOX1SW - both JTAG inbox flags will need to
//!             be reset manually by the SYS_clearJTAGMailboxFlagStatus() function
//!        Modified bits are \b JMBCLR1OFF and \b JMBCLR0OFF of \b SYSJMBC
//!        register.
//!
//! This function sets the specified settings for the JTAG Mailbox system. The
//! settings that can be set are the size of the JTAG messages, and the auto-
//! clearing of the inbox flags. If the inbox flags are set to auto-clear, then
//! the inbox flags will be cleared upon reading of the inbox message buffer,
//! otherwise they will have to be reset by software using the
//! SYS_clearJTAGMailboxFlagStatus() function.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_JTAGMailboxInit (unsigned int baseAddress,
    unsigned char mailboxSizeSelect,
    unsigned char autoClearInboxFlagSelect)
{
    HWREGB(baseAddress + OFS_SYSJMBC_L) &= ~(JMBCLR1OFF + JMBCLR0OFF + JMBMODE);
    HWREGB(baseAddress + OFS_SYSJMBC_L) |=
        mailboxSizeSelect + autoClearInboxFlagSelect;
}

//*****************************************************************************
//
//! Returns the status of the selected JTAG Mailbox flags.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//! \param mailboxFlagMask is the bit mask of JTAG mailbox flags that the status
//!       of should be returned.
//!        Mask Value is the logical OR of any of the following
//!        \b JMBOUT1FG - flag for JTAG outbox 1
//!        \b JMBOUT0FG - flag for JTAG outbox 0
//!        \b JMBIN1FG - flag for JTAG inbox 1
//!        \b JMBIN0FG - flag for JTAG inbox 0
//!
//! This function will return the status of the selected JTAG Mailbox flags
//! in bit mask format matching that passed into the mailboxFlagMask parameter.
//!
//! \return A bit mask of the status of the selected mailbox flags.
//
//*****************************************************************************
unsigned char SYS_getJTAGMailboxFlagStatus (unsigned int baseAddress,
    unsigned char mailboxFlagMask)
{
    return ( HWREGB(baseAddress + OFS_SYSJMBC_L) | mailboxFlagMask);
}

//*****************************************************************************
//
//! Clears the status of the selected JTAG Mailbox flags.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//! \param mailboxFlagMask is the bit mask of JTAG mailbox flags that the status
//!       of should be cleared.
//!        Mask Value is the logical OR of any of the following
//!        \b JMBOUT1FG - flag for JTAG outbox 1
//!        \b JMBOUT0FG - flag for JTAG outbox 0
//!        \b JMBIN1FG - flag for JTAG inbox 1
//!        \b JMBIN0FG - flag for JTAG inbox 0
//!
//! This function clears the selected JTAG Mailbox flags.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_clearJTAGMailboxFlagStatus (unsigned int baseAddress,
    unsigned char mailboxFlagMask)
{
    HWREGB(baseAddress + OFS_SYSJMBC_L) &= ~(mailboxFlagMask);
}

//*****************************************************************************
//
//! Returns the contents of the selected JTAG Inbox in a 16 bit format.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//! \param inboxSelect is the chosen JTAG inbox that the contents of should be
//!       returned
//!        Valid values are
//!        \b SYS_JTAGINBOX_0 - return contents of JTAG inbox 0
//!        \b SYS_JTAGINBOX_1 - return contents of JTAG inbox 1
//!
//! This function returns the message contents of the selected JTAG inbox. If
//! the auto clear settings for the Inbox flags were set, then using this
//! function will automatically clear the corresponding JTAG inbox flag.
//!
//! \return The contents of the selected JTAG inbox in a 16 bit format.
//
//*****************************************************************************
unsigned int SYS_getJTAGInboxMessage16Bit (unsigned int baseAddress,
    unsigned char inboxSelect)
{
    return ( HWREG(baseAddress + OFS_SYSJMBI0 + inboxSelect) );
}

//*****************************************************************************
//
//! Returns the contents of JTAG Inboxes in a 32 bit format.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//!
//! This function returns the message contents of both JTAG inboxes in a 32 bit
//! format. This function should be used if 32-bit messaging has been set in the
//! SYS_JTAGMailboxInit() function.  If the auto clear settings for the Inbox
//! flags were set, then using this function will automatically clear both JTAG
//! inbox flags.
//!
//! \return The contents of both JTAG messages in a 32 bit format.
//
//*****************************************************************************
unsigned long SYS_getJTAGInboxMessage32Bit (unsigned int baseAddress)
{
    unsigned long JTAGInboxMessageLow = HWREG(baseAddress + OFS_SYSJMBI0);
    unsigned long JTAGInboxMessageHigh = HWREG(baseAddress + OFS_SYSJMBI1);

    return ( (JTAGInboxMessageHigh << 16) + JTAGInboxMessageLow );
}

//*****************************************************************************
//
//! Sets a 16 bit outgoing message in to the selected JTAG Outbox.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//! \param outboxSelect is the chosen JTAG outbox that the message should be
//!       set it.
//!        Valid values are
//!        \b SYS_JTAGOUTBOX_0 - set the contents of JTAG outbox 0
//!        \b SYS_JTAGOUTBOX_1 - set the contents of JTAG outbox 1
//! \param outgoingMessage is the message to send to the JTAG.
//!        Modified bits are \b MSGHI and \b MSGLO of \b SYSJMBOx register.
//!
//! This function sets the outgoing message in the selected JTAG outbox. The
//! corresponding JTAG outbox flag is cleared after this function, and set after
//! the JTAG has read the message.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_setJTAGOutgoingMessage16Bit (unsigned int baseAddress,
    unsigned char outboxSelect,
    unsigned int outgoingMessage)
{
    HWREG(baseAddress + OFS_SYSJMBO0 + outboxSelect) = outgoingMessage;
}

//*****************************************************************************
//
//! Sets a 32 bit message in to both JTAG Outboxes.
//!
//! \param baseAddress is the Base Address of the SYS Module.
//! \param outgoingMessage is the message to send to the JTAG.
//!        Modified bits are \b MSGHI and \b MSGLO of \b SYSJMBO0 and
//!        \b SYSJMBO1 registers.
//!
//! This function sets the 32-bit outgoing message in both JTAG outboxes. The
//! JTAG outbox flags are cleared after this function, and set after the JTAG
//! has read the message.
//!
//! \return NONE
//
//*****************************************************************************
void SYS_setJTAGOutgoingMessage32Bit (unsigned int baseAddress,
    unsigned long outgoingMessage)
{
    HWREG(baseAddress + OFS_SYSJMBO0) = (outgoingMessage);
    HWREG(baseAddress + OFS_SYSJMBO1) = (outgoingMessage >> 16);
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************

