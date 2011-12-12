/**
 *  @file UnifiedClock.c
 *
 *  @brief MSP430 Unified Clock module peripheral interface definitions.
 *
 *  @author   BB
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup [BB]
 */
#include "UnifiedClock.h"

// UNIFIED CLOCK MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_UNIFIEDCLOCK)

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details
 */
void InitUnifiedClock()
{
  // Initialize the UCS module.
  #if defined(__MCU_MSP430_X5XX)
    UCSCTL0 = __SET_MSP430_UNIFIEDCLOCK_UCSCTL0;
    UCSCTL1 = __SET_MSP430_UNIFIEDCLOCK_UCSCTL1;
    UCSCTL2 = __SET_MSP430_UNIFIEDCLOCK_UCSCTL2;
    UCSCTL3 = __SET_MSP430_UNIFIEDCLOCK_UCSCTL3;
    UCSCTL4 = __SET_MSP430_UNIFIEDCLOCK_UCSCTL4;
    UCSCTL5 = __SET_MSP430_UNIFIEDCLOCK_UCSCTL5;
    UCSCTL6 = __SET_MSP430_UNIFIEDCLOCK_UCSCTL6;
    UCSCTL7 = __SET_MSP430_UNIFIEDCLOCK_UCSCTL7;
    UCSCTL8 = __SET_MSP430_UNIFIEDCLOCK_UCSCTL8;
  #endif
}

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