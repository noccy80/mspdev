/**
 *  @file GPIO.c
 *
 *  @brief MSP430 GPIO definitions for the Digital I/O module.
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
#include "GPIO.h"

/**
 *  @fn void InitGPIO() 
 *
 *  @brief Set GPIO ports to a predetermined state.
 */
void InitGPIO() 
{
  #if defined(__MCU_MSP430_DIGITALIO)
    InitDigitalIO();
  #endif
}

/**
 *  @fn void ToggleGPIOPortOutputRegister(uint8_t port, uint8_t pin)
 *
 *  @brief This function toggles GPIO port output register by the specified pin.
 *
 *  @param port an unsigned int
 *  @param pin an unsigned int
 */
void ToggleGPIOPortOutputRegister(uint8_t port, uint8_t pin)
{
  #if defined(__MCU_MSP430_DIGITALIO)
  switch (port)
  {
    #if defined(__MCU_MSP430_DIGITALIO_PORT1)
    case PORT1:
      ToggleDigitalIOPort1OutputRegister(pin);
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT2)
    case PORT2:
      ToggleDigitalIOPort2OutputRegister(pin);
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT3)
    case PORT3:
      ToggleDigitalIOPort3OutputRegister(pin);
      break;
    #endif
    default:
      // Error: Invalid port selected. Do nothing.
      break;
  }
  #endif
}

/**
 *  @fn void SetGPIOOutputPort(uint8_t port, uint8_t pin)
 *
 *  @brief This function sets the GPIO output port by the psecified pin.
 *
 *  @param port an unsigned int
 *  @param pin an unsigned int
 */
void SetGPIOOutputPort(uint8_t port, uint8_t pin)
{
  #if defined(__MCU_MSP430_DIGITALIO)
  switch (port)
  {
    #if defined(__MCU_MSP430_DIGITALIO_PORT1)
    case PORT1:
      SetDigitalIOPort1OutputRegister(pin);
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT2)
    case PORT2:
      SetDigitalIOPort2OutputRegister(pin);
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT3)
    case PORT3:
      SetDigitalIOPort3OutputRegister(pin);
      break;
    #endif
    default:
      // Error: Invalid port selected. Do nothing.
      break;
  }
  #endif
}

/**
 *  @fn void ClearGPIOOutputPort(uint8_t port, uint8_t pin)
 *
 *  @brief This function clears the GPIO output port by the psecified pin.
 *
 *  @param port an unsigned int
 *  @param pin an unsigned int
 */
void ClearGPIOOutputPort(uint8_t port, uint8_t pin)
{
  #if defined(__MCU_MSP430_DIGITALIO)
    if (port == PORT1)
    {
      ClearDigitalIOPort1OutputRegister(pin);
    }
    else if (port == PORT2)
    {
      ClearDigitalIOPort2OutputRegister(pin);
    }
    else if (port == PORT3)
    {
      ClearDigitalIOPort3OutputRegister(pin); 
    }
    #if defined(__MCU_MSP430_DIGITALIO_PORT4)
      else if (port == PORT4)
      {
          ClearDigitalIOPort4OutputRegister(pin);
      }
    #endif
  #endif
}

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void GPIOCallback(uint8_t port, uint8_t pin, uint8_t edge)
 *
 *  @brief GPIO port ISR extension.
 *
 *  @param port an unsigned int
 *  @param pin an unsigned int 
 *  @param edge an unsigned int
 */
void GPIOCallback(uint8_t port, uint8_t pin, uint8_t edge)
{
  // Select the correct port that triggered the callback.
  switch (port)
  {
    case PORT1: // Port 1
      #if defined(__MCU_MSP430_DIGITALIO_PORT1)
        GPIOCallbackPort1(pin, edge);
      #endif
      break;
    case PORT2: // Port 2
      #if defined(__MCU_MSP430_DIGITALIO_PORT2)
        GPIOCallbackPort2(pin, edge);
      #endif
      break;
    default:
      // Error: Invalid port selected.
      break;
  }
}