/**
 *  @file FPI.h
 *
 *  @brief Hardware Abstraction Layer (HAL) Framework Programming Interface 
 *  (FPI) public interface definitions.
 *
 *  @note Any compiler header files must be included before this file. The MCU
 *	  series must also be defined. This data should be defined in the Config
 *	  and Settings configuration files.
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
#ifndef __HAL_FPI_H
#define __HAL_FPI_H

// Include framework files.
#include "../Configuration/Config.h"
#include "../Board/BoardDefinition.h"	                                        // Board definition
#include "../MCU/MCUInterface.h"                                                // Processor interface

// Include device interface header files.
// NOTE: Some devices do not require an interface header file.
#if defined(__BOARD_RADIO)
  #include "Devices/Radio/RadioInterface.h"                                     // Radio interface
#endif

// Include generic interface header files.
// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

// MICROCONTROLLER
/**
 *  @details Calls processor public interface functions to initialize the CPU.
 *
 *  @see MCUInterface.c
 */
void MCUInit();

/**
 *  @details Put the microprocessor to sleep.
 *
 *  @see MCUInterface.c
 */
void MCUSleep(uint8_t mode);

/**
 *  @details Stall the micropsocessor. 
 *
 *  @see MCUInterface.c
 */
void MCUDelay(uint_least8_t delay);

/**
 *  @details Get the data buffer form communication peripheral.
 * 
 *  @see MCUInterface.c
 */
void MCUGetCommunicationBuffer(uint8_t peripheral, uint8_t * pBuffer, uint8_t count);

/**
 *  @details Set the data buffer form communication peripheral.
 *
 *  @see MCUInterface.c
 */
void MCUSetCommunicationBuffer(uint8_t peripheral, uint8_t * pBuffer, uint8_t count);

// LED
#if defined(__BOARD_LED)
/**
 *  @details Toggle board LED.
 *
 *  @see LEDInterface.c
 */
void LEDToggle(uint8_t led);
#endif  //  __BOARD_LED

// RADIO
#if defined(__BOARD_RADIO)
/**
 *  @details Initialize the radio with the configuration settings.
 *
 *  @see RadioInterface.c
 */
void RadioInit(Radio * radio, RFSettings * pConfiguration);

/**
 *  @details This function is intended to turn on the external power supply to  
 *           the radio from LDO. This functionality is currently not supported.
 *
 *  @see RadioInterface.c
 */
void RadioOn(Radio * radio, void (*RadioOnCallback)(void));

/**
 *  @details This function is intended to turn off the external power supply to  
 *           the radio from LDO. This functionality is currently not supported.
 *
 *  @see RadioInterface.c
 */
void RadioOff(Radio * radio);

/**
 *  @details Wake up the radio from sleep.
 *
 *  @see RadioInterface.c
 */
void RadioWakeup(Radio * radio);

/**
 *  @details Place the radio in sleep mode.
 *
 *  @see RadioInterface.c
 */
void RadioSleep(Radio * radio);

/**
 *  @details Configure the radio.
 *
 *  @see RadioInterface.c
 */
void RadioConfigure(Radio * radio, RFSettings * pConfiguration);

/**
 *  @details Change radio channel.
 *
 *  @see RadioInterface.c
 */
void RadioChangeChannel(Radio * radio, RFChannel * pChannel);

/**
 *  @details Change radio power level.
 *
 *  @see RadioInterface.c
 */
void RadioChangePowerLevel(Radio * radio, RFPowerSettings * pPower);

/**
 *  @details Manually calibrate the radio. This functionality is currently not 
 *           supported.
 *
 *  @see RadioInterface.c
 */
uint8_t RadioCalibrate(Radio * radio);

/**
 *  @details Transmit the frame on radio.
 *
 *  @see RadioInterface.c
 */
void RadioTransmit(Radio * radio, uint8_t * pBuffer, uint8_t count);

/**
 *  @details Read the received frame from radio.
 *
 *  @see RadioInterface.c
 */
void RadioReceive(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count);

/**
 *  @details End a currently running operation based on the mode of termination. 
 *           Place the radio into an IDLE state. This functionality is currently 
 *           not supported.
 *
 *  @see RadioInterface.c
 */
void RadioTerminateOperation(Radio * radio, uint8_t mode);

/**
 *  @details Write the data to the specified Radio register(s). Supports single 
 *           and burst register access.
 *
 *  @see RadioInterface.c
 */
void RadioWrite(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count);

/**
 *  @details Set the register to the specified value.
 *
 *  @see RadioInterface.c
 */
void RadioSetRegister(Radio * radio, uint8_t addr, uint8_t value);

/**
 *  @details Read the data from the specified Radio register(s). Supports single 
 *           and burst register access.
 *
 *  @see RadioInterface.c
 */
void RadioRead(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count);

/**
 *  @details Get the value of the specified register.
 *
 *  @see RadioInterface.c
 */
uint8_t RadioGetRegister(Radio * radio, uint8_t addr);
#endif  //  __BOARD_RADIO

// COM Port
#if defined(__BOARD_COMPORT)
/**
 *  @details Write to communication port.
 *
 *  @see COMPortInterface.c
 */
void COMPortWrite(uint8_t peripheral, uint8_t block, uint8_t * pBuffer, uint8_t count);
#endif  //  __BOARD_COMPORT

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// MICROCONTROLLER
// Communication
/**
 *  @details Communication Module 0 Receive ISR extension at FPI level.
 */
void CommunicationCallbackModule0();

/**
 *  @details Communication Module 1 Receive ISR extension at FPI level.
 */
void CommunicationCallbackModule1();

/**
 *  @details Communication Module 2 Receive ISR extension at FPI level.
 */
void CommunicationCallbackModule2();

// Data Converter

/**
 *  @details Data Converter ISR extension at FPI level.
 */
void DataConverterISRExtension1();

// GPIO
/**
 *  @details GPIO Port 1 ISR extension at FPI level.
 */
void GPIOCallbackPort1(uint8_t pin, uint8_t edge);

/**
 *  @details GPIO Port 2 ISR extension at FPI level.
 */
void GPIOCallbackPort2(uint8_t pin, uint8_t edge);

// Timers
/**
 *  @details Timer Module 1 ISR extension at FPI level.
 */
void TimerCallbackModule1(uint8_t ccifg);

/**
 *  @details Timer Module 2 ISR extension at FPI level.
 */
void TimerCallbackModule2(uint8_t ccifg);

// APPLICATION CALLBACK FUNCTION PROTOTYPES
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details Communication Module 0 Receive ISR extension at Application level.
 * 
 *  @see Callback.c
 */
void AppCommunicationModule0();

/**
 *  @details Communication Module 1 Receive ISR extension at Application level.
 * 
 *  @see Callback.c
 */
void AppCommunicationModule1();

/**
 *  @details Communication Module 2 Receive ISR extension at Application level.
 * 
 *  @see Callback.c
 */
void AppCommunicationModule2();

/**
 *  @details Data Converter ISR extension at Application level.
 * 
 *  @see Callback.c
 */
void AppDataConverterISRExtension1();

/**
 *  @details GPIO Port 1 ISR extension at Application level.
 * 
 *  @see Callback.c
 */
void AppGPIOPort1(uint8_t pin, uint8_t edge);

/**
 *  @details GPIO Port 2 ISR extension at Application level.
 * 
 *  @see Callback.c
 */
void AppGPIOPort2(uint8_t pin, uint8_t edge);

/**
 *  @details Timer Module 1 ISR extension at Application level.
 * 
 *  @see Callback.c
 */
void AppTimerModule1(uint8_t ccifg);

/**
 *  @details Timer Module 2 ISR extension at Application level.
 * 
 *  @see Callback.c
 */
void AppTimerModule2(uint8_t ccifg);

/**
 *  @details Application specific callback function for RadioOn()
 * 
 *  @see RadioInterface.c
 */
void RadioOnCallback();

#endif	// __HAL_API_H
