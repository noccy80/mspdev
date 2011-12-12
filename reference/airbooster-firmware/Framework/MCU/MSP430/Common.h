/**
 *  @file Common.h
 *
 *  @brief MSP430 common public interface definitions. These definitions are
 *  microcontroller specifc, not peripheral specific. They are defined to
 *  encapsulate intrinsic functions and special registers.
 *
 *  @author   BB
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup [BB]
 */
#ifndef __MCU_MSP430_COMMON_H
#define	__MCU_MSP430_COMMON_H

// Processor configuration
#include "Configuration/MSP430Config.h"

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void ProcessorSleep(uint8_t)
 *
 *  @brief Put the processor into a low power state.
 *
 *    @param    mode    The mode for low power.
 *
 *    @return           nothing
 */
void ProcessorSleep(uint8_t mode);

/**
 *  @fn void SetCommonInterruptEnable(uint8_t, uint8_t)
 */
void SetCommonInterruptEnable(uint8_t select, uint8_t bitmask);

/**
 *  @fn void ClearCommonInterruptEnable(uint8_t, uint8_t)
 */
void ClearCommonInterruptEnable(uint8_t select, uint8_t bitmask);

/**
 *  @fn void SetCommonInterruptFlag(uint8_t, uint8_t)
 */
void SetCommonInterruptFlag(uint8_t select, uint8_t bitmask);

/**
 *  @fn void ClearCommonInterruptFlag(uint8_t, uint8_t)
 */
void ClearCommonInterruptFlag(uint8_t select, uint8_t bitmask);

// PRIVATE INTERFACE
////////////////////////////////////////////////////////////////////////////////

// NOTE: Private interface prototypes go here.

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// NOTE: Callback function prototypes go here.

// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn __interrupt void NMIISR()
 */
__interrupt void NMIISR();

#endif  // __MCU_MSP430_COMMON_H