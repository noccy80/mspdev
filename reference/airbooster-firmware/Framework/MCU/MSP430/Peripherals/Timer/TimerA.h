/**
 *  @file TimerA.h
 *
 *  @brief MSP430 TimerA module peripheral interface prototypes.
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
#ifndef __MCU_MSP430_TIMERA_H
#define __MCU_MSP430_TIMERA_H

#include "../../Timer.h"

/**
 *  @details TimerA peripheral register stucture
 */
typedef struct TimerAPeripheral
{
  uint16_t tactl;	        // Timer A control
  uint16_t tar;		        // Timer A counter
  uint16_t tacctl0;	        // Timer A capture/compare control 0
  uint16_t taccr0;	        // Timer A compare 0
  uint16_t tacctl1;	        // Time A capture/compare control 1
  uint16_t taccr1;	        // Time A compare 1
  uint16_t tacctl2;	        // Timer A capture/compare control 2
  uint16_t taccr2;	        // Timer A compare 2
} TimerAPeripheral;

/**
 *  @details Initialize TimerA.
 */
#define InitTimerA()                              \
(                                                 \
  TACTL   = __SET_MSP430_TIMERA_TACTL,            \
  TAR     = __SET_MSP430_TIMERA_TAR,              \
  TACCTL0 = __SET_MSP430_TIMERA_TACCTL0,          \
  TACCR0  = __SET_MSP430_TIMERA_TACCR0,           \
  TACCTL1 = __SET_MSP430_TIMERA_TACCTL1,          \
  TACCR1  = __SET_MSP430_TIMERA_TACCR1,           \
  TACCTL2 = __SET_MSP430_TIMERA_TACCTL2,          \
  TACCR2  = __SET_MSP430_TIMERA_TACCR2            \
)                                                 
  
/**
 *  @details Set TimerA TACTL register to a values specified by the bitmask.
 */
#define SetTimerATACTLRegister(bitmask)           \
(                                                 \
  TACTL = bitmask                                 \
)                                                 \
  
/**
 *  @details Set TimerA TAR register to a values specified by the bitmask.
 */
#define SetTimerATARRegister(bitmask)             \
(                                                 \
  TAR = bitmask                                   \
)                                                 \
  
/**
 *  @details Set TimerA TACCTL0 register to a values specified by the bitmask.
 */
#define SetTimerATACCTL0Register(bitmask)         \
(                                                 \
  TACCTL0 = bitmask                               \
)                                                 \
  
/**
 *  @details Set TimerA TACCTL1 register to a values specified by the bitmask.
 */
#define SetTimerATACCTL1Register(bitmask)         \
(                                                 \
  TACCTL1 = bitmask                               \
)                                                 \
  
/**
 *  @details Set TimerA TACCTL2 register to a values specified by the bitmask.
 */
#define SetTimerATACCTL2Register(bitmask)         \
(                                                 \
  TACCTL2 = bitmask                               \
)                                                 \

/**
 *  @details Set TimerA TACCR0 register to a values specified by the bitmask.
 */
#define SetTimerATACCR0Register(bitmask)          \
(                                                 \
  TACCR0 = bitmask                                \
)                                                 \
  
/**
 *  @details Set TimerA TACCR1 register to a values specified by the bitmask.
 */
#define SetTimerATACCR1Register(bitmask)          \
(                                                 \
  TACCR1 = bitmask                                \
)                                                 \
  
/**
 *  @details Set TimerA TACCR2 register to a values specified by the bitmask.
 */
#define SetTimerATACCR2Register(bitmask)          \
(                                                 \
  TACCR2 = bitmask                                \
)                                                 \
  
/**
 *  @details Reconfigure TimerA. This functionality is currently not supported.
 */
void ReconfigureTimerA(TimerAPeripheral * pConfiguration);

/**
 *  @details Return TimerA TACTL register.
 */
uint8_t GetTimerATACTLRegister();

/**
 *  @details Return TimerA TAR register.
 */
uint8_t GetTimerATARRegister();

/**
 *  @details Return TimerA TACCTL0 register.
 */
uint8_t GetTimerATACCTL0Register();

/**
 *  @details Return TimerA TACCTL1 register.
 */
uint8_t GetTimerATACCTL1Register();

/**
 *  @details Return TimerA TACCTL2 register.
 */
uint8_t GetTimerATACCTL2Register();

/**
 *  @details Return TimerA TACCR0 register.
 */
uint8_t GetTimerATACCR0Register();

/**
 *  @details Return TimerA TACCR1 register.
 */
uint8_t GetTimerATACCR1Register();

/**
 *  @details Return TimerA TACCR2 register.
 */
uint8_t GetTimerATACCR2Register();

/**
 *  @details Set the TimerA3 module to a predetermined state.
 */
void InitTimerA3();

/**
 *  @details Set the Timer0A3 module to a predetermined state.
 */
void InitTimer0A3();

/**
 *  @details Set the Timer0A5 module to a predetermined state.
 */
void InitTimer0A5();

/**
 *  @details Set the Timer0A3 module to a predetermined state.
 */
void InitTimer1A3();

/**
 *  @brief Set the Timer2A3 module to a predetermined state.
 */
void InitTimer2A3();

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details TimerA ISR extension.
 */
void TimerACallback(uint8_t ccifg);


// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

__interrupt void TimerA0ISR();

__interrupt void TimerA1ISR();

#endif  // __MCU_MSP430_TIMERA_H