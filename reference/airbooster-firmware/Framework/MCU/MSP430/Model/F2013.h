/**
 *  @file F2013.h
 *
 *  @brief MSP430F2013 model pin out and peripheral definitions.
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
#ifndef __MCU_MSP430_F2013_H
#define __MCU_MSP430_F2013_H

// MCU SPECIFIC PORT/PIN ADDRESSES
#ifdef __COMPILER_IARSYSTEMS
  #include <msp430f2013.h>
#else
  #error "__HAL_ERROR: Compiler currently not supported."
#endif

// PINS
#define PIN0		          BIT0
#define PIN1		          BIT1
#define PIN2		          BIT2
#define PIN3		          BIT3
#define PIN4		          BIT4
#define PIN5		          BIT5
#define PIN6		          BIT6
#define PIN7		          BIT7

// Communication
#define USICOUNT                  1
#define USCICOUNT                 0
#define USARTCOUNT                0

// PERIPHERALS
#define __MCU_MSP430_CPU                                                        // CPU
#define __MCU_MSP430_BASICCLOCKSYSTEMPLUS                                       // Basic Clock System+
#define __MCU_MSP430_SD16A                                                      // Sigma Delta A/D Converter
#define __MCU_MSP430_FLASH                                                      // Flash
#define __MCU_MSP430_DIGITALIO                                                  // Digital I/O
#define __MCU_MSP430_DIGITALIO_PORT1                                            // Port P1
#define __MCU_MSP430_DIGITALIO_PORT2                                            // Port P2
#define __MCU_MSP430_WATCHDOGTIMERPLUS                                          // Watchdog Timer+
#define __MCU_MSP430_TIMERA2                                                    // Timer_A2
#define __MCU_MSP430_USI                                                        // Universal Serial Interface (SPI, I2C)

#endif  // __MCU_MSP430_F2013_H