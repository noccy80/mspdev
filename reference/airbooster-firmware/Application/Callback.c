/**
 *  @file Callback.c
 *
 *  @brief Function Definitions for ISR Extensions, brought upto Application Layer.
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

#include "Protocol.h"

extern ConfigStruct ConfigSettings[];
extern RadioStruct RadioLocal;
extern TimerStruct TimerLocal;

uint8_t configTimeoutCount = 0x00;
uint8_t PushButton = 0, ADCConversionDone = 0;

/**
 * @fn void AppCommunicationModule0(void)
 *
 *  @brief This function is an extension of Communication Module 0 ISR. It makes 
 *         a call to a function that collects the command for command interface and
 *         manipulates the read pointer accordingly.
 */
void AppCommunicationModule0()
{
  CmdIFCollect(*(CommStructure[__BOARD_COMPORT1_PERIPHERAL]->RXQueue.pRead));   // Collect the received command character by character.
      
  if(( CommStructure[__BOARD_COMPORT1_PERIPHERAL]->RXQueue.pRead) <= ( CommStructure[__BOARD_COMPORT1_PERIPHERAL]->RXQueue.pWrite))
    CommStructure[__BOARD_COMPORT1_PERIPHERAL]->RXQueue.pRead++;
  else
    (CommStructure[__BOARD_COMPORT1_PERIPHERAL]->RXQueue.pRead) = (CommStructure[__BOARD_COMPORT1_PERIPHERAL]->RXQueue.pBuffer);
}

/** 
 * @fn void AppCommunicationModule1(void)
 *
 * @brief This function is an extension of Communication Module 1 ISR.
 */
void AppCommunicationModule1()
{
  RadioOperation();
}

/**
 * @fn void AppDataConverterISRExtension1(void)
 *
 * @brief This function is an extension of Data Converter ISR. It sets a flag 
 *        that indicates the application that Sensor ADC data is available.
 */
void AppDataConverterISRExtension1()
{
  ADCConversionDone = 1;                                                        // Set sensor ADC data available flag for application.
}

/**
 * @fn void AppGPIOPort1(uint8_t pin, uint8_t edge)
 *
 * @brief This function is an extension of GPIO Port 1 ISR. It sets a flag based
 *         on the button press on the board.
 *
 * @param pin an integer
 * @param edge an integer
 */
void AppGPIOPort1(uint8_t pin, uint8_t edge)
{
  if(pin & __BOARD_MODESWITCH_PIN){                                             // Button press on the board
    PushButton = 1;
  }
  
  if(pin & 0xC0){
    __no_operation();
  }
}

/**
 * @fn void AppGPIOPort2(uint8_t pin, uint8_t edge)
 *
 * @brief This function is an extension of GPIO Port 2 ISR. It checks for two cases.
 *        For falling edge of GDO0, it checks if a packet has been transmitted or 
 *        received. For rising edge of GDO0, it loads the timeout to wait for EOP.
 *
 * @param pin an integer
 * @param edge an integer
 */
void AppGPIOPort2(uint8_t pin, uint8_t edge)
{
  uint16_t tempVar = 0;

  if((pin & __BOARD_RADIO1_GDO0PIN) && (edge & __BOARD_RADIO1_GDO0PIN)){        // Falling edge of GDO0 for EOP
    if(pCurrentFrameworkRadio()->radioState == RADIO_TRANSMIT){
      RadioLocal.FrameState = FRAME_SENT;                                       // Update frame state
      //GDO0 asserted slightly before RF transmission ends, so add a little delay
      for(tempVar=0;tempVar<200;tempVar++){
        __no_operation();
      }
    }
    else if(pCurrentFrameworkRadio()->radioState == RADIO_RECEIVE){
      RadioLocal.FrameState = FRAME_RECEIVED;                                   // Update frame state
      TACCTL1 &= ~CCIE;
    }
    pCurrentFrameworkRadio()->radioState = RADIO_CALIBRATED;
  }

  if((pin & __BOARD_RADIO1_GDO0PIN) && (~edge & __BOARD_RADIO1_GDO0PIN)){       // Rising edge of GDO0 for syncword (only enabled for RX)
    __BOARD_RADIO1_GDO0EDGESELECT = 1;
    __BOARD_RADIO1_GDO0FLAG = 0;
    
    RadioLocal.FrameState = WAITING_FOR_EOP;                                    // Update frame state

    tempVar = TACCR0;
    if((tempVar - TAR) > EOP_TIMEOUT){                                          // If EOP_TIMEOUT is less than the time remaining in the cycle
      TACCR1 = EOP_TIMEOUT + TAR;                                               // Load EOP_TIMEOUT
    }
    else{
      TACCR1 = EOP_TIMEOUT - (tempVar - TAR);                                   // Load the difference
    }
    TACCTL1 = CCIE;
  }
}

/**
 * @fn void AppTimerModule1(uint8_t ccifg)
 *
 * @brief This function is an extension of Timer Module 1 ISR. It checks for 
 *        config timeout and frame timeout.
 *
 * @param ccifg an integer
 */
void AppTimerModule1(uint8_t ccifg)
{
  switch(ccifg){
    case 0x00:                                                                  // Config timeout
      if(configTimeoutCount){
        configTimeoutCount--;
        if(!configTimeoutCount){
          TimerLocal.configTimeout = 1;
        }
      }
      break;
    case 0x02:                                                                  // Frame timeout
      TACCTL1 &= ~CCIE;
      TimerLocal.frameTimeout = 1;
      break;
    default:
      break;
  }
}

/**
 * @fn void AppTimerModule2(uint8_t ccifg)
 *
 * @brief This function is an extension of Timer Module 2 ISR
 *
 * @param ccifg an integer
 */
void AppTimerModule2(uint8_t ccifg)
{
  __no_operation();
}
