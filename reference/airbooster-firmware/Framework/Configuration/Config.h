/**
 *  @file Config.h
 *
 *  @brief Hardware Abstraction Layer (HAL) framework configuration definitions.
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
#ifndef __HAL_CONFIG_H
#define __HAL_CONFIG_H

// HAL FRAMEWORK COMPILER
////////////////////////////////////////////////////////////////////////////////

// @note If IAR is the only compiler that provides its own definition identifier,
//       we may need to provide an option for the user to define the compiler.
// @warning Do not change definition for compiler.
// COMPILER DEFINITION
#if defined(__IAR_SYSTEMS_ICC__)
  #define __COMPILER_IARSYSTEMS		                                        // Compiler
#else
  #error "__HAL_ERROR: Compiler is not supported."
#endif

// HAL FRAMEWORK CONSTANTS
////////////////////////////////////////////////////////////////////////////////

enum HALCONSTANTS
{
  __DISABLE_PERIPHERAL_INTERRUPTS = 0,                                          // Disable peripheral interrupt service routines
  __ENABLE_PERIPHERAL_INTERRUPTS = 1,                                           // Enable peripheral interrupt service routines
  __WRITE = 1,                                                                  // Single write (w/o interrupts)
  __READ = 2,                                                                   // Single read (w/o interrupts)
  __WRITEREAD = 3                                                               // Single write/read (w/o interrupts)
};

// NOTE: Do not change these framework constants.
#if defined(__COMPILER_IARSYSTEMS)
  #include <intrinsics.h>
#else

#endif
#include <stdint.h>
#define NULL ((void *)0)

// PROCESSOR DEFINITION
#if defined(__COMPILER_IARSYSTEMS)
  // Define the series.
  #if defined(__MSP430F2013__) || defined(__MSP430F2274__) || defined(__MSP430G2553__) \
    || defined(__MSP430FG4618__) || defined(__MSP430F5510__) || defined(__MSP430G2453__)
    #define __MCU_MSP430_SERIES		                                        // Microcontroller series
  #else
    #error "__HAL_ERROR: Microcontroller not currently supported."
  #endif
  // Define the family.
  #if defined(__MSP430F2013__) || defined(__MSP430F2274__) || defined(__MSP430G2453) \
    || defined(__MSP430G2553__)
    #define __MCU_MSP430_X2XX                                                   // Microcontroller family
  #elif defined(__MSP430FG4618__)
    #define __MCU_MSP430_X4XX
  #elif defined(__MSP430F5510__)
    #define __MCU_MSP430_X5XX
  #endif
  // Define the model.
  #ifdef __MSP430F2013__
    #define __MCU_MSP430_F2013
  #endif
  #ifdef __MSP430F2274__
    #define __MCU_MSP430_F2274		                                        // Microcontroller model
  #endif
  #ifdef __MSP430G2453__
    #define __MCU_MSP430_G2453
  #endif
  #ifdef __MSP430G2553__
    #define __MCU_MSP430_G2553
  #endif
  #ifdef __MSP430FG4618__
    #define __MCU_MSP430_FG4618
  #endif
  #ifdef __MSP430F5510__
    #define __MCU_MSP430_F5510
  #endif
#else
  // Other compilers will require manual processor selection.
#endif

// NOTE: Currently removed as it may reside in the compiler definitions section.
// RADIO DEFINITION
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
    #define __RADIO_CCXXX_SERIES                                                // Radio series
  #endif

#endif	// __HAL_CONFIG_H