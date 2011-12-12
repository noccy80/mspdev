/**
 *  @file MSP430Config.h
 *
 *  @brief MSP430 series configuration definitions. Defines MCU model supported
 *         peripherals.
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
#ifndef __MCU_MSP430_CONFIG_H
#define __MCU_MSP430_CONFIG_H

#include "../../../Configuration/Config.h"
#include "Settings.h"

// Include correct MCU header file.
#if defined(__COMPILER_IARSYSTEMS)
  #if defined(__MCU_MSP430_F2013)
    #include <msp430f2013.h>
    #include "../Model/F2013.h"
  #elif defined(__MCU_MSP430_F2274)
    #include "../Model/F2274.h"
  #elif defined(__MCU_MSP430_G2453)
    #include <msp430g2453.h>
    #include "../Model/G2453.h"
  #elif defined(__MCU_MSP430_G2553)
    #include "../Model/G2553.h"
  #elif defined(__MCU_MSP430_F5510)
    #include <msp430f5510.h>
    #include "../Model/F5510.h"
  #endif
#endif

// Common interface
// NOTE: Interface functions are utilized throughout the processor interface.
//#include "Common.h"

// PROCESSOR SERIES DEFINITIONS
////////////////////////////////////////////////////////////////////////////////
/**
 *  @details The MSP430 microcontroller allows for sleep operation.
 */
#define __MCU_MSP430_SLEEP                                                      // MSP430 family supports sleep

#endif	// __MCU_MSP430_CONFIG_H