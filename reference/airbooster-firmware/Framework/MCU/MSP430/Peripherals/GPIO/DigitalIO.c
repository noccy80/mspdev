/**
 *  @file DigitalIO.c
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

#include "DigitalIO.h"

// DIGITAL IO MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_DIGITALIO)

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void InitDigitalIO()
 *
 *  @brief This function determines the digital I/O ports available and sets their initial 
 *           state to user defined register values.
 */
void InitDigitalIO()
{
  #if defined(__MCU_MSP430_DIGITALIO_PORT1)
    
    // Initialize the Digital I/O 1 module.
    #if defined(__SET_MSP430_DIGITALIO1_P1OUT)
      P1OUT = __SET_MSP430_DIGITALIO1_P1OUT;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO1_P1DIR)
      P1DIR = __SET_MSP430_DIGITALIO1_P1DIR;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO1_P1IFG)
      P1IFG = __SET_MSP430_DIGITALIO1_P1IFG;
    #endif
      
    #if defined(__SET_MSP430_DIGITALIO1_P1IES)
      P1IES = __SET_MSP430_DIGITALIO1_P1IES;
    #endif
      
    #if defined(__SET_MSP430_DIGITALIO1_P1IE)
      P1IE = __SET_MSP430_DIGITALIO1_P1IE;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO1_P1SEL)
      P1SEL = __SET_MSP430_DIGITALIO1_P1SEL;
    #endif
      
    #if defined(__SET_MSP430_DIGITALIO1_P1REN)
      P1REN = __SET_MSP430_DIGITALIO1_P1REN;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO1_P1SEL2)
      P1SEL2 = __SET_MSP430_DIGITALIO1_P1SEL2;
    #endif
  #endif
 
  #if defined(__MCU_MSP430_DIGITALIO_PORT2)
        
    // Initialize the Digital I/O 2 module.
    #if defined(__SET_MSP430_DIGITALIO2_P2OUT)
      P2OUT = __SET_MSP430_DIGITALIO2_P2OUT;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO2_P2DIR)
      P2DIR = __SET_MSP430_DIGITALIO2_P2DIR;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO2_P2IFG)
      P2IFG = __SET_MSP430_DIGITALIO2_P2IFG;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO2_P2IES)
      P2IES = __SET_MSP430_DIGITALIO2_P2IES;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO2_P2IE)
      P2IE  = __SET_MSP430_DIGITALIO2_P2IE;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO2_P2SEL)
      P2SEL = __SET_MSP430_DIGITALIO2_P2SEL;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO2_P2REN)
      P2REN = __SET_MSP430_DIGITALIO2_P2REN;
    #endif
      
  #endif
     
  #if defined(__MCU_MSP430_DIGITALIO_PORT3)
        
    // Initialize the Digital I/O 3 module.
    #if defined(__SET_MSP430_DIGITALIO3_P3OUT)
      P3OUT = __SET_MSP430_DIGITALIO3_P3OUT;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO3_P3DIR)
      P3DIR = __SET_MSP430_DIGITALIO3_P3DIR;
    #endif

    #if defined(__SET_MSP430_DIGITALIO3_P3SEL)
      P3SEL = __SET_MSP430_DIGITALIO3_P3SEL;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO3_P3REN)
      P3REN = __SET_MSP430_DIGITALIO3_P3REN;
    #endif
      
  #endif
    
  #if defined(__MCU_MSP430_DIGITALIO_PORT4)
    
      // Initialize the Digital I/O 4 module.
    #if defined(__SET_MSP430_DIGITALIO4_P4OUT)
      P4OUT = __SET_MSP430_DIGITALIO4_P4OUT;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO4_P4DIR)
      P4DIR = __SET_MSP430_DIGITALIO4_P4DIR;    
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO4_P4SEL)
      P4SEL = __SET_MSP430_DIGITALIO4_P4SEL;
    #endif
    
    #if defined(__SET_MSP430_DIGITALIO4_P4REN)
      P4REN = __SET_MSP430_DIGITALIO4_P4REN;
    #endif
      
  #endif
     
  #if defined(__MCU_MSP430_DIGITALIO_PORT5)
      
    P5OUT = __SET_MSP430_DIGITALIO5_P5OUT;
    P5DIR = __SET_MSP430_DIGITALIO5_P5DIR;    
    P5SEL = __SET_MSP430_DIGITALIO5_P5SEL;
    
  #endif
      
  #if defined(__MCU_MSP430_DIGITALIO_PORT6)
  #endif
      
  #if defined(__MCU_MSP430_DIGITALIO_PORTJ)
  #endif
}

/**
 *  @fn uint8_t GetDigitalIOPortRegister(const volatile uint8_t * reg)
 *
 *  @brief This function returns the value of digital IO port register.
 *
 *  @param reg a constant volatile unsigned integer pointer
 *
 *  @return an unsigned int
 */
uint8_t GetDigitalIOPortRegister(const volatile uint8_t * reg)
{
  return *(reg);
}

/**
 *  @fn void SetDigitalIOPortRegister(volatile uint8_t * reg, uint8_t operation, uint8_t bitmask)
 *
 *  @brief This function sets/clears the specified pin of the digital IO port register.
 *
 *  @param reg a volatile unsigned integer pointer
 *  @param operation an unsigned int
 *  @param bitmask an unsigned int
 */
void SetDigitalIOPortRegister(volatile uint8_t * reg, uint8_t operation, uint8_t bitmask)
{
  if (operation == SETPIN)
  {
    *(reg) |= bitmask;
  }
  else if (operation == CLEARPIN)
  {
    *(reg) &= ~bitmask;
  }
  else
  {
    *(reg) = bitmask;
  }
}

/**
 *  @fn void ClearDigitalIOOutputPort(uint8_t port, uint8_t bitmask)
 *
 *  @brief This function clears the specified bit mask of the digital IO port.
 *
 *  @param port an unsigned int
 *  @param bitmask an unsigned int
 */
void ClearDigitalIOOutputPort(uint8_t port, uint8_t bitmask)
{
  // Select the corresponding port.
  switch (port)
  {
    #if defined(__MCU_MSP430_DIGITALIO_PORT1)
    case PORT1: // Port 
      P1OUT &= ~bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT2)
    case PORT2: // Port 2
      P2OUT &= ~bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT3)
    case PORT3: // Port 3
      P3OUT &= ~bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT4)
    case PORT4: // Port 4
      P4OUT &= ~bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT5)
    case PORT5: // Port 5
      P5OUT &= ~bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT6)
    case PORT6: // Port 6
      P6OUT &= ~bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORTJ)
    case PORTJ: // Port J
      PJOUT &= ~bitmask;
      break;
    #endif
    default:
      // No defined port selected. Do nothing.
      break;
  }
}

/**
 *  @fn void SetDigitalIOOutputPort(uint8_t port, uint8_t bitmask)
 *
 *  @brief This function sets the specified bit mask of the digital IO port.
 *
 *  @param port an unsigned int
 *  @param bitmask an unsigned int
 */
void SetDigitalIOOutputPort(uint8_t port, uint8_t bitmask)
{
  // Select the corresponding port.
  switch (port)
  {
    #if defined(__MCU_MSP430_DIGITALIO_PORT1)
    case PORT1: // Port 
      P1OUT |= bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT2)
    case PORT2: // Port 2
      P2OUT |= bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT3)
    case PORT3: // Port 3
      P3OUT |= bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT4)
    case PORT4: // Port 4
      P4OUT |= bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT5)
    case PORT5: // Port 5
      P5OUT |= bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT6)
    case PORT6: // Port 6
      P6OUT |= bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORTJ)
    case PORTJ: // Port J
      PJOUT |= bitmask;
      break;
    #endif
    default:
      // No defined port selected. Do nothing.
      break;
  }
}

/**
 *  @fn void ToggleDigitalIOOutputPort(uint8_t port, uint8_t bitmask)
 *
 *  @brief This function toggles the specified bit of the digital IO port.
 *
 *  @param port an unsigned int
 *  @param bitmask an unsigned int
 */
void ToggleDigitalIOOutputPort(uint8_t port, uint8_t bitmask)
{
  // Select the corresponding port.
  switch (port)
  {
    #if defined(__MCU_MSP430_DIGITALIO_PORT1)
    case PORT1: // Port 
      P1OUT ^= bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT2)
    case PORT2: // Port 2
      P2OUT ^= bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT3)
    case PORT3: // Port 3
      P3OUT ^= bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT4)
    case PORT4: // Port 4
      P4OUT ^= bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT5)
    case PORT5: // Port 5
      P5OUT ^= bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT6)
    case PORT6: // Port 6
      P6OUT ^= bitmask;
      break;
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORTJ)
    case PORTJ: // Port J
      PJOUT ^= bitmask;
      break;
    #endif
    default:
      // No defined port selected. Do nothing.
      break;
  }
}

// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

#pragma vector=PORT1_VECTOR
__interrupt void PORT1ISR()
{
  // Clear the current flags that are being serviced for Port1.
  uint8_t pin = P1IFG;
  pin &= P1IE;
  P1IFG &= ~pin;
  
  // Go to GPIO interrupt service routine extension for application access.
  GPIOCallback(PORT1, pin, P1IES);

  // Exit low power mode if the processor was asleep when this interrupt was triggered.
  __low_power_mode_off_on_exit();
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2ISR()
{
  // Clear the current flags that are being serviced for Port2.
  uint8_t pin = P2IFG;
  pin &= P2IE;
  P2IFG &= ~pin;
  
  // Go to GPIO interrupt service routine extension for application access.
  GPIOCallback(PORT2, pin, P2IES);

  // Exit low power mode if the processor was asleep when this interrupt was triggered.
  __low_power_mode_off_on_exit();
}

#endif  // DIGITAL IO MODULE