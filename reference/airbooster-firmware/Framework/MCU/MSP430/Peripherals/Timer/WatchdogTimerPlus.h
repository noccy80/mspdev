/**
 *  @file WatchdogTimerPlus.c
 *
 *  @brief MSP430 Watchdog Timer+ peripheral interface prototypes.
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
#ifndef __MCU_MSP430_WATCHDOGTIMERPLUS_H
#define __MCU_MSP430_WATCHDOGTIMERPLUS_H

#include "../../Timer.h"

// WATCHDOG PLUS MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_WATCHDOGTIMERPLUS)

/**
 *  @details Watchdog Timer Plus peripheral register structure
 */
typedef struct WatchdogTimerPlusPeripheral
{
  uint16_t wdtctl;                // Watchdog timer+ control register
  uint8_t nmiie;                  // NMI interrupt enable bit
  uint8_t nmiifg;                 // NMI interrupt flag bit
  uint8_t wdtie;                  // Watchdog timer+ interrupt enable bit
  uint8_t wdtifg;                 // Watchdog timer+ interrupt flag bit
} WatchdogTimerPlusPeripheral;

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details Reconfigure Watchdog Timer Plus.
 */
void ReconfigureWatchdogTimerPlus(WatchdogTimerPlusPeripheral * pConfiguration);

/**
 *  @details Return the value of WDTPW register.
 */
uint8_t GetWDTPassword();

/**
 *  @details Return the value of NMIIE bit.
 */
uint8_t GetNMIIEBit();

/**
 *  @details Return the value of NMIIFG bit.
 */
uint8_t GetNMIIFGBit();

/**
 *  @details Return the value of WDTIE bit.
 */
uint8_t GetWDTIEBit();

/**
 *  @details Return the value of WDTIFG bit.
 */
uint8_t GetWDTIFGBit();

/**
 *  @details Initialize Watchdog Timer Plus.
 */
#define InitWatchdogTimerPlus()                   \
(                                                 \
  WDTCTL = __SET_MSP430_WATCHDOGTIMERPLUS_WDTCTL  \
)                                                 \
  
/**
 *  @details Set WDTCTL register with value of specified bitmask.
 */
#define SetWDTCTLRegister(bitmask)                \
(                                                 \
  WDTCTL = bitmask                                \
)                                                 \
  
/**
 *  @details Set NMIIE bit with value of specified bitmask.
 */
#define SetNMIIEBit(bit)                          \
(                                                 \
  NMIIE = bit                                     \
)                                                 \
  
/**
 *  @details Set NMIIFG bit with value of specified bitmask.
 */
#define SetNMIIFGBit(bit)                         \
(                                                 \
  NMIIFG = bit                                    \
)                                                 \
  
/**
 *  @details Set WDTIEB bit with value of specified bitmask.
 */
#define SetWDTIEBit(bit)                          \
(                                                 \
  WDTIEB = bit                                    \
)                                                 \
  
/**
 *  @details Set WDTIFG bit with value of specified bitmask.
 */
#define SetWDTIFGBit(bit)                         \
(                                                 \
  WDTIFG = bit                                    \
)                                                 \

// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

__interrupt void NMIISR();

__interrupt void WDTISR();

#endif  // WATCHDOG TIMER+ PERIPHERAL

#endif  // __MCU_MSP430_WATCHDOGTIMERPLUS_H