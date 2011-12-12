/**
 *  @file CC1101.h
 *
 *  @brief CC1101 model register definitions.
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
#ifndef __RADIO_CCXXX_CC1101_H
#define __RADIO_CCXXX_CC1101_H

/**
 *  @details Configuration registers for CC1101.
 */
typedef struct CC1101RFSettings
{
  uint8_t iocfg2;                 // GDO2 output pin configuration.
  uint8_t iocfg1;                 // GDO1 output pin configuration.
  uint8_t iocfg0;                 // GDO0 output pin configuration.
  uint8_t fifothr;                // RXFIFO and TXFIFO thresholds.
  uint8_t sync1;                  // Sync word, high byte
  uint8_t sync0;                  // Sync word, low byte
  uint8_t pktlen;                 // Packet length.  
  uint8_t pktctrl1;               // Packet automation control.
  uint8_t pktctrl0;               // Packet automation control.
  uint8_t addr;                   // Device address.
  uint8_t channr;                 // Channel number.
  uint8_t fsctrl1;                // Frequency synthesizer control.
  uint8_t fsctrl0;                // Frequency synthesizer control.
  uint8_t freq2;                  // Frequency control word, high byte.
  uint8_t freq1;                  // Frequency control word, middle byte.
  uint8_t freq0;                  // Frequency control word, low byte.
  uint8_t mdmcfg4;                // Modem configuration.
  uint8_t mdmcfg3;                // Modem configuration.
  uint8_t mdmcfg2;                // Modem configuration.
  uint8_t mdmcfg1;                // Modem configuration.
  uint8_t mdmcfg0;                // Modem configuration.
  uint8_t deviatn;                // Modem deviation setting (when FSK modulation is enabled).
  uint8_t mcsm2;                  // Main Radio Control State Machine configuration.
  uint8_t mcsm1;                  // Main Radio Control State Machine configuration.
  uint8_t mcsm0;                  // Main Radio Control State Machine configuration.
  uint8_t foccfg;                 // Frequency Offset Compensation Configuration.
  uint8_t bscfg;                  // Bit synchronization Configuration.
  uint8_t agcctrl2;               // AGC control.
  uint8_t agcctrl1;               // AGC control.
  uint8_t agcctrl0;               // AGC control.
  uint8_t worevt1;                // High byte Event 0 timeout
  uint8_t worevt0;                // Low byte Event 0 timeout
  uint8_t worctrl;                // Wake On Radio control
  uint8_t frend1;                 // Front end RX configuration.
  uint8_t frend0;                 // Front end RX configuration.
  uint8_t fscal3;                 // Frequency synthesizer calibration.
  uint8_t fscal2;                 // Frequency synthesizer calibration.
  uint8_t fscal1;                 // Frequency synthesizer calibration.
  uint8_t fscal0;                 // Frequency synthesizer calibration.
  uint8_t rcctrl1;                // RC oscillator configuration
  uint8_t rcctrl0;                // RC oscillator configuration  
  uint8_t fstest;                 // Frequency synthesizer calibration control
  uint8_t ptest;                  // Production test
  uint8_t agctest;                // AGC test
  uint8_t test2;                  // Various test settings.
  uint8_t test1;                  // Various test settings.
  uint8_t test0;                  // Various test settings.
} CC1101RFSettings;

/**
 *  @details CC1101 channel.
 */
typedef struct CC1101RFChannel
{
  uint8_t channr;                                                               // Channel number.
} CC1101RFChannel;

/**
 *  @details CC1101 calibration data registers.
 */
typedef struct CC1101RFCalibration
{
  uint8_t fscal3;                                                               // Frequency synthesizer calibration.
  uint8_t fscal2;                                                               // Frequency synthesizer calibration.
  uint8_t fscal1;                                                               // Frequency synthesizer calibration.
  uint8_t fscal0;                                                               // Frequency synthesizer calibration.
} CC1101RFCalibration;


/**
 *  @details CC1101 power table.
 */
typedef struct CC1101RFPowerSettings
{
  uint8_t patable[8];                                                           // Output power table.
} CC1101RFPowerSettings;

#endif  // __RADIO_CCXXX_CC1101_H
