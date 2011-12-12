/**
 *  @file Application.h
 *
 *  @brief Application Layer Function Declarations
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

#ifndef __APP_APPLICATION_H
#define __APP_APPLICATION_H

#if defined(__BOARD_EZ430_SERIES)
  #define __BOARD_MODESWITCH __BOARD_SWITCH1
  #define __BOARD_MODESWITCH_PIN __BOARD_SWITCH1_PIN
#elif defined(__BOARD_LAUNCHPAD_SERIES)
  #define __BOARD_MODESWITCH __BOARD_SWITCH2
  #define __BOARD_MODESWITCH_PIN __BOARD_SWITCH2_PIN
#endif

#define __APPLICATION_NAME "Application"                                        //!< Module Display Name
#define __APPLICATION_VERSION   1                                               //!< Module Version
#define __APPLICATION_REVISION  0                                               //!< Module Revision
#define __APPLICATION_DESCRIPTION "Sensor-Hub P2P and Star Demo"                //!< Module Description


/**
 *  @brief Flash memory location definitions.
 */
#define INCLUDE_FLASH_STORAGE
#ifdef INCLUDE_FLASH_STORAGE

/**
 * @brief For the flash storage of the Radio, Settings, Channel and Power we 
 *          so far have been using
 */
typedef struct RadioSettingChannelPower {
  unsigned char Radio;
  unsigned char Setting;
  unsigned char Channel;
  unsigned char Power;
} RadioSettingChannelPower;

/**
 * @brief Application state enumerations
 */
typedef enum __ApplicationState {
  SENSOR = 0,
  HUB = 1,
} __ApplicationState;

// These static address depend on the processor
__no_init volatile unsigned char MyFlashedID[4] @ 0x1000;                       //!< Flash storage of our own device address
__no_init volatile unsigned char MyFlashedPairedID[4] @ 0x1004;                 //!< Flash storage of the device we so far have been paired to
__no_init volatile RadioSettingChannelPower MyFlashedRSCP @ 0x1008;             //!< Flash storage of the Radio, Settings, Channel and Power we so far have been using
__no_init volatile unsigned char MyFlashedAppState @ 0x1010;                    //!< Flash storage of the application state

#endif

#define DEFAULT_SENSOR_ID    0x5A5A5A5A
#define DEFAULT_HUB_ID       0x12345678
#define DEFAULT_PAIRING_MASK 0x00000000                                         //!< Startup defult pairing behavior, 0x00000000 requires manual intervention and 0xFFFFFFFF will automatically allow any
#define MAX_NODES 5                                                             //!< Note that Node index 0 is always the local node, thus the max number of external nodes are MAX_NODES-1

/**
 * @brief Payload Flags
 */
typedef struct PayloadFlags {
  unsigned char PairingSolicitation : 1;
  unsigned char MsgCounter : 7;
} PayloadFlags;

#define DATA_CHANNELS 2

/**
 * @brief Payload Frame
 */
typedef struct PayloadFrame {                                                   // Right now this must be exactly 10, as its hardcoded in lower levels
  unsigned long NodeID;
  unsigned int Data[DATA_CHANNELS];
  PayloadFlags Flags;
  unsigned int CycleTime;
} PayloadFrame;

#define PAYLOAD_SIZE_VALIDATION ((sizeof(PayloadFrame) < MAX_PAYLOAD_LENGTH) ? 1 : -1)
#define INCLUDE_FRAMECOUNTER_STATUS
#define INCLUDE_RSSI_STATUS

/**
 * @brief Node Information
 */
typedef struct NodeInfo {
  unsigned long ID;
  unsigned int CurrentCycleTime;
  volatile unsigned int InData[DATA_CHANNELS];
  unsigned int OutData[DATA_CHANNELS];
  unsigned char LastRSSI;
  #ifdef INCLUDE_LQI_STATUS
    unsigned char LastLocalLQI;
    unsigned char LastRemoteLQI;
  #endif
  #ifdef INCLUDE_FREQOFF_STATUS
    unsigned char LastLocalFoff;
    unsigned char LastRemoteFoff;
  #endif
  #ifdef INCLUDE_POWER_STATUS
    unsigned char LastLocalPower;
    unsigned char LastRemotePower;
  #endif
  #ifdef INCLUDE_CHANNEL_STATUS
    unsigned char LastUsedChannel;
  #endif
  #ifdef INCLUDE_FRAMECOUNTER_STATUS
    unsigned char FrameCounter;
    unsigned char LastFrameCounter;
  #endif
} NodeInfo;


extern __ApplicationState ApplicationState;

/**
 * @details Listen for incomming data, network qualification and data presenting
 */
uint8_t HubWirelessOperation(void);

/**
 * @details Initiates a data exchange, network qualification and data presenting 
 *          of incomming data
 */
uint8_t SensorWirelessOperation(void);

/**
 * @details Write the application state into Flash
 */
uint8_t SetApplicationState(__ApplicationState state);

/**
 * @details Flash pairing mechanism prototypes. Write my ID into Flash
 */
void WriteMyFlashedID(unsigned long ID);

/**
 * @details Write the ID of device paired with me, into Flash
 */
void WriteMyFlashedPairedID(unsigned long ID);

/**
 * @details Write my Radio, Config, Channel and Power indices into Flash
 */
void WriteMyFlashedRSCP(unsigned char Radio, unsigned char Setting, unsigned char Channel, unsigned char Power);

/**
 * @details Read my ID from Flash
 */
unsigned long ReadMyFlashedID(void);

/**
 * @details Read the ID of the device paired with me, from Flash
 */
unsigned long ReadMyFlashedPairedID(void);

/**
 * @details Create random address for pairing
 */
unsigned long CreateRandomAddress(void);

/**
 * @details Initialize Application
 */
void InitApplication(unsigned long addr);

/**
 * @details Set pairing mask
 */
void SetPairingMask(unsigned long mask);

/**
 * @details Set my node ID
 */
unsigned char SetMyNodeID(unsigned long NodeID);

/**
 * @details Get my pairing mask
 */
unsigned long GetPairingMask(void);

/**
 * @details Check if the node is in my net
 */
unsigned char NodeIsInMyNet(unsigned long NodeID);

/**
 * @details Add the node to my network
 */
unsigned char AddNodeToNetwork(unsigned long NodeID);

/**
 * @details Remove the node from my network
 */
unsigned char RemoveNodeFromNetwork(unsigned char NodeID_index);

/**
 * @details Validate my network
 */
unsigned char NetworkValidation(PayloadFrame *AppFrame);

/**
 * @details Create ACK/payload frame
 */
PayloadFrame *NodeAckPayload(unsigned long NodeID);

/**
 * @details Create Sensor payload frame
 */
PayloadFrame *SensorPayload(void);

#endif  // __APP_APPLICATION_H
