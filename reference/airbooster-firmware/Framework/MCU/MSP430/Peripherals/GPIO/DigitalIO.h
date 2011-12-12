/**
 *  @file DigitalIO.h
 *
 *  @brief MSP430 Digital I/O module peripheral interface definitions.
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

#ifndef __MCU_MSP430_DIGITALIO_H
#define __MCU_MSP430_DIGITALIO_H

#include "../../GPIO.h"

// DIGITAL IO MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_DIGITALIO)

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details Set Digital I/O module to a predetermined state.
 */
void InitDigitalIO();

/**
 *  @details Return the value of digital IO port register.
 */
uint8_t GetDigitalIOPortRegister(const volatile uint8_t * reg);

/**
 *  @details Set the value to the digital IO port register.
 */
void SetDigitalIOPortRegister(volatile uint8_t * reg, uint8_t operation, uint8_t bitmask);

/**
 *  @details  Clear the digital IO port 1 output register.
 */
#define ClearDigitalIOPort1OutputRegister(bitmask)  \
(                                                   \
  P1OUT &= ~bitmask                                 \
)                                                   \

/**
 *  @details  Clear the digital IO port 2 output register.
 */
#define ClearDigitalIOPort2OutputRegister(bitmask)  \
(                                                   \
  P2OUT &= ~bitmask                                 \
)                                                   \

/**
 *  @details  Clear the digital IO port 3 output register.
 */
#define ClearDigitalIOPort3OutputRegister(bitmask)  \
(                                                   \
  P3OUT &= ~bitmask                                 \
)                                                   \

/**
 *  @details  Clear the digital IO port 4 output register.
 */
#define ClearDigitalIOPort4OutputRegister(bitmask)  \
(                                                   \
  P4OUT &= ~bitmask                                 \
)                                                   \

/**
 *  @details Set digital IO port 1 output register to a value specified by a bitmask.
 */
#define SetDigitalIOPort1OutputRegister(bitmask)    \
(                                                   \
  P1OUT |= bitmask                                  \
)                                                   \

/**
 *  @details Set digital IO port 2 output register to a value specified by a bitmask.
 */
#define SetDigitalIOPort2OutputRegister(bitmask)    \
(                                                   \
  P2OUT |= bitmask                                  \
)                                                   \

/**
 *  @details Set digital IO port 3 output register to a value specified by a bitmask.
 */
#define SetDigitalIOPort3OutputRegister(bitmask)    \
(                                                   \
  P3OUT |= bitmask                                  \
)                                                   \

/**
 *  @details Set digital IO port 4 output register to a value specified by a bitmask.
 */
#define SetDigitalIOPort4OutputRegister(bitmask)    \
(                                                   \
  P4OUT |= bitmask                                  \
)                                                   \

/**
 *  @details Toggle digital IO port 1 output register by a value specified a bitmask.
 */
#define ToggleDigitalIOPort1OutputRegister(bitmask) \
(                                                   \
  P1OUT ^= bitmask                                  \
)                                                   \

/**
 *  @details Toggle digital IO port 2 output register by a value specified a bitmask.
 */
#define ToggleDigitalIOPort2OutputRegister(bitmask) \
(                                                   \
  P2OUT ^= bitmask                                  \
)                                                   \

/**
 *  @details Toggle digital IO port 2 output register by a value specified a bitmask.
 */
#define ToggleDigitalIOPort3OutputRegister(bitmask) \
(                                                   \
  P3OUT ^= bitmask                                  \
)                                                   \

/**
 *  @details Toggle digital IO port 3 output register by a value specified a bitmask.
 */
#define ToggleDigitalIOPort4OutputRegister(bitmask) \
(                                                   \
  P4OUT ^= bitmask                                  \
)                                                   \

// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

__interrupt void PORT1ISR();

__interrupt void PORT2ISR();

#endif  // DIGITAL IO MODULE

#endif // __MCU_MSP430_DIGITALIO_H