/**
 *  @file main.c
 *
 *  @brief Application main
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
#include "RadioOperation.h"
#include "Protocol.h"
#include "Definitions.h"
#include "CommandInterface.h"
              
//#define RedLEDAlarm                                                           //!< Enable the functionality of Red LED Alarm
#define SENSOR_TICKS_TO_PAIR 2                                                  //!< Number of data transfer cycles on Sensor (to hold the button down for pairing)
extern PayloadFrame Payloads[];
extern uint8_t PushButton, ADCConversionDone;
extern uint8_t AnalogUpdating;

void main()
{
  unsigned char PairCountDown = SENSOR_TICKS_TO_PAIR;                           //!< Button press for the number of data transfer cycles on Sensor                    
  unsigned char i,id;
  #ifdef RedLEDAlarm
    unsigned int r;
  #endif

  // Initialize microcontroller peripherals and application.
  InitTimers();                                                                 // Initialize the Timers modules
  InitArchitecture();                                                           // Initialize the Architecture modules
  SetMyNodeID(0);                                                               // Set node ID. The random number generator requires this function
                                                                                // be called after timers and clocks are intitialized, but before the
                                                                                // ADC (data converters)
  InitCommunication();                                                          // Initialize the Communication modules
  InitDataConverters();                                                         // Initialize the Data Converter modules
  InitGPIO();                                                                   // Initialize the GPIO modules
  InitApplication(Nodes[0].ID);

  #if defined(__BOARD_LAUNCHPAD_SERIES)
    __BOARD_LEDRED_DIRECTION = 1;                                               // Change Red LED pin to output after radio has been initialized
  #endif
  
  TimerMode(TIMER1, TIMER_UP);                                                  // Start the timer prior to enabling interrupts
  
  __enable_interrupt();                                                         // Enable interrupts after everything has been initialized.

  while(1)
  {
    if(ApplicationState == HUB){
      id = HubWirelessOperation();                                              // Check for messages 
      if (id){
        // Do something with data in Nodes[]."In/Out"Data[]
        #ifdef RedLEDAlarm
          r = 0;
          for (i=1;i<MAX_NODES;i++) {
            if (Nodes[i].ID) {                                                  // Is it a valid network member
              r |= Nodes[i].InData[0] & 0x8000;                                 // 'OR' all red LED's (alarm)
            }
          }
          Nodes[0].InData[0] = (Nodes[0].InData[0] & (~0x8000)) | r;            // Update our local copy for a red LED Alarm
          if (r) {                                                              // Write to the HW the red LED (redundant)
            P1OUT_0 = 1;
          } else {
            P1OUT_0 = 0;
          }
        #endif
      }
      if (ADCConversionDone){                                                   // Check for new analog data (local temperature)
        ADCConversionDone = 0;                                                  // Clear flag
        #if defined(__COMMAND_INTERFACE)
          ReportData(0);                                                        // Report Local only HW 
          for (i=1;i<MAX_NODES;i++) {
            //for (r=0;r<DATA_CHANNELS;r++) {                                   // Commented out as we want only temperature to propagate
              Nodes[i].OutData[1]=Nodes[0].InData[1];                           // Reflect the info from hub on all sensors/remotes
            //}
          }
        #endif
        if (!__BOARD_MODESWITCH) {                                              // Pressing the pairing button while in HUB mode temporarily changes the node to SENSOR mode
          if (!PairCountDown--) {                                               // Must press pairing button for a little while for it to stick - should this number of sensor ticks?
            for (i=1;i<MAX_NODES;i++) {
              Nodes[i].ID = 0;                                                  // Get rid of the current one if we have one
            }
            SetApplicationState(SENSOR);                                        // Change the applictaion state to Sensor and immediately place it in pairing mode.
            SetPairingMask(0xFFFFFFFF);
            PairCountDown = SENSOR_TICKS_TO_PAIR;                               // Reset the pairing count down counter
          }
        }
      }
    }
    else if(ApplicationState == SENSOR) {
      if (ADCConversionDone) {
        ADCConversionDone = 0;                                                  // Clear flag
        ReportData(0);                                                          // Report it local only HW
        if (!__BOARD_MODESWITCH) {
          if (!PairCountDown--) {                                               // Must press pairing button for a little while for it to stick - should this number of sensor ticks?
            RemoveNodeFromNetwork(1);                                           // Get rid of the current one if we have one
            SetPairingMask(0xFFFFFFFF);
          }
        } 
        else{
        }
        if (GetPairingMask()) {
          PairCountDown = SENSOR_TICKS_TO_PAIR;                                 // Reset the pairing count down counter
        }
        MapSensorsFromHW(1);                                                    // Map input to Hub spot
        id = SensorWirelessOperation();                                         // Send ADC sample, etc,
        if (id){
          // Do something with the arrived data
          MapControlsToHW(id);                                                  // Map the received data to HW, data already has been copied to local storage area (Node index 0) 
        }
        ApplicationState = (__ApplicationState) MyFlashedAppState;              // If pairing was unsuccessful or there is no payload, change to state stored in flash
      } 
    }

    #if defined(__COMMAND_INTERFACE)
      if(CmdIFProcess(0)){                                                      // Run the command interface.
      }
    #endif

    __low_power_mode_0();                                                       // Nothing else to do.  Sleep until next interrupt arrives.
  }
}
