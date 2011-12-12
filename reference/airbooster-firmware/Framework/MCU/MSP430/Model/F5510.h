/**
 *  @file F5510.h
 *
 *  @brief MSP430F5510 model pin out and peripheral definitions.
 *
 *  @author   BB
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup [BB]
 */
#ifndef __MCU_MSP430_F5510_H
#define __MCU_MSP430_F5510_H

// MCU SPECIFIC PORT/PIN ADDRESSES
#ifdef __COMPILER_IARSYSTEMS
  #include <msp430f5510.h>
#else
  #define BIT0                    (0x0001u)
  #define BIT1                    (0x0002u)
  #define BIT2                    (0x0004u)
  #define BIT3                    (0x0008u)
  #define BIT4                    (0x0010u)
  #define BIT5                    (0x0020u)
  #define BIT6                    (0x0040u)
  #define BIT7                    (0x0080u)

  #define P1OUT                   (0x0202u)
  #define P2OUT                   (0x0203u)
  #define P3OUT                   (0x0222u)
  #define P4OUT                   (0x0223u)
  #define P5OUT                   (0x0242u)
  #define P6OUT                   (0x0243u)
  #define PJOUT                   (0x0322u)

  #define P1IN                    (0x0200u)
  #define P2IN                    (0x0201u)
  #define P3IN                    (0x0220u)
  #define P4IN                    (0x0221u)
  #define P5IN                    (0x0240u)
  #define P6IN                    (0x0241u)
  #define PJIN                    (0x0320u)

  #define UCA0TXIFG               (0x02)
  #define UCB0TXIFG               (0x08)
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

// PORTS
#define PORT1		          1
#define PORT2		          2
#define PORT3		          3
#define PORT4		          4
#define PORT5                     5
#define PORT6                     6
#define PORTJ                     'J'

#define USICOUNT                  0
#define USCICOUNT                 2
#define USCIA0                    0
#define USCIA0TXFLAG              UCA0TXIFG
#define USCIB0                    1
#define USCIB0TXFLAG              UCB0TXIFG
#define USCIA1                    2
#define USCIA1TXFLAG              UCA1TXIFG
#define USCIB1                    3
#define USCIB1TXFLAG              UCB1TXIFG
#define USARTCOUNT                0

// PERIPHERALS
#define __MCU_MSP430_SPECIALFUNCTIONREGISTER1
#define __MCU_MSP430_SPECIALFUNCTIONREGISTER2
#define __MCU_MSP430_UNIFIEDCLOCK
#define __MCU_MSP430_ADC10A
#define __MCU_MSP430_COMPB
#define __MCU_MSP430_CRC
#define __MCU_MSP430_DMAX
#define __MCU_MSP430_FLASH
#define __MCU_MSP430_MPY32
#define __MCU_MSP430_DIGITALIO
#define __MCU_MSP430_DIGITALIO_PORT1
#define __MCU_MSP430_DIGITALIO_PORT2
#define __MCU_MSP430_DIGITALIO_PORT3
#define __MCU_MSP430_DIGITALIO_PORT4
#define __MCU_MSP430_DIGITALIO_PORT5
#define __MCU_MSP430_DIGITALIO_PORT6
#define __MCU_MSP430_DIGITALIO_PORTJ
#define __MCU_MSP430_PMM
#define __MCU_MSP430_RTC
#define __MCU_MSP430_WATCHDOGPLUS
#define __MCU_MSP430_TIMER0A5
#define __MCU_MSP430_TIMER1A3
#define __MCU_MSP430_TIMER2A3
#define __MCU_MSP430_TIMER0B7
#define __MCU_MSP430_USCI
#define __MCU_MSP430_USCIA0
#define __MCU_MSP430_USCIA1
#define __MCU_MSP430_USCIB0
#define __MCU_MSP430_USCIB1
#define __MCU_MSP430_USB

#endif  // __MCU_MSP430_F5510_H