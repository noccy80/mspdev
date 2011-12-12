/**
 *  @file Protocol.h
 *
 *  @brief Protocol Layer Function Declarations
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

#ifndef __APP_PROTOCOL_H
#define __APP_PROTOCOL_H

#include "Framework\FPI\FPI.h"
#include "Application.h"
#include "CommandInterface.h"
#include "RadioOperation.h"

#define __PROTOCOL_NAME "BoosterStack"                                          //!< Module Display Name
#define __PROTOCOL_VERSION   1                                                  //!< Module Version
#define __PROTOCOL_REVISION  0                                                  //!< Module Revision
#define __PROTOCOL_DESCRIPTION "Lite physical channel handling and frame transport" //!< Module Description

/**
 * @details Initialize the Protocol
 */
void InitProtocol(void);

/**
 * @details exchange information; wake radio, transmit, receive, radio sleep
 */
uint8_t DataExchange(uint8_t * pBuffer, uint8_t *count);

/**
 * @details Listen for a packet
 */
uint8_t Listen(uint8_t * pBuffer, uint8_t * pCount);

/**
 * @details Config change sequence
 */
uint8_t RXTXCycle(AppRadio * radio, uint8_t * pBuffer, uint8_t * pCount);

/**
 * @details Provide Status Update when necessary
 */
void Query_Current_Status(PayloadFrame *payload);

/**
 * @details Start the Timer
 */
void StartTimer(void);

/**
 * @details Provide information about all the config, its corresponding channels,
 *          and maximum power settings.
 */
unsigned char ConfigurationInfo(void);

/**
 * @details Set the Physical Settings as current settings(config, channel and power)
 */
unsigned char SetCurrentPhysical(void);

/**
 * @details Get current Physical Settings(config, channel and power)
 */
unsigned char GetCurrentPhysical(void);

/**
 * @details Output the values of all the radio registers
 */
unsigned char DumpRadioRegisters(void);

/**
 * @details Set the total Cycle Time
 */
unsigned char SetCycleTime(unsigned char ID, unsigned int newCycleTime);

/**
 * @details Send Config Change Ping Sequence
 */
uint8_t SendConfigPingSequence(uint8_t * pBuffer, uint8_t * pCount);

#endif  // __APP_PROTOCOL_H
