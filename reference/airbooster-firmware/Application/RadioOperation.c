/**
 *  @file RadioOperation.c
 *
 *  @brief Radio Operation function Definitions
 *         This file defines the functions for Initializing and Configuring the
 *         radio, Frame-Transmit and Frame-Receive.
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

#include "Framework\FPI\FPI.h"
#include "Application.h"
#include "RadioOperation.h"
#include "CommandInterface.h"

RXFlagStruct RXFlags;
TXFlagStruct TXFlags;
ConfigStruct ConfigSettings[] = { {0},{0} };
RadioStruct RadioLocal = {0};
TimerStruct TimerLocal = {0};

#if defined(__RADIO_CCXXX_CC1101)
  #include "CC1101Settings.h"
#endif
#if defined(__RADIO_CCXXX_CC110L)
  #include "CC110LSettings.h"
#endif
#if defined(__RADIO_CCXXX_CC2500)
  #include "CC2500Settings.h"
#endif

/**
 * @brief Application Radio Definition Structure
 */
AppRadio radio[] = {
  #if defined(__RADIO_CCXXX_CC1101)
    {
      {
        CC1101,
        RADIO_ON,
        RADIO_READY,
        &RadioConnection,
        &RadioRegisterSettingsFCC[0].registerSettings,
        &RadioChannelListFCC[0].radioChannel,
        &RadioPowerListFCC[0].radioPower
      },
      { &RadioConfigurationFCC[0] },
      { &RadioChannelListFCC[0] },
      { &RadioPowerListFCC[0] },
      { &RadioArraySizesFCC },
      { "A1101R09C" }
    },
  #endif  // __RADIO_CCXXX_CC1101

  #if defined(__RADIO_CCXXX_CC110L)
    {
      {
        CC110L,
        RADIO_ON,
        RADIO_READY,
        &RadioConnection,
        &RadioRegisterSettingsETSI[0].registerSettings,
        &RadioChannelListETSI[0].radioChannel,
        &RadioPowerListETSI[0].radioPower
      },
      { &RadioConfigurationETSI[0] },
      { &RadioChannelListETSI[0] },
      { &RadioPowerListETSI[0] },
      { &RadioArraySizesETSI },
      { "A110LR09A, ETSI" }
    },
    {
      {
        CC110L,
        RADIO_ON,
        RADIO_READY,
        &RadioConnection,
        &RadioRegisterSettingsFCC[0].registerSettings,
        &RadioChannelListFCC[0].radioChannel,
        &RadioPowerListFCC[0].radioPower
      },
      { &RadioConfigurationFCC[0] },
      { &RadioChannelListFCC[0] },
      { &RadioPowerListFCC[0] },
      { &RadioArraySizesFCC },
      { "A110LR09A, FCC" }
    },
  #endif  // __RADIO_CCXXX_CC110L

  #if defined(__RADIO_CCXXX_CC2500)
    {
      {
        CC2500,
        RADIO_ON,
        RADIO_READY,
        &RadioConnection,
        &RadioRegisterSettingsFCC[0].registerSettings,
        &RadioChannelListFCC[0].radioChannel,
        &RadioPowerListFCC[0].radioPower
      },
      { &RadioConfigurationFCC[0] },
      { &RadioChannelListFCC[0] },
      { &RadioPowerListFCC[0] },
      { &RadioArraySizesFCC },
      { "A2500R24A, WW" }
    }
  #endif  // __RADIO_CCXXX_CC2500
};

uint8_t const radio_Count = sizeof(radio)/sizeof(AppRadio);                     //!< Number of radios supported in the AppRadio structure.

/**
 * @fn void InitRadio(AppRadio * radio)
 *
 * @brief This function initializes the radio to its default config, channel and
 *        power. It resets the radio upon power up.
 *
 * @param radio an AppRadio structure pointer
 */
void InitRadio(AppRadio * radio)
{
  PowerUpResetCCxxxx(radio);                                                    // Reset the Radio

  #ifdef INCLUDE_FLASH_STORAGE
    // These temporary variables are used to remove compiler warnings regarding multiple volatile arguments in a single C instruction
    uint8_t tempRadio   = MyFlashedRSCP.Radio;
    uint8_t tempConfig  = MyFlashedRSCP.Setting;
    uint8_t tempChannel = MyFlashedRSCP.Channel;
    uint8_t tempPower   = MyFlashedRSCP.Power;

    if(tempRadio < radio_Count){
      if((tempConfig  < pCurrentRadioArraySizesStruct(tempRadio)->radioConfigurationCount) &&
         (tempChannel < pCurrentRadioArraySizesStruct(tempRadio)->radioChannelListCount) &&
         (tempPower   < pCurrentRadioArraySizesStruct(tempRadio)->radioPowerListCount)){
        ChangeConfiguration(0, tempRadio, tempConfig, tempChannel, tempPower);  // Set radio configuration to values stored in flash
        return;
      }
    }
  #endif
  ChangeConfiguration(0, 0, 0, 0, 0);                                           // Set radio configuration to default values
}

/**
 * @fn void RXPacketProcessing(uint8_t * pBuffer)
 *
 * @brief This function processes the received packet to manipulate the flags
 *        necessary for config change cycle, payload acknowledgement
 *
 * @param pBuffer an integer pointer
 */
void RXPacketProcessing(uint8_t * pBuffer)
{
  if(pBuffer[NEW_CONFIG_INDEX] & 0x80){                                         // If config change request received
    RXFlags.RxConfigMessageType = RECEIVED_CONFIG_REQUEST;
  }
  else if(pBuffer[NEW_CONFIG_INDEX] & 0x40){                                    // If ACK received for config change request 
    RXFlags.RxConfigMessageType = RECEIVED_CONFIG_ACK;
  }
  else if(pBuffer[NEW_CONFIG_INDEX] & 0x20){                                    // If config change ping received
    RXFlags.RxConfigMessageType = RECEIVED_CONFIG_PING;
  }
  else{
    RXFlags.RxConfigMessageType = RECEIVED_NO_CONFIG_CHANGE;
  }
  if(pBuffer[NEW_POWER_COMMAND] & 0x80){                                        // If ACK received for data
    RXFlags.RxACKMessageType = RECEIVED_ACK;
    RXFlags.RxPayloadMessageType = RECEIVED_NO_PAYLOAD;
  }
  if(pBuffer[NEW_POWER_COMMAND] & 0x40){                                        // If data received
    RXFlags.RxPayloadMessageType = RECEIVED_PAYLOAD;
    RXFlags.RxACKMessageType = RECEIVED_NO_ACK;
    TXFlags.TxACKMessageType = SEND_ACK;
  }
  if((pBuffer[NEW_POWER_COMMAND] & 0x80) && (pBuffer[NEW_POWER_COMMAND] & 0x40)){
    RXFlags.RxACKMessageType = RECEIVED_ACK;
    RXFlags.RxPayloadMessageType = RECEIVED_PAYLOAD;
  }
}

/**
 * @fn uint8_t FrameSend(AppRadio * radio, uint8_t * pBuffer, uint8_t count, uint16_t timeout, uint8_t timeoutAction)
 *
 * @brief This function takes care of steps required in sending the packet. It flushes the RX-TX FIFOs and creates the
 *        data packet to be sent. Once the packet it transmitted, it loads the timer for the timeout value so that the
 *        radio is placed in low power state if frame timeout occures.
 *
 * @param radio an AppRadio structure pointer
 * @param pBuffer an integer pointer
 * @param count an integer
 * @param timeout an integer
 * @param timeoutAction an integer
 *
 * @return an integer
 */
uint8_t FrameSend(AppRadio * radio, uint8_t * pBuffer, uint8_t count, uint16_t timeout, uint8_t timeoutAction)
{
  uint16_t tempVar = 0;

  __BOARD_RADIO1_GDO0ENABLE = 0;
  
  RadioSetRegister(pCurrentFrameworkRadio(), CCXXX_STRB_SIDLE, 0);              // Strobe Idle
  RadioSetRegister(pCurrentFrameworkRadio(), CCXXX_STRB_SFTX, 0);               // Strobe flush TX FIFO
  RadioSetRegister(pCurrentFrameworkRadio(), CCXXX_STRB_SFRX, 0);               // Strobe flush RX FIFO

  for(tempVar=0;tempVar<400;tempVar++){
    __no_operation();
  }
  
  __BOARD_RADIO1_GDO0EDGESELECT = 1;
  __BOARD_RADIO1_GDO0FLAG = 0;
  __BOARD_RADIO1_GDO0ENABLE = 1;
 
  CreateDataPacket(pBuffer, count, RadioLocal.TxFrameStruct.frameHeader, &RadioLocal.frameLength);        // Create the data packet to be sent
  pCurrentFrameworkRadio()->radioState = RADIO_TRANSMIT;                                                  // Update radio state
  RadioLocal.FrameState = WAITING_FOR_SYNCWORD;                                                           // Update frame state
  RadioTransmit(pCurrentFrameworkRadio(), RadioLocal.TxFrameStruct.frameHeader, RadioLocal.frameLength);  // Transmit the packet

  // Load timer with timeout value.  The radio should be placed in a low-power state if frame timeout occurs.
  tempVar = TACCR0;
  if((tempVar - TAR) > timeout){                                                // If timeout value is less than the time remaining in the cycle
    TACCR1 = timeout + TAR;                                                     // Load timeout value
  }
  else{
    TACCR1 = timeout - (tempVar - TAR);                                         // Load the difference
  }
  TACCTL1 = CCIE;

  while(pCurrentFrameworkRadio()->radioState == RADIO_TRANSMIT){                // Wait until transmit is complete.  
    if(TimerLocal.frameTimeout){                                                // This blocks all other application code (except ISR stuff) from running.
      TimerLocal.frameTimeout = 0;
      RadioLocal.FrameState = FRAME_IDLE;                                       // Update frame state
      CycleTimeoutAction(radio, timeoutAction);                                 // If frame timeout occured, perform the timeout action
      return 0;
    }
    __low_power_mode_0();                                                       // Else stay in low power mode until the packet is being transmitted
  }

  TACCTL1 &= ~CCIE;

  pCurrentFrameworkRadio()->radioState = RADIO_CALIBRATED;                      // Restore radio state      
  
  TXFlags.TxPayloadMessageType = SEND_NO_PAYLOAD;                               // Clear all TX flags
  TXFlags.TxACKMessageType = SEND_NO_ACK;

  return 1;
}

/**
 * @fn uint8_t FrameListen(AppRadio * radio, uint8_t * pBuffer, uint8_t * pCount, uint16_t timeout, uint8_t timeoutAction)
 *
 * @brief This function listens to receive a frame. It places the radio in receive mode and loads the timer with timeout
 *        value so that the radio is placed in low power state if nothing is received. If the packet is received, it 
 *        grabs the data from radio.
 *
 * @param radio an AppRadio structure pointer
 * @param pBuffer an integer pointer
 * @param pCount an integer pointer
 * @param timeout an integer
 * @param timeoutAction an integer
 *
 * @return GetFrame a function
 */
uint8_t FrameListen(AppRadio * radio, uint8_t * pBuffer, uint8_t * pCount, uint16_t timeout, uint8_t timeoutAction)
{
  uint16_t tempVar = 0;

  RXFlags.RxConfigMessageType = RECEIVED_NO_CONFIG_CHANGE;                      // Clear all RX flags
  RXFlags.RxPayloadMessageType = RECEIVED_NO_PAYLOAD;
  RXFlags.RxACKMessageType = RECEIVED_NO_ACK;
    
  ReceiveOn(radio);                                                             // Place radio into receive mode to look for ACK or config change order.

  // Load timer with timeout value.  The radio should be placed in a low-power state if nothing received.
  tempVar = TACCR0;                                                             
  if((tempVar - TAR) > timeout){                                                // If timeout value is less than the time remaining in the cycle
    TACCR1 = timeout + TAR;                                                     // Load timeout value
  }
  else{
    TACCR1 = timeout - (tempVar - TAR);                                         // Load the difference
  }
  TACCTL1 = CCIE;

  while(pCurrentFrameworkRadio()->radioState == RADIO_RECEIVE){                 // Wait for an ACK or timeout event.  
    if(TimerLocal.frameTimeout){                                                // This blocks all other application code (except ISR stuff) from running.
      TimerLocal.frameTimeout = 0;
      RadioLocal.FrameState = FRAME_IDLE;                                       // Update frame state
      CycleTimeoutAction(radio, timeoutAction);                                 // If frame timeout occured, perform the timeout action
      return 0;
    }
    __low_power_mode_0();
  }
  
  TACCTL1 &= ~CCIE;

  return GetFrame(radio, pBuffer, pCount);                                      // Check to see if we received a packet.  If so, grab the data from the radio.
}

/**
 * @fn uint8_t GetFrame(AppRadio * radio, uint8_t * pBuffer, uint8_t * pCount)
 *
 * @brief This function grabs the data from radio and puts it into local buffer.
 *        It checks if a frame is received, and if so, it checks for a valid length.
 *        If the length is valid, it reads the data and status bytes from radio. 
 *        If length is not valid, it flushes the receive FIFO. At last, it checks
 *        for CRC okay and if so, it reads the payload data from the frame and 
 *        provides status update if its the time to report.
 *
 * @param radio an AppRadio structure pointer
 * @param pBuffer an integer pointer
 * @param pCount an integer pointer
 *
 * @return an integer
 */
uint8_t GetFrame(AppRadio * radio, uint8_t * pBuffer, uint8_t * pCount)
{
  if(RadioLocal.FrameState == FRAME_RECEIVED){
    RadioLocal.FrameState = FRAME_IDLE;

    // This status register is safe to read since it will not be updated after
    // the packet has been received (See the CC1100 and 2500 Errata Note)
    if (RadioGetRegister(pCurrentFrameworkRadio(), CCXXX_STAT_RXBYTES) & BYTES_IN_RXFIFO){
      RadioLocal.RxFrameStruct.frameHeader[LENGTH] = RadioGetRegister(pCurrentFrameworkRadio(), CCXXX_REG_RXFIFO);// Read length byte
      if(RadioLocal.RxFrameStruct.frameHeader[LENGTH] < MAX_FRAME_LENGTH){      // Read the packet if length is valid
        RadioReceive(pCurrentFrameworkRadio(), CCXXX_REG_RXFIFO, RadioLocal.RxFrameStruct.frameHeader + 1, RadioLocal.RxFrameStruct.frameHeader[LENGTH]++);
        RadioReceive(pCurrentFrameworkRadio(), CCXXX_REG_RXFIFO, RadioLocal.linkStatus, 2);       
      }
      else{
        // Make sure that the radio is in IDLE state before flushing the FIFO
        // (Unless RXOFF_MODE has been changed, the radio should be in IDLE state at this point)
        RadioSetRegister(pCurrentFrameworkRadio(), CCXXX_STRB_SIDLE, 0);        // Strobe Idle
        RadioSetRegister(pCurrentFrameworkRadio(), CCXXX_STRB_SFRX, 0);         // Strobe flush RX FIFO
        // if valid packet is not received (there are no bytes in RXFIFO), there should not be any check for CRC okay,
        // else it will just return the previous value in the RadioLocal.linkStatus buffer
        return 0;  // so return
      }
    }

    if((RadioLocal.linkStatus[LQI] & 0x80) && (RadioGetRegister(pCurrentFrameworkRadio(), CCXXX_STAT_LQI) & 0x80)){// CRC OK?
      *pCount = RadioLocal.RxFrameStruct.frameHeader[LENGTH] - HEADER_LENGTH;   // Set the payload length
      if(*pCount <= sizeof(PayloadFrame)){
        if((void*)pCount != NULL){
          for(uint8_t i=0;i<*pCount;i++){
            pBuffer[i] = RadioLocal.RxFrameStruct.framePayload[i];              // Store payload into local buffer
          }
          if(((PayloadFrame *)pBuffer)->Flags.PairingSolicitation || NodeIsInMyNet(((PayloadFrame *)pBuffer)->NodeID)){
            RXPacketProcessing(RadioLocal.RxFrameStruct.frameHeader);           // Process the received packet to set necessary flags 
            Query_Current_Status((PayloadFrame *)&pBuffer[0]);                  // Check if status update should be given
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

/**
 * @fn uint8_t ChangeConfiguration(uint8_t remote, uint8_t radioIndex, uint8_t configIndex, uint8_t channelIndex, uint8_t powerIndex)
 *
 * @brief This function takes necessary steps to change local or remote configuration 
 *        based on the user's requirement. It checks if all config, channel and 
 *        power indices fed to it are within the range, if they are, it checks 
 *        if its a remote or local config change. For remote, it sets a flag to 
 *        initiate the config change request and loads config timeout value. For
 *        local, it updates the indices for config, channel and power and loads 
 *        new settings into the radio. At last, it sets the cycle time to the 
 *        default cycle time.
 *
 * @param remote an integer
 * @param radioIndex an integer
 * @param configIndex an integer
 * @param channelIndex an integer
 * @param powerIndex an integer
 *
 * @return an integer
 */
uint8_t ChangeConfiguration(uint8_t remote, uint8_t radioIndex, uint8_t configIndex, uint8_t channelIndex, uint8_t powerIndex)
{
  // If all indices within range
  if(radioIndex < radio_Count){
    if(configIndex  < pCurrentRadioArraySizesStruct(radioIndex)->radioConfigurationCount &&
       channelIndex < pCurrentRadioArraySizesStruct(radioIndex)->radioChannelListCount &&
       powerIndex   < pCurrentRadioArraySizesStruct(radioIndex)->radioPowerListCount){

      if(remote){
        RadioLocal.TxFrameStruct.frameHeader[NEW_RADIO_INDEX]   = radioIndex;   // Using this field to send radio index for now.(do not want to make changes to header length yet)              
        RadioLocal.TxFrameStruct.frameHeader[NEW_CONFIG_INDEX]  = configIndex;  // Config index
        RadioLocal.TxFrameStruct.frameHeader[NEW_CHANNEL_INDEX] = channelIndex; // Channel index
        RadioLocal.TxFrameStruct.frameHeader[NEW_POWER_COMMAND] = powerIndex;   // Power index

        TXFlags.TxConfigMessageType = SEND_CONFIG_REQUEST;
      }
      else{
        if(pCurrentFrameworkRadio()->radioState == RADIO_SLEEP){                // If radio is in sleep due to last timeout action      
          RadioWakeup(pCurrentFrameworkRadio());                                // Wake up the radio (SYNC_TIMEOUT_ACTION = SLEEP)
          pCurrentFrameworkRadio()->radioState = RADIO_CALIBRATED;              // Restore the radio state
        }

        RadioLocal.oldRadio = RadioLocal.currentRadio;                          // Update radio index
        RadioLocal.currentRadio = radioIndex;

        RadioSetRegister(pCurrentFrameworkRadio(), CCXXX_STRB_SIDLE, 0);        // Place selected radio in IDLE

        // Update config index and load new register settings into radio
        pCurrentConfigSettingsStruct()->oldRFICConfig = CurrentBaseConfig();
        pCurrentConfigSettingsStruct()->currentRFICConfig = configIndex;
        RadioConfigure(pCurrentFrameworkRadio(), &pCurrentRadioConfigurationStruct()->pRegisterSettings->registerSettings);

        // Update channel index and load new value into radio
        pCurrentConfigSettingsStruct()->oldRFChannelNum = CurrentChannel();
        pCurrentConfigSettingsStruct()->currentRFChannelNum = channelIndex;
        RadioChangeChannel(pCurrentFrameworkRadio(), &radio[RadioLocal.currentRadio].pRadioChannelList[pCurrentRadioConfigurationStruct()->pConfigurationChannel[CurrentChannel()].radioChannelIndex].radioChannel);

        // Update power index and load new value into radio
        pCurrentConfigSettingsStruct()->oldRFPower = CurrentPower();
        if(powerIndex < pCurrentRadioConfigurationStruct()->pConfigurationChannel[CurrentChannel()].radioPowerIndex){
          pCurrentConfigSettingsStruct()->currentRFPower = pCurrentRadioConfigurationStruct()->pConfigurationChannel[CurrentChannel()].radioPowerIndex;
        }
        else{
          pCurrentConfigSettingsStruct()->currentRFPower = powerIndex;
        }
        RadioChangePowerLevel(pCurrentFrameworkRadio(), &(radio[RadioLocal.currentRadio].pRadioPowerList[CurrentPower()].radioPower));

        #ifdef INCLUDE_FLASH_STORAGE
          WriteMyFlashedRSCP(radioIndex, configIndex, channelIndex, powerIndex);// If flash storage is enabled, save new settings
        #endif

        SetCycleTime(0, TACCR0);                                                // Restore the original cycle time
        if((TXFlags.TxConfigMessageType == SEND_CONFIG_PING) &&
           (RXFlags.RxConfigMessageType != RECEIVED_CONFIG_ACK)){
        }
        #if defined(__COMMAND_INTERFACE)
          PhysicalChanged();
        #endif
      }
      return 1;
    }
  }
  return 0;
}

/**
 * @fn void CreateDataPacket(uint8_t * pBufferIn, uint8_t countIn, uint8_t * pBufferOut, uint8_t * countOut)
 *
 * @brief This function loads the buffer to send the data out in the packet. It  
 *        sets the bit fields based on config change cycle flags, payload and 
 *        acknowledgement flags. It reads the RSSI, LQI and frequency offset 
 *        values from radio and places in the packet to give status update to the 
 *        remote module. At the end, it puts the payload data available from the 
 *        application, into the packet.
 *
 * @param pBufferIn an integer pointer
 * @param countIn an integer
 * @param pBufferOut an integer pointer
 * @param countOut an integer
 */
void CreateDataPacket(uint8_t * pBufferIn, uint8_t countIn, uint8_t * pBufferOut, uint8_t * countOut)
{
  *countOut = HEADER_LENGTH + countIn;

  pBufferOut[LENGTH] = *countOut - 1;				
  pBufferOut[DESTINATION_ADDR] = 0x00;                                          // Destination address;
  pBufferOut[SOURCE_ID] = 0x00;                                                 // Source node ID;

  pBufferOut[NEW_CONFIG_INDEX] &= 0x1F;                                         // Configuration;
  
  if(TXFlags.TxConfigMessageType == SEND_CONFIG_REQUEST){                       // 0x80 = Config Change Request,
     pBufferOut[NEW_CONFIG_INDEX] |= 0x80;
  }
  else if(TXFlags.TxConfigMessageType == SEND_CONFIG_ACK){                      // 0x40 = Config Change ACK,
     pBufferOut[NEW_CONFIG_INDEX] |= 0x40;
  }
  else if(TXFlags.TxConfigMessageType == SEND_CONFIG_PING){                     // 0x20 = Config change ping,
     pBufferOut[NEW_CONFIG_INDEX] |= 0x20;
  }

  pBufferOut[NEW_POWER_COMMAND] &= 0x3F;                                        // Power and Command;
  
  if(TXFlags.TxACKMessageType == SEND_ACK){                                     
    pBufferOut[NEW_POWER_COMMAND] |= 0x80;                                      // 0x80 = ACK for received data,  
  }
  if(countIn){
    pBufferOut[NEW_POWER_COMMAND] |= 0x40;                                      // 0x40 = Payload is a data,                                        
  }
  
  pBufferOut[RSSI_RECEIVER] = RadioLocal.linkStatus[RSSI];                      // RSSI @ receiver
  pBufferOut[LQI_RECEIVER] = RadioLocal.linkStatus[LQI];	                // LQI @ receiver
  pBufferOut[FREQ_OFFSET_RECEIVER] = RadioGetRegister(pCurrentFrameworkRadio(), CCXXX_STAT_FREQEST); // Frequency offset @ receiver

  pBufferOut[CURRENT_POWER_INDEX] = pCurrentConfigSettingsStruct()->currentRFPower; // Power @ receiver

  if(TXFlags.TxPayloadMessageType == SEND_PAYLOAD){
    for(uint8_t i=0;i<countIn;i++){
      pBufferOut[HEADER_LENGTH+i] = *(pBufferIn + i);                           // Payload
    }
  }
}

/**
 * @fn void CycleTimeoutAction(AppRadio * radio, uint8_t action)
 *
 * @brief This function performs the cycle timeout action based on the action provided
 *
 * @param radio an AppRadio structure pointer
 * @param action an integer
 */
void CycleTimeoutAction(AppRadio * radio, uint8_t action)
{
  if(action == SET_RADIO_IDLE){
    RadioSetRegister(pCurrentFrameworkRadio(), CCXXX_STRB_SIDLE, 0);            // Strobe Idle
    pCurrentFrameworkRadio()->radioState = RADIO_CALIBRATED;                    // Update radio state
  }
  else{
    RadioSleep(pCurrentFrameworkRadio());                                       // Put radio to sleep
    pCurrentFrameworkRadio()->radioState = RADIO_SLEEP;                         // Update radio state
  }
}

/**
 * @fn void ReceiveOn(AppRadio* radio)
 *
 * @brief This function performs steps necessary to put the radio in receive mode.
 *        It flushes the receive FIFO, enables the GDO0 interrupt at rising edge
 *        to check if sync word in received. It then updates radio and frame states
 *        and strobes receive command.
 *
 * @param radio an AppRadio structure pointer
 */
void ReceiveOn(AppRadio* radio)
{
  RadioSetRegister(pCurrentFrameworkRadio(), CCXXX_STRB_SIDLE, 0);              // Strobe Idle
  RadioSetRegister(pCurrentFrameworkRadio(), CCXXX_STRB_SFRX, 0);               // Strobe flush RX FIFO

  __BOARD_RADIO1_GDO0ENABLE = 0;                                                // GDO0 interrupt enabled at rising edge to check if sync word received
  __BOARD_RADIO1_GDO0EDGESELECT = 0;
  __BOARD_RADIO1_GDO0FLAG = 0;
  __BOARD_RADIO1_GDO0ENABLE = 1;

  pCurrentFrameworkRadio()->radioState = RADIO_RECEIVE;                         // Update radio state
  RadioLocal.FrameState = WAITING_FOR_SYNCWORD;                                 // Update frame state
  RadioSetRegister(pCurrentFrameworkRadio(), CCXXX_STRB_SRX, 0);                // Strobe RX
}

/**
 * @fn AppRadioArraySizes * pCurrentRadioArraySizesStruct(uint8_t currentRadio)
 *
 * @brief This function returns the pointer to array size of the Radio in use.
 *
 * @param currentRadio an unsigned int
 *
 * @return an AppRadioArraySizes structure pointer
 */
AppRadioArraySizes * pCurrentRadioArraySizesStruct(uint8_t currentRadio)
{
  return radio[currentRadio].pRadioArraySizes;                                  // Pointer to the array size of current radio.
}

/**
 * @fn ConfigStruct * pCurrentConfigSettingsStruct(void)
 *
 * @brief This function returns the current configuration in use for current radio.
 *
 * @return a ConfigStruct structure pointer
 */
ConfigStruct * pCurrentConfigSettingsStruct(void)
{
  return &ConfigSettings[RadioLocal.currentRadio];                              // Current configuration is use for current radio.
}

/**
 * @fn AppRadioConfiguration * pCurrentRadioConfigurationStruct(void)
 *
 * @brief This function returns the pointer to the current configuration structure 
 *        in use for current radio.
 *
 * @return an AppRadioConfiguration structure pointer
 */
AppRadioConfiguration * pCurrentRadioConfigurationStruct(void)
{
  return &radio[RadioLocal.currentRadio].pRadioConfiguration[CurrentBaseConfig()]; // Pointer to the current configuration structure in use for current radio.
}

/**
 * @fn Radio * pCurrentFrameworkRadio(void)
 *
 * @brief This function returns the pointer to current framework radio in use.
 *
 * @return a Radio structure pointer
 */
Radio * pCurrentFrameworkRadio(void)
{
  return &radio[RadioLocal.currentRadio].frameworkRadio;                        // Pointer to current Framework Radio in use
}

/**
 * @fn uint8_t CurrentRadio(void)
 *
 * @brief Returns the index of current radio in use
 *
 * @return an integer
 */
uint8_t CurrentRadio(void)
{
  return RadioLocal.currentRadio;                                               // Current Radio in use
}

/**
 * @fn uint8_t CurrentBaseConfig(void)
 *
 * @brief Returns the index of current configuration set
 *
 * @return an integer
 */
uint8_t CurrentBaseConfig(void)
{
  return pCurrentConfigSettingsStruct()->currentRFICConfig;                     // Current Config for CCxxxx
}

/**
 * @fn uint8_t CurrentChannel(void)
 *
 * @brief Returns the index of current channel in use
 *
 * @return an integer
 */
uint8_t CurrentChannel(void)
{
  return pCurrentConfigSettingsStruct()->currentRFChannelNum;                   // Current Channel Number for CCxxxx
}

/**
 * @fn uint8_t CurrentPower(void)
 *
 * @brief Returns the index of current power setting in use
 *
 * @return an integer
 */
uint8_t CurrentPower(void)
{
  return pCurrentConfigSettingsStruct()->currentRFPower;                        // Current Power for CCxxxx
}

/**
 * @fn uint8_t PowerUpResetCCxxxx(AppRadio * radio)
 *
 * @brief Resets the radio upon power up.
 *
 * @param radio an AppRadio structure pointer
 *
 * @return an integer
 */
uint8_t PowerUpResetCCxxxx(AppRadio * radio)                                    
{
  ClearGPIOOutputPort(__BOARD_RADIO1_CSNPORT, __BOARD_RADIO1_CSNPIN);           // Set CSn low
  for(uint16_t i=0;i<60000;i++){
    if(!(__BOARD_RADIO1_MISOPORT_IN & __BOARD_RADIO1_MISOPIN)){                 // Wait until SOMI is low
      RadioSetRegister(&radio[RadioLocal.currentRadio].frameworkRadio, CCXXX_STRB_SRES, 0); // CCxxxx_STRB_SRES : reset the chip
      SetGPIOOutputPort(__BOARD_RADIO1_CSNPORT, __BOARD_RADIO1_CSNPIN);         // Set CSn low
      return 1;
    }
  }
  SetGPIOOutputPort(__BOARD_RADIO1_CSNPORT, __BOARD_RADIO1_CSNPIN);
  return 0;
}

/**
 * @fn uint8_t ReadMARCSTATE(AppRadio * radio)
 *
 * @brief This radio reads the current state of the MARCSTATE status reg for CCxxxx. 
 *        It must be read up to 4 times(see errata).
 *
 * @param radio an AppRadio structure pointer
 *
 * @return an integer
 */
uint8_t ReadMARCSTATE(AppRadio * radio)
{
  uint8_t loopCount, localStatus[4];
  // Read the current state of MARCSTATE status reg for CCxxxx.  Must be read up to 4 times (see device errata).
  localStatus[0] = RadioGetRegister(pCurrentFrameworkRadio(), CCXXX_STAT_MARCSTATE);
  for(loopCount=1;loopCount<4;loopCount++){
    localStatus[loopCount] = RadioGetRegister(pCurrentFrameworkRadio(), CCXXX_STAT_MARCSTATE);
    if ( localStatus[loopCount] == localStatus[loopCount-1] )
    { 
      return localStatus[loopCount];
    }
  }
  return -1;
}

/**
 * @fn void RadioOperation(void)
 *
 * @brief ISR extension of Communication Module 1 ISR. This functionality is
 *        currently not implemented.
 */
void RadioOperation(void)
{
}

/**
 * @fn signed int RSSI2dBm(unsigned char rssi)  
 *
 * @brief This function shifts the RSSI value to have the decimal point between 
 *        the two bytes in the integer and adds offset to it(see CC110L datasheet).
 *
 * @param rssi an unsigned int
 *
 * @return signed int
 */
signed int RSSI2dBm(unsigned char rssi) 
{
  signed int temp, offset;
  temp = (rssi < 128 || rssi >= 148) ? (signed int)(signed char)rssi : -108;    // Remove -128.5dBm to -138dBm range since they exceed size of data type and are not valid values from radio
  temp <<= 7;                                                                   // RSSI is in 1/2 dB's, move it up to have the decimal point between the two bytes in the int
  offset = -74 * 256;                                                           // hardcoded for now, recommended value from CC110L datasheet
  // This really should be an offset specifically measured for each config setting......
  temp += offset;                                                               //Radio...etc...RSSI_Offset.
  return temp;
}
