/**
 *  @file BoardDefinition.h
 *
 *  @mainpage Board Definition
 *
 *  The following documents define the AIR Framework supported boards:
 *  @subpage ez430 "EZ430 Definition"
 *  @subpage launchpad "LaunchPad Definition"
 *  @subpage experimentersboard "Experimenter's Board Definition"
 *
 *  @brief AIR Framework Hardware Abstraction Layer (HAL) Board Definition 
 *         public definition header files.
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
#ifndef __HAL_BOARDDEFINITION_H
#define __HAL_BOARDDEFINITION_H

#include "../Configuration/Config.h"

// Include the selected board definition.
#if defined(__BOARD_EZ430_SERIES)
  // TI EZ430 board selected.
  #include "EZ430\EZ430.h"
#elif defined(__BOARD_LAUNCHPAD_SERIES)
  // TI LaunchPad board selected.
  #include "LaunchPad\LaunchPad.h"
#elif defined(__BOARD_EXPERIMENTERSBOARD_SERIES)
  // TI Experimenter's board selected.
  #include "ExperimentersBoard\ExperimentersBoard.h"
#else
  #error "__HAL_ERROR: No definition is defined for the specified board."
#endif

#endif  // __HAL_BOARDDEFINITION_H