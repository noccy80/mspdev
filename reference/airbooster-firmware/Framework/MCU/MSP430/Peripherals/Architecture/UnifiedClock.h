/**
 *  @file UnifiedClock.h
 *
 *  @brief MSP430 Unified Clock module peripheral interface prototypes.
 *
 *  @author   BB
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup [BB]
 */
#ifndef __MCU_MSP430_UNIFIEDCLOCK_H
#define __MCU_MSP430_UNIFIEDCLOCK_H

#include "../../Architecture.h"

// UNIFIED CLOCK MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_UNIFIEDCLOCK)

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void InitUnifiedClock()
 *
 *  @brief Set the Unified Clock module to a predetermined state.
 *
 *    @return   nothing
 */
void InitUnifiedClock();

// PRIVATE INTERFACE
////////////////////////////////////////////////////////////////////////////////

// NOTE: Private interface prototypes go here.

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// NOTE: Callback function prototypes go here.

// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

// NOTE: Interrupt service routine prototypes go here.

#endif  // UNIFIED CLOCK MODULE

#endif  // __MCU_MSP430_UNIFIEDCLOCK_H