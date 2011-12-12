/**
 *  @file Timer.c
 *
 *  @brief MSP430 timer definitions for the Basic Timer, Real Time Clock, 
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
// NOTE: This file needs extensive revisions.
#include "Timer.h"

/**
 *  @fn void InitTimers()
 *
 *  @brief Initialize Timer modules
 */
void InitTimers() 
{
  #ifdef __MCU_MSP430_BASICTIMER
  #endif

  #ifdef __MCU_MSP430_RTC
  #endif

  #ifdef __MCU_MSP430_TIMERA3
    InitTimerA3();
  #endif
    
  #ifdef __MCU_MSP430_TIMER0A3
   InitTimer0A3();
  #endif
    
  #ifdef __MCU_MSP430_TIMER0A5
    InitTimer0A5();
  #endif
    
  #ifdef __MCU_MSP430_TIMER1A3
    InitTimer1A3();
  #endif
    
  #ifdef __MCU_MSP430_TIMER2A3
    InitTimer2A3();
  #endif

  #ifdef __MCU_MSP430_TIMERB3
  #endif

  #ifdef __MCU_MSP430_WATCHDOGTIMERPLUS
    InitWatchdogTimerPlus();
  #endif
}

/**
 *  @fn void TimerMode(uint8_t timer, uint8_t mode)
 *
 *  @brief Set timer mode.
 *
 *  @param timer an unsigned int
 *  @param mode an unsigned int
 */
void TimerMode(uint8_t timer, uint8_t mode)
{
  #if defined(__MCU_MSP430_TIMERA3) || defined(__MCU_MSP430_TIMER0A3)
  if (timer == TIMER1)
  {
    // Clear timer mode bits.
    TACTL &= ~MC_3; 
    
    // Set new timer mode.
    TACTL |= mode;
  }
  #endif
}

/**
 *  @fn void TimerStop()
 *
 *  @brief Set the timer mode as stop mode.
 */
void TimerStop()
{
  #if defined(__MCU_MSP430_TIMERA3) || defined(__MCU_MSP430_TIMER0A3)
    TACTL |= MC_0;
  #endif
}

// PRIVATE INTERFACE
////////////////////////////////////////////////////////////////////////////////

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void TimerACallback(uint8_t ccifg)
 *
 *  @brief TimerA ISR extension.
 *
 *  @param ccifg an unsigned int
 */
void TimerACallback(uint8_t ccifg)
{
  TimerCallbackModule1(ccifg);
}

/**
 *  @fn void TimerBCallback(uint8_t ccifg)
 *
 *  @brief TimerB ISR extension.
 *
 *  @param ccifg an unsigned int
 */
void TimerBCallback(uint8_t ccifg)
{
  TimerCallbackModule2(ccifg);
}
