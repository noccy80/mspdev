/**
 *  @file TimerB.h
 *
 *  @brief MSP430 TimerB module peripheral interface prototypes.
 *
 *  @author   BB
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup [BB]
 */
#ifndef __MCU_MSP430_TIMERB_H
#define __MCU_MSP430_TIMERB_H

#include "../../Timer.h"

/**
 *  @fn void InitTimerB3()
 *
 *  @brief Set the Timer_B3 module to a predetermined state.
 *
 *    @return   nothing
 */
void InitTimerB3();

/**
 *  @fn void InitTimer0B7()
 *
 *  @brief Set the Timer0_B7 module to a predetermined state.
 *
 *    @return   nothing
 */
void InitTimer0B7();

#endif  // __MCU_MSP430_TIMERB_H