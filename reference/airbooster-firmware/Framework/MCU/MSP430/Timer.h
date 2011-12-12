/**
 *  @file Timer.h
 *
 *  @brief MSP430 timer public interface definitions for the Basic Timer, Real Time Clock, 
 *         Timer_A, Timer_B, and Watchdog module.
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
#ifndef __MCU_MSP430_TIMERS_H
#define	__MCU_MSP430_TIMERS_H

// Processor configuration
#include "Configuration/MSP430Config.h"

/**
 *  @details Timer enumerations
 */ 
enum
{
  TIMER1,
  TIMER2,
  TIMER3,
  TIMER4
};

/**
 *  @details Timer mode enumerations
 */ 
enum TIMER_MODE
{
  TIMER_STOP        = MC_0,
  TIMER_UP          = MC_1,
  TIMER_CONTINUOUS  = MC_2,
  TIMER_UP_DOWN     = MC_3
};

// Peripheral interfaces
#include "Peripherals/Timer/TimerA.h"
#include "Peripherals/Timer/TimerB.h"
#include "Peripherals/Timer/WatchdogTimerPlus.h"

/**
 *  @details Sets timer peripherals to a predetermined state.
 *           These peripherals include: Basic Timer, Real Time Clock, Timer A, 
 *           Timer B, Watchdog Timer
 */
void InitTimers(void);

/**
 *  @details Set timer mode.
 */
void TimerMode(uint8_t timer, uint8_t mode);

// PRIVATE INTERFACE
////////////////////////////////////////////////////////////////////////////////

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details TimerA ISR extension.
 */
void TimerCallbackModule1(uint8_t ccifg);

/**
 *  @details TimerB ISR extension.
 */
void TimerCallbackModule2(uint8_t ccifg);

#endif	// __MCU_MSP430_TIMERS_H