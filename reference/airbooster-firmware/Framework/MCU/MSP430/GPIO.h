/**
 *  @file GPIO.h
 *
 *  @brief MSP430 GPIO public interface definitions for the Digital I/O module.
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
#ifndef __MCU_MSP430_GPIO_H
#define	__MCU_MSP430_GPIO_H

// Processor configuration
#include "Configuration/MSP430Config.h"

enum PORTREGISTER
{
  PxIN,                           // Port input register (read-only)
  PxOUT,                          // Port output register
  PxDIR,                          // Port direction register
  PxIFG,                          // Port interrupt flag register
  PxIES,                          // Port interrupt edge select register
  PxIE,                           // Port interrupt enable register
  PxSEL,                          // Port selection register
  PxSEL2,                         // Port selection 2 register
  PxREN                           // Port resistor enable register
};

enum PORT
{
  PORT1,
  PORT2,
  PORT3,
  PORT4,
  PORT5,
  PORT6,
  PORTJ
};

enum OPERATION
{
  SETPIN,
  CLEARPIN,
  SETREGISTER,
  CLEARREGISTER
};

// Peripheral interfaces
#include "Peripherals/GPIO/DigitalIO.h"

// FPI callback functions
extern void GPIOCallbackPort1(uint8_t pin, uint8_t edge);
extern void GPIOCallbackPort2(uint8_t pin, uint8_t edge);

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details Sets general purpose IO peripheral to a predetermined state.
 */
void InitGPIO(void);

/**
 *  @details Sets a GPIO port output register based on the specified pin.
 */
void SetGPIOOutputPort(uint8_t port, uint8_t pin);

/**
 *  @details Sets a GPIO port output register based on the specified pin.
 */
void ClearGPIOOutputPort(uint8_t port, uint8_t pin);

/**
 *  @details Toggle a GPIO port output register pin.
 */
void ToggleGPIOPortOutputRegister(uint8_t port, uint8_t pin);                                         

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details GPIO port ISR extension.
 */
void GPIOCallback(uint8_t port, uint8_t pin, uint8_t edge);

#endif	// __MCU_MSP430_GPIO_H