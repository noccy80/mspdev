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
//crc.c - Driver for the CRC Module.
//
//*****************************************************************************
#include "driverlib/5xx_6xx/crc.h"
#include "inc/hw_types.h"
#include "msp430xgeneric.h"
#include "driverlib/5xx_6xx/debug.h"

//*****************************************************************************
//
//! Sets the seed for the CRC.
//!
//! \param baseAddress is the base address of the CRC module.
//! \param seed is the seed for the CRC to start generating a signature from.
//!        Modified bits are \b CRCINIRES of \b CRCINIRES register.
//!
//! This function sets the seed for the CRC to begin generating a signature with
//! the given seed and all passed data. Using this funtion resets the CRC
//! signature.
//!
//! \return NONE
//
//*****************************************************************************
void CRC_setSeed (unsigned int baseAddress,
    unsigned int seed)
{
    HWREG(baseAddress + OFS_CRCINIRES) = seed;
}

//*****************************************************************************
//
//! Sets the data to add into the CRC module to generate a new signature.
//!
//! \param baseAddress is the base address of the CRC module.
//! \param dataIn is the data to be added, through the CRC module, to the
//!       signature.
//!        Modified bits are \b CRCDI of \b CRCDI register.
//!
//! This function sets the given data into the CRC module to generate the new
//! signature from the current signature and new data.
//!
//! \return NONE
//
//*****************************************************************************
void CRC_setData (unsigned int baseAddress,
    unsigned int dataIn)
{
    HWREG(baseAddress + OFS_CRCDI) = dataIn;
}

//*****************************************************************************
//
//! Translates the data by reversing the bits in each byte and then sets this
//! data to add into the CRC module to generate a new signature.
//!
//! \param baseAddress is the base address of the CRC module.
//! \param dataIn is the data to be added, through the CRC module, to the
//!       signature.
//!        Modified bits are \b CRCDIRB of \b CRCDIRB register.
//!
//! This function first reverses the bits in each byte of the data and then
//! generates the new signature from the current signature and new translated
//! data.
//!
//! \return NONE
//
//*****************************************************************************
void CRC_setDataByteBitsReversed (unsigned int baseAddress,
    unsigned int dataIn)
{
    HWREG(baseAddress + OFS_CRCDIRB) = dataIn;
}

//*****************************************************************************
//
//! Returns the value currently in the Data register.
//!
//! \param baseAddress is the base address of the CRC module.
//!
//! This function returns the value currently in the data register. If set in
//! byte bits reversed format, then the translated data would be returned.
//!
//! \return NONE
//
//*****************************************************************************
unsigned int CRC_getData (unsigned int baseAddress)
{
    return ( HWREG(baseAddress + OFS_CRCDI) );
}

//*****************************************************************************
//
//! Returns the value pf the Signature Result.
//!
//! \param baseAddress is the base address of the CRC module.
//!
//! This function returns the value of the signature result generated by the CRC.
//!
//! \return NONE
//
//*****************************************************************************
unsigned int CRC_getResult (unsigned int baseAddress)
{
    return ( HWREG(baseAddress + OFS_CRCINIRES) );
}

//*****************************************************************************
//
//! Returns the bit-wise reversed format of the Signature Result.
//!
//! \param baseAddress is the base address of the CRC module.
//!
//! This function returns the bit-wise reversed format of the Signature Result.
//!
//! \return NONE
//
//*****************************************************************************
unsigned int CRC_getResultBitsReversed (unsigned int baseAddress)
{
    return ( HWREG(baseAddress + OFS_CRCRESR) );
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
