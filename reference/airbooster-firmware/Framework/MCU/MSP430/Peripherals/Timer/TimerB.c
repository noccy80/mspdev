/**
 *  @file TimerB.c
 *
 *  @brief MSP430 TimerB module peripheral interface definitions.
 *
 *  @author   BB
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup [BB]
 */
#include "TimerB.h"

#if defined(__MCU_MSP430_TIMERB3)

/**
 *  @details
 */
void InitTimerB3()
{
  #if defined(__MCU_MSP430_X2XX)
  // TODO: Define implementation for Timer_B3 initialization function.
  #endif
}

#endif  // Timer_B3

#if defined(__MCU_MSP430_TIMER0B7)

/**
 *  @details
 */
void InitTimer0B7()
{
  #if defined(__MCU_MSP430_X5XX)
    // TODO: Define implementation for Timer0_B7 initialization function.
  #endif
}

#endif  // Timer0_B7