/**
 *  @file CommandInterface.c
 *
 *  @brief Command Interface Module
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
 *
 * version 1.1 Notes:
 * - All commands moved from seperate modules into this command interface module
 *      -# This necesitates use of externs to be able to access data
 *      -# The only command interface interactions left is for the main loop
 *         to poll for commands as usual and for the spontaneous events to 
 *         notify the command interface of the event.
 * - Control flags seperated into byte structures rather than word structures
 *   to make transitioning to 8051 processor easier. Thus what used to be simply 
 *   FlagBits is now:
 *      -# ControlFlags, these handle the flow of command input and execution.
 *      -# ResponseFlags, these handles the output format and which spontaneous
 *         outputs are allowed.
 * - All spontaneous update rates changes to a single bit to allow or deny. This 
     saves RAM, but does not allow to slow down the rate of information. This 
     will now be up to the Application to make sure that amount of information 
     being output is less than what the output stream and recipient can handle.
 * - Command names changed from 2 byte names to more descriptive names
 * - Command listing no longer has layers, since they are now all defined in 
     this module.
 * - ID in the status message has been moved to the front to be consistent with 
     other commands and responses.
 * - RSSI values in status message has been changed to Sint16 fp dBm values (byte.byte)
 * - The function "PhysicalChanged()" was added to signal to the GUI that 
     one or more of r.s.c.p was changed - needs to be implemented in the 
     protocol. The AllowPhysical flagg (bit 6) controls whether or not it is 
     actually output. The same information can be polled for using the "pget" 
     command.
 * - 

*/

#include "Framework\FPI\FPI.h"
#include "CommandInterface.h"
#include "protocol.h"
#include "application.h"

//! \brief Private functions
char BuiltInCmdProcessing(void);                                                // Private functions called from ProcessRawCommand (typically called from the application) to handle 
                                                                                // Built in commands like read/write
char HexNibble(char num); 
void ResponseResult(unsigned char res);

extern AppRadio radio[];
extern NodeInfo Nodes[MAX_NODES];
extern uint8_t PushButton;
/**
 * @brief Control the input and execution of commands.
 */
typedef struct CommandFlags {                                                   // Assumes #pragma bitfields=default (i.e. listed from least significant bit to most
  unsigned int ParmCount        : 4;                                            //!< bits 0-3, counts the supplied parameters, used for unique XML identifiers during cmd repeat.
  unsigned int CommandReady     : 1;                                            //!< bit 4, signal from input stream that a command is ready.
  unsigned int InternalCommand  : 1;                                            //!< bit 5, the command came from internal code, not the input stream.
  unsigned int ToggleFormatUponCmdCompletion : 1;                               //!< bit 6, used to change output format XML or Abbreviated.
  unsigned int ResultIsDelayed  : 1;                                            //!< bit 7, used to allow the cmd if to return to the main loop and finish a command at a later time.
} CommandFlags;

/**
 * @brief Union for command flags
 */
typedef union CommandUnion { 
  CommandFlags  bits;
  uint8_t       byte;
} CommandUnion;

/**
 * @brief Controls the spontaneous responses and the response format.
 *        It allows or disallows the various responses that can be 
 *        output and the format in which they are output. In the following; 
 *        - "#" is used for a hex nibble {0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F}.
 *        - "$" is used for an integer decimal number of unspecified length.
 *        - "@" is used as a single byte value (>=0x20).
 *        - "?" is used for multiple byte values (>=0x20).
 *        - "+" is used to denote concatenation.
 *        - "{" and "}" is used to bracket a range, only one of which is actually
 *          present.
 *        - "<" and ">" is used to bracket an descriptive field identifier (not 
 *          part of the output).
 *        There is both an abbreviated output format and an XML output format 
 *        available.
 *        Starting with the abbreviated format: 
 *        - "!i:?\r\n", is for debug information using the DebugNotes().
 *        - "!s:" + <ID index>## + "," + <>#### + <>#### + "\r\n"
 */
typedef struct ResponseFlags {                                                  // Assumes #pragma bitfields=default (i.e. listed from least significant bit to most
  uint8_t AllowDebug    : 1;                                                    //!< bit 0, allow "!i:..." responses from DebugNotes().
  uint8_t AllowStatus   : 1;                                                    //!< bit 1, allow "!s:..." responses from ReportStatus().
  uint8_t AllowData     : 1;                                                    //!< bit 2, allow "!d:..." responses from ReportData().
  uint8_t AllowMessage  : 1;                                                    //!< bit 3, allow "!m:..." responses from NewMessage().
  uint8_t AllowNetwork  : 1;                                                    //!< bit 4, allow "!n:..." responses from NetworkChanged().
  uint8_t AllowAppChg   : 1;                                                    //!< bit 5, allow "!a:..." responses from ApplicationChanged().
  uint8_t AllowPhysical : 1;                                                    //!< bit 6, allow "!p:..." responses from PhysicalChanged().
  uint8_t XML_Output    : 1;                                                    //!< bit 7, Output format in 0=abbreviated or 1=XML
} ResponseFlags;

/**
 * @brief Response Flags as a byte.
 */
typedef union ResponseUnion {
  ResponseFlags bits;
  uint8_t       byte;
} ResponseUnion;

/**
 * @brief Controls the formatting of the responses as they are created.
 */
typedef struct TagFlags {                                                       // Assumes #pragma bitfields=default (i.e. listed from least significant bit to most
  uint8_t TagLevel         : 4;                                                 //!< bits0-3, used to keep track of delimiters and proper endings
  uint8_t InsideTag        : 1;                                                 //!< bit 4 - a tag has been started, but not finished. Used for adding attributes.
  uint8_t InsideAttribute  : 1;                                                 //!< bit 5 - an attribute has been started, but not finished. Used to add attribute termination.
  uint8_t OneOrMoreAttribs : 1;                                                 //!< bit 6 - Set if a tag has any attributes. Used to close the tag properly.
  uint8_t Spare            : 1;                                                 //!< bit 7 - simply to fully define the byte
} TagFlags;

/**
 * @brief  Control Tag flags as a byte.
 */
typedef struct TagUnion {
  TagFlags bits;
  uint8_t  byte;
} TagUnion;

//! \brief RAM Footprint
char *CmdIFCommandString;                                                       //!< Used to point to the current command being (or to be) executed
volatile unsigned char InCmdSeq;                                                //!< pointer to the current char in the command collect buffer
char RawCommand[MaxRawCommandLength];                                           //!< command collect buffer. Static while being processed and thus does not need to be volatile.
volatile CommandUnion cFlags = {0};                                             //!< Command collection and execution flags
ResponseUnion rFlags = {0};                                                     //!< Response control flags
TagUnion tFlags = {0};                                                          //!< Response creation format controls
unsigned char DelayedResult = 0;                                                //!< used both as a delayed command result (CmdFlags.ResultIsDelayed) and as a timeout for same.

//define shortcuts for readability of the code
#define AllCmdFlags      cFlags.byte
#define CmdFlags         cFlags.bits
#define AllResponseFlags rFlags.byte
#define ResponseFlags    rFlags.bits
#define AllTagFlags      tFlags.byte
#define TagFlags         tFlags.bits

//! \brief Command definitions
// Local function prototyping:
unsigned char AppInformation(void);
unsigned char CommandListing(void);
unsigned char ResponseCtrl(void);
unsigned char CmdIF_SetDataValue(void);
unsigned char CmdIF_DataDefinitions(void);

#ifdef __INCLUDE_ELABORATE_HELP
  #define DefineCommand(cmd,fct,help) { cmd, fct, help }
#else
  #define DefineCommand(cmd,fct,help) { cmd, fct }
#endif

//! \brief Definition of commands and the functions the call
/**
 * @brief CmdIFCommandDefs[] holds all valid commands. Each command causes a 
 *          call to the function specified, this function in turn will read any 
 *          applicable parameters 
 */
static const CommandDefinition CommandDefinitions[] = {
  // command interface commands
  DefineCommand("info",  AppInformation,   "\"info\"; app info and version/revision"),
  DefineCommand("help",  CommandListing,   "\"help\"; list of all commands"),
  DefineCommand("resp",  ResponseCtrl,     "\"resp(Flag bit)##(value)##\"; Flag bits: 0=Debug 1=Status 2=Data 3=Message 4=Network 5=AppCHg 6=Physical 7=XML; (value of same bit) 0=off 1=on"),
  DefineCommand("peek",  MemoryRead,       "\"peek(address)########(count)##\"; reads (count) bytes starting from (address)"),
  DefineCommand("poke",  MemoryWrite,      "\"poke(address)########(n*data)##....\"; writes (n) supplied bytes starting from (address)"),
  #ifdef __CmdIF_TESTMODE
    DefineCommand("ctest", CmdIF_ModuleTest, "\"ctest\"; runs predefined test for the Command Interface"),
  #endif
  // Protocol commands
  DefineCommand("cfgs",   ConfigurationInfo,    "\"cfgs\"; listing of physical channel configuration information"),
  DefineCommand("pget",   GetCurrentPhysical,   "\"pget\"; get current physical channel info (indexes)"),
  DefineCommand("pset",   SetCurrentPhysical,   "\"pset(ID index)##(radio)##(config)##(ch)##(power)##\"; (ID index) 0=local; FF=all; other=node and local"),
  DefineCommand("dump",   DumpRadioRegisters,   "\"dump(radio)##\"; dump physical radio's registers"),
  #ifdef __DEBUG_COMMANDS
    DefineCommand("lr",     SetCurrentRadio,      "\"lr(radio)##\"; sets current local radio - debug only"),
    DefineCommand("ls",     SetCurrentConfig,     "\"ls(setting)##\"; sets current local config setting - debug only"),
    DefineCommand("lc",     SetCurrentChannel,    "\"lc(channel)##\"; sets current local logical channel - debug only"),
    DefineCommand("lp",     SetCurrentPower,      "\"lp(power)##\"; sets current local power - debug only"),
    DefineCommand("lt",     ResetCurrentRadio,    "\"lt(radio)##\"; resets local radio - debug only"),
  #endif
  //DefineCommand("ptest",  Protocol_ModuleTest,  "\"ptest\"; runs predefined test for the Protocol"),
  // Application commands
  DefineCommand("states", CmdIF_GetAppStates,    "\"states\"; listing of possible application states"),
  DefineCommand("state",  CmdIF_SetAppState,     "\"state##\"; change to the specified app state"),
  DefineCommand("nodes",  CmdIF_GetNodeIDs,      "\"nodes##\"; lists all nodes in network"),
  DefineCommand("idset",  CmdIF_SetThisNodeID,   "\"setid(id)########\"; set the local nodes ID"),
  DefineCommand("pmask",  CmdIF_SetPairingMask,  "\"mask(pairingmask)########\"; set the local pairing mask, 00000000=none, FFFFFFFF=all"),
  DefineCommand("ndel",   CmdIF_RemoveNode,      "\"ndel##\"; removed the node specified by index from the paired network"),
  DefineCommand("time",   CmdIF_SetCycleUpdateRate, "\"time(ID index)##(time ms)####\"; set the time between sensor updates from the specified node"),
  DefineCommand("dset",   CmdIF_SetDataValue,    "\"dset(ID index)##(channel)##(value)####\"; set the value for specified channel on specified node"),
  DefineCommand("ddef",   CmdIF_DataDefinitions, "\"ddef\"; get definitions for each data channel"),
  //DefineCommand("atest",  App_ModuleTest,       "\"atest\"; runs predefined test for the Application"),
  DefineCommand("", 0, "EOC") // This terminates the command list
};

/**
 * @brief Definitions for the network data as seen from the Sensor/Actuator.
 *          In/Out refers to into the Sensor node (displayed by GUI) or out from  
 *          the Sensor (controlled by the GUI).
 */
const DataDefinition SensorDataDefinitions[] = {
  // direction&type, GUI presentation Info,           Memory mappings, HW mapping
  // direction, label, min, max, unit, data channel, storage location, mask
  { AnalogInput,   "Chip Temp",  "-69", "354",   "Deg C", 1, 0xFFFF, HWMap_ChipTemp }, // 0
  { DigitalOutput, "GreenLED",     "0",   "1",     "Bit",   0, 0x0001, HWMap_GreenLED }, // 1
  { DigitalInput,  "RedLED",     "0",   "1",     "Bit",   0, 0x8000, HWMap_RedLEDandButton }, // 2
  { AnalogOutput,  "unused",     "0",   "65535", "Int",   1, 0xFFFF, HWMap_PWM } // 3
};

/**
 * @brief Definitions for the network data as seen from the Hub.
 */
const DataDefinition HubDataDefinitions[] = {
  // direction, label, min, max, unit, data channel, storage location, mask
  { AnalogInput,   "Chip Temp",  "-69", "354",   "Deg C", 1, 0xFFFF, HWMap_ChipTemp }, // 0
  { DigitalOutput, "GreenLED",   "0",   "1",     "Bit",     0, 0x0001, HWMap_GreenLED }, // 1
  { DigitalInput,  "RedLED",     "0",   "1",     "Bit",   0, 0x8000, HWMap_RedLEDandButton }, // 2
  { AnalogOutput,  "unused",     "0",   "65535", "Int",   1, 0xFFFF, HWMap_PWM } // 3
};

/**
 * @brief Definitions for the network data (Nodes[]."In/Out"Data[]), organized by 
 *          application state. Note that the order here must match the order of 
 *          "__ApplicationState" enumeration
 */
const DataDefinition *DataDefinitions[] = {
  SensorDataDefinitions,
  HubDataDefinitions
};

/**
 * @brief Number of data definitions per application state. Note that the 
 *          order here must match the order of "__ApplicationState" enumeration.
 *          And the count must match the definition for all to be processed
 */
const uint8_t DataDefCount[] = {
  4,
  4
};

/**
 * @fn void ModuleInfo(char * Module, uint8_t Version, uint8_t Revision, char * Description)
 *
 * @brief This is a private function to AppInformation (code reduction purpose).
 *
 * @param Module a character pointer
 * @param Version an unsigned integer
 * @param Revision an unsigned integer
 * @param Description a character pointer
 */
void ModuleInfo(char * Module, uint8_t Version, uint8_t Revision, char * Description) 
{
  TagBegin(Module,1);                                                           // Tag with attributes
  ElemAttrUint8("ver",Version);
  ElemAttrUint8("rev",Revision);
  ElemAttrText("desc",Description);
  TagEnd(Module,0);                                                             // Tag end, no element
}

/**
 * @fn unsigned char AppInformation(void)
 *
 * @brief This function provides version, revision and description for each major 
 *        module.
 *
 * @return an unsigned char
 */
unsigned char AppInformation(void) 
{
  TagBegin("info",0);
  #ifdef __FRAMEWORK_NAME
      ModuleInfo( __FRAMEWORK_NAME, __FRAMEWORK_VERSION, __FRAMEWORK_REVISION,  __FRAMEWORK_DESCRIPTION);
  #endif
  ModuleInfo(__CmdIF_NAME, __CmdIF_VERSION, __CmdIF_REVISION, __CmdIF_DESCRIPTION);
  ModuleInfo(__PROTOCOL_NAME, __PROTOCOL_VERSION, __PROTOCOL_REVISION, __PROTOCOL_DESCRIPTION);
  ModuleInfo(__APPLICATION_NAME, __APPLICATION_VERSION, __APPLICATION_REVISION, __APPLICATION_DESCRIPTION);
  TagEnd("info",0);
  return 1;
}

/**
 * @fn unsigned char CommandListing(void)
 *
 * @brief This function lists all the commands available through the Command
 *        Interface.
 *
 * @return an unsigned char
 */
unsigned char CommandListing(void) 
{
  unsigned char c=0;
  TagBegin("Commands",0);                                                       // Tag no attributes  
  while (CommandDefinitions[c].Command[0]) {                                    // Check to see that the command is not a null string, which would mean its the end of the list
    TagBegin("Command",1); 
    ElemAttrUint8("num",c);
    ElemAttrText("label",CommandDefinitions[c].Command);
    #ifdef __INCLUDE_ELABORATE_HELP
      ElemAttrText("desc",CommandDefinitions[c].HelpTxt);
    #endif
    TagEnd("Command",0);
    c++;
  }
  TagEnd("Commands",0); 
  return 1;
}

/**
 * @fn unsigned char ResponseCtrl(void) 
 *
 * @brief This function controls the spontaneous outputs and the output format. 
 *        If we are asked to change output format, then it temporarily sets it to 
 *        what it was and signals to change upon command completion. 
 *
 * @return an unsigned char
 */
unsigned char ResponseCtrl(void) 
{
  uint8_t bits,value;
  ResponseUnion temp;
  if (GetParmByte("bits",&bits)) { 
    if (GetParmByte("value",&value)) {
      temp.byte = (AllResponseFlags & ~bits) | (value & bits);                  // Change only the bits that we are specifying
      if (temp.bits.XML_Output != ResponseFlags.XML_Output) {
        temp.bits.XML_Output = ResponseFlags.XML_Output;
        CmdFlags.ToggleFormatUponCmdCompletion = 1;
      }
      AllResponseFlags = temp.byte;                                             // All but XML changes take effect NOW!
      return 1;
    }
  }
  return 0;
}

#if MaxRawCommandLength < 11
  #warning Cannot implement CommandInterface.MemoryRead command with (MaxRawCommandLength<11)
#endif
#pragma diag_suppress=Pe1053                                                    // Turn off the "Warning[Pe1053]: conversion from integer to smaller pointer" warning

/**
 * @fn unsigned char MemoryRead(void)
 *
 * @brief This function reads the data from memory(with the given address and 
 *        count of data).
 *
 * @return an unsigned char
 */
unsigned char MemoryRead(void) 
{
  unsigned long temp;
  unsigned char *Ptr;
  unsigned char Count;
  unsigned char DidIt=0;
  if (GetParmLong("addr",&temp)) {
    if (GetParmByte("count", &Count)) {
      Ptr = (unsigned char *)temp;
      TagBegin("mread",1);                                                      // Tag with attribute   
      ElemAttrUint32("addr",(unsigned long)Ptr);
      TagEnd("mread",1);                                                        // Has elements
      do {                                                                      // A 'Count' of 0 means 256 !
        ElemAttrUint8("d",*Ptr++);
      } while (--Count);
      DidIt=1;
      TagEnd("mread",0);     
    }
  }
  return DidIt;
}
#if MaxRawCommandLength < 11
  #warning Cannot implement CommandInterface.MemoryWrite command with (MaxRawCommandLength<11)
#endif

/**
 * @fn unsigned char MemoryWrite(void) 
 *
 * @brief This function writes the data to given address in the memory.
 *
 * @return an unsigned char
 */
unsigned char MemoryWrite(void) 
{
  unsigned long temp;
  unsigned char *Ptr;
  unsigned char Data;
  unsigned char DidIt=0;
  if (GetParmLong("addr",&temp)) {
    Ptr = (unsigned char *)temp;
    TagBegin("mwrite",0);     
    while (GetParmByte("data", &Data)) {
      *Ptr++ = Data;
      DidIt=1;
    }
    TagEnd("mwrite",0);   
  }
  return DidIt;
}
#pragma diag_warning=Pe1053                                                     // Re-enable warning 

//! \brief Protocol part of CmdIF
/**
 * @fn void ReportStatus(unsigned char IDindex)
 *
 * @brief This function reports the status of the following parameters:
 *        Local and Remote: RSSI, LQI, Frequency Offset, Power.
 *        Last Used Channel, and Frame Counter.
 */
void ReportStatus(unsigned char IDindex)
{
  unsigned char i;
  if (ResponseFlags.AllowStatus) {
    TagBegin("status",0);                                                       // Begin status tag, no attributes
    for (i=0;i<((IDindex) ? 2 : 1);i++) {                                       // Do it for the local and the node provided, if any
      TagBegin("RSSI",1);
        ElemAttrUint8("ID", i*IDindex);
        ElemAttrSint16("val", RSSI2dBm(Nodes[i*IDindex].LastRSSI));
      TagEnd("RSSI",0);
    }
    TagEnd("status",0);
  }
} 


//! \brief Command functions 
/**
 * @fn unsigned char ConfigurationInfo(void)
 *
 * @brief Outputs a block named <PhysDef> describing the physical layer settings 
 *        for all radios. 
 *        For each radio the radio is first described as <radio rn="#" rd="*" [rc="*"]>, 
 *        where 'rn' is the radio number, 'rd' is a description of the radio and 
 *        the optional 'rc' is a HW connection description (e.g. "SPI CSN2.2").
 *        Next the entire channel list for the current radio is output:
 *        <Channels><Channel cn="#" MHz="#" [cd="*"]/> ... </Channels>
 *        Where 'cn' is the channel number, 'MHz' is the center frequency of the 
 *        channel in MHz and the optional 'cd' is a description of the channel.
 *        Next the entire power settings list for the current radio is output:
 *        <Powers><Power pn="#" dBm="#" [pd="*"]/> ... </Powers>
 *        Where 'pn' is the power number, 'dBm' is the nominal output power for 
 *        this power setting in dBm and the optional 'pd' is a description of the 
 *        power setting.
 *        Finally the configurations for the current radio are output:
 *        <Settings><setting sn="#" sd="*" [kb="#"] [sk="#"]>
 *        <ChList><ch i="#" n="#" p="#"/> ... </ChList></Settings>
 *        Where 'sn' is the settings number, 'sd' is the settings description, 
 *        the optional 'kb' is the data rate in kilo bits/s and the optional 'sk' 
 *        is the kost number associated with this configuration setting. 'i' is 
 *        the channel list index number, 'n' is the channel number, as a reference 
 *        into the list of channels and 'p' is the maximum power index into the 
 *        list of power settings.
 *        Note: this output format is subject to change without notice!
 *
 * @return an unsigned char
 */
unsigned char ConfigurationInfo(void) 
{
  unsigned char r,s,c,p;
  TagBegin("PhysDef",0);      
  for (r=0;r<radio_Count;r++) {
    TagBegin("radio",1);     
    ElemAttrUint8("rn",r);
    ElemAttrText("rd",radio[r].radioDescription);
    TagEnd("radio",1);                                                          // Has elements to come
    TagBegin("Channels",0);
    for (c=0;c<radio[r].pRadioArraySizes->radioChannelListCount;c++) {
      TagBegin("channel",1);     
      ElemAttrUint8("cn",c);
      ElemAttrText("MHz",radio[r].pRadioChannelList[c].channelDescription);
      TagEnd("channel",0);                                                      // No further
    }
    TagEnd("Channels",0);                                                       // Has elements to come
    TagBegin("Powers",0);
    for (p=0;p<radio[r].pRadioArraySizes->radioPowerListCount;p++) {
      TagBegin("power",1);                                                      // Has attributes    
      ElemAttrUint8("pn",p);
      ElemAttrText("dBm",radio[r].pRadioPowerList[p].powerDescription);
      TagEnd("p",0); 
    }
    TagEnd("Powers",0);                                                         // Has elements to come
    TagBegin("Settings",0);
    for (s=0;s<radio[r].pRadioArraySizes->radioConfigurationCount;s++) {
      TagBegin("setting",1);     
      ElemAttrUint8("sn",s);
      ElemAttrText("sd",radio[r].pRadioConfiguration[s].pRegisterSettings->baseSettingsDescription);
      TagEnd("setting",1);                                                      // Elements to come
      TagBegin("ChList",0);
      for (c=0;c<radio[r].pRadioConfiguration[s].configurationChannelCount;c++) {
        TagBegin("ch",1);
        ElemAttrUint8("i",c);
        ElemAttrUint8("n",radio[r].pRadioConfiguration[s].pConfigurationChannel[c].radioChannelIndex);
        ElemAttrUint8("p",radio[r].pRadioConfiguration[s].pConfigurationChannel[c].radioPowerIndex);
        TagEnd("ch",0); 
      }
      TagEnd("ChList",0); 
      TagEnd("setting",0); 
    }
    TagEnd("Settings",0);
    TagEnd("radio",0);
  }
  TagEnd("PhysDef",0);
  return 1;
}

/**
 * @fn unsigned char SetCurrentPhysical(void)
 *
 * @brief This function sets the current radio, config, channel and power as per 
 *        user's input.(local or sends across the link).
 *
 * @return an unsigned char
 */
unsigned char SetCurrentPhysical(void) 
{
  unsigned char remote, radio1, config, channel, power;
  if(GetParmByte("remote", &remote)){
    if (GetParmByte("radio",&radio1)) { 
      if (GetParmByte("config",&config)) { 
        if (GetParmByte("channel",&channel)) { 
          if (GetParmByte("power",&power)) { 
            if(ChangeConfiguration(remote, radio1, config, channel, power)){
              if(remote) return 0xFF;
              else return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}

/**
 * @fn unsigned char GetCurrentPhysical(void)
 *
 * @brief This function outputs currents indices of radio, config, channel and 
 *        power.
 *
 * @return an unsigned char
 */
unsigned char GetCurrentPhysical(void) 
{
  TagBegin("physCurr",1);
  ElemAttrUint8("radio",CurrentRadio()); 
  ElemAttrUint8("setting",CurrentBaseConfig()); 
  ElemAttrUint8("channel",CurrentChannel()); 
  ElemAttrUint8("power",CurrentPower()); 
  TagEnd("PhysCurr",0);
  return 1;
}

/**
 * @fn void PhysicalChanged(void)
 *
 * @brief This function is called whenever any of the physical channel parameters 
 *        have been changed. I.e. if the radio, setting, channel or power was 
 *        changed, either from a local request or from a remote request; call this
 *        function, such that the GUI will be notified of the change (if it so 
 *        chooses to be).
 */
void PhysicalChanged(void) 
{
  if ((ResponseFlags.AllowPhysical) && (TagFlags.TagLevel==0)) GetCurrentPhysical();
}

/**
 * @fn unsigned char DumpRadioRegisters(void)
 *
 * @brief This function writes out the values of all the radio registers.
 *
 * @return an unsigned char
 */
unsigned char DumpRadioRegisters(void) 
{
  unsigned char radio1,i;
  if (GetParmByte("radio",&radio1)) {
    if (radio1 >= radio_Count) return 0;
    TagBegin("registers",1);
    ElemAttrUint8("radio",radio1);
    TagEnd("registers",1);
    for (i=0;i<0x3E;i++) {
      TagBegin("reg",1);
      ElemAttrUint8("a",i); 
      ElemAttrUint8("d",RadioGetRegister(&radio[radio1].frameworkRadio, i)); 
      TagEnd("reg",0);
    }
    for (i=0;i<8;i++) {
      TagBegin("PAtable",1);
      ElemAttrUint8("i",i); 
      ElemAttrUint8("d",RadioGetRegister(&radio[radio1].frameworkRadio, 0x3E));
      TagEnd("PAtable",0);
    }
    TagEnd("registers",0);
    return 1;
  } else return 0;
}

#ifdef __DEBUG_COMMANDS
extern RadioStruct RadioLocal;
extern ConfigStruct ConfigSettings[];

 /**
  * @fn unsigned char SetCurrentChannel(void)
  *
  * @brief This function sets the current channel index as per user's input.
  *
  * @return an unsigned char
  */
  unsigned char SetCurrentChannel(void)
  {
    unsigned char channel;
    if(GetParmByte("channel",&channel)) { 
      ChangeConfiguration(0, RadioLocal.currentRadio, CurrentBaseConfig(), channel, CurrentPower());
      return 1;
    }
    return 0;
  }
  
 /**
  * @fn unsigned char SetCurrentPower(void)
  *
  * @brief This function sets the current power index as per user's input.
  *
  * @return an unsigned char
  */
  unsigned char SetCurrentPower(void)
  {
    unsigned char power;
    if(GetParmByte("power",&power)) { 
      ChangeConfiguration(0, RadioLocal.currentRadio, CurrentBaseConfig(), CurrentChannel(), power);
      return 1;
    }
    return 0;
  }
  
 /**
  * @fn unsigned char SetCurrentConfig(void)
  *
  * @brief This function sets the current config index as per user's input.
  *
  * @return an unsigned char
  */
  unsigned char SetCurrentConfig(void)
  {
    unsigned char config;
    if(GetParmByte("config",&config)) { 
      ChangeConfiguration(0, RadioLocal.currentRadio, config, CurrentChannel(), CurrentPower());
      return 1;
    }
    return 0;
  }
  
 /**
  * @fn unsigned char SetCurrentRadio(void)
  *
  * @brief This function sets the current radio index as per user's input.
  *
  * @return an unsigned char
  */
  unsigned char SetCurrentRadio(void)
  {
    unsigned char radio1;
    if(GetParmByte("radio",&radio1)) { 
      ChangeConfiguration(0, radio1, CurrentBaseConfig(), CurrentChannel(), CurrentPower());
      return 1;
    }
    return 0;
  }
  
 /**
  * @fn  unsigned char ResetCurrentRadio(void)
  *
  * @brief This function resets the the current radio.
  *
  * @return an unsigned char
  */
  unsigned char ResetCurrentRadio(void)
  {
    unsigned char radio1;
    if(GetParmByte("radio",&radio1)) { 
      RadioSetRegister(pCurrentFrameworkRadio(), CCXXX_STRB_SIDLE, 0);          // Strobe Idle
      RadioSetRegister(pCurrentFrameworkRadio(), CCXXX_STRB_SRES, 0);           // CCxxxx_STRB_SRES : reset the chip
      return 1;
    }
    return 0;
  }
#endif //ifdef __DEBUG_COMMANDS

//! \brief Application part of CmdIF
/**
  * @fn unsigned char CmdIF_GetNodeIDs(void)
  *
  * @brief This function writes out the IDs of all the nodes in the network,
  *        including the empty slots.
  *
  * @return an unsigned char
  */
unsigned char CmdIF_GetNodeIDs(void) 
{
  unsigned char i;
  TagBegin("network",0);
    TagBegin("Pairing",1);                                                      // Tag with attributes
      ElemAttrUint32("mask",GetPairingMask());
    TagEnd("Pairing",0);
    TagBegin("NodeIDs",0);                                                      // Tag, no attributes
      for (i=0;i<MAX_NODES;i++) {
        TagBegin("Node",1);                                                     // Tag with attributes
          ElemAttrUint8("num",i);
          ElemAttrUint32("ID",Nodes[i].ID);
        TagEnd("Node",0);
      }
    TagEnd("NodeIDs",0);
  TagEnd("network",0);
  return 1;
}

/**
 * @fn void NetworkChanged(void)
 *
 * @brief Use this function to inform the GUI that a network change has taken place.
 *        This includes a pairing mask change, nodes added to the network and nodes
 *        deleted from the network.
 */
void NetworkChanged(void) 
{
  if ((ResponseFlags.AllowNetwork) && (TagFlags.TagLevel==0)) CmdIF_GetNodeIDs();
}

/**
 * @fn unsigned char CmdIF_SetThisNodeID(void)
 *
 * @brief This function sets the node's own ID as per user's input.
 *
 * @return an unsigned char
 */
unsigned char CmdIF_SetThisNodeID(void) 
{
  unsigned long ID;
  if (GetParmLong("ID",&ID)) { 
    if (SetMyNodeID(ID)) {
      return 1;
    }
  }
  return 0;
}

/**
 * @fn unsigned char CmdIF_SetPairingMask(void)
 *
 * @brief This function sets the pairing mask as per the user's input.
 *
 * @return an unsigned char
 */
unsigned char CmdIF_SetPairingMask(void) 
{
  unsigned long mask;
  if (GetParmLong("mask",&mask)) { 
    SetPairingMask(mask);
    return 1;
  }
  return 0;
}

/**
 * @fn unsigned char CmdIF_RemoveNode(void)
 *
 * @brief This function removes the node form the network as per user's input.
 *
 * @return an unsigned char
 */
unsigned char CmdIF_RemoveNode(void) 
{
  unsigned char ID_index;
  if (GetParmByte("ID",&ID_index)) { 
    if (RemoveNodeFromNetwork(ID_index)) {
      return 1;
    }
  }
  return 0;
}

/**
 * @fn unsigned char CmdIF_GetAppStates(void)
 *
 * @brief This function returns the current state of the application (sensor or 
 *        hub).
 *
 * @return an unsigned char
 */
unsigned char CmdIF_GetAppStates(void) 
{
  //TagBegin("States",0);                                                         // Tag with attributes
  TagBegin("app",0);                                                            // Changed 111013
  TagBegin("state",1);
    ElemAttrUint8("num",0);
    ElemAttrText("label","Sensor");
  TagEnd("state",0);
  TagBegin("state",1);
    ElemAttrUint8("num",1);
    ElemAttrText("label","Hub");
  TagEnd("state",0);
  TagBegin("current",1);
    ElemAttrUint8("num",ApplicationState);
  TagEnd("state",0);
  //TagEnd("States",0);                                                           // Tag end, no element
  TagEnd("app",0);                                                              // Changed 111013
  return 1;
}

/**
 * @fn unsigned char CmdIF_SetAppState(void)
 *
 * @brief This function sets the application state(sensor or hub) of the module 
 *        based on the user's input.
 *
 * @return an unsigned char
 */
unsigned char CmdIF_SetAppState(void) 
{
  unsigned char state;
  if (GetParmByte("state",&state)) { 
    for (unsigned char i=1;i<MAX_NODES;i++) RemoveNodeFromNetwork(i);           // Clear our memory of any memberships
    if (state) {
      SetApplicationState(HUB);
      return 1;
    } else {
      SetApplicationState(SENSOR);
      return 1;
    }
  } else return 0;
}

/**
 * @fn void ApplicationChanged(void)
 *
 * @brief Use this function to inform the GUI that the application has changed.
 *        This could be a change from Hub to Sensor, vise versa or another
 *        future application state.
 */
void ApplicationChanged(void) 
{
  if ((ResponseFlags.AllowNetwork) && (TagFlags.TagLevel==0)) CmdIF_GetNodeIDs();
  if ((ResponseFlags.AllowAppChg) && (TagFlags.TagLevel==0)) CmdIF_GetAppStates(); // added 111013
}

/**
 * @fn void ReportData(unsigned char IDindex)
 *
 * @brief This function writes out the local data.
 */
void ReportData(unsigned char IDindex)
{
  unsigned char j; //,s;
  unsigned int temp;
  if ((ResponseFlags.AllowData) && (TagFlags.TagLevel==0)) {
    if (!IDindex) {
      MapSensorsFromHW(0); // get local only HW states
    }
    if (Nodes[IDindex].ID) {
      TagBegin("data",1);
      ElemAttrUint8("ID",IDindex);
      TagEnd("data",1);
      for (j=0;j<DataDefCount[ApplicationState];j++) {
        if (DataDefinitions[ApplicationState][j].DataType & DATA_INPUT_MASK) {  // Special case for local querry, to not overwrite values just set
          TagBegin("item",1);
            ElemAttrUint8("num",j);
            temp = Nodes[IDindex].InData[DataDefinitions[ApplicationState][j].DataChannel] & DataDefinitions[ApplicationState][j].Mask;
            if (!IDindex) {
              DataDefinitions[ApplicationState][j].HWMapFunc(1,temp);           // Rare case of writing to an input control
            }
            ElemAttrUint16("val",temp);
          TagEnd("item",0);
        }
      }
      TagEnd("data",0);
    }
  }
}

/**
 * @fn unsigned char CmdIF_SetDataValue(void)
 *
 * @brief This function sets the data value to the channel of the given node ID 
 *        as per user's input.
 *
 * @return an unsigned char
 */
unsigned char CmdIF_SetDataValue(void) 
{
  unsigned char ID,num,IDindex;
  unsigned int val,temp;
  if (GetParmByte("ID",&ID)) {
    if (ID){
      IDindex = NodeIsInMyNet(Nodes[ID].ID);
      if (!IDindex) return 0;                                                   // Specified node not in network
    } else {
      IDindex = 0;                                                              // Local node
    }
    if ((GetParmByte("num",&num)) && (GetParmWord("val",&val))) {               // We need a minimum of one set of ch and val for this command to be valid
      if (num > DataDefCount[ApplicationState]) return 0;                       // No definition for this data num
      if (DataDefinitions[ApplicationState][num].DataType & DATA_OUTPUT_MASK) {
        // First map the setting into memory
        temp = Nodes[IDindex].OutData[DataDefinitions[ApplicationState][num].DataChannel]; // Set data value to corresponding data channel
        temp &= ~DataDefinitions[ApplicationState][num].Mask;
        if (DataDefinitions[ApplicationState][num].DataType & DATA_DIGITAL_MASK) if (val) val=0xFFFF; // If its digital then expand a true to all bits
        temp |= DataDefinitions[ApplicationState][num].Mask & val;
        Nodes[IDindex].OutData[DataDefinitions[ApplicationState][num].DataChannel] = temp; // Store in mem
        if (!IDindex) {                                                         // If its for the local node then make it effective immediately
          DataDefinitions[ApplicationState][num].HWMapFunc(1,DataDefinitions[ApplicationState][num].Mask & val);
          // I wonder if we shouldnt also copy this into InData for the local, to reflect the change
        }
        return 1;
      }                                                                         // This is not an output so we cant "set" it to anything
    }
  }
  return 0;
}

/**
 * @fn void MapControlsToHW(unsigned char IDindex)
 *
 * @brief Maps data from a network node storage location (Nodes[].Data[])
 *        into all applicable HW "actuators"
 *
 * @param IDindex an unsigned char
 */
void MapControlsToHW(unsigned char IDindex)
{
  uint8_t num;
  unsigned int temp;
  for (num=0;num<DataDefCount[ApplicationState];num++) {
    if (DataDefinitions[ApplicationState][num].DataType & DATA_OUTPUT_MASK) {
      temp = Nodes[IDindex].InData[DataDefinitions[ApplicationState][num].DataChannel]; // Get data from memery location
      temp &= DataDefinitions[ApplicationState][num].Mask;                      // Mask off what pertains to this data definition
      DataDefinitions[ApplicationState][num].HWMapFunc(1,temp);                 // "Actuate" the HW
    }
  }
}

/**
 * @fn void MapSensorsFromHW(unsigned char IDindex)
 *
 * @brief Maps all applicable HW sensors into the network node storage 
 *        location (Nodes[].Data[]) specified
 *
 * @param IDindex an unsigned char
 */
void MapSensorsFromHW(unsigned char IDindex)
{
  uint8_t num;
  unsigned int temp;
  for (num=0;num<DataDefCount[ApplicationState];num++) {
    if (DataDefinitions[ApplicationState][num].DataType & DATA_INPUT_MASK) {
      temp = Nodes[IDindex].OutData[DataDefinitions[ApplicationState][num].DataChannel] & ~DataDefinitions[ApplicationState][num].Mask; // Get the existing data
      temp |= DataDefinitions[ApplicationState][num].HWMapFunc(0,0) & DataDefinitions[ApplicationState][num].Mask; // Add the new from HW data in
      Nodes[IDindex].OutData[DataDefinitions[ApplicationState][num].DataChannel] = temp; // Update memory location with result
      if (!IDindex) {                                                           // Copy to in-data when its local only
        Nodes[IDindex].InData[DataDefinitions[ApplicationState][num].DataChannel] = temp; 
      }
    }
  }
}
    
// "Direction" is a temporary fix to having node dependent ddef's
/**
 * @fn unsigned int HWMap_ChipTemp(uint8_t direction, unsigned int Value)
 *
 * @brief This fucntion returns the current temperature data.
 *
 * @param direction an unsigned int
 * @param Value an unsigned int
 *
 * @return an unsigned int
 */
unsigned int HWMap_ChipTemp(uint8_t direction, unsigned int Value)
{
  return ADC10MEM;
}

/**
 * @fn unsigned int HWMap_RedLED(uint8_t direction, unsigned int Value)
 *
 * @brief This function maps the Red LED to hardware based on the input.
 *
 * @param direction an unsigned int
 * @param Value an unsigned int
 *
 * @return an unsigned int
 */
unsigned int HWMap_RedLED(uint8_t direction, unsigned int Value)
{
  if (Value) {
    SetGPIOOutputPort(__BOARD_LED1_PORT,__BOARD_LED1_PIN);
  } else {
    ClearGPIOOutputPort(__BOARD_LED1_PORT,__BOARD_LED1_PIN);
  }
  return Value;
}

/**
 * @fn unsigned int HWMap_GreenLED(uint8_t direction, unsigned int Value)
 *
 * @brief This function maps the Green LED to hardware based on the input.
 *
 * @param direction an unsigned int
 * @param Value an unsigned int
 *
 * @return an unsigned int
 */
unsigned int HWMap_GreenLED(uint8_t direction, unsigned int Value)
{
  if (direction) if (Value) P1OUT_6 = 1; else P1OUT_6 = 0;
  return P1IN_6;
}

/**
 * @fn unsigned int HWMap_RedLEDandButton(uint8_t direction, unsigned int Value)
 *
 * @brief This function maps the Red LED to hardware based on the button switch 
 *        input.
 *
 * @param direction an unsigned int
 * @param Value an unsigned int
 *
 * @return an unsigned int
 */
unsigned int HWMap_RedLEDandButton(uint8_t direction, unsigned int Value)
{
  static unsigned int ButtonToggle=0;
  if (direction) {
    if (Value) P1OUT_0 = 1; else P1OUT_0 = 0;
  } else {
    if ((PushButton) || (!__BOARD_MODESWITCH)) {
      ButtonToggle ^= 0xFFFF;
      PushButton = 0;
      if (ButtonToggle) P1OUT_0 = 1; else P1OUT_0 = 0;
    }
  }
  return ButtonToggle;
}

/**
 * @fn HWMap_PWM(uint8_t direction, unsigned int Value)
 *
 * @brief This function maps the PWM to hardware based on the input.
 *        This functionality is currently not implemented.
 *
 * @param direction an unsigned int
 * @param Value an unsigned int
 *
 * @return an unsigned int
 */
unsigned int HWMap_PWM(uint8_t direction, unsigned int Value)
{
  return 0;
}

/**
 * @fn unsigned char CmdIF_DataDefinitions(void)
 *
 * @brief This function writes out what data is received from Application
 *        State - Hub.      
 *
 * @return an unsigned char
 */
unsigned char CmdIF_DataDefinitions(void) 
{
  unsigned char i;
  TagBegin("DataDef",0);                                                        // Tag with attributes
  for (i=0;i<DataDefCount[ApplicationState];i++) {
    TagBegin("data",1);
      ElemAttrUint8("num",i);
      ElemAttrUint8("type",DataDefinitions[ApplicationState][i].DataType);      // Maybe convert to text?
      ElemAttrText("label",DataDefinitions[ApplicationState][i].Label);
      ElemAttrText("min",DataDefinitions[ApplicationState][i].Min);
      ElemAttrText("max",DataDefinitions[ApplicationState][i].Max);
      ElemAttrText("unit",DataDefinitions[ApplicationState][i].Unit);
    TagEnd("data",0);
  }
  TagEnd("DataDef",0);                                                          // Tag end, no element
  return 1;
}


/**
 * @fn void NewMessage(PayloadFrame *Payload, unsigned char id)
 *
 * @brief This function writes out a message from the specified node.
 *
 * @param Payload a PayloadFrame structure pointer
 * @param id an unsigned char
 */
void NewMessage(PayloadFrame * Payload, unsigned char id) 
{
  if ((ResponseFlags.AllowMessage) && (TagFlags.TagLevel==0)) {
    TagBegin("message",1);
    ElemAttrUint8("src",id);
    // We dont have messaging implemented yet, we need to move to payload unions first
    TagEnd("message",0);
  }
}


/**
 * @fn unsigned char CmdIF_SetCycleUpdateRate(void)
 *
 * @brief This function sets the current cycle time based on user's input.
 *
 * @return an unsigned char
 */
unsigned char CmdIF_SetCycleUpdateRate(void)
{
  unsigned char i,ID;
  unsigned int rate;
  if(GetParmByte("ID",&ID)){
    if(GetParmWord("rate",&rate)){
      if (ID < MAX_NODES) {
        if (ID) {
          i=NodeIsInMyNet(Nodes[ID].ID);                                        // Check thats its an active ID
          if(i){
            SetCycleTime(i, rate);                                              // Set the remote nodes cycle time field to be relayed at next ack to this node
            return 1;                                                           // Should perhaps return a "wait for command completion" status?
          } else {
            return 0;
          }
        } else {
          SetCycleTime(0, rate);
          return 1;
        }
      }
    }
  }
  return 0;                                                                     // If all else ... fail(s)
}

//! \brief Command Interface Processing 
//! \brief Command Interface 
/**
 * @fn void CmdIFResponse(char* string, unsigned char length)
 *
 * @brief This function writes out the response of the command.
 *
 * @param string a character pointer
 * @param length an unsigned char
 */
void CmdIFResponse(char * string, unsigned char length) 
{
  unsigned int i=0;
  if (!CmdFlags.ResultIsDelayed) {                                              // If we are waiting for a delayed result, we will throw away everything until then - just too bad, 
                                                                                // Otherwize we could end up with status messages etc. inside the command response
    while ((i<length) || ((length==0) && string[i]!=0)) {                       // i<length will be evaluated first and if true the second part will not be evaluate, 
                                                                                // making fixed length the fastest to execute
      i++;
    }
    length = i;
    if (length) {
      uint8_t r = length % 10;
      uint8_t d = length / 10;
      uint8_t index = 0;
      for(uint8_t i=0;i<d;i++){
        COMPortWrite(__BOARD_COMPORT1_PERIPHERAL, BLOCKING, (uint8_t *)&string[index], 10); 
        index = index + 10;
      }
      COMPortWrite(__BOARD_COMPORT1_PERIPHERAL, BLOCKING, (uint8_t *)&string[index], r); 
    }
  }
}

//! \brief Now for the Command Interface
/**
 * @fn signed char CmdIFCollect(signed char InData)
 *
 * @brief This function should called from the function that receives the incomming
 *        data. This could for instance be a UART ISR, a USB ISR or another stream
 *        of characters. This function takes only one character at a time as it is 
 *        intended to be used as an extension to an ISR, taking bytes as they 
 *        arrive. The function is written to be efficient to allow running it under
 *        ISR, but it can also safely be run with interrupt enabled - provided that
 *        the CmdFlags.Command = 1 operation is atomic for the target uCtrl.
 *
 *        If this function returns 0 then there is already a potential command waiting
 *        for the application to process and this function cannot accept any further
 *        inputs. If the incomming data is buffered from the source then a returned 0 
 *        should be used to keep buffering until this function can again accept data.
 *        If the incomming data is not buffered then it will be lost if this function
 *        returns 0.
 *
 *        A number different than 0 is returned if this function "took" the data (this
 *        does not mean it was added to the potential command as certain characters
 *        are simply discarded)
 * 
 *        The application should poll for commands using the CommandPreProcessing()
 *        function as that will reset CmdIF.InCmdSeq, which will allow taking in a
 *        a new comand.
 *
 * @param InData a signed char
 *
 * @return a signed char
 */
signed char CmdIFCollect(signed char InData /*!< Character to be added to command */) 
{                                                                               // This function will be called while under interrupt, so it must be very quick!
  if (CmdFlags.CommandReady) return 0;                                          // There's an unprocessed command waiting
  #ifdef XML_INPUT_SUPPORT
  if ((InData<0x20) || ((InData == '>') && (RawCommand[InCmdSeq-1]=='/'))) {    // XML format allows 'space', but not XML end brackets (obviously!)
  #else
  if (InData<0x21) {                                                            // The abreviated format terminates on 'space' too, but not on XML end brackets
  #endif
                                                                                // Any control character and 'space' will be used as command termination,
                                                                                // including return, linefeed etc. An inline XML termination is an 
                                                                                // alternative termination sequence
    CmdFlags.CommandReady=1;                                                    // Command is waiting for processing, atomic operation otherwise must be interrupt protected
    return 1;                                                                   // discard the command terminating character i.e. it is not added to the local 'raw' command buffer
  }
  if (InCmdSeq < MaxRawCommandLength-1) {
    RawCommand[InCmdSeq++]=InData;                                              // Add on to command
  } else {
    CmdFlags.CommandReady=1;                                                    // If our buffer is full then attempt to use it as a complete command
  }
  return 1;
}

/**
 * @fn unsigned char CmdIFProcess(char *CmdString)
 *
 * @brief This function is called from a polling loop in the application. 
 *        If called with a null pointer it will check if a command was received 
 *        through the CmdIFCollect().
 *        If called with a non-null pointer it will use the string pointed to by
 *        the pointer as the command.
 *        Next it will perform a rudimentary syntax check and discard the command
 *        if it fails.
 *        The application should use this function to poll for command or to setup
 *        and 'screen' a command delivered as a string. The string passed via the 
 *        pointer or the internally collected command string are used directly 
 *        during the entire command execution and MAY NOT BE MODIFIED until the 
 *        command is completely executed. The internal command collector mechanism 
 *        includes an blocking mechanism, however, if a command is passed as a 
 *        string pointer, no such blocking mechanism exist.
 *        --------------- update below ----------------
 *        perform a rudimetary command syntax checkreply back with the interpreted 
 *        command through the command interface. If the format is valid it will 
 *        add the command-response and data seperator ":". If the format is invalid
 *        it will reply with illegal command, terminate the response and reset 
 *        the Command to 0.
 *        If the command is 0, then the application should simply ignore it. The
 *        application shall process the command first, and if it's not a valid 
 *        application command, pass it on to the protocol. The protocol shall
 *        then process the command and if it is not a valid protocol command, pass
 *        it on to the hardware layer (BuiltInCmdProcessing()). Commands can thus
 *        be overlaid, such that even if a command is a valid hardware layer command,
 *        the protocol or the application cam implement an overriding command.
 *        Similarly it is possible to have multiple or all layers react to a command,
 *        by processing it, but still passing it on to the next level down.
 *
 * @param CmdString a char
 *
 * @return an unsigned char
 */
unsigned char CmdIFProcess(char * CmdString) 
{
  unsigned char c,len=0,res,FoundCmd=0;
  if (!CmdFlags.ResultIsDelayed) {
    if (CmdString) {                                                            // A command string was passed to us
      CmdIFCommandString = CmdString;
      CmdFlags.InternalCommand = 0;
    } else if (CmdFlags.CommandReady) {                                         // Do we have a CmdIFCollect()'ed command string?
      RawCommand[InCmdSeq] = 0;                                                 // Add string terminator to command string
      InCmdSeq=0;                                                               // Reset the incomming command character index
      CmdFlags.InternalCommand = 1;
      CmdIFCommandString = RawCommand;
    } else {                                                                    // App may call this any time in a polling fashion, so if theres no cmd return 0
      return 0;
    }
    while (CmdIFCommandString[len]) len++;                                      // Find termination null char
    if (len) {                                                                  // Dont accept a null length string
      while (*CmdIFCommandString < 0x40) { CmdIFCommandString++; len--; }       // Get rid of XML bracketing and other leading garbage, commands must begin with '@' or higher
      #ifdef XML_INPUT_SUPPORT
      if (CmdIFCommandString[len-1] == '/') CmdIFCommandString[len-1] = 0;      // Move command termination to get rid of XML termination chars 
      #endif
                                                                                // Execute the command 
      TagBegin("command",0);                                                    // We have arguments
      DelayedResult=0;
      CmdFlags.ResultIsDelayed = 0;
      c=0;
      while (CommandDefinitions[c].Command[0]) {                                // Check to see that the command is not a null string, which would mean its the end of the list
        if (StrCmp(CommandDefinitions[c].Command,CmdIFCommandString)) {
          TagBegin("cmd",0);                                                    // We have found the command

          CmdIFResponse(CommandDefinitions[c].Command,0);
          if (!ResponseFlags.XML_Output) CmdIFResponse(":",1);
          TagEnd("cmd",0);
          CmdIFCommandString += StrLen(CommandDefinitions[c].Command);          // Remove the command and point to possible arguments
          FoundCmd=1; res = 0;
          CmdFlags.ParmCount = 0;                                               // Reset the parameter counter
          if (CommandDefinitions[c].CmdFunction) {
            res = CommandDefinitions[c].CmdFunction();
          }
          if (res==0xFF) {                                                      // If the function is unable to complete immediately
            CmdFlags.ResultIsDelayed = 1;
                                                                                // Set the delayed command to timeout after 16calls to this function (0xF0+16=0=error) 
            DelayedResult = 0xF0;                                               // Set it to minimum one higher than what a result can be (2), so when we count up it will roll over to 0=fail
            return 1;
          }
          ResponseResult(res);
          break;
        }
        c++;
      }
    ThisIsBadCodingStyleIKnow:
      if (!FoundCmd) ElemAttrText("cmddef",(ResponseFlags.XML_Output) ? "err" : ":#");
      TagEnd("command",0);
      if (CmdFlags.ToggleFormatUponCmdCompletion) {
        ResponseFlags.XML_Output ^= 1;
        CmdFlags.ToggleFormatUponCmdCompletion = 0;
      }
      TagFlags.TagLevel=0;                                                      // Just in case we messed it up somewhere, at least it does not propagate
    }
    if (CmdFlags.InternalCommand) CmdFlags.CommandReady=0;
    if (FoundCmd) return 1; else return 0;
  } else {                                                                      // Result is delayed
    if (DelayedResult < 2) {                                                    // Its eiter a failure or a success
      CmdFlags.ResultIsDelayed = 0;                                             // Our wait is over
      res = DelayedResult;
      FoundCmd = 1;
      ResponseResult(res);
      goto ThisIsBadCodingStyleIKnow;
    } else {
      DelayedResult++;                                                          // This serves as a timeout, we can only go through this function 253 times before we give up
      return 0;
    }
  }
}

/**
 * @fn void ResponseResult(unsigned char res)
 *
 * @brief This function writes out the result of the command.
 *
 * @param res an unsigned char
 */
void ResponseResult(unsigned char res) 
{
  if (ResponseFlags.XML_Output) {
    ElemAttrText("res",(res) ? "ok" : "err");
  } else {
    ElemAttrText("res",(res) ? ":*" : ":#");
  }
}

/**
 * @fn void ProvideDelayedResult(unsigned char result)
 *
 * @brief This function is called when a delayed result for the command is intended.
 *
 * @param result an unsigned char
 */
void ProvideDelayedResult(unsigned char result) 
{
  DelayedResult=result;
}
  
/**
 * @fn unsigned char StrLen(char *Str)
 *
 * @brief This function finds out the length of the string passed to it.
 *
 * @param Str a character pointer
 */
unsigned char StrLen(char * Str) 
{
  unsigned char i=0;
  while (Str[i]) i++;                                                           // Find the null char
  return i;
}

/**
 * @fn unsigned char StrCmp(char * Src, char * Dst)
 *
 * @brief This function compares two strings.
 *        Note that this string compare function is tailored to finding a command
 *        and will therefore return false if both strings are "null". Similarly
 *        it will return true even though one string may contain command parameters
 *        following the command string.
 *
 * @param Src a character pointer
 * @param Dst a character pointer
 */
unsigned char StrCmp(char * Src, char * Dst) 
{
  unsigned char i=0;
  if (!Src[i] || !Dst[i]) return 0;                                             // We dont consider two null strings a match
  while (Src[i] == Dst[i]) {
    i++;
    if (!Src[i] || !Dst[i]) {                                                   // If one of them is null terminated then we gotta check for end of cmd
      if ((Src[i] ? Src[i] : Dst[i]) > 0x46) {                                  // If one of them still has valid cmd char(s) left then its not a match
        return 0;
      } else {
        return 1;
      }
    }
  }
  return 0;                                                                     // It was not a match
}

/**
 * @fn void ResponseParameter(signed long value, unsigned char format, unsigned char valid)
 *
 * @brief This function repeats the interpreted parameter.
 *
 * @param value a signed long
 * @param format an unsigned char
 * @param valid an unsigned char
 */
void ResponseParameter(signed long value, unsigned char format, unsigned char valid) 
{
  char text[5];                                                                 // Max size required to hold 'p' and a byte in decimal format and string termination
  text[0]='p';
  ResponseNumber((signed long)CmdFlags.ParmCount++, UnsignedDecimalByte, &text[1]);
  text[4]=0; // just in case
  if (valid) ElemAttrUniv(text, 0, value, format); else ElemAttrText(text,"NaN");// Autotag usage
}

/**
 * @fn unsigned char GetParmByte(char *ParmLabel, unsigned char *ReturnDataPtr) 
 *
 * @brief This function returns the parameter byte passed by user in the command 
 *        argument.
 *
 * @param ParmLabel a character pointer
 * @param ReturnDataPtr an unsigned character pointer
 */
unsigned char GetParmByte(char * ParmLabel, unsigned char * ReturnDataPtr) 
{
  unsigned long temp;
  unsigned char r=GetParmValue(ParmLabel,&temp,1);
  *ReturnDataPtr=(unsigned char)temp;
  ResponseParameter(temp, UnsignedDecimalByte, r);
  return r;
}

/**
 * @fn unsigned char GetParmWord(char * ParmLabel, unsigned int * ReturnDataPtr) 
 *
 * @brief This function returns the parameter word passed by user in the command 
 *        argument.
 *
 * @param ParmLabel a character pointer
 * @param ReturnDataPtr an unsigned integer pointer
 */
unsigned char GetParmWord(char * ParmLabel, unsigned int * ReturnDataPtr) 
{
  unsigned long temp;
  unsigned char r=GetParmValue(ParmLabel,&temp,3);
  *ReturnDataPtr=(unsigned int)temp;
  ResponseParameter(temp, UnsignedDecimalWord, r);
  return r;
}

/**
 * @fn unsigned char GetParmLong(char *ParmLabel, unsigned long *ReturnDataPtr) 
 *
 * @brief This function returns the parameter long value passed by user in the  
 *        command argument.
 *
 * @param ParmLabel a character pointer
 * @param ReturnDataPtr an unsigned long pointer
 */
unsigned char GetParmLong(char *ParmLabel, unsigned long *ReturnDataPtr) {
  unsigned long temp;
  unsigned char r=GetParmValue(ParmLabel,&temp,7);
  *ReturnDataPtr=temp;
  ResponseParameter(temp, UnsignedDecimalLong, r);
  return r;
}
  
/**
 * @fn unsigned char GetParmValue(char * ParmLabel, unsigned long * ReturnDataPtr, unsigned char ParmSize) 
 *
 * @brief This function returns the parameter value passed by user in the command 
 *        argument.
 *
 * @param ParmLabel a character pointer
 * @param ReturnDataPtr an unsigned long pointer
 * @param ParmSize an unsigned char
 */
unsigned char GetParmValue(char * ParmLabel, unsigned long * ReturnDataPtr, unsigned char ParmSize) 
{
  unsigned char i,temp;
  unsigned long num=0;
  // First get rid of leading garbage if any
  while ((*CmdIFCommandString) && (((*CmdIFCommandString < 0x30) || (*CmdIFCommandString > 0x46)) 
                                   || ((*CmdIFCommandString > 0x39) && (*CmdIFCommandString < 0x41)))) CmdIFCommandString++;
  i=ParmSize;                                                                   // Restrict to long?
  do {
    temp = *CmdIFCommandString++ - 0x30;                                        // Numerals start at 0x30
    if (temp>0x10) temp -= 7;                                                   // We have to get rid of ":;<=>?@" if its "ABCDEF"
    if (temp>0x10) {
      return 0;
    } else {
      num += ((unsigned long)temp) << (i*4);
    }
  } while (i--);
  *ReturnDataPtr = num;
  return 1;
}

/**
 * @fn void CommandError(char *desc)
 *
 * @brief This function writes out if there is any error in the command.
 *
 * @param desc a character pointer
 */
void CommandError(char * desc) 
{
  if (ResponseFlags.XML_Output) {                                               // Error descriptions are not used in abbreviated format
    TagBegin("Err",0); 
    CmdIFResponse(desc,0);
    TagEnd("Err",0); 
  }
}

/**
 * @fn unsigned char DebugNote(char * Desc) 
 *
 * @brief This function writes a test string to the response stream. All information 
 *        that are not part of the command interface protocol must use this function 
 *        to output the information string to the response stream. This allows the
 *        GUI to eliminate the debug information at will through the 'hn' command.
 *
 * @param Desc a character pointer
 */
unsigned char DebugNote(char * Desc) 
{
  static unsigned int NoteID=0;
  if (ResponseFlags.AllowDebug) {
    TagBegin("note", 1);
    ElemAttrUint16("num",NoteID++);
    TagEnd("Note",1);
    CmdIFResponse(",",1);
    CmdIFResponse(Desc,0);
    TagEnd("note",0);
    return 1;
  }
  return 0;
}

/**
 * @fn void ResponseFileHeader(void) 
 *
 * @brief This function writes out the header of the file in XML format.
 */
void ResponseFileHeader(void) 
{
  CmdIFResponse("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n", 0);
}

/**
 * @brief 0-7, abreviated format, 8-15,  XML format.
 *        0,4 StartID begin bracket, 1,5 StartID end bracket, 2,6 EndID begin 
 *        bracket, 3,7 EndID end bracket
 *        8 inline startID begin bracket, 9 inline StartID end bracket, 10, inline
 *        EndID begin bracket, 11 EndID end bracket
 * -------------------------   0    1    2     3        4         5   6      7  ----------
 */
char * const Brackets[16] = { "!", ":", "",   "\r\n",  "\r\n",   ",", "",    "", 
                              "<", ">", "</", ">\r\n", "/>\r\n", " ", "=\"", "\"" }; // Bracketing chars used below
  typedef enum eBracketDesc {
    eTagBeginBeginBracket = 0,
    eTagBeginEndBracket   = 1,
    eTagEndBeginBracket   = 2,
    eTagEndEndBracket     = 3,
    eTagEndElementless    = 4,
    eAttributeBegin       = 5,
    eAttributeDivide      = 6,
    eAttributeEnd         = 7,
  } eBracketDesc;
  
/**
 * @fn char * Bracket(unsigned char placement)
 *
 * @brief This function returns a bracket based on its placement.
 *
 * @param placement an unsigned char
 *
 * @return a character pointer
 */
char * Bracket(unsigned char placement) 
{
  unsigned char i;
  i = ResponseFlags.XML_Output * 8;
  i += placement;
  return Brackets[i];
}

#define MAX_ABBREV_TAG_LEVEL 0
/**
 * @fn void TagBegin(char *label, unsigned char attributes) 
 *
 * @brief This function begins the tag and writes out the appropriate bracket for it.
 *
 * @param label a character pointer
 * @param attributes an unsigned char
 */
void TagBegin(char * label, unsigned char attributes) 
{
  if (TagFlags.InsideAttribute) AttributeEnd();
  if (TagFlags.InsideTag) TagEnd(label,1);                                      // This label is wrong, but this should only happen for element less
  if (ResponseFlags.XML_Output) {
    CmdIFResponse(Bracket(eTagBeginBeginBracket),0);
    CmdIFResponse(label,0);
  } else {
    if (TagFlags.TagLevel <= MAX_ABBREV_TAG_LEVEL) {
      CmdIFResponse(Bracket(eTagBeginBeginBracket),0);
      CmdIFResponse(label,1);
      CmdIFResponse(Bracket(eTagBeginEndBracket),0);
    }
  }
  if (attributes) {
    TagFlags.InsideTag = 1;
  } else {
    TagFlags.InsideTag = 0;
    if (ResponseFlags.XML_Output) CmdIFResponse(Bracket(eTagBeginEndBracket),0); 
  }
  TagFlags.TagLevel++;
}

/**
 * @fn void TagEnd(char * label, unsigned char elements)
 *
 * @brief This function ends the tag and writes out the appropriate bracket for it.
 *
 * @param label a character pointer
 * @param elements an unsigned char
 */
void TagEnd(char * label, unsigned char elements) 
{
  if (TagFlags.InsideAttribute) AttributeEnd();
  if (TagFlags.InsideTag) {                                                     // Element less
    if (!elements) TagFlags.TagLevel--;
    // The abbreviated format only uses tag level 0
    if ((TagFlags.TagLevel == 0) || (ResponseFlags.XML_Output)) CmdIFResponse(Bracket((elements) ? eTagBeginEndBracket : eTagEndElementless),0); 
    TagFlags.InsideTag = 0;
  } else {
    TagFlags.TagLevel--;
    if (ResponseFlags.XML_Output) { 
      CmdIFResponse(Bracket(eTagEndBeginBracket),0);
      CmdIFResponse(label,0); 
      CmdIFResponse(Bracket(eTagEndEndBracket),0);
    } else {
      if (TagFlags.TagLevel == 0) {
        CmdIFResponse(Bracket(eTagEndEndBracket),0);
      }
    }
  }
  if (TagFlags.TagLevel==0) TagFlags.OneOrMoreAttribs=0;                        // Start a fresh
}

/**
 * @fn void ElemAttrUint8(char *label, unsigned char data)
 *
 * @brief This function writes out a 8 bit unsigned integer element attribute.
 *
 * @param label a character pointer
 * @param data an unsigned char
 */
void ElemAttrUint8(char * label, unsigned char data) {  ElemAttrUniv(label, 0, (signed long)data, UnsignedDecimalByte); }

/**
 * @fn void ElemAttrUint16(char * label, unsigned int data)
 *
 * @brief This function writes out a 16 bit unsigned integer element attribute.
 *
 * @param label a character pointer
 * @param data an unsigned char
 */
void ElemAttrUint16(char * label, unsigned int data) {  ElemAttrUniv(label, 0, (signed long)data, UnsignedDecimalWord); }

/**
 * @fn void ElemAttrSint16(char * label, signed int data)
 *
 * @brief This function writes out a 16 bit signed integer element attribute.
 *
 * @param label a character pointer
 * @param data an signed char
 */
void ElemAttrSint16(char * label, signed int data) {    ElemAttrUniv(label, 0, (signed long)data, SignedDecimalWord); }

/**
 * @fn void ElemAttrUint32(char * label, unsigned long data) 
 *
 * @brief This function writes out a 16 bit unsigned integer element attribute.
 *
 * @param label a character pointer
 * @param data an unsigned char
 */
void ElemAttrUint32(char * label, unsigned long data) { ElemAttrUniv(label, 0, (signed long)data, UnsignedDecimalLong); }

/**
 * @fn void ElemAttrText(char * label, char *text)
 *
 * @brief This function writes out text element attribute.
 *
 * @param label a character pointer
 * @param text a character pointer
 */
void ElemAttrText(char * label, char * text) { ElemAttrUniv(label, text, 0,0); }

/**
 * @fn void ElemAttrUniv(char * label, char *text, signed long data, unsigned char format)
 *
 * @brief This function writes out the element attribute based on its data type.
 *
 * @param label a character pointer
 * @param text a character pointer
 * @param data a signed long
 * @param format an unsigned char
 */
void ElemAttrUniv(char * label, char * text, signed long data, unsigned char format) 
{
  if (TagFlags.InsideTag) {                                                     // If were in a tag then we create an attribute
    if (TagFlags.InsideAttribute) AttributeEnd();
    // Is this the first attribute, then dont add the attribute begin
    if ((TagFlags.OneOrMoreAttribs) || (ResponseFlags.XML_Output)) CmdIFResponse(Bracket(eAttributeBegin),0);       
    if (ResponseFlags.XML_Output) CmdIFResponse(label,0);                       // Attribute labels are not used in abbrreviated format
    CmdIFResponse(Bracket(eAttributeDivide),0);
    if (text) {
      CmdIFResponse(text,0);                                                    // If non-null text pointer we will print text
    } else {
      ResponseNumber(data, format, 0);                                          // Otherwize we will print the number
    }
    CmdIFResponse(Bracket(eAttributeEnd),0);
    TagFlags.InsideAttribute = 0;
    TagFlags.OneOrMoreAttribs = 1;
  } else {                                                                      // If were not in a tag we will create an element instead
    TagBegin(label,0);
    if (text) {
      CmdIFResponse(text,0);                                                    // If non-null text pointer we will print text
    } else {
      ResponseNumber(data, format, 0);                                          // Otherwize we will print the number
    }
    TagEnd(label,0);
  }
}

/**
 * @fn void AttributeEnd(void)
 *
 * @brief This function ends the attribute and writes out the appropriate bracket.
 */
void AttributeEnd(void) 
{
  TagFlags.InsideAttribute = 0;
  CmdIFResponse(Bracket(eAttributeEnd),0);
}
  
/**
 * @fn inline char HexNibble(char num)
 *
 * @brief This function writes out a hex nibble
 *
 * @param num a character
 */
inline char HexNibble(char num) { return num+0x30+(num>9)*7; }

/**
 * @fn void ResponseNumber(signed long Universal, unsigned char Format, char * Destination)
 *
 * @brief This function writes out a number in specified format.
 *
 * @param Universal a signed long
 * @param Format an unsigned char
 * @param Destination a character pointer
 */
void ResponseNumber(signed long Universal, unsigned char Format, char * Destination) 
{
  char TWS[12];
  unsigned char i, Size, k;
  if (Format==0) return;                                                        // Lets not output anything if the format is not specified
  if (!ResponseFlags.XML_Output) {
    Format &= 0x0F;                                                             // If not XML, force it to be hexadecimal formatting
    Format |= 0x40;
  }
  Size = Format & 0x0F;
  i=sizeof(TWS)-2;
  if (Format & 0x40) {                                                          // Hexadecimal format
    k=Size*2;
    while (k--) {
      TWS[i--] = HexNibble((unsigned char)(Universal & 0x0000000F));
      Universal >>= 4;
    }
  } else if (Format & 0x20) {                                                   // Binary Format
    k=Size;
    while (k--) {
      TWS[i--] = (unsigned char)(Universal & 0x000000FF);
      Universal >>= 8;
    }
  } else {                                                                      // Decimal format is default
    if (Universal == 0) {
      TWS[i--]= 0x30;
    } else {
      if ((Format & 0x80) && (Universal < 0)) {                                 // Negative number & format
        while (Universal) {
          TWS[i--]= 0x30-((signed char)(Universal % 10));
          Universal /= 10;
        }
        TWS[i--]='-';
      } else {                                                                  // Its a positive number, or we want it unsigned
        unsigned long TempUniv = (unsigned long)Universal;
        while (TempUniv) {
          TWS[i--]= 0x30+((unsigned char)(TempUniv % 10));
          TempUniv/=10;
        }
      }
    }
  }
  TWS[sizeof(TWS)-1]=0;                                                         // String termination character
  if (Destination) {
    while (++i < sizeof(TWS)) *Destination++ = TWS[i];
  } else {
    CmdIFResponse(&TWS[i+1],0);
  }
}

//! \brief Lastly we have the optional test functions 
#ifdef CmdIF_TestMode

/**
 * @fn void WaitForResponseQueueToEmpty(void)
 *
 * @brief This function waits for the command response buffer to empty.
 *        This is purely for debugging purposes to ensure that a breakpoint does 
 *        not disrupt the serial stream.
 */
void WaitForResponseQueueToEmpty(void) 
{
  volatile unsigned int sc, count=100;
  while (count--) for (sc=3000;sc;sc--);
}

/**
 * @fn unsigned char CmdIFCommand_ModuleTest(void)
 *
 * @brief This function runs a test of all functionality in this command interface 
 *        module.
 *
 * @return an unsigned char
 */
unsigned char CmdIFCommand_ModuleTest(void) 
{
  ResponseFileHeader();
  ResponseIdentifier("CmdIFCommand_ModuleTest",0);                              // Begin test marker
  TestCmdResponse();
  TestHWCommands();
  WaitForResponseQueueToEmpty();                                                // Have to wait as SampleApp() will re-init the CmdIF
  ResponseIDTerminator("CmdIFCommand_ModuleTest");                              // End test marker    
  return 1;
}

/**
 * @fn void TestCmdResponse(void) 
 *
 * @brief This function tests all functions that write to the UART. It inherently 
 *        includes UART buffer overrun test.
 */
void TestCmdResponse(void) 
{                                                   
  unsigned char k;
  unsigned int kw;
  signed int kws;
  unsigned long kl;
  signed long kls;
  char TWS[12];
  
  ResponseIdentifier("ResponseTest",0);                                         // Begin test marker
  //------------HexByte------------
  ResponseIdentifier("HexByte",1);                                              // Begin test marker
  k=0;
  do {
    ResponseNumber((signed long)k++, HexadecimalByte, TWS);
    ResponseArgumentText("hb",TWS);
  } while (k);
  ResponseIDTerminator("HexByte");
  //------------HexWord-------------
  ResponseIdentifier("HexWord",1);                                              // Begin test marker
  k=0;
  do {
    kw=0x55 << k++;
    ResponseNumber((signed long)kw, HexadecimalWord, TWS);
    ResponseArgumentText("hw",TWS);
  } while (k < 16);
  ResponseIDTerminator("HexWord");
  //--------------HexLong-----------
  ResponseIdentifier("HexLong",1);                                              // Begin test marker
  k=0;
  do {
    kl=0x55 << k++;
    ResponseNumber((signed long)kl, HexadecimalLong, TWS);
    ResponseArgumentText("hw",TWS);
  } while (k < 32);
  ResponseIDTerminator("HexLong");
  //---------------Unsigned Byte----------
  ResponseIdentifier("UnsignedByte",1);                                         // Begin test marker
  k=0;
  do {
    ResponseNumber((signed long)k++, UnsignedDecimalByte, TWS);
    ResponseArgumentText("hb",TWS);
  } while (k);
  ResponseIDTerminator("UnsignedByte");
  //--------------Signed byte-------------
  ResponseIdentifier("SignedByte",1);                                           // Begin test marker
  k=0;
  do {
    ResponseNumber((signed long)k++, SignedDecimalByte, TWS);
    ResponseArgumentText("hb",TWS);
  } while (k);
  ResponseIDTerminator("SignedByte");
  //--------------Unsigned Word-------------
  ResponseIdentifier("UnsignedWord",1);                                         // Begin test marker
  k=0;
  do {
    kw=0x55 << k++;
    ResponseNumber((signed long)kw, UnsignedDecimalWord, TWS);
    ResponseArgumentText("hw",TWS);
  } while (k < 16);
  ResponseIDTerminator("UnsignedWord");
  //--------------Signed Word-------------
  ResponseIdentifier("SignedWord",1);                                           // Begin test marker
  k=0;
  kws=-19;
  do {
    ResponseNumber((signed long)kws++, SignedDecimalWord, TWS);
    ResponseArgumentText("hw",TWS);
  } while (++k < 38);
  ResponseIDTerminator("SignedWord");
  //--------------Unsigned Long-------------
  ResponseIdentifier("UnsignedLong",1);                                         // Begin test marker
  k=0;
  do {
    kl=0x55 << k++;
    ResponseNumber((signed long)kl, UnsignedDecimalLong, TWS);
    ResponseArgumentText("hw",TWS);
  } while (k < 32);
  ResponseIDTerminator("UnsignedLong");
  //--------------Signed Long-------------
  ResponseIdentifier("SignedLong",1);                                           // Begin test marker
  k=0;
  kls=-19;
  do {
    ResponseNumber((signed long)kls++, SignedDecimalLong, TWS);
    ResponseArgumentText("hw",TWS);
  } while (++k < 38);
  ResponseIDTerminator("SignedLong");
  //--------------------------------------
  ResponseIDTerminator("ResponseTest");                                         // End test marker
}

#if MaxRawCommandLength < 20
#warning TestHWCommands() needs MaxRawCommandLength>=20 for desired results
#endif
void TestSingleHWCmd(char * TxtCmd);                                             //!< Prototyping of private fct right before we need it

/**
 * @fn void TestHWCommands(void)
 *
 * @brief This function tests all the hardware related commands.
 */
void TestHWCommands(void) 
{
  char TempCmd1[20];
  char TempCmd2[20];
  unsigned char TestData[32];
  unsigned char *DataPtr;
  unsigned long Temp;
  unsigned int i;
  char VeryLongCommand[MaxRawCommandLength+2];
  ResponseIdentifier("CommandTest",0);                                          // Begin test marker

  for (unsigned int i=0;i<32;i++) TestData[i]=i*8;
  TestSingleHWCmd("~~\r");
  TestSingleHWCmd("h~\r");
  TestSingleHWCmd("hn01\r");
  DebugNote("Debug Information notes are on");                                  // This should show up in the response stream
  TestSingleHWCmd("hn00\r");
  DebugNote("Debug Information notes are off");                                 // This should NOT show up in the response stream.
  TestSingleHWCmd("hn01\r");
  DebugNote("Debug Information notes are on");                                  // This should show up in the response stream
  
  //Illegal command checks
  TestSingleHWCmd("~~\r");                                                      // First a valid command
  TestSingleHWCmd("!~\r");                                                      // Then an invalid command, to make sure there are no 'hanging chads'
  TestSingleHWCmd("~~\r");                                                      // First a valid command
  TestSingleHWCmd("-~\r");                                                      // Then an invalid command, to make sure there are no 'hanging chads'
  TestSingleHWCmd("~~\r");                                                      // First a valid command
  TestSingleHWCmd("'~\r");                                                      // Then an invalid command, to make sure there are no 'hanging chads'
  TestSingleHWCmd("~~\r");                                                      // First a valid command
  TestSingleHWCmd("'~\r");                                                      // Then an invalid command, to make sure there are no 'hanging chads'
  TestSingleHWCmd("~~\r");                                                      // First a valid command
  TestSingleHWCmd("}~\r");                                                      // Then an invalid command, to make sure there are no 'hanging chads'
  TestSingleHWCmd("~~\r");                                                      // First a valid command
  TestSingleHWCmd("~!\r");                                                      // Then an invalid command, to make sure there are no 'hanging chads'
  TestSingleHWCmd("~~\r");                                                      // First a valid command
  TestSingleHWCmd("~-\r");                                                      // Then an invalid command, to make sure there are no 'hanging chads'
  TestSingleHWCmd("~~\r");                                                      // First a valid command
  TestSingleHWCmd("~'\r");                                                      // Then an invalid command, to make sure there are no 'hanging chads'
  TestSingleHWCmd("~~\r");                                                      // First a valid command
  TestSingleHWCmd("~}\r");                                                      // Then an invalid command, to make sure there are no 'hanging chads'
  TestSingleHWCmd("~~~\r");                                                     // Illegal
  TestSingleHWCmd("~~~~\r");                                                    // Illegal
  TestSingleHWCmd("hn\r");                                                      // Illegal number of parameters
  TestSingleHWCmd("hn0\r");                                                     // Illegal number of parameters
  TestSingleHWCmd("hn01\r");                                                    // legal number of parameters
  TestSingleHWCmd("hn011\r");                                                   // Illegal number of parameters
  TestSingleHWCmd("hn0101\r");                                                  // Illegal number of parameters
  TestSingleHWCmd("hnFF\r");                                                    // legal number of parameters
  TestSingleHWCmd("hn0FF0\r");                                                  // Illegal number of parameters
  TestSingleHWCmd("hnn0\r");                                                    // Illegal syntax
  TestSingleHWCmd("hn0n\r");                                                    // Illegal syntax
  TestSingleHWCmd("hn00\r");                                                    // legal number of parameters, end with debug off!
  
  //Command buffer overrun check
  VeryLongCommand[0] = 'h';
  VeryLongCommand[1] = 'n';
  for (i=2;(i<(sizeof(VeryLongCommand)-2));i++) VeryLongCommand[i]='0';
  VeryLongCommand[sizeof(VeryLongCommand)-2] = ' ';
  VeryLongCommand[sizeof(VeryLongCommand)-1] = 0;
  TestSingleHWCmd(VeryLongCommand);

  
  // Get ready for memory read/write testing
  DataPtr=&TestData[0];
  Temp = (unsigned long)DataPtr;
  // Memory read
  TempCmd1[0]='h';
  TempCmd1[1]='r';                                                              // Memory read command
  HexLong(Temp,&TempCmd1[2]);                                                   // Pointer to memory area
  HexByte(1,&TempCmd1[10]);                                                     // Read 1 byte
  TempCmd1[12]=13;                                                              // Command termination
  TempCmd1[13]=0;                                                               // String termination
  TestSingleHWCmd(&TempCmd1[0]);
  HexByte(2,&TempCmd1[10]);                                                     // Read two bytes
  TestSingleHWCmd(&TempCmd1[0]);
  HexByte(3,&TempCmd1[10]);                                                     // Read 3 bytes
  TestSingleHWCmd(&TempCmd1[0]);
  HexByte(255,&TempCmd1[10]);                                                   // Read 255 bytes
  TestSingleHWCmd(&TempCmd1[0]);
  HexByte(0,&TempCmd1[10]);                                                     // Read 256 bytes
  TestSingleHWCmd(&TempCmd1[0]);
 
  // Memory write
  TempCmd2[0]='h';
  TempCmd2[1]='w';                                                              // Memory write command
  HexLong(Temp,&TempCmd2[2]);                                                   // Pointer to memory area
  HexByte(~TestData[0],&TempCmd2[10]);                                          // Write 1 byte, inverse of original
  TempCmd2[12]=13;                                                              // Command termination
  TempCmd2[13]=0;                                                               // String termination
  HexByte(1,&TempCmd1[10]);                                                     // Read 1 bytes
  TestSingleHWCmd(&TempCmd2[0]);                                                // Write to memory
  TestSingleHWCmd(&TempCmd1[0]);                                                // Read from memory
  HexByte(~TestData[0],&TempCmd2[10]); 
  HexByte(~TestData[1],&TempCmd2[12]);                                          // Write 2 bytes, inverse of original
  TempCmd2[14]=13;                                                              // Command termination
  TempCmd2[15]=0;                                                               // String termination
  HexByte(2,&TempCmd1[10]);                                                     // Read 2 bytes
  TestSingleHWCmd(&TempCmd2[0]);                                                // Write to memory
  TestSingleHWCmd(&TempCmd1[0]);                                                // Read from memory
  HexByte(~TestData[0],&TempCmd2[10]); 
  HexByte(~TestData[1],&TempCmd2[12]);                                          // Write 2 bytes, inverse of original
  HexByte(~TestData[2],&TempCmd2[14]);                                          // Write 2 bytes, inverse of original
  TempCmd2[16]=13;                                                              // Command termination
  TempCmd2[17]=0;                                                               // String termination
  HexByte(3,&TempCmd1[10]);                                                     // Read 2 bytes
  TestSingleHWCmd(&TempCmd2[0]);                                                // Write to memory
  TestSingleHWCmd(&TempCmd1[0]);                                                // Read from memory  
  ResponseIDTerminator("CommandTest");                                          // Begin test marker
}

/**
 * @fn void TestSingleHWCmd(char *TxtCmd)
 *
 * @brief This function tests individual hardware related command.
 *
 * @param TxtCmd a character pointer
 */
void TestSingleHWCmd(char * TxtCmd) 
{
  unsigned int i=0;
  while (!TxtCmd[i]==0) {
    if (!CmdIFCollect(TxtCmd[i++])) {
      DebugNote("CmdIF in-buffer full");
    }
  }
  CmdIFProcess(0);
  WaitForResponseQueueToEmpty();
}

#endif

