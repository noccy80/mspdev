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
//ldoPwr.c - Driver for the LDO-PWR Module.
//
//*****************************************************************************
#include "inc/hw_types.h"
#include "driverlib/5xx_6xx/debug.h"
#include "driverlib/5xx_6xx/ldoPwr.h"
#include "msp430xgeneric.h"

//*****************************************************************************

//*****************************************************************************
//
//! Unlocks the configuration registers and enables write access
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! Modified register is \b LDOKEYPID
//!
//! \returns NONE
//
//*****************************************************************************
void LDOPWR_unLockConfiguration ( unsigned int baseAddress )
{
    HWREG(baseAddress + OFS_LDOKEYPID) = 0x9628;
}

//*****************************************************************************
//
//! Locks the configuration registers and disables write access
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! Modified register is \b LDOKEYPID
//!
//! \returns NONE
//
//*****************************************************************************
void LDOPWR_lockConfiguration ( unsigned int baseAddress )
{
    HWREG(baseAddress + OFS_LDOKEYPID) = 0x0000;
}

//*****************************************************************************
//
//! Enables Port U inputs
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! Modified register is \b PUCTL
//!
//! \returns NONE
//
//*****************************************************************************
void LDOPWR_enablePort_U_inputs (unsigned int baseAddress )
{
    HWREGB(baseAddress + OFS_PUCTL_H) |= PUIPE_H;
}

//*****************************************************************************
//
//! Disables Port U inputs
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! Modified register is \b PUCTL
//!
//! \returns NONE
//
//*****************************************************************************
void LDOPWR_disablePort_U_inputs (unsigned int baseAddress )
{
    HWREGB(baseAddress + OFS_PUCTL_H) &= ~PUIPE_H;
}

//*****************************************************************************
//
//! Enables Port U outputs
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! Modified register is \b PUCTL
//!
//! \returns NONE
//
//*****************************************************************************
void LDOPWR_enablePort_U_outputs (unsigned int baseAddress )
{
    HWREGB(baseAddress + OFS_PUCTL_L) |= PUOPE;
}

//*****************************************************************************
//
//! Disables Port U inputs
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! Modified register is \b PUCTL
//!
//! \returns NONE
//
//*****************************************************************************
void LDOPWR_disablePort_U_outputs (unsigned int baseAddress )
{
    HWREGB(baseAddress + OFS_PUCTL_L) &= ~PUOPE;
}

//*****************************************************************************
//
//! Returns PU.1 input data
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! \returns LDOPWR_PORTU_PIN_HIGH or LDOPWR_PORTU_PIN_LOW - PU.1 input data
//
//*****************************************************************************
unsigned char LDOPWR_getPort_U1_inputData (unsigned int baseAddress )
{
    return ((HWREGB(baseAddress + OFS_PUCTL_L) & PUIN1) >> 3 );
}

//*****************************************************************************
//
//! Returns PU.0 input data
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! \returns LDOPWR_PORTU_PIN_HIGH or LDOPWR_PORTU_PIN_LOW - PU.0 input data
//
//*****************************************************************************
unsigned char LDOPWR_getPort_U0_inputData (unsigned int baseAddress )
{
    return ((HWREGB(baseAddress + OFS_PUCTL_L) & PUIN0) >> 2 );
}

//*****************************************************************************
//
//! Returns PU.1 output data
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! \returns LDOPWR_PORTU_PIN_HIGH or LDOPWR_PORTU_PIN_LOW - PU.1 output data
//
//*****************************************************************************
unsigned char LDOPWR_getPort_U1_outputData (unsigned int baseAddress )
{
    return ((HWREGB(baseAddress + OFS_PUCTL_L) & PUOUT1) >> 1 );
}

//*****************************************************************************
//
//! Returns PU.0 output data
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! \returns LDOPWR_PORTU_PIN_HIGH or LDOPWR_PORTU_PIN_LOW - PU.0 output data
//
//*****************************************************************************
unsigned char LDOPWR_getPort_U0_outputData (unsigned int baseAddress )
{
    return (HWREGB(baseAddress + OFS_PUCTL_L) & PUOUT0);
}

//*****************************************************************************
//
//! Sets PU.1 output data
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//! \param value.
//!         Valid values are
//!  \b LDOPWR_PORTU_PIN_HIGH
//!  \b LDOPWR_PORTU_PIN_LOW
//!
//! Modified register is \b PUCTL
//!
//! \returns None
//
//*****************************************************************************
void LDOPWR_setPort_U1_outputData (unsigned int baseAddress,
    unsigned char value
    )
{
    if (LDOPWR_PORTU_PIN_HIGH == value){
        HWREGB(baseAddress + OFS_PUCTL_L) |= PUOUT1;
    } else   {
        HWREGB(baseAddress + OFS_PUCTL_L) &= ~PUOUT1;
    }
}

//*****************************************************************************
//
//! Sets PU.0 output data
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//! \param value
//! Valid values are
//!     \b LDOPWR_PORTU_PIN_HIGH
//!     \b LDOPWR_PORTU_PIN_LOW
//!
//! Modified register is \b PUCTL
//!
//! \returns None
//
//*****************************************************************************
void LDOPWR_setPort_U0_outputData (unsigned int baseAddress,
    unsigned char value
    )
{
    if (LDOPWR_PORTU_PIN_HIGH == value){
        HWREGB(baseAddress + OFS_PUCTL_L) |= PUOUT0;
    } else   {
        HWREGB(baseAddress + OFS_PUCTL_L) &= ~PUOUT0;
    }
}

//*****************************************************************************
//
//! Toggles PU.1 output data
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! Modified register is PUCTL
//!
//! \returns None
//
//*****************************************************************************
void LDOPWR_togglePort_U1_outputData (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_PUCTL_L) ^= PUOUT1;
}

//*****************************************************************************
//
//! Toggles PU.0 output data
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! Modified register is \b PUCTL
//!
//! \returns None
//
//*****************************************************************************
void LDOPWR_togglePort_U0_outputData (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_PUCTL_L) ^= PUOUT0;
}

//*****************************************************************************
//
//! Enables LDO-PWR module interrupts
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//! \param mask is the logical OR of
//!        \b LDOPWR_LDOI_VOLTAGE_GOING_OFF_INTERRUPT,
//!        \b LDOPWR_LDOI_VOLTAGE_COMING_ON_INTERRUPT or
//!        \b LDOPWR_LDO_OVERLOAD_INDICATION_INTERRUPT
//!
//! Modified register is \b LDOPWRCTL
//!
//! \returns None
//
//*****************************************************************************
void LDOPWR_enableInterrupt (unsigned int baseAddress,
    unsigned int mask
    )
{
    ASSERT(0x00 == (mask & ~(LDOPWR_LDOI_VOLTAGE_GOING_OFF_INTERRUPT +
                             LDOPWR_LDOI_VOLTAGE_COMING_ON_INTERRUPT +
                             LDOPWR_LDO_OVERLOAD_INDICATION_INTERRUPT
                             )
                    )
        );
    HWREGB(baseAddress + OFS_LDOPWRCTL_L) &=  ~mask;
    HWREGB(baseAddress + OFS_LDOPWRCTL_H) |= mask;
}

//*****************************************************************************
//
//! Disables LDO-PWR module interrupts
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//! \param mask is the logical OR of
//!     \b LDOPWR_LDOI_VOLTAGE_GOING_OFF_INTERRUPT,
//!     \b LDOPWR_LDOI_VOLTAGE_COMING_ON_INTERRUPT,
//!        LDOPWR_LDO_OVERLOAD_INDICATION_INTERRUPT
//!
//! Modified register is LDOPWRCTL
//!
//! \returns None
//
//*****************************************************************************
void LDOPWR_disableInterrupt (unsigned int baseAddress,
    unsigned int mask
    )
{
    ASSERT(0x00 == (mask & ~(LDOPWR_LDOI_VOLTAGE_GOING_OFF_INTERRUPT +
                             LDOPWR_LDOI_VOLTAGE_COMING_ON_INTERRUPT +
                             LDOPWR_LDO_OVERLOAD_INDICATION_INTERRUPT
                             )
                    )
        );
    HWREGB(baseAddress + OFS_LDOPWRCTL_H) &= ~mask;
}

//*****************************************************************************
//
//! Enables LDO-PWR module
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! Modified register is \b LDOPWRCTL
//!
//! \returns None
//
//*****************************************************************************
void LDOPWR_enable (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_LDOPWRCTL_H) |= LDOOEN_H;
}

//*****************************************************************************
//
//! Disables LDO-PWR module
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! Modified register is \b LDOPWRCTL
//!
//! \returns None
//
//*****************************************************************************
void LDOPWR_disable (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_LDOPWRCTL_H) &= ~LDOOEN_H;
}

//*****************************************************************************
//
//! Returns the interrupt status of LDO-PWR module interrupts
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//! \param mask is the logical OR of
//!        \b LDOPWR_LDOI_VOLTAGE_GOING_OFF_INTERRUPT,
//!        \b LDOPWR_LDOI_VOLTAGE_COMING_ON_INTERRUPT or
//!        \b LDOPWR_LDO_OVERLOAD_INDICATION_INTERRUPT
//!
//! \returns unsigned char - masked interrupt flags
//
//*****************************************************************************
unsigned char LDOPWR_getInterruptStatus (unsigned int baseAddress,
    unsigned int mask
    )
{
    ASSERT(0x00 == (mask & ~(LDOPWR_LDOI_VOLTAGE_GOING_OFF_INTERRUPT +
                             LDOPWR_LDOI_VOLTAGE_COMING_ON_INTERRUPT +
                             LDOPWR_LDO_OVERLOAD_INDICATION_INTERRUPT
                             )
                    )
        );
    return (HWREGB(baseAddress + OFS_LDOPWRCTL_L) & mask);
}

//*****************************************************************************
//
//! Clears the interrupt status of LDO-PWR module interrupts
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//! \param mask is the logical OR of
//!        \b LDOPWR_LDOI_VOLTAGE_GOING_OFF_INTERRUPT,
//!        \b LDOPWR_LDOI_VOLTAGE_COMING_ON_INTERRUPT,
//!        \b LDOPWR_LDO_OVERLOAD_INDICATION_INTERRUPT
//!
//! Modified register is \b LDOPWRCTL
//!
//! \returns None
//
//*****************************************************************************
void LDOPWR_clearInterruptStatus (unsigned int baseAddress,
    unsigned int mask
    )
{
    ASSERT(0x00 == (mask & ~(LDOPWR_LDOI_VOLTAGE_GOING_OFF_INTERRUPT +
                             LDOPWR_LDOI_VOLTAGE_COMING_ON_INTERRUPT +
                             LDOPWR_LDO_OVERLOAD_INDICATION_INTERRUPT
                             )
                    )
        );
    HWREGB(baseAddress + OFS_LDOPWRCTL_L) &=  ~mask;
}

//*****************************************************************************
//
//! Returns if the the LDOI is valid and within bounds
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! \returns unsigned char - Valid values are
//!         \b LDOPWR_LDO_INPUT_VALID
//!         \b LDOPWR_LDO_INPUT_INVALID
//
//*****************************************************************************
unsigned char LDOPWR_isLDOInputValid (unsigned int baseAddress)
{
    return (HWREGB(baseAddress + OFS_LDOPWRCTL_L) & LDOBGVBV);
}

//*****************************************************************************
//
//! Enables the LDO overload auto-off
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! Modified register is \b LDOPWRCTL
//!
//! \returns None
//
//*****************************************************************************
void LDOPWR_enableOverloadAutoOff (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_LDOPWRCTL_L) |= OVLAOFF_L;
}

//*****************************************************************************
//
//! Disables the LDO overload auto-off
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! Modified register is \b LDOPWRCTL
//!
//! \returns None
//
//*****************************************************************************
void LDOPWR_disableOverloadAutoOff (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_LDOPWRCTL_L) &= ~OVLAOFF_L;
}

//*****************************************************************************
//
//! Returns if the LDOI overload auto-off is enabled or disabled
//!
//! \param baseAddress is the base address of the LDO-PWR module.
//!
//! \returns unsigned char - Valid values are
//!         \b LDOPWR_AUTOOFF_ENABLED
//!         \b LDOPWR_AUTOOFF_DISABLED
//
//*****************************************************************************
unsigned char LDOPWR_getOverloadAutoOffStatus (unsigned int baseAddress)
{
    return (HWREGB(baseAddress + OFS_LDOPWRCTL_L) & OVLAOFF_L);
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
