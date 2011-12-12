/**
 *  @file BasicClockSystemPlus.h
 *
 *  @brief MSP430 Basic Clock System+ peripheral interface prototypes.
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
#ifndef __MCU_MSP430_BASICCLOCKSYSTEMPLUS_H
#define __MCU_MSP430_BASICCLOCKSYSTEMPLUS_H

#include "../../Configuration/MSP430Config.h"

// BASIC CLOCK PLUS MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_BASICCLOCKSYSTEMPLUS)

/**
 *  @details Basic Clock System+ Register Indexes
 */
enum BASICCLOCKSYSTEMPLUSREGISTERS
{
  __MCU_MSP430_BASICCLOCKSYSTEMPLUS_DCOCTL = 0,
  __MCU_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL1 = 1,
  __MCU_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL2 = 2,
  __MCU_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL3 = 3,
  __OFIE = 4,
  __OFIFG = 5
};

/**
 *  @details Basic Clock System Plus Peripheral 
 */
typedef struct BasicClockSystemPlusPeripheral
{
  uint8_t dcoctl;                 // DCO control register
  uint8_t bcsctl1;                // Basic clock system control 1
  uint8_t bcsctl2;                // Basic clock system control 2
  uint8_t bcsctl3;                // Basic clock system control 3
  uint8_t ofie;                   // Oscillator fault interrupt enable bit
  uint8_t ofifg;                  // Oscillator fault interrupt flag bit
} BasicClockSystemPlusPeripheral;

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details Initialize Basic Clock System Plus peripheral. 
 */
void InitBasicClockSystemPlus();

/**
 *  @details Reconfigure Basic Clock System Plus peripheral. 
 */
void ReconfigureBasicClockSystemPlus(BasicClockSystemPlusPeripheral * pConfiguration);

/**
 *  @details Return the value of DCOCTL register.
 */
uint8_t GetDCOCTLRegister();

/**
 *  @details Set the value of DCOCTL register.
 */
#define SetDCOCTLRegister(bitmask)    \
(                                     \
  DCOCTL = bitmask                    \
)                                     \

/**
 *  @details Return the value of BCSCTL1 register.
 */
uint8_t GetBCSCTL1Register();

/**
 *  @details Set the value of BCSCTL1 register.
 */
#define SetBCSCTL1Register(bitmask) \
(                                   \
  BCSCTL1 = bitmask                 \
)                                   \

/**
 *  @details Return the value of BCSCTL2 register.
 */
uint8_t GetBCSCTL2Register();

/**
 *  @details Set the value of BCSCTL2 register.
 */
#define SetBCSCTL2Register(bitmask) \
(                                   \
  BCSCTL2 = bitmask                 \
)                                   \

/**
 *  @details Return the value of BCSCTL3 register.
 */
uint8_t GetBCSCTL3Register();

/**
 *  @details Set the value of BCSCTL3 register.
 */
#define SetBCSCTL3Register(bitmask) \
(                                   \
  BCSCTL3 = bitmask                 \
)                                   \

/**
 *  @details Return the value of OFIE bit.
 */
uint8_t GetOFIEBit();

/**
 *  @details Set the value of OFIE bit.
 */
#define SetOFIEBit(bit)                         \
(                                               \
  IE1 = (IE1 & 0xFD) | ((bit & BIT0) << 1)      \
)                                               \

/**
 *  @details Return the value of OFIFG bit.
 */
uint8_t GetOFIFGBit();

/**
 *  @details Set the value of OFIFG bit.
 */
#define SetOFIFGBit(bit)                        \
(                                               \
  IFG1 = (IFG1 & 0xFD) | ((bit & BIT0) << 1)    \
)                                               \

#endif  // BASIC CLOCK SYSTEM+ PERIPHERAL

#endif  // __MCU_MSP430_BASICCLOCKSYSTEMPLUS_H