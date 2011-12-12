/**
 *  @file CC2500Settings.h
 *
 *  @brief Configuration, Channel and Power settings for CC2500
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
#ifndef __APP_CC2500SETTINGS_H
#define __APP_CC2500SETTINGS_H

#include "RadioOperation.h"


#ifdef RADIO_FULL_TEXT_DESCRIPTIONS
  #define ChannelDefine(ChanNr,Description) ChanNr, Description
  #define PowerDefine(PowerSetting,Description) PowerSetting, Description
  #define PowerDefineAllSame(PowerSetting,Description) PowerSetting,PowerSetting,PowerSetting,PowerSetting,PowerSetting,PowerSetting,PowerSetting,PowerSetting, Description
#else
  #define ChannelDefine(ChanNr,Description) ChanNr
  #define PowerDefine(PowerSetting,Description) PowerSetting
  #define PowerDefineAllSame(PowerSetting,Description) PowerSetting,PowerSetting,PowerSetting,PowerSetting,PowerSetting,PowerSetting,PowerSetting,PowerSetting
#endif


/**
 * @brief Application RF Connection
 */
RFConnection RadioConnection = {
  EXTERNAL,                                                                     //!< Connection
  IRFSPI,                                                                       //!< Connection type
  USCIB0,                                                                       //!< Connection peripheral
  {__BOARD_RADIO1_CSNPORT, __BOARD_RADIO1_CSNPIN},                              //!< CSN {port, pin}
  {__BOARD_RADIO1_MOSIPORT, __BOARD_RADIO1_MOSIPIN},                            //!< MOSI {port, pin}
  {__BOARD_RADIO1_MISOPORT, __BOARD_RADIO1_MISOPIN},                            //!< MISO {port, pin}
  {__BOARD_RADIO1_SCLKPORT, __BOARD_RADIO1_SCLKPIN},                            //!< SCLK {port, pin}
  {__BOARD_RADIO1_GDO0PORT, __BOARD_RADIO1_GDO0PIN},                            //!< GDO0 {port, pin}
  {__BOARD_RADIO1_GDO2PORT, __BOARD_RADIO1_GDO2PIN}                             //!< GDO2 {port, pin}
};

/**
 * @brief Application Radio Settings - FCC Approved
 */
AppRegisterSettings RadioRegisterSettingsFCC[] = {
  // RadioRegisterSettingsFCC[0] - 38.4kBaud, 2FSK, 2400MHz
  {
    {
      0x2E,               // GDO2 output pin configuration.                     
      0x2E,               // GDO1 output pin configuration.
      0x06,               // GDO0 output pin configuration.
      0x07,               // RXFIFO and TXFIFO thresholds.
      0xD3,               // Sync word, high byte
      0x91,               // Sync word, low byte
      0xFF,               // Packet length.                                      
      0x0C,               // Packet automation control.                          
      0x05,               // Packet automation control.
      0x00,               // Device address.
      0x00,               // Channel number.
      0x10,               // Frequency synthesizer control.
      0x00,               // Frequency synthesizer control.
      0x5C,               // Frequency control word, high byte.
      0x5B,               // Frequency control word, middle byte.
      0x91,               // Frequency control word, low byte.
      0x4A,               // Modem configuration.
      0x7F,               // Modem configuration.
      0x83,               // Modem configuration.
      0x23,               // Modem configuration.
      0x83,               // Modem configuration.
      0x63,               // Modem deviation setting (when FSK modulation is enabled).
      0x07,               // Main Radio Control State Machine configuration.
      0x00,               // Main Radio Control State Machine configuration.    
      0x18,               // Main Radio Control State Machine configuration.
      0x1D,               // Frequency Offset Compensation Configuration.
      0x1C,               // Bit synchronization Configuration.
      0xc7,               // AGC control.
      0x00,               // AGC control.
      0xb0,               // AGC control.
      0x87,               // High byte Event 0 timeout
      0x6B,               // Low byte Event 0 timeout
      0xF8,               // Wake On Radio control
      0x57,               // Front end RX configuration.
      0x10,               // Front end RX configuration.
      0xa9,               // Frequency synthesizer calibration.
      0x0A,               // Frequency synthesizer calibration.
      0x00,               // Frequency synthesizer calibration.
      0x11,               // Frequency synthesizer calibration.
      0x41,               // RC oscillator configuration
      0x00,               // RC oscillator configuration  
      0x59,               // Frequency synthesizer calibration control
      0x7F,               // Production test
      0x3F,               // AGC test
      0x88,               // Various test settings.
      0x31,               // Various test settings.
      0x0b,               // Various test settings.
    },
    #ifdef RADIO_FULL_TEXT_DESCRIPTIONS
      "38.4kb/s, 2FSK"    // Description
    #endif
    ,{
      3000,               // Minimum Update Period: 500ms at 12kHz (TA3.out has twice the period and is used to start ADC sample)
      120,                // Syncword Timeout: 6ms at 20kHz (4.4ms + 25% margin rounded off)
      340                 // EOP Timeout: 17ms at 20kHz (13.3ms + 25% margin rounded off)
    }
  },
  // RadioRegisterSettingsFCC[1] - 250kBaud, 2FSK, 2400MHz
  {
    {
      0x2E,               // GDO2 output pin configuration.                     
      0x2E,               // GDO1 output pin configuration.
      0x06,               // GDO0 output pin configuration.
      0x07,               // RXFIFO and TXFIFO thresholds.
      0xD3,               // Sync word, high byte
      0x91,               // Sync word, low byte
      0xFF,               // Packet length.                                     
      0x0C,               // Packet automation control.                         
      0x05,               // Packet automation control.
      0x00,               // Device address.
      0x00,               // Channel number.
      0x0D,               // Frequency synthesizer control.
      0x00,               // Frequency synthesizer control.
      0x22,               // Frequency control word, high byte.
      0xB6,               // Frequency control word, middle byte.
      0x27,               // Frequency control word, low byte.
      0x2D,               // Modem configuration.
      0x83,               // Modem configuration.
      0x03,               // Modem configuration.
      0x21,               // Modem configuration.
      0xEE,               // Modem configuration.
      0x65,               // Modem deviation setting (when FSK modulation is enabled).
      0x07,               // Main Radio Control State Machine configuration.
      0x00,               // Main Radio Control State Machine configuration.    
      0x18,               // Main Radio Control State Machine configuration.
      0x16,               // Frequency Offset Compensation Configuration.
      0x6C,               // Bit synchronization Configuration.
      0x47,               // AGC control.
      0x40,               // AGC control.
      0x91,               // AGC control.
      0x87,               // High byte Event 0 timeout
      0x6B,               // Low byte Event 0 timeout
      0xF8,               // Wake On Radio control
      0xB7,               // Front end RX configuration.
      0x10,               // Front end RX configuration.
      0xE9,               // Frequency synthesizer calibration.
      0x2A,               // Frequency synthesizer calibration.
      0x00,               // Frequency synthesizer calibration.
      0x1F,               // Frequency synthesizer calibration.
      0x41,               // RC oscillator configuration
      0x00,               // RC oscillator configuration  
      0x59,               // Frequency synthesizer calibration control
      0x7F,               // Production test
      0x3F,               // AGC test
      0x88,               // Various test settings.
      0x35,               // Various test settings.
      0x09,               // Various test settings.
    },
    #ifdef RADIO_FULL_TEXT_DESCRIPTIONS
      "250kb/s, 2FSK"     // Description
    #endif
    ,{
      3000,               // Minimum Update Period: 500ms at 12kHz (TA3.out has twice the period and is used to start ADC sample)
      120,                // Syncword Timeout: 6ms at 20kHz (4.4ms + 25% margin rounded off)
      340                 // EOP Timeout: 17ms at 20kHz (13.3ms + 25% margin rounded off)
    }
  } 
 };

/**
 * @brief Application RF Power Settings
 */
AppRadioPowerList RadioPowerListFCC[] = {
  { PowerDefineAllSame(0xC0,"12.6") },
  { PowerDefineAllSame(0xC1,"12.2") },
  { PowerDefineAllSame(0xC2,"11.9") },
  { PowerDefineAllSame(0xC3,"11.5") },
  { PowerDefineAllSame(0xC4,"11.2") },
  { PowerDefineAllSame(0xC5,"10.7") },
  { PowerDefineAllSame(0xC6,"10.4") },
  { PowerDefineAllSame(0xC7,"10.0") },
  { PowerDefineAllSame(0xC8,"9.6") },
  { PowerDefineAllSame(0xC9,"9.3") },
  { PowerDefineAllSame(0xCA,"8.9") },
  { PowerDefineAllSame(0xCB,"8.5") },
  { PowerDefineAllSame(0xCC,"8.1") },
  { PowerDefineAllSame(0xCD,"7.7") },
  { PowerDefineAllSame(0xCE,"6.9") },
  { PowerDefineAllSame(0x88,"3.0") },
  { PowerDefineAllSame(0x8D,"0.5") },
  { PowerDefineAllSame(0x65,"-3.7") },
  { PowerDefineAllSame(0x69,"-6.4") },
  { PowerDefineAllSame(0x1B,"-17.7") },
  { PowerDefineAllSame(0x03,"-30") },
  { PowerDefineAllSame(0x00,"-60") }
};

/**
 * @brief Application RF Channels
 */
AppRadioChannelList RadioChannelListFCC[] = {
  { ChannelDefine(0x00,"902.81") },
  { ChannelDefine(0x10,"904.34") },
  { ChannelDefine(0x20,"905.87") },
  { ChannelDefine(0x30,"907.40") },
  { ChannelDefine(0x40,"908.93") },
  { ChannelDefine(0x50,"910.46") },
  { ChannelDefine(0x60,"911.99") },
  { ChannelDefine(0x70,"913.52") },
  { ChannelDefine(0x80,"915.05") },
  { ChannelDefine(0x90,"916.58") },
  { ChannelDefine(0xA0,"918.11") },
  { ChannelDefine(0xB0,"919.64") },
  { ChannelDefine(0xC0,"921.17") },
  { ChannelDefine(0xD0,"922.70") },
  { ChannelDefine(0xE0,"924.23") },
  { ChannelDefine(0xF0,"925.76") },
  { ChannelDefine(0xFF,"927.19") }
};

/**
 * @brief Application RF Channel-Power Settings
 */
AppRadioChannel RadioConfigurationChannelsFCC[] = {
  {0,0},                  // Channel[0], Power[0]
  {1,0},                  // Channel[1], Power[0]
  {2,0},                  // Channel[2], Power[0]
  {3,0},                  // Channel[3], Power[0]
  {4,0},                  // Channel[4], Power[0]
  {5,0},                  // Channel[5], Power[0]
  {6,0},                  // Channel[6], Power[0]
  {7,0},                  // Channel[7], Power[0]
  {8,0},                  // Channel[8], Power[0]
  {9,0},                  // Channel[9], Power[0]
  {10,0},                 // Channel[10], Power[0]
  {11,0},                 // Channel[11], Power[0]
  {12,0},                 // Channel[12], Power[0]
  {13,0},                 // Channel[13], Power[0]
  {14,0},                 // Channel[14], Power[0]
  {15,0},                 // Channel[15], Power[0]
  {16,0}                  // Channel[16], Power[0]
};

/**
 * @brief Application Radio Configurations
 */
AppRadioConfiguration RadioConfigurationFCC[] = {
  {
    &RadioRegisterSettingsFCC[0],
    &RadioConfigurationChannelsFCC[0],
    sizeof(RadioConfigurationChannelsFCC)/sizeof(AppRadioChannel),
  },
  {
    &RadioRegisterSettingsFCC[1],
    &RadioConfigurationChannelsFCC[0],
    sizeof(RadioConfigurationChannelsFCC)/sizeof(AppRadioChannel),
  }
 
};

/**
 * @brief Application Radio Array Sizes
 */
AppRadioArraySizes RadioArraySizesFCC = {
  sizeof(RadioConfigurationFCC)/sizeof(AppRadioConfiguration),
  sizeof(RadioChannelListFCC)/sizeof(AppRadioChannelList),
  sizeof(RadioPowerListFCC)/sizeof(AppRadioPowerList),
  sizeof(AppRegisterSettings),
  sizeof(AppRadioChannelList),
  sizeof(AppRadioPowerList)
};

#endif  // __APP_CC2500SETTINGS_H
