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
//ramcontrol.c - Driver for the RAM Controller Module.
//
//*****************************************************************************
#include "inc/hw_types.h"
#include "driverlib/5xx_6xx/debug.h"
#include "driverlib/5xx_6xx/ramcontroller.h"
#include "msp430xgeneric.h"

//*****************************************************************************
//
//! Set specified RAM sector off
//!
//! \param baseAddress is the base address of the Timer module.
//! \param sector is specified sector to be set off.
//! Valid values are a logical OR of
//!         \b RAMCONTROL_SECTOR0
//!         \b RAMCONTROL_SECTOR1
//!         \b RAMCONTROL_SECTOR2
//!         \b RAMCONTROL_SECTOR3
//!         \b RAMCONTROL_SECTOR4
//!         \b RAMCONTROL_SECTOR5
//!         \b RAMCONTROL_SECTOR6
//!         \b RAMCONTROL_SECTOR7
//!
//! Modified register RCCTL0
//!
//! \return None
//
//*****************************************************************************
void ramController_setSectorOff (unsigned int baseAddress,
    unsigned char sector
    )
{
    ASSERT(0x00 == sector & (~(RAMCONTROL_SECTOR0 +
                               RAMCONTROL_SECTOR1 +
                               RAMCONTROL_SECTOR2 +
                               RAMCONTROL_SECTOR3 
                               )
                             )

        );
    //Write key to start write to RCCTL0 and sector
    HWREG(baseAddress + OFS_RCCTL0) = (RCKEY + sector);
}

//*****************************************************************************
//
//! Get RAM sector ON/OFF status
//!
//! \param baseAddress is the base address of the Timer module.
//! \param sector is specified sector
//! Valid values are a logical OR of
//!         \b RAMCONTROL_SECTOR0
//!         \b RAMCONTROL_SECTOR1
//!         \b RAMCONTROL_SECTOR2
//!         \b RAMCONTROL_SECTOR3
//!         \b RAMCONTROL_SECTOR4
//!         \b RAMCONTROL_SECTOR5
//!         \b RAMCONTROL_SECTOR6
//!         \b RAMCONTROL_SECTOR7
//!
//! Modified register RCCTL0
//!
//! \return Mask of the sector state that are ON
//
//*****************************************************************************
unsigned char ramController_getSectorState (unsigned int baseAddress,
    unsigned char sector
    )
{
    ASSERT(0x00 == sector & (~(RAMCONTROL_SECTOR0 +
                               RAMCONTROL_SECTOR1 +
                               RAMCONTROL_SECTOR2 +
                               RAMCONTROL_SECTOR3 
                               )
                             )

        );
    return (HWREGB(baseAddress + OFS_RCCTL0_L) & sector);
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
