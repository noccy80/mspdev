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
//mpy.c - Driver for the MPY32 Module.
//
//*****************************************************************************
#include "driverlib/5xx_6xx/mpy32.h"
#include "inc/hw_types.h"
#include "msp430xgeneric.h"
#include "driverlib/5xx_6xx/debug.h"

//*****************************************************************************
//
//! Sets the write delay setting for the MPY32 module.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//! \param writeDelaySelect delays the write to any MPY32 register until the
//!       selected bit size of result has been written.
//!        Valid values are
//!        \b MPY32_WRITEDELAY_OFF - writes are not delayed [Default]
//!        \b MPY32_WRITEDELAY_32BIT - writes are delayed until a 32-bit result
//!             is available in the result registers
//!        \b MPY32_WRITEDELAY_64BIT - writes are delayed until a 64-bit result
//!             is available in the result registers
//!        Modified bits are \b MPYDLY32 and \b MPYDLYWRTEN of \b MPY32CTL0 register.
//!
//! This function sets up a write delay to the MPY module's registers, which
//! holds any writes to the registers until all calculations are complete. There
//! are two different settings, one which waits for 32-bit results to be ready,
//! and one which waits for 64-bit results to be ready. This prevents
//! unpredicatble results if registers are changed before the results are ready.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_setWriteDelay (unsigned int baseAddress,
    unsigned int writeDelaySelect)
{
    HWREG(baseAddress + OFS_MPY32CTL0) &= ~(MPYDLY32 + MPYDLYWRTEN);
    HWREG(baseAddress + OFS_MPY32CTL0) |= writeDelaySelect;
}

//*****************************************************************************
//
//! Enables Saturation Mode.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//!
//! This function enables saturation mode. When this is enabled, the result read
//! out from the MPY result registers is converted to the most-positive number
//! in the case of an overflow, or the most-negative number in the case of an
//! underflow. Please note, that the raw value in the registers does not reflect
//! the result returned, and if the saturation mode is disabled, then the raw
//! value of the registers will be returned instead.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_setSaturationMode (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_MPY32CTL0_L) |= MPYSAT;
}

//*****************************************************************************
//
//! Disables Saturation Mode.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//!
//! This function disables saturation mode, which allows the raw result of the
//! MPY result registers to be returned.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_resetSaturationMode (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_MPY32CTL0_L) &= ~(MPYSAT);
}

//*****************************************************************************
//
//! Enables Fraction Mode.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//!
//! This function enables fraction mode.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_setFractionMode (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_MPY32CTL0_L) |= MPYFRAC;
}

//*****************************************************************************
//
//! Disables Fraction Mode.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//!
//! This function disables fraction mode.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_resetFractionMode (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_MPY32CTL0_L) &= ~(MPYFRAC);
}

//*****************************************************************************
//
//! Sets an 8-bit value into operand 1.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//! \param multiplicationType is the type of multiplication to perform once the
//!       second operand is set.
//!        Valid values are
//!        \b MPY_MULTIPLY_UNSIGNED
//!        \b MPY_MULTIPLY_SIGNED
//!        \b MPY_MULTIPLYACCUMULATE_UNSIGNED
//!        \b MPY_MULTIPLEACCUMULATE_SIGNED
//! \param operand is the 8-bit value to load into the 1st operand.
//!
//! This function sets the first operand for multiplication and determines what
//! type of operation should be performed. Once the second operand is set, then
//! the operation will begin.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_setOperandOne8Bit (unsigned int baseAddress,
    unsigned char multiplicationType,
    unsigned char operand)
{
    HWREGB(baseAddress + OFS_MPY + multiplicationType) = operand;
}

//*****************************************************************************
//
//! Sets an 16-bit value into operand 1.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//! \param multiplicationType is the type of multiplication to perform once the
//!       second operand is set.
//!        Valid values are
//!        \b MPY_MULTIPLY_UNSIGNED
//!        \b MPY_MULTIPLY_SIGNED
//!        \b MPY_MULTIPLYACCUMULATE_UNSIGNED
//!        \b MPY_MULTIPLEACCUMULATE_SIGNED
//! \param operand is the 16-bit value to load into the 1st operand.
//!
//! This function sets the first operand for multiplication and determines what
//! type of operation should be performed. Once the second operand is set, then
//! the operation will begin.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_setOperandOne16Bit (unsigned int baseAddress,
    unsigned char multiplicationType,
    unsigned int operand)
{
    HWREG(baseAddress + OFS_MPY + multiplicationType) = operand;
}

//*****************************************************************************
//
//! Sets an 24-bit value into operand 1.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//! \param multiplicationType is the type of multiplication to perform once the
//!       second operand is set.
//!        Valid values are
//!        \b MPY_MULTIPLY_UNSIGNED
//!        \b MPY_MULTIPLY_SIGNED
//!        \b MPY_MULTIPLYACCUMULATE_UNSIGNED
//!        \b MPY_MULTIPLEACCUMULATE_SIGNED
//! \param operand is the 24-bit value to load into the 1st operand.
//!
//! This function sets the first operand for multiplication and determines what
//! type of operation should be performed. Once the second operand is set, then
//! the operation will begin.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_setOperandOne24Bit (unsigned int baseAddress,
    unsigned char multiplicationType,
    unsigned long operand)
{
    multiplicationType <<= 1;
    HWREG(baseAddress + OFS_MPY32L + multiplicationType) = operand;
    HWREGB(baseAddress + OFS_MPY32H + multiplicationType) = (operand >> 16);
}

//*****************************************************************************
//
//! Sets an 32-bit value into operand 1.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//! \param multiplicationType is the type of multiplication to perform once the
//!       second operand is set.
//!        Valid values are
//!        \b MPY_MULTIPLY_UNSIGNED
//!        \b MPY_MULTIPLY_SIGNED
//!        \b MPY_MULTIPLYACCUMULATE_UNSIGNED
//!        \b MPY_MULTIPLEACCUMULATE_SIGNED
//! \param operand is the 32-bit value to load into the 1st operand.
//!
//! This function sets the first operand for multiplication and determines what
//! type of operation should be performed. Once the second operand is set, then
//! the operation will begin.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_setOperandOne32Bit (unsigned int baseAddress,
    unsigned char multiplicationType,
    unsigned long operand)
{
    multiplicationType <<= 1;
    HWREG(baseAddress + OFS_MPY32L + multiplicationType) = operand;
    HWREG(baseAddress + OFS_MPY32H + multiplicationType) = (operand >> 16);
}

//*****************************************************************************
//
//! Sets an 8-bit value into operand 2, which starts the multiplication.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//! \param operand is the 8-bit value to load into the 2nd operand.
//!
//! This function sets the second operand of the multiplication operation and
//! starts the operation.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_setOperandTwo8Bit (unsigned int baseAddress,
    unsigned char operand)
{
    HWREGB(baseAddress + OFS_OP2) = operand;
}

//*****************************************************************************
//
//! Sets an 16-bit value into operand 2, which starts the multiplication.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//! \param operand is the 16-bit value to load into the 2nd operand.
//!
//! This function sets the second operand of the multiplication operation and
//! starts the operation.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_setOperandTwo16Bit (unsigned int baseAddress,
    unsigned int operand)
{
    HWREG(baseAddress + OFS_OP2) = operand;
}

//*****************************************************************************
//
//! Sets an 24-bit value into operand 2, which starts the multiplication.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//! \param operand is the 24-bit value to load into the 2nd operand.
//!
//! This function sets the second operand of the multiplication operation and
//! starts the operation.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_setOperandTwo24Bit (unsigned int baseAddress,
    unsigned long operand)
{
    HWREG(baseAddress + OFS_OP2L) = operand;
    HWREGB(baseAddress + OFS_OP2H) = (operand >> 16);
}

//*****************************************************************************
//
//! Sets an 32-bit value into operand 2, which starts the multiplication.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//! \param operand is the 32-bit value to load into the 2nd operand.
//!
//! This function sets the second operand of the multiplication operation and
//! starts the operation.
//!
//! \return NONE
//
//*****************************************************************************
void MPY32_setOperandTwo32Bit (unsigned int baseAddress,
    unsigned long operand)
{
    HWREG(baseAddress + OFS_OP2L) = operand;
    HWREG(baseAddress + OFS_OP2H) = (operand >> 16);
}

//*****************************************************************************
//
//! Returns an 8-bit result of the last multiplication operation.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//!
//! This function returns the 8 least significant bits of the result registers.
//! This can improve efficiency if the operation has no more than an 8-bit
//! result.
//!
//! \return The 8-bit result of the last multiplication operation.
//
//*****************************************************************************
unsigned char MPY32_getResult8Bit (unsigned int baseAddress)
{
    return ( HWREGB(baseAddress + OFS_RES0_L) );
}

//*****************************************************************************
//
//! Returns an 16-bit result of the last multiplication operation.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//!
//! This function returns the 16 least significant bits of the result registers.
//! This can improve efficiency if the operation has no more than a 16-bit
//! result.
//!
//! \return The 16-bit result of the last multiplication operation.
//
//*****************************************************************************
unsigned int MPY32_getResult16Bit (unsigned int baseAddress)
{
    return ( HWREG(baseAddress + OFS_RES0) );
}

//*****************************************************************************
//
//! Returns an 24-bit result of the last multiplication operation.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//!
//! This function returns the 24 least significant bits of the result registers.
//! This can improve efficiency if the operation has no more than an 24-bit
//! result.
//!
//! \return The 24-bit result of the last multiplication operation.
//
//*****************************************************************************
unsigned long MPY32_getResult24Bit (unsigned int baseAddress)
{
    unsigned long result = HWREG(baseAddress + OFS_RES1);

    result = (result << 16) + HWREG(baseAddress + OFS_RES0);
    return ( result );
}

//*****************************************************************************
//
//! Returns an 32-bit result of the last multiplication operation.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//!
//! This function returns a 32-bit result of the last multiplication operation,
//! which is the maximum amount of bits of a 16 x 16 operation.
//!
//! \return The 32-bit result of the last multiplication operation.
//
//*****************************************************************************
unsigned long MPY32_getResult32Bit (unsigned int baseAddress)
{
    unsigned long result = HWREG(baseAddress + OFS_RES1);

    result = (result << 16) + HWREG(baseAddress + OFS_RES0);
    return ( result );
}

//*****************************************************************************
//
//! Returns an 64-bit result of the last multiplication operation.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//!
//! This function returns all 64 bits of the result registers. The way this is
//! passed is with 4 integers contained within a uint64 struct.
//!
//! \return The 64-bit result seperated into 4 unsigned ints in a uint64 struct.
//
//*****************************************************************************
uint64 MPY32_getResult64Bit (unsigned int baseAddress)
{
    uint64 result;

    result.RES0 = HWREG(baseAddress + OFS_RES0);
    result.RES1 = HWREG(baseAddress + OFS_RES1);
    result.RES2 = HWREG(baseAddress + OFS_RES2);
    result.RES3 = HWREG(baseAddress + OFS_RES3);
    return ( result );
}

//*****************************************************************************
//
//! Returns the Sum Extension of the last multiplcation operation.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//!
//! This function returns the Sum Extension of the MPY module, which either
//! gives the sign after a signed operation or shows a carry after a multiply-
//! and-accumulate operation. The Sum Extension acts as a check for overflows
//! or underflows.
//!
//! \return The value of the MPY32 module Sum Extension.
//
//*****************************************************************************
unsigned int MPY32_getSumExtension (unsigned int baseAddress)
{
    return ( HWREG(baseAddress + OFS_SUMEXT) );
}

//*****************************************************************************
//
//! Returns the Carry Bitof the last multiplication operation.
//!
//! \param baseAddress is the Base Address of the MPY32 Module.
//!
//! This function returns the Carry Bit of the MPY module, which either
//! gives the sign after a signed operation or shows a carry after a multiply-
//! and-accumulate operation.
//!
//! \return The value of the MPY32 module Carry Bit 0x0 or 0x1.
//
//*****************************************************************************
unsigned short MPY32_getCarryBitValue (unsigned int baseAddress)
{
    return ( HWREGB(baseAddress + OFS_MPY32CTL0_L) | MPYC);
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
