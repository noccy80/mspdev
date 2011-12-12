/**
 *  @file COMPortInterface.c
 *
 *  @brief Function definitions for COM port operation
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
#include "../../FPI.h"

#if defined(__BOARD_COMPORT)

/**
 *  @function void COMPortWrite(uint8_t peripheral, uint8_t block, uint8_t * pBuffer, uint8_t count)
 *
 *  @brief This function writes to the specified COM port. It has two functionalities 
 *         depending on its operation.
 *         Blocking: Processor is put in low power mode 0 until the write operation 
 *         is complete.
 *         Non-Blocking: The data to be written is sent to the COM port and processor 
 *         continues with its operation. 
 *
 *  @param peripheral an unsigned int
 *  @param block an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 */
void COMPortWrite(uint8_t peripheral, uint8_t block, uint8_t * pBuffer, uint8_t count)
{  
  // Perform UART blocking write operation.
  CommunicationReadWrite(peripheral, pBuffer, count, 1, 1);
  
  // Check if blocking UART write
  if (block == 1)  // Blocking functionality
  {
    // Turn the CPU off until the operation is complete.
//    while (CommStructure[peripheral]->done == 0)
    while (CommStructure[peripheral]->done == 0)
    { // NOTE: This is a potential deadlock if done is set between while and low power mode.
      __low_power_mode_0();
      __no_operation();
    } 
    // Operation is done.
    CommStructure[peripheral]->done = 0;
  }
}

#endif  // Is COMPort defined on board?