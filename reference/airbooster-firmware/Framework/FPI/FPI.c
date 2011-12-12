/**
 *  @file FPI.c
 *
 *  @brief Hardware Abstraction Layer (HAL) Framework Programming Interface 
 *         (FPI) definitions.
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
#include "FPI.h"

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

// NOTE: Implementation of the public interface has been moved to each device's
//       designated folder. The prototypes remain in FPI.h.

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// Communication

// NOTE: CommunicationCallbackModule0 is used at the processor interface level 
//       and must therefore always be included in the build.
/**
 *  @fn void CommunicationCallbackModule0()
 *
 *  @brief Communication Module 0 Receive ISR extension at FPI level.
 */
void CommunicationCallbackModule0()
{
  AppCommunicationModule0();
}

// NOTE: CommunicationCallbackPeripheral1 is used at the processor interface level 
//       and must therefore always be included in the build.
/**
 *  @fn void CommunicationCallbackModule1()
 *
 *  @brief Communication Module 1 Receive ISR extension at FPI level.
 */
void CommunicationCallbackModule1()
{
  // NOTE: This function sits at the application level. We provide the function name
  //       and the user provides the actual implementation.
  AppCommunicationModule1();
}

/**
 *  @fn void CommunicationCallbackModule2()
 *
 *  @brief Communication Module 2 Receive ISR extension at FPI level.
 */
void CommunicationCallbackModule2()
{
    // NOTE: This function sits at the application level. We provide the function name
  //       and the user provides the actual implementation.
  AppCommunicationModule2();
}

// Data Converter

/**
 *  @fn void DataConverterISRExtension1()
 *
 *  @brief Data Converter ISR extension at FPI level.
 */
void DataConverterISRExtension1()
{
  AppDataConverterISRExtension1(); 
}

// GPIO

/**
 *  @fn void GPIOCallbackPort1(uint8_t pin, uint8_t edge)
 *
 *  @brief GPIO Port 1 ISR extension at FPI level.
 *
 *  @param pin an unsigned int
 *  @param edge an unsigned int
 */
void GPIOCallbackPort1(uint8_t pin, uint8_t edge)
{
  AppGPIOPort1(pin, edge);
}

/**
 *  @fn void GPIOCallbackPort2(uint8_t pin, uint8_t edge)
 *
 *  @brief GPIO Port 2 ISR extension at FPI level.
 *
 *  @param pin an unsigned int
 *  @param edge an unsigned int
 */
void GPIOCallbackPort2(uint8_t pin, uint8_t edge)
{
  AppGPIOPort2(pin, edge);
}

// Timers

/**
 *  @fn void TimerCallbackModule1(uint8_t ccifg)
 *
 *  @brief Timer Module 2 ISR extension at FPI level.
 *
 *  @param ccifg an unsigned int
 */
void TimerCallbackModule1(uint8_t ccifg)
{
  AppTimerModule1(ccifg);
}

/**
 *  @fn void TimerCallbackModule2(uint8_t ccifg)
 *
 *  @brief Timer Module 2 ISR extension at FPI level.
 *
 *  @param ccifg an unsigned int
 */
void TimerCallbackModule2(uint8_t ccifg)
{
  AppTimerModule2(ccifg);
}
