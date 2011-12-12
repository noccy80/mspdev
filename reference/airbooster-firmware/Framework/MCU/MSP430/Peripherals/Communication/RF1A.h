/**
 *  @file     RF1A.h
 *
 *  @brief    MSP430 communication public interface definitions for RF1A module
 *
 *  @author   BB
 *
 *  @version  1.0 
 *
 *  @remarks  Rev. 1.0, Initial setup [BB]
 */
#ifndef __MCU_MSP430_RF1A_H
#define __MCU_MSP430_RF1A_H

#include "../../Communication.h"

// RF1A MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_RF1A)

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void ResetRadioCore()
 *
 *  @brief Reset the radio core using RF_SRES command.
 *
 *    @return           nothing
 */
void ResetRadioCore();

/**
 *  @fn uint8_t Strobe(uint8_t)
 *
 *  @brief Send a command strobe to the radio. Includes workaround for RF1A7.
 *
 *    @param    strobe      The strobe command to be sent.
 *
 *    @return   statusByte  The status byte that follows the strobe.
 */
uint8_t Strobe(uint8_t strobe);

/**
 *  @fn void WriteSingleReg(uint8_t, uint8_t)
 *
 *  @brief Write a single byte to a radio register.
 *
 *    @param    addr      Target radio register address
 *    @param    value     Value to be written
 *
 *    @return             nothing
 */
void WriteSingleReg(uint8_t addr, uint8_t value);

/**
 *  @fn void WriteBurstReg(uint8_t, uint8_t *, uint8_t)
 *
 *  @brief Write multiple bytes to the radio registers.
 *
 *    @param    addr    Beginning address of burst write.
 *    @param    buffer  Pointer to data table.
 *    @param    count   Number of bytes to be written.
 *
 *    @return           nothing
 */
void WriteBurstReg(uint8_t addr, uint8_t * buffer, uint8_t count);

/**
 *  @fn uint8_t ReadSingleReg(uint8_t)
 *
 *  @brief Read a single byte from the radio register.
 *
 *    @param    addr      Target radio register address.
 *
 *    @return   data_out  Value of byte that was read.
 */
uint8_t ReadSingleReg(uint8_t addr);

/**
 *  @fn void ReadBurstReg(uint8_t, uint8_t *, uint8_t)
 *
 *  @brief Read multiple bytes to the radio registers.
 *
 *    @param    addr    Beginning address of burst read.
 *    @param    buffer  Pointer to data table.
 *    @param    count   Number of bytes to be read.
 *
 *    @return           nothing
 */
void ReadBurstReg(uint8_t addr, uint8_t * buffer, uint8_t count);

/**
 *  @fn void WriteSinglePATable(uint8_t)
 *
 *  @brief Write data to power table.
 *
 *    @param    value   Value to write.
 *
 *    @return           nothing
 */
void WriteSinglePATable(uint8_t value);

/**
 *  @fn void WriteBurstPATable(uint8_t *, uint8_t)
 *
 *  @brief Write to multiple locations in power table.
 *
 *    @param    buffer    Pointer to the table of values to be written.
 *    @param    count     Number of values to be written
 *
 *    @return             nothing
 */
void WriteBurstPATable(uint8_t * buffer, uint8_t count); 

// PRIVATE INTERFACE
////////////////////////////////////////////////////////////////////////////////

// NOTE: Private interface prototypes go here.

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// NOTE: Callback function prototypes go here.

// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

// NOTE: Interrupt service routine prototypes go here.

#endif  // RF1A MODULE

#endif  // __MCU_MSP430_RF1A_H