/**
 *  @file Communication.c
 *
 *  @brief MSP430 communication definitions for the USI, USCI, and USART modules.
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
#include "Communication.h"

/**
 *  @details USI data definition structure
 */
#if defined(__MCU_MSP430_USI)
  uint8_t USITXQueue[__SET_MSP430_USI_TXBUFSIZE] = {0x00};
  uint8_t USIRXQueue[__SET_MSP430_USI_RXBUFSIZE] = {0x00};

  CommunicationDataDefinition USIStructure = {
    {
      &USITXQueue[0],
      &USITXQueue[0],
      &USITXQueue[0],
      __SET_MSP430_USI_TXBUFSIZE
    },
    {
      &USIRXQueue[0],
      &USIRXQueue[0],
      &USIRXQueue[0],
      __SET_MSP430_USI_RXBUFSIZE - 1
    },
    0,
    0
  };
#endif

/**
 *  @details USCIA0 data definition structure
 */
#if defined(__MCU_MSP430_USCIA0) 
  uint8_t USCIA0TXQueue[__SET_MSP430_USCIA0_TXBUFSIZE] = {0x00};
  uint8_t USCIA0RXQueue[__SET_MSP430_USCIA0_RXBUFSIZE] = {0x00}; 
  
  CommunicationDataDefinition USCIA0Structure = {
    {
      &USCIA0TXQueue[0],
      &USCIA0TXQueue[0],
      &USCIA0TXQueue[0],
      __SET_MSP430_USCIA0_TXBUFSIZE
    },
    {
      &USCIA0RXQueue[0],
      &USCIA0RXQueue[0],
      &USCIA0RXQueue[0],
      __SET_MSP430_USCIA0_RXBUFSIZE - 1
    },
    0,
    0
  };
#endif

/**
 *  @details USCIB0 data definition structure
 */
#if defined(__MCU_MSP430_USCIB0)
  // NOTE: Hacked fix for removing queues from USCIB0 implementation for now.
  // This may end up being in the finalized version, but is currently just an
  // ad-hoc solution.  
  CommunicationDataBufferDefinition USCIB0Structure = {
    NULL,
    0,
    NULL,
    0,
    0,
    0
  };
  CommunicationDataBufferDefinition * communicationBuffer = &USCIB0Structure;
  
#endif
  
/**
 *  @details Communication modules data definition structure
 */
CommunicationDataDefinition * CommStructure[COMMCOUNT] = {
  #if defined(__MCU_MSP430_USI)
    &USIStructure
  #elif defined(__MCU_MSP430_USCI)
    #if defined(__MCU_MSP430_USCIA0)
      &USCIA0Structure
    #endif
    #if defined(__MCU_MSP430_USCIA1)
      ,&USCIA1Structure
    #endif
    #if defined(__MCU_MSP430_USCIB1)
      ,&USCIB1Structure
    #endif
  #endif
  #if defined(__MCU_MSP430_USART)
  #endif
};

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void GetCommunicationBuffer(uint8_t peripheral, uint8_t * pBuffer, uint8_t count)
 *
 *  @brief Get data from the RX Queue buffer.
 *
 *  @param peripheral an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 */
void GetCommunicationBuffer(uint8_t peripheral, uint8_t * pBuffer, uint8_t count)
{
  uint8_t i;                                                                    // Loop counter
  uint8_t current_interrupt_state = __get_interrupt_state();

  __disable_interrupt();

  for (i = 0; i < count; i++)
  {
    // Update the RX queue pointers.
    *(pBuffer + i) = UpdateRXQueue(peripheral, &CommStructure[peripheral]->RXQueue.pRead);
  }

  // Set communication buffer count.
  if (CommStructure[peripheral]->count)
  {
    CommStructure[peripheral]->count--;
  }

  __set_interrupt_state(current_interrupt_state);
}

/**
 *  @fn void SetCommunicationBuffer(uint8_t peripheral, uint8_t * pBuffer, uint8_t count)
 *
 *  @brief Set data to the TX Queue buffer.
 *
 *  @param peripheral an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 */
void SetCommunicationBuffer(uint8_t peripheral, uint8_t * pBuffer, uint8_t count)
{
  uint8_t i;                                                                    // Loop counter
  uint8_t current_interrupt_state = __get_interrupt_state();

  __disable_interrupt();
  
  // Loop through buffer to fill TX communication queue buffer.
  for (i = 0; i < count; i++)
  {
    *(CommStructure[peripheral]->TXQueue.pWrite) = *(pBuffer + i);
    
    // Update the TX queue pointers.
    UpdateTXQueue(peripheral, &CommStructure[peripheral]->TXQueue.pWrite);
  }

  // Set communication buffer count.
  if ((CommStructure[peripheral]->count + count) < CommStructure[peripheral]->TXQueue.bufsize)
  {
    CommStructure[peripheral]->count = CommStructure[peripheral]->count + count;
  }
  else
  {
    CommStructure[peripheral]->count = CommStructure[peripheral]->TXQueue.bufsize; 
  }
  __set_interrupt_state(current_interrupt_state);
}

/**
 *  @fn void InitCommunication()
 * 
 *  @brief Initialize Communication modules.
 */
void InitCommunication()
{
  #ifdef __MCU_MSP430_USI
  #endif

  #ifdef __MCU_MSP430_USCI
    InitUSCI();
  #endif

  #ifdef __MCU_MSP430_USART
  #endif
}

/**
 *  @fn void CommunicationReadWrite(uint8_t port, uint8_t * pBuffer, uint8_t count, uint8_t readwrite, uint8_t useinterrupts)
 *
 *  @brief This function performs write/read operation on communication module.
 *
 *  @param port an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 *  @param readwrite an unsigned int
 *  @param useinterrupts an unsigned int
 */
void CommunicationReadWrite(uint8_t port, uint8_t * pBuffer, uint8_t count, uint8_t readwrite, uint8_t useinterrupts)
{
  // NOTE: Temporary: To remove internal buffer associated with USCIB0.
  if (port != USCIB0)
  {
    // Move data from the buffer into the communication queue.
    SetCommunicationBuffer(port, pBuffer, count);
  }
  else
  {
    // This is a USCIB0 specific implementation to save RAM for the moment.
    communicationBuffer->TXBuffer = pBuffer;
    communicationBuffer->count = count;
  }
  
  // Set the corresponding port transmit flag.
  switch (port)
  {
    #if defined(__MCU_MSP430_USCIA0)
    case USCIA0:
      // Set USCI interrupt enables.
      SetUCAxTXIEBit(port, useinterrupts);
      SetUCAxRXIEBit(port, useinterrupts);
      // Set USCI Tx interrupt flag.
      SetUCAxTXIFGBit(port, useinterrupts);
      if(!useinterrupts)
      {
        while (!USCIA0Structure.done)
        {
          switch(readwrite)
          {
            case 1:  // write only
              USCIWrite(port, 0);
              break;
            case 2:  // read only
              USCIRead(port, 0);
              break;
            case 3:  // write then read
              USCIWrite(port, 0);
              //The last call to USCIWrite will set the done flag but does not actually write anything or update pointers,
              //so don't read data if we're done
              if(!USCIA0Structure.done)
              {
                USCIRead(port, 0);
              }
              break;
            default:  
              break;
          }
        }
        // Clear the flag.
        USCIA0Structure.done = 0;
      }
      break;
    #endif
    #if defined(__MCU_MSP430_USCIA1)
    case USCIA1:
      // Set USCI interrupt enables.
      SetUCAxTXIEBit(port, useinterrupts);
      SetUCAxRXIEBit(port, useinterrupts);
      // Set USCI Tx interrupt flag.
      SetUCAxTXIFGBit(port, useinterrupts);
      if(!useinterrupts)
      {
        while (!USCIA1Structure.done)
        {
          switch(readwrite)
          {
            case 1:  // write only
              USCIWrite(port, 0);
              break;
            case 2:  // read only
              USCIRead(port, 0);
              break;
            case 3:  // write then read
              USCIWrite(port, 0);
              //The last call to USCIWrite will set the done flag but does not actually write anything or update pointers,
              //so don't read data if we're done
              if(!USCIA1Structure.done)
              {
                USCIRead(port, 0);
              }
              break;
            default:  
              break;
          }
        }
        // Clear the flag.
        USCIA1Structure.done = 0;
      }
      break;
    #endif
    #if defined(__MCU_MSP430_USCIB0)
    case USCIB0:
      // Set USCI interrupt enables.
      SetUCBxTXIEBit(port, useinterrupts);
      SetUCBxRXIEBit(port, useinterrupts);
      // Set USCI Tx interrupt flag.
      SetUCBxTXIFGBit(port, useinterrupts);
      if(!useinterrupts)
      {
        while (!USCIB0Structure.done)
        {
          switch(readwrite)
          {
            case 1:  // write only
              USCIWrite(port, 0);
              break;
            case 2:  // read only
              USCIRead(port, 0);
              break;
            case 3:  // write then read
              USCIWrite(port, 0);
              //The last call to USCIWrite will set the done flag but does not actually write anything or update pointers,
              //so don't read data if we're done
              if(!USCIB0Structure.done)
              {
                USCIRead(port, 0);
              }
              break;
            default:  
              break;
          }
        }
        // Clear the flag.
        USCIB0Structure.done = 0;
      }
      break;
    #endif
    #if defined(__MCU_MSP430_USCIB1)
    case USCIB1:
      // Set USCI interrupt enables.
      SetUCBxTXIEBit(port, useinterrupts);
      SetUCBxRXIEBit(port, useinterrupts);
      // Set USCI Tx interrupt flag.
      SetUCBxTXIFGBit(port, useinterrupts);
      if(!useinterrupts)
      {
        while (!USCIB1Structure.done)
        {
          switch(readwrite)
          {
            case 1:  // write only
              USCIWrite(port, 0);
              break;
            case 2:  // read only
              USCIRead(port, 0);
              break;
            case 3:  // write then read
              USCIWrite(port, 0);
              //The last call to USCIWrite will set the done flag but does not actually write anything or update pointers,
              //so don't read data if we're done
              if(!USCIB1Structure.done)
              {
                USCIRead(port, 0);
              }
              break;
            default:  
              break;
          }
        }
        // Clear the flag.
        USCIB1Structure.done = 0;
      }
      break;
    #endif
    default:
      // Error: Port is not defined for the selected peripheral.
      break;
  }
  
  // NOTE: Temporary: To remove internal buffer associated with USCIB0.
  if (port == USCIB0)
  {
    // This is a USCIB0 specific implementation to save RAM for the moment.
    pBuffer = communicationBuffer->RXBuffer;
  }
}

// PRIVATE INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void UpdateTXQueue(uint8_t peripheral, uint8_t ** pReadWrite)
 *
 *  @brief This function updates the transmit queue read/write pointer.
 *  
 *  @param peripheral an unsigned int
 *  @param pReadWrite an unsigned int double pointer
 */
void UpdateTXQueue(uint8_t peripheral, uint8_t ** pReadWrite)
{
  // Manipulate pointers to loopback to beginning once the end has been reached.
  if (*(pReadWrite) < CommStructure[peripheral]->TXQueue.pBuffer + CommStructure[peripheral]->TXQueue.bufsize - 1)
  {
    // Increment the pointer.
    *(pReadWrite) = *(pReadWrite) + 1;
  }
  else
  {
    // Set the pointer back to the beginning.
    *(pReadWrite) = CommStructure[peripheral]->TXQueue.pBuffer;
  }
}

/**
 *  @fn uint8_t UpdateRXQueue(uint8_t peripheral, uint8_t ** pReadWrite)
 *
 *  @brief This function updates the receive queue read/write pointer.
 *  
 *  @param peripheral an unsigned int
 *  @param pReadWrite an unsigned int double pointer
 */
uint8_t UpdateRXQueue(uint8_t peripheral, uint8_t ** pReadWrite)
{
  // Store current read value.
  uint8_t value = **(pReadWrite);
  
  // Manipulate pointers to loopback to beginning once the end has been reached.
  if (*(pReadWrite) < CommStructure[peripheral]->RXQueue.pBuffer + CommStructure[peripheral]->RXQueue.bufsize)
  {
    // Increment the pointer.
    *(pReadWrite) = *(pReadWrite) + 1;
  }
  else
  {
    // Set the pointer back to the beginning.
    *(pReadWrite) = CommStructure[peripheral]->RXQueue.pBuffer;
  }
  
  return value;
}

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 *  @fn void CommunicationCallback(uint8_t port)
 *
 *  @brief Communication module ISR extension.
 *  
 *  @param port an unsigned int
 */
void CommunicationCallback(uint8_t port)
{
  switch(port){
    case 0:
      // Call communication callback for module 0.
      CommunicationCallbackModule0();
      break;
    case 1:
      // Call communication callback for module 1.
      CommunicationCallbackModule1();
      break;
    default:
      break;
  }
}
