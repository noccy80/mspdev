/**
 *  @file RadioInterface.c
 *
 *  @brief Hardware Abstraction Layer (HAL) Framework radio public interface 
 *         definitions. Requires FPI.h to function.
 *
 *  @see FPI.h
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

// Include radio interface implementation is a radio is defined.
#if defined(__BOARD_RADIO)

/**
 * @fn void RadioInit(Radio * radio, RFSettings * pConfiguration)
 *
 * @brief This function performs the radio initialization by writing the 
 *        configuration settings to the radio. 
 *
 * @param radio a Radio structure pointer
 * @param pConfiguration a RFSettings structure pointer
 */
void RadioInit(Radio * radio, RFSettings * pConfiguration)
{
  RadioConfigure(radio, pConfiguration);
}

/**
 *  @fn void RadioOn(Radio * radio, void (*RadioOnCallback)(void))
 *
 *  @brief This function is intended to turn on the external power supply to the 
 *         radio from LDO. This functionality is currently not supported.
 *
 *  @see For the complement, see RadioOff()
 *
 *  @param radio a Radio structure pointer
 *  @param RadioOnCallback function pointer
 */
void RadioOn(Radio * radio, void (*RadioOnCallback)(void))
{
  // Go to callback.
  RadioOnCallback();
}

/**
 *  @fn void RadioOff(Radio * radio)
 *
 *  @brief This function is intended to turn off the external power supply to the 
 *         radio from LDO. This functionality is currently not supported.
 *
 *  @see For the complement, see RadioOn().
 *
 *  @param radio a Radio structure pointer
 */
void RadioOff(Radio * radio)
{
}

/**
 *  @fn void RadioWakeup(Radio * radio)
 *
 *  @brief This function wakes updates the radio state and wakes it up from sleep.
 *
 *  @see For the complement, see RadioSleep().
 *
 *  @param radio a Radio structure pointer
 */
void RadioWakeup(Radio * radio)
{
  // Set the radio busy flag.
  radio->radioBusy = RADIO_BUSY;
  
  // Set the radio state to configured.
  radio->radioState = RADIO_CONFIGURED;
  
  // Wake up the radio.
  RFWakeUp(radio);
  
  // Clear the radio busy flag.
  radio->radioBusy = RADIO_READY;
}

/**
 *  @fn void RadioSleep(Radio * radio)
 *
 *  @brief This function updats the radio state and places it in sleep mode.
 *
 *  @see For the complement, see RadioWakeup().
 *
 *  @param radio a Radio structure pointer
 */
void RadioSleep(Radio * radio)
{
  // Set the radio state to sleep.
  radio->radioState = RADIO_SLEEP;
  
  // Put the radio to sleep.
  RFSleep(radio);
}

/**
 *  @fn void RadioConfigure(Radio * radio, RFSettings * pConfiguration)
 *
 *  @brief This function updates the radio state and loads configuration settings.
 *
 *  @param radio a Radio structure pointer
 *  @param pConfiguration a RFSettings structure pointer
 */
void RadioConfigure(Radio * radio, RFSettings * pConfiguration)
{
  // Set the radio busy flag.
  radio->radioBusy = RADIO_BUSY;
  
  // Set radio configuration settings.
  radio->pRadioSettings = pConfiguration;

  // Perform configuration.  
  RFConfigureSettings(radio);
  
  // Set the radio state to configured.
  radio->radioState = RADIO_CONFIGURED;
  
  // Clear the radio busy flag.
  radio->radioBusy = RADIO_READY;
}

/**
 *  @fn void RadioChangeChannel(Radio * radio, RFChannel * pChannel)
 *
 *  @brief This function changes the radio channel.
 *
 *  @param radio a Radio structure pointer
 *  @param pChannel a RFChannel structure pointer
 */
void RadioChangeChannel(Radio * radio, RFChannel * pChannel)
{
  // Set the radio busy flag.
  radio->radioBusy = RADIO_BUSY;
  
  // Set radio channel.
  radio->pRadioChannel = pChannel;
  
  // Perform channel change.
  RFChangeChannel(radio);
  
  // Clear the radio busy flag.
  radio->radioBusy = RADIO_READY;
}

/**
 *  @fn void RadioChangePowerLevel(Radio * radio, RFPowerSettings * pPower)
 *
 *  @brief This function changes the radio power level.
 *
 *  @param radio a Radio structure pointer
 *  @param pPower a RFPowerSettings structure pointer
 */
void RadioChangePowerLevel(Radio * radio, RFPowerSettings * pPower)
{
  // Set the radio busy flag.
  radio->radioBusy = RADIO_BUSY;
  
  // Set radio power.
  radio->pRadioPower = pPower;
  
  // Perform channel change.
  RFChangePowerLevel(radio); 

  // Clear the radio busy flag.
  radio->radioBusy = RADIO_READY;
}

/**
 *  @fn uint8_t RadioCalibrate(Radio * radio)
 *
 *  @brief This function performs manual calibration of the radio. This functionality 
 *          is currently not supported.
 *
 *  @param radio a Radio structure pointer
 *
 *  @return an unsigned integer
 */
uint8_t RadioCalibrate(Radio * radio)
{
  return 0;
}

/**
 *  @fn void RadioTransmit(Radio * radio, uint8_t * pBuffer, uint8_t count)
 *
 *  @brief This function updates the radio state, writes the data to the transmit 
 *         FIFO and strobes Transmit.
 *
 *  @param radio a Radio structure pointer
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 */
void RadioTransmit(Radio * radio, uint8_t * pBuffer, uint8_t count)
{
  // Set the radio busy flag.
  radio->radioBusy = RADIO_BUSY;
  
  // Write to the transmit FIFO.
  RadioWrite(radio, CCXXX_REG_TXFIFO, pBuffer, count);
  
  // Strobe TX.
  RadioSetRegister(radio, CCXXX_STRB_STX, 0);
}

/**
 *  @fn void RadioReceive(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count)
 *
 *  @brief This function reads the data from the radio(mainly used to read from 
 *         receive FIFO).
 *
 *  @param radio a Radio structure pointer
 *  @param addr an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 */
void RadioReceive(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count)
{
  RFReadRegister(radio, addr, pBuffer, count);
}

/**
 *  @fn void RadioTerminateOperation(Radio * radio, uint8_t mode)
 *
 *  @brief This function terminates the current operation on the radio. This 
 *         functionality is currently not supported.
 *
 *  @param radio a Radio structure pointer
 *  @mode an unsigned int
 */
void RadioTerminateOperation(Radio * radio, uint8_t mode)
{
}

/**
 *  @fn void RadioWrite(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count)
 *
 *  @brief This function performs a write operation the radio register(s).
 *         Supports single and burst register access.
 * 
 *  @param radio a Radio structure pointer
 *  @param addr an unsigned int
 *  @param pBuffer an unsigned integer pointer
 *  @param count an unsigned int
 */
void RadioWrite(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count)
{
  // Perfrom a write to radio register(s).
  RFWriteRegister(radio, addr, pBuffer, count);
}

/**
 *  @fn void RadioSetRegister(Radio * radio, uint8_t addr, uint8_t value)
 *
 *  @brief This function sets a value to the radio register.
 *
 *  @param radio a Radio structure pointer
 *  @param addr an unsigned int
 *  @param value an unsigned int
 */
void RadioSetRegister(Radio * radio, uint8_t addr, uint8_t value)
{
  // Set value to a radio register.
  RFWriteRegister(radio, addr, &value, 1);
}

/**
 *  @fn void RadioRead(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count)
 * 
 *  @brief This function performs a read operation from radio register(s).
 *         Supports single and burst register access.
 *
 *  @param radio a Radio structure pointer
 *  @param addr an unsigned int
 *  @param count an unsigned int
 */
void RadioRead(Radio * radio, uint8_t addr, uint8_t * pBuffer, uint8_t count)
{
  // Perform a read from radio register(s).
  RFReadRegister(radio, addr, pBuffer, count);
}

/**
 *  @fn uint8_t RadioGetRegister(Radio * radio, uint8_t addr)
 *
 *  @brief This function gets a value froma radio register.
 *
 *  @param radio a Radio structure pointer
 *  @param addr an unsigned int
 * 
 *  @return an unsigned integer
 */
uint8_t RadioGetRegister(Radio * radio, uint8_t addr)
{
  uint8_t tempBuffer;
  // Get value of a radio register.
  RFReadRegister(radio, addr, &tempBuffer, 1);
  return tempBuffer;
}

#endif  // Radio is defined on board?