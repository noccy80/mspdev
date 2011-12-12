/**
 *  @file MCUInterface.h
 *
 *  @brief Hardware Abstraction Layer (HAL) Framework microcontroller (MCU) public 
 *         interface definitions. This file can be included instead of including  
 *         all individual interface files.
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
#include "../FPI/FPI.h"

/**
 *  @fn void MCUInit()
 *
 *  @brief Sets the microcontroller to a predetermined state. Handles initialization
 *         for all categories of peripherals: Analog, Architecture, Communication,
 *         Data Converters, GPIO, LCD, Special Modules, Timers.
 *
 */
void MCUInit()
{
  #if defined(__MCU_MSP430_SERIES)
    InitAnalog();				                                // Initialize the Analog modules
    InitArchitecture();			                                        // Initialize the Architecture modules
    InitCommunication();			                                // Initialize the Communication modules
    InitDataConverters();			                                // Initialize the Data Converter modules
    InitGPIO();				                                        // Initialize the GPIO modules
    InitLCD();				                                        // Initialize the LCD modules
    InitSpecialModules();			                                // Initialize the Special modules
    InitTimers();				                                // Initialize the Timers modules
  #endif
}

/**
 *  @fn void MCUSleep(uint8_t mode)
 *
 *  @brief Puts the microcontroller into a low power mode - "sleep state".
 *
 *  @param mode an unsigned int
 */
void MCUSleep(uint8_t mode)
{
  #if defined(__MCU_MSP430_SERIES)
  // TODO: Definition of implementing low power mode must be further defined.
  // NOTE: There are 5 different low power modes for the MSP430 (0 - CPUOFF, 1, 
  //       2, 3, 4).
    __low_power_mode_0();
  #endif
}

/**
 *  @fn void MCUDelay(uint_least8_t delay)
 *
 *  @brief Stalls the microcontroller using a traditional loop delay.
 *
 *  @param delay an unsigned int
 */
void MCUDelay(uint_least8_t delay)
{
  uint_least8_t i;
  
  for (i = 0; i < delay; i++); 
}

/**
 *  @fn void MCUGetCommunicationBuffer(uint8_t peripheral, uint8_t * pBuffer, uint8_t count)
 *
 *  @brief
 *
 *  @param peripheral an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 */
void MCUGetCommunicationBuffer(uint8_t peripheral, uint8_t * pBuffer, uint8_t count)
{
  GetCommunicationBuffer(peripheral, pBuffer, count);
}

/**
 *  @fn void MCUSetCommunicationBuffer(uint8_t peripheral, uint8_t * pBuffer, uint8_t count)
 *
 *  @brief
 *
 *  @param peripheral an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 */
void MCUSetCommunicationBuffer(uint8_t peripheral, uint8_t * pBuffer, uint8_t count)
{
  SetCommunicationBuffer(peripheral, pBuffer, count);
}