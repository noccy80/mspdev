/**
 *  @file G2553.h
 *
 *  @brief MSP430G2553 model pin out and peripheral definitions.
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
#ifndef __MCU_MSP430_G2553_H
#define __MCU_MSP430_G2553_H

// MCU SPECIFIC PORT/PIN ADDRESSES
#ifdef __COMPILER_IARSYSTEMS
  #include <io430g2553.h>
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

#define USICOUNT                  0
#define USCICOUNT                 2
#define USARTCOUNT                0

// PORT 1 
// Input
#define P1IN                      P1IN
#define P1IN_0                    P1IN_bit.P1IN_0
#define P1IN_1                    P1IN_bit.P1IN_1
#define P1IN_2                    P1IN_bit.P1IN_2
#define P1IN_3                    P1IN_bit.P1IN_3
#define P1IN_4                    P1IN_bit.P1IN_4
#define P1IN_5                    P1IN_bit.P1IN_5
#define P1IN_6                    P1IN_bit.P1IN_6
#define P1IN_7                    P1IN_bit.P1IN_7
// Output
#define P1OUT                     P1OUT
#define P1OUT_0                   P1OUT_bit.P1OUT_0
#define P1OUT_1                   P1OUT_bit.P1OUT_1
#define P1OUT_2                   P1OUT_bit.P1OUT_2
#define P1OUT_3                   P1OUT_bit.P1OUT_3
#define P1OUT_4                   P1OUT_bit.P1OUT_4
#define P1OUT_5                   P1OUT_bit.P1OUT_5
#define P1OUT_6                   P1OUT_bit.P1OUT_6
#define P1OUT_7                   P1OUT_bit.P1OUT_7
// Direction
#define P1DIR                     P1DIR
#define P1DIR_0                   P1DIR_bit.P1DIR_0
#define P1DIR_1                   P1DIR_bit.P1DIR_1
#define P1DIR_2                   P1DIR_bit.P1DIR_2
#define P1DIR_3                   P1DIR_bit.P1DIR_3
#define P1DIR_4                   P1DIR_bit.P1DIR_4
#define P1DIR_5                   P1DIR_bit.P1DIR_5
#define P1DIR_6                   P1DIR_bit.P1DIR_6
#define P1DIR_7                   P1DIR_bit.P1DIR_7
// Interrupt Enable
#define P1IE                      P1IE
#define P1IE_0                    P1IE_bit.P1IE_0
#define P1IE_1                    P1IE_bit.P1IE_1
#define P1IE_2                    P1IE_bit.P1IE_2
#define P1IE_3                    P1IE_bit.P1IE_3
#define P1IE_4                    P1IE_bit.P1IE_4
#define P1IE_5                    P1IE_bit.P1IE_5
#define P1IE_6                    P1IE_bit.P1IE_6
#define P1IE_7                    P1IE_bit.P1IE_7
// Interrupt Edge Select
#define P1IES                     P1IES
#define P1IES_0                   P1IES_bit.P1IES_0
#define P1IES_1                   P1IES_bit.P1IES_1
#define P1IES_2                   P1IES_bit.P1IES_2
#define P1IES_3                   P1IES_bit.P1IES_3
#define P1IES_4                   P1IES_bit.P1IES_4
#define P1IES_5                   P1IES_bit.P1IES_5
#define P1IES_6                   P1IES_bit.P1IES_6
#define P1IES_7                   P1IES_bit.P1IES_7
// Interrupt Flag
#define P1IFG                     P1IFG
#define P1IFG_0                   P1IFG_bit.P1IFG_0
#define P1IFG_1                   P1IFG_bit.P1IFG_1
#define P1IFG_2                   P1IFG_bit.P1IFG_2
#define P1IFG_3                   P1IFG_bit.P1IFG_3
#define P1IFG_4                   P1IFG_bit.P1IFG_4
#define P1IFG_5                   P1IFG_bit.P1IFG_5
#define P1IFG_6                   P1IFG_bit.P1IFG_6
#define P1IFG_7                   P1IFG_bit.P1IFG_7
// Resistor Enable
#define P1REN                     P1REN
// Select
#define P1SEL                     P1SEL
#define P1SEL_0                   P1SEL_bit.P1SEL_0
#define P1SEL_1                   P1SEL_bit.P1SEL_1
#define P1SEL_2                   P1SEL_bit.P1SEL_2
#define P1SEL_3                   P1SEL_bit.P1SEL_3
#define P1SEL_4                   P1SEL_bit.P1SEL_4
#define P1SEL_5                   P1SEL_bit.P1SEL_5
#define P1SEL_6                   P1SEL_bit.P1SEL_6
#define P1SEL_7                   P1SEL_bit.P1SEL_7
// Select 2
#define P1SEL2                    P1SEL2
#define P1SEL2_0                  P1SEL2_bit.P1SEL2_0
#define P1SEL2_1                  P1SEL2_bit.P1SEL2_1
#define P1SEL2_2                  P1SEL2_bit.P1SEL2_2
#define P1SEL2_3                  P1SEL2_bit.P1SEL2_3
#define P1SEL2_4                  P1SEL2_bit.P1SEL2_4
#define P1SEL2_5                  P1SEL2_bit.P1SEL2_5
#define P1SEL2_6                  P1SEL2_bit.P1SEL2_6
#define P1SEL2_7                  P1SEL2_bit.P1SEL2_7

// PORT 2
// Input
#define P2IN                      P2IN
#define P2IN_0                    P2IN_bit.P2IN_0
#define P2IN_1                    P2IN_bit.P2IN_1
#define P2IN_2                    P2IN_bit.P2IN_2
#define P2IN_3                    P2IN_bit.P2IN_3
#define P2IN_4                    P2IN_bit.P2IN_4
#define P2IN_5                    P2IN_bit.P2IN_5
#define P2IN_6                    P2IN_bit.P2IN_6
#define P2IN_7                    P2IN_bit.P2IN_7
// Output
#define P2OUT                     P2OUT
#define P2OUT_0                   P2OUT_bit.P2OUT_0
#define P2OUT_1                   P2OUT_bit.P2OUT_1
#define P2OUT_2                   P2OUT_bit.P2OUT_2
#define P2OUT_3                   P2OUT_bit.P2OUT_3
#define P2OUT_4                   P2OUT_bit.P2OUT_4
#define P2OUT_5                   P2OUT_bit.P2OUT_5
#define P2OUT_6                   P2OUT_bit.P2OUT_6
#define P2OUT_7                   P2OUT_bit.P2OUT_7
// Direction
#define P2DIR                     P2DIR
// Interrupt Enable
#define P2IE                      P2IE
#define P2IE_0                    P2IE_bit.P2IE_0
#define P2IE_1                    P2IE_bit.P2IE_1
#define P2IE_2                    P2IE_bit.P2IE_2
#define P2IE_3                    P2IE_bit.P2IE_3
#define P2IE_4                    P2IE_bit.P2IE_4
#define P2IE_5                    P2IE_bit.P2IE_5
#define P2IE_6                    P2IE_bit.P2IE_6
#define P2IE_7                    P2IE_bit.P2IE_7
// Interrupt Edge Select
#define P2IES                     P2IES
#define P2IES_0                   P2IES_bit.P2IES_0
#define P2IES_1                   P2IES_bit.P2IES_1
#define P2IES_2                   P2IES_bit.P2IES_2
#define P2IES_3                   P2IES_bit.P2IES_3
#define P2IES_4                   P2IES_bit.P2IES_4
#define P2IES_5                   P2IES_bit.P2IES_5
#define P2IES_6                   P2IES_bit.P2IES_6
#define P2IES_7                   P2IES_bit.P2IES_7
// Interrupt Flag
#define P2IFG                     P2IFG
#define P2IFG_0                   P2IFG_bit.P2IFG_0
#define P2IFG_1                   P2IFG_bit.P2IFG_1
#define P2IFG_2                   P2IFG_bit.P2IFG_2
#define P2IFG_3                   P2IFG_bit.P2IFG_3
#define P2IFG_4                   P2IFG_bit.P2IFG_4
#define P2IFG_5                   P2IFG_bit.P2IFG_5
#define P2IFG_6                   P2IFG_bit.P2IFG_6
#define P2IFG_7                   P2IFG_bit.P2IFG_7
// Resistor Enable
#define P2REN                     P2REN
// Select
#define P2SEL                     P2SEL

// PERIPHERALS
#define __MCU_MSP430_CPUX
#define __MCU_MSP430_BASICCLOCKSYSTEMPLUS
#define __MCU_MSP430_ADC10
#define __MCU_MSP430_COMPAPLUS
#define __MCU_MSP430_FLASH
#define __MCU_MSP430_DIGITALIO
#define __MCU_MSP430_DIGITALIO_PORT1
#define __MCU_MSP430_DIGITALIO_PORT2
#define __MCU_MSP430_DIGITALIO_PORT3
#define __MCU_MSP430_WATCHDOGTIMERPLUS
#define __MCU_MSP430_TIMER0A3
#define __MCU_MSP430_TIMER1A3
#define __MCU_MSP430_USCI
#define __MCU_MSP430_USCIA0
#define __MCU_MSP430_USCIB0

#endif  // __MCU_MSP430_G2553_H