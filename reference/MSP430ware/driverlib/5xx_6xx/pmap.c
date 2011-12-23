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
//pmap.c - Driver for the PMAP Module.
//
//*****************************************************************************
#include "inc/hw_types.h"
#include "driverlib/5xx_6xx/debug.h"
#include "driverlib/5xx_6xx/pmap.h"
#include "msp430xgeneric.h"

//*****************************************************************************
//
//! This function configures the MSP430 Port Mapper
//!
//! \param baseAddress is the base address of the Port Mapper module.
//! \param portMapping is the pointer to init Data
//! \param PxMAPy is the pointer start of first Port Mapper to initialize
//! \param numberOfPorts is the number of Ports to initialize
//! \param portMapReconfigure is used to enable/disable reconfiguration
//!             Valid values are
//!             \b PMAP_ENABLE_RECONFIGURATION
//!             \b PMAP_DISABLE_RECONFIGURATION [Default value]
//! Modified registers are \b PMAPKEYID, \b PMAPCTL
//!
//! \return None
//
//*****************************************************************************
void PMAP_configurePorts ( unsigned int baseAddress,
    const unsigned char *portMapping,
    unsigned char *PxMAPy,
    unsigned char numberOfPorts,
    unsigned char portMapReconfigure
    )
{
    ASSERT((portMapReconfigure == PMAP_ENABLE_RECONFIGURATION) ||
        (portMapReconfigure == PMAP_DISABLE_RECONFIGURATION)
        );

    //Store current interrupt state, then disable all interrupts
    unsigned int globalInterruptState = __get_SR_register() & GIE;
    __disable_interrupt();

    //Get write-access to port mapping registers:
    HWREG(baseAddress + OFS_PMAPKEYID) = PMAPPW;

    //Enable/Disable reconfiguration during runtime
    HWREGB(baseAddress + OFS_PMAPCTL) &= ~PMAPRECFG;
    HWREGB(baseAddress + OFS_PMAPCTL) |= portMapReconfigure;

    //Configure Port Mapping:
    unsigned int i;
    for (i = 0; i < numberOfPorts * 8; i++)
    {
        PxMAPy[i] = portMapping[i];
    }

    //Disable write-access to port mapping registers:
    HWREGB(baseAddress + OFS_PMAPKEYID) = 0;

    //Restore previous interrupt state
    __bis_SR_register(globalInterruptState);
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
