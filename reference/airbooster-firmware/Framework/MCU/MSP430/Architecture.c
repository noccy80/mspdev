/**
 *  @file Architecture.c
 *
 *  @brief MSP430 architecture definitions for the Clock System and Flash modules.
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
#include "Architecture.h"

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void InitArchitecture() 
 *
 *  @brief Initialize architecture for clock system and flash modules.
 */
void InitArchitecture() 
{
  // Set up clock system.
  InitClockSystem();

  // Set up flash module.
  InitFlash();
}

/**
 *  @fn void InitClockSystem() 
 *
 *  @brief Initialize clock system.
 */
void InitClockSystem() 
{
  #ifdef __MCU_MSP430_BASICCLOCK
    InitBasicClock();
  #elif defined(__MCU_MSP430_BASICCLOCKSYSTEMPLUS)
    InitBasicClockSystemPlus();
  #elif defined(__MCU_MSP430_FLLPLUS)
  #elif defined(__MCU_MSP430_UNIFIEDCLOCK)
    InitUnifiedClock();
  #else
    #error "__HAL_ERROR: Clock system peripheral is not supported."
  #endif
}

/**
 *  @fn void ReconfigureClockSystem(ClockSystemModule * pClockSystemModule)
 *
 *  @brief Reconfigure clock system. 
 *
 *  @param pClockSystemModule a ClockSystemModule structure pointer
 */
void ReconfigureClockSystem(ClockSystemModule * pClockSystemModule)
{
  switch (pClockSystemModule->peripheral)
  {
    case BASICCLOCKSYSTEMPLUS:
      SetDCOCTLRegister(pClockSystemModule->pBasicClockSystemPlus->dcoctl);
      SetBCSCTL1Register(pClockSystemModule->pBasicClockSystemPlus->bcsctl1);
      SetBCSCTL2Register(pClockSystemModule->pBasicClockSystemPlus->bcsctl2);
      SetBCSCTL3Register(pClockSystemModule->pBasicClockSystemPlus->bcsctl3);
      break;
    default: break;                                                             // Error: Invalid case index. Do nothing.
  }
}

/**
 *  @fn uint_least8_t GetClockSystemRegister(uint8_t regIndex)
 *
 *  @brief Return the value of clock system register by the specified index. 
 *
 *  @param regIndex an unsigned int
 *
 *  @return an unsigned int
 */
uint_least8_t GetClockSystemRegister(uint8_t regIndex)
{
  uint_least8_t result = 0;                                                     // Result of the get operation
  
  // Basic Clock System+
  #if defined(__MCU_MSP430_BASICCLOCKSYSTEMPLUS)
    switch (regIndex)
    {
      case __MCU_MSP430_BASICCLOCKSYSTEMPLUS_DCOCTL: result = GetDCOCTLRegister(); break;     // DCO control register
      case __MCU_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL1: result = GetBCSCTL1Register(); break;   // Basic Clock System control 1
      case __MCU_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL2: result = GetBCSCTL2Register(); break;   // Basic Clock System control 2
      case __MCU_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL3: result = GetBCSCTL3Register(); break;   // Basic Clock System control 3
      default: break;                                                           // Error: Invalid register index. Do nothing.
    }
  // FLL+
  #elif defined(__MCU_MSP430_FLLPLUS)
    __no_operation();
  #elif defined(__MCU_MSP430_UNIFIEDCLOCKSYSTEMPLUS)
    __no_operation();
  #endif
    
  return result;
}

/**
 *  @fn void SetClockSystemRegister(uint8_t regIndex, uint_least8_t value)
 *
 *  @brief Set the clock system register to the specified value.
 *
 *  @param regIndex an unsigned int
 *  @param value an unsigned int
 */
void SetClockSystemRegister(uint8_t regIndex, uint_least8_t value)
{
  // Basic Clock System+
  #if defined(__MCU_MSP430_BASICCLOCKSYSTEMPLUS)
    switch (regIndex)
    {
      case __MCU_MSP430_BASICCLOCKSYSTEMPLUS_DCOCTL: SetDCOCTLRegister(value); break;    // DCO control register
      case __MCU_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL1: SetBCSCTL1Register(value); break;   // Basic Clock System control 1
      case __MCU_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL2: SetBCSCTL2Register(value); break;   // Basic Clock System control 2
      case __MCU_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL3: SetBCSCTL3Register(value); break;   // Basic Clock System control 3
      default: break;                             // Error: Invalid register index. Do nothing.
    }
  // FLL+
  #elif defined(__MCU_MSP430_FLLPLUS)
    __no_operation();
  #elif defined(__MCU_MSP430_UNIFIEDCLOCKSYSTEMPLUS)
    __no_operation();
  #endif
}

/**
 *  @fn void InitFlash()
 *
 *  @brief Initialize flash module. This functionality is currently not supported.
 */
void InitFlash()
{
  #if defined(__MCU_MSP430_FLASH)
    
  #endif
}

/**
 *  @fn void FlashWriteChar(volatile unsigned char * address, unsigned char value)
 *
 *  @brief This function writes a character value into flash.
 *
 *  @param adderss a volatile unsigned character pointer
 *  @param value an unsigned char
 */
void FlashWriteChar(volatile unsigned char * address, unsigned char value)
{
  #if defined(__MCU_MSP430_FLASH)
    FLASH_UNLOCK();                                                             // Unlock the flash
    if((*address & value) != value){                                            // Determine if erase is needed
      uint8_t count, flashedData[64];
      uint8_t index = (uint16_t)(address - 0x1000) % 64;                        // Get the index of the address within the flash segment
      for(count=0;count<sizeof(flashedData);count++){
        flashedData[count] = *(address - index + count);                        // Store all values in segment into buffer
      }
      flashedData[index] = value;                                               // Rewrite the buffer location specified by index with the desire value
      FLASH_ERASE(address);                                                     // Erase the flash segment
      for(count=0;count<sizeof(flashedData);count++){
        FLASH_WRITE_BYTE((address - index + count),flashedData[count]);         // Write the entire buffer back into flash
      }
    }
    else{
      FLASH_WRITE_BYTE(address,value);                                          // No erase needed, just write the value to address
    }
    FLASH_LOCK();                                                               // Lock the flash when done
  #endif
}