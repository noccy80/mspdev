/**
 *  @file Common.c
 *
 *  @brief MSP430 common definitions.
 *
 *  @author   BB
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup [BB]
 */
#include "Common.h"

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details
 */
void ProcessorSleep(uint8_t mode)
{
  // Put the MSP430 into sleep operation.
  switch (mode)
  {
     // The CPU is disabled.
    case 0:
      __low_power_mode_0();
      __no_operation();                     // Sleep begins on this instruction.
      break;
    // The loop control for the fast clock (MCLK) is also disabled.
    case 1:
      __low_power_mode_1();
      __no_operation();
      break;
    // The fast clock (MCLK) is also disabled.
    case 2:
      __low_power_mode_2();
      __no_operation();
      break;
    // The DCO oscillator and its DC generator are also disabled.
    case 3:
      __low_power_mode_3();
      __no_operation();
      break;
    // The crystal oscillator is also disabled.
    case 4:
      __low_power_mode_4();
      __no_operation();
      break;
  }
}

/**
 *  @details
 */
void SetCommonInterruptEnable(uint8_t select, uint8_t bitmask)
{
  switch (select)
  {
    case 1:
      #if defined(__MCU_MSP430_SPECIALFUNCTIONREGISTER1)
        IE1 |= bitmask;
      #endif
      break;
    case 2:
      #if defined(__MCU_MSP430_SPECIALFUNCTIONREGISTER2)
        IE2 |= bitmask;
      #endif
      break;
    default:
      // No selection defined. Do nothing.
      break;
  }
}

/**
 *  @details
 */
void ClearCommonInterruptEnable(uint8_t select, uint8_t bitmask)
{
  switch (select)
  {
    case 1:
      #if defined(__MCU_MSP430_SPECIALFUNCTIONREGISTER1)
        IE1 &= ~bitmask;
      #endif
      break;
    case 2:
      #if defined(__MCU_MSP430_SPECIALFUNCTIONREGISTER2)
        IE2 &= ~bitmask;
      #endif
      break;
    default:
      // No selection defined. Do nothing.
      break;
  }
}

/**
 *  @details
 */
void SetCommonInterruptFlag(uint8_t select, uint8_t bitmask)
{
  switch (select)
  {
    case 1:
      #if defined(__MCU_MSP430_SPECIALFUNCTIONREGISTER1)
        IFG1 |= bitmask;
      #endif
      break;
    case 2:
      #if defined(__MCU_MSP430_SPECIALFUNCTIONREGISTER2)
        IFG2 |= bitmask;
      #endif
      break;
    default:
      // No selection defined. Do nothing.
      break;
  }
}

/**
 *  @details
 */
void ClearCommonInterruptFlag(uint8_t select, uint8_t bitmask)
{
  switch (select)
  {
    case 1:
      #if defined(__MCU_MSP430_SPECIALFUNCTIONREGISTER1)
        IFG1 &= ~bitmask;
      #endif
      break;
    case 2:
      #if defined(__MCU_MSP430_SPECIALFUNCTIONREGISTER2)
        IFG2 &= ~bitmask;
      #endif
      break;
    default:
      // No selection defined. Do nothing.
      break;
  }
}

// PRIVATE INTERFACE
////////////////////////////////////////////////////////////////////////////////

// NOTE: Private interface defintions go here.

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// NOTE: Callback function defintions go here.

// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details
 */
#pragma vector=NMI_VECTOR
__interrupt void NMIISR()
{
  // TODO: Define non-maskable interrupt service routine generic implementation.
  __no_operation(); 
}