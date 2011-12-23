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
//flash.c - Driver for the FLASH Module.
//
//*****************************************************************************
#include "inc/hw_types.h"
#include "driverlib/5xx_6xx/debug.h"
#include "driverlib/5xx_6xx/flash.h"
#include "msp430xgeneric.h"

//*****************************************************************************
//
//! Erase a single segment of the flash memory.
//!
//! \param baseAddress is the base address of the Flash module.
//! \param Flash_ptr is the pointer into the flash segment to be erased
//!
//! \returns NONE
//
//*****************************************************************************
void Flash_segmentErase (unsigned int baseAddress, unsigned char *Flash_ptr)
{
    //5xx Workaround: Disable global interrupt while erasing.
    //local variable to store GIE status
    unsigned int gieStatus;

    //Store current SR register
    gieStatus = __get_SR_register() & GIE;
    //Disable global interrupt
    __disable_interrupt();

    //Clear Lock bit
    HWREG(baseAddress + OFS_FCTL3) = FWKEY;

    //Set Erase bit
    HWREG(baseAddress + OFS_FCTL1) = FWKEY + ERASE;

    //Dummy write to erase Flash seg
    *Flash_ptr = 0;

    //test busy
    while (HWREGB(baseAddress + OFS_FCTL3) & BUSY) ;

    //Clear WRT bit
    HWREG(baseAddress + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG(baseAddress + OFS_FCTL3) = FWKEY + LOCK;

    //Reinstate SR register
    __bis_SR_register(gieStatus);
}

//*****************************************************************************
//
//! Erase a single bank of the flash memory.
//!
//! \param baseAddress is the base address of the Flash module.
//! \param Flash_ptr is a pointer into the bank to be erased
//!
//! \returns NONE
//
//*****************************************************************************
void Flash_bankErase (unsigned int baseAddress, unsigned char *Flash_ptr)
{
    //5xx Workaround: Disable global interrupt while erasing.
    //local variable to store GIE status
    unsigned int gieStatus;

    //Store current SR register
    gieStatus = __get_SR_register() & GIE;
    //Disable global interrupt
    __disable_interrupt();
  
    //Clear Lock bit
    HWREG(baseAddress + OFS_FCTL3) = FWKEY;
    
    while (HWREGB(baseAddress + OFS_FCTL3) & BUSY) ;

    //Set MERAS bit
    HWREG(baseAddress + OFS_FCTL1) = FWKEY + MERAS;

    //Dummy write to erase Flash seg
    *Flash_ptr = 0;

    //test busy
    while (HWREGB(baseAddress + OFS_FCTL3) & BUSY) ;

    //Clear WRT bit
    HWREG(baseAddress + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG(baseAddress + OFS_FCTL3) = FWKEY + LOCK;

    //Reinstate SR register
    __bis_SR_register(gieStatus);
}

//*****************************************************************************
//
//! Erase check of the flash memory
//!
//! \param baseAddress is the base address of the Flash module.
//! \param Flash_ptr is the Pointer to the starting location of the erase check
//! \param numberOfBytes is the number of bytes to be checked
//!
//! \returns STATUS_SUCCESS or STATUS_FAIL
//
//*****************************************************************************
unsigned short Flash_eraseCheck (unsigned int baseAddress,
    unsigned char *Flash_ptr,
    unsigned int numberOfBytes
    )
{
    unsigned int i;

    for (i = 0; i < numberOfBytes; i++)
    {
        //was erasing successfull?
        if ((*(Flash_ptr + i)) != 0xFF){
            return ( STATUS_FAIL) ;
        }
    }
    return ( STATUS_SUCCESS) ;
}

//*****************************************************************************
//
//! Write data into the flash memory in byte format.
//!
//! \param baseAddress is the base address of the Flash module.
//! \param Data_ptr is the pointer to the data to be written
//! \param Flash_ptr is the pointer into which to write the data
//! \param numberOfBytes is the number of bytes to be written
//!
//! \returns NONE
//
//*****************************************************************************
void Flash_write8 (unsigned int baseAddress,
    unsigned char *Data_ptr,
    unsigned char *Flash_ptr,
    unsigned int numberOfBytes
    )
{
    //Clear Lock bit
    HWREG(baseAddress + OFS_FCTL3) = FWKEY;

    //Enable byte/word write mode
    HWREG(baseAddress + OFS_FCTL1) = FWKEY + WRT;

    while (numberOfBytes > 0)
    {
        //test busy
        while (HWREGB(baseAddress + OFS_FCTL3) & BUSY) ;

        //Write to Flash
        *Flash_ptr++ = *Data_ptr++;
        numberOfBytes--;
    }

    //Clear write bit
    HWREG(baseAddress + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG(baseAddress + OFS_FCTL3) = FWKEY + LOCK;
}

//*****************************************************************************
//
//! Write data into the flash memory in word format.
//!
//! \param baseAddress is the base address of the Flash module.
//! \param Data_ptr is the pointer to the data to be written
//! \param Flash_ptr is the pointer into which to write the data
//! \param numberOfBytes is the number of bytes to be written
//!
//! \returns NONE
//
//*****************************************************************************
void Flash_write16 (unsigned int baseAddress,
    unsigned int *Data_ptr,
    unsigned int *Flash_ptr,
    unsigned int numberOfBytes
    )
{
    //Clear Lock bit
    HWREG(baseAddress + OFS_FCTL3) = FWKEY;

    //Enable byte/word write mode
    HWREG(baseAddress + OFS_FCTL1) = FWKEY + WRT;

    while (numberOfBytes > 0)
    {
        //test busy
        while (HWREGB(baseAddress + OFS_FCTL3) & BUSY) ;

        //Write to Flash
        *Flash_ptr++ = *Data_ptr++;
        numberOfBytes--;
    }

    //Clear Erase bit
    HWREG(baseAddress + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG(baseAddress + OFS_FCTL3) = FWKEY + LOCK;
}

//*****************************************************************************
//
//! Write data into the flash memory in long format, pass by reference
//!
//! \param baseAddress is the base address of the Flash module.
//! \param Data_ptr is the pointer to the data to be written
//! \param Flash_ptr is the pointer into which to write the data
//! \param numberOfBytes is the number of bytes to be written
//!
//! \returns NONE
//
//*****************************************************************************
void Flash_write32 (unsigned int baseAddress,
    unsigned long *Data_ptr,
    unsigned long *Flash_ptr,
    unsigned int numberOfBytes
    )
{
    //Clear Lock bit
    HWREG(baseAddress + OFS_FCTL3) = FWKEY;

    //Enable long-word write
    HWREG(baseAddress + OFS_FCTL1) = FWKEY + BLKWRT;

    while (numberOfBytes > 0)
    {
        //test busy
        while (HWREGB(baseAddress + OFS_FCTL3) & BUSY) ;

        //Write to Flash
        *Flash_ptr++ = *Data_ptr++;
        numberOfBytes--;
    }

    //Clear Erase bit
    HWREG(baseAddress + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG(baseAddress + OFS_FCTL3) = FWKEY + LOCK;
}

//*****************************************************************************
//
//! Write data into the flash memory in long format, pass by value
//!
//! \param baseAddress is the base address of the Flash module.
//! \param Data_ptr is the pointer to the data to be written
//! \param Flash_ptr is the pointer into which to write the data
//! \param numberOfBytes is the number of bytes to be written
//!
//! \returns NONE
//
//*****************************************************************************
void Flash_memoryFill32 (unsigned int baseAddress,
    unsigned long value,
    unsigned long *Flash_ptr,
    unsigned int count
    )
{
    //Clear Lock bit
    HWREG(baseAddress + OFS_FCTL3) = FWKEY;

    //Enable long-word write
    HWREG(baseAddress + OFS_FCTL1) = FWKEY + BLKWRT;

    //test busy
    while (count > 0)
    {
        while ((HWREGB(baseAddress + OFS_FCTL3)) & BUSY) ;

        //Write to Flash
        *Flash_ptr++ = value;
        count--;
    }

    //Clear Erase bit
    HWREG(baseAddress + OFS_FCTL1) = FWKEY;

    //Set LOCK bit
    HWREG(baseAddress + OFS_FCTL3) = FWKEY + LOCK;
}

//*****************************************************************************
//
//! Check if Flash status to see if it is currently busy erasing or programming
//!
//! \param baseAddress is the base address of the Flash module.
//! \param mask is the logical OR of the status mask requested
//!            (FLASH_READY_FOR_NEXT_WRITE)
//!            (FLASH_ACCESS_VIOLATION_INTERRUPT_FLAG)
//!            (FLASH_PASSWORD_WRITTEN_INCORRECTLY)
//!            (FLASH_BUSY)
//! \returns logical OR of FLASH_READY_FOR_NEXT_WRITE/
//!          FLASH_ACCESS_VIOLATION_INTERRUPT_FLAG/
//!          FLASH_PASSWORD_WRITTEN_INCORRECTLY/FLASH_BUSY/0x00
//!
//*****************************************************************************
unsigned char Flash_status (unsigned int baseAddress,
    unsigned char mask
    )
{
    return ((HWREGB(baseAddress + OFS_FCTL3) & mask ));
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
