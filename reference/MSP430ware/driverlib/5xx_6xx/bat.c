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
//bak.c - Driver for the BAK Module.
//
//*****************************************************************************
#include "driverlib/5xx_6xx/bat.h"
#include "inc/hw_types.h"
#include "msp430xgeneric.h"
#include "driverlib/5xx_6xx/debug.h"

//*****************************************************************************
//
//! Unlocks any pending backup input pins and RTC_B interrupts to be serviced.
//!
//! \param baseAddress is the base address of the BAT module.
//!
//! This function unlocks the ability to view and service any pending backup
//! input pin interrupts, as well as pending RTC_B interrupts. The backup
//! sub-system can only be unlocked when the backup domain has settled, so
//! this function returns the status of the unlock bit after it has been
//! to be verified by user code. Please note, the backup sub-system should only
//! be unlocked after modifying the RTC_B registers.
//!
//! \return BAT_UNLOCKSUCCESS if the backup subsystem has been successfully
//!        unlocked, or BAT_UNLOCKFAILURE if the backup subsystem has not yet
//!        settled.
//
//*****************************************************************************
unsigned short BAT_unlockBackupSubSystem (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_BAKCTL) &= ~(LOCKBAK);
    if ( HWREGB(baseAddress + OFS_BAKCTL) & LOCKBAK){
        return ( BAT_UNLOCKFAILURE) ;
    } else   {
        return ( BAT_UNLOCKSUCCESS) ;
    }
}

//*****************************************************************************
//
//! Enables the backup supply to be measured by the ADC battery monitor input.
//!
//! \param baseAddress is the base address of the BAT module.
//!
//! This function enables the backup supply signal to be monitored by the ADC
//! battery supply monitor input, to allow a measurement of the voltage from
//! the backup battery.
//!
//! \return NONE
//
//*****************************************************************************
void BAT_enableBackupSupplyToADC (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_BAKCTL) |= BAKADC;
}

//*****************************************************************************
//
//! Disables the backup supply input to the ADC module.
//!
//! \param baseAddress is the base address of the BAT module.
//!
//! This function disables the ability to monitor the backup supply voltage
//! from the ADC battery monitor input.
//!
//! \return NONE
//
//*****************************************************************************
void BAT_disableBackupSupplyToADC (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_BAKCTL) &= ~(BAKADC);
}

//*****************************************************************************
//
//! Manually switches to backup supply.
//!
//! \param baseAddress is the base address of the BAT module.
//!
//! This function uses software to manually switch to the backup battery supply.
//! Once this bit is set, it will be automatically reset by a POR and the system
//! returns to an automatic switch to backup supply.
//!
//! \return NONE
//
//*****************************************************************************
void BAT_manuallySwitchToBackupSupply (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_BAKCTL) |= BAKSW;
}

//*****************************************************************************
//
//! Disables backup battery system.
//!
//! \param baseAddress is the base address of the BAT module.
//!
//! This function disables the battery backup system from being used. The
//! battery backup system is reenabled after a power cycle.
//!
//! \return NONE
//
//*****************************************************************************
void BAT_disable (unsigned int baseAddress)
{
    HWREGB(baseAddress + OFS_BAKCTL) |= BAKDIS;
}

//*****************************************************************************
//
//! Initializes and enables the backup battery charger.
//!
//! \param baseAddress is the base address of the BAT module.
//! \param chargerEndVoltage is the maximum voltage to charge the backup
//!       battery to.
//!        Valid values are
//!        \b BAT_CHARGERENDVOLTAGE_VCC - charges backup battery up to Vcc
//!        \b BAT_CHARGERENDVOLTAGE2_7V - charges backup battery up to 2.7V
//!             OR up to Vcc if Vcc is less than 2.7V.
//!        Modified bits are \b BAKCHVx of \b BAKCHCTL register.
//! \param chargeCurrent is the maximum current to charge the backup battery at.
//!        Valid values are
//!        \b BAT_CHARGECURRENT_5KOHM
//!        \b BAT_CHARGECURRENT_10KOHM
//!        \b BAT_CHARGECURRENT_20KOHM
//!        Modified bits are \b BAKCHCx of \b BAKCHCTL register.
//!
//! This function initializes the backup battery charger with the selected
//! settings.
//!
//! \return NONE
//
//*****************************************************************************
void BAT_chargerInitAndEnable (unsigned int baseAddress,
    unsigned char chargerEndVoltage,
    unsigned char chargeCurrent)
{
    HWREG(baseAddress +
        OFS_BAKCHCTL) = CHPWD + chargerEndVoltage + chargeCurrent;
}

//*****************************************************************************
//
//! Disables and resets backup battery charger settings.
//!
//! \param baseAddress is the base address of the BAT module.
//!
//! This function clears all backup battery charger settings and disabes it.
//! To renable the charger, a call to BAT_chargerInitAndEnable() is required.
//!
//! \return NONE
//
//*****************************************************************************
void BAT_disableCharger (unsigned int baseAddress)
{
    HWREG(baseAddress + OFS_BAKCHCTL) = CHPWD;
}

//*****************************************************************************
//
//! Sets data into the selected backup RAM space.
//!
//! \param baseAddress is the base address of the BAT module.
//! \param backupRAMSelect is the backup RAM space to set data into.
//!        Valid values are
//!        \b BAT_RAMSELECT_0
//!        \b BAT_RAMSELECT_1
//!        \b BAT_RAMSELECT_2
//!        \b BAT_RAMSELECT_3
//! \param data is the data to set into the selected backup RAM space.
//!
//! This function sets the given 16-bit data into the selected backup RAM space.
//!
//! \return NONE
//
//*****************************************************************************
void BAT_setBackupRAMData (unsigned int baseAddress,
    unsigned char backupRAMSelect,
    unsigned int data)
{
    HWREG(baseAddress + backupRAMSelect) = data;
}

//*****************************************************************************
//
//! Returns the data from the selected backup RAM space.
//!
//! \param baseAddress is the base address of the BAT module.
//! \param backupRAMSelect is the backup RAM space to read out from.
//!        Valid values are
//!        \b BAT_RAMSELECT_0
//!        \b BAT_RAMSELECT_1
//!        \b BAT_RAMSELECT_2
//!        \b BAT_RAMSELECT_3
//!
//! This function returns the 16-bit data currently residing in the selected
//! backup RAM space.
//!
//! \return Data residing in the selected backup RAM space.
//
//*****************************************************************************
unsigned int BAT_getBackupRAMData (unsigned int baseAddress,
    unsigned char backupRAMSelect)
{
    return ( HWREG(baseAddress + backupRAMSelect) );
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
