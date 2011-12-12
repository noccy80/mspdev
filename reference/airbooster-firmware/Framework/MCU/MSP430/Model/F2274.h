/**
 *  @file F2274.h
 *
 *  @brief MSP430F2274 model pin out and peripheral definitions.
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
#ifndef __MCU_MSP430_F2274_H
#define __MCU_MSP430_F2274_H

// MCU SPECIFIC PORT/PIN ADDRESSES
#ifdef __COMPILER_IARSYSTEMS
  #include <io430x22x4.h>
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

// PORT 3
// Input
#define P3IN                      P3IN
#define P3IN_0                    P3IN_bit.P3IN_0
#define P3IN_1                    P3IN_bit.P3IN_1
#define P3IN_2                    P3IN_bit.P3IN_2
#define P3IN_3                    P3IN_bit.P3IN_3
#define P3IN_4                    P3IN_bit.P3IN_4
#define P3IN_5                    P3IN_bit.P3IN_5
#define P3IN_6                    P3IN_bit.P3IN_6
#define P3IN_7                    P3IN_bit.P3IN_7
// Output
#define P3OUT                     P3OUT
#define P3OUT_0                   P3OUT_bit.P3OUT_0
#define P3OUT_1                   P3OUT_bit.P3OUT_1
#define P3OUT_2                   P3OUT_bit.P3OUT_2
#define P3OUT_3                   P3OUT_bit.P3OUT_3
#define P3OUT_4                   P3OUT_bit.P3OUT_4
#define P3OUT_5                   P3OUT_bit.P3OUT_5
#define P3OUT_6                   P3OUT_bit.P3OUT_6
#define P3OUT_7                   P3OUT_bit.P3OUT_7
// Direction
#define P3DIR                     P3DIR
// Interrupt Enable
#define P3IE                      P3IE
#define P3IE_0                    P3IE_bit.P3IE_0
#define P3IE_1                    P3IE_bit.P3IE_1
#define P3IE_2                    P3IE_bit.P3IE_2
#define P3IE_3                    P3IE_bit.P3IE_3
#define P3IE_4                    P3IE_bit.P3IE_4
#define P3IE_5                    P3IE_bit.P3IE_5
#define P3IE_6                    P3IE_bit.P3IE_6
#define P3IE_7                    P3IE_bit.P3IE_7
// Interrupt Edge Select
#define P3IES                     P3IES
#define P3IES_0                   P3IES_bit.P3IES_0
#define P3IES_1                   P3IES_bit.P3IES_1
#define P3IES_2                   P3IES_bit.P3IES_2
#define P3IES_3                   P3IES_bit.P3IES_3
#define P3IES_4                   P3IES_bit.P3IES_4
#define P3IES_5                   P3IES_bit.P3IES_5
#define P3IES_6                   P3IES_bit.P3IES_6
#define P3IES_7                   P3IES_bit.P3IES_7
// Interrupt Flag
#define P3IFG                     P3IFG
#define P3IFG_0                   P3IFG_bit.P3IFG_0
#define P3IFG_1                   P3IFG_bit.P3IFG_1
#define P3IFG_2                   P3IFG_bit.P3IFG_2
#define P3IFG_3                   P3IFG_bit.P3IFG_3
#define P3IFG_4                   P3IFG_bit.P3IFG_4
#define P3IFG_5                   P3IFG_bit.P3IFG_5
#define P3IFG_6                   P3IFG_bit.P3IFG_6
#define P3IFG_7                   P3IFG_bit.P3IFG_7
// Resistor Enable
#define P3REN                     P3REN
// Select
#define P3SEL                     P3SEL

// PERIPHERALS
#define __MCU_MSP430_CPUX
#define __MCU_MSP430_BASICCLOCKSYSTEMPLUS
#define __MCU_MSP430_ADC10
#define __MCU_MSP430_OA0
#define __MCU_MSP430_OA1
#define __MCU_MSP430_FLASH
#define __MCU_MSP430_DIGITALIO
#define __MCU_MSP430_DIGITALIO_PORT1
#define __MCU_MSP430_DIGITALIO_PORT2
#define __MCU_MSP430_DIGITALIO_PORT3
#define __MCU_MSP430_DIGITALIO_PORT4
#define __MCU_MSP430_WATCHDOGTIMERPLUS
#define __MCU_MSP430_TIMERA3
#define __MCU_MSP430_TIMERB3
#define __MCU_MSP430_USCI
#define __MCU_MSP430_USCIA0
#define __MCU_MSP430_USCIB0

#endif  // __MCU_MSP430_F2274_H
