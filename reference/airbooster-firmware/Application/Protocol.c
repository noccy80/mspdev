/**
 *  @file Protocol.c
 *
 *  @brief Protocol Layer Function Definitions
 *         This file defines the functions for operation of each application 
 *         state in the protocol, i.e. sensor and hub. Function definitions for 
 *         Protocol Layer Command-Interface are included within this file.
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
extern RXFlagStruct RXFlags;
extern TXFlagStruct TXFlags;
extern TimerStruct TimerLocal;

extern RFChannel RadioFCCChannels[];
extern RFPowerSettings RadioFCCPowerSettings[];
extern RFSettings RadioFCCSettings[];

extern uint8_t configTimeoutCount;

unsigned char CountDown = 0x00;

/**
 * @fn void InitProtocol(void)
 *
 * @brief This function initializes the radio for the protocol
 */
void InitProtocol(void)
{
  InitRadio(radio);                                                             // Initialize radio to default config, channel and power 
}

/**
 * @fn uint8_t DataExchange(uint8_t * pBuffer, uint8_t *count)
 *
 * @brief This function performs the initiates a data exchange.
 *        In the beginning it checks if the radio is in sleep mode due to last
 *        timeout, if it is, it wakes up the radio. It sends a frame with the 
 *        payload data, waits to get the ACK and data, and if a config change was 
 *        requested in the ack it will support completion with an ack back.
 *        If a config change request is to be sent, it initiates and completes
 *        the config change cycle.
 *
 * @param pBuffer an integer pointer
 * @param count an integer pointer, provides the number of bytes to be sent and
 *        sets the max number that can be recieved and returns the actual 
 *        payload length delivered.
 *
 * @return an integer
 */
uint8_t DataExchange(uint8_t * pBuffer, uint8_t *count)
{
  if(pCurrentFrameworkRadio()->radioState == RADIO_SLEEP){                      // If radio is in sleep due to last timeout action      
    RadioWakeup(pCurrentFrameworkRadio());                                      // Wake up the radio (SYNC_TIMEOUT_ACTION = SLEEP)
    pCurrentFrameworkRadio()->radioState = RADIO_CALIBRATED;                    // Restore the radio state
  }
  
  TXFlags.TxPayloadMessageType = SEND_PAYLOAD;
  TXFlags.TxACKMessageType = SEND_NO_ACK;
  if(TXFlags.TxConfigMessageType != SEND_CONFIG_REQUEST){
    if(FrameSend(radio, pBuffer, *count, EOP_TIMEOUT, EOP_TIMEOUT_ACTION)){     // Send sensor data to the hub
      if(FrameListen(radio, pBuffer, count, SYNC_TIMEOUT, SYNC_TIMEOUT_ACTION)){// Wait for ACK and data from hub
        RXTXCycle(radio, pBuffer, count);                                       // Send ACK back to hub
        if(RXFlags.RxPayloadMessageType == RECEIVED_PAYLOAD){
          return 1;
        }
      }
    }
  }
  else{
    return RXTXCycle(radio, pBuffer, count);                                    // If config request to be sent, perform the config change sequence
  }
  return 0;
}


/**
 * @fn uint8_t Listen(uint8_t * pBuffer, uint8_t * pCount)
 *
 * @brief This function performs the operation of Application State - Hub. It checks
 *        to see if a frame is received, if so, it reads the data from radio. If
 *        payload is received, it processes the packet and sends ACK and data back,
 *        and places radio in receive mode to listen for the ACK. It initiates or 
 *        responds to config change and completes the cycle. At the end it checks 
 *        if frane timeout is occured, if so, it checks if the radio is in receive 
 *        mode. If its not, then it places radio back to receive mode to listen for
 *        the next frame.
 *
 * @param pBuffer an integer pointer
 * @param pCount an integer pointer
 *
 * @return an integer
 */
uint8_t Listen(uint8_t * pBuffer, uint8_t * pCount)
{
  uint8_t tempVar = 0;
  PayloadFrame *ackPayload;
  unsigned char ackCount;
  
  if(RadioLocal.FrameState == FRAME_RECEIVED){                                  // Check to see if a frame has been received.
    GetFrame(radio, pBuffer, pCount);                                           // Read data from radio.
    if((RXFlags.RxPayloadMessageType == RECEIVED_PAYLOAD) && (RXFlags.RxACKMessageType == RECEIVED_NO_ACK)){
      ackPayload = NodeAckPayload(((PayloadFrame *)pBuffer)->NodeID);           // Inform application if payload data was received.
      TXFlags.TxPayloadMessageType = SEND_PAYLOAD;
      if (ackPayload){                                                          // If payload received from sensor, send ACK and data back to sensor
        ackCount = sizeof(PayloadFrame);
        RXTXCycle(radio, (uint8_t *)ackPayload, &ackCount);
      }
      tempVar = 1;
    }
    else if((RXFlags.RxPayloadMessageType == RECEIVED_NO_PAYLOAD) && (RXFlags.RxACKMessageType == RECEIVED_NO_ACK)){
      RXTXCycle(radio, pBuffer, pCount);
    }
    ReceiveOn(radio);                                                           // Place radio back into receive mode.
    return tempVar;
  }
  else if(TXFlags.TxConfigMessageType == SEND_CONFIG_REQUEST){                  
    if(TimerLocal.configTimeout){                                               
      TimerLocal.configTimeout = 0;
      TXFlags.TxConfigMessageType = SEND_NO_CONFIG_CHANGE;                      // If Config timeout occured, abort current config change cycle
      ProvideDelayedResult(0);                                                  // Tell the GUI that we failed
    }
  }

  if((RadioLocal.FrameState != WAITING_FOR_EOP) || TimerLocal.frameTimeout){    // If frame timeout occured, check if radio is in Receive
    TimerLocal.frameTimeout = 0;
    uint8_t temp = ReadMARCSTATE(radio);
    if(!(temp == 13 || temp == 14 || temp == 15)){
      ReceiveOn(radio);                                                         // If not, place it back in receive to wait for next packet from sensor
    }
  }
  return 0;
}


/**
 * @fn uint8_t RXTXCycle(AppRadio * radio, uint8_t * pBuffer, uint8_t * pCount)
 *
 * @brief This function performs the config change cycle. It is divided into two parts
 *        based on the Initiator and Receiver operation.
 *        
 *        Initiator Operation: It sends a config change request and waits for its ACK.
 *        If an CONFIG_ACK is received, It switches to the new configuration itself,
 *        and sends a config ping. If it receives an ACK for the ping, it returns, 
 *        else it reverts back to old config and sends a config ping. If it receives
 *        an ACK for the ping, it returns. Else it goes to new config and concludes 
 *        that the other module changed to new config and missed the first ping 
 *        for some reason. 
 *        
 *        Receiver Operation: It receives a config change request and sends an ACK for 
 *        that. Then it switches to new config and listens for the config ping. If it
 *        receives config ping, it sends the ACK back and returns. Else it reverts to 
 *        old config and listens for a another config ping. It it receives one, it 
 *        sends an ACK back and returns. Else it goes to new config and concludes 
 *        that it missed the first config ping for some reason.
 *
 *        If none of these conditions are true, it checks if a payload is received and
 *        ACK is to be sent, if yes, it sends the ACK and returns.
 *
 * @param radio an AppRadio structure pointer
 * @param pBuffer an integer pointer
 * @param pCount an integer pointer
 *
 * @return an integer
 */
uint8_t RXTXCycle(AppRadio * radio, uint8_t * pBuffer, uint8_t * pCount)
{
  uint8_t tempVar = 0;
  
  // Config Change Receiver: Check to see if we received a config change request.  If so, send a config change ACK then change config.
  if(RXFlags.RxConfigMessageType == RECEIVED_CONFIG_REQUEST){
    TXFlags.TxConfigMessageType = SEND_CONFIG_ACK;
    FrameSend(radio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION);        // Send ACK for config change request and change to the new config
    ChangeConfiguration(0, RadioLocal.RxFrameStruct.frameHeader[NEW_RADIO_INDEX], (RadioLocal.RxFrameStruct.frameHeader[NEW_CONFIG_INDEX] & 0x1F), 
                        RadioLocal.RxFrameStruct.frameHeader[NEW_CHANNEL_INDEX], (RadioLocal.RxFrameStruct.frameHeader[NEW_POWER_COMMAND] & 0x3F));
    if(FrameListen(radio, pBuffer, pCount, CONFIG_TIMEOUT, CONFIG_TIMEOUT_ACTION)){// Check if config ping received
      if(RXFlags.RxConfigMessageType == RECEIVED_CONFIG_PING){
        TXFlags.TxConfigMessageType = SEND_CONFIG_ACK;
        FrameSend(radio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION);    // Send config ACK
        TXFlags.TxConfigMessageType = SEND_NO_CONFIG_CHANGE;
        return tempVar;
      }
    }
    else{                                                                       // If config ping not received
      // Configuration change sequence failed, revert back to previous settings 
      ChangeConfiguration(0, RadioLocal.oldRadio, pCurrentConfigSettingsStruct()->oldRFICConfig, pCurrentConfigSettingsStruct()->oldRFChannelNum, pCurrentConfigSettingsStruct()->oldRFPower);
      if(FrameListen(radio, pBuffer, pCount, CONFIG_TIMEOUT, CONFIG_TIMEOUT_ACTION)){  // Check if config ping received
        if(RXFlags.RxConfigMessageType == RECEIVED_CONFIG_PING){
          TXFlags.TxConfigMessageType = SEND_CONFIG_ACK;
          FrameSend(radio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION);  // Send config ACK
        }
      }
    }
  }

  // Config Change Initiator:
  else if(TXFlags.TxConfigMessageType == SEND_CONFIG_REQUEST){
    if(FrameSend(radio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION)){    // Send config change request
      if(FrameListen(radio, pBuffer, pCount, SYNC_TIMEOUT, CONFIG_TIMEOUT_ACTION)){
        if(RXFlags.RxPayloadMessageType == RECEIVED_PAYLOAD){
          tempVar = 1;
        }
        if(RXFlags.RxConfigMessageType == RECEIVED_CONFIG_ACK){                 // Check to see if we received a config change request ACK.  If so, change to new config.
          ChangeConfiguration(0, RadioLocal.TxFrameStruct.frameHeader[NEW_RADIO_INDEX], (RadioLocal.TxFrameStruct.frameHeader[NEW_CONFIG_INDEX] & 0x1F), 
                              RadioLocal.TxFrameStruct.frameHeader[NEW_CHANNEL_INDEX], (RadioLocal.TxFrameStruct.frameHeader[NEW_POWER_COMMAND] & 0x3F));
          if(SendConfigPingSequence(pBuffer, pCount)) return tempVar;
          // Configuration change sequence failed, revert back to previous settings
          ChangeConfiguration(0, RadioLocal.oldRadio, pCurrentConfigSettingsStruct()->oldRFICConfig, pCurrentConfigSettingsStruct()->oldRFChannelNum, pCurrentConfigSettingsStruct()->oldRFPower);
          if(SendConfigPingSequence(pBuffer, pCount)) return tempVar;
          ChangeConfiguration(0, RadioLocal.oldRadio, pCurrentConfigSettingsStruct()->oldRFICConfig, pCurrentConfigSettingsStruct()->oldRFChannelNum, pCurrentConfigSettingsStruct()->oldRFPower);
        }
      }
    }
    ProvideDelayedResult(0);                                                    // Tell the GUI that we failed
    TXFlags.TxConfigMessageType = SEND_NO_CONFIG_CHANGE;                        // Abort current config change cycle
  }

  else if(RXFlags.RxConfigMessageType == RECEIVED_CONFIG_PING){                 // Received packet is a config change ping, so send a config change ACK
      TXFlags.TxConfigMessageType = SEND_CONFIG_ACK;
      FrameSend(radio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION);
      return tempVar;
    }

  else if(RXFlags.RxPayloadMessageType == RECEIVED_PAYLOAD){                    // Received packet has payload data, so send an ACK
    TXFlags.TxACKMessageType = SEND_ACK;
    if((pBuffer == NULL) || (pCount == NULL)){
      FrameSend(radio, NULL, 0, EOP_TIMEOUT, EOP_TIMEOUT_ACTION);               // If no payload is to be sent
    }
    else{
      FrameSend(radio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION);      // If payload is to be sent
    }
  }
  return tempVar;
}

/**
 * @fn void StartTimer(void)
 *
 * @brief Start the timer in up mode
 */
void StartTimer(void)
{
  TACTL |= MC_1;                                                                // Start in up mode
}

/**
 * @fn unsigned char SetCycleTime(unsigned char ID, unsigned int newCycleTime)
 *
 * @brief This function checks whether the cycle time entered by the user is 
 *        greater than the minimum cycle time corresponding to current config.
 *        If so, it sets the new cycle time. If not, it sets the minimum cycle
 *        time corresponding to the current config.
 *
 * @param ID an unsigned char
 * @param newCycleTime an unsigned int
 *
 * @return an unsigned char
 */
unsigned char SetCycleTime(unsigned char ID, unsigned int newCycleTime)
{
  // If the cycle time provided by the user is greater than the minimum cycle time, assign it to current cycle time
  if(newCycleTime >= pCurrentRadioConfigurationStruct()->pRegisterSettings->configCycleTimeout.cycleTime){
    Nodes[ID].CurrentCycleTime = newCycleTime;
  }
  else{                                                                         // If not then load the minimum cycle time value
    Nodes[ID].CurrentCycleTime = pCurrentRadioConfigurationStruct()->pRegisterSettings->configCycleTimeout.cycleTime;
  }
  TACCTL0 &= ~CCIE;
  TAR = 0;
  TACCR0 = Nodes[0].CurrentCycleTime;                                           // Load the cycle time into TACCR0
  TACCTL0 |= CCIE;
  return 1;
}


/**
 * @fn void Query_Current_Status(PayloadFrame *payload)
 *
 * @brief This function checks if its the time to report the status. If yes, 
 *        It populates the status information in its own node structure.
 *
 * @param payload a PayloadFrame structure pointer
 */
void Query_Current_Status(PayloadFrame *payload)
{
  unsigned char i;
  i = NodeIsInMyNet(payload->NodeID);                                           // Check if the node is in my net
  if (i) {                                                                      // Load status bytes into my  node structure
    #ifdef INCLUDE_FRAMECOUNTER_STATUS
      Nodes[i].FrameCounter++;
    #endif
      Nodes[0].LastRSSI = RadioGetRegister(pCurrentFrameworkRadio(), CCXXX_STAT_RSSI);
      Nodes[i].LastRSSI = RadioLocal.RxFrameStruct.frameHeader[RSSI_RECEIVER];
    #ifdef INCLUDE_LQI_STATUS
      Nodes[i].LastLocalLQI  = RadioGetRegister(pCurrentFrameworkRadio(), CCXXX_STAT_LQI) & 0x7F;
      Nodes[i].LastRemoteLQI = RadioLocal.RxFrameStruct.frameHeader[LQI_RECEIVER] & 0x7F;
    #endif
    #ifdef INCLUDE_FREQOFF_STATUS
      Nodes[i].LastLocalFoff  = ~(RadioGetRegister(pCurrentFrameworkRadio(), CCXXX_STAT_FREQEST) - 1);
      Nodes[i].LastRemoteFoff = ~(RadioLocal.RxFrameStruct.frameHeader[FREQ_OFFSET_RECEIVER] - 1);
    #endif
    #ifdef INCLUDE_POWER_STATUS
      Nodes[i].LastLocalPower  = CurrentPower();
      Nodes[i].LastRemotePower = RadioLocal.RxFrameStruct.frameHeader[CURRENT_POWER_INDEX];
    #endif
    #ifdef INCLUDE_CHANNEL_STATUS
      Nodes[i].LastUsedChannel = CurrentChannel();
    #endif
  }
}

/**
 * @fn uint8_t SendConfigPingSequence(uint8_t * pBuffer, uint8_t * pCount)
 *
 * @brief This function performs the config ping sequence. It sends the config 
 *        ping and listens for ACK. This sequence is continued until config timeout 
 *        occurs. If config ACK is received, config change cycle is finished.
 *
 * @param pBuffer an unsigned integer pointer
 * @param pCount an unsigned integer pointer
 *
 * @return an unsigned int
 */
uint8_t SendConfigPingSequence(uint8_t * pBuffer, uint8_t * pCount)
{
  TAR = 0;
  configTimeoutCount = 1;                                                       // Set timer count initial value (timeout declared when counter reaches 0)
  TimerLocal.configTimeout = 0;
  while(!TimerLocal.configTimeout){
    TXFlags.TxConfigMessageType = SEND_CONFIG_PING;
    if(FrameSend(radio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION)){    // Send config ping
      if(FrameListen(radio, pBuffer, pCount, SYNC_TIMEOUT, CONFIG_TIMEOUT_ACTION)){// Check if ACK for config ping is received
        if(RXFlags.RxConfigMessageType == RECEIVED_CONFIG_ACK){
          ProvideDelayedResult(1);                                              // Tell the GUI that we passed
          TXFlags.TxConfigMessageType = SEND_NO_CONFIG_CHANGE;                  // Clear the flag to indicate that the config cycle is finished
          configTimeoutCount = 0;
          TimerLocal.configTimeout = 0;
          return 1;
        }
      }
    }
  }
  return 0;
}
