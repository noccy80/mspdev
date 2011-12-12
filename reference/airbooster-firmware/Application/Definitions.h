/**
 *  @file Definitions.h
 *
 *  @brief Defines for Application files
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

#ifndef __APP_DEFINITIONS_H
#define __APP_DEFINITIONS_H

// Defines 
#define CRC_OK                  0x80                                            //!< CRC okay
#define RSSI                    0                                               //!< Received Signal Strength Indicator 
#define LQI                     1                                               //!< Link Quality Indicator
#define BYTES_IN_RXFIFO         0x7F                                            //!< Number of bytes in RX_FIFO      
#define FALSE                   0x00                                            //!< Simple true/false constants
#define TRUE                    0x01                                            //!< Simple true/false constants
#define CLEAR                   0x00                                            //!< Reset to zero  
#define BIT_CLEAR	        0x00                                            //!< Clear the bit  
#define TX_MODE                 0x00                                            //!< Transmit mode
#define RX_MODE                 0x01                                            //!< Receive mode
#define NUMCONFIG	        6                                               //!< Maximum number of configurations supported
#define	NUMREG_PER_CONFIG       48                                              //!< Number of configuration registers            
#define	CONFIG_ARRAY_SIZE       NUMCONFIG * NUMREG_PER_CONFIG                   //!< Size of configuration array
#define HEADER_LENGTH           11                                              //!< Length of frame header                            
#define MAX_FRAME_LENGTH        26                                              //!< Maximum legnth of frame
#define MAX_PAYLOAD_LENGTH      MAX_FRAME_LENGTH - HEADER_LENGTH                //!< Maximum length of payload in the frame

/**
 * @brief Timeout Action Enumerations
 */
enum TIMEOUT_ACTION{
  SET_RADIO_SLEEP,
  SET_RADIO_IDLE
};

// Defines for CCxxx
#define CC2500_REG_PARTNUM      0x80                                            //!< Part number for CC2500		
#define CC2500_REG_VER_NUM      0x03                                            //!< Version number for CC2500			
#define CC1101_REG_PARTNUM      0x00                                            //!< Part number for CC1101	
#define CC1101_REG_VER_NUM      0x04                                            //!< Version number for CC1101
#define CC110L_REG_PARTNUM      0x00                                            //!< Part number for CC110L
#define CC110L_REG_VER_NUM      0x07                                            //!< Version number for CC110L

//!< Defines for the data packet indices
#define LENGTH                  0                                               //!< Frame Length
#define DESTINATION_ADDR        1                                               //!< Destination Address
#define SOURCE_ID               2                                               //!< Source ID
#define NEW_RADIO_INDEX         3                                               //!< New Radio Index fot Radio Change 
#define NEW_CONFIG_INDEX        4                                               //!< New Configuration Index for Configuration Change
#define NEW_CHANNEL_INDEX       5                                               //!< New Channel Index for Channel Change
#define NEW_POWER_COMMAND       6                                               //!< New Power Index for Power Change and Command if the payload is a command
#define RSSI_RECEIVER           7                                               //!< RSSI at receiver
#define LQI_RECEIVER            8                                               //!< LQI at receiver
#define FREQ_OFFSET_RECEIVER    9                                               //!< Frequency Offset at receiver
#define CURRENT_POWER_INDEX     10                                              //!< Current Power Index

#endif //__APP_DEFINITIONS_H
