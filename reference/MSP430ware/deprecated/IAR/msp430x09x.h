/******************************************************************************/
/* Legacy Header File                                                         */
/* Not recommended for use in new projects.                                   */
/* Please use the msp430.h file or the device specific header file            */
/******************************************************************************/

/********************************************************************
*
* Standard register and bit definitions for the Texas Instruments
* MSP430 microcontroller.
*
* This file supports assembler and C development for
* MSP430x09x devices.
*
* Texas Instruments, Version 1.1
*
* Rev. 1.0, Initial Release
* Rev. 1.0, Added LCMP : A-POOL Latch comparator
*
*
********************************************************************/

#ifndef __msp430x09x
#define __msp430x09x

#define __MSP430_HEADER_VERSION__ 1059

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error msp430x09x.h file for use with ICC430/A430 only
#endif


#ifdef __IAR_SYSTEMS_ICC__
#include "in430.h"
#pragma language=extended

#define DEFC(name, address) __no_init volatile unsigned char name @ address;
#define DEFW(name, address) __no_init volatile unsigned short name @ address;

#define DEFCW(name, address) __no_init union \
{ \
  struct \
  { \
    volatile unsigned char  name##_L; \
    volatile unsigned char  name##_H; \
  }; \
  volatile unsigned short   name; \
} @ address;

#define READ_ONLY_DEFCW(name, address) __no_init union \
{ \
  struct \
  { \
    volatile READ_ONLY unsigned char  name##_L; \
    volatile READ_ONLY unsigned char  name##_H; \
  }; \
  volatile READ_ONLY unsigned short   name; \
} @ address;


#if __REGISTER_MODEL__ == __REGISTER_MODEL_REG20__
#define __ACCESS_20BIT_REG__  void __data20 * volatile
#else
#define __ACCESS_20BIT_REG__  volatile unsigned short  /* only short access from C is allowed in small memory model */
#endif

#define DEFA(name, address) __no_init union \
{ \
  struct \
  { \
    volatile unsigned char  name##_L; \
    volatile unsigned char  name##_H; \
  }; \
  struct \
  { \
    volatile unsigned short name##L; \
    volatile unsigned short name##H; \
  }; \
  __ACCESS_20BIT_REG__ name; \
} @ address;

#endif  /* __IAR_SYSTEMS_ICC__  */


#ifdef __IAR_SYSTEMS_ASM__
#define DEFC(name, address) sfrb name = address;
#define DEFW(name, address) sfrw name = address;

#define DEFCW(name, address) sfrbw name, name##_L, name##_H, address;
sfrbw macro name, name_L, name_H, address;
sfrb name_L = address;
sfrb name_H = address+1;
sfrw name   = address;
      endm

#define READ_ONLY_DEFCW(name, address) const_sfrbw name, name##_L, name##_H, address;
const_sfrbw macro name, name_L, name_H, address;
const sfrb name_L = address;
const sfrb name_H = address+1;
const sfrw name   = address;
      endm

#define DEFA(name, address) sfrba name, name##L, name##H, name##_L, name##_H, address;
sfrba macro name, nameL, nameH, name_L, name_H, address;
sfrb name_L = address;
sfrb name_H = address+1;
sfrw nameL  = address;
sfrw nameH  = address+2;
sfrl name   = address;
      endm

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
* CPU
************************************************************/
#define __MSP430_HAS_MSP430XV2_CPU__  /* Definition to show that it has MSP430XV2 CPU */

/************************************************************
* PERIPHERAL FILE MAP
************************************************************/

/************************************************************
* A-POOL
************************************************************/
#define __MSP430_HAS_APOOL__           /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_APOOL__ 0x01A0

#define  APCNF_              (0x01A0u)  /* A-POOL Configuration Register */
DEFCW(   APCNF             , APCNF_)
#define  APCTL_              (0x01A2u)  /* A-POOL Control Register 1 */
DEFCW(   APCTL             , APCTL_)
#define  APOMR_              (0x01A4u)  /* A-POOL Operation Mode Register 2 */
DEFCW(   APOMR             , APOMR_)
#define  APVDIV_             (0x01A6u)  /* A-POOL Voltage Divider Register 3 */
DEFCW(   APVDIV            , APVDIV_)
#define  APTRIM_             (0x01A8u)  /* A-POOL trimming register */
DEFCW(   APTRIM            , APTRIM_)
#define  APINT_              (0x01B0u)  /* A-POOL Integer Conversion Register */
DEFCW(   APINT             , APINT_)
#define  APINTB_             (0x01B2u)  /* A-POOL Integer Conversion Buffer Register */
DEFCW(   APINTB            , APINTB_)
#define  APFRACT_            (0x01B4u)  /* A-POOL Fractional Conversion Register */
DEFCW(   APFRACT           , APFRACT_)
#define  APFRACTB_           (0x01B6u)  /* A-POOL Fractional Conversion Buffer Register */
DEFCW(   APFRACTB          , APFRACTB_)
#define  APIFG_              (0x01BAu)  /* A-POOL Interrupt Flag Register */
DEFCW(   APIFG             , APIFG_)
#define  APIE_               (0x01BCu)  /* A-POOL Interrupt Enable Register */
DEFCW(   APIE              , APIE_)
#define APIV_               (0x01BEu)  /* A-POOL Interrupt Vector Word */
READ_ONLY_DEFCW( APIV           , APIV_)

/* APCNF Control Bits */
#define TA0EN                (0x0001u)  /* A-POOL TimerA0 trigger enable */
#define TA1EN                (0x0002u)  /* A-POOL TimerA1 trigger enable */
#define DFSET0               (0x0004u)  /* A-POOL Deglitch Filter Bit: 0 */
#define DFSET1               (0x0008u)  /* A-POOL Deglitch Filter Bit: 1 */
#define LCMP                 (0x0010u)  /* A-POOL Latch comparator */
#define CMPON                (0x0020u)  /* A-POOL Comparator enable */
#define DBON                 (0x0040u)  /* A-POOL DAC buffer enable signal */
#define CONVON               (0x0080u)  /* A-POOL Enable for converter’s resistor ladder */
#define CLKSEL0              (0x0100u)  /* A-POOL Conversion clock select Bit: 0 */
#define CLKSEL1              (0x0200u)  /* A-POOL Conversion clock select Bit: 1 */
#define EOCBU                (0x0400u)  /* A-POOL Enable bit for loading conversion buffer */
#define ATBU                 (0x0800u)  /* A-POOL Automatic update of conversion register */
#define A3PSEL               (0x1000u)  /* A-POOL Analog input A3 access Bit */
#define APREFON              (0x2000u)  /* A-POOL Internal voltage reference enable */
#define VREFEN               (0x4000u)  /* A-POOL Reference voltage pin enable */
//#define RESERVED             (0x8000u)  /* A-POOL */

/* APCNF Control Bits */
#define TA0EN_L             (0x0001u)  /* A-POOL TimerA0 trigger enable */
#define TA1EN_L             (0x0002u)  /* A-POOL TimerA1 trigger enable */
#define DFSET0_L            (0x0004u)  /* A-POOL Deglitch Filter Bit: 0 */
#define DFSET1_L            (0x0008u)  /* A-POOL Deglitch Filter Bit: 1 */
#define LCMP_L              (0x0010u)  /* A-POOL Latch comparator */
#define CMPON_L             (0x0020u)  /* A-POOL Comparator enable */
#define DBON_L              (0x0040u)  /* A-POOL DAC buffer enable signal */
#define CONVON_L            (0x0080u)  /* A-POOL Enable for converter’s resistor ladder */
//#define RESERVED             (0x8000u)  /* A-POOL */

/* APCNF Control Bits */
#define CLKSEL0_H           (0x0001u)  /* A-POOL Conversion clock select Bit: 0 */
#define CLKSEL1_H           (0x0002u)  /* A-POOL Conversion clock select Bit: 1 */
#define EOCBU_H             (0x0004u)  /* A-POOL Enable bit for loading conversion buffer */
#define ATBU_H              (0x0008u)  /* A-POOL Automatic update of conversion register */
#define A3PSEL_H            (0x0010u)  /* A-POOL Analog input A3 access Bit */
#define APREFON_H           (0x0020u)  /* A-POOL Internal voltage reference enable */
#define VREFEN_H            (0x0040u)  /* A-POOL Reference voltage pin enable */
//#define RESERVED             (0x8000u)  /* A-POOL */

#define DFSET_0              (0x0000u)  /* A-POOL Deglitch Filter select: 0 */
#define DFSET_1              (0x0004u)  /* A-POOL Deglitch Filter select: 1 */
#define DFSET_2              (0x0008u)  /* A-POOL Deglitch Filter select: 2 */
#define DFSET_3              (0x000Cu)  /* A-POOL Deglitch Filter select: 3 */

#define CLKSEL_0             (0x0000u)  /* A-POOL Conversion clock select: 0 */
#define CLKSEL_1             (0x0100u)  /* A-POOL Conversion clock select: 1 */
#define CLKSEL_2             (0x0200u)  /* A-POOL Conversion clock select: 2 */
#define CLKSEL_VLOCLK        (0x0000u)  /* A-POOL Conversion clock select: VLOCLK */
#define CLKSEL_MCLK          (0x0100u)  /* A-POOL Conversion clock select: MCLK */
#define CLKSEL_SMCLK         (0x0200u)  /* A-POOL Conversion clock select: SMCLK */

/* APCTL Control Bits */
#define ODEN                 (0x0001u)  /* A-POOL Output driver enable */
#define OSWP                 (0x0002u)  /* A-POOL Output swap */
#define OSEL                 (0x0004u)  /* A-POOL Output buffer select */
#define SLOPE                (0x0008u)  /* A-POOL Slope select of converter */
#define APNSEL0              (0x0010u)  /* A-POOL Neg. Channel Input Select 0 */
#define APNSEL1              (0x0020u)  /* A-POOL Neg. Channel Input Select 1 */
#define APNSEL2              (0x0040u)  /* A-POOL Neg. Channel Input Select 2 */
#define APNSEL3              (0x0080u)  /* A-POOL Neg. Channel Input Select 3 */
#define RUNSTOP              (0x0100u)  /* A-POOL Converter’s Run/Stop bit */
#define SBSTP                (0x0200u)  /* A-POOL Saturation based conversion stop enable */
#define CBSTP                (0x0400u)  /* A-POOL Comparator based conversion stop enable */
#define TBSTP                (0x0800u)  /* A-POOL Timer based conversion stop enable for TimerA0 */
#define APPSEL0              (0x1000u)  /* A-POOL Pos. Channel Input Select 0 */
#define APPSEL1              (0x2000u)  /* A-POOL Pos. Channel Input Select 1 */
#define APPSEL2              (0x4000u)  /* A-POOL Pos. Channel Input Select 2 */
#define APPSEL3              (0x8000u)  /* A-POOL Pos. Channel Input Select 3 */

/* APCTL Control Bits */
#define ODEN_L              (0x0001u)  /* A-POOL Output driver enable */
#define OSWP_L              (0x0002u)  /* A-POOL Output swap */
#define OSEL_L              (0x0004u)  /* A-POOL Output buffer select */
#define SLOPE_L             (0x0008u)  /* A-POOL Slope select of converter */
#define APNSEL0_L           (0x0010u)  /* A-POOL Neg. Channel Input Select 0 */
#define APNSEL1_L           (0x0020u)  /* A-POOL Neg. Channel Input Select 1 */
#define APNSEL2_L           (0x0040u)  /* A-POOL Neg. Channel Input Select 2 */
#define APNSEL3_L           (0x0080u)  /* A-POOL Neg. Channel Input Select 3 */

/* APCTL Control Bits */
#define RUNSTOP_H           (0x0001u)  /* A-POOL Converter’s Run/Stop bit */
#define SBSTP_H             (0x0002u)  /* A-POOL Saturation based conversion stop enable */
#define CBSTP_H             (0x0004u)  /* A-POOL Comparator based conversion stop enable */
#define TBSTP_H             (0x0008u)  /* A-POOL Timer based conversion stop enable for TimerA0 */
#define APPSEL0_H           (0x0010u)  /* A-POOL Pos. Channel Input Select 0 */
#define APPSEL1_H           (0x0020u)  /* A-POOL Pos. Channel Input Select 1 */
#define APPSEL2_H           (0x0040u)  /* A-POOL Pos. Channel Input Select 2 */
#define APPSEL3_H           (0x0080u)  /* A-POOL Pos. Channel Input Select 3 */

#define APNSEL_0             (0x0000u)  /* A-POOL V- terminal Input Select: Channel 0 */
#define APNSEL_1             (0x0010u)  /* A-POOL V- terminal Input Select: Channel 1 */
#define APNSEL_2             (0x0020u)  /* A-POOL V- terminal Input Select: Channel 2 */
#define APNSEL_3             (0x0030u)  /* A-POOL V- terminal Input Select: Channel 3 */
#define APNSEL_4             (0x0040u)  /* A-POOL V- terminal Input Select: Channel 4 */
#define APNSEL_5             (0x0050u)  /* A-POOL V- terminal Input Select: Channel 5 */
#define APNSEL_6             (0x0060u)  /* A-POOL V- terminal Input Select: Channel 6 */
#define APNSEL_7             (0x0070u)  /* A-POOL V- terminal Input Select: Channel 7 */

#define APPSEL_0             (0x0000u)  /* A-POOL V+ Terminal Input Select: Channel 0 */
#define APPSEL_1             (0x1000u)  /* A-POOL V+ Terminal Input Select: Channel 1 */
#define APPSEL_2             (0x2000u)  /* A-POOL V+ Terminal Input Select: Channel 2 */
#define APPSEL_3             (0x3000u)  /* A-POOL V+ Terminal Input Select: Channel 3 */
#define APPSEL_4             (0x4000u)  /* A-POOL V+ Terminal Input Select: Channel 4 */
#define APPSEL_5             (0x5000u)  /* A-POOL V+ Terminal Input Select: Channel 5 */
#define APPSEL_6             (0x6000u)  /* A-POOL V+ Terminal Input Select: Channel 6 */
#define APPSEL_7             (0x7000u)  /* A-POOL V+ Terminal Input Select: Channel 7 */
#define APPSEL_8             (0x8000u)  /* A-POOL V+ Terminal Input Select: Channel 8 */

/* APVDIV Control Bits */
#define A0DIV                (0x0001u)  /* A-POOL Analog channel #0 voltage divider control */
#define A1DIV                (0x0002u)  /* A-POOL Analog channel #1 voltage divider control */
#define A2DIV0               (0x0004u)  /* A-POOL Analog channel #2 voltage divider control Bit : 0 */
#define A2DIV1               (0x0008u)  /* A-POOL Analog channel #2 voltage divider control Bit : 1 */
#define A3DIV0               (0x0010u)  /* A-POOL Analog channel #3 voltage divider control Bit : 0 */
#define A3DIV1               (0x0020u)  /* A-POOL Analog channel #3 voltage divider control Bit : 0 */
#define TMPSEN               (0x0040u)  /* A-POOL Temperature sensor enable */
#define VCCDIVEN             (0x0080u)  /* A-POOL VCC voltage divider enable */
//#define RESERVED             (0x0100u)  /* A-POOL */
//#define RESERVED             (0x0200u)  /* A-POOL */
#define CLKTRIM0             (0x0400u)  /* A-POOL Clock trimming Bit : 0 */
#define CLKTRIM1             (0x0800u)  /* A-POOL Clock trimming Bit : 1 */
//#define RESERVED             (0x1000u)  /* A-POOL */
//#define RESERVED             (0x2000u)  /* A-POOL */
//#define RESERVED             (0x4000u)  /* A-POOL */
//#define RESERVED             (0x8000u)  /* A-POOL */

/* APVDIV Control Bits */
#define A0DIV_L             (0x0001u)  /* A-POOL Analog channel #0 voltage divider control */
#define A1DIV_L             (0x0002u)  /* A-POOL Analog channel #1 voltage divider control */
#define A2DIV0_L            (0x0004u)  /* A-POOL Analog channel #2 voltage divider control Bit : 0 */
#define A2DIV1_L            (0x0008u)  /* A-POOL Analog channel #2 voltage divider control Bit : 1 */
#define A3DIV0_L            (0x0010u)  /* A-POOL Analog channel #3 voltage divider control Bit : 0 */
#define A3DIV1_L            (0x0020u)  /* A-POOL Analog channel #3 voltage divider control Bit : 0 */
#define TMPSEN_L            (0x0040u)  /* A-POOL Temperature sensor enable */
#define VCCDIVEN_L          (0x0080u)  /* A-POOL VCC voltage divider enable */
//#define RESERVED             (0x0100u)  /* A-POOL */
//#define RESERVED             (0x0200u)  /* A-POOL */
//#define RESERVED             (0x1000u)  /* A-POOL */
//#define RESERVED             (0x2000u)  /* A-POOL */
//#define RESERVED             (0x4000u)  /* A-POOL */
//#define RESERVED             (0x8000u)  /* A-POOL */

/* APVDIV Control Bits */
//#define RESERVED             (0x0100u)  /* A-POOL */
//#define RESERVED             (0x0200u)  /* A-POOL */
#define CLKTRIM0_H          (0x0004u)  /* A-POOL Clock trimming Bit : 0 */
#define CLKTRIM1_H          (0x0008u)  /* A-POOL Clock trimming Bit : 1 */
//#define RESERVED             (0x1000u)  /* A-POOL */
//#define RESERVED             (0x2000u)  /* A-POOL */
//#define RESERVED             (0x4000u)  /* A-POOL */
//#define RESERVED             (0x8000u)  /* A-POOL */

#define A2DIV_0              (0x0000u)  /* A-POOL Analog channel #2 voltage divider control: 0 */
#define A2DIV_1              (0x0004u)  /* A-POOL Analog channel #2 voltage divider control: 1 */
#define A2DIV_2              (0x0008u)  /* A-POOL Analog channel #2 voltage divider control: 2 */
#define A2DIV_3              (0x000Cu)  /* A-POOL Analog channel #2 voltage divider control: 3 */

#define A3DIV_0              (0x0000u)  /* A-POOL Analog channel #3 voltage divider control: 0 */
#define A3DIV_1              (0x0010u)  /* A-POOL Analog channel #3 voltage divider control: 1 */
#define A3DIV_2              (0x0020u)  /* A-POOL Analog channel #3 voltage divider control: 2 */
#define A3DIV_3              (0x0030u)  /* A-POOL Analog channel #3 voltage divider control: 3 */

#define CLKTRIM_0            (0x0000u)  /* A-POOL Clock trimming: 0 */
#define CLKTRIM_1            (0x0400u)  /* A-POOL Clock trimming: 1 */
#define CLKTRIM_2            (0x0800u)  /* A-POOL Clock trimming: 2 */
#define CLKTRIM_3            (0x0C00u)  /* A-POOL Clock trimming: 3 */

#define REFTRIM_0            (0x0000u)  /* A-POOL Reference trimming: 0 */
#define REFTRIM_1            (0x1000u)  /* A-POOL Reference trimming: 1 */
#define REFTRIM_2            (0x2000u)  /* A-POOL Reference trimming: 2 */
#define REFTRIM_3            (0x3000u)  /* A-POOL Reference trimming: 3 */
#define REFTRIM_4            (0x4000u)  /* A-POOL Reference trimming: 4 */
#define REFTRIM_5            (0x5000u)  /* A-POOL Reference trimming: 5 */
#define REFTRIM_6            (0x6000u)  /* A-POOL Reference trimming: 6 */
#define REFTRIM_7            (0x7000u)  /* A-POOL Reference trimming: 7 */

/* APTRIM Control Bits */
#define REFTSEL              (0x0001u)  /* A-POOL Register bank used for the reference trimming */
#define REFTRIM0             (0x1000u)  /* A-POOL Reference trimming bit: 0 */
#define REFTRIM1             (0x2000u)  /* A-POOL Reference trimming bit: 1 */
#define REFTRIM2             (0x4000u)  /* A-POOL Reference trimming bit: 2 */
#define REFTRIM3             (0x8000u)  /* A-POOL Reference trimming bit: 3 */

/* APTRIM Control Bits */
#define REFTSEL_L           (0x0001u)  /* A-POOL Register bank used for the reference trimming */

/* APTRIM Control Bits */
#define REFTRIM0_H          (0x0010u)  /* A-POOL Reference trimming bit: 0 */
#define REFTRIM1_H          (0x0020u)  /* A-POOL Reference trimming bit: 1 */
#define REFTRIM2_H          (0x0040u)  /* A-POOL Reference trimming bit: 2 */
#define REFTRIM3_H          (0x0080u)  /* A-POOL Reference trimming bit: 3 */

/* APOMR Control Bits */
#define CLKDIV0              (0x0001u)  /* A-POOL Prescaler Control Bit: 0 */
#define CLKDIV1              (0x0002u)  /* A-POOL Prescaler Control Bit: 1 */
#define CLKDIV2              (0x0004u)  /* A-POOL Prescaler Control Bit: 2 */
#define SAREN                (0x0008u)  /* A-POOL SAR conversion enable */
#define CTEN                 (0x0100u)  /* A-POOL Continuous time mode of comparator */
#define AZCMP                (0x0200u)  /* A-POOL Clocked zero compensated long term comparison */
#define AZSWREQ              (0x0400u)  /* A-POOL SW request for Auto Zero Phase */
#define SVMINH               (0x0800u)  /* A-POOL Suppress the generation of an SVM interrupt event. */

/* APOMR Control Bits */
#define CLKDIV0_L           (0x0001u)  /* A-POOL Prescaler Control Bit: 0 */
#define CLKDIV1_L           (0x0002u)  /* A-POOL Prescaler Control Bit: 1 */
#define CLKDIV2_L           (0x0004u)  /* A-POOL Prescaler Control Bit: 2 */
#define SAREN_L             (0x0008u)  /* A-POOL SAR conversion enable */

/* APOMR Control Bits */
#define CTEN_H              (0x0001u)  /* A-POOL Continuous time mode of comparator */
#define AZCMP_H             (0x0002u)  /* A-POOL Clocked zero compensated long term comparison */
#define AZSWREQ_H           (0x0004u)  /* A-POOL SW request for Auto Zero Phase */
#define SVMINH_H            (0x0008u)  /* A-POOL Suppress the generation of an SVM interrupt event. */

#define CLKDIV_0             (0x0000u)  /* A-POOL Prescaler Control 0 : /1 */
#define CLKDIV_1             (0x0001u)  /* A-POOL Prescaler Control 1 : /2 */
#define CLKDIV_2             (0x0002u)  /* A-POOL Prescaler Control 2 : /4 */
#define CLKDIV_3             (0x0003u)  /* A-POOL Prescaler Control 3 : /8 */
#define CLKDIV_4             (0x0004u)  /* A-POOL Prescaler Control 4 : /16 */
#define CLKDIV_5             (0x0005u)  /* A-POOL Prescaler Control 5 : /32 */
#define CLKDIV__1            (0x0000u)  /* A-POOL Prescaler Control 0 : /1 */
#define CLKDIV__2            (0x0001u)  /* A-POOL Prescaler Control 1 : /2 */
#define CLKDIV__4            (0x0002u)  /* A-POOL Prescaler Control 2 : /4 */
#define CLKDIV__8            (0x0003u)  /* A-POOL Prescaler Control 3 : /8 */
#define CLKDIV__16           (0x0004u)  /* A-POOL Prescaler Control 4 : /16 */
#define CLKDIV__32           (0x0005u)  /* A-POOL Prescaler Control 5 : /32 */

/* APIFG Control Bits */
#define EOCIFG               (0x0001u)  /* A-POOL End of conversion interrupt flag */
#define CFIFG                (0x0002u)  /* A-POOL Comparator falling edge interrupt flag */
#define CRIFG                (0x0004u)  /* A-POOL Comparator rising edge interrupt flag */
#define REFOKIFG             (0x0008u)  /* A-POOL Reference voltage ready interrupt flag */

/* APIFG Control Bits */
#define EOCIFG_L            (0x0001u)  /* A-POOL End of conversion interrupt flag */
#define CFIFG_L             (0x0002u)  /* A-POOL Comparator falling edge interrupt flag */
#define CRIFG_L             (0x0004u)  /* A-POOL Comparator rising edge interrupt flag */
#define REFOKIFG_L          (0x0008u)  /* A-POOL Reference voltage ready interrupt flag */

/* APIFG Control Bits */

/* APIFG Control Bits */
#define EOCIE                (0x0001u)  /* A-POOL End of conversion interrupt enable */
#define CFIE                 (0x0002u)  /* A-POOL Comparator falling edge interrupt enable */
#define CRIE                 (0x0004u)  /* A-POOL Comparator rising edge interrupt enable */
#define REFIKIE              (0x0008u)  /* A-POOL Reference voltage ready interrupt enable */

/* APIFG Control Bits */
#define EOCIE_L             (0x0001u)  /* A-POOL End of conversion interrupt enable */
#define CFIE_L              (0x0002u)  /* A-POOL Comparator falling edge interrupt enable */
#define CRIE_L              (0x0004u)  /* A-POOL Comparator rising edge interrupt enable */
#define REFIKIE_L           (0x0008u)  /* A-POOL Reference voltage ready interrupt enable */

/* APIFG Control Bits */

/* APIV Definitions */
#define APIV_NONE           (0x0000u)    /* No Interrupt pending */
#define APIV_EOCIF          (0x0002u)    /* EOCIFG */
#define APIV_CFIFG          (0x0004u)    /* CFIFG */
#define APIV_CRIFG          (0x0006u)    /* CRIFG */

/************************************************************
* COMPACT CLOCK SYSTEM
************************************************************/
#define __MSP430_HAS_CCS__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CCS__ 0x0160

#define  CCSCTL0_            (0x0160u)  /* CCS Control Register 0 */
DEFCW(   CCSCTL0           , CCSCTL0_)
#define  CCSCTL1_            (0x0162u)  /* CCS Control Register 1 */
DEFCW(   CCSCTL1           , CCSCTL1_)
#define  CCSCTL2_            (0x0164u)  /* CCS Control Register 2 */
DEFCW(   CCSCTL2           , CCSCTL2_)
#define  CCSCTL4_            (0x0168u)  /* CCS Control Register 4 */
DEFCW(   CCSCTL4           , CCSCTL4_)
#define  CCSCTL5_            (0x016Au)  /* CCS Control Register 5 */
DEFCW(   CCSCTL5           , CCSCTL5_)
#define  CCSCTL6_            (0x016Cu)  /* CCS Control Register 6 */
DEFCW(   CCSCTL6           , CCSCTL6_)
#define  CCSCTL7_            (0x016Eu)  /* CCS Control Register 7 */
DEFCW(   CCSCTL7           , CCSCTL7_)
#define  CCSCTL8_            (0x0170u)  /* CCS Control Register 8 */
DEFCW(   CCSCTL8           , CCSCTL8_)

/* CCSCTL0 Control Bits */

/* CCSCTL0 Control Bits */

/* CCSCTL0 Control Bits */
#define CCSKEY               (0xA500u)    /* CCS Password */

/* CCSCTL1 Control Bits */
#define DIVCLK              (0x0001u)    /* Clock division for CLKIN / X-OSC */

/* CCSCTL1 Control Bits */
#define DIVCLK_L            (0x0001u)    /* Clock division for CLKIN / X-OSC */

/* CCSCTL1 Control Bits */

/* CCSCTL2 Control Bits */
#define FSEL0               (0x0001u)    /* Frequency trimming of the HF-OSC Bit: 0 */
#define FSEL1               (0x0002u)    /* Frequency trimming of the HF-OSC Bit: 1 */
#define FSEL2               (0x0004u)    /* Frequency trimming of the HF-OSC Bit: 2 */
#define FSEL3               (0x0008u)    /* Frequency trimming of the HF-OSC Bit: 3 */
#define FSEL4               (0x0010u)    /* Frequency trimming of the HF-OSC Bit: 4 */
#define FSEL5               (0x0020u)    /* Frequency trimming of the HF-OSC Bit: 5 */
#define FSEL6               (0x0040u)    /* Frequency trimming of the HF-OSC Bit: 6 */

/* CCSCTL2 Control Bits */
#define FSEL0_L             (0x0001u)    /* Frequency trimming of the HF-OSC Bit: 0 */
#define FSEL1_L             (0x0002u)    /* Frequency trimming of the HF-OSC Bit: 1 */
#define FSEL2_L             (0x0004u)    /* Frequency trimming of the HF-OSC Bit: 2 */
#define FSEL3_L             (0x0008u)    /* Frequency trimming of the HF-OSC Bit: 3 */
#define FSEL4_L             (0x0010u)    /* Frequency trimming of the HF-OSC Bit: 4 */
#define FSEL5_L             (0x0020u)    /* Frequency trimming of the HF-OSC Bit: 5 */
#define FSEL6_L             (0x0040u)    /* Frequency trimming of the HF-OSC Bit: 6 */

/* CCSCTL2 Control Bits */

/* CCSCTL4 Control Bits */
#define SELM0               (0x0001u)   /* MCLK Source Select Bit: 0 */
#define SELM1               (0x0002u)   /* MCLK Source Select Bit: 1 */
//#define RESERVED            (0x0004u)    /* RESERVED */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define SELS0               (0x0010u)   /* SMCLK Source Select Bit: 0 */
#define SELS1               (0x0020u)   /* SMCLK Source Select Bit: 1 */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
#define SELA0               (0x0100u)   /* ACLK Source Select Bit: 0 */
#define SELA1               (0x0200u)   /* ACLK Source Select Bit: 1 */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* CCSCTL4 Control Bits */
#define SELM0_L             (0x0001u)   /* MCLK Source Select Bit: 0 */
#define SELM1_L             (0x0002u)   /* MCLK Source Select Bit: 1 */
//#define RESERVED            (0x0004u)    /* RESERVED */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define SELS0_L             (0x0010u)   /* SMCLK Source Select Bit: 0 */
#define SELS1_L             (0x0020u)   /* SMCLK Source Select Bit: 1 */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* CCSCTL4 Control Bits */
//#define RESERVED            (0x0004u)    /* RESERVED */
//#define RESERVED            (0x0008u)    /* RESERVED */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
#define SELA0_H             (0x0001u)   /* ACLK Source Select Bit: 0 */
#define SELA1_H             (0x0002u)   /* ACLK Source Select Bit: 1 */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

#define SELM_0              (0x0000u)   /* MCLK Source Select 0 */
#define SELM_1              (0x0001u)   /* MCLK Source Select 1 */
#define SELM_2              (0x0002u)   /* MCLK Source Select 2 */
#define SELM_3              (0x0003u)   /* MCLK Source Select 3 */
#define SELM__HFCLK         (0x0000u)   /* MCLK Source Select HFCLK */
#define SELM__LFCLK         (0x0001u)   /* MCLK Source Select LFCLK */
#define SELM__CLKIN         (0x0002u)   /* MCLK Source Select CLKIN */

#define SELS_0              (0x0000u)   /* SMCLK Source Select 0 */
#define SELS_1              (0x0010u)   /* SMCLK Source Select 1 */
#define SELS_2              (0x0020u)   /* SMCLK Source Select 2 */
#define SELS_3              (0x0030u)   /* SMCLK Source Select 3 */
#define SELS__HFCLK         (0x0000u)   /* SMCLK Source Select HFCLK */
#define SELS__LFCLK         (0x0010u)   /* SMCLK Source Select LFCLK */
#define SELS__CLKIN         (0x0020u)   /* SMCLK Source Select CLKIN */

#define SELA_0              (0x0000u)   /* ACLK Source Select 0 */
#define SELA_1              (0x0100u)   /* ACLK Source Select 1 */
#define SELA_2              (0x0200u)   /* ACLK Source Select 2 */
#define SELA_3              (0x0300u)   /* ACLK Source Select 3 */
#define SELA__HFCLK         (0x0000u)   /* ACLK Source Select HFCLK */
#define SELA__LFCLK         (0x0100u)   /* ACLK Source Select LFCLK */
#define SELA__CLKIN         (0x0200u)   /* ACLK Source Select CLKIN */

/* CCSCTL5 Control Bits */
#define DIVM0               (0x0001u)   /* MCLK Divider Bit: 0 */
#define DIVM1               (0x0002u)   /* MCLK Divider Bit: 1 */
#define DIVM2               (0x0004u)   /* MCLK Divider Bit: 2 */
//#define RESERVED            (0x0004u)    /* RESERVED */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define DIVS0               (0x0010u)   /* SMCLK Divider Bit: 0 */
#define DIVS1               (0x0020u)   /* SMCLK Divider Bit: 1 */
#define DIVS2               (0x0040u)   /* SMCLK Divider Bit: 2 */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
#define DIVA0               (0x0100u)   /* ACLK Divider Bit: 0 */
#define DIVA1               (0x0200u)   /* ACLK Divider Bit: 1 */
#define DIVA2               (0x0400u)   /* ACLK Divider Bit: 2 */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* CCSCTL5 Control Bits */
#define DIVM0_L             (0x0001u)   /* MCLK Divider Bit: 0 */
#define DIVM1_L             (0x0002u)   /* MCLK Divider Bit: 1 */
#define DIVM2_L             (0x0004u)   /* MCLK Divider Bit: 2 */
//#define RESERVED            (0x0004u)    /* RESERVED */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define DIVS0_L             (0x0010u)   /* SMCLK Divider Bit: 0 */
#define DIVS1_L             (0x0020u)   /* SMCLK Divider Bit: 1 */
#define DIVS2_L             (0x0040u)   /* SMCLK Divider Bit: 2 */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* CCSCTL5 Control Bits */
//#define RESERVED            (0x0004u)    /* RESERVED */
//#define RESERVED            (0x0008u)    /* RESERVED */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
#define DIVA0_H             (0x0001u)   /* ACLK Divider Bit: 0 */
#define DIVA1_H             (0x0002u)   /* ACLK Divider Bit: 1 */
#define DIVA2_H             (0x0004u)   /* ACLK Divider Bit: 2 */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

#define DIVM_0              (0x0000u)    /* MCLK Source Divider 0 */
#define DIVM_1              (0x0001u)    /* MCLK Source Divider 1 */
#define DIVM_2              (0x0002u)    /* MCLK Source Divider 2 */
#define DIVM_3              (0x0003u)    /* MCLK Source Divider 3 */
#define DIVM_4              (0x0004u)    /* MCLK Source Divider 4 */
#define DIVM_5              (0x0005u)    /* MCLK Source Divider 5 */
#define DIVM__1             (0x0000u)    /* MCLK Source Divider f(MCLK)/1 */
#define DIVM__2             (0x0001u)    /* MCLK Source Divider f(MCLK)/2 */
#define DIVM__4             (0x0002u)    /* MCLK Source Divider f(MCLK)/4 */
#define DIVM__8             (0x0003u)    /* MCLK Source Divider f(MCLK)/8 */
#define DIVM__16            (0x0004u)    /* MCLK Source Divider f(MCLK)/16 */
#define DIVM__32            (0x0005u)    /* MCLK Source Divider f(MCLK)/32 */

#define DIVS_0              (0x0000u)    /* SMCLK Source Divider 0 */
#define DIVS_1              (0x0010u)    /* SMCLK Source Divider 1 */
#define DIVS_2              (0x0020u)    /* SMCLK Source Divider 2 */
#define DIVS_3              (0x0030u)    /* SMCLK Source Divider 3 */
#define DIVS_4              (0x0040u)    /* SMCLK Source Divider 4 */
#define DIVS_5              (0x0050u)    /* SMCLK Source Divider 5 */
#define DIVS__1             (0x0000u)    /* SMCLK Source Divider f(SMCLK)/1 */
#define DIVS__2             (0x0010u)    /* SMCLK Source Divider f(SMCLK)/2 */
#define DIVS__4             (0x0020u)    /* SMCLK Source Divider f(SMCLK)/4 */
#define DIVS__8             (0x0030u)    /* SMCLK Source Divider f(SMCLK)/8 */
#define DIVS__16            (0x0040u)    /* SMCLK Source Divider f(SMCLK)/16 */
#define DIVS__32            (0x0050u)    /* SMCLK Source Divider f(SMCLK)/32 */

#define DIVA_0              (0x0000u)    /* ACLK Source Divider 0 */
#define DIVA_1              (0x0100u)    /* ACLK Source Divider 1 */
#define DIVA_2              (0x0200u)    /* ACLK Source Divider 2 */
#define DIVA_3              (0x0300u)    /* ACLK Source Divider 3 */
#define DIVA_4              (0x0400u)    /* ACLK Source Divider 4 */
#define DIVA_5              (0x0500u)    /* ACLK Source Divider 5 */
#define DIVA__1             (0x0000u)    /* ACLK Source Divider f(ACLK)/1 */
#define DIVA__2             (0x0100u)    /* ACLK Source Divider f(ACLK)/2 */
#define DIVA__4             (0x0200u)    /* ACLK Source Divider f(ACLK)/4 */
#define DIVA__8             (0x0300u)    /* ACLK Source Divider f(ACLK)/8 */
#define DIVA__16            (0x0400u)    /* ACLK Source Divider f(ACLK)/16 */
#define DIVA__32            (0x0500u)    /* ACLK Source Divider f(ACLK)/32 */

/* CCSCTL6 Control Bits */
#define XTOFF               (0x0001u)    /* Disable XT oscillator */

/* CCSCTL6 Control Bits */
#define XTOFF_L             (0x0001u)    /* Disable XT oscillator */

/* CCSCTL6 Control Bits */

/* CCSCTL7 Control Bits */
#define XOFFG              (0x0001u)    /* X-tal Oscillator Fault Flag */
#define HFOFFG             (0x0002u)    /* High Frequency Oscillator Fault Flag */

/* CCSCTL7 Control Bits */
#define XOFFG_L             (0x0001u)    /* X-tal Oscillator Fault Flag */
#define HFOFFG_L            (0x0002u)    /* High Frequency Oscillator Fault Flag */

/* CCSCTL7 Control Bits */

/* CCSCTL8 Control Bits */
#define ACLKREQEN           (0x0001u)    /* ACLK Clock Request Enable */
#define MCLKREQEN           (0x0002u)    /* MCLK Clock Request Enable */
#define SMCLKREQEN          (0x0004u)    /* SMCLK Clock Request Enable */

/* CCSCTL8 Control Bits */
#define ACLKREQEN_L         (0x0001u)    /* ACLK Clock Request Enable */
#define MCLKREQEN_L         (0x0002u)    /* MCLK Clock Request Enable */
#define SMCLKREQEN_L        (0x0004u)    /* SMCLK Clock Request Enable */

/* CCSCTL8 Control Bits */

/************************************************************
* DIGITAL I/O Port1/2 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT1_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT1_R__ 0x0200
#define __MSP430_HAS_PORT2_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORT2_R__ 0x0200
#define __MSP430_HAS_PORTA_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTA_R__ 0x0200

#define PAIN_               (0x0200u)  /* Port A Input */
READ_ONLY_DEFCW( PAIN           , PAIN_)
#define  PAOUT_              (0x0202u)  /* Port A Output */
DEFCW(   PAOUT             , PAOUT_)
#define  PADIR_              (0x0204u)  /* Port A Direction */
DEFCW(   PADIR             , PADIR_)
#define  PAREN_              (0x0206u)  /* Port A Resistor Enable */
DEFCW(   PAREN             , PAREN_)
#define  PADS_               (0x0208u)  /* Port A Resistor Drive Strenght */
DEFCW(   PADS              , PADS_)
#define  PASEL0_             (0x020Au)  /* Port A Selection 0 */
DEFCW(   PASEL0            , PASEL0_)
#define  PASEL1_             (0x020Cu)  /* Port A Selection 1 */
DEFCW(   PASEL1            , PASEL1_)
#define  PAIES_              (0x0218u)  /* Port A Interrupt Edge Select */
DEFCW(   PAIES             , PAIES_)
#define  PAIE_               (0x021Au)  /* Port A Interrupt Enable */
DEFCW(   PAIE              , PAIE_)
#define  PAIFG_              (0x021Cu)  /* Port A Interrupt Flag */
DEFCW(   PAIFG             , PAIFG_)


#define P1IV_               (0x020Eu)  /* Port 1 Interrupt Vector Word */
DEFW(   P1IV              , P1IV_)
#define P2IV_               (0x021Eu)  /* Port 2 Interrupt Vector Word */
DEFW(   P2IV              , P2IV_)
#define P1IN                (PAIN_L)  /* Port 1 Input */
#define P1OUT               (PAOUT_L) /* Port 1 Output */
#define P1DIR               (PADIR_L) /* Port 1 Direction */
#define P1REN               (PAREN_L) /* Port 1 Resistor Enable */
#define P1DS                (PADS_L)  /* Port 1 Resistor Drive Strenght */
#define P1SEL0              (PASEL0_L) /* Port 1 Selection 0 */
#define P1SEL1              (PASEL1_L) /* Port 1 Selection 1 */
#define P1IES               (PAIES_L) /* Port 1 Interrupt Edge Select */
#define P1IE                (PAIE_L)  /* Port 1 Interrupt Enable */
#define P1IFG               (PAIFG_L) /* Port 1 Interrupt Flag */

//Definitions for P1IV
#define P1IV_NONE            (0x0000u)    /* No Interrupt pending */
#define P1IV_P1IFG0          (0x0002u)    /* P1IV P1IFG.0 */
#define P1IV_P1IFG1          (0x0004u)    /* P1IV P1IFG.1 */
#define P1IV_P1IFG2          (0x0006u)    /* P1IV P1IFG.2 */
#define P1IV_P1IFG3          (0x0008u)    /* P1IV P1IFG.3 */
#define P1IV_P1IFG4          (0x000Au)    /* P1IV P1IFG.4 */
#define P1IV_P1IFG5          (0x000Cu)    /* P1IV P1IFG.5 */
#define P1IV_P1IFG6          (0x000Eu)    /* P1IV P1IFG.6 */
#define P1IV_P1IFG7          (0x0010u)    /* P1IV P1IFG.7 */

#define P2IN                (PAIN_H)  /* Port 2 Input */
#define P2OUT               (PAOUT_H) /* Port 2 Output */
#define P2DIR               (PADIR_H) /* Port 2 Direction */
#define P2REN               (PAREN_H) /* Port 2 Resistor Enable */
#define P2DS                (PADS_H)  /* Port 2 Resistor Drive Strenght */
#define P2SEL0              (PASEL0_H) /* Port 2 Selection 0 */
#define P2SEL1              (PASEL1_H) /* Port 2 Selection 1 */
#define P2IES               (PAIES_H) /* Port 2 Interrupt Edge Select */
#define P2IE                (PAIE_H)  /* Port 2 Interrupt Enable */
#define P2IFG               (PAIFG_H) /* Port 2 Interrupt Flag */

//Definitions for P2IV
#define P2IV_NONE            (0x0000u)    /* No Interrupt pending */
#define P2IV_P2IFG0          (0x0002u)    /* P2IV P2IFG.0 */
#define P2IV_P2IFG1          (0x0004u)    /* P2IV P2IFG.1 */
#define P2IV_P2IFG2          (0x0006u)    /* P2IV P2IFG.2 */
#define P2IV_P2IFG3          (0x0008u)    /* P2IV P2IFG.3 */
#define P2IV_P2IFG4          (0x000Au)    /* P2IV P2IFG.4 */
#define P2IV_P2IFG5          (0x000Cu)    /* P2IV P2IFG.5 */
#define P2IV_P2IFG6          (0x000Eu)    /* P2IV P2IFG.6 */
#define P2IV_P2IFG7          (0x0010u)    /* P2IV P2IFG.7 */


/************************************************************
* SFR - Special Function Register Module
************************************************************/
#define __MSP430_HAS_SFR__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_SFR__ 0x0100

#define  SFRIE1_             (0x0100u)  /* Interrupt Enable 1 */
DEFCW(   SFRIE1            , SFRIE1_)

/* SFRIE1 Control Bits */
#define WDTIE               (0x0001u)  /* WDT Interrupt Enable */
#define OFIE                (0x0002u)  /* Osc Fault Enable */
//#define Reserved          (0x0004u)
#define VMAIE               (0x0008u)  /* Vacant Memory Interrupt Enable */
#define NMIIE               (0x0010u)  /* NMI Interrupt Enable */
#define JMBINIE             (0x0040u)  /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE            (0x0080u)  /* JTAG Mail Box output Interrupt Enable */
#define SVMIE               (0x0100u)  /* SVM Interrupt Enable */

#define WDTIE_L             (0x0001u)  /* WDT Interrupt Enable */
#define OFIE_L              (0x0002u)  /* Osc Fault Enable */
//#define Reserved          (0x0004u)
#define VMAIE_L             (0x0008u)  /* Vacant Memory Interrupt Enable */
#define NMIIE_L             (0x0010u)  /* NMI Interrupt Enable */
#define JMBINIE_L           (0x0040u)  /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE_L          (0x0080u)  /* JTAG Mail Box output Interrupt Enable */

//#define Reserved          (0x0004u)
#define SVMIE_H             (0x0001u)  /* SVM Interrupt Enable */

#define  SFRIFG1_            (0x0102u)  /* Interrupt Flag 1 */
DEFCW(   SFRIFG1           , SFRIFG1_)
/* SFRIFG1 Control Bits */
#define WDTIFG              (0x0001u)  /* WDT Interrupt Flag */
#define OFIFG               (0x0002u)  /* Osc Fault Flag */
//#define Reserved          (0x0004u)
#define VMAIFG              (0x0008u)  /* Vacant Memory Interrupt Flag */
#define NMIIFG              (0x0010u)  /* NMI Interrupt Flag */
//#define Reserved          (0x0020u)
#define JMBINIFG            (0x0040u)  /* JTAG Mail Box input Interrupt Flag */
#define JMBOUTIFG           (0x0080u)  /* JTAG Mail Box output Interrupt Flag */
#define SVMIFG              (0x0100u)  /* SVM Interrupt Flag */

#define WDTIFG_L            (0x0001u)  /* WDT Interrupt Flag */
#define OFIFG_L             (0x0002u)  /* Osc Fault Flag */
//#define Reserved          (0x0004u)
#define VMAIFG_L            (0x0008u)  /* Vacant Memory Interrupt Flag */
#define NMIIFG_L            (0x0010u)  /* NMI Interrupt Flag */
//#define Reserved          (0x0020u)
#define JMBINIFG_L          (0x0040u)  /* JTAG Mail Box input Interrupt Flag */
#define JMBOUTIFG_L         (0x0080u)  /* JTAG Mail Box output Interrupt Flag */

//#define Reserved          (0x0004u)
//#define Reserved          (0x0020u)
#define SVMIFG_H            (0x0001u)  /* SVM Interrupt Flag */

#define  SFRRPCR_            (0x0104u)  /* RESET Pin Control Register */
DEFCW(   SFRRPCR           , SFRRPCR_)
/* SFRRPCR Control Bits */
#define SYSNMI              (0x0001u)  /* NMI select */
#define SYSNMIIES           (0x0002u)  /* NMI edge select */
#define SYSRSTUP            (0x0004u)  /* RESET Pin pull down/up select */
#define SYSRSTRE            (0x0008u)  /* RESET Pin Resistor enable */

#define SYSNMI_L            (0x0001u)  /* NMI select */
#define SYSNMIIES_L         (0x0002u)  /* NMI edge select */
#define SYSRSTUP_L          (0x0004u)  /* RESET Pin pull down/up select */
#define SYSRSTRE_L          (0x0008u)  /* RESET Pin Resistor enable */

/************************************************************
* COMPACT SYS - System Module
************************************************************/
#define __MSP430_HAS_SYS__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_SYS__ 0x0180

#define  SYSCTL_             (0x0180u)  /* System control */
DEFCW(   SYSCTL            , SYSCTL_)
#define  SYSBSLC_            (0x0182u)  /* Boot strap configuration area */
DEFCW(   SYSBSLC           , SYSBSLC_)
#define  SYSJMBC_            (0x0186u)  /* JTAG mailbox control */
DEFCW(   SYSJMBC           , SYSJMBC_)
#define  SYSJMBI0_           (0x0188u)  /* JTAG mailbox input 0 */
DEFCW(   SYSJMBI0          , SYSJMBI0_)
#define  SYSJMBI1_           (0x018Au)  /* JTAG mailbox input 1 */
DEFCW(   SYSJMBI1          , SYSJMBI1_)
#define  SYSJMBO0_           (0x018Cu)  /* JTAG mailbox output 0 */
DEFCW(   SYSJMBO0          , SYSJMBO0_)
#define  SYSJMBO1_           (0x018Eu)  /* JTAG mailbox output 1 */
DEFCW(   SYSJMBO1          , SYSJMBO1_)
#define  SYSCNF_             (0x0190u)  /* System Configuration Register */
DEFCW(   SYSCNF            , SYSCNF_)

#define  SYSBERRIV_          (0x0198u)  /* Bus Error vector generator */
DEFCW(   SYSBERRIV         , SYSBERRIV_)
#define  SYSUNIV_            (0x019Au)  /* User NMI vector generator */
DEFCW(   SYSUNIV           , SYSUNIV_)
#define  SYSSNIV_            (0x019Cu)  /* System NMI vector generator */
DEFCW(   SYSSNIV           , SYSSNIV_)
#define  SYSRSTIV_           (0x019Eu)  /* Reset vector generator */
DEFCW(   SYSRSTIV          , SYSRSTIV_)

/* SYSCTL Control Bits */
#define SYSRIVECT           (0x0001u)  /* SYS - RAM based interrupt vectors */
//#define RESERVED            (0x0002u)  /* SYS - Reserved */
#define SYSPMMPE            (0x0004u)  /* SYS - PMM access protect */
//#define RESERVED            (0x0008u)  /* SYS - Reserved */
#define SYSBSLIND           (0x0010u)  /* SYS - TCK/RST indication detected */
#define SYSJTAGPIN          (0x0020u)  /* SYS - Dedicated JTAG pins enabled */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSCTL Control Bits */
#define SYSRIVECT_L         (0x0001u)  /* SYS - RAM based interrupt vectors */
//#define RESERVED            (0x0002u)  /* SYS - Reserved */
#define SYSPMMPE_L          (0x0004u)  /* SYS - PMM access protect */
//#define RESERVED            (0x0008u)  /* SYS - Reserved */
#define SYSBSLIND_L         (0x0010u)  /* SYS - TCK/RST indication detected */
#define SYSJTAGPIN_L        (0x0020u)  /* SYS - Dedicated JTAG pins enabled */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSCTL Control Bits */
//#define RESERVED            (0x0002u)  /* SYS - Reserved */
//#define RESERVED            (0x0008u)  /* SYS - Reserved */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSBSLC Control Bits */
#define SYSBSLSIZE0         (0x0001u)  /* SYS - BSL Protection Size 0 */
#define SYSBSLSIZE1         (0x0002u)  /* SYS - BSL Protection Size 1 */
#define SYSBSLR             (0x0004u)  /* SYS - RAM assigned to BSL */
//#define RESERVED            (0x0008u)  /* SYS - Reserved */
//#define RESERVED            (0x0010u)  /* SYS - Reserved */
//#define RESERVED            (0x0020u)  /* SYS - Reserved */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
#define SYSBSLOFF           (0x4000u)  /* SYS - BSL Memeory disabled */
#define SYSBSLPE            (0x8000u)  /* SYS - BSL Memory protection enabled */

/* SYSBSLC Control Bits */
#define SYSBSLSIZE0_L       (0x0001u)  /* SYS - BSL Protection Size 0 */
#define SYSBSLSIZE1_L       (0x0002u)  /* SYS - BSL Protection Size 1 */
#define SYSBSLR_L           (0x0004u)  /* SYS - RAM assigned to BSL */
//#define RESERVED            (0x0008u)  /* SYS - Reserved */
//#define RESERVED            (0x0010u)  /* SYS - Reserved */
//#define RESERVED            (0x0020u)  /* SYS - Reserved */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */

/* SYSBSLC Control Bits */
//#define RESERVED            (0x0008u)  /* SYS - Reserved */
//#define RESERVED            (0x0010u)  /* SYS - Reserved */
//#define RESERVED            (0x0020u)  /* SYS - Reserved */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
#define SYSBSLOFF_H         (0x0040u)  /* SYS - BSL Memeory disabled */
#define SYSBSLPE_H          (0x0080u)  /* SYS - BSL Memory protection enabled */

/* SYSJMBC Control Bits */
#define JMBIN0FG            (0x0001u)  /* SYS - Incoming JTAG Mailbox 0 Flag */
#define JMBIN1FG            (0x0002u)  /* SYS - Incoming JTAG Mailbox 1 Flag */
#define JMBOUT0FG           (0x0004u)  /* SYS - Outgoing JTAG Mailbox 0 Flag */
#define JMBOUT1FG           (0x0008u)  /* SYS - Outgoing JTAG Mailbox 1 Flag */
#define JMBMODE             (0x0010u)  /* SYS - JMB 16/32 Bit Mode */
//#define RESERVED            (0x0020u)  /* SYS - Reserved */
#define JMBCLR0OFF          (0x0040u)  /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
#define JMBCLR1OFF          (0x0080u)  /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSJMBC Control Bits */
#define JMBIN0FG_L          (0x0001u)  /* SYS - Incoming JTAG Mailbox 0 Flag */
#define JMBIN1FG_L          (0x0002u)  /* SYS - Incoming JTAG Mailbox 1 Flag */
#define JMBOUT0FG_L         (0x0004u)  /* SYS - Outgoing JTAG Mailbox 0 Flag */
#define JMBOUT1FG_L         (0x0008u)  /* SYS - Outgoing JTAG Mailbox 1 Flag */
#define JMBMODE_L           (0x0010u)  /* SYS - JMB 16/32 Bit Mode */
//#define RESERVED            (0x0020u)  /* SYS - Reserved */
#define JMBCLR0OFF_L        (0x0040u)  /* SYS - Incoming JTAG Mailbox 0 Flag auto-clear disalbe */
#define JMBCLR1OFF_L        (0x0080u)  /* SYS - Incoming JTAG Mailbox 1 Flag auto-clear disalbe */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSJMBC Control Bits */
//#define RESERVED            (0x0020u)  /* SYS - Reserved */
//#define RESERVED            (0x0100u)  /* SYS - Reserved */
//#define RESERVED            (0x0200u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSCNF Control Bits */
//#define RESERVED            (0x0001u)  /* SYS - Reserved */
//#define RESERVED            (0x0002u)  /* SYS - Reserved */
#define SVMOE               (0x0004u)  /* SYS - SVM output enable */
#define SVMPO               (0x0008u)  /* SYS - SVM based Ports off flag */
#define SVMPD               (0x0010u)  /* SYS - Incoming JTAG Mailbox 0 Flag */
#define SVMEN               (0x0020u)  /* SYS - SVM based port disable */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
#define RAMLCK0             (0x0100u)  /* SYS - Write lock enable for configuration RAM */
#define RAMLCK1             (0x0200u)  /* SYS - Write lock enable for application’s code RAM */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSCNF Control Bits */
//#define RESERVED            (0x0001u)  /* SYS - Reserved */
//#define RESERVED            (0x0002u)  /* SYS - Reserved */
#define SVMOE_L             (0x0004u)  /* SYS - SVM output enable */
#define SVMPO_L             (0x0008u)  /* SYS - SVM based Ports off flag */
#define SVMPD_L             (0x0010u)  /* SYS - Incoming JTAG Mailbox 0 Flag */
#define SVMEN_L             (0x0020u)  /* SYS - SVM based port disable */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSCNF Control Bits */
//#define RESERVED            (0x0001u)  /* SYS - Reserved */
//#define RESERVED            (0x0002u)  /* SYS - Reserved */
//#define RESERVED            (0x0040u)  /* SYS - Reserved */
//#define RESERVED            (0x0080u)  /* SYS - Reserved */
#define RAMLCK0_H           (0x0001u)  /* SYS - Write lock enable for configuration RAM */
#define RAMLCK1_H           (0x0002u)  /* SYS - Write lock enable for application’s code RAM */
//#define RESERVED            (0x0400u)  /* SYS - Reserved */
//#define RESERVED            (0x0800u)  /* SYS - Reserved */
//#define RESERVED            (0x1000u)  /* SYS - Reserved */
//#define RESERVED            (0x2000u)  /* SYS - Reserved */
//#define RESERVED            (0x4000u)  /* SYS - Reserved */
//#define RESERVED            (0x8000u)  /* SYS - Reserved */

/* SYSUNIV Definitions */
#define SYSUNIV_NONE       (0x0000u)    /* No Interrupt pending */
#define SYSUNIV_NMIIFG     (0x0002u)    /* SYSUNIV : NMIIFG */
#define SYSUNIV_OFIFG      (0x0004u)    /* SYSUNIV : Osc. Fail - OFIFG */
#define SYSUNIV_SYSBERRIV  (0x0006u)    /* SYSUNIV : Bus Error - SYSBERRIV */

/* SYSSNIV Definitions */
#define SYSSNIV_NONE       (0x0000u)    /* No Interrupt pending */
#define SYSSNIV_SVMIFG     (0x0002u)    /* SYSSNIV : SVMLIFG */
#define SYSSNIV_VMAIFG     (0x0004u)    /* SYSSNIV : VMAIFG */
#define SYSSNIV_JMBINIFG   (0x0006u)    /* SYSSNIV : JMBINIFG */
#define SYSSNIV_JMBOUTIFG  (0x0008u)    /* SYSSNIV : JMBOUTIFG */

/* SYSRSTIV Definitions */
#define SYSRSTIV_NONE      (0x0000u)    /* No Interrupt pending */
#define SYSRSTIV_BOR       (0x0002u)    /* SYSRSTIV : BOR */
#define SYSRSTIV_SVMBOR    (0x0004u)    /* SYSRSTIV : SVMBOR */
#define SYSRSTIV_RSTNMI    (0x0006u)    /* SYSRSTIV : RST/NMI */
#define SYSRSTIV_DOBOR     (0x0008u)    /* SYSRSTIV : Do BOR */
#define SYSRSTIV_SECYV     (0x000Au)    /* SYSRSTIV : Security violation */
#define SYSRSTIV_DOPOR     (0x000Cu)    /* SYSRSTIV : Do POR */
#define SYSRSTIV_WDTTO     (0x000Eu)    /* SYSRSTIV : WDT Time out */
#define SYSRSTIV_WDTKEY    (0x0010u)    /* SYSRSTIV : WDTKEY violation */
#define SYSRSTIV_CCSKEY    (0x0012u)    /* SYSRSTIV : CCS Key violation */
#define SYSRSTIV_PMMKEY    (0x0014u)    /* SYSRSTIV : PMMKEY violation */
#define SYSRSTIV_PERF      (0x0016u)    /* SYSRSTIV : peripheral/config area fetch */
/************************************************************
* Timer0_A3
************************************************************/
#define __MSP430_HAS_T0A3__           /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T0A3__ 0x0340

#define  TA0CTL_             (0x0340u)  /* Timer0_A3 Control */
DEFW(    TA0CTL            , TA0CTL_)
#define  TA0CCTL0_           (0x0342u)  /* Timer0_A3 Capture/Compare Control 0 */
DEFW(    TA0CCTL0          , TA0CCTL0_)
#define  TA0CCTL1_           (0x0344u)  /* Timer0_A3 Capture/Compare Control 1 */
DEFW(    TA0CCTL1          , TA0CCTL1_)
#define  TA0CCTL2_           (0x0346u)  /* Timer0_A3 Capture/Compare Control 2 */
DEFW(    TA0CCTL2          , TA0CCTL2_)
#define  TA0R_               (0x0350u)  /* Timer0_A3 */
DEFW(    TA0R              , TA0R_)
#define  TA0CCR0_            (0x0352u)  /* Timer0_A3 Capture/Compare 0 */
DEFW(    TA0CCR0           , TA0CCR0_)
#define  TA0CCR1_            (0x0354u)  /* Timer0_A3 Capture/Compare 1 */
DEFW(    TA0CCR1           , TA0CCR1_)
#define  TA0CCR2_            (0x0356u)  /* Timer0_A3 Capture/Compare 2 */
DEFW(    TA0CCR2           , TA0CCR2_)
#define  TA0IV_              (0x036Eu)  /* Timer0_A3 Interrupt Vector Word */
DEFW(    TA0IV             , TA0IV_)
#define  TA0EX0_             (0x0360u)  /* Timer0_A3 Expansion Register 0 */
DEFW(    TA0EX0            , TA0EX0_)

/* TAxCTL Control Bits */
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
#define MC__STOP            (0*0x10u)  /* Timer A mode control: 0 - Stop */
#define MC__UP              (1*0x10u)  /* Timer A mode control: 1 - Up to CCR0 */
#define MC__CONTINOUS       (2*0x10u)  /* Timer A mode control: 2 - Continous up */
#define MC__UPDOWN          (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
#define ID__1               (0*0x40u)  /* Timer A input divider: 0 - /1 */
#define ID__2               (1*0x40u)  /* Timer A input divider: 1 - /2 */
#define ID__4               (2*0x40u)  /* Timer A input divider: 2 - /4 */
#define ID__8               (3*0x40u)  /* Timer A input divider: 3 - /8 */
#define TASSEL__TACLK       (0*0x100u) /* Timer A clock source select: 0 - TACLK */
#define TASSEL__ACLK        (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
#define TASSEL__SMCLK       (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
#define TASSEL__INCLK       (3*0x100u) /* Timer A clock source select: 3 - INCLK */

/* TAxCCTLx Control Bits */
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

/* TAxEX0 Control Bits */
#define TAIDEX0             (0x0001u)  /* Timer A Input divider expansion Bit: 0 */
#define TAIDEX1             (0x0002u)  /* Timer A Input divider expansion Bit: 1 */
#define TAIDEX2             (0x0004u)  /* Timer A Input divider expansion Bit: 2 */

#define TAIDEX_0            (0*0x0001u) /* Timer A Input divider expansion : /1 */
#define TAIDEX_1            (1*0x0001u) /* Timer A Input divider expansion : /2 */
#define TAIDEX_2            (2*0x0001u) /* Timer A Input divider expansion : /3 */
#define TAIDEX_3            (3*0x0001u) /* Timer A Input divider expansion : /4 */
#define TAIDEX_4            (4*0x0001u) /* Timer A Input divider expansion : /5 */
#define TAIDEX_5            (5*0x0001u) /* Timer A Input divider expansion : /6 */
#define TAIDEX_6            (6*0x0001u) /* Timer A Input divider expansion : /7 */
#define TAIDEX_7            (7*0x0001u) /* Timer A Input divider expansion : /8 */

/* T0A3IV Definitions */
#define TA0IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA0IV_TA0CCR1       (0x0002u)    /* TA0CCR1_CCIFG */
#define TA0IV_TA0CCR2       (0x0004u)    /* TA0CCR2_CCIFG */
#define TA0IV_3             (0x0006u)    /* Reserved */
#define TA0IV_4             (0x0008u)    /* Reserved */
#define TA0IV_5             (0x000Au)    /* Reserved */
#define TA0IV_6             (0x000Cu)    /* Reserved */
#define TA0IV_TA0IFG        (0x000Eu)    /* TA0IFG */

/************************************************************
* Timer1_A3
************************************************************/
#define __MSP430_HAS_T1A3__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T1A3__ 0x0380

#define  TA1CTL_             (0x0380u)  /* Timer1_A3 Control */
DEFW(    TA1CTL            , TA1CTL_)
#define  TA1CCTL0_           (0x0382u)  /* Timer1_A3 Capture/Compare Control 0 */
DEFW(    TA1CCTL0          , TA1CCTL0_)
#define  TA1CCTL1_           (0x0384u)  /* Timer1_A3 Capture/Compare Control 1 */
DEFW(    TA1CCTL1          , TA1CCTL1_)
#define  TA1CCTL2_           (0x0386u)  /* Timer1_A3 Capture/Compare Control 2 */
DEFW(    TA1CCTL2          , TA1CCTL2_)
#define  TA1R_               (0x0390u)  /* Timer1_A3 */
DEFW(    TA1R              , TA1R_)
#define  TA1CCR0_            (0x0392u)  /* Timer1_A3 Capture/Compare 0 */
DEFW(    TA1CCR0           , TA1CCR0_)
#define  TA1CCR1_            (0x0394u)  /* Timer1_A3 Capture/Compare 1 */
DEFW(    TA1CCR1           , TA1CCR1_)
#define  TA1CCR2_            (0x0396u)  /* Timer1_A3 Capture/Compare 2 */
DEFW(    TA1CCR2           , TA1CCR2_)
#define  TA1IV_              (0x03AEu)  /* Timer1_A3 Interrupt Vector Word */
DEFW(    TA1IV             , TA1IV_)
#define  TA1EX0_             (0x03A0u)  /* Timer1_A3 Expansion Register 0 */
DEFW(    TA1EX0            , TA1EX0_)

/* Bits are already defined within the Timer0_Ax */

/* TA1IV Definitions */
#define TA1IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TA1IV_TA1CCR1       (0x0002u)    /* TA1CCR1_CCIFG */
#define TA1IV_TA1CCR2       (0x0004u)    /* TA1CCR2_CCIFG */
#define TA1IV_3             (0x0006u)    /* Reserved */
#define TA1IV_4             (0x0008u)    /* Reserved */
#define TA1IV_5             (0x000Au)    /* Reserved */
#define TA1IV_6             (0x000Cu)    /* Reserved */
#define TA1IV_TA1IFG        (0x000Eu)    /* TA1IFG */

/************************************************************
* WATCHDOG TIMER A
************************************************************/
#define __MSP430_HAS_WDT_A__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_WDT_A__ 0x0150

#define  WDTCTL_             (0x015Cu)  /* Watchdog Timer Control */
DEFCW(   WDTCTL            , WDTCTL_)
/* The bit names have been prefixed with "WDT" */
/* WDTCTL Control Bits */
#define WDTIS0              (0x0001u)  /* WDT - Timer Interval Select 0 */
#define WDTIS1              (0x0002u)  /* WDT - Timer Interval Select 1 */
#define WDTIS2              (0x0004u)  /* WDT - Timer Interval Select 2 */
#define WDTCNTCL            (0x0008u)  /* WDT - Timer Clear */
#define WDTTMSEL            (0x0010u)  /* WDT - Timer Mode Select */
#define WDTSSEL0            (0x0020u)  /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1            (0x0040u)  /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD             (0x0080u)  /* WDT - Timer hold */

/* WDTCTL Control Bits */
#define WDTIS0_L            (0x0001u)  /* WDT - Timer Interval Select 0 */
#define WDTIS1_L            (0x0002u)  /* WDT - Timer Interval Select 1 */
#define WDTIS2_L            (0x0004u)  /* WDT - Timer Interval Select 2 */
#define WDTCNTCL_L          (0x0008u)  /* WDT - Timer Clear */
#define WDTTMSEL_L          (0x0010u)  /* WDT - Timer Mode Select */
#define WDTSSEL0_L          (0x0020u)  /* WDT - Timer Clock Source Select 0 */
#define WDTSSEL1_L          (0x0040u)  /* WDT - Timer Clock Source Select 1 */
#define WDTHOLD_L           (0x0080u)  /* WDT - Timer hold */

/* WDTCTL Control Bits */

#define WDTPW               (0x5A00u)

#define WDTIS_0           (0*0x0001u)  /* WDT - Timer Interval Select: /2G */
#define WDTIS_1           (1*0x0001u)  /* WDT - Timer Interval Select: /128M */
#define WDTIS_2           (2*0x0001u)  /* WDT - Timer Interval Select: /8192k */
#define WDTIS_3           (3*0x0001u)  /* WDT - Timer Interval Select: /512k */
#define WDTIS_4           (4*0x0001u)  /* WDT - Timer Interval Select: /32k */
#define WDTIS_5           (5*0x0001u)  /* WDT - Timer Interval Select: /8192 */
#define WDTIS_6           (6*0x0001u)  /* WDT - Timer Interval Select: /512 */
#define WDTIS_7           (7*0x0001u)  /* WDT - Timer Interval Select: /64 */
#define WDTIS__2G         (0*0x0001u)  /* WDT - Timer Interval Select: /2G */
#define WDTIS__128M       (1*0x0001u)  /* WDT - Timer Interval Select: /128M */
#define WDTIS__8192K      (2*0x0001u)  /* WDT - Timer Interval Select: /8192k */
#define WDTIS__512K       (3*0x0001u)  /* WDT - Timer Interval Select: /512k */
#define WDTIS__32K        (4*0x0001u)  /* WDT - Timer Interval Select: /32k */
#define WDTIS__8192       (5*0x0001u)  /* WDT - Timer Interval Select: /8192 */
#define WDTIS__512        (6*0x0001u)  /* WDT - Timer Interval Select: /512 */
#define WDTIS__64         (7*0x0001u)  /* WDT - Timer Interval Select: /64 */

#define WDTSSEL_0         (0*0x0020u)  /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL_1         (1*0x0020u)  /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL_2         (2*0x0020u)  /* WDT - Timer Clock Source Select: VLO_CLK */
#define WDTSSEL_3         (3*0x0020u)  /* WDT - Timer Clock Source Select: reserved */
#define WDTSSEL__SMCLK    (0*0x0020u)  /* WDT - Timer Clock Source Select: SMCLK */
#define WDTSSEL__ACLK     (1*0x0020u)  /* WDT - Timer Clock Source Select: ACLK */
#define WDTSSEL__VLO      (2*0x0020u)  /* WDT - Timer Clock Source Select: VLO_CLK */

/* WDT-interval times [1ms] coded with Bits 0-2 */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MDLY_32         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2)                         /* 32ms interval (default) */
#define WDT_MDLY_8          (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS0)                  /* 8ms     " */
#define WDT_MDLY_0_5        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1)                  /* 0.5ms   " */
#define WDT_MDLY_0_064      (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)           /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ADLY_1000       (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0)                /* 1000ms  " */
#define WDT_ADLY_250        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS0)         /* 250ms   " */
#define WDT_ADLY_16         (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1)         /* 16ms    " */
#define WDT_ADLY_1_9        (WDTPW+WDTTMSEL+WDTCNTCL+WDTIS2+WDTSSEL0+WDTIS1+WDTIS0)  /* 1.9ms   " */
/* Watchdog mode -> reset after expired time */
/* WDT is clocked by fSMCLK (assumed 1MHz) */
#define WDT_MRST_32         (WDTPW+WDTCNTCL+WDTIS2)                                  /* 32ms interval (default) */
#define WDT_MRST_8          (WDTPW+WDTCNTCL+WDTIS2+WDTIS0)                           /* 8ms     " */
#define WDT_MRST_0_5        (WDTPW+WDTCNTCL+WDTIS2+WDTIS1)                           /* 0.5ms   " */
#define WDT_MRST_0_064      (WDTPW+WDTCNTCL+WDTIS2+WDTIS1+WDTIS0)                    /* 0.064ms " */
/* WDT is clocked by fACLK (assumed 32KHz) */
#define WDT_ARST_1000       (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2)                         /* 1000ms  " */
#define WDT_ARST_250        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS0)                  /* 250ms   " */
#define WDT_ARST_16         (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1)                  /* 16ms    " */
#define WDT_ARST_1_9        (WDTPW+WDTCNTCL+WDTSSEL0+WDTIS2+WDTIS1+WDTIS0)           /* 1.9ms   " */


/************************************************************
* Interrupt Vectors (offset from 0xFFFF - 0x20)
************************************************************/


#define PORT2_VECTOR        (5 * 2u)  /* 0xFFEA Port 2 */
#define TIMER0_A1_VECTOR    (6 * 2u)  /* 0xFFEC Timer0_A3 CC1-2, TA1 */
#define TIMER0_A0_VECTOR    (7 * 2u)  /* 0xFFEE Timer0_A3 CC0 */
#define PORT1_VECTOR        (8 * 2u)  /* 0xFFF0 Port 1 */
#define APOOL_VECTOR        (9 * 2u)  /* 0xFFF2 Analog Pool */
#define WDT_VECTOR          (10 * 2u) /* 0xFFF4 Watchdog Timer */
#define TIMER1_A1_VECTOR    (11 * 2u) /* 0xFFF6 Timer1_A5 CC1-4, TA */
#define TIMER1_A0_VECTOR    (12 * 2u) /* 0xFFF8 Timer1_A5 CC0 */
#define UNMI_VECTOR         (13 * 2u) /* 0xFFFA User Non-maskable */
#define SYSNMI_VECTOR       (14 * 2u) /* 0xFFFC System Non-maskable */
#define RESET_VECTOR        (15 * 2u) /* 0xFFFE Reset [Highest Priority] */

/************************************************************
* End of Modules
************************************************************/
#pragma language=default

#endif /* #ifndef __msp430x09x */

