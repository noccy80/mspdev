/**
 *  @file Application.c
 *
 *  @brief Application Layer Function Definitions
 *         This file defines the functions for Application-State Operations, 
 *         Network Setup and Validation.
 *         Function definitions for Application Layer Command-Interface are 
 *         included within this file.
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

#include "../Framework/FPI/FPI.h"
#include "Application.h"
#include "protocol.h"
#include "RadioOperation.h"
#include "CommandInterface.h"

extern DataDefinition *DataDefinitions[];

__ApplicationState ApplicationState = HUB;

/*! The pairingMask is used as a mask to all AddNodeIDToNetwork() calls. A zero 
  mask will not allow any nodes to be added to the network (paired) and 
  a 0xFFFFFFFF mask will allow any node to be added (provided there is room left 
  in the array holding the node ID's).
  Since the protocol ALLWAYS will attempt to add an unknown node to the network, 
  the pairingMaks is the only means for controlling pairing.
*/
unsigned long pairingMask;
NodeInfo Nodes[MAX_NODES] = {0};

/*! If the payload frame is bigger than what will fit in the radio frame 
  then PAYLOAD_SIZE_VALIDATION will evaluate to -1 and a compiler error will 
  be generated on the below allocation. If the payload size will fit then 
  PAYLOAD_SIZE_VALIDATION will evaluate to 1, and no compile errors will
  be generated. This 'quirky' construction is necessary because the pre-processor 
  does not know the sizes of things and we want to generate a compile error 
  to avoid overwriting other data areas (without costly run time checks).
*/
PayloadFrame Payloads[2*PAYLOAD_SIZE_VALIDATION];                               // Allows us to buffer payloads or prepare seperate payloads, should we so desire
#define NodeAckTempFrame ((sizeof(Payloads)/sizeof(PayloadFrame))-1)            //!< Use the last(does not mean previous, it means the highest index!) payload for node acks
#define IncommingFrame 0
#define SensorSendFrame 0


/**
 * @fn uint8_t HubWirelessOperation(void)
 *
 * @brief This function listens for incoming frames, qualifies the data as 
 *        being from a network member, and if so copies data to Nodes[].InData[]
 *        and returns the node IDindex that it came from
 *
 * @return an unsigned int, IDindex; >0 is valid, =0 is invalid/no data
 */
uint8_t HubWirelessOperation(void)
{
  uint8_t IDindex;
  uint8_t ByteCount;
  if (Listen((uint8_t *)&Payloads[0], &ByteCount)) {                            // Listen for a packet from remote (sensor/actuator)
    //We should perhaps check here if we got a full payload?
    IDindex = NetworkValidation(&Payloads[IncommingFrame]);                     // Data from the radio is available, check if its from a member, if so copy the data and return the node index it came from.
    if (IDindex){
      //If there is a need to do something with the data here.....
      return IDindex;                                                           // Allow main() to be notified of the newly arrived data, which is now in Nodes[].InData[]
    }
  }
  return 0;                                                                     // There is no data or it was not from a network member
}

/**
 * @fn uint8_t SensorWirelessOperation(void)
 *
 * @brief This function initiates a data exchange, qualifies any received data as 
 *        being from a network member, and if so copies data to Nodes[].InData[]
 *        and returns the node IDindex that it came from
 *
 * @return an unsigned int, IDindex; >0 is valid, =0 is invalid/no data
 */
uint8_t SensorWirelessOperation(void)
{
  uint8_t IDindex;
  uint8_t ByteCount = sizeof(PayloadFrame);
  //If there is a need to do additional stuff prior to send, do it here!
  if (DataExchange((uint8_t *)(SensorPayload()), &ByteCount)) {                 // Prepare the sensor/actuator payload and initiate data exchange
    //We should perhaps check here if we got a full payload?
    if (ByteCount != sizeof(PayloadFrame)) {
      DebugNote("Sensor received; frame < payload");                            // Temporary, just for debugging the DebugNote() for GUI
    }
    IDindex = NetworkValidation(&Payloads[0]);                                  // Data from the radio is available, check if its from a member, if so copy the data and return the node index it came from.
    if (IDindex){
      if(Nodes[0].CurrentCycleTime != Payloads[0].CycleTime){
        SetCycleTime(0, Payloads[0].CycleTime);
      }
      //If there is a need to do something more with the arrived data, do it here.....
      return IDindex;                                                           // Allow main() to be notified of the newly arrived data, which is now in Nodes[].InData[]
    }
  }
  return 0;                                                                     // There is no data or it was not from a network member
}

/**
 * @fn uint8_t SetApplicationState(__ApplicationState state) 
 *
 * @brief This function sets the application state of the node. If flash storage
 *        is included, it writes the state to flash.
 *
 * @param state an __ApplicationState enumeration
 *
 * @return an unsigned int
 */
uint8_t SetApplicationState(__ApplicationState state) 
{
  #ifdef INCLUDE_FLASH_STORAGE
    FlashWriteChar(&MyFlashedAppState,(uint8_t)state);                          // Write application state to Flash
  #endif
  ApplicationState = state;
  ApplicationChanged();
  return 1;
}

/**
 * @fn unsigned char SetMyNodeID(unsigned long NodeID)
 *
 * @brief This function sets the node ID of the node itself. If flash storage is
 *        included, it writes its own ID to flash. If command interface is included,
 *        it makes a call to a function to inform the GUI that a network change has 
 *        taken place.
 *
 *        Providing NodeID with a value of zero or 0xFFFFFFFF will cause ID to be
 *        read from flash if flash storage is included.  If the ID in flash is
 *        equal to zero or 0xFFFFFFFF, or if flash storage is not included, a new
 *        random ID will be created.
 *
 * @param NodeID an unsigned long
 *
 * @return an unsigned char
 */
unsigned char SetMyNodeID(unsigned long NodeID) 
{
  if ((NodeID != 0) && (NodeID != 0xFFFFFFFF)) {
    Nodes[0].ID = NodeID;
    #ifdef INCLUDE_FLASH_STORAGE
      WriteMyFlashedID(NodeID);                                                 // Also flash it so it starts up this way;
    #endif
    #ifdef __COMMAND_INTERFACE
      NetworkChanged();
    #endif
    return 1;                                                                   // Return 1 only when Nodes[0].ID set to NodeID arg
  }
  else {
    #ifdef INCLUDE_FLASH_STORAGE
      NodeID = ReadMyFlashedID();
    #endif
    if ((NodeID == 0) || (NodeID == 0xFFFFFFFF)) {
      NodeID = CreateRandomAddress();
      #ifdef INCLUDE_FLASH_STORAGE
        WriteMyFlashedID(NodeID);                                               // Also flash it so it starts up this way;
      #endif
    }
    Nodes[0].ID = NodeID;
    #ifdef __COMMAND_INTERFACE
      NetworkChanged();
    #endif
  }
  return 0;
}

/**
 * @fn inline void SetPairingMask(unsigned long mask)
 *
 * @brief This function sets the pairing mask for the node. If command interface 
 *        is included, it makes a call to a function to inform the GUI that a 
 *        network change has taken place.
 *
 * @param mask an unsigned long
 */
inline void SetPairingMask(unsigned long mask) 
{
  pairingMask = mask;
  #ifdef __COMMAND_INTERFACE
    NetworkChanged();
  #endif
}

/**
 * @fn inline unsigned long GetPairingMask(void)
 *
 * @brief This function returns the pairing mask of the node.
 *
 * @return an unsigned long
 */
inline unsigned long GetPairingMask(void) 
{
  return pairingMask;
}

/**
 * @fn unsigned char NodeIsInMyNet(unsigned long NodeID) 
 *
 * @brief The node ID array is defined to have this node as index 0. it is also 
 *        defined that a node ID of 0 is an invalid ID. When searching to see if
 *        a NodeID is in the network list this function will return the index 
 *        number to the ID if it was found and 0 (index to this node) if it was 
 *        not found.
 *
 * @param NodeID an unsigned long
 *
 * @return an unsigned char
 */
unsigned char NodeIsInMyNet(unsigned long NodeID) 
{
  unsigned char i;
  for (i=1;i<MAX_NODES;i++) {
    if (NodeID) {                                                               // We do not accept requests for ID==0
      if (NodeID == Nodes[i].ID) return i;
    }
  }
  return 0;
}

/**
 * @fn unsigned char AddNodeToNetwork(unsigned long NodeID)
 *
 * @brief This function adds a paired node to the network. It checks if the node 
 *        is already in the network. If not, it checks if the ID has the content 
 *        within the mask, if yes, then it finds a spot for the node. If command  
 *        interface is included, it makes a call to a function to inform the GUI  
 *        that a network change has taken place.
 *
 * @param NodeID an unsigned long
 *
 * @return an unsigned char
 */
unsigned char AddNodeToNetwork(unsigned long NodeID) 
{
  unsigned char i;
  if (i=NodeIsInMyNet(NodeID)) {
    return i;                                                                   // We don't want to add it more than once
  } else {
    // ID cannot have content outside the mask but must have content within the mask
    if ((!(NodeID & ~pairingMask)) && (NodeID & pairingMask)) {                 // Node is qualified for membership or knows someone high up......
      for (i=1;i<((ApplicationState == HUB) ? MAX_NODES:2);i++) {               // Only the Hub is allowed more than one node
        if (Nodes[i].ID == 0) {                                                 // we found a spot for it
          Nodes[i].ID = NodeID;
          if (ApplicationState == SENSOR) {
            SetPairingMask(0);                                                  // The sensor is paired up, so close for any further pairing
            SetApplicationState(SENSOR);                                        // Keep node in SENSOR mode if pairing was successful
          } else {                                                              // Avoid double network changed notifications
            #ifdef __COMMAND_INTERFACE
              NetworkChanged();
            #endif
          }
          return i;
        }
      }
    }
  }
  return 0;
}

/**
 * @fn unsigned char RemoveNodeFromNetwork(unsigned char NodeIndex)
 *
 * @brief This function removes the node from the network. It checks if the node
 *        index is valid, if so, it clears all the data so the the spot can be 
 *        taken by the new node. If command interface is included, it makes a call
 *        to a function to inform the GUI that a network change has taken place.
 *
 * @param NodeIndex an unsigned char
 *
 * @return an unsigned char
 */
unsigned char RemoveNodeFromNetwork(unsigned char NodeIndex) 
{
  unsigned char i;
  if ((NodeIndex) && (NodeIndex < MAX_NODES)) {
    Nodes[NodeIndex].ID = 0;                                                    // What node? I've never heard of him.....
    for (i=0;i<DATA_CHANNELS;i++) {
      Nodes[NodeIndex].OutData[i] = 0;                                          // Clear also the data area so a new node taking this spot would not inherit this nodes data
    }
    Nodes[NodeIndex].CurrentCycleTime = 0;
    Nodes[NodeIndex].FrameCounter=0;
    #ifdef __COMMAND_INTERFACE
      NetworkChanged();
    #endif
    return 1;
  }
  return 0;
}

/**
 * @fn unsigned char NetworkValidation(PayloadFrame *AppFrame) 
 *
 * @brief This function performs network validation by checking the pairing with 
 *        the node. If the node is not paired with, it adds it to the network. 
 *        Else it checks if the node is already in the network. If command interface 
 *        is included, it makes a call to a function to output the data and RSSI from the node.
 *
 * @param AppFrame a PayloadFrame structure pointer
 *
 * @return an unsigned char
 */
unsigned char NetworkValidation(PayloadFrame * AppFrame) 
{
  unsigned char i,k;
  if (AppFrame->Flags.PairingSolicitation) {                                    // If node not paired with, add it to the network
    i = AddNodeToNetwork(AppFrame->NodeID);
  } else {
    i = NodeIsInMyNet(AppFrame->NodeID);                                        // Else node is already in the net
  }
  if (i) {
    for (k=0;k<DATA_CHANNELS;k++) {                                             // This should be put into seperate fct for data copying, i think
      Nodes[i].InData[k] = AppFrame->Data[k];                                   // Copy the payload to local (temporary) storage
    }
    #ifdef __COMMAND_INTERFACE
      ReportStatus(i);  // Tell GUI all about the RSSI values
      ReportData(i);    // Tell the GUI all about the newly arrived data                                         
    #endif
    return i;
  }
  return 0;
}

/**
 * @fn PayloadFrame *NodeAckPayload(unsigned long NodeID)
 *
 * @brief This function checks if the node is in the net and then stores the 
 *        payload or ACK data to be sent, into the Payloads structure. This 
 *        function is used by hub.
 *
 * @param NodeID an unsigned long
 *
 * @return a PayloadFrame structure pointer
 */
PayloadFrame * NodeAckPayload(unsigned long NodeID)                            
{
  unsigned char k;
  unsigned char i=NodeIsInMyNet(NodeID);
  if (i) {                                                                      // If the node is a member, we will fill in stored data for it
    Payloads[NodeAckTempFrame].NodeID = Nodes[0].ID;                            // Tell sensor who we are
    for (k=0;k<DATA_CHANNELS;k++) {
      // Copy the temperature data to the payload frame (send local temperature data to Sensor)
      Payloads[NodeAckTempFrame].Data[k] = Nodes[i].OutData[k];               
    }
    Payloads[NodeAckTempFrame].Flags.PairingSolicitation = Payloads[IncommingFrame].Flags.PairingSolicitation;// Payloads[0] is the receive frame
    Payloads[NodeAckTempFrame].CycleTime = Nodes[0].CurrentCycleTime;
    return &Payloads[NodeAckTempFrame];
  } else {                                                                      // If he's not a member dont tell him anything!
    return 0;
  }
}

/**
 * @fn PayloadFrame * SensorPayload(void)
 *
 * @brief This fucntion creates a payload frame to be sent by sensor.
 *
 * @return a PayloadFrame structure pointer
 */
PayloadFrame * SensorPayload(void) 
{
  unsigned char k;
  //unsigned char i=NodeIsInMyNet(NodeID);
  // The sensor is unique in that it always must be able to send out a pairing message, this will make it also send analog data etc.
  // If thats not desired then dont set i=1 and use the if below to make appropriate actions
  if (1) {                                                                   
    Payloads[SensorSendFrame].NodeID = Nodes[0].ID;                             // Tell sensor who we are
    for (k=0;k<DATA_CHANNELS;k++) {
      Payloads[SensorSendFrame].Data[k] = Nodes[1].OutData[k];                  // Copy the stored data to the payload
    }
    if (GetPairingMask()) {
      Payloads[SensorSendFrame].Flags.PairingSolicitation = 1;
    } else {
      Payloads[SensorSendFrame].Flags.PairingSolicitation = 0;
    }
    Payloads[SensorSendFrame].CycleTime = Nodes[0].CurrentCycleTime;
    return &Payloads[SensorSendFrame];
  } else {                                                                      // If he's not a member dont tell him anything!
    return 0;
  }
}

#ifdef INCLUDE_FLASH_STORAGE
/**
 * @fn void WriteMyFlashedID(unsigned long ID) 
 *
 * @brief This function writes the node's own ID into flash
 *
 * @param ID an unsigned long
 */
void WriteMyFlashedID(unsigned long ID) 
{
  for (unsigned char i=0;i<sizeof(ID);i++) {
    FlashWriteChar(&MyFlashedID[i],(unsigned char)((ID>>i*8) & 0xFF));          // Write my ID to Flash
  }
}

/**
 * @fn void WriteMyFlashedPairedID(unsigned long ID) 
 *
 * @brief This function writes the ID of the paired node into flash.
 *
 * @param ID an unsigned long
 */
void WriteMyFlashedPairedID(unsigned long ID) 
{
  for (unsigned char i=0;i<sizeof(ID);i++) {
    FlashWriteChar(&MyFlashedPairedID[i],(unsigned char)((ID>>i*8) & 0xFF));    // Write the ID of the paired node to Flash
  }
}

/**
 * @fn void WriteMyFlashedRSCP(unsigned char Radio, unsigned char Setting, unsigned char Channel, unsigned char Power)
 *
 * @brief This function writes the node's indices for current radio, config, 
 *        channel and power, into flash
 *
 * @param Radio an unsigned char
 * @param Setting an unsigned char
 * @param Channel an unsigned char
 * @param Power an unsigned char
 */
void WriteMyFlashedRSCP(unsigned char Radio, unsigned char Setting, unsigned char Channel, unsigned char Power) 
{
  FlashWriteChar(&MyFlashedRSCP.Radio,Radio);                                   // Write Radio Index to Flash
  FlashWriteChar(&MyFlashedRSCP.Setting,Setting);                               // Write Config Index to Flash
  FlashWriteChar(&MyFlashedRSCP.Channel,Channel);                               // Write Channel Index to Flash
  FlashWriteChar(&MyFlashedRSCP.Power,Power);                                   // Write Power Index to Flash
}

/**
 * @fn unsigned long ReadMyFlashedID(void)
 *
 * @brief This function reads the node's ID from flash.
 *
 * @return an unsigned long
 */
unsigned long ReadMyFlashedID(void) 
{
  unsigned long temp=0;
  for (unsigned char i=0;i<sizeof(MyFlashedID);i++) {
    temp += ((unsigned long)MyFlashedID[i]) << (i*8);                           // Read my ID from Flash
  }
  return temp;
}

/**
 * @fn unsigned long ReadMyFlashedPairedID(void)
 *
 * @brief This function reads the ID of the paired node form the flash.
 *
 * @return an unsigned long
 */
unsigned long ReadMyFlashedPairedID(void) 
{
  unsigned long temp=0;
  for (unsigned char i=0;i<sizeof(MyFlashedPairedID);i++) {                     // Read the ID of paired node, from Flash
    temp += MyFlashedPairedID[i] << (i*8);
  }
  return temp;
}
#endif  //INCLUDE_FLASH_STORAGE

/**
 * @fn unsigned long CreateRandomAddress(void)
 *
 * @brief This function creates a random address for the node ID. 
 *
 * @return an unsigned long
 */
unsigned long CreateRandomAddress(void)
{
  int n,k;
  __no_init unsigned long RanNum;
  __no_init unsigned long RanNum1;
  __no_init unsigned long RanNum2;

  for (k=1;k>0;k--) {                                                           // Just for test purposes, we can make a whole bunch of them
    for (n=0x0F;n>=0;n--) {                                                     // Scan all channels, to construct a random seed number
      ADC10CTL1 = n*0x1000;                                                     // Channel, never mind other settings as we just want noise
      ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE + ADC10SR;
      ADC10CTL0 |= ENC + ADC10SC;                                               // Sampling and conversion start
      __bis_SR_register(CPUOFF + GIE);                                          // LPM0 with interrupts enabled
      RanNum1 += ADC10MEM;                                                      // Add result together from all channels
      ADC10CTL0 &= ~ENC;
      ADC10CTL0 &= ~(REFON + ADC10ON);                                          // Turn off A/D to get reference destabilized (and to save power after we're all done)
    }                                                                           // The second seed number is taken from un-initialized memory
    RanNum2=~RanNum1;
    do {
      RanNum1 = 36969 * (RanNum1 & 0xFFFF) + (RanNum1 >> 16);
      RanNum2 = 18000 * (RanNum2 & 0xFFFF) + (RanNum2 >> 16);
      RanNum = (RanNum1 << 16) + RanNum2;                                       // 32-bit result 
    } while (RanNum==0);                                                        // We cannot have 0
  }
  return RanNum;
}
  
/**
 * @fn void InitApplication(unsigned long addr)
 *
 * @brief This function initializes the application. It first sets the application
 *        state, then initializes the protocol, and finally sets the pairing mask.
 *
 * @param addr an unsigned long
 */
void InitApplication(unsigned long addr) 
{
  #ifdef INCLUDE_FLASH_STORAGE
    if((__ApplicationState) MyFlashedAppState <= HUB){                          
      ApplicationState = (__ApplicationState) MyFlashedAppState;                // Get application state from flash
    }
    else{
      SetApplicationState(HUB);                                                 // Set default application state
    }
  #endif
  InitProtocol();                                                               // Initialize Protocol 
  SetPairingMask(DEFAULT_PAIRING_MASK);                                         // Set pairing mask
}


