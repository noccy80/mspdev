/**
 *  @file CCXXXInterface.h
 *
 *  @brief Chipcon (CCXXX) radio public interface prototype definitions. Requires 
 *         RadioInterface.h to function.
 *
 *  @see ProcessorInterface.h
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
#ifndef __RADIO_CCXXXINTERFACE_H
#define __RADIO_CCXXXINTERFACE_H

#include "Configuration/CCXXXConfig.h"

/**
 *  @details The following provides a definition of the interface for CCxxx radios. 
 *           This interface currently supports the following radios,
 *           CC1101, CC110L, CC2500.
 *           If a radio is defined as a CCxxx Series, include the interface 
 *           definitions to be used by the application. Otherwise, compiler errors 
 *           will be thrown as these definitions will be invalid.
 */
#if defined(__RADIO_CCXXX_SERIES)

/**
 *  @details Represents how a radio is connected to the microcontroller.
 */
typedef const struct RFConnection
{
  enum                                
  {
    INTERNAL,
    EXTERNAL
  } connection;                                                                 // Radio connection
  enum                                
  {
    IRF1A,                                                                      // RF1A interface
    IRFSPI                                                                      // RF SPI interface
  } connectionType;                                                             // Radio connection type
  uint8_t peripheral;                                                           // Peripheral port defined in MCU model
  uint8_t csn[2];                                                               // Chip select (port, pin)
  uint8_t mosi[2];                                                              // Master out, slave in (port, pin)
  uint8_t miso[2];                                                              // Master in, slave out (port, pin)
  uint8_t sclk[2];                                                              // Source clock (port, pin)
  uint8_t gdo0[2];                                                              // GDO0 (port, pin)
  uint8_t gdo2[2];                                                              // GDO2 (port, pin)
} RFConnection;

/**
 *  @details Represents all registers for a specific radio.
 */
typedef const struct RFSettings
{
  union settings                                                                // Radio configuration register settings
  {
    #ifdef __RADIO_CCXXX_CC1101
      CC1101RFSettings cc1101;                                                  // CC1101 configuration registers definition
    #endif
    #ifdef __RADIO_CCXXX_CC110L
      CC110LRFSettings cc110L;                                                  // CC110L configuration registers definition
    #endif
    #ifdef __RADIO_CCXXX_CC2500
      CC2500RFSettings cc2500;                                                  // CC2500 configuration registers definition
    #endif
    #ifdef __RADIO_CCXXX_CC430
      CC430RFSettings cc430;                                                    // CC430 configuration registers definition
    #endif
  };
} RFSettings;

/**
 *  @details Represents the registers used for calibration.
 */
typedef struct RFCalibration
{
  union calibration
  {
    #ifdef __RADIO_CCXXX_CC1101
      CC1101RFCalibration cc1101;                                               // CC1101 calibration data definition
    #endif
    #ifdef __RADIO_CCXXX_CC110L
      CC110LRFCalibration cc110L;                                               // CC110L calibration data definition
    #endif
    #ifdef __RADIO_CCXXX_CC2500
      CC2500RFCalibration cc2500;                                               // CC2500 calibration data definition
    #endif
  };
} RFCalibration;

/**
 *  @details Represents the registers for the PA table.
 */
typedef const struct RFPowerSettings
{
  union power
  {
    #ifdef __RADIO_CCXXX_CC1101
      CC1101RFPowerSettings cc1101;                                             // CC1101 power table definition
    #endif
    #ifdef __RADIO_CCXXX_CC110L
      CC110LRFPowerSettings cc110L;                                             // CC110L power table definition
    #endif
    #ifdef __RADIO_CCXXX_CC2500
      CC2500RFPowerSettings cc2500;                                             // CC2500 power table definition
    #endif
  };
} RFPowerSettings;

/**
 *  @details Represents the registers used for channels.
 */
typedef const struct RFChannel
{
  union channel
  {
    #ifdef __RADIO_CCXXX_CC1101
      CC1101RFChannel cc1101;                                                   // CC1101 channel definition
    #endif
    #ifdef __RADIO_CCXXX_CC110L
      CC110LRFChannel cc110L;                                                   // CC110L channel definition
    #endif
    #ifdef __RADIO_CCXXX_CC2500
      CC2500RFChannel cc2500;                                                   // CC2500 channel definition
    #endif
  };
} RFChannel;

/**
 *  @details Represents the current state information for a specific radio.
 */
typedef struct Radio
{
  enum                                
  {
    CC1101,                                                                     // Radio is a CC1101
    CC110L,                                                                     // Radio is a CC110L
    CC2500,                                                                     // Radio is a CC2500
    CC430                                                                       // Radio is a CC430
  } model;                                                                      // Radio model
  enum
  {
    RADIO_OFF = 0,                                                              // Radio is turned off
    RADIO_ON = 1,                                                               // Radio is turned on
    RADIO_SLEEP = 2,                                                            // Radio is sleeping
    RADIO_CONFIGURED = 3,                                                       // Radio is configured
    RADIO_CALIBRATED = 4,                                                       // Radio is calibrated
    RADIO_RECEIVE = 5,                                                          // Radio is receiving
    RADIO_TRANSMIT = 6                                                          // Radio is transmitting
  } radioState;                                                                 // Radio state
  enum
  {
    RADIO_READY = 0,                                                            // Radio is ready for next operation
    RADIO_BUSY = 1                                                              // Radio is currently handling an operation
  } radioBusy;                                                                  // Radio busy flag
  RFConnection * pRadioConnection;                                              // Radio connection definitions
  RFSettings * pRadioSettings;                                                  // Radio register settings
  RFChannel * pRadioChannel;                                                    // Radio channel
  RFPowerSettings * pRadioPower;                                                // Radio power settings
} Radio;


/**
 *  @details Reset the radio.
 */
void RFResetRadioCore(Radio * radio);

/**
 *  @details Configure the radio.
 */
void RFConfigureSettings(Radio * radio);

/**
 *  @details Change the radio channel.
 */
void RFChangeChannel(Radio * radio);

/**
 *  @details Change the radio power level.
 */
void RFChangePowerLevel(Radio * radio);

/**
 *  @details Place radio into sleep mode.
 */
void RFSleep(Radio * radio);

/**
 *  @details Wake up the radio from sleep.
 */
void RFWakeUp(Radio * radio);

/**
 *  @details Write to radio.
 */
void RFWriteRegister(Radio * radio, uint8_t addr, uint8_t* pBuffer, uint8_t count);

/**
 *  @details Write to specified radio register(count of one).
 */
void RFSetRegister(Radio * radio, uint8_t addr, uint8_t value);

/**
 *  @details Read from the radio.
 */
void RFReadRegister(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count);

/**
 *  @details Read the specified radio register(count of one).
 */
uint8_t RFGetRegister(Radio * radio, uint8_t addr);

#endif  // __RADIO_CCXXX_SERIES

#endif  // __RADIO_CCXXXINTERFACE_H
