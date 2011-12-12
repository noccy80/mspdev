/**
 *  @file Communication.h
 *
 *  @brief MSP430 communication public interface definitions for the USART, USI, 
 *         and USCI modules.
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
#ifndef __MCU_MSP430_COMMUNICATION_H
#define	__MCU_MSP430_COMMUNICATION_H

// Processor configuration
#include "Configuration/MSP430Config.h"

#define COMMCOUNT     USICOUNT + USARTCOUNT + USCICOUNT

#define BLOCKING      1
#define NONBLOCKING   0

/**
 *  @details Queue management sturucture
 */
typedef struct Queue
{
  uint8_t * pBuffer;
  uint8_t * pWrite;
  uint8_t * pRead;
  uint8_t bufsize;
} Queue;

/**
 *  @details Communication Data Definition structure
 */
typedef struct CommunicationDataDefinition
{
  Queue TXQueue;
  Queue RXQueue; 
  uint8_t done  : 1;
  uint8_t count : 7;
} CommunicationDataDefinition;

/**
 *  @details Communication Data Definition Buffer management structure
 */
typedef struct CommunicationDataBufferDefinition
{
  uint8_t * TXBuffer;
  uint8_t TXBufferIndex;
  uint8_t * RXBuffer;
  uint8_t RXBufferIndex;
  uint8_t done  : 1;
  uint8_t count : 7;
} CommunicationDataBufferDefinition;

extern CommunicationDataDefinition * CommStructure[COMMCOUNT];
extern CommunicationDataBufferDefinition * communicationBuffer;

// Peripheral interfaces
#include "Peripherals/Communication/USCI.h"

// FPI callback functions
extern void CommunicationCallbackModule0();
extern void CommunicationCallbackModule1();
extern void CommunicationCallbackModule2();

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details Get data from the RX Queue buffer.
 */
void GetCommunicationBuffer(uint8_t peripheral, uint8_t * pBuffer, uint8_t count);

/**
 *  @details Set data to the TX Queue buffer.
 */
void SetCommunicationBuffer(uint8_t peripheral, uint8_t * pBuffer, uint8_t count);

/**
 *  @details Sets communication peripherals to a predetermined state.
 *           These peripherals include: USART, USI, USCI
 */
void InitCommunication(void);

/**
 *  @brief  Read/Write data from Communication module.
 */
void CommunicationReadWrite(uint8_t port, uint8_t * pBuffer, uint8_t count, uint8_t readwrite, uint8_t useinterrupts);

// PRIVATE INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details Update read/write pointers for transmit queue.
 */
void UpdateTXQueue(uint8_t peripheral, uint8_t ** pReadWrite);

/**
 *  @details Update read/write pointers for receive queue.
 */
uint8_t UpdateRXQueue(uint8_t peripheral, uint8_t ** pReadWrite);

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 *  @Communication module ISR extension.
 */
void CommunicationCallback(uint8_t port);

#endif	// __MCU_MSP430_COMMUNICATION_H