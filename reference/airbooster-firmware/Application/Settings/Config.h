/**
 *  @file Config.h
 *
 *  @brief Hardware Abstraction Layer (HAL) framework configuration definitions.
 *
 *  @author   BB
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup [BB]
 */
#ifndef __HAL_CONFIG_H
#define __HAL_CONFIG_H

// HAL FRAMEWORK COMPILER
////////////////////////////////////////////////////////////////////////////////

// @note If IAR is the only compiler that provides its own definition identifier,
//       we may need to provide an option for the user to define the compiler.
// @warning Do not change definition for compiler.
// COMPILER DEFINITION
#if defined(__IAR_SYSTEMS_ICC__)
  #define __COMPILER_IARSYSTEMS		    // Compiler
#else
  #error "__HAL_ERROR: Compiler is not supported."
#endif

// HAL FRAMEWORK CONSTANTS
////////////////////////////////////////////////////////////////////////////////

enum HALCONSTANTS
{
  __DISABLE_PERIPHERAL_INTERRUPTS = 0,      // Disable peripheral interrupt service routines
  __ENABLE_PERIPHERAL_INTERRUPTS = 1,       // Enable peripheral interrupt service routines
  __WRITE = 1,                              // Single write (w/o interrupts)
  __READ = 2,                               // Single read (w/o interrupts)
  __WRITEREAD = 3                           // Single write/read (w/o interrupts)
};

// NOTE: Do not change these framework constants.
#if defined(__COMPILER_IARSYSTEMS)
  #include <intrinsics.h>
#else
  // TODO: Define an intrinsics file to compensate for non-IAR compilers.
#endif
#include <stdint.h>
#define NULL ((void *)0)

// HAL FRAMEWORK DEFINITIONS
// TODO: Move this definition to settings file. Change name appropriately.
//#define __HAL_USE_BSP			    // Use a board support package

// HAL FRAMEWORK GLOBAL SETTINGS
////////////////////////////////////////////////////////////////////////////////

// BOARD DEFINITION
//#define __BOARD_EZ430_SERIES	            // Board support package
//#define __BOARD_LAUNCHPAD_SERIES
//#define __BOARD_EXPERIMENTERSBOARD_SERIES
//#define __BOARD_MSPTS430RGC64USB_SERIES

// PROCESSOR DEFINITION
#if defined(__COMPILER_IARSYSTEMS)
  // Define the series.
  #if defined(__MSP430F2013__) || defined(__MSP430F2274__) || defined(__MSP430G2553__) || defined(__MSP430FG4618__) || defined(__MSP430F5510__)
    #define __MCU_MSP430_SERIES		    // Microcontroller series
  #else
    #error "__HAL_ERROR: Microcontroller not currently supported."
  #endif
  // Define the family.
  #if defined(__MSP430F2013__) || defined(__MSP430F2274__) || defined(__MSP430G2553__)
    #define __MCU_MSP430_X2XX               // Microcontroller family
  #elif defined(__MSP430FG4618__)
    #define __MCU_MSP430_X4XX
  #elif defined(__MSP430F5510__)
    #define __MCU_MSP430_X5XX
  #endif
  // Define the model.
  #ifdef __MSP430F2013__
    #define __MCU_MSP430_F2013
  #endif
  #ifdef __MSP430F2274__
    #define __MCU_MSP430_F2274		    // Microcontroller model
  #endif
  #ifdef __MSP430G2553__
    #define __MCU_MSP430_G2553
  #endif
  #ifdef __MSP430FG4618__
    #define __MCU_MSP430_FG4618
  #endif
  #ifdef __MSP430F5510__
    #define __MCU_MSP430_F5510
  #endif
#else
  // Other compilers will require manual processor selection.
//  #define __MCU_MSP430_SERIES		    // Microcontroller series
//  #define __MCU_MSP430_X2XX		    // Microcontroller family
//  #define __MCU_MSP430_F2274		    // Microcontroller model
#endif

// NOTE: Currently removed as it may reside in the compiler definitions section.
// RADIO DEFINITION
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L)
    #define __RADIO_CCXXX_SERIES                // Radio series
  #endif
//#define __RADIO_CCXXX_CC1101		    // Radio model
//#define __RADIO_CCXXX_CC110L

#endif	// __HAL_CONFIG_H