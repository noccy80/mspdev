/**
 *  @file RadioOperation.h
 *
 *  @brief Radio Operation structure and function Declarations
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

#ifndef __APP_RADIOOPERATION_H
#define __APP_RADIOOPERATION_H

#include "Definitions.h"
#include "Framework\FPI\FPI.h"

#define RADIO_FULL_TEXT_DESCRIPTIONS

/**
 * @brief Cycle Timeout Flags
 */
typedef const struct CycleTimeout{
  uint16_t cycleTime;                                                           //!< Cycle time for config timeout
  uint16_t syncTimeout;                                                         //!< Sync word timeout
  uint16_t EOPTimeout;                                                          //!< End of Packet timeout
}CycleTimeout;

/**
 * @brief Application Radio Power Settings
 */
typedef const struct AppRadioPowerList
{
  RFPowerSettings radioPower;                                                   //!< Radio power definitions
  char *powerDescription;
} AppRadioPowerList;

/**
 * @brief Application Radio Channels
 */
typedef const struct AppRadioChannelList
{
  RFChannel radioChannel;                                                       //!< Radio channel definitions
  char *channelDescription;
} AppRadioChannelList;

/**
 * @brief Application RF Channels
 */
typedef const struct AppRadioChannel
{
  uint8_t radioChannelIndex;                                                    //!< Radio channel index
  uint8_t radioPowerIndex;                                                      //!< Radio power index
} AppRadioChannel;

/**
 * @brief Application RF Register Settings
 */
typedef const struct AppRegisterSettings
{
  RFSettings registerSettings;                                                  //!< Radio register settings
  char *baseSettingsDescription;
  CycleTimeout configCycleTimeout;
} AppRegisterSettings;

/**
 * @brief Application Radio Configuration Settings
 */
typedef const struct AppRadioConfiguration
{
  AppRegisterSettings * pRegisterSettings;                                      //!< Radio register settings
  AppRadioChannel * pConfigurationChannel;                                      //!< Radio channels assigned to configuration
  uint8_t configurationChannelCount;                                            //!< Number of channels assigned to configuration
  char *baseConfigurationDescription;
} AppRadioConfiguration;

/**
 * @brief Array Sizes
 *
 * @brief Represents the array sizes of the radio settings.
 */
typedef const struct AppRadioArraySizes 
{
  uint8_t radioConfigurationCount;                                              //!< Number of configurations assigned to radio
  uint8_t radioChannelListCount;                                                //!< Number of channel settings assigned to radio
  uint8_t radioPowerListCount;                                                  //!< Number of power settings assigned to radio
  uint8_t radioRegisterSettingsSize;                                            //!< Size of configuration settings structure
  uint8_t radioChannelSize;                                                     //!< Size of channel array
  uint8_t radioPowerSize;                                                       //!< Size of power array
} AppRadioArraySizes;

/**
 * @brief Application Radio Definition
 */
typedef struct AppRadio
{
  Radio frameworkRadio;                                                         //!< Radio configuration settings
  AppRadioConfiguration * pRadioConfiguration;                                  //!< Radio configuration definitions
  AppRadioChannelList * pRadioChannelList;                                      //!< Radio channel definitions
  AppRadioPowerList * pRadioPowerList;                                          //!< Radio power definitions
  AppRadioArraySizes * pRadioArraySizes;                                        //!< Radio array sizes 
  char *radioDescription;
} AppRadio;

/**
 * @brief Timeout Flags
 */
typedef struct TimerStruct{
  uint8_t frameTimeout;                                                         //!< Frame timeout
  uint8_t configTimeout;                                                        //!< Config change timeout
}TimerStruct;

/**
 * @brief Radio Frame Definition
 */
typedef struct RadioFrameStruct{
  uint8_t frameHeader[HEADER_LENGTH];                                           //!< Frame header      
  uint8_t framePayload[MAX_PAYLOAD_LENGTH];                                     //!< Frame payload
}RadioFrameStruct;

/**
 * @brief Structure for Operation of Radio Functions
 */
typedef struct RadioStruct{
  RadioFrameStruct TxFrameStruct;
  RadioFrameStruct RxFrameStruct;
  uint8_t linkStatus[2];                                                        //!< Status bytes
  uint8_t frameLength;                                                          //!< Length of the total packet
  enum FrameState {                                                             //!< for current frame state
    FRAME_IDLE                        = 0,
    WAITING_FOR_SYNCWORD              = BIT0,
    WAITING_FOR_EOP                   = BIT1,
    FRAME_RECEIVED                    = BIT2,
    FRAME_SENT                        = BIT3
  } FrameState;

  uint8_t oldRadio;                                                             //!< Radio Index Information
  uint8_t currentRadio;
}RadioStruct;

/**
 * @brief Configuration Settings Information
 */
typedef struct ConfigStruct{
  uint8_t currentRFICConfig;                                                    //!< Config Index Information
  uint8_t oldRFICConfig;
  uint8_t currentRFChannelNum;                                                  //!< Channel Index Information
  uint8_t oldRFChannelNum;
  uint8_t currentRFPower;                                                       //!< Power Index Information
  uint8_t oldRFPower;
}ConfigStruct;

/**
 * @brief TX Flags
 */
typedef struct TXFlagStruct{
  enum TxConfigMessageType {                                                    //!< Flags for config change sequence
    SEND_NO_CONFIG_CHANGE             = 0,
    SEND_CONFIG_REQUEST               = BIT0,
    SEND_CONFIG_PING                  = BIT1,
    SEND_CONFIG_ACK                   = BIT2
  } TxConfigMessageType;
  enum TxPayloadMessageType {                                                   //!< Flags for payload tranfer
    SEND_NO_PAYLOAD                   = 0,
    SEND_PAYLOAD                      = 1
  } TxPayloadMessageType;
  enum TxACKMessageType {                                                       //!< Flags to ACK transfer
    SEND_NO_ACK                       = 0,
    SEND_ACK                          = 1
  } TxACKMessageType;
}TXFlagStruct;

/**
 * @brief RX Flags
 */
typedef struct RXFlagStruct{
  enum RxConfigMessageType {                                                    //!< Flags for config change sequence
    RECEIVED_NO_CONFIG_CHANGE         = 0,
    RECEIVED_CONFIG_REQUEST           = BIT0,
    RECEIVED_CONFIG_PING              = BIT1,
    RECEIVED_CONFIG_ACK               = BIT2
  } RxConfigMessageType;
  enum RxPayloadMessageType {                                                   //!< Flags for payload transfer
    RECEIVED_NO_PAYLOAD               = 0,
    RECEIVED_PAYLOAD                  = 1
  } RxPayloadMessageType;
  enum RxACKMessageType {                                                       //!< Flags to ACK transfer
    RECEIVED_NO_ACK                   = 0,
    RECEIVED_ACK                      = 1
  } RxACKMessageType;
}RXFlagStruct;

extern AppRadio radio[];
extern uint8_t const radio_Count;
extern NodeInfo Nodes[];

/**
 * @details ISR extension of Communication Module 1 ISR. This functionality is
 *          currently not implemented.
 */
void RadioOperation(void);

/**
 * @details Initialize Radio settings to default
 */
void InitRadio(AppRadio * radio);

/**
 * @details Return pointer to the current RadioArraySizes structure
 */
AppRadioArraySizes * pCurrentRadioArraySizesStruct(uint8_t currentRadio);

/**
 * @details Return pointer to the current ConfigSettings structure
 */
ConfigStruct * pCurrentConfigSettingsStruct(void);

/**
 * @details Return pointer to the current RadioConfiguration structure
 */
AppRadioConfiguration * pCurrentRadioConfigurationStruct(void);

/**
 * @details Return the pointer of current Framework Radio
 */
Radio * pCurrentFrameworkRadio(void);

/**
 * @details Return the index of current Radio
 */
uint8_t CurrentRadio(void);

/**
 * @details Return the index of current Configuration
 */
uint8_t CurrentBaseConfig(void);

/**
 * @details Return the index of current Channel
 */
uint8_t CurrentChannel(void);

/**
 * @details Return the index of current Power
 */
uint8_t CurrentPower(void);

/**
 * @details Change current configuration
 */
uint8_t ChangeConfiguration(uint8_t remote, uint8_t radioIndex, uint8_t configIndex, uint8_t channelIndex, uint8_t powerIndex);

/**
 * @details Send a Frame
 */
uint8_t FrameSend(AppRadio * radio, uint8_t * pBuffer, uint8_t count, uint16_t timeout, uint8_t timeoutAction);

/**
 * @details Listen to receive a Frame
 */
uint8_t FrameListen(AppRadio * radio, uint8_t * pBuffer, uint8_t * pCount, uint16_t timeout, uint8_t timeoutAction);

/**
 * @details Read the received Frame
 */
uint8_t GetFrame(AppRadio * radio, uint8_t * pBuffer, uint8_t * pCount);

/**
 * @details Radio reset
 */
uint8_t PowerUpResetCCxxxx(AppRadio * radio);

/**
 * @details Read the current MARCSTATE of the Radio
 */
uint8_t ReadMARCSTATE(AppRadio * radio);

/**
 * @details Put radio in Receive mode
 */
void ReceiveOn(AppRadio * radio);

/**
 * @details Process the received packet to set necessary flags
 */
void RXPacketProcessing(uint8_t * pBuffer);

/**
 * @details Perform the Timeout action
 */
void CycleTimeoutAction(AppRadio * radio, uint8_t action);

/**
 * @details Create the data packet to be sent
 */
void CreateDataPacket(uint8_t * pBufferIn, uint8_t countIn, uint8_t * pBufferOut, uint8_t * countOut);

/**
 * @details This function shifts the RSSI value to have the decimal point between the
 *          the two bytes in the integer and adds offset to it(see CC110L datasheet).
 */
signed int RSSI2dBm(unsigned char rssi);

extern void Query_Current_Status(PayloadFrame *payload);
extern unsigned char SetCycleTime(unsigned char ID, unsigned int newCycleTime);

#define SYNC_TIMEOUT pCurrentRadioConfigurationStruct()->pRegisterSettings->configCycleTimeout.syncTimeout
#define EOP_TIMEOUT pCurrentRadioConfigurationStruct()->pRegisterSettings->configCycleTimeout.EOPTimeout
#define CONFIG_TIMEOUT Nodes[0].CurrentCycleTime

#define SYNC_TIMEOUT_ACTION SET_RADIO_SLEEP
#define EOP_TIMEOUT_ACTION SET_RADIO_IDLE
#define CONFIG_TIMEOUT_ACTION SET_RADIO_IDLE

#endif  // __APP_RADIOOPERATION_H
