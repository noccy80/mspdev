/**
 *  @file MCUInterface.h
 *
 *  @brief Hardware Abstraction Layer (HAL) Framework microcontroller (MCU) public 
 *         interface definition header files. This file can be included instead of 
 *         including all individual interface files.
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
#ifndef __HAL_MCUINTERFACE_H
#define __HAL_MCUINTERFACE_H

#include "../Configuration/Config.h"

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

// MSP430 Series.
#if defined(__MCU_MSP430_SERIES)

  // Include public interface files.
  #include "MSP430/Analog.h"		                                        // Analog interface for peripheral support
  #include "MSP430/Architecture.h"	                                        // Architecture interface for peripheral support
  #include "MSP430/Communication.h"	                                        // Communication interface for peripheral support
  #include "MSP430/DataConverter.h"	                                        // DataConverter interface for peripheral support
  #include "MSP430/GPIO.h"		                                        // GPIO interface for peripheral support
  #include "MSP430/LCD.h"		                                        // LCD interface for peripheral support
  #include "MSP430/SpecialModule.h"	                                        // SpecialModule interface for peripheral support
  #include "MSP430/Timer.h"		                                        // Timer interface for peripheral support

  // Define processor specific definitions based on series definitions.
  #if defined(__MCU_MSP430_SLEEP)
    #define __MCU_SLEEP                                                         // Processor is sleep compatible.
  #endif

// 8051 Series.
#elif defined(__MCU_8051_SERIES)
#else

  #error "__HAL_ERROR: No interface is defined for the specified MCU."

#endif

#endif	// __HAL_MCUINTERFACE_H