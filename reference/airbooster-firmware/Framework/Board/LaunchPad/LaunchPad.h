/**
 *  @file LaunchPad.h
 *
 *  @subpage launchpad LaunchPad Definition
 *
 *  @brief Board definition for the LaunchPad. This definition allows for the
 *         AIR BoosterPack Lite to be connected to add radio capabilities.
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
#ifndef __BOARD_LAUNCHPAD_H
#define __BOARD_LAUNCHPAD_H

// Include AIR Framework configuration
#include "../../Configuration/Config.h"

// Verify that the MCU provided is supported by this board
// NOTE: This LaunchPad definition currently supports the MSP430G2453 and MSP430G2553 
// microcontroller.
#if defined(__MCU_MSP430_G2553)
  #include "../../MCU/MSP430/Model/G2553.h"
#elif defined(__MCU_MSP430_G2453)
  #include "../../MCU/MSP430/Model/G2453.h"
#else
  #error "__HAL_ERROR: Microcontroller not supported on the selected board."
#endif

// MSP430G2453/G2553
//
// The following describes the MSP430G2453/MSP430G2553 connections as seen on the
// LaunchPad board.
////////////////////////////////////////////////////////////////////////////////

/**
 *  @section Microcontroller
 *
 *  @brief Microcontroller socket definition for the LaunchPad board. Describes
 *  the package and socket pin count.
 */
#define __BOARD_MCU_PDIPPACKAGE                                                 // PDIP packaging
#define __BOARD_MCU_SOCKET	      20                                        // 20 pin socket

// COMPONENT DEFINITIONS
//
// This section describes the components that the MSP430G2453/G2553 is connected
// to. Only components that require an interface from the AIR Framework are 
// defined. These interfaces are implemented in the FPI directory and FPI.h.
//
// @see FPI.h
//
// The following are the LaunchPad board components that have interfaces in the
// AIR Framework:
//  - LED
//  - Switch
//  - Communication Port (COM Port)
//  - Radio (when AIR BoosterPack Lite attached and defined)
////////////////////////////////////////////////////////////////////////////////

/**
 *  @section LED
 *
 *  @brief LED definition for the LaunchPad board. Describes how to interact with
 *  an onboard LED.
 */
#define __BOARD_LED                                                             // The board has a LED
#define __BOARD_LED_COUNT	      2                                         // Number of LEDs
// Define basic information about LED 1.
#define __BOARD_LED1		      1	                                        // LED1 connected on P1.0
#define __BOARD_LED1_PORT	      PORT1                                     // LED1 port connection
#define __BOARD_LED1_PIN	      PIN0                                      // LED1 pin connection
#define __BOARD_LED1_DIRECTION        P1DIR_0                                   // LED1 direction
// Define basic information about LED 2.
#define __BOARD_LED2		      2		                                // LED2 connection on P1.6
#define __BOARD_LED2_PORT	      PORT1                                     // LED2 port connection
#define __BOARD_LED2_PIN	      PIN6                                      // LED2 pin connection
#define __BOARD_LED2_DIRECTION        P1DIR_6
// Define LED aliases.
#define __BOARD_LEDRED		      __BOARD_LED1                              // LED1 alias
#define __BOARD_LEDRED_DIRECTION      __BOARD_LED1_DIRECTION
#define __BOARD_LEDGREEN	      __BOARD_LED2                              // LED2 alias
#define __BOARD_LEDGREEN_DIRECTION    __BOARD_LED2_DIRECTION

/**
 *  @section Switch
 *
 *  @brief Switch definition for the LaunchPad board. Describes how to interact 
 *  with an onboard switch.
 */
#define __BOARD_SWITCH                                                          // The board has a switch
#define __BOARD_SWITCH_COUNT	      2                                         // Number of switches
// Define basic information about switch 1.
#define __BOARD_SWITCH1               1                                         // SWITCH1 connected on RST
#define __BOARD_SWITCH1_PORT                                                    // NOTE: Switch connected to reset.
#define __BOARD_SWITCH1_PIN                                                     // NOTE: Switch connected to reset.
#define __BOARD_SWITCH1_PUSHBUTTON                                              // SWITCH1 is a push button
// Define basic information about switch 2.
#define __BOARD_SWITCH2               P1IN_3                                    // SWITCH2 connected on P1.3
#define __BOARD_SWITCH2_PORT	      PORT1                                     // SWITCH2 port connection
#define __BOARD_SWITCH2_PIN	      PIN3                                      // SWITCH2 pin connection
#define __BOARD_SWITCH2_PUSHBUTTON                                              // SWITCH2 is a push button

/**
 *  @section COM Port
 * 
 *  @brief COM Port definition for the LaunchPad board. Describes how to interact 
 *  with an onboard COM Port.
 */
#define __BOARD_COMPORT                                                         // The board has a COM port
#define __BOARD_COMPORT_COUNT	      1                                         // Number of COM ports
// Define basic information about COM port 1.         
#define __BOARD_COMPORT1              1                                         // COMPORT1 is connected using a UART interface
#define __BOARD_COMPORT1_PERIPHERAL   USCIA0                                    // Connection to peripheral
// Define COM port 1 UART connection.
#define __BOARD_COMPORT1_TX                                                     // COMPORT1 transmit line
#define __BOARD_COMPORT1_TXPORT	      PORT1                                     // COMPORT1 transmit line port connection
#define __BOARD_COMPORT1_TXPIN	      PIN1                                      // COMPORT1 transmit line pin connection
#define __BOARD_COMPORT1_RX                                                     // COMPORT1 receive line
#define __BOARD_COMPORT1_RXPORT	      PORT1                                     // COMPORT1 receive line port connection
#define __BOARD_COMPORT1_RXPIN	      PIN2                                      // COMPORT1 receive line pin connection

// AIR BOOSTERPACK LITE
//
// This section defines the AIR BoosterPack Lite board that can attach onto the
// TI LaunchPad board. This board provides wireless communicate capabilities
// using ANAREN AIR modules.
//
// NOTE: This may be moved to a seperate file dedicated to the AIR BoosterPack
// Lite board underneath the LaunchPad directory in a BoosterPacks/ directory.
////////////////////////////////////////////////////////////////////////////////
#if defined(__BOARD_AIRBOOSTERPACKLITE_SERIES)

/**
 *  @section Radio
 *
 *  @brief Radio definition for the AIR BoosterPack Lite board. Describes how 
 *  to interact with an onboard radio.
 */
#define __BOARD_RADIO                                                           // The board has a radio
#define __BOARD_RADIO_SOCKET	                                                // Radio socket.
#define __BOARD_RADIO_COUNT         1                                           // Number of radios
// Define basic information about radio 1
#define __BOARD_RADIO1                1                                         // RADIO1 is connected using a serial peripheral interface (SPI)
#define __BOARD_RADIO1_PERIPHERAL     USCIB0                                    // RADIO1 connection to peripheral
#define __BOARD_RADIO1_CONNECTION     EXTERNAL                                  // RADIO1 connection is external
#define __BOARD_RADIO1_CONNECTIONTYPE IRFSPI                                    // RADIO1 external connection type is SPI based
// Define radio 1 interrupt source.
#define __BOARD_RADIO1_GDO0           P2IN_6                                    // RADIO1 interrupt source 1
#define __BOARD_RADIO1_GDO0PORT       PORT2                                     // RADIO1 interrupt source 1 port connection
#define __BOARD_RADIO1_GDO0PIN	      PIN6                                      // RADIO1 interrupt source 1 pin connection
#define __BOARD_RADIO1_GDO0ENABLE     P2IE_6                                    // RADIO1 interrupt source 1 enable
#define __BOARD_RADIO1_GDO0EDGESELECT P2IES_6                                   // RADIO1 interrupt source 1 edge select
#define __BOARD_RADIO1_GDO0FLAG       P2IFG_6                                   // RADIO1 interrupt source 1 flag
#define __BOARD_RADIO1_GDO2           P1IN_0                                    // RADIO1 interrupt source 2
#define __BOARD_RADIO1_GDO2PORT       PORT1                                     // RADIO1 interrupt source 2 port connection
#define __BOARD_RADIO1_GDO2PIN	      PIN0                                      // RADIO1 interrupt source 2 pin connection
#define __BOARD_RADIO1_GDO2ENABLE     P1IE_0                                    // RADIO1 interrupt source 2 enable
#define __BOARD_RADIO1_GDO2EDGESELECT P1IES_0                                   // RADIO1 interrupt source 2 edge select
#define __BOARD_RADIO1_GDO2FLAG       P1IFG_0                                   // RADIO1 interrupt source 2 flag
// Define radio 1 SPI connection.
#define __BOARD_RADIO1_CSN                                                      // RADIO1 chip select
#define __BOARD_RADIO1_CSNPORT	      PORT2                                     // RADIO1 chip select port connection
#define __BOARD_RADIO1_CSNPIN	      PIN7                                      // RADIO1 chip select pin connection
#define __BOARD_RADIO1_MOSI                                                     // RADIO1 master-out/slave-in
#define __BOARD_RADIO1_MOSIPORT	      PORT1                                     // RADIO1 master-out/slave-in port connection
#define __BOARD_RADIO1_MOSIPIN	      PIN7                                      // RADIO1 master-out/slave-in pin connection
#define __BOARD_RADIO1_MISO                                                     // RADIO1 master-in/slave-out
#define __BOARD_RADIO1_MISOPORT	      PORT1                                     // RADIO1 master-in/slave-out port connection
#define __BOARD_RADIO1_MISOPIN	      PIN6                                      // RADIO1 master-in/slave-out pin connection
#define __BOARD_RADIO1_SCLK                                                     // RADIO1 clock source
#define __BOARD_RADIO1_SCLKPORT	      PORT1                                     // RADIO1 clock source port connection
#define __BOARD_RADIO1_SCLKPIN	      PIN5                                      // RADIO1 clock source pin connection

#define __BOARD_RADIO1_MISOPORT_IN    P1IN                                      // RADIO1 SPI port IN
#define __BOARD_RADIO1_SPIPIN_DIR     P1DIR_6                                   // RADIO1 SPI (MISO) / GPIO (Green LED) direction
#define __BOARD_RADIO1_SPIPIN_SEL     P1SEL_6                                   // RADIO1 SPI (MISO) / GPIO (Green LED) select
#define __BOARD_RADIO1_SPIPIN_SEL2    P1SEL2_6                                  // RADIO1 SPI (MISO) / GPIO (Green LED) select 2
#endif  // __BOARD_AIRBOOSTERPACKLITE_SERIES

#endif	// __BOARD_LAUNCHPAD_H
