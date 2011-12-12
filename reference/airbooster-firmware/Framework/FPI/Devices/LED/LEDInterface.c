/**
 *  @file LEDInterface.c
 *
 *  @brief Function definitions for LED interface on the board.
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

#if defined(__BOARD_LED)
/**
 *  @fn void LEDToggle(uint8_t led)
 *
 *  @brief This function toggles an LED on/off based on its previous state. It 
 *         utilizes the board definition to determine whether the LED exists.
 *
 *  @param led an unsigend int
 */
void LEDToggle(uint8_t led)
{
  switch (led)
  {
    case 1:
      #ifdef __BOARD_LED1
        ToggleGPIOPortOutputRegister(__BOARD_LED1_PORT, __BOARD_LED1_PIN);
      #endif
      break;
    case 2:
      #ifdef __BOARD_LED2
        ToggleGPIOPortOutputRegister(__BOARD_LED2_PORT, __BOARD_LED2_PIN);
      #endif
      break;
    case 3:
      #ifdef __BOARD_LED3
        ToggleGPIOPortOutputRegister(__BOARD_LED3_PORT, __BOARD_LED3_PIN);
      #endif
      break;
    default:
      break;
  }
}
#endif  // Is LED defined on board?