/**
 *  @file CC110LSettings.h
 *
 *  @brief Configuration, Channel and Power settings for CC110L 
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

#ifndef __APP_CC110LSETTINGS_H
#define __APP_CC110LSETTINGS_H

#include "RadioOperation.h"


#ifdef RADIO_FULL_TEXT_DESCRIPTIONS
  #define ChannelDefine(freq2, freq1,freq0,description) freq2, freq1, freq0, description
  #define PowerDefine(powerSetting, description) powerSetting, description
  #define PowerDefineAllSame(powerSetting, description) powerSetting, powerSetting, description
#else
  #define ChannelDefine(freq2, freq1, freq0, description) freq2, freq1, freq0
  #define PowerDefine(powerSetting, description) powerSetting
  #define PowerDefineAllSame(powerSetting, description) powerSetting, powerSetting
#endif


/**
 *  @brief Application RF Connection
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
 * @brief Application Radio Settings - Pre-ETSI Approval
 */
AppRegisterSettings RadioRegisterSettingsETSI[] = {
  {
    // This one makes the Band 4, 1% duty cycle with sensor updates > 1.2s, we currently use 1.5!
    /* ETSI:M7_GFSK_38kB_18kHzDev_70kHzRxBW.  Deviation = 18.127441 .  Base frequency = 867.999985 .  Modulated = true .  Modulation format = GFSK .  Manchester enable = false .  Sync word qualifier mode = 30/32 sync word bits detected .  Preamble count = 4 .  Data rate = 38.0058 .  RX filter BW = 70.312500 .  Data format = Normal mode .  CRC enable = true .  Device address = 0 .  Address config = No address check .  Address config = No address check .  CRC autoflush = false .  Deviation = 18.127441 .  PA ramping = false . */
    {
      0x2E,               // IOCFG2*, GDO2 output pin configuration.
      0x2E,               // IOCFG1,  GDO1 output pin configuration.
      0x06,               // IOCFG0,  GDO0 output pin configuration.
      0x07,               // FIFOTHR,  RXFIFO and TXFIFO thresholds.
      0xD3,               // SYNC1, Sync word, high byte
      0x91,               // SYNC0, Sync word, low byte
      0xFF,               // PKTLEN*,  Packet length.
      0x0C,               // PKTCTRL1*, Packet automation control.
      0x05,               // PKTCTRL0, Packet automation control.
      0x00,               // ADDR, Device address.
      0x00,               // CHANNR, Channel number.
      0x06,               // FSCTRL1, Frequency synthesizer control.
      0x00,               // FSCTRL0, Frequency synthesizer control.
      0x20,               // FREQ2, Frequency control word, high byte.
      0x25,               // FREQ1, Frequency control word, middle byte.
      0xED,               // FREQ0, Frequency control word, low byte.
      0xEA,               // MDMCFG4, Modem configuration.
      0x71,               // MDMCFG3, Modem configuration.
      0x13,               // MDMCFG2,  Modem configuration.
      0x20,               // MDMCFG1,  Modem configuration.
      0xF8,               // MDMCFG0,  Modem configuration.
      0x33,               // DEVIATN,  Modem deviation setting (when FSK modulation is enabled).
      0x07,               // MCSM2, Main Radio Control State Machine configuration.
      0x00,               // MCSM1*, Main Radio Control State Machine configuration.
      0x18,               // MCSM0, Main Radio Control State Machine configuration.
      0x16,               // FOCCFG, Frequency Offset Compensation Configuration.
      0x6C,               // BSCFG, Bit synchronization Configuration.
      0x43,               // AGCCTRL2, AGC control.
      0x4F,               // AGCCTRL1, AGC control.
      0x91,               // AGCCTRL0, AGC control.
      0x00,               // WOREVT1, High byte Event 0 timeout
      0x00,               // WOREVT0, Low byte Event 0 timeout
      0xF8,               // WORCTRL, Wake On Radio control
      0x56,               // FREND1, Front end RX configuration.
      0x10,               // FREND0, Front end RX configuration.
      0xE9,               // FSCAL3, Frequency synthesizer calibration.
      0x2A,               // FSCAL2, Frequency synthesizer calibration.
      0x00,               // FSCAL1, Frequency synthesizer calibration.
      0x1F,               // FSCAL0, Frequency synthesizer calibration.
      0x00,               // RCCTRL1, RC oscillator configuration
      0x00,               // RCCTRL0, RC oscillator configuration  
      0x59,               // FSTEST, Frequency synthesizer calibration control
      0x7F,               // PTEST, Production test
      0x3F,               // AGCTEST, AGC test
      0x81,               // TEST2, Various test settings.
      0x35,               // TEST1, Various test settings.
      0x09,               // TEST0, Various test settings.
    },
    #ifdef RadioFullTextDescriptions
      "ETSI:B4,10,12, 1%, M7_GFSK_38kB_18kHzDev_70kHzRxBW"  // Description
    #endif
    ,{
      4500,               // Minimum Update Period: 750ms at 12kHz (TA3.out has twice the period and is used to start ADC sample)
      120,                // Syncword Timeout: 6ms at 20kHz (4.4ms + 25% margin rounded off)
      340,                // EOP Timeout: 17ms at 20kHz (13.3ms + 25% margin rounded off)
    }
  },
  {
    /* ETSI:M12_GFSK_4.8kB_13kHzDev_60kHzRxBW.  Deviation = 13.183594 .  Base frequency = 867.999985 .  Modulated = true .  Modulation format = GFSK .  Manchester enable = false .  Sync word qualifier mode = 30/32 sync word bits detected .  Preamble count = 4 .  Data rate = 4.80223 .  RX filter BW = 60.267857 .  Data format = Normal mode .  CRC enable = true .  Device address = 0 .  Address config = No address check .  Address config = No address check .  CRC autoflush = false .  Deviation = 13.183594 .  PA ramping = false . */
    {
      0x2E,               // IOCFG2*, GDO2 output pin configuration.
      0x2E,               // IOCFG1,  GDO1 output pin configuration.
      0x06,               // IOCFG0,  GDO0 output pin configuration.
      0x07,               // FIFOTHR,  RXFIFO and TXFIFO thresholds.
      0xD3,               // SYNC1, Sync word, high byte
      0x91,               // SYNC0, Sync word, low byte
      0xFF,               // PKTLEN*,  Packet length.
      0x0C,               // PKTCTRL1*, Packet automation control.
      0x05,               // PKTCTRL0, Packet automation control.
      0x00,               // ADDR, Device address.
      0x00,               // CHANNR, Channel number.
      0x05,               // FSCTRL1, Frequency synthesizer control.
      0x00,               // FSCTRL0, Frequency synthesizer control.
      0x20,               // FREQ2, Frequency control word, high byte.
      0x25,               // FREQ1, Frequency control word, middle byte.
      0xED,               // FREQ0, Frequency control word, low byte.
      0xF7,               // MDMCFG4, Modem configuration.
      0x75,               // MDMCFG3, Modem configuration.
      0x13,               // MDMCFG2,  Modem configuration.
      0x20,               // MDMCFG1,  Modem configuration.
      0xF8,               // MDMCFG0,  Modem configuration.
      0x30,               // DEVIATN,  Modem deviation setting (when FSK modulation is enabled).
      0x07,               // MCSM2, Main Radio Control State Machine configuration.
      0x00,               // MCSM1*, Main Radio Control State Machine configuration.
      0x18,               // MCSM0, Main Radio Control State Machine configuration.
      0x16,               // FOCCFG, Frequency Offset Compensation Configuration.
      0x6C,               // BSCFG, Bit synchronization Configuration.
      0x04,               // AGCCTRL2, AGC control.
      0x4F,               // AGCCTRL1, AGC control.
      0x91,               // AGCCTRL0, AGC control.
      0x00,               // WOREVT1, High byte Event 0 timeout
      0x00,               // WOREVT0, Low byte Event 0 timeout
      0xFB,               // WORCTRL, Wake On Radio control
      0x56,               // FREND1, Front end RX configuration.
      0x10,               // FREND0, Front end RX configuration.
      0xE9,               // FSCAL3, Frequency synthesizer calibration.
      0x2A,               // FSCAL2, Frequency synthesizer calibration.
      0x00,               // FSCAL1, Frequency synthesizer calibration.
      0x1F,               // FSCAL0, Frequency synthesizer calibration.
      0x00,               // RCCTRL1, RC oscillator configuration
      0x00,               // RCCTRL0, RC oscillator configuration  
      0x59,               // FSTEST, Frequency synthesizer calibration control
      0x7F,               // PTEST, Production test
      0x3F,               // AGCTEST, AGC test
      0x81,               // TEST2, Various test settings.
      0x35,               // TEST1, Various test settings.
      0x09,               // TEST0, Various test settings.
    },
    #ifdef RadioFullTextDescriptions
      "ETSI:B10, 10%, M12_GFSK_4.8kB_13kHzDev_60kHzRxBW"  // Description
    #endif
    ,{
      3360,               // Minimum Update Period: 560ms at 12kHz (TA3.out has twice the period and is used to start ADC sample)
      1400,               // Syncword Timeout: 70ms at 20kHz (56.0ms + 25% margin rounded off)
      3359,               // EOP Timeout: 550ms at 20kHz (426.7ms + 25% margin rounded off)  -  max out at CCR0 value - 1
    }
  },
};

/**
 * @brief Application RF Power Settings
 */
AppRadioPowerList RadioPowerListETSI[] = {
  { PowerDefineAllSame(0xC0,"10") },
  { PowerDefineAllSame(0xC2,"9") },
  { PowerDefineAllSame(0xC5,"8") },
  { PowerDefineAllSame(0xC8,"7") },
  { PowerDefineAllSame(0xCB,"6") },
  { PowerDefineAllSame(0xCD,"5") },
  { PowerDefineAllSame(0xCE,"4") },
  { PowerDefineAllSame(0x88,"3") },
  { PowerDefineAllSame(0x8D,"0") },
  { PowerDefineAllSame(0x65,"-3") },
  { PowerDefineAllSame(0x69,"-6") },
  { PowerDefineAllSame(0x1B,"-18") },
  { PowerDefineAllSame(0x03,"-30") },
  { PowerDefineAllSame(0x00,"-60") }
};

/**
 * @brief Application RF Channels
 */
AppRadioChannelList RadioChannelListETSI[] = {
  { ChannelDefine(0x20, 0x26, 0xDF, "868.10") },                                // Band 4, M7, Ch 2.
  { ChannelDefine(0x20, 0x27, 0x59, "868.15") },                                // Band 4, M7, Ch 3.
  { ChannelDefine(0x20, 0x27, 0xD2, "868.20") },                                // Band 4, M7, Ch 4.
  { ChannelDefine(0x20, 0x28, 0x4B, "868.25") },                                // Band 4, M7, Ch 5.
  { ChannelDefine(0x20, 0x28, 0xC5, "868.30") },                                // Band 4, M7, Ch 6.
  { ChannelDefine(0x20, 0x29, 0x3E, "868.35") },                                // Band 4, M7, Ch 7.
  { ChannelDefine(0x20, 0x34, 0x25, "869.50") },                                // Band 10, M12, M7, Ch 30.
  { ChannelDefine(0x20, 0x36, 0xFE, "869.80") },                                // Band 12, M7, Ch 36.
  { ChannelDefine(0x20, 0x37, 0x77, "869.85") },                                // Band 12, M7, Ch 37.
};

/**
 * @brief Application Radio Channel-Power Settings
 */
AppRadioChannel RadioConfigurationChannelsETSI_M7[] = {
  {0,0},                  // Channel[0], Power[0]
  {1,0},                  // Channel[1], Power[0]
  {2,0},                  // Channel[2], Power[0]
  {3,0},                  // Channel[3], Power[0]
  {4,0},                  // Channel[4], Power[0]
  {5,0},                  // Channel[5], Power[0]
  {6,0},                  // Channel[6], Power[0]
  {7,0},                  // Channel[7], Power[0]
  {8,0},                  // Channel[8], Power[0]
};

/**
 * @brief Application Radio Channel-Power Settings
 */
AppRadioChannel RadioConfigurationChannelsETSI_M12[] = {
  {6,0},                  // Channel[6], Power[0]
};

/**
 * @brief Application Radio Configurations
 */
AppRadioConfiguration RadioConfigurationETSI[] = {
  {
    &RadioRegisterSettingsETSI[0],
    &RadioConfigurationChannelsETSI_M7[0],
    sizeof(RadioConfigurationChannelsETSI_M7)/sizeof(AppRadioChannel),
  },
  {
    &RadioRegisterSettingsETSI[1],
    &RadioConfigurationChannelsETSI_M12[0],
    sizeof(RadioConfigurationChannelsETSI_M12)/sizeof(AppRadioChannel),
  },
};

AppRadioArraySizes RadioArraySizesETSI = {
  sizeof(RadioConfigurationETSI)/sizeof(AppRadioConfiguration),
  sizeof(RadioChannelListETSI)/sizeof(AppRadioChannelList),
  sizeof(RadioPowerListETSI)/sizeof(AppRadioPowerList),
  sizeof(AppRegisterSettings),
  sizeof(AppRadioChannelList),
  sizeof(AppRadioPowerList)
};

/**
 * @brief Application Radio Settings - Pre-FCC Approval
 */
AppRegisterSettings RadioRegisterSettingsFCC[] = {
  {
    /* FCC:ML4_2FSK_1_2kB_237kHzDev_675kHzRxBW.  Deviation = 237.304688 .  Base frequency = 902.299988 .  Modulated = true .  Modulation format = 2-FSK .  Manchester enable = false .  Sync word qualifier mode = 30/32 sync word bits detected .  Preamble count = 4 .  Data rate = 1.20056 .  RX filter BW = 675.000000 .  Data format = Normal mode .  CRC enable = true .  Device address = 0 .  Address config = No address check .  Address config = No address check .  CRC autoflush = false .  Deviation = 237.304688 .  PA ramping = false . */
    {
      0x2E,               // IOCFG2*, GDO2 output pin configuration.
      0x2E,               // IOCFG1,  GDO1 output pin configuration.
      0x06,               // IOCFG0,  GDO0 output pin configuration.
      0x07,               // FIFOTHR,  RXFIFO and TXFIFO thresholds.
      0xD3,               // SYNC1, Sync word, high byte
      0x91,               // SYNC0, Sync word, low byte
      0xFF,               // PKTLEN*,  Packet length.
      0x0C,               // PKTCTRL1*, Packet automation control.
      0x05,               // PKTCTRL0, Packet automation control.
      0x00,               // ADDR, Device address.
      0x00,               // CHANNR, Channel number.
      0x0C,               // FSCTRL1, Frequency synthesizer control.
      0x00,               // FSCTRL0, Frequency synthesizer control.
      0x21,               // FREQ2, Frequency control word, high byte.
      0x6B,               // FREQ1, Frequency control word, middle byte.
      0x24,               // FREQ0, Frequency control word, low byte.
      0x15,               // MDMCFG4, Modem configuration.
      0x75,               // MDMCFG3, Modem configuration.
      0x03,               // MDMCFG2,  Modem configuration.
      0x21,               // MDMCFG1,  Modem configuration.
      0xE5,               // MDMCFG0,  Modem configuration.
      0x71,               // DEVIATN,  Modem deviation setting (when FSK modulation is enabled).
      0x07,               // MCSM2, Main Radio Control State Machine configuration.
      0x00,               // MCSM1*, Main Radio Control State Machine configuration.
      0x18,               // MCSM0, Main Radio Control State Machine configuration.
      0x1D,               // FOCCFG, Frequency Offset Compensation Configuration.
      0x1C,               // BSCFG, Bit synchronization Configuration.
      0x47,               // AGCCTRL2, AGC control.
      0x40,               // AGCCTRL1, AGC control.
      0xB0,               // AGCCTRL0, AGC control.
      0x00,               // WOREVT1, High byte Event 0 timeout
      0x00,               // WOREVT0, Low byte Event 0 timeout
      0xF8,               // WORCTRL, Wake On Radio control
      0xB7,               // FREND1, Front end RX configuration.
      0x10,               // FREND0, Front end RX configuration.
      0xE9,               // FSCAL3, Frequency synthesizer calibration.
      0x2A,               // FSCAL2, Frequency synthesizer calibration.
      0x00,               // FSCAL1, Frequency synthesizer calibration.
      0x1F,               // FSCAL0, Frequency synthesizer calibration.
      0x00,               // RCCTRL1, RC oscillator configuration
      0x00,               // RCCTRL0, RC oscillator configuration  
      0x59,               // FSTEST, Frequency synthesizer calibration control
      0x7F,               // PTEST, Production test
      0x3E,               // AGCTEST, AGC test
      0x88,               // TEST2, Various test settings.
      0x31,               // TEST1, Various test settings.
      0x09,               // TEST0, Various test settings.
    },
    #ifdef RadioFullTextDescriptions
      "FCC:ML4_2FSK_1_2kB_237kHzDev_675kHzRxBW"  // Description
    #endif
    ,{
      6000,                // Minimum Update Period: 1sec at 12kHz (TA3.out has twice the period and is used to start ADC sample)
      1400,                // Syncword Timeout: 70ms at 20kHz (56.0ms + 25% margin rounded off)
      5999,                // EOP Timeout: 550ms at 20kHz (426.7ms + 25% margin rounded off)  -  max out at CCR0 value - 1
    }
  },
  {
    /* FCC:ML5_2FSK_38kB_237kHzDev_675kHzRxBW.  Deviation = 237.304688 .  Base frequency = 902.299988 .  Modulated = true .  Modulation format = 2-FSK .  Manchester enable = false .  Sync word qualifier mode = 30/32 sync word bits detected .  Preamble count = 4 .  Data rate = 38.0058 .  RX filter BW = 675.000000 .  Data format = Normal mode .  CRC enable = true .  Device address = 0 .  Address config = No address check .  Address config = No address check .  CRC autoflush = false .  Deviation = 237.304688 .  PA ramping = false . */
    {
      0x2E,               // IOCFG2*, GDO2 output pin configuration.
      0x2E,               // IOCFG1,  GDO1 output pin configuration.
      0x06,               // IOCFG0,  GDO0 output pin configuration.
      0x07,               // FIFOTHR,  RXFIFO and TXFIFO thresholds.
      0xD3,               // SYNC1, Sync word, high byte
      0x91,               // SYNC0, Sync word, low byte
      0xFF,               // PKTLEN*,  Packet length.
      0x0C,               // PKTCTRL1*, Packet automation control.
      0x05,               // PKTCTRL0, Packet automation control.
      0x00,               // ADDR, Device address.
      0x00,               // CHANNR, Channel number.
      0x0C,               // FSCTRL1, Frequency synthesizer control.
      0x00,               // FSCTRL0, Frequency synthesizer control.
      0x21,               // FREQ2, Frequency control word, high byte.
      0x6B,               // FREQ1, Frequency control word, middle byte.
      0x24,               // FREQ0, Frequency control word, low byte.
      0x1A,               // MDMCFG4, Modem configuration.
      0x71,               // MDMCFG3, Modem configuration.
      0x03,               // MDMCFG2,  Modem configuration.
      0x21,               // MDMCFG1,  Modem configuration.
      0xE5,               // MDMCFG0,  Modem configuration.
      0x71,               // DEVIATN,  Modem deviation setting (when FSK modulation is enabled).
      0x07,               // MCSM2, Main Radio Control State Machine configuration.
      0x00,               // MCSM1*, Main Radio Control State Machine configuration.
      0x18,               // MCSM0, Main Radio Control State Machine configuration.
      0x1D,               // FOCCFG, Frequency Offset Compensation Configuration.
      0x1C,               // BSCFG, Bit synchronization Configuration.
      0x47,               // AGCCTRL2, AGC control.
      0x40,               // AGCCTRL1, AGC control.
      0xB0,               // AGCCTRL0, AGC control.
      0x00,               // WOREVT1, High byte Event 0 timeout
      0x00,               // WOREVT0, Low byte Event 0 timeout
      0xF8,               // WORCTRL, Wake On Radio control
      0xB7,               // FREND1, Front end RX configuration.
      0x10,               // FREND0, Front end RX configuration.
      0xE9,               // FSCAL3, Frequency synthesizer calibration.
      0x2A,               // FSCAL2, Frequency synthesizer calibration.
      0x00,               // FSCAL1, Frequency synthesizer calibration.
      0x1F,               // FSCAL0, Frequency synthesizer calibration.
      0x00,               // RCCTRL1, RC oscillator configuration
      0x00,               // RCCTRL0, RC oscillator configuration  
      0x59,               // FSTEST, Frequency synthesizer calibration control
      0x7F,               // PTEST, Production test
      0x3F,               // AGCTEST, AGC test
      0x88,               // TEST2, Various test settings.
      0x31,               // TEST1, Various test settings.
      0x09,               // TEST0, Various test settings.
    },
    #ifdef RadioFullTextDescriptions
      "FCC:ML5_2FSK_38kB_237kHzDev_675kHzRxBW"  // Description
    #endif
    ,{
      3000,               // Minimum Update Period: 500ms at 12kHz (TA3.out has twice the period and is used to start ADC sample)
      120,                // Syncword Timeout: 6ms at 20kHz (4.4ms + 25% margin rounded off)
      340,                // EOP Timeout: 17ms at 20kHz (13.3ms + 25% margin rounded off)
    }
  },
  {
    /* FCC:ML6_2FSK_100kB_237kHzDev_675kHzRxBW.  Deviation = 237.304688 .  Base frequency = 902.299988 .  Modulated = true .  Modulation format = 2-FSK .  Manchester enable = false .  Sync word qualifier mode = 30/32 sync word bits detected .  Preamble count = 4 .  Data rate = 99.9069 .  RX filter BW = 675.000000 .  Data format = Normal mode .  CRC enable = true .  Device address = 0 .  Address config = No address check .  Address config = No address check .  CRC autoflush = false .  Deviation = 237.304688 .  PA ramping = false . */
    {
      0x2E,               // IOCFG2*, GDO2 output pin configuration.
      0x2E,               // IOCFG1,  GDO1 output pin configuration.
      0x06,               // IOCFG0,  GDO0 output pin configuration.
      0x07,               // FIFOTHR,  RXFIFO and TXFIFO thresholds.
      0xD3,               // SYNC1, Sync word, high byte
      0x91,               // SYNC0, Sync word, low byte
      0xFF,               // PKTLEN*,  Packet length.
      0x0C,               // PKTCTRL1*, Packet automation control.
      0x05,               // PKTCTRL0, Packet automation control.
      0x00,               // ADDR, Device address.
      0x00,               // CHANNR, Channel number.
      0x0D,               // FSCTRL1, Frequency synthesizer control.
      0x00,               // FSCTRL0, Frequency synthesizer control.
      0x21,               // FREQ2, Frequency control word, high byte.
      0x6B,               // FREQ1, Frequency control word, middle byte.
      0x24,               // FREQ0, Frequency control word, low byte.
      0x1B,               // MDMCFG4, Modem configuration.
      0xE5,               // MDMCFG3, Modem configuration.
      0x03,               // MDMCFG2,  Modem configuration.
      0x21,               // MDMCFG1,  Modem configuration.
      0xE5,               // MDMCFG0,  Modem configuration.
      0x71,               // DEVIATN,  Modem deviation setting (when FSK modulation is enabled).
      0x07,               // MCSM2, Main Radio Control State Machine configuration.
      0x00,               // MCSM1*, Main Radio Control State Machine configuration.
      0x18,               // MCSM0, Main Radio Control State Machine configuration.
      0x1D,               // FOCCFG, Frequency Offset Compensation Configuration.
      0x1C,               // BSCFG, Bit synchronization Configuration.
      0x47,               // AGCCTRL2, AGC control.
      0x40,               // AGCCTRL1, AGC control.
      0xB0,               // AGCCTRL0, AGC control.
      0x00,               // WOREVT1, High byte Event 0 timeout
      0x00,               // WOREVT0, Low byte Event 0 timeout
      0xF8,               // WORCTRL, Wake On Radio control
      0xB7,               // FREND1, Front end RX configuration.
      0x10,               // FREND0, Front end RX configuration.
      0xEA,               // FSCAL3, Frequency synthesizer calibration.
      0x2A,               // FSCAL2, Frequency synthesizer calibration.
      0x00,               // FSCAL1, Frequency synthesizer calibration.
      0x1F,               // FSCAL0, Frequency synthesizer calibration.
      0x00,               // RCCTRL1, RC oscillator configuration
      0x00,               // RCCTRL0, RC oscillator configuration  
      0x59,               // FSTEST, Frequency synthesizer calibration control
      0x7F,               // PTEST, Production test
      0x3F,               // AGCTEST, AGC test
      0x88,               // TEST2, Various test settings.
      0x31,               // TEST1, Various test settings.
      0x09,               // TEST0, Various test settings.
    },
    #ifdef RadioFullTextDescriptions
      "FCC:ML6_2FSK_100kB_237kHzDev_675kHzRxBW"  // Description
    #endif
    ,{
      3000,               // Minimum Update Period: 500ms at 12kHz (TA3.out has twice the period and is used to start ADC sample)
      120,                // Syncword Timeout: 6ms at 20kHz (4.4ms + 25% margin rounded off)
      340,                // EOP Timeout: 17ms at 20kHz (13.3ms + 25% margin rounded off)
    }
  },
  {
    /* FCC:ML7_2FSK_250kB_237kHzDev_844kHzRxBW.  Deviation = 237.304688 .  Base frequency = 902.299988 .  Modulated = true .  Modulation format = 2-FSK .  Manchester enable = false .  Sync word qualifier mode = 30/32 sync word bits detected .  Preamble count = 4 .  Data rate = 249.664 .  RX filter BW = 843.750000 .  Data format = Normal mode .  CRC enable = true .  Device address = 0 .  Address config = No address check .  Address config = No address check .  CRC autoflush = false .  Deviation = 237.304688 .  PA ramping = false . */
    {
      0x2E,               // IOCFG2*, GDO2 output pin configuration.
      0x2E,               // IOCFG1,  GDO1 output pin configuration.
      0x06,               // IOCFG0,  GDO0 output pin configuration.
      0x07,               // FIFOTHR,  RXFIFO and TXFIFO thresholds.
      0xD3,               // SYNC1, Sync word, high byte
      0x91,               // SYNC0, Sync word, low byte
      0xFF,               // PKTLEN*,  Packet length.
      0x0C,               // PKTCTRL1*, Packet automation control.
      0x05,               // PKTCTRL0, Packet automation control.
      0x00,               // ADDR, Device address.
      0x00,               // CHANNR, Channel number.
      0x0D,               // FSCTRL1, Frequency synthesizer control.
      0x00,               // FSCTRL0, Frequency synthesizer control.
      0x21,               // FREQ2, Frequency control word, high byte.
      0x6B,               // FREQ1, Frequency control word, middle byte.
      0x24,               // FREQ0, Frequency control word, low byte.
      0x0D,               // MDMCFG4, Modem configuration.
      0x2F,               // MDMCFG3, Modem configuration.
      0x03,               // MDMCFG2,  Modem configuration.
      0x21,               // MDMCFG1,  Modem configuration.
      0xE5,               // MDMCFG0,  Modem configuration.
      0x71,               // DEVIATN,  Modem deviation setting (when FSK modulation is enabled).
      0x07,               // MCSM2, Main Radio Control State Machine configuration.
      0x00,               // MCSM1*, Main Radio Control State Machine configuration.
      0x18,               // MCSM0, Main Radio Control State Machine configuration.
      0x1D,               // FOCCFG, Frequency Offset Compensation Configuration.
      0x1C,               // BSCFG, Bit synchronization Configuration.
      0xC7,               // AGCCTRL2, AGC control.
      0x40,               // AGCCTRL1, AGC control.
      0xB0,               // AGCCTRL0, AGC control.
      0x00,               // WOREVT1, High byte Event 0 timeout
      0x00,               // WOREVT0, Low byte Event 0 timeout
      0xF8,               // WORCTRL, Wake On Radio control
      0xB7,               // FREND1, Front end RX configuration.
      0x10,               // FREND0, Front end RX configuration.
      0xEA,               // FSCAL3, Frequency synthesizer calibration.
      0x2A,               // FSCAL2, Frequency synthesizer calibration.
      0x00,               // FSCAL1, Frequency synthesizer calibration.
      0x1F,               // FSCAL0, Frequency synthesizer calibration.
      0x00,               // RCCTRL1, RC oscillator configuration
      0x00,               // RCCTRL0, RC oscillator configuration  
      0x59,               // FSTEST, Frequency synthesizer calibration control
      0x7F,               // PTEST, Production test
      0x3C,               // AGCTEST, AGC test
      0x88,               // TEST2, Various test settings.
      0x31,               // TEST1, Various test settings.
      0x09,               // TEST0, Various test settings.
    },
    #ifdef RadioFullTextDescriptions
      "FCC:ML7_2FSK_250kB_237kHzDev_844kHzRxBW"  // Description
    #endif
    ,{
      3000,               // Minimum Update Period: 500ms at 12kHz (TA3.out has twice the period and is used to start ADC sample)
      120,                // Syncword Timeout: 6ms at 20kHz (4.4ms + 25% margin rounded off)
      340,                // EOP Timeout: 17ms at 20kHz (13.3ms + 25% margin rounded off)
    }
  },
};

/**
 * @brief Application RF Power Settings
 */
AppRadioPowerList RadioPowerListFCC[] = {
  { PowerDefineAllSame(0xC0,"10") },
  { PowerDefineAllSame(0xC4,"9") },
  { PowerDefineAllSame(0xC7,"8") },
  { PowerDefineAllSame(0xC9,"7") },
  { PowerDefineAllSame(0xCC,"6") },
  { PowerDefineAllSame(0xCE,"5") },
  { PowerDefineAllSame(0x88,"3") },
  { PowerDefineAllSame(0x8D,"0") },
  { PowerDefineAllSame(0x65,"-3") },
  { PowerDefineAllSame(0x69,"-6") },
  { PowerDefineAllSame(0x1B,"-18") },
  { PowerDefineAllSame(0x03,"-30") },
  { PowerDefineAllSame(0x00,"-60") }
};

/**
 * @brief Application RF Channels
 */
AppRadioChannelList RadioChannelListFCC[] = {
  { ChannelDefine(0x21, 0x6F, 0xF9, "902.81") },                                // FCC915, Ch 0.
  { ChannelDefine(0x21, 0x7E, 0x7A, "904.34") },                                // FCC915, Ch 16.
  { ChannelDefine(0x21, 0x8C, 0xFC, "905.87") },                                // FCC915, Ch 32.
  { ChannelDefine(0x21, 0x9B, 0x7D, "907.40") },                                // FCC915, Ch 48.
  { ChannelDefine(0x21, 0xA9, 0xFE, "908.93") },                                // FCC915, Ch 64.
  { ChannelDefine(0x21, 0xB8, 0x7F, "910.46") },                                // FCC915, Ch 80.
  { ChannelDefine(0x21, 0xC7, 0x00, "911.99") },                                // FCC915, Ch 96.
  { ChannelDefine(0x21, 0xD5, 0x81, "913.52") },                                // FCC915, Ch 112.
  { ChannelDefine(0x21, 0xE4, 0x02, "915.05") },                                // FCC915, Ch 128.
  { ChannelDefine(0x21, 0xF2, 0x83, "916.58") },                                // FCC915, Ch 144.
  { ChannelDefine(0x22, 0x01, 0x04, "918.11") },                                // FCC915, Ch 160.
  { ChannelDefine(0x22, 0x0F, 0x85, "919.64") },                                // FCC915, Ch 176.
  { ChannelDefine(0x22, 0x1E, 0x06, "921.17") },                                // FCC915, Ch 192.
  { ChannelDefine(0x22, 0x2C, 0x87, "922.70") },                                // FCC915, Ch 208.
  { ChannelDefine(0x22, 0x3B, 0x08, "924.23") },                                // FCC915, Ch 224.
  { ChannelDefine(0x22, 0x49, 0x89, "925.76") },                                // FCC915, Ch 240.
  { ChannelDefine(0x22, 0x57, 0x22, "927.19") },                                // FCC915, Ch 255.
};

/**
 * @brief Application Radio Channel-Power Settings
 */
AppRadioChannel RadioConfigurationChannelsFCC0[] = {
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
 * @brief Application Radio Channel-Power Settings
 */
AppRadioChannel RadioConfigurationChannelsFCC2[] = {
  {0,2},                  // Channel[0], Power[2]
  {1,2},                  // Channel[1], Power[2]
  {2,2},                  // Channel[2], Power[2]
  {3,2},                  // Channel[3], Power[2]
  {4,2},                  // Channel[4], Power[2]
  {5,2},                  // Channel[5], Power[2]
  {6,2},                  // Channel[6], Power[2]
  {7,2},                  // Channel[7], Power[2]
  {8,2},                  // Channel[8], Power[2]
  {9,2},                  // Channel[9], Power[2]
  {10,2},                 // Channel[10], Power[2]
  {11,2},                 // Channel[11], Power[2]
  {12,2},                 // Channel[12], Power[2]
  {13,2},                 // Channel[13], Power[2]
  {14,2},                 // Channel[14], Power[2]
  {15,2},                 // Channel[15], Power[2]
  {16,2}                  // Channel[16], Power[2]
};

/**
 * @brief Application Radio Channel-Power Settings
 */
AppRadioChannel RadioConfigurationChannelsFCC3[] = {
  {0,3},                  // Channel[0], Power[3]
  {1,3},                  // Channel[1], Power[3]
  {2,3},                  // Channel[2], Power[3]
  {3,3},                  // Channel[3], Power[3]
  {4,3},                  // Channel[4], Power[3]
  {5,3},                  // Channel[5], Power[3]
  {6,3},                  // Channel[6], Power[3]
  {7,3},                  // Channel[7], Power[3]
  {8,3},                  // Channel[8], Power[3]
  {9,3},                  // Channel[9], Power[3]
  {10,3},                 // Channel[10], Power[3]
  {11,3},                 // Channel[11], Power[3]
  {12,3},                 // Channel[12], Power[3]
  {13,3},                 // Channel[13], Power[3]
  {14,3},                 // Channel[14], Power[3]
  {15,3},                 // Channel[15], Power[3]
  {16,3}                  // Channel[16], Power[3]
};

/**
 * @brief Application Radio Configurations
 */
AppRadioConfiguration RadioConfigurationFCC[] = {
  {
    &RadioRegisterSettingsFCC[0],
    &RadioConfigurationChannelsFCC3[0],
    sizeof(RadioConfigurationChannelsFCC3)/sizeof(AppRadioChannel),
  },
  {
    &RadioRegisterSettingsFCC[1],
    &RadioConfigurationChannelsFCC2[0],
    sizeof(RadioConfigurationChannelsFCC2)/sizeof(AppRadioChannel),
  },
  {
    &RadioRegisterSettingsFCC[2],
    &RadioConfigurationChannelsFCC0[0],
    sizeof(RadioConfigurationChannelsFCC0)/sizeof(AppRadioChannel),
  },
  {
    &RadioRegisterSettingsFCC[3],
    &RadioConfigurationChannelsFCC0[0],
    sizeof(RadioConfigurationChannelsFCC0)/sizeof(AppRadioChannel),
  },
};

AppRadioArraySizes RadioArraySizesFCC = {
  sizeof(RadioConfigurationFCC)/sizeof(AppRadioConfiguration),
  sizeof(RadioChannelListFCC)/sizeof(AppRadioChannelList),
  sizeof(RadioPowerListFCC)/sizeof(AppRadioPowerList),
  sizeof(AppRegisterSettings),
  sizeof(AppRadioChannelList),
  sizeof(AppRadioPowerList)
};

#endif  // __APP_CC110LSETTINGS_H
