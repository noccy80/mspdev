/**
 *  @file ExperimentersBoard.h
 *
 *  @subpage experimentersboard Experimenter's Board Definition
 *
 *  @brief Board definition for the Experimenter's Board.
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
#ifndef __BOARD_EXPERIMENTERSBOARD_H
#define __BOARD_EXPERIMENTERSBOARD_H

// Include AIR Framework configuration.
#include "../../Configuration/Config.h"

// Verify that the MCU provided is supported by this board
// NOTE: The Experimenter's Board definition currently supports the MSP430F2013 
// microcontroller.
#if defined(__MCU_MSP430_F2013)
  #include "../../MCU/MSP430/Model/F2013.h"
#elif defined(__MCU_MSP430_FG4618)

#else
  #error "__HAL_ERROR: Microcontroller not supported on the selected board."
#endif

// MSP430F2013
//
// The following describes the MSP430F2013 connections as seen on an Experimenter's
// board.
////////////////////////////////////////////////////////////////////////////////

/**
 *  @section Microcontroller
 *
 *  @brief Microcontroller socket definition for the Experimenter's Board. Describes 
 *  the package and socket pin count.
 */
#define __BOARD_MCU_TSSOPPACKAGE
#define __BOARD_MCU_SOCKET            14

// COMPONENT DEFINITIONS
//
// This section describes the components that the MSP430F2013 is connected to.
// Only components that require an interface from the AIR Framework are defined.
// These interfaces are implemented in the FPI directory and FPI.h.
//
// @see FPI.h
//
// The following are the Experimenter's Board components that have interfaces in 
// the AIR framework:
//  - LED
////////////////////////////////////////////////////////////////////////////////

/**
 *  @section LED
 *
 *  @brief LED definition for the Experimenter's Board. Describes how to interact 
 *  with an onboard LED.
 */
#define __BOARD_LED                                                             // The board has a LED
#define __BOARD_LED_COUNT	      1                                         // Number of LEDs
// Define basic information about LED 1.
#define __BOARD_LED1		      1	                                        // LED1 connected on P1.0			
#define __BOARD_LED1_PORT             PORT1                                     // LED1 port connection
#define __BOARD_LED1_PIN	      PIN0                                      // LED1 pin connection
// Define LED aliases
#define __BOARD_LEDRED		      __BOARD_LED1                              // LED1 alias

#endif	// __BOARD_EXPERIMENTERSBOARD_H