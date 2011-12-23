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
#ifndef __MSP430WARE_SFR_SYS_H__
#define __MSP430WARE_SFR_SYS_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_SFR__
#define __MSP430_HAS_SYS__


//*****************************************************************************
//
//The following are values that can be passed to SFR_setResetPinPullResistor()
//in the pullResistorSetup parameter.
//
//*****************************************************************************
#define SFR_RESISTORDISABLE         ( !(SYSRSTRE + SYSRSTUP) )
#define SFR_RESISTORENABLE_PULLUP   ( SYSRSTRE + SYSRSTUP )
#define SFR_RESISTORENABLE_PULLDOWN (SYSRSTRE)

//*****************************************************************************
//
//The following are values that can be passed to SFR_setNMIEdge()
//in the edgeDirection parameter.
//
//*****************************************************************************
#define SFR_NMI_RISINGEDGE  ( !(SYSNMIIES) )
#define SFR_NMI_FALLINGEDGE (SYSNMIIES)

//*****************************************************************************
//
//The following are values that can be passed to SFR_setResetNMIPinFunction()
//in the resetPinFunction parameter.
//
//*****************************************************************************
#define SFR_RESETPINFUNC_RESET ( !(SYSNMI) )
#define SFR_RESETPINFUNC_NMI   (SYSNMI)


//*****************************************************************************
//
//The following are values that can be returned by SYS_getBSLEntryIndication()
//
//*****************************************************************************
#define SYS_BSLENTRY_NOTINDICATED (0x0)
#define SYS_BSLENTRY_INDICATED    (0x1)

//*****************************************************************************
//
//The following are values that can be passed to SYS_setRAMAssignedToBSL()
//in the BSLRAMAssignment parameter.
//
//*****************************************************************************
#define SYS_BSLRAMASSIGN_NORAM         ( !(SYSBSLR) )
#define SYS_BSLRAMASSIGN_LOWEST16BYTES (SYSBSLR)

//*****************************************************************************
//
//The following are values that can be passed to SYS_setBSLSize()
//in the BSLSizeSelect parameter.
//
//*****************************************************************************
#define SYS_BSLSIZE_SEG3     ( ~(SYSBSLSIZE0 + SYSBSLSIZE1) )
#define SYS_BSLSIZE_SEGS23   (SYSBSLSIZE0)
#define SYS_BSLSIZE_SEGS123  (SYSBSLSIZE1)
#define SYS_BSLSIZE_SEGS1234 (SYSBSLSIZE0 + SYSBSLSIZE1)

//*****************************************************************************
//
//The following are values that can be passed to SYS_JTAGMailboxInit()
//in the mailboxSizeSelect parameter.
//
//*****************************************************************************
#define SYS_JTAGMBSIZE_16BIT ( !(JMBMODE) )
#define SYS_JTAGMBSIZE_32BIT (JMBMODE)

//*****************************************************************************
//
//The following are values that can be passed to SYS_JTAGMailboxInit()
//in the autoClearInboxFlagSelect parameter.
//
//*****************************************************************************
#define SYS_JTAGINBOX0AUTO_JTAGINBOX1AUTO ( !(JMBCLR0OFF + JMBCLR1OFF) )
#define SYS_JTAGINBOX0AUTO_JTAGINBOX1SW   (JMBCLR1OFF)
#define SYS_JTAGINBOX0SW_JTAGINBOX1AUTO   (JMBCLR0OFF)
#define SYS_JTAGINBOX0SW_JTAGINBOX1SW     (JMBCLR0OFF + JMBCLR1OFF)

//*****************************************************************************
//
//The following are values that can be passed to SYS_getJTAGInboxMessage16Bit()
//in the inboxSelect parameter.
//
//*****************************************************************************
#define SYS_JTAGINBOX_0 (0x0)
#define SYS_JTAGINBOX_1 (0x2)

//*****************************************************************************
//
//The following are values that can be passed to 
//SYS_setJTAGOutgoingMessage16Bit() in the outboxSelect parameter.
//
//*****************************************************************************
#define SYS_JTAGOUTBOX_0 (0x0)
#define SYS_JTAGOUTBOX_1 (0x2)

//******************************************************************************
//
//The following are values that can be passed to 
//SFR_enableInterrupt(), SFR_disableInterrupt(), SFR_getInterruptStatus(),
//SFR_clearInterrupt() in the outboxSelect parameter.
//
//******************************************************************************
#define SFR_JTAG_OUTBOX_INTERRUPT                         JMBOUTIE
#define SFR_JTAG_INBOX_INTERRUPT                          JMBINIE
#define SFR_FLASH_CONTROLLER_ACCESS_VIOLATION_INTERRUPT   ACCVIE
#define SFR_NMI_PIN_INTERRUPT                             NMIIE
#define SFR_VACANT_MEMORY_ACCESS_INTERRUPT                VMAIE
#define SFR_OSCILLATOR_FAULT_INTERRUPT                    OFIE
#define SFR_WATCHDOG_INTERVAL_TIMER_INTERRUPT             WDTIE

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************

extern void SFR_enableInterrupt (unsigned int baseAddress,
    unsigned char interruptMask);

extern void SFR_disableInterrupt (unsigned int baseAddress,
    unsigned char interruptMask);

extern unsigned char SFR_getInterruptStatus (unsigned int baseAddress,
    unsigned char interruptFlagMask);

extern void SFR_clearInterrupt (unsigned int baseAddress,
    unsigned char interruptFlagMask);

extern void SFR_setResetPinPullResistor (unsigned int baseAddress,
    unsigned int pullResistorSetup);

extern void SFR_setNMIEdge (unsigned int baseAddress,
    unsigned int edgeDirection);

extern void SFR_setResetNMIPinFunction (unsigned int baseAddress,
    unsigned char resetPinFunction);

extern void SYS_enableDedicatedJTAGPins (unsigned int baseAddress);

extern unsigned short SYS_getBSLEntryIndication (unsigned int baseAddress);

extern void SYS_enablePMMAccessProtect (unsigned int baseAddress);

extern void SYS_enableRAMBasedInterruptVectors (unsigned int baseAddress);

extern void SYS_disableRAMBasedInterruptVectors (unsigned int baseAddress);

extern void SYS_enableBSLProtect (unsigned int baseAddress);

extern void SYS_disableBSLProtect (unsigned int baseAddress);

extern void SYS_disableBSLMemory (unsigned int baseAddress);

extern void SYS_enableBSLMemory (unsigned int baseAddress);

extern void SYS_setRAMAssignedToBSL (unsigned int baseAddress,
    unsigned char BSLRAMAssignment);

extern void SYS_setBSLSize (unsigned int baseAddress,
    unsigned char BSLSizeSelect);

extern void SYS_JTAGMailboxInit (unsigned int baseAddress,
    unsigned char mailboxSizeSelect,
    unsigned char autoClearInboxFlagSelect);

extern unsigned char SYS_getJTAGMailboxFlagStatus (unsigned int baseAddress,
    unsigned char mailboxFlagMask);

extern void SYS_clearJTAGMailboxFlagStatus (unsigned int baseAddress,
    unsigned char mailboxFlagMask);

extern unsigned int SYS_getJTAGInboxMessage16Bit (unsigned int baseAddress,
    unsigned char inboxSelect);

extern unsigned long SYS_getJTAGInboxMessage32Bit (unsigned int baseAddress);

extern void SYS_setJTAGOutgoingMessage16Bit (unsigned int baseAddress,
    unsigned char outboxSelect,
    unsigned int outgoingMessage);

extern void SYS_setJTAGOutgoingMessage32Bit (unsigned int baseAddress,
    unsigned long outgoingMessage);

#endif
