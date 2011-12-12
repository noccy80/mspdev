/**
 *  @file CCXXXInterface.c
 *
 *  @brief Chipcon (CCXXX) radio public interface definitions.
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
#include "CCXXXInterface.h"

#if defined(__RADIO_CCXXX_SERIES)

// Radio interfaces
#if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  #include "Interface/CC1101Interface.h"
#endif

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////
/**
 *  @fn void RFResetRadioCore(Radio * radio)
 *
 *  @brief This function performs a manual power-up sequence.
 *
 *  @param radio a Radio structure pointer
 */
void RFResetRadioCore(Radio * radio)
{
  // CC1101, CC110L, and CC2500
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
    if ((radio->model == CC1101) || (radio->model == CC110L) || (radio->model == CC2500))
    {
      ResetCC1101(radio); 
    }
  #endif
}

/**
 *  @fn void RFConfigureSettings(Radio * radio)
 *
 *  @brief This function writes to the configuration setting registers of the radio.
 *
 *  @param radio a Radio structure pointer.
 */
void RFConfigureSettings(Radio * radio)
{
  // Configure the radio with new settings.
  // CC1101 and CC2500
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
    if ((radio->model == CC1101) || (radio->model == CC110L) || (radio->model == CC2500))
    {
      ConfigureCC1101(radio);
    }
  #endif
}

/**
 *  @fn void RFChangeChannel(Radio * radio)
 *
 *  @brief This function performs the channel change for the radio.
 *
 *  @param radio a Radio structure pointer.
 */
void RFChangeChannel(Radio * radio)
{
  #if defined(__RADIO_CCXXX_CC1101)
    if (radio->model == CC1101)
    {
      uint8_t tempBuffer[1] = {
        radio->pRadioChannel->cc1101.channr
      };
      
      // Write channel register.
      CC1101Write(radio, CCXXX_REG_CHANNR, tempBuffer, 1);
    }
  #endif
  
  #if defined(__RADIO_CCXXX_CC2500)
    if (radio->model == CC2500)
    {
      uint8_t tempBuffer[1] = {
        radio->pRadioChannel->cc2500.channr
      };
              
      // Write channel register.
      CC1101Write(radio, CCXXX_REG_CHANNR, tempBuffer, 1);
    }
  #endif
    
  #if defined(__RADIO_CCXXX_CC110L)
    if (radio->model == CC110L)
    {
      // NOTE: This implementation will change once bursts are working correctly.
      uint8_t tempBuffer[3] = {
        radio->pRadioChannel->cc110L.freq2,
        radio->pRadioChannel->cc110L.freq1,
        radio->pRadioChannel->cc110L.freq0
      };
      // Write frequency registers to change CC110L channel.
      CC1101Write(radio, CCXXX_REG_FREQ2, &tempBuffer[0], 1);
      CC1101Write(radio, CCXXX_REG_FREQ1, &tempBuffer[1], 1);
      CC1101Write(radio, CCXXX_REG_FREQ0, &tempBuffer[2], 1);
    }
  #endif
}

/**
 *  @fn void RFChangePowerLevel(Radio * radio)
 *
 *  @brief This function performs the power level change for the raido.
 *
 *  @param radio a Radio structure pointer
 */
void RFChangePowerLevel(Radio * radio)
{
  #if defined(__RADIO_CCXXX_CC1101)
    if (radio->model == CC1101)
    {
      uint8_t tempBuffer[sizeof(radio->pRadioPower->cc1101.patable)];
      uint8_t i;
      for (i = 0; i < sizeof(radio->pRadioPower->cc1101.patable); i++)
      {
        tempBuffer[i] = radio->pRadioPower->cc1101.patable[i];
      }
      // Write PA table register.
      CC1101Write(radio, CCXXX_REG_PATABLE, tempBuffer, sizeof(radio->pRadioPower->cc1101.patable));
    }
  #endif
  #if defined(__RADIO_CCXXX_CC110L)
    if (radio->model == CC110L)
    {
      uint8_t tempBuffer[sizeof(radio->pRadioPower->cc110L.patable)];
      uint8_t i;
      for (i = 0; i < sizeof(radio->pRadioPower->cc110L.patable); i++)
      {
        tempBuffer[i] = radio->pRadioPower->cc110L.patable[i];
      }
      // Write PA table register.
      CC1101Write(radio, CCXXX_REG_PATABLE, tempBuffer, sizeof(radio->pRadioPower->cc110L.patable));
    }
  #endif
  #if defined(__RADIO_CCXXX_CC2500)
    if (radio->model == CC2500)
    {
      uint8_t tempBuffer[sizeof(radio->pRadioPower->cc2500.patable)];
      uint8_t i;
      for (i = 0; i < sizeof(radio->pRadioPower->cc2500.patable); i++)
      {
        tempBuffer[i] = radio->pRadioPower->cc2500.patable[i];
      }
      // Write PA table register.
      CC1101Write(radio, CCXXX_REG_PATABLE, tempBuffer, sizeof(radio->pRadioPower->cc2500.patable));
    }
  #endif
}

/**
 *  @fn void RFSleep(Radio * radio)
 *
 *  @brief This function performs radio sleep operation.
 *
 *  @param radio a Radio structure pointer
 */
void RFSleep(Radio * radio)
{
  // CC1101, CC110L, and CC2500
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
    if ((radio->model == CC1101) || (radio->model == CC110L) || (radio->model == CC2500))
    {
      CC1101Sleep(radio); 
    }
  #endif
}

/**
 *  @fn void RFWakeUp(Radio * radio)
 *
 *  @brief This function wakes up the radio from sleep.
 *
 *  @param radio a Radio structure pointer
 */
void RFWakeUp(Radio * radio)
{
    // CC1101, CC110L, and CC2500
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
    if ((radio->model == CC1101) || (radio->model == CC110L) || (radio->model == CC2500))
    {
      CC1101WakeUp(radio); 
    }
  #endif

}

/**
 *  @fn void RFWriteRegister(Radio * radio, uint8_t addr, uint8_t* pBuffer, uint8_t count)
 *
 *  @brief This function performs a write operation on the radio.
 *
 *  @param radio a Radio structure pointer
 *  @param addr an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 */
void RFWriteRegister(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count)
{
  // CC1101, CC110L, and CC2500
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
    if ((radio->model == CC1101) || (radio->model == CC110L) || (radio->model == CC2500))
    {
      CC1101Write(radio, addr, pBuffer, count); 
    }
  #endif
}

/**
 *  @fn void RFSetRegister(Radio * radio, uint8_t addr, uint8_t value)
 *
 *  @brief This function sets the radio register to the specifies value.
 *
 *  @param radio a Radio structure pointer
 *  @param addr an unsigned int
 *  @param value an unsigned int
 */
void RFSetRegister(Radio * radio, uint8_t addr, uint8_t value)
{
  // CC1101, CC110L, and CC2500
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
    if ((radio->model == CC1101) || (radio->model == CC110L) || (radio->model == CC2500))
    {
      CC1101Write(radio, addr, &value, 1);
    }
  #endif
}

/**
 *  @fn void RFReadRegister(Radio * radio, uint8_t addr, uint8_t* pBuffer, uint8_t count)
 *
 *  @brief This function performs a read operation on the radio.
 *
 *  @param radio a Radio structure pointer
 *  @param addr an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 */
void RFReadRegister(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count)
{
  // CC1101, CC110L, and CC2500
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
    if ((radio->model == CC1101) || (radio->model == CC110L) || (radio->model == CC2500))
    {
      CC1101Read(radio, addr, pBuffer, count); 
    }
  #endif
}

/**
 *  @fn void RFGetRegister(Radio * radio, uint8_t addr, uint8_t value)
 *
 *  @brief This function gets the value of the specified radio register.
 *
 *  @param radio a Radio structure pointer
 *  @param addr an unsigned int
 */
uint8_t RFGetRegister(Radio * radio, uint8_t addr)
{
  uint8_t tempBuffer = 0x00;                                                    // Temporary variable of size 1 to emulate a buffer.
  
  // CC1101, CC110L, and CC2500
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
    if ((radio->model == CC1101) || (radio->model == CC110L) || (radio->model == CC2500))
    {
      CC1101Read(radio, addr, &tempBuffer, 1);
      return tempBuffer; 
    }
  #endif
  
  return 0;
}

#endif  // __RADIO_CCXXX_SERIES