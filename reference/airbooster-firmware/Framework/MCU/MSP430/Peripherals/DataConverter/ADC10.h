/**
 *  @file ADC10.h
 *
 *  @brief MSP430 ADC10 module peripheral interface prototypes.
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
#ifndef __MCU_MSP430_ADC10_H
#define __MCU_MSP430_ADC10_H

#include "../../DataConverter.h"

// ADC10 MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_ADC10)

/**
 *  @details ADC10 Register Index
 */
enum ADC10REGISTERS
{
  __MCU_MSP430_ADC10_ADC10AE0  = 0,
  __MCU_MSP430_ADC10_ADC10AE1  = 1,
  __MCU_MSP430_ADC10_ADC10CTL0 = 2,
  __MCU_MSP430_ADC10_ADC10CTL1 = 3,
  __MCU_MSP430_ADC10_ADC10DTC0 = 4,
  __MCU_MSP430_ADC10_ADC10DTC1 = 5,
  __MCU_MSP430_ADC10_ADC10SA   = 6,
};

/**
 *  @details ADC10 registers
 */
typedef struct ADC10Peripheral
{
  uint8_t adc10ae0;	// ADC10 input enable register 0
  uint8_t adc10ae1;	// ADC10 input enable register 1
  uint16_t adc10ctl0;	// ADC10 control register 0
  uint16_t adc10ctl1;	// ADC10 control register 1
  uint8_t adc10dtc0;	// ADC10 data transfer control register 0
  uint8_t adc10dtc1;	// ADC10 data transfer control register 1
  uint16_t adc10sa;	// ADC10 data transfer start address
} ADC10Peripheral;

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details Initialize ADC10 peripheral. 
 */
void InitADC10();

/**
 *  @details Reconfigure ADC10 peripheral.
 */
void ReconfigureADC10(ADC10Peripheral * pConfiguration);

/**
 *  @details Get the value of ADC10AE0 register.
 */
uint8_t GetADC10AE0Register();

/**
 *  @details Get the value of ADC10AE1 register.
 */
uint8_t GetADC10AE1Register();

/**
 *  @details Get the value of ADC10CTL0 register.
 */
uint16_t GetADC10CTL0Register();

/**
 *  @details Get the value of ADC10CTL1 register.
 */
uint16_t GetADC10CTL1Register();

/**
 *  @details Get the value of ADC10MEM register.
 */
uint8_t GetADC10MEMRegister();

/**
 *  @details Get the value of ADC10DTC0 register.
 */
uint8_t GetADC10DTC0Register();

/**
 *  @details Get the value of ADC10DTC1 register.
 */
uint8_t GetADC10DTC1Register();

/**
 *  @details Get the value of ADC10SA register.
 */
uint16_t GetADC10SARegister();

/**
 *  @details Set value to ADC10AE0 register.
 */
#define SetADC10AE0Register(bitmask) \
(                                    \
  ADC10AE0 = bitmask                 \
)                                    \

/**
 *  @details Set value to ADC10AE1 register.
 */
#define SetADC10AE1Register(bitmask) \
(                                    \
  ADC10AE1 = bitmask                 \
)                                    \
  
/**
 *  @details Set value to ADC10CTL0 register.
 */
#define SetADC10CTL0Register(bitmask) \
(                                     \
  ADC10CTL0 = bitmask                 \
)                                     \
  
/**
 *  @details Set value to ADC10CTL1 register.
 */
#define SetADC10CTL1Register(bitmask) \
(                                     \
  ADC10CTL1 = bitmask                 \
)                                     \
 
/**
 *  @details Set value to ADC10DTC0 register.
 */
#define SetADC10DTC0Register(bitmask) \
(                                     \
  ADC10DTC0 = bitmask                 \
)                                     \
  
/**
 *  @details Set value to ADC10DTC1 register.
 */
#define SetADC10DTC1Register(bitmask) \
(                                     \
  ADC10DTC1 = bitmask                 \
)                                     \
  
/**
 *  @details Set value to ADC10SA register.
 */
#define SetADC10SARegister(bitmask) \
(                                   \
  ADC10SA = bitmask                 \
)                                   \


// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details ADC10 ISR
 */
__interrupt void ADC10ISR();

#endif  // ADC10 MODULE

#endif  // __MCU_MSP430_ADC10_H