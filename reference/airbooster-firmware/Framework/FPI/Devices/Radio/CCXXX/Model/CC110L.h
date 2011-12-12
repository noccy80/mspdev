/**
 *  @file CC110L.h
 *
 *  @brief CC110L model register definitions.
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
#ifndef __RADIO_CCXXX_CC110L_H
#define __RADIO_CCXXX_CC110L_H

#define RadioFullTextDescriptions

/**
 *  @details Configuration registers for CC110L excluding the PA Table.
 */
typedef struct CC110LRFSettings
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
  uint8_t reserved1;              // NOTE: Was previously the CC1101 channr register.
  uint8_t fsctrl1;                // Frequency synthesizer control.
  uint8_t fsctrl0;                // Frequency synthesizer control.
  uint8_t freq2;                  // Frequency control word, high byte.
  uint8_t freq1;                  // Frequency control word, middle byte.
  uint8_t freq0;                  // Frequency control word, low byte.
  uint8_t mdmcfg4;                // Modem configuration.
  uint8_t mdmcfg3;                // Modem configuration.
  uint8_t mdmcfg2;                // Modem configuration.
  uint8_t mdmcfg1;                // Modem configuration.
  uint8_t notused1;               // NOTE: Was previously the CC1101 mdmcfg0 register.
  uint8_t deviatn;                // Modem deviation setting (when FSK modulation is enabled).
  uint8_t mcsm2;                  // Main Radio Control State Machine configuration.
  uint8_t mcsm1;                  // Main Radio Control State Machine configuration.
  uint8_t mcsm0;                  // Main Radio Control State Machine configuration.
  uint8_t foccfg;                 // Frequency Offset Compensation Configuration.
  uint8_t bscfg;                  // Bit synchronization Configuration.
  uint8_t agcctrl2;               // AGC control.
  uint8_t agcctrl1;               // AGC control.
  uint8_t agcctrl0;               // AGC control.
  uint8_t notused2;               // NOTE: Was previously the CC1101 worevt1 register.
  uint8_t notused3;               // NOTE: Was previously the CC1101 worevt0 register.
  uint8_t reserved2;              // NOTE: Was previously the CC1101 worctrl1 register.
  uint8_t frend1;                 // Front end RX configuration.
  uint8_t frend0;                 // Front end RX configuration.
  uint8_t fscal3;                 // Frequency synthesizer calibration.
  uint8_t fscal2;                 // Frequency synthesizer calibration.
  uint8_t fscal1;                 // Frequency synthesizer calibration.
  uint8_t fscal0;                 // Frequency synthesizer calibration.
  uint8_t notused4;               // NOTE: Was previously the CC1101 rcctrl1 register.
  uint8_t notused5;               // NOTE: Was previously the CC1101 rcctrl0 register.
  uint8_t reserved3;              // NOTE: Was previously the CC1101 fstest register.
  uint8_t reserved4;              // NOTE: Was previously the CC1101 ptest register.
  uint8_t reserved5;              // NOTE: Was previously the CC1101 agctest register.
  uint8_t test2;                  // Various test settings.
  uint8_t test1;                  // Various test settings.
  uint8_t test0;                  // Various test settings.
} CC110LRFSettings;

/**
 *  @details CC110L channel.
 */
typedef struct CC110LRFChannel
{
  uint8_t freq2;                                                                // Frequency control word, high byte.
  uint8_t freq1;                                                                // Frequency control word, middle byte.
  uint8_t freq0;                                                                // Frequency control word, low byte.
} CC110LRFChannel;

/**
 *  @details CC110L calibration data registers.
 */
typedef struct CC110LRFCalibration
{
  uint8_t fscal3;                                                               // Frequency synthesizer calibration.
  uint8_t fscal2;                                                               // Frequency synthesizer calibration.
  uint8_t fscal1;                                                               // Frequency synthesizer calibration.
  uint8_t fscal0;                                                               // Frequency synthesizer calibration.
} CC110LRFCalibration;


/**
 *  @details CC110L power table.
 */
typedef struct CC110LRFPowerSettings
{
  uint8_t patable[2];                                                           // Output power table.
} CC110LRFPowerSettings;

#endif  // __RADIO_CCXXX_CC110L_H
