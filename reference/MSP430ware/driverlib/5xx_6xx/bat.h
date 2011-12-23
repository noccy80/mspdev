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
#ifndef __MSP430WARE_BAT_H__
#define __MSP430WARE_BAT_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_BATTERY_CHARGER__
#define __MSP430_HAS_BACKUP_RAM__

//*****************************************************************************
//
//The following are values that can be returned by BAT_unlockBackupSubSystem().
//
//*****************************************************************************
#define BAT_UNLOCKFAILURE (0x0)
#define BAT_UNLOCKSUCCESS (0x1)

//*****************************************************************************
//
//The following are values that can be passed to BAT_chargerInitAndEnable()
//in the chargerEndVoltage parameter.
//
//*****************************************************************************
#define BAT_CHARGERENDVOLTAGE_VCC (BAKCHV0)
#define BAT_CHARGERENDVOLTAGE2_7V (BAKCHV1)

//*****************************************************************************
//
//The following are values that can be passed to BAT_chargerInitAndEnable()
//in the chargeCurrent parameter.
//
//*****************************************************************************
#define BAT_CHARGECURRENT_5KOHM  (BAKCHC0)
#define BAT_CHARGECURRENT_10KOHM (BAKCHC1)
#define BAT_CHARGECURRENT_20KOHM (BAKCHC0 + BAKCHC1)

//*****************************************************************************
//
//The following are values that can be passed to BAT_setBackupRAMData() and
//BAT_getBackupRAMData() in the backupRAMSelect parameter.
//
//*****************************************************************************
#define BAT_RAMSELECT_0 (0x0000)
#define BAT_RAMSELECT_1 (0x0002)
#define BAT_RAMSELECT_2 (0x0004)
#define BAT_RAMSELECT_3 (0x0006)

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************

extern unsigned short BAT_unlockBackupSubSystem (unsigned int baseAddress);

extern void BAT_enableBackupSupplyToADC (unsigned int baseAddress);

extern void BAT_disableBackupSupplyToADC (unsigned int baseAddress);

extern void BAT_manuallySwitchToBackupSupply (unsigned int baseAddress);

extern void BAT_disable (unsigned int baseAddress);

extern void BAT_chargerInitAndEnable (unsigned int baseAddress,
    unsigned char chargerEndVoltage,
    unsigned char chargeCurrent);

extern void BAT_disableCharger (unsigned int baseAddress);

extern void BAT_setBackupRAMData (unsigned int baseAddress,
    unsigned char backupRAMSelect,
    unsigned int data);

extern unsigned int BAT_getBackupRAMData (unsigned int baseAddress,
    unsigned char backupRAMSelect);


#endif
