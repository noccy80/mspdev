/********************************************************************
*
* Standard register and bit definitions for the Texas Instruments
* MSP430 microcontroller.
*
* This file supports assembler and C development for
* MSP430x41x2 devices.
*
* Texas Instruments, Version 1.2
*
* Rev. 1.0, First Release
* Rev. 1.1, Fixed typo in ADC10: SREF3 -> SREF2
* Rev. 1.2, Corrected OSCCAP settings
*
********************************************************************/

#ifndef __msp430x41x2
#define __msp430x41x2

#define __MSP430_HEADER_VERSION__ 1059

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error msp430f4132.h file for use with ICC430/A430 only
#endif


#ifdef __IAR_SYSTEMS_ICC__
#include "in430.h"
#pragma language=extended

#define DEFC(name, address) __no_init volatile unsigned char name @ address;
#define DEFW(name, address) __no_init volatile unsigned short name @ address;
#define DEFXC  volatile unsigned char
#define DEFXW  volatile unsigned short

#endif  /* __IAR_SYSTEMS_ICC__  */


#ifdef __IAR_SYSTEMS_ASM__
#define DEFC(name, address) sfrb name = address;
#define DEFW(name, address) sfrw name = address;

#endif /* __IAR_SYSTEMS_ASM__*/

#ifdef __cplusplus
#define READ_ONLY
#else
#define READ_ONLY const
#endif

/************************************************************
* STANDARD BITS
************************************************************/

#define BIT0                (0x0001u)
#define BIT1                (0x0002u)
#define BIT2                (0x0004u)
#define BIT3                (0x0008u)
#define BIT4                (0x0010u)
#define BIT5                (0x0020u)
#define BIT6                (0x0040u)
#define BIT7                (0x0080u)
#define BIT8                (0x0100u)
#define BIT9                (0x0200u)
#define BITA                (0x0400u)
#define BITB                (0x0800u)
#define BITC                (0x1000u)
#define BITD                (0x2000u)
#define BITE                (0x4000u)
#define BITF                (0x8000u)

/************************************************************
* STATUS REGISTER BITS
************************************************************/

#define C                   (0x0001u)
#define Z                   (0x0002u)
#define N                   (0x0004u)
#define V                   (0x0100u)
#define GIE                 (0x0008u)
#define CPUOFF              (0x0010u)
#define OSCOFF              (0x0020u)
#define SCG0                (0x0040u)
#define SCG1                (0x0080u)

/* Low Power Modes coded with Bits 4-7 in SR */

#ifndef __IAR_SYSTEMS_ICC__ /* Begin #defines for assembler */
#define LPM0                (CPUOFF)
#define LPM1                (SCG0+CPUOFF)
#define LPM2                (SCG1+CPUOFF)
#define LPM3                (SCG1+SCG0+CPUOFF)
#define LPM4                (SCG1+SCG0+OSCOFF+CPUOFF)
/* End #defines for assembler */

#else /* Begin #defines for C */
#define LPM0_bits           (CPUOFF)
#define LPM1_bits           (SCG0+CPUOFF)
#define LPM2_bits           (SCG1+CPUOFF)
#define LPM3_bits           (SCG1+SCG0+CPUOFF)
#define LPM4_bits           (SCG1+SCG0+OSCOFF+CPUOFF)

#include "in430.h"

#define LPM0      _BIS_SR(LPM0_bits)     /* Enter Low Power Mode 0 */
#define LPM0_EXIT _BIC_SR_IRQ(LPM0_bits) /* Exit Low Power Mode 0 */
#define LPM1      _BIS_SR(LPM1_bits)     /* Enter Low Power Mode 1 */
#define LPM1_EXIT _BIC_SR_IRQ(LPM1_bits) /* Exit Low Power Mode 1 */
#define LPM2      _BIS_SR(LPM2_bits)     /* Enter Low Power Mode 2 */
#define LPM2_EXIT _BIC_SR_IRQ(LPM2_bits) /* Exit Low Power Mode 2 */
#define LPM3      _BIS_SR(LPM3_bits)     /* Enter Low Power Mode 3 */
#define LPM3_EXIT _BIC_SR_IRQ(LPM3_bits) /* Exit Low Power Mode 3 */
#define LPM4      _BIS_SR(LPM4_bits)     /* Enter Low Power Mode 4 */
#define LPM4_EXIT _BIC_SR_IRQ(LPM4_bits) /* Exit Low Power Mode 4 */
#endif /* End #defines for C */

/************************************************************
* PERIPHERAL FILE MAP
************************************************************/

/************************************************************
* SPECIAL FUNCTION REGISTER ADDRESSES + CONTROL BITS
************************************************************/

#define IE1_                (0x0000u)  /* Interrupt Enable 1 */
DEFC(   IE1               , IE1_)
#define WDTIE               (0x01)    /* Watchdog Interrupt Enable */
#define OFIE                (0x02)    /* Osc. Fault  Interrupt Enable */
#define NMIIE               (0x10)    /* NMI Interrupt Enable */
#define ACCVIE              (0x20)    /* Flash Access Violation Interrupt Enable */

#define IFG1_               (0x0002u)  /* Interrupt Flag 1 */
DEFC(   IFG1              , IFG1_)
#define WDTIFG              (0x01)    /* Watchdog Interrupt Flag */
#define OFIFG               (0x02)    /* Osc. Fault Interrupt Flag */
#define PORIFG              (0x04)    /* Power On Interrupt Flag */
#define RSTIFG              (0x08)    /* Reset Interrupt Flag */
#define NMIIFG              (0x10)    /* NMI Interrupt Flag */

#define IE2_                (0x0001u)  /* Interrupt Enable 2 */
DEFC(   IE2               , IE2_)
#define UC0IE               IE2
#define UCA0RXIE            (0x01)
#define UCA0TXIE            (0x02)
#define UCB0RXIE            (0x04)
#define UCB0TXIE            (0x08)
#define BTIE                (0x80)

#define IFG2_               (0x0003u)  /* Interrupt Flag 2 */
DEFC(   IFG2              , IFG2_)
#define UC0IFG              IFG2
#define UCA0RXIFG           (0x01)
#define UCA0TXIFG           (0x02)
#define UCB0RXIFG           (0x04)
#define UCB0TXIFG           (0x08)
#define BTIFG               (0x80)

/************************************************************
* ADC10
************************************************************/
#define __MSP430_HAS_ADC10__            /* Definition to show that Module is available */

#define ADC10DTC0_          (0x0048u)    /* ADC10 Data Transfer Control 0 */
DEFC(   ADC10DTC0         , ADC10DTC0_)
#define ADC10DTC1_          (0x0049u)    /* ADC10 Data Transfer Control 1 */
DEFC(   ADC10DTC1         , ADC10DTC1_)
#define ADC10AE0_           (0x004Au)    /* ADC10 Analog Enable 0 */
DEFC(   ADC10AE0          , ADC10AE0_)
#define ADC10AE1_           (0x004Bu)    /* ADC10 Analog Enable 1 */
DEFC(   ADC10AE1          , ADC10AE1_)

#define ADC10CTL0_          (0x01B0u)    /* ADC10 Control 0 */
DEFW(   ADC10CTL0         , ADC10CTL0_)
#define ADC10CTL1_          (0x01B2u)    /* ADC10 Control 1 */
DEFW(   ADC10CTL1         , ADC10CTL1_)
#define ADC10MEM_           (0x01B4u)    /* ADC10 Memory */
DEFW(   ADC10MEM          , ADC10MEM_)
#define ADC10SA_            (0x01BCu)    /* ADC10 Data Transfer Start Address */
DEFW(   ADC10SA           , ADC10SA_)

/* ADC10CTL0 */
#define ADC10SC             (0x001)     /* ADC10 Start Conversion */
#define ENC                 (0x002)     /* ADC10 Enable Conversion */
#define ADC10IFG            (0x004)     /* ADC10 Interrupt Flag */
#define ADC10IE             (0x008)     /* ADC10 Interrupt Enalbe */
#define ADC10ON             (0x010)     /* ADC10 On/Enable */
#define REFON               (0x020)     /* ADC10 Reference on */
#define REF2_5V             (0x040)     /* ADC10 Ref 0:1.5V / 1:2.5V */
#define MSC                 (0x080)     /* ADC10 Multiple SampleConversion */
#define REFBURST            (0x100)     /* ADC10 Reference Burst Mode */
#define REFOUT              (0x200)     /* ADC10 Enalbe output of Ref. */
#define ADC10SR             (0x400)     /* ADC10 Sampling Rate 0:200ksps / 1:50ksps */
#define ADC10SHT0           (0x800)     /* ADC10 Sample Hold Select Bit: 0 */
#define ADC10SHT1           (0x1000u)    /* ADC10 Sample Hold Select Bit: 1 */
#define SREF0               (0x2000u)    /* ADC10 Reference Select Bit: 0 */
#define SREF1               (0x4000u)    /* ADC10 Reference Select Bit: 1 */
#define SREF2               (0x8000u)    /* ADC10 Reference Select Bit: 2 */
#define ADC10SHT_0          (0*0x800u)   /* 4 x ADC10CLKs */
#define ADC10SHT_1          (1*0x800u)   /* 8 x ADC10CLKs */
#define ADC10SHT_2          (2*0x800u)   /* 16 x ADC10CLKs */
#define ADC10SHT_3          (3*0x800u)   /* 64 x ADC10CLKs */

#define SREF_0              (0*0x2000u)  /* VR+ = AVCC and VR- = AVSS */
#define SREF_1              (1*0x2000u)  /* VR+ = VREF+ and VR- = AVSS */
#define SREF_2              (2*0x2000u)  /* VR+ = VEREF+ and VR- = AVSS */
#define SREF_3              (3*0x2000u)  /* VR+ = VEREF+ and VR- = AVSS */
#define SREF_4              (4*0x2000u)  /* VR+ = AVCC and VR- = VREF-/VEREF- */
#define SREF_5              (5*0x2000u)  /* VR+ = VREF+ and VR- = VREF-/VEREF- */
#define SREF_6              (6*0x2000u)  /* VR+ = VEREF+ and VR- = VREF-/VEREF- */
#define SREF_7              (7*0x2000u)  /* VR+ = VEREF+ and VR- = VREF-/VEREF- */

/* ADC10CTL1 */
#define ADC10BUSY           (0x0001u)    /* ADC10 BUSY */
#define CONSEQ0             (0x0002u)    /* ADC10 Conversion Sequence Select 0 */
#define CONSEQ1             (0x0004u)    /* ADC10 Conversion Sequence Select 1 */
#define ADC10SSEL0          (0x0008u)    /* ADC10 Clock Source Select Bit: 0 */
#define ADC10SSEL1          (0x0010u)    /* ADC10 Clock Source Select Bit: 1 */
#define ADC10DIV0           (0x0020u)    /* ADC10 Clock Divider Select Bit: 0 */
#define ADC10DIV1           (0x0040u)    /* ADC10 Clock Divider Select Bit: 1 */
#define ADC10DIV2           (0x0080u)    /* ADC10 Clock Divider Select Bit: 2 */
#define ISSH                (0x0100u)    /* ADC10 Invert Sample Hold Signal */
#define ADC10DF             (0x0200u)    /* ADC10 Data Format 0:binary 1:2's complement */
#define SHS0                (0x0400u)    /* ADC10 Sample/Hold Source Bit: 0 */
#define SHS1                (0x0800u)    /* ADC10 Sample/Hold Source Bit: 1 */
#define INCH0               (0x1000u)    /* ADC10 Input Channel Select Bit: 0 */
#define INCH1               (0x2000u)    /* ADC10 Input Channel Select Bit: 1 */
#define INCH2               (0x4000u)    /* ADC10 Input Channel Select Bit: 2 */
#define INCH3               (0x8000u)    /* ADC10 Input Channel Select Bit: 3 */

#define CONSEQ_0            (0*2u)       /* Single channel single conversion */
#define CONSEQ_1            (1*2u)       /* Sequence of channels */
#define CONSEQ_2            (2*2u)       /* Repeat single channel */
#define CONSEQ_3            (3*2u)       /* Repeat sequence of channels */

#define ADC10SSEL_0         (0*8u)       /* ADC10OSC */
#define ADC10SSEL_1         (1*8u)       /* ACLK */
#define ADC10SSEL_2         (2*8u)       /* MCLK */
#define ADC10SSEL_3         (3*8u)       /* SMCLK */

#define ADC10DIV_0          (0*0x20u)    /* ADC10 Clock Divider Select 0 */
#define ADC10DIV_1          (1*0x20u)    /* ADC10 Clock Divider Select 1 */
#define ADC10DIV_2          (2*0x20u)    /* ADC10 Clock Divider Select 2 */
#define ADC10DIV_3          (3*0x20u)    /* ADC10 Clock Divider Select 3 */
#define ADC10DIV_4          (4*0x20u)    /* ADC10 Clock Divider Select 4 */
#define ADC10DIV_5          (5*0x20u)    /* ADC10 Clock Divider Select 5 */
#define ADC10DIV_6          (6*0x20u)    /* ADC10 Clock Divider Select 6 */
#define ADC10DIV_7          (7*0x20u)    /* ADC10 Clock Divider Select 7 */

#define SHS_0               (0*0x400u)   /* ADC10SC */
#define SHS_1               (1*0x400u)   /* Ext. SC Trigger 1 */
#define SHS_2               (2*0x400u)   /* Ext. SC Trigger 2 */
#define SHS_3               (3*0x400u)   /* Ext. SC Trigger 3 */

#define INCH_0              (0*0x1000u)  /* Selects Channel 0 */
#define INCH_1              (1*0x1000u)  /* Selects Channel 1 */
#define INCH_2              (2*0x1000u)  /* Selects Channel 2 */
#define INCH_3              (3*0x1000u)  /* Selects Channel 3 */
#define INCH_4              (4*0x1000u)  /* Selects Channel 4 */
#define INCH_5              (5*0x1000u)  /* Selects Channel 5 */
#define INCH_6              (6*0x1000u)  /* Selects Channel 6 */
#define INCH_7              (7*0x1000u)  /* Selects Channel 7 */
#define INCH_8              (8*0x1000u)  /* Selects Channel 8 */
#define INCH_9              (9*0x1000u)  /* Selects Channel 9 */
#define INCH_10             (10*0x1000u) /* Selects Channel 10 */
#define INCH_11             (11*0x1000u) /* Selects Channel 11 */
#define INCH_12             (12*0x1000u) /* Selects Channel 12 */
#define INCH_13             (13*0x1000u) /* Selects Channel 13 */
#define INCH_14             (14*0x1000u) /* Selects Channel 14 */
#define INCH_15             (15*0x1000u) /* Selects Channel 15 */

/* ADC10DTC0 */
#define ADC10FETCH          (0x001)     /* This bit should normally be reset */
#define ADC10B1             (0x002)     /* ADC10 block one */
#define ADC10CT             (0x004)     /* ADC10 continuous transfer */
#define ADC10TB             (0x008)     /* ADC10 two-block mode */
#define ADC10DISABLE        (0x000)     /* ADC10DTC1 */

/************************************************************
* BASIC TIMER with Real Time Clock
************************************************************/
#define __MSP430_HAS_BT_RTC__          /* Definition to show that Module is available */

#define BTCTL_              (0x0040)  /* Basic Timer Control */
#ifndef __IAR_SYSTEMS_ICC__
DEFC(   BTCTL             , BTCTL_)
#endif
#define RTCCTL_             (0x0041)  /* Real Time Clock Control */
#ifndef __IAR_SYSTEMS_ICC__
DEFC(   RTCCTL            , RTCCTL_)
#endif
#define RTCNT1_             (0x0042)  /* Real Time Counter 1 */
#ifndef __IAR_SYSTEMS_ICC__
DEFC(   RTCNT1            , RTCNT1_)
#endif
#define RTCNT2_             (0x0043)  /* Real Time Counter 2 */
#ifndef __IAR_SYSTEMS_ICC__
DEFC(   RTCNT2            , RTCNT2_)
#endif
#define RTCNT3_             (0x0044)  /* Real Time Counter 3 */
#ifndef __IAR_SYSTEMS_ICC__
DEFC(   RTCNT3            , RTCNT3_)
#endif
#define RTCNT4_             (0x0045)  /* Real Time Counter 4 */
#ifndef __IAR_SYSTEMS_ICC__
DEFC(   RTCNT4            , RTCNT4_)
#endif
#define BTCNT1_             (0x0046)  /* Basic Timer Count 1 */
#ifndef __IAR_SYSTEMS_ICC__
DEFC(   BTCNT1            , BTCNT1_)
#endif
#define BTCNT2_             (0x0047)  /* Basic Timer Count 2 */
#ifndef __IAR_SYSTEMS_ICC__
DEFC(   BTCNT2            , BTCNT2_)
#endif
#define RTCDAY_             (0x004C)  /* Real Time Clock Day */
#ifndef __IAR_SYSTEMS_ICC__
DEFC(   RTCDAY            , RTCDAY_)
#endif
#define RTCMON_             (0x004D)  /* Real Time Clock Month */
#ifndef __IAR_SYSTEMS_ICC__
DEFC(   RTCMON            , RTCMON_)
#endif
#define RTCYEARL_           (0x004E)  /* Real Time Clock Year (Low Byte) */
#ifndef __IAR_SYSTEMS_ICC__
DEFC(   RTCYEARL          , RTCYEARL_)
#endif
#define RTCYEARH_           (0x004F)  /* Real Time Clock Year (High Byte) */
#ifndef __IAR_SYSTEMS_ICC__
DEFC(   RTCYEARH          , RTCYEARH_)
#endif
#define RTCSEC              RTCNT1
#define RTCMIN              RTCNT2
#define RTCHOUR             RTCNT3
#define RTCDOW              RTCNT4

#define RTCTL_              (0x0040)  /* Basic/Real Timer Control */
#ifndef __IAR_SYSTEMS_ICC__
DEFW(   RTCTL             , RTCTL_)
#endif

#ifdef __IAR_SYSTEMS_ICC__
__no_init union
{
  struct
  {
    DEFXC                             BTCTL;
    DEFXC                             RTCCTL;
  };
  DEFXW                               RTCTL;
} @ 0x0040;
#endif
#define RTCTIM0_            (0x0042)  /* Real Time Clock Time 0 */
#ifndef __IAR_SYSTEMS_ICC__
DEFW(   RTCTIM0           , RTCTIM0_)
#endif

#ifdef __IAR_SYSTEMS_ICC__
__no_init union
{
  struct
  {
    DEFXC                             RTCNT1;
    DEFXC                             RTCNT2;
  };
  DEFXW                               RTCTIM0;
} @ 0x0042;
#endif
#define RTCTIM1_            (0x0044)  /* Real Time Clock Time 1 */
#ifndef __IAR_SYSTEMS_ICC__
DEFW(   RTCTIM1           , RTCTIM1_)
#endif

#ifdef __IAR_SYSTEMS_ICC__
__no_init union
{
  struct
  {
    DEFXC                             RTCNT3;
    DEFXC                             RTCNT4;
  };
  DEFXW                               RTCTIM1;
} @ 0x0044;
#endif
#define BTCNT12_            (0x0046)  /* Basic Timer Count 1/2 */
#ifndef __IAR_SYSTEMS_ICC__
DEFW(   BTCNT12           , BTCNT12_)
#endif

#ifdef __IAR_SYSTEMS_ICC__
__no_init union
{
  struct
  {
    DEFXC                             BTCNT1;
    DEFXC                             BTCNT2;
  };
  DEFXW                               BTCNT12;
} @ 0x0046;
#endif
#define RTCDATE_            (0x004C)  /* Real Time Clock Date */
#ifndef __IAR_SYSTEMS_ICC__
DEFW(   RTCDATE           , RTCDATE_)
#endif

#ifdef __IAR_SYSTEMS_ICC__
__no_init union
{
  struct
  {
    DEFXC                             RTCDAY;
    DEFXC                             RTCMON;
  };
  DEFXW                               RTCDATE;
} @ 0x004C;
#endif
#define RTCYEAR_            (0x004E)  /* Real Time Clock Year */
#ifndef __IAR_SYSTEMS_ICC__
DEFW(   RTCYEAR           , RTCYEAR_)
#endif

#ifdef __IAR_SYSTEMS_ICC__
__no_init union
{
  struct
  {
    DEFXC                             RTCYEARL;
    DEFXC                             RTCYEARH;
  };
  DEFXW                               RTCYEAR;
} @ 0x004E;
#endif
#define RTCNT12             RTCTIM0
#define RTCNT34             RTCTIM1

#define BTSSEL              (0x80)                     /* fBT = fMCLK (main clock) */
#define BTHOLD              (0x40)                     /* BT1 is held if this bit is set */
#define BTDIV               (0x20)                     /* fCLK2 = ACLK:256 */
//#define res               (0x10)
//#define res               (0x08)
#define BTIP2               (0x04)
#define BTIP1               (0x02)
#define BTIP0               (0x01)

#define RTCBCD              (0x80)                     /* RTC BCD Select */
#define RTCHOLD             (0x40)                     /* RTC Hold */
#define RTCMODE1            (0x20)                     /* RTC Mode 1 */
#define RTCMODE0            (0x10)                     /* RTC Mode 0 */
#define RTCTEV1             (0x08)                     /* RTC Time Event 1 */
#define RTCTEV0             (0x04)                     /* RTC Time Event 0 */
#define RTCIE               (0x02)                     /* RTC Interrupt Enable */
#define RTCFG               (0x01)                     /* RTC Event Flag */

#define RTCTEV_0            (0x00)                     /* RTC Time Event: 0 */
#define RTCTEV_1            (0x04)                     /* RTC Time Event: 1 */
#define RTCTEV_2            (0x08)                     /* RTC Time Event: 2 */
#define RTCTEV_3            (0x0C)                     /* RTC Time Event: 3 */
#define RTCMODE_0           (0x00)                     /* RTC Mode: 0 */
#define RTCMODE_1           (0x10)                     /* RTC Mode: 1 */
#define RTCMODE_2           (0x20)                     /* RTC Mode: 2 */
#define RTCMODE_3           (0x30)                     /* RTC Mode: 3 */

/* Frequency of the BTCNT2 coded with Bit 5 and 7 in BTCTL */
#define BT_fCLK2_ACLK               (0x00)
#define BT_fCLK2_ACLK_DIV256        (BTDIV)
#define BT_fCLK2_MCLK               (BTSSEL)

/* Interrupt interval time fINT coded with Bits 0-2 in BTCTL */
#define BT_fCLK2_DIV2       (0x00)                    /* fINT = fCLK2:2 (default) */
#define BT_fCLK2_DIV4       (BTIP0)                   /* fINT = fCLK2:4 */
#define BT_fCLK2_DIV8       (BTIP1)                   /* fINT = fCLK2:8 */
#define BT_fCLK2_DIV16      (BTIP1+BTIP0)             /* fINT = fCLK2:16 */
#define BT_fCLK2_DIV32      (BTIP2)                   /* fINT = fCLK2:32 */
#define BT_fCLK2_DIV64      (BTIP2+BTIP0)             /* fINT = fCLK2:64 */
#define BT_fCLK2_DIV128     (BTIP2+BTIP1)             /* fINT = fCLK2:128 */
#define BT_fCLK2_DIV256     (BTIP2+BTIP1+BTIP0)       /* fINT = fCLK2:256 */

/* with assumed vlues of fACLK=32KHz, fMCLK=1MHz */
/* fBT=fACLK is thought for longer interval times */
#define BT_ADLY_0_064       (0x00)                    /* 0.064ms interval (default) */
#define BT_ADLY_0_125       (BTIP0)                   /* 0.125ms    " */
#define BT_ADLY_0_25        (BTIP1)                   /* 0.25ms     " */
#define BT_ADLY_0_5         (BTIP1+BTIP0)             /* 0.5ms      " */
#define BT_ADLY_1           (BTIP2)                   /* 1ms        " */
#define BT_ADLY_2           (BTIP2+BTIP0)             /* 2ms        " */
#define BT_ADLY_4           (BTIP2+BTIP1)             /* 4ms        " */
#define BT_ADLY_8           (BTIP2+BTIP1+BTIP0)       /* 8ms        " */
#define BT_ADLY_16          (BTDIV)                   /* 16ms       " */
#define BT_ADLY_32          (BTDIV+BTIP0)             /* 32ms       " */
#define BT_ADLY_64          (BTDIV+BTIP1)             /* 64ms       " */
#define BT_ADLY_125         (BTDIV+BTIP1+BTIP0)       /* 125ms      " */
#define BT_ADLY_250         (BTDIV+BTIP2)             /* 250ms      " */
#define BT_ADLY_500         (BTDIV+BTIP2+BTIP0)       /* 500ms      " */
#define BT_ADLY_1000        (BTDIV+BTIP2+BTIP1)       /* 1000ms     " */
#define BT_ADLY_2000        (BTDIV+BTIP2+BTIP1+BTIP0) /* 2000ms     " */
/* fCLK2=fMCLK (1MHz) is thought for short interval times */
/* the timing for short intervals is more precise than ACLK */
/* NOTE */
/* Be sure that the SCFQCTL-Register is set to 01Fh so that fMCLK=1MHz */
/* Too low interval time results in interrupts too frequent for the processor to handle! */
#define BT_MDLY_0_002       (BTSSEL)                  /* 0.002ms interval       *** interval times */
#define BT_MDLY_0_004       (BTSSEL+BTIP0)            /* 0.004ms    "           *** too short for */
#define BT_MDLY_0_008       (BTSSEL+BTIP1)            /* 0.008ms    "           *** interrupt */
#define BT_MDLY_0_016       (BTSSEL+BTIP1+BTIP0)      /* 0.016ms    "           *** handling */
#define BT_MDLY_0_032       (BTSSEL+BTIP2)            /* 0.032ms    " */
#define BT_MDLY_0_064       (BTSSEL+BTIP2+BTIP0)      /* 0.064ms    " */
#define BT_MDLY_0_125       (BTSSEL+BTIP2+BTIP1)      /* 0.125ms    " */
#define BT_MDLY_0_25        (BTSSEL+BTIP2+BTIP1+BTIP0)/* 0.25ms     " */

/* Hold coded with Bits 6-7 in BT(1)CTL */
/* this is for BT */
#define BTHOLD_CNT1         (BTHOLD)            /* BTCNT1 is held while BTHOLD is set */
#define BTHOLD_CNT1_2       (BTHOLD+BTDIV)      /* BT1CNT1 .AND. BT1CNT2 are held while ~ is set */

/* INTERRUPT CONTROL BITS */
/* #define BTIE                0x80 */
/* #define BTIFG               0x80 */

/************************************************************
* Comparator A
************************************************************/
#define __MSP430_HAS_CAPLUS__         /* Definition to show that Module is available */

#define CACTL1_             (0x0059u)  /* Comparator A Control 1 */
DEFC(   CACTL1            , CACTL1_)
#define CACTL2_             (0x005Au)  /* Comparator A Control 2 */
DEFC(   CACTL2            , CACTL2_)
#define CAPD_               (0x005Bu)  /* Comparator A Port Disable */
DEFC(   CAPD              , CAPD_)

#define CAIFG               (0x01)    /* Comp. A Interrupt Flag */
#define CAIE                (0x02)    /* Comp. A Interrupt Enable */
#define CAIES               (0x04)    /* Comp. A Int. Edge Select: 0:rising / 1:falling */
#define CAON                (0x08)    /* Comp. A enable */
#define CAREF0              (0x10)    /* Comp. A Internal Reference Select 0 */
#define CAREF1              (0x20)    /* Comp. A Internal Reference Select 1 */
#define CARSEL              (0x40)    /* Comp. A Internal Reference Enable */
#define CAEX                (0x80)    /* Comp. A Exchange Inputs */

#define CAREF_0             (0x00)    /* Comp. A Int. Ref. Select 0 : Off */
#define CAREF_1             (0x10)    /* Comp. A Int. Ref. Select 1 : 0.25*Vcc */
#define CAREF_2             (0x20)    /* Comp. A Int. Ref. Select 2 : 0.5*Vcc */
#define CAREF_3             (0x30)    /* Comp. A Int. Ref. Select 3 : Vt*/

#define CAOUT               (0x01)    /* Comp. A Output */
#define CAF                 (0x02)    /* Comp. A Enable Output Filter */
#define P2CA0               (0x04)    /* Comp. A +Terminal Multiplexer */
#define P2CA1               (0x08)    /* Comp. A -Terminal Multiplexer */
#define P2CA2               (0x10)    /* Comp. A -Terminal Multiplexer */
#define P2CA3               (0x20)    /* Comp. A -Terminal Multiplexer */
#define P2CA4               (0x40)    /* Comp. A +Terminal Multiplexer */
#define CASHORT             (0x80)    /* Comp. A Short + and - Terminals */

#define CAPD0               (0x01)    /* Comp. A Disable Input Buffer of Port Register .0 */
#define CAPD1               (0x02)    /* Comp. A Disable Input Buffer of Port Register .1 */
#define CAPD2               (0x04)    /* Comp. A Disable Input Buffer of Port Register .2 */
#define CAPD3               (0x08)    /* Comp. A Disable Input Buffer of Port Register .3 */
#define CAPD4               (0x10)    /* Comp. A Disable Input Buffer of Port Register .4 */
#define CAPD5               (0x20)    /* Comp. A Disable Input Buffer of Port Register .5 */
#define CAPD6               (0x40)    /* Comp. A Disable Input Buffer of Port Register .6 */
#define CAPD7               (0x80)    /* Comp. A Disable Input Buffer of Port Register .7 */

/*************************************************************
* Flash Memory
*************************************************************/
#define __MSP430_HAS_FLASH2__         /* Definition to show that Module is available */

#define FCTL1_              (0x0128u)  /* FLASH Control 1 */
DEFW(   FCTL1             , FCTL1_)
#define FCTL2_              (0x012Au)  /* FLASH Control 2 */
DEFW(   FCTL2             , FCTL2_)
#define FCTL3_              (0x012Cu)  /* FLASH Control 3 */
DEFW(   FCTL3             , FCTL3_)

#define FRKEY               (0x9600u)  /* Flash key returned by read */
#define FWKEY               (0xA500u)  /* Flash key for write */
#define FXKEY               (0x3300u)  /* for use with XOR instruction */

#define ERASE               (0x0002u)  /* Enable bit for Flash segment erase */
#define MERAS               (0x0004u)  /* Enable bit for Flash mass erase */
#define EEI                 (0x0008u)  /* Enable Erase Interrupts */
#define EEIEX               (0x0010u)  /* Enable Emergency Interrupt Exit */
#define WRT                 (0x0040u)  /* Enable bit for Flash write */
#define BLKWRT              (0x0080u)  /* Enable bit for Flash segment write */
#define SEGWRT              (0x0080u)  /* old definition */ /* Enable bit for Flash segment write */

#define FN0                 (0x0001u)  /* Divide Flash clock by 1 to 64 using FN0 to FN5 according to: */
#define FN1                 (0x0002u)  /*  32*FN5 + 16*FN4 + 8*FN3 + 4*FN2 + 2*FN1 + FN0 + 1 */
#ifndef FN2
#define FN2                 (0x0004u)
#endif
#ifndef FN3
#define FN3                 (0x0008u)
#endif
#ifndef FN4
#define FN4                 (0x0010u)
#endif
#define FN5                 (0x0020u)
#define FSSEL0              (0x0040u)  /* Flash clock select 0 */        /* to distinguish from USART SSELx */
#define FSSEL1              (0x0080u)  /* Flash clock select 1 */

#define FSSEL_0             (0x0000u)  /* Flash clock select: 0 - ACLK */
#define FSSEL_1             (0x0040u)  /* Flash clock select: 1 - MCLK */
#define FSSEL_2             (0x0080u)  /* Flash clock select: 2 - SMCLK */
#define FSSEL_3             (0x00C0u)  /* Flash clock select: 3 - SMCLK */

#define BUSY                (0x0001u)  /* Flash busy: 1 */
#define KEYV                (0x0002u)  /* Flash Key violation flag */
#define ACCVIFG             (0x0004u)  /* Flash Access violation flag */
#define WAIT                (0x0008u)  /* Wait flag for segment write */
#define LOCK                (0x0010u)  /* Lock bit: 1 - Flash is locked (read only) */
#define EMEX                (0x0020u)  /* Flash Emergency Exit */
#define LOCKA               (0x0040u)  /* Segment A Lock bit: read = 1 - Segment is locked (read only) */
#define FAIL                (0x0080u)  /* Last Program or Erase failed */

/************************************************************
* SYSTEM CLOCK, FLL+
************************************************************/
#define __MSP430_HAS_FLLPLUS__        /* Definition to show that Module is available */

#define SCFI0_              (0x0050u)  /* System Clock Frequency Integrator 0 */
DEFC(   SCFI0             , SCFI0_)
#define FN_2                (0x04)    /* fDCOCLK =   1.4-12MHz*/
#define FN_3                (0x08)    /* fDCOCLK =   2.2-17Mhz*/
#define FN_4                (0x10)    /* fDCOCLK =   3.2-25Mhz*/
#define FN_8                (0x20)    /* fDCOCLK =     5-40Mhz*/
#define FLLD0               (0x40)    /* Loop Divider Bit : 0 */
#define FLLD1               (0x80)    /* Loop Divider Bit : 1 */

#define FLLD_1              (0x00)    /* Multiply Selected Loop Freq. By 1 */
#define FLLD_2              (0x40)    /* Multiply Selected Loop Freq. By 2 */
#define FLLD_4              (0x80)    /* Multiply Selected Loop Freq. By 4 */
#define FLLD_8              (0xC0)    /* Multiply Selected Loop Freq. By 8 */

#define SCFI1_              (0x0051u)  /* System Clock Frequency Integrator 1 */
DEFC(   SCFI1             , SCFI1_)
#define SCFQCTL_            (0x0052u)  /* System Clock Frequency Control */
DEFC(   SCFQCTL           , SCFQCTL_)
/* System clock frequency values fMCLK coded with Bits 0-6 in SCFQCTL */
/* #define SCFQ_32K            0x00                        fMCLK=1*fACLK       only a range from */
#define SCFQ_64K            (0x01)                     /* fMCLK=2*fACLK          1+1 to 127+1 is possible */
#define SCFQ_128K           (0x03)                     /* fMCLK=4*fACLK */
#define SCFQ_256K           (0x07)                     /* fMCLK=8*fACLK */
#define SCFQ_512K           (0x0F)                     /* fMCLK=16*fACLK */
#define SCFQ_1M             (0x1F)                     /* fMCLK=32*fACLK */
#define SCFQ_2M             (0x3F)                     /* fMCLK=64*fACLK */
#define SCFQ_4M             (0x7F)                     /* fMCLK=128*fACLK */
#define SCFQ_M              (0x80)                     /* Modulation Disable */

#define FLL_CTL0_           (0x0053u)  /* FLL+ Control 0 */
DEFC(   FLL_CTL0          , FLL_CTL0_)
#define DCOF                (0x01)                     /* DCO Fault Flag */
#define LFOF                (0x02)                     /* Low Frequency Oscillator Fault Flag */
#define XT1OF               (0x04)                     /* High Frequency Oscillator 1 Fault Flag */
#define OSCCAP0             (0x10)                     /* XIN/XOUT Cap 0 */
#define OSCCAP1             (0x20)                     /* XIN/XOUT Cap 1 */
#define XTS_FLL             (0x40)                     /* 1: Selects high-freq. oscillator */
#define DCOPLUS             (0x80)                     /* DCO+ Enable */

#define XCAP0PF             (0x00)                     /* XIN Cap = XOUT Cap = 0pf */
#define XCAP5_5F            (0x10)                     /* XIN Cap = XOUT Cap = 5.5pf */
#define XCAP8_5PF           (0x20)                     /* XIN Cap = XOUT Cap = 8.5pf */
#define XCAP11PF            (0x30)                     /* XIN Cap = XOUT Cap = 11pf */
#define OSCCAP_0            (0x00)                     /* XIN Cap = XOUT Cap: 0 */
#define OSCCAP_1            (0x10)                     /* XIN Cap = XOUT Cap: 1 */
#define OSCCAP_2            (0x20)                     /* XIN Cap = XOUT Cap: 2 */
#define OSCCAP_3            (0x30)                     /* XIN Cap = XOUT Cap: 3 */

#define FLL_CTL1_           (0x0054u)  /* FLL+ Control 1 */
DEFC(   FLL_CTL1          , FLL_CTL1_)
#define FLL_DIV0            (0x01)                     /* FLL+ Divide Px.x/ACLK 0 */
#define FLL_DIV1            (0x02)                     /* FLL+ Divide Px.x/ACLK 1 */
#define SELM0               (0x08)                     /* MCLK Source Select 0 */
#define SELM1               (0x10)                     /* MCLK Source Select 1 */
#define SMCLKOFF            (0x40)                     /* Peripheral Module Clock (SMCLK) disable */

#define FLL_DIV_1           (0x00)                     /* FLL+ Divide Px.x/ACLK By 1 */
#define FLL_DIV_2           (0x01)                     /* FLL+ Divide Px.x/ACLK By 2 */
#define FLL_DIV_4           (0x02)                     /* FLL+ Divide Px.x/ACLK By 4 */
#define FLL_DIV_8           (0x03)                     /* FLL+ Divide Px.x/ACLK By 8 */

#define SELM_DCO            (0x00)                     /* Select DCO for CPU MCLK */
#define SELM_A              (0x18)                     /* Select A (from LFXT1) for CPU MCLK */

#define FLL_CTL2_           (0x0055u)  /* FLL+ Control 2 */
DEFC(   FLL_CTL2          , FLL_CTL2_)

#define LF1XT1S0            (0x10)   /* Mode 0 for LFXT1 */
#define LF1XT1S1            (0x20)   /* Mode 0 for LFXT1 */

#define LF1XT1S_0           (0x00)   /* Mode 0 for LF : 32kHz */
#define LF1XT1S_1           (0x10)   /* Mode 1 for LF : reserved */
#define LF1XT1S_2           (0x20)   /* Mode 2 for LF : VLO */
#define LF1XT1S_3           (0x30)   /* Mode 3 for LF : Digital input signal */

/* INTERRUPT CONTROL BITS */
/* These two bits are defined in the Special Function Registers */
/* #define OFIFG               0x02 */
/* #define OFIE                0x02 */

/************************************************************
* LCD_A
************************************************************/
#define __MSP430_HAS_LCD_A__          /* Definition to show that Module is available */

#define LCDACTL_            (0x0090u)  /* LCD_A Control Register */
DEFC(   LCDACTL           , LCDACTL_)
#define LCDON               (0x01)
#define LCDSON              (0x04)
#define LCDMX0              (0x08)
#define LCDMX1              (0x10)
#define LCDFREQ0            (0x20)
#define LCDFREQ1            (0x40)
#define LCDFREQ2            (0x80)
/* Display modes coded with Bits 2-4 */
#define LCDSTATIC           (LCDSON)
#define LCD2MUX             (LCDMX0+LCDSON)
#define LCD3MUX             (LCDMX1+LCDSON)
#define LCD4MUX             (LCDMX1+LCDMX0+LCDSON)
/* Frequency select code with Bits 5-7 */
#define LCDFREQ_32          (0x00)    /* LCD Freq: ACLK divided by 32 */
#define LCDFREQ_64          (0x20)    /* LCD Freq: ACLK divided by 64 */
#define LCDFREQ_96          (0x40)    /* LCD Freq: ACLK divided by 96 */
#define LCDFREQ_128         (0x60)    /* LCD Freq: ACLK divided by 128 */
#define LCDFREQ_192         (0x80)    /* LCD Freq: ACLK divided by 192 */
#define LCDFREQ_256         (0xA0)    /* LCD Freq: ACLK divided by 256 */
#define LCDFREQ_384         (0xC0)    /* LCD Freq: ACLK divided by 384 */
#define LCDFREQ_512         (0xE0)    /* LCD Freq: ACLK divided by 512 */

#define LCDAPCTL0_          (0x00ACu)  /* LCD_A Port Control Register 0 */
DEFC(   LCDAPCTL0         , LCDAPCTL0_)
#define LCDS0               (0x01)    /* LCD Segment  0 to  3 Enable. */
#define LCDS4               (0x02)    /* LCD Segment  4 to  7 Enable. */
#define LCDS8               (0x04)    /* LCD Segment  8 to 11 Enable. */
#define LCDS12              (0x08)    /* LCD Segment 12 to 15 Enable. */
#define LCDS16              (0x10)    /* LCD Segment 16 to 19 Enable. */
#define LCDS20              (0x20)    /* LCD Segment 20 to 23 Enable. */
#define LCDS24              (0x40)    /* LCD Segment 24 to 27 Enable. */
#define LCDS28              (0x80)    /* LCD Segment 28 to 31 Enable. */

#define LCDAPCTL1_          (0x00ADu)  /* LCD_A Port Control Register 1 */
DEFC(   LCDAPCTL1         , LCDAPCTL1_)
#define LCDS32              (0x01)    /* LCD Segment 32 to 35 Enable. */
#define LCDS36              (0x02)    /* LCD Segment 36 to 39 Enable. */

#define LCDAVCTL0_          (0x00AEu)  /* LCD_A Voltage Control Register 0 */
DEFC(   LCDAVCTL0         , LCDAVCTL0_)
#define LCD2B               (0x01)    /* Selects 1/2 bias. */
#define VLCDREF0            (0x02)    /* Selects reference voltage for regulated charge pump: 0 */
#define VLCDREF1            (0x04)    /* Selects reference voltage for regulated charge pump: 1 */
#define LCDCPEN             (0x08)    /* LCD Voltage Charge Pump Enable. */
#define VLCDEXT             (0x10)    /* Select external source for VLCD. */
#define LCDREXT             (0x20)    /* Selects external connections for LCD mid voltages. */
#define LCDR03EXT           (0x40)    /* Selects external connection for lowest LCD voltage. */

/* Reference voltage source select for the regulated charge pump */
#define VLCDREF_0           (0<<1)    /* Internal */
#define VLCDREF_1           (1<<1)    /* External */
#define VLCDREF_2           (2<<1)    /* Reserved */
#define VLCDREF_3           (3<<1)    /* Reserved */

#define LCDAVCTL1_          (0x00AFu)  /* LCD_A Voltage Control Register 1 */
DEFC(   LCDAVCTL1         , LCDAVCTL1_)
#define VLCD0               (0x02)    /* VLCD select: 0 */
#define VLCD1               (0x04)    /* VLCD select: 1 */
#define VLCD2               (0x08)    /* VLCD select: 2 */
#define VLCD3               (0x10)    /* VLCD select: 3 */

/* Charge pump voltage selections */
#define VLCD_0              (0<<1)    /* Charge pump disabled */
#define VLCD_1              (1<<1)    /* VLCD = 2.60V */
#define VLCD_2              (2<<1)    /* VLCD = 2.66V */
#define VLCD_3              (3<<1)    /* VLCD = 2.72V */
#define VLCD_4              (4<<1)    /* VLCD = 2.78V */
#define VLCD_5              (5<<1)    /* VLCD = 2.84V */
#define VLCD_6              (6<<1)    /* VLCD = 2.90V */
#define VLCD_7              (7<<1)    /* VLCD = 2.96V */
#define VLCD_8              (8<<1)    /* VLCD = 3.02V */
#define VLCD_9              (9<<1)    /* VLCD = 3.08V */
#define VLCD_10             (10<<1)   /* VLCD = 3.14V */
#define VLCD_11             (11<<1)   /* VLCD = 3.20V */
#define VLCD_12             (12<<1)   /* VLCD = 3.26V */
#define VLCD_13             (12<<1)   /* VLCD = 3.32V */
#define VLCD_14             (13<<1)   /* VLCD = 3.38V */
#define VLCD_15             (15<<1)   /* VLCD = 3.44V */

#define VLCD_DISABLED       (0<<1)    /* Charge pump disabled */
#define VLCD_2_60           (1<<1)    /* VLCD = 2.60V */
#define VLCD_2_66           (2<<1)    /* VLCD = 2.66V */
#define VLCD_2_72           (3<<1)    /* VLCD = 2.72V */
#define VLCD_2_78           (4<<1)    /* VLCD = 2.78V */
#define VLCD_2_84           (5<<1)    /* VLCD = 2.84V */
#define VLCD_2_90           (6<<1)    /* VLCD = 2.90V */
#define VLCD_2_96           (7<<1)    /* VLCD = 2.96V */
#define VLCD_3_02           (8<<1)    /* VLCD = 3.02V */
#define VLCD_3_08           (9<<1)    /* VLCD = 3.08V */
#define VLCD_3_14           (10<<1)   /* VLCD = 3.14V */
#define VLCD_3_20           (11<<1)   /* VLCD = 3.20V */
#define VLCD_3_26           (12<<1)   /* VLCD = 3.26V */
#define VLCD_3_32           (12<<1)   /* VLCD = 3.32V */
#define VLCD_3_38           (13<<1)   /* VLCD = 3.38V */
#define VLCD_3_44           (15<<1)   /* VLCD = 3.44V */

#define LCDMEM_             (0x0091u)  /* LCD Memory */
#ifndef __IAR_SYSTEMS_ICC__
#define LCDMEM              (LCDMEM_) /* LCD Memory (for assembler) */
#else
#define LCDMEM              ((char*) LCDMEM_) /* LCD Memory (for C) */
#endif
#define LCDM1_              (0x0091u)  /* LCD Memory 1 */
DEFC(   LCDM1             , LCDM1_)
#define LCDM2_              (0x0092u)  /* LCD Memory 2 */
DEFC(   LCDM2             , LCDM2_)
#define LCDM3_              (0x0093u)  /* LCD Memory 3 */
DEFC(   LCDM3             , LCDM3_)
#define LCDM4_              (0x0094u)  /* LCD Memory 4 */
DEFC(   LCDM4             , LCDM4_)
#define LCDM5_              (0x0095u)  /* LCD Memory 5 */
DEFC(   LCDM5             , LCDM5_)
#define LCDM6_              (0x0096u)  /* LCD Memory 6 */
DEFC(   LCDM6             , LCDM6_)
#define LCDM7_              (0x0097u)  /* LCD Memory 7 */
DEFC(   LCDM7             , LCDM7_)
#define LCDM8_              (0x0098u)  /* LCD Memory 8 */
DEFC(   LCDM8             , LCDM8_)
#define LCDM9_              (0x0099u)  /* LCD Memory 9 */
DEFC(   LCDM9             , LCDM9_)
#define LCDM10_             (0x009Au)  /* LCD Memory 10 */
DEFC(   LCDM10            , LCDM10_)
#define LCDM11_             (0x009Bu)  /* LCD Memory 11 */
DEFC(   LCDM11            , LCDM11_)
#define LCDM12_             (0x009Cu)  /* LCD Memory 12 */
DEFC(   LCDM12            , LCDM12_)
#define LCDM13_             (0x009Du)  /* LCD Memory 13 */
DEFC(   LCDM13            , LCDM13_)
#define LCDM14_             (0x009Eu)  /* LCD Memory 14 */
DEFC(   LCDM14            , LCDM14_)
#define LCDM15_             (0x009Fu)  /* LCD Memory 15 */
DEFC(   LCDM15            , LCDM15_)
#define LCDM16_             (0x00A0u)  /* LCD Memory 16 */
DEFC(   LCDM16            , LCDM16_)
#define LCDM17_             (0x00A1u)  /* LCD Memory 17 */
DEFC(   LCDM17            , LCDM17_)
#define LCDM18_             (0x00A2u)  /* LCD Memory 18 */
DEFC(   LCDM18            , LCDM18_)
#define LCDM19_             (0x00A3u)  /* LCD Memory 19 */
DEFC(   LCDM19            , LCDM19_)
#define LCDM20_             (0x00A4u)  /* LCD Memory 20 */
DEFC(   LCDM20            , LCDM20_)

#define LCDMA               (LCDM10)  /* LCD Memory A */
#define LCDMB               (LCDM11)  /* LCD Memory B */
#define LCDMC               (LCDM12)  /* LCD Memory C */
#define LCDMD               (LCDM13)  /* LCD Memory D */
#define LCDME               (LCDM14)  /* LCD Memory E */
#define LCDMF               (LCDM15)  /* LCD Memory F */

/************************************************************
* DIGITAL I/O Port1/2
************************************************************/
#define __MSP430_HAS_PORT1__          /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2__          /* Definition to show that Module is available */

#define P1IN_               (0x0020u)  /* Port 1 Input */
READ_ONLY DEFC( P1IN           , P1IN_)
#define P1OUT_              (0x0021u)  /* Port 1 Output */
DEFC(   P1OUT             , P1OUT_)
#define P1DIR_              (0x0022u)  /* Port 1 Direction */
DEFC(   P1DIR             , P1DIR_)
#define P1IFG_              (0x0023u)  /* Port 1 Interrupt Flag */
DEFC(   P1IFG             , P1IFG_)
#define P1IES_              (0x0024u)  /* Port 1 Interrupt Edge Select */
DEFC(   P1IES             , P1IES_)
#define P1IE_               (0x0025u)  /* Port 1 Interrupt Enable */
DEFC(   P1IE              , P1IE_)
#define P1SEL_              (0x0026u)  /* Port 1 Selection */
DEFC(   P1SEL             , P1SEL_)

#define P2IN_               (0x0028u)  /* Port 2 Input */
READ_ONLY DEFC( P2IN           , P2IN_)
#define P2OUT_              (0x0029u)  /* Port 2 Output */
DEFC(   P2OUT             , P2OUT_)
#define P2DIR_              (0x002Au)  /* Port 2 Direction */
DEFC(   P2DIR             , P2DIR_)
#define P2IFG_              (0x002Bu)  /* Port 2 Interrupt Flag */
DEFC(   P2IFG             , P2IFG_)
#define P2IES_              (0x002Cu)  /* Port 2 Interrupt Edge Select */
DEFC(   P2IES             , P2IES_)
#define P2IE_               (0x002Du)  /* Port 2 Interrupt Enable */
DEFC(   P2IE              , P2IE_)
#define P2SEL_              (0x002Eu)  /* Port 2 Selection */
DEFC(   P2SEL             , P2SEL_)

/************************************************************
* DIGITAL I/O Port3/4
************************************************************/
#define __MSP430_HAS_PORT3__          /* Definition to show that Module is available */
#define __MSP430_HAS_PORT4__          /* Definition to show that Module is available */

#define P3IN_               (0x0018u)  /* Port 3 Input */
READ_ONLY DEFC( P3IN           , P3IN_)
#define P3OUT_              (0x0019u)  /* Port 3 Output */
DEFC(   P3OUT             , P3OUT_)
#define P3DIR_              (0x001Au)  /* Port 3 Direction */
DEFC(   P3DIR             , P3DIR_)
#define P3SEL_              (0x001Bu)  /* Port 3 Selection */
DEFC(   P3SEL             , P3SEL_)

#define P4IN_               (0x001Cu)  /* Port 4 Input */
READ_ONLY DEFC( P4IN           , P4IN_)
#define P4OUT_              (0x001Du)  /* Port 4 Output */
DEFC(   P4OUT             , P4OUT_)
#define P4DIR_              (0x001Eu)  /* Port 4 Direction */
DEFC(   P4DIR             , P4DIR_)
#define P4SEL_              (0x001Fu)  /* Port 4 Selection */
DEFC(   P4SEL             , P4SEL_)

/************************************************************
* DIGITAL I/O Port5/6
************************************************************/
#define __MSP430_HAS_PORT5__          /* Definition to show that Module is available */
#define __MSP430_HAS_PORT6__          /* Definition to show that Module is available */

#define P5IN_               (0x0030u)  /* Port 5 Input */
READ_ONLY DEFC( P5IN           , P5IN_)
#define P5OUT_              (0x0031u)  /* Port 5 Output */
DEFC(   P5OUT             , P5OUT_)
#define P5DIR_              (0x0032u)  /* Port 5 Direction */
DEFC(   P5DIR             , P5DIR_)
#define P5SEL_              (0x0033u)  /* Port 5 Selection */
DEFC(   P5SEL             , P5SEL_)

#define P6IN_               (0x0034u)  /* Port 6 Input */
READ_ONLY DEFC( P6IN           , P6IN_)
#define P6OUT_              (0x0035u)  /* Port 6 Output */
DEFC(   P6OUT             , P6OUT_)
#define P6DIR_              (0x0036u)  /* Port 6 Direction */
DEFC(   P6DIR             , P6DIR_)
#define P6SEL_              (0x0037u)  /* Port 6 Selection */
DEFC(   P6SEL             , P6SEL_)

/************************************************************
* DIGITAL I/O Port7
************************************************************/
#define __MSP430_HAS_PORT7__          /* Definition to show that Module is available */

#define P7IN_               (0x0038u)  /* Port 7 Input */
READ_ONLY DEFC( P7IN           , P7IN_)
#define P7OUT_              (0x0039u)  /* Port 7 Output */
DEFC(   P7OUT             , P7OUT_)
#define P7DIR_              (0x003Au)  /* Port 7 Direction */
DEFC(   P7DIR             , P7DIR_)
#define P7SEL_              (0x003Bu)  /* Port 7 Selection */
DEFC(   P7SEL             , P7SEL_)

/************************************************************
* Brown-Out, Supply Voltage Supervision (SVS)
************************************************************/
#define __MSP430_HAS_SVS__            /* Definition to show that Module is available */

#define SVSCTL_             (0x0056u)  /* SVS Control */
DEFC(   SVSCTL            , SVSCTL_)
#define SVSFG               (0x01)    /* SVS Flag */
#define SVSOP               (0x02)    /* SVS output (read only) */
#define SVSON               (0x04)    /* Switches the SVS on/off */
#define PORON               (0x08)    /* Enable POR Generation if Low Voltage */
#define VLD0                (0x10)
#define VLD1                (0x20)
#define VLD2                (0x40)
#define VLD3                (0x80)

#define VLDON               (0x10)
#define VLDOFF              (0x00)
#define VLD_1_8V            (0x10)

/************************************************************
* Timer0_A3
************************************************************/
#define __MSP430_HAS_TA3__            /* Definition to show that Module is available */

#define TA0IV_              (0x012Eu)  /* Timer0_A3 Interrupt Vector Word */
READ_ONLY DEFW( TA0IV          , TA0IV_)
#define TA0CTL_             (0x0160u)  /* Timer0_A3 Control */
DEFW(   TA0CTL            , TA0CTL_)
#define TA0CCTL0_           (0x0162u)  /* Timer0_A3 Capture/Compare Control 0 */
DEFW(   TA0CCTL0          , TA0CCTL0_)
#define TA0CCTL1_           (0x0164u)  /* Timer0_A3 Capture/Compare Control 1 */
DEFW(   TA0CCTL1          , TA0CCTL1_)
#define TA0CCTL2_           (0x0166u)  /* Timer0_A3 Capture/Compare Control 2 */
DEFW(   TA0CCTL2          , TA0CCTL2_)
#define TA0R_               (0x0170u)  /* Timer0_A3 */
DEFW(   TA0R              , TA0R_)
#define TA0CCR0_            (0x0172u)  /* Timer0_A3 Capture/Compare 0 */
DEFW(   TA0CCR0           , TA0CCR0_)
#define TA0CCR1_            (0x0174u)  /* Timer0_A3 Capture/Compare 1 */
DEFW(   TA0CCR1           , TA0CCR1_)
#define TA0CCR2_            (0x0176u)  /* Timer0_A3 Capture/Compare 2 */
DEFW(   TA0CCR2           , TA0CCR2_)

/* Alternate register names */
#define TAIV                TA0IV     /* Timer A Interrupt Vector Word */
#define TACTL               TA0CTL    /* Timer A Control */
#define TACCTL0             TA0CCTL0  /* Timer A Capture/Compare Control 0 */
#define TACCTL1             TA0CCTL1  /* Timer A Capture/Compare Control 1 */
#define TACCTL2             TA0CCTL2  /* Timer A Capture/Compare Control 2 */
#define TAR                 TA0R      /* Timer A */
#define TACCR0              TA0CCR0   /* Timer A Capture/Compare 0 */
#define TACCR1              TA0CCR1   /* Timer A Capture/Compare 1 */
#define TACCR2              TA0CCR2   /* Timer A Capture/Compare 2 */
#define TAIV_               TA0IV_    /* Timer A Interrupt Vector Word */
#define TACTL_              TA0CTL_   /* Timer A Control */
#define TACCTL0_            TA0CCTL0_ /* Timer A Capture/Compare Control 0 */
#define TACCTL1_            TA0CCTL1_ /* Timer A Capture/Compare Control 1 */
#define TACCTL2_            TA0CCTL2_ /* Timer A Capture/Compare Control 2 */
#define TAR_                TA0R_     /* Timer A */
#define TACCR0_             TA0CCR0_  /* Timer A Capture/Compare 0 */
#define TACCR1_             TA0CCR1_  /* Timer A Capture/Compare 1 */
#define TACCR2_             TA0CCR2_  /* Timer A Capture/Compare 2 */

/* Alternate register names 2 */
#define CCTL0               TACCTL0   /* Timer A Capture/Compare Control 0 */
#define CCTL1               TACCTL1   /* Timer A Capture/Compare Control 1 */
#define CCTL2               TACCTL2   /* Timer A Capture/Compare Control 2 */
#define CCR0                TACCR0    /* Timer A Capture/Compare 0 */
#define CCR1                TACCR1    /* Timer A Capture/Compare 1 */
#define CCR2                TACCR2    /* Timer A Capture/Compare 2 */
#define CCTL0_              TACCTL0_  /* Timer A Capture/Compare Control 0 */
#define CCTL1_              TACCTL1_  /* Timer A Capture/Compare Control 1 */
#define CCTL2_              TACCTL2_  /* Timer A Capture/Compare Control 2 */
#define CCR0_               TACCR0_   /* Timer A Capture/Compare 0 */
#define CCR1_               TACCR1_   /* Timer A Capture/Compare 1 */
#define CCR2_               TACCR2_   /* Timer A Capture/Compare 2 */

#define TASSEL1             (0x0200u)  /* Timer A clock source select 1 */
#define TASSEL0             (0x0100u)  /* Timer A clock source select 0 */
#define ID1                 (0x0080u)  /* Timer A clock input divider 1 */
#define ID0                 (0x0040u)  /* Timer A clock input divider 0 */
#define MC1                 (0x0020u)  /* Timer A mode control 1 */
#define MC0                 (0x0010u)  /* Timer A mode control 0 */
#define TACLR               (0x0004u)  /* Timer A counter clear */
#define TAIE                (0x0002u)  /* Timer A counter interrupt enable */
#define TAIFG               (0x0001u)  /* Timer A counter interrupt flag */

#define MC_0                (0*0x10u)  /* Timer A mode control: 0 - Stop */
#define MC_1                (1*0x10u)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC_2                (2*0x10u)  /* Timer A mode control: 2 - Continous up */
#define MC_3                (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
#define ID_0                (0*0x40u)  /* Timer A input divider: 0 - /1 */
#define ID_1                (1*0x40u)  /* Timer A input divider: 1 - /2 */
#define ID_2                (2*0x40u)  /* Timer A input divider: 2 - /4 */
#define ID_3                (3*0x40u)  /* Timer A input divider: 3 - /8 */
#define TASSEL_0            (0*0x100u) /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1            (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2            (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3            (3*0x100u) /* Timer A clock source select: 3 - INCLK */

#define CM1                 (0x8000u)  /* Capture mode 1 */
#define CM0                 (0x4000u)  /* Capture mode 0 */
#define CCIS1               (0x2000u)  /* Capture input select 1 */
#define CCIS0               (0x1000u)  /* Capture input select 0 */
#define SCS                 (0x0800u)  /* Capture sychronize */
#define SCCI                (0x0400u)  /* Latched capture signal (read) */
#define CAP                 (0x0100u)  /* Capture mode: 1 /Compare mode : 0 */
#define OUTMOD2             (0x0080u)  /* Output mode 2 */
#define OUTMOD1             (0x0040u)  /* Output mode 1 */
#define OUTMOD0             (0x0020u)  /* Output mode 0 */
#define CCIE                (0x0010u)  /* Capture/compare interrupt enable */
#define CCI                 (0x0008u)  /* Capture input signal (read) */
#define OUT                 (0x0004u)  /* PWM Output signal if output mode 0 */
#define COV                 (0x0002u)  /* Capture/compare overflow flag */
#define CCIFG               (0x0001u)  /* Capture/compare interrupt flag */

#define OUTMOD_0            (0*0x20u)  /* PWM output mode: 0 - output only */
#define OUTMOD_1            (1*0x20u)  /* PWM output mode: 1 - set */
#define OUTMOD_2            (2*0x20u)  /* PWM output mode: 2 - PWM toggle/reset */
#define OUTMOD_3            (3*0x20u)  /* PWM output mode: 3 - PWM set/reset */
#define OUTMOD_4            (4*0x20u)  /* PWM output mode: 4 - toggle */
#define OUTMOD_5            (5*0x20u)  /* PWM output mode: 5 - Reset */
#define OUTMOD_6            (6*0x20u)  /* PWM output mode: 6 - PWM toggle/set */
#define OUTMOD_7            (7*0x20u)  /* PWM output mode: 7 - PWM reset/set */
#define CCIS_0              (0*0x1000u) /* Capture input select: 0 - CCIxA */
#define CCIS_1              (1*0x1000u) /* Capture input select: 1 - CCIxB */
#define CCIS_2              (2*0x1000u) /* Capture input select: 2 - GND */
#define CCIS_3              (3*0x1000u) /* Capture input select: 3 - Vcc */
#define CM_0                (0*0x4000u) /* Capture mode: 0 - disabled */
#define CM_1                (1*0x4000u) /* Capture mode: 1 - pos. edge */
#define CM_2                (2*0x4000u) /* Capture mode: 1 - neg. edge */
#define CM_3                (3*0x4000u) /* Capture mode: 1 - both edges */

/* T0_A3IV Definitions */
#define TA0IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA0IV_TACCR1        (0x0002u)    /* TA0CCR1_CCIFG */
#define TA0IV_TACCR2        (0x0004u)    /* TA0CCR2_CCIFG */
#define TA0IV_6             (0x0006u)    /* Reserved */
#define TA0IV_8             (0x0008u)    /* Reserved */
#define TA0IV_TAIFG         (0x000Au)    /* TA0IFG */

/************************************************************
* Timer1_A5
************************************************************/
#define __MSP430_HAS_T1A5__           /* Definition to show that Module is available */

#define TA1IV_              (0x011Eu)  /* Timer1_A5 Interrupt Vector Word */
READ_ONLY DEFW( TA1IV          , TA1IV_)
#define TA1CTL_             (0x0180u)  /* Timer1_A5 Control */
DEFW(   TA1CTL            , TA1CTL_)
#define TA1CCTL0_           (0x0182u)  /* Timer1_A5 Capture/Compare Control 0 */
DEFW(   TA1CCTL0          , TA1CCTL0_)
#define TA1CCTL1_           (0x0184u)  /* Timer1_A5 Capture/Compare Control 1 */
DEFW(   TA1CCTL1          , TA1CCTL1_)
#define TA1CCTL2_           (0x0186u)  /* Timer1_A5 Capture/Compare Control 2 */
DEFW(   TA1CCTL2          , TA1CCTL2_)
#define TA1CCTL3_           (0x0188u)  /* Timer1_A5 Capture/Compare Control 3 */
DEFW(   TA1CCTL3          , TA1CCTL3_)
#define TA1CCTL4_           (0x018Au)  /* Timer1_A5 Capture/Compare Control 4 */
DEFW(   TA1CCTL4          , TA1CCTL4_)
#define TA1R_               (0x0190u)  /* Timer1_A5 */
DEFW(   TA1R              , TA1R_)
#define TA1CCR0_            (0x0192u)  /* Timer1_A5 Capture/Compare 0 */
DEFW(   TA1CCR0           , TA1CCR0_)
#define TA1CCR1_            (0x0194u)  /* Timer1_A5 Capture/Compare 1 */
DEFW(   TA1CCR1           , TA1CCR1_)
#define TA1CCR2_            (0x0196u)  /* Timer1_A5 Capture/Compare 2 */
DEFW(   TA1CCR2           , TA1CCR2_)
#define TA1CCR3_            (0x0198u)  /* Timer1_A5 Capture/Compare 3 */
DEFW(   TA1CCR3           , TA1CCR3_)
#define TA1CCR4_            (0x019Au)  /* Timer1_A5 Capture/Compare 4 */
DEFW(   TA1CCR4           , TA1CCR4_)

/* Bits are already defined within the Timer0_Ax */

/* T1_A5IV Definitions */
#define TA1IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA1IV_TACCR1        (0x0002u)    /* TA1CCR1_CCIFG */
#define TA1IV_TACCR2        (0x0004u)    /* TA1CCR2_CCIFG */
#define TA1IV_TACCR3        (0x0006u)    /* TA1CCR3_CCIFG */
#define TA1IV_TACCR4        (0x0008u)    /* TA1CCR4_CCIFG */
#define TA1IV_TAIFG         (0x000Au)    /* TA1IFG */

/************************************************************
* USCI
************************************************************/
#define __MSP430_HAS_USCI__           /* Definition to show that Module is available */

#define UCA0CTL0_           (0x0060u)  /* USCI A0 Control Register 0 */
DEFC(   UCA0CTL0          , UCA0CTL0_)
#define UCA0CTL1_           (0x0061u)  /* USCI A0 Control Register 1 */
DEFC(   UCA0CTL1          , UCA0CTL1_)
#define UCA0BR0_            (0x0062u)  /* USCI A0 Baud Rate 0 */
DEFC(   UCA0BR0           , UCA0BR0_)
#define UCA0BR1_            (0x0063u)  /* USCI A0 Baud Rate 1 */
DEFC(   UCA0BR1           , UCA0BR1_)
#define UCA0MCTL_           (0x0064u)  /* USCI A0 Modulation Control */
DEFC(   UCA0MCTL          , UCA0MCTL_)
#define UCA0STAT_           (0x0065u)  /* USCI A0 Status Register */
DEFC(   UCA0STAT          , UCA0STAT_)
#define UCA0RXBUF_          (0x0066u)  /* USCI A0 Receive Buffer */
READ_ONLY DEFC( UCA0RXBUF      , UCA0RXBUF_)
#define UCA0TXBUF_          (0x0067u)  /* USCI A0 Transmit Buffer */
DEFC(   UCA0TXBUF         , UCA0TXBUF_)
#define UCA0ABCTL_          (0x005Du)  /* USCI A0 LIN Control */
DEFC(   UCA0ABCTL         , UCA0ABCTL_)
#define UCA0IRTCTL_         (0x005Eu)  /* USCI A0 IrDA Transmit Control */
DEFC(   UCA0IRTCTL        , UCA0IRTCTL_)
#define UCA0IRRCTL_         (0x005Fu)  /* USCI A0 IrDA Receive Control */
DEFC(   UCA0IRRCTL        , UCA0IRRCTL_)



#define UCB0CTL0_           (0x0068u)  /* USCI B0 Control Register 0 */
DEFC(   UCB0CTL0          , UCB0CTL0_)
#define UCB0CTL1_           (0x0069u)  /* USCI B0 Control Register 1 */
DEFC(   UCB0CTL1          , UCB0CTL1_)
#define UCB0BR0_            (0x006Au)  /* USCI B0 Baud Rate 0 */
DEFC(   UCB0BR0           , UCB0BR0_)
#define UCB0BR1_            (0x006Bu)  /* USCI B0 Baud Rate 1 */
DEFC(   UCB0BR1           , UCB0BR1_)
#define UCB0I2CIE_          (0x006Cu)  /* USCI B0 I2C Interrupt Enable Register */
DEFC(   UCB0I2CIE         , UCB0I2CIE_)
#define UCB0STAT_           (0x006Du)  /* USCI B0 Status Register */
DEFC(   UCB0STAT          , UCB0STAT_)
#define UCB0RXBUF_          (0x006Eu)  /* USCI B0 Receive Buffer */
READ_ONLY DEFC( UCB0RXBUF      , UCB0RXBUF_)
#define UCB0TXBUF_          (0x006Fu)  /* USCI B0 Transmit Buffer */
DEFC(   UCB0TXBUF         , UCB0TXBUF_)
#define UCB0I2COA_          (0x0118u)  /* USCI B0 I2C Own Address */
DEFW(   UCB0I2COA         , UCB0I2COA_)
#define UCB0I2CSA_          (0x011Au)  /* USCI B0 I2C Slave Address */
DEFW(   UCB0I2CSA         , UCB0I2CSA_)

// UART-Mode Bits
#define UCPEN               (0x80)    /* Async. Mode: Parity enable */
#define UCPAR               (0x40)    /* Async. Mode: Parity     0:odd / 1:even */
#define UCMSB               (0x20)    /* Async. Mode: MSB first  0:LSB / 1:MSB */
#define UC7BIT              (0x10)    /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
#define UCSPB               (0x08)    /* Async. Mode: Stop Bits  0:one / 1: two */
#define UCMODE1             (0x04)    /* Async. Mode: USCI Mode 1 */
#define UCMODE0             (0x02)    /* Async. Mode: USCI Mode 0 */
#define UCSYNC              (0x01)    /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */

// SPI-Mode Bits
#define UCCKPH              (0x80)    /* Sync. Mode: Clock Phase */
#define UCCKPL              (0x40)    /* Sync. Mode: Clock Polarity */
#define UCMST               (0x08)    /* Sync. Mode: Master Select */

// I2C-Mode Bits
#define UCA10               (0x80)    /* 10-bit Address Mode */
#define UCSLA10             (0x40)    /* 10-bit Slave Address Mode */
#define UCMM                (0x20)    /* Multi-Master Environment */
//#define res               (0x10)    /* reserved */
#define UCMODE_0            (0x00)    /* Sync. Mode: USCI Mode: 0 */
#define UCMODE_1            (0x02)    /* Sync. Mode: USCI Mode: 1 */
#define UCMODE_2            (0x04)    /* Sync. Mode: USCI Mode: 2 */
#define UCMODE_3            (0x06)    /* Sync. Mode: USCI Mode: 3 */

// UART-Mode Bits
#define UCSSEL1             (0x80)    /* USCI 0 Clock Source Select 1 */
#define UCSSEL0             (0x40)    /* USCI 0 Clock Source Select 0 */
#define UCRXEIE             (0x20)    /* RX Error interrupt enable */
#define UCBRKIE             (0x10)    /* Break interrupt enable */
#define UCDORM              (0x08)    /* Dormant (Sleep) Mode */
#define UCTXADDR            (0x04)    /* Send next Data as Address */
#define UCTXBRK             (0x02)    /* Send next Data as Break */
#define UCSWRST             (0x01)    /* USCI Software Reset */

// SPI-Mode Bits
//#define res               (0x20)    /* reserved */
//#define res               (0x10)    /* reserved */
//#define res               (0x08)    /* reserved */
//#define res               (0x04)    /* reserved */
//#define res               (0x02)    /* reserved */

// I2C-Mode Bits
//#define res               (0x20)    /* reserved */
#define UCTR                (0x10)    /* Transmit/Receive Select/Flag */
#define UCTXNACK            (0x08)    /* Transmit NACK */
#define UCTXSTP             (0x04)    /* Transmit STOP */
#define UCTXSTT             (0x02)    /* Transmit START */
#define UCSSEL_0            (0x00)    /* USCI 0 Clock Source: 0 */
#define UCSSEL_1            (0x40)    /* USCI 0 Clock Source: 1 */
#define UCSSEL_2            (0x80)    /* USCI 0 Clock Source: 2 */
#define UCSSEL_3            (0xC0)    /* USCI 0 Clock Source: 3 */

#define UCBRF3              (0x80)    /* USCI First Stage Modulation Select 3 */
#define UCBRF2              (0x40)    /* USCI First Stage Modulation Select 2 */
#define UCBRF1              (0x20)    /* USCI First Stage Modulation Select 1 */
#define UCBRF0              (0x10)    /* USCI First Stage Modulation Select 0 */
#define UCBRS2              (0x08)    /* USCI Second Stage Modulation Select 2 */
#define UCBRS1              (0x04)    /* USCI Second Stage Modulation Select 1 */
#define UCBRS0              (0x02)    /* USCI Second Stage Modulation Select 0 */
#define UCOS16              (0x01)    /* USCI 16-times Oversampling enable */

#define UCBRF_0             (0x00)    /* USCI First Stage Modulation: 0 */
#define UCBRF_1             (0x10)    /* USCI First Stage Modulation: 1 */
#define UCBRF_2             (0x20)    /* USCI First Stage Modulation: 2 */
#define UCBRF_3             (0x30)    /* USCI First Stage Modulation: 3 */
#define UCBRF_4             (0x40)    /* USCI First Stage Modulation: 4 */
#define UCBRF_5             (0x50)    /* USCI First Stage Modulation: 5 */
#define UCBRF_6             (0x60)    /* USCI First Stage Modulation: 6 */
#define UCBRF_7             (0x70)    /* USCI First Stage Modulation: 7 */
#define UCBRF_8             (0x80)    /* USCI First Stage Modulation: 8 */
#define UCBRF_9             (0x90)    /* USCI First Stage Modulation: 9 */
#define UCBRF_10            (0xA0)    /* USCI First Stage Modulation: A */
#define UCBRF_11            (0xB0)    /* USCI First Stage Modulation: B */
#define UCBRF_12            (0xC0)    /* USCI First Stage Modulation: C */
#define UCBRF_13            (0xD0)    /* USCI First Stage Modulation: D */
#define UCBRF_14            (0xE0)    /* USCI First Stage Modulation: E */
#define UCBRF_15            (0xF0)    /* USCI First Stage Modulation: F */

#define UCBRS_0             (0x00)    /* USCI Second Stage Modulation: 0 */
#define UCBRS_1             (0x02)    /* USCI Second Stage Modulation: 1 */
#define UCBRS_2             (0x04)    /* USCI Second Stage Modulation: 2 */
#define UCBRS_3             (0x06)    /* USCI Second Stage Modulation: 3 */
#define UCBRS_4             (0x08)    /* USCI Second Stage Modulation: 4 */
#define UCBRS_5             (0x0A)    /* USCI Second Stage Modulation: 5 */
#define UCBRS_6             (0x0C)    /* USCI Second Stage Modulation: 6 */
#define UCBRS_7             (0x0E)    /* USCI Second Stage Modulation: 7 */

#define UCLISTEN            (0x80)    /* USCI Listen mode */
#define UCFE                (0x40)    /* USCI Frame Error Flag */
#define UCOE                (0x20)    /* USCI Overrun Error Flag */
#define UCPE                (0x10)    /* USCI Parity Error Flag */
#define UCBRK               (0x08)    /* USCI Break received */
#define UCRXERR             (0x04)    /* USCI RX Error Flag */
#define UCADDR              (0x02)    /* USCI Address received Flag */
#define UCBUSY              (0x01)    /* USCI Busy Flag */
#define UCIDLE              (0x02)    /* USCI Idle line detected Flag */

//#define res               (0x80)    /* reserved */
//#define res               (0x40)    /* reserved */
//#define res               (0x20)    /* reserved */
//#define res               (0x10)    /* reserved */
#define UCNACKIE            (0x08)    /* NACK Condition interrupt enable */
#define UCSTPIE             (0x04)    /* STOP Condition interrupt enable */
#define UCSTTIE             (0x02)    /* START Condition interrupt enable */
#define UCALIE              (0x01)    /* Arbitration Lost interrupt enable */

#define UCSCLLOW            (0x40)    /* SCL low */
#define UCGC                (0x20)    /* General Call address received Flag */
#define UCBBUSY             (0x10)    /* Bus Busy Flag */
#define UCNACKIFG           (0x08)    /* NAK Condition interrupt Flag */
#define UCSTPIFG            (0x04)    /* STOP Condition interrupt Flag */
#define UCSTTIFG            (0x02)    /* START Condition interrupt Flag */
#define UCALIFG             (0x01)    /* Arbitration Lost interrupt Flag */

#define UCIRTXPL5           (0x80)    /* IRDA Transmit Pulse Length 5 */
#define UCIRTXPL4           (0x40)    /* IRDA Transmit Pulse Length 4 */
#define UCIRTXPL3           (0x20)    /* IRDA Transmit Pulse Length 3 */
#define UCIRTXPL2           (0x10)    /* IRDA Transmit Pulse Length 2 */
#define UCIRTXPL1           (0x08)    /* IRDA Transmit Pulse Length 1 */
#define UCIRTXPL0           (0x04)    /* IRDA Transmit Pulse Length 0 */
#define UCIRTXCLK           (0x02)    /* IRDA Transmit Pulse Clock Select */
#define UCIREN              (0x01)    /* IRDA Encoder/Decoder enable */

#define UCIRRXFL5           (0x80)    /* IRDA Receive Filter Length 5 */
#define UCIRRXFL4           (0x40)    /* IRDA Receive Filter Length 4 */
#define UCIRRXFL3           (0x20)    /* IRDA Receive Filter Length 3 */
#define UCIRRXFL2           (0x10)    /* IRDA Receive Filter Length 2 */
#define UCIRRXFL1           (0x08)    /* IRDA Receive Filter Length 1 */
#define UCIRRXFL0           (0x04)    /* IRDA Receive Filter Length 0 */
#define UCIRRXPL            (0x02)    /* IRDA Receive Input Polarity */
#define UCIRRXFE            (0x01)    /* IRDA Receive Filter enable */

//#define res               (0x80)    /* reserved */
//#define res               (0x40)    /* reserved */
#define UCDELIM1            (0x20)    /* Break Sync Delimiter 1 */
#define UCDELIM0            (0x10)    /* Break Sync Delimiter 0 */
#define UCSTOE              (0x08)    /* Sync-Field Timeout error */
#define UCBTOE              (0x04)    /* Break Timeout error */
//#define res               (0x02)    /* reserved */
#define UCABDEN             (0x01)    /* Auto Baud Rate detect enable */

#define UCGCEN              (0x8000u)  /* I2C General Call enable */
#define UCOA9               (0x0200u)  /* I2C Own Address 9 */
#define UCOA8               (0x0100u)  /* I2C Own Address 8 */
#define UCOA7               (0x0080u)  /* I2C Own Address 7 */
#define UCOA6               (0x0040u)  /* I2C Own Address 6 */
#define UCOA5               (0x0020u)  /* I2C Own Address 5 */
#define UCOA4               (0x0010u)  /* I2C Own Address 4 */
#define UCOA3               (0x0008u)  /* I2C Own Address 3 */
#define UCOA2               (0x0004u)  /* I2C Own Address 2 */
#define UCOA1               (0x0002u)  /* I2C Own Address 1 */
#define UCOA0               (0x0001u)  /* I2C Own Address 0 */

#define UCSA9               (0x0200u)  /* I2C Slave Address 9 */
#define UCSA8               (0x0100u)  /* I2C Slave Address 8 */
#define UCSA7               (0x0080u)  /* I2C Slave Address 7 */
#define UCSA6               (0x0040u)  /* I2C Slave Address 6 */
#define UCSA5               (0x0020u)  /* I2C Slave Address 5 */
#define UCSA4               (0x0010u)  /* I2C Slave Address 4 */
#define UCSA3               (0x0008u)  /* I2C Slave Address 3 */
#define UCSA2               (0x0004u)  /* I2C Slave Address 2 */
#define UCSA1               (0x0002u)  /* I2C Slave Address 1 */
#define UCSA0               (0x0001u)  /* I2C Slave Address 0 */

/************************************************************
* WATCHDOG TIMER
************************************************************/
#define __MSP430_HAS_WDT__            /* Definition to show that Module is available */

#define WDTCTL_             (0x0120u)  /* Watchdog Timer Control */
DEFW(   WDTCTL            , WDTCTL_)
/* The bit names have been prefixed with "WDT" */
#define WDTIS0              (0x0001u)
#define WDTIS1              (0x0002u)
#define WDTSSEL             (0x0004u)
#define WDTCNTCL            (0x0008u)
#define WDTTMSEL            (0x0010u)
#define WDTNMI              (0x0020u)
#define WDTNMIES            (0x0040u)
#define WDTHOLD             (0x0080u)

#define WDTPW               (0x5A00u)

/* WDT-interval times [1ms] coded with Bits 0-2 */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS0)                  /* 8ms     " */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1)                  /* 0.5ms   " */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS1+WDTIS0)           /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL)                 /* 1000ms  " */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS0)          /* 250ms   " */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1)          /* 16ms    " */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0)   /* 1.9ms   " */
/* Watchdog mode -> reset after expired time */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS0)                           /* 8ms     " */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS1)                           /* 0.5ms   " */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS1+WDTIS0)                    /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL)                          /* 1000ms  " */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL+WDTIS0)                   /* 250ms   " */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL+WDTIS1)                   /* 16ms    " */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL+WDTIS1+WDTIS0)            /* 1.9ms   " */

/* INTERRUPT CONTROL */
/* These two bits are defined in the Special Function Registers */
/* #define WDTIE               0x01 */
/* #define WDTIFG              0x01 */

/************************************************************
* Interrupt Vectors (offset from 0xFFE0)
************************************************************/

#define BASICTIMER_VECTOR   (0 * 2u)  /* 0xFFE0 Basic Timer */
#define PORT2_VECTOR        (1 * 2u)  /* 0xFFE2 Port 2 */
#define PORT1_VECTOR        (4 * 2u)  /* 0xFFE8 Port 1 */
#define TIMER0_A1_VECTOR    (5 * 2u)  /* 0xFFEA Timer0_A CC1-2, TA0 */
#define TIMER0_A0_VECTOR    (6 * 2u)  /* 0xFFEC Timer0_A CC0 */
#define ADC10_VECTOR        (7 * 2u)  /* 0xFFEE ADC10 */
#define USCIAB0TX_VECTOR    (8 * 2u)  /* 0xFFF0 USCI A0/B0 Transmit */
#define USCIAB0RX_VECTOR    (9 * 2u)  /* 0xFFF2 USCI A0/B0 Receive */
#define WDT_VECTOR          (10 * 2u) /* 0xFFF4 Watchdog Timer */
#define COMPARATORA_VECTOR  (11 * 2u) /* 0xFFF6 Comparator A */
#define TIMER1_A1_VECTOR    (12 * 2u) /* 0xFFF8 Timer1_A CC1-4, TA1 */
#define TIMER1_A0_VECTOR    (13 * 2u) /* 0xFFFA Timer1_A CC0 */
#define NMI_VECTOR          (14 * 2u) /* 0xFFFC Non-maskable */
#define RESET_VECTOR        (15 * 2u) /* 0xFFFE Reset [Highest Priority] */

/* Alternate Names */
#define TIMERA1_VECTOR      TIMER0_A1_VECTOR
#define TIMERA0_VECTOR      TIMER0_A0_VECTOR

/************************************************************
* End of Modules
************************************************************/
#pragma language=default

#endif /* #ifndef __msp430x41x2 */

