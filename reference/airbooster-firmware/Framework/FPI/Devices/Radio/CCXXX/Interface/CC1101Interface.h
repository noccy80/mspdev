/**
 *  @file CC1101Interface.h
 *
 *  @brief CC1101 radio interface prototype definitions.
 *
 *  @see RadioInterface.h
 *
 *  @version  1.0
 *
 *  @attention IMPORTANT: Your use of this Software is limited to those specific 
 *             rights granted under the terms of a software license agreement 
 *             between the user who downloaded the software, his/her employer 
 *             (which must be your employer) and Anaren (the "License"). You may
 *             not use this Software unless you agree to abide by the terms of 
 *             the License. The License limits your use, and you acknowledge,
 *             that the Software may not be modified, copied or distributed unless
 *             in connection with an authentic Anaren product. Other than for the 
 *             foregoing purpose, you may not use, reproduce, copy, prepare 
 *             derivative works of, modify, distribute, reverse engineer, decompile,
 *             perform, display or sell this Software and/or its documentation 
 *             for any purpose. 
 *             YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION
 *             ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS 
 *             OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY  WARRANTY OF 
 *             MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR 
 *             PURPOSE. IN NO EVENT SHALL ANAREN OR ITS LICENSORS BE LIABLE OR
 *             OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 *             BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR 
 *             INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY 
 *             INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, 
 *             LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS,
 *             TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT
 *             NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS. 
 */
#ifndef __RADIO_CC1101INTERFACE_H
#define __RADIO_CC1101INTERFACE_H

#if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)

#include "../CCXXXInterface.h"
#include "Framework\FPI\FPI.h"

// Microcontroller interface
#include "../../../../../MCU/MCUInterface.h"

/**
 *  @details Configure CC1101 radio.
 */
void ConfigureCC1101(Radio * radio);

/**
 *  @details Configure CC110L radio.
 */
void ConfigureCC110L(Radio * radio);

/**
 *  @details Reset the radio. This functionality is currently not supported.
 */
void ResetCC1101(Radio * radio);

/**
 *  @details Place radio into sleep mode.
 */
void CC1101Sleep(Radio * radio);

/**
 *  @details Wake up the radio.
 */
void CC1101WakeUp(Radio * radio);

/**
 *  @details Write to the radio.
 */
void CC1101Write(Radio * radio, uint8_t addr, uint8_t* pBuffer, uint8_t count);

/**
 *  @details Read from the radio.
 */
uint8_t CC1101Read(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count);

// PRIVATE INTERFACE
////////////////////////////////////////////////////////////////////////////////
/**
 *  @details Perform read/write from/to the radio.
 */
void CC1101SPIExternalReadWrite(Radio * radio, uint8_t command, uint8_t * pBuffer, uint8_t count, uint8_t readwrite);

/**
 *  @details Write to the PATABLE of the radio. This functionality is currently 
 *           not supported.
 */
void CC1101WritePATable(Radio * radio, uint8_t * pBuffer, uint8_t count);

#endif  // __RADIO_CCXXX_CC1101, __RADIO_CCXXX_CC110L, __RADIO_CCXXX_CC2500

#endif  // __RADIO_CC1101INTERFACE_H