/**
 *  @file MSP430F2274Settings.h
 *
 *  @brief Settings file for the EZ430 board using an MSP430 microcontroller.
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
#ifndef __APP_MSP430F2274SETTINGS_H
#define __APP_MSP430F2274SETTINGS_H

// HAL FRAMEWORK SETTINGS
////////////////////////////////////////////////////////////////////////////////
// MSP430 INITIAL PROCESSOR SETTINGS
////////////////////////////////////////////////////////////////////////////////

// ANALOG SETTINGS

// ARCHITECTURE SETTINGS
// Clock System Registers
// Basic Clock
// Basic Clock System+
#define	__SET_MSP430_BASICCLOCKSYSTEMPLUS_DCOCTL	  CALDCO_8MHZ
#define __SET_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL1	  CALBC1_8MHZ
#define __SET_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL2	  DIVS_0
#define __SET_MSP430_BASICCLOCKSYSTEMPLUS_BCSCTL3	  LFXT1S_2
#define __SET_MSP430_BASICCLOCKSYSTEMPLUS_IE1_OFIE        0
#define __SET_MSP430_BASICCLOCKSYSTEMPLUS_IFG1_OFIFG      0
// FLL+
// Unified Clock System
#define __SET_MSP430_UNIFIEDCLOCK_UCSCTL0           0
#define __SET_MSP430_UNIFIEDCLOCK_UCSCTL1           0
#define __SET_MSP430_UNIFIEDCLOCK_UCSCTL2           0
#define __SET_MSP430_UNIFIEDCLOCK_UCSCTL3           0
#define __SET_MSP430_UNIFIEDCLOCK_UCSCTL4           0
#define __SET_MSP430_UNIFIEDCLOCK_UCSCTL5           0
#define __SET_MSP430_UNIFIEDCLOCK_UCSCTL6           0
#define __SET_MSP430_UNIFIEDCLOCK_UCSCTL7           0
#define __SET_MSP430_UNIFIEDCLOCK_UCSCTL8           0
// Clock System Macros
#define __MACRO_MSP430_BASICCLOCKPLUS_SETFREQUENCY  (0)
// Flash Registers
// Flash Macros

// COMMUNICATION SETTINGS
// USI General Settings
#define __SET_MSP430_USI_TXBUFSIZE                  1
#define __SET_MSP430_USI_RXBUFSIZE                  1
// USI Registers

// USCIA0 General Settings
#define __SET_MSP430_USCIA0_TXBUFSIZE               10
#define __SET_MSP430_USCIA0_RXBUFSIZE               10
// USCIA0 Registers
#define __SET_MSP430_USCIA0_UCA0CTL0		    0                           // USCI_A0 control register 0
#define __SET_MSP430_USCIA0_UCA0CTL1		    UCSSEL_2                    // USCI_A0 control register 1
#define __SET_MSP430_USCIA0_UCA0BR0		    0x41          
#define __SET_MSP430_USCIA0_UCA0BR1		    0x03
#define __SET_MSP430_USCIA0_UCA0MCTL		    UCBRS_2
#define __SET_MSP430_USCIA0_UCA0STAT		    0
#define __SET_MSP430_USCIA0_UCA0TXBUF		    0
#define __SET_MSP430_USCIA0_UCA0ABCTL		    0
#define __SET_MSP430_USCIA0_UCA0IRTCTL		    0
#define __SET_MSP430_USCIA0_UCA0IRRCTL		    0
#define __SET_MSP430_USCIA0_IE2_UCA0TXIE            0
#define __SET_MSP430_USCIA0_IFG2_UCA0TXIFG	    0
#define __SET_MSP430_USCIA0_IE2_UCA0RXIE            0
#define __SET_MSP430_USCIA0_IFG2_UCA0RXIFG	    0
// USCIA1 General Settings
#define __SET_MSP430_USCIA1_TXBUFSIZE               1
#define __SET_MSP430_USCIA1_RXBUFSIZE               1
// USCIA1 Registers
// USCIB0 General Settings
#define __SET_MSP430_USCIB0_TXBUFSIZE               50
#define __SET_MSP430_USCIB0_RXBUFSIZE               50
// USCIB0 Registers
#define __SET_MSP430_USCIB0_UCB0CTL0		    UCCKPH | UCMST | UCSYNC | UCMSB
#define __SET_MSP430_USCIB0_UCB0CTL1		    UCSSEL_2
#define __SET_MSP430_USCIB0_UCB0BR0		    0x01
#define __SET_MSP430_USCIB0_UCB0BR1		    0x00
#define __SET_MSP430_USCIB0_UCB0STAT		    0
#define __SET_MSP430_USCIB0_UCB0TXBUF		    0
#define __SET_MSP430_USCIB0_UCB0I2CIE		    0
#define __SET_MSP430_USCIB0_UCB0I2COA		    0
#define __SET_MSP430_USCIB0_UCB0I2CSA		    0
#define __SET_MSP430_USCIB0_IE2_UCB0TXIE	    0
#define __SET_MSP430_USCIB0_IFG2_UCB0TXIFG          0
#define __SET_MSP430_USCIB0_IE2_UCB0RXIE	    0
#define __SET_MSP430_USCIB0_IFG2_UCB0RXIFG          0
// USCIB1 General Settings
#define __SET_MSP430_USCIB1_TXBUFSIZE               1
#define __SET_MSP430_USCIB1_RXBUFSIZE               1
// USCIB1 Registers

// DATA CONVERTER SETTINGS
// ADC10 Registers
#define __SET_MSP430_ADC10_ADC10AE0		    0
#define __SET_MSP430_ADC10_ADC10AE1		    0
#define __SET_MSP430_ADC10_ADC10CTL0		    SREF_1 | ADC10SHT_3 | ADC10SR | REFBURST | REFON | ADC10ON | ADC10IE | ENC  //vref, 64xSH, <50ksps, ref out off, buff during SH only, SHI trig each, ref1.5V, ref on, ADC on, int on, conv on, S&C not started yet
#define __SET_MSP430_ADC10_ADC10CTL1		    INCH_10 | SHS_2 | ADC10DF | ADC10SSEL_1  // Temp sense, SHS=TA3.out0, 2's compl, /1, ACLK, single
#define __SET_MSP430_ADC10_ADC10MEM		    0
#define	__SET_MSP430_ADC10_ADC10DTC0		    0
#define	__SET_MSP430_ADC10_ADC10DTC1		    0
#define __SET_MSP430_ADC10_ADC10SA		    0

// GPIO SETTINGS
// Digital I/O 1 Registers
//#define __SET_MSP430_DIGITALIO1_P1IN		    0
#define __SET_MSP430_DIGITALIO1_P1OUT		    0x04
#define __SET_MSP430_DIGITALIO1_P1DIR		    0x03
#define __SET_MSP430_DIGITALIO1_P1IFG		    0
#define __SET_MSP430_DIGITALIO1_P1IES		    0x04
#define __SET_MSP430_DIGITALIO1_P1IE		    0x04
#define __SET_MSP430_DIGITALIO1_P1SEL		    0x00
#define __SET_MSP430_DIGITALIO1_P1REN		    0x04
// Digital I/O 2 Registers
//#define __SET_MSP430_DIGITALIO2_P2IN		    0
#define __SET_MSP430_DIGITALIO2_P2OUT		    0
#define __SET_MSP430_DIGITALIO2_P2DIR		    0x00
#define __SET_MSP430_DIGITALIO2_P2IFG		    0x00
#define __SET_MSP430_DIGITALIO2_P2IES		    0x00
#define __SET_MSP430_DIGITALIO2_P2IE		    0x00
#define __SET_MSP430_DIGITALIO2_P2SEL		    0x02
#define __SET_MSP430_DIGITALIO2_P2REN		    0
// Digital I/O 3 Registers
//#define __SET_MSP430_DIGITALIO3_P3IN		    0
#define __SET_MSP430_DIGITALIO3_P3OUT		    0x01
#define __SET_MSP430_DIGITALIO3_P3DIR		    0x1B
#define __SET_MSP430_DIGITALIO3_P3SEL		    0x7E
#define __SET_MSP430_DIGITALIO3_P3SEL2		    0
#define __SET_MSP430_DIGITALIO3_P3REN		    0
// Digital I/O 4 Registers
//#define __SET_MSP430_DIGITALIO4_P4IN		    0
#define __SET_MSP430_DIGITALIO4_P4OUT		    0x00
#define __SET_MSP430_DIGITALIO4_P4DIR		    0xFF
#define __SET_MSP430_DIGITALIO4_P4SEL		    0x00
#define __SET_MSP430_DIGITALIO4_P4SEL2		    0
#define __SET_MSP430_DIGITALIO4_P4REN		    0
// Digital I/O 5 Registers
#define __SET_MSP430_DIGITALIO5_P5OUT		    0
#define __SET_MSP430_DIGITALIO5_P5DIR		    0x02
#define __SET_MSP430_DIGITALIO5_P5SEL		    0
// Digital I/O 6 Registers
// Digital I/O 7 Registers
// Digital I/O 8 Registers
// Digital I/O 9 Registers
// Digital I/O 10 Registers
// Digital I/O J Registers

// LCD SETTINGS

// SPECIAL MODULE SETTINGS

// TIMER SETTINGS
// Timer_A Registers
#define __SET_MSP430_TIMERA_TACTL		    TASSEL_1 | TACLR
#define __SET_MSP430_TIMERA_TAR		            0
#define __SET_MSP430_TIMERA_TACCTL0		    OUTMOD_4 | CCIE
#define __SET_MSP430_TIMERA_TACCR0		    6000                        // TA3.out has twice the period and is used to start ADC sample(1 sec at 12kHz)
#define __SET_MSP430_TIMERA_TACCTL1		    0
#define __SET_MSP430_TIMERA_TACCR1		    0
#define __SET_MSP430_TIMERA_TACCTL2		    0
#define __SET_MSP430_TIMERA_TACCR2		    0
// Watchdog+ Registers
#define __SET_MSP430_WATCHDOGTIMERPLUS_WDTCTL	    WDTPW + WDTHOLD
#define __SET_MSP430_WATCHDOGTIMERPLUS_IE1_NMIIE    0
#define __SET_MSP430_WATCHDOGTIMERPLUS_IFG1_NMIIFG  0
#define __SET_MSP430_WATCHDOGTIMERPLUS_IE1_WDTIE    0
#define __SET_MSP430_WATCHDOGTIMERPLUS_IFG1_WDTIFG  0

#endif	// __APP_MSP430F2274SETTINGS_H
