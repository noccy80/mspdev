/********************************************************************
*
* Standard register and bit definitions for the Texas Instruments
* MSP430 microcontroller.
*
* This file supports assembler and C development for
* MSP430FR5720 devices.
*
* Texas Instruments, Version 1.1
*
* Rev. 1.0, Setup
* Rev. 1.1  Fixed definition of RTCTEV__0000 and RTCTEV__1200
*           Removed not availabe bits RTCMODE and RTCSSELx
*           Added PxSELC registers
*
*
********************************************************************/

#ifndef __MSP430FR5720
#define __MSP430FR5720

#define __MSP430_HEADER_VERSION__ 1059

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error msp430fr5720.h file for use with ICC430/A430 only
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
* ADC10_B
************************************************************/
#define __MSP430_HAS_ADC10_B__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_ADC10_B__ 0x0700

#define ADC10CTL0_          (0x0700u)  /* ADC10 Control 0 */
DEFCW(  ADC10CTL0         , ADC10CTL0_)
#define ADC10CTL1_          (0x0702u)  /* ADC10 Control 1 */
DEFCW(  ADC10CTL1         , ADC10CTL1_)
#define ADC10CTL2_          (0x0704u)  /* ADC10 Control 2 */
DEFCW(  ADC10CTL2         , ADC10CTL2_)
#define ADC10LO_            (0x0706u)  /* ADC10 Window Comparator High Threshold */
DEFCW(  ADC10LO           , ADC10LO_)
#define ADC10HI_            (0x0708u)  /* ADC10 Window Comparator High Threshold */
DEFCW(  ADC10HI           , ADC10HI_)
#define ADC10MCTL0_         (0x070Au)  /* ADC10 Memory Control 0 */
DEFCW(  ADC10MCTL0        , ADC10MCTL0_)
#define ADC10MEM0_          (0x0712u)  /* ADC10 Conversion Memory 0 */
DEFCW(  ADC10MEM0         , ADC10MEM0_)
#define ADC10IE_            (0x071Au)  /* ADC10 Interrupt Enable */
DEFCW(  ADC10IE           , ADC10IE_)
#define ADC10IFG_           (0x071Cu)  /* ADC10 Interrupt Flag */
DEFCW(  ADC10IFG          , ADC10IFG_)
#define ADC10IV_            (0x071Eu)  /* ADC10 Interrupt Vector Word */
DEFCW(  ADC10IV           , ADC10IV_)

/* ADC10CTL0 Control Bits */
#define ADC10SC             (0x0001u)  /* ADC10 Start Conversion */
#define ADC10ENC            (0x0002u)  /* ADC10 Enable Conversion */
#define ADC10ON             (0x0010u)  /* ADC10 On/enable */
#define ADC10MSC            (0x0080u)  /* ADC10 Multiple SampleConversion */
#define ADC10SHT0           (0x0100u)  /* ADC10 Sample Hold Select Bit: 0 */
#define ADC10SHT1           (0x0200u)  /* ADC10 Sample Hold Select Bit: 1 */
#define ADC10SHT2           (0x0400u)  /* ADC10 Sample Hold Select Bit: 2 */
#define ADC10SHT3           (0x0800u)  /* ADC10 Sample Hold Select Bit: 3 */

/* ADC10CTL0 Control Bits */
#define ADC10SC_L           (0x0001u)  /* ADC10 Start Conversion */
#define ADC10ENC_L          (0x0002u)  /* ADC10 Enable Conversion */
#define ADC10ON_L           (0x0010u)  /* ADC10 On/enable */
#define ADC10MSC_L          (0x0080u)  /* ADC10 Multiple SampleConversion */

/* ADC10CTL0 Control Bits */
#define ADC10SHT0_H         (0x0001u)  /* ADC10 Sample Hold Select Bit: 0 */
#define ADC10SHT1_H         (0x0002u)  /* ADC10 Sample Hold Select Bit: 1 */
#define ADC10SHT2_H         (0x0004u)  /* ADC10 Sample Hold Select Bit: 2 */
#define ADC10SHT3_H         (0x0008u)  /* ADC10 Sample Hold Select Bit: 3 */

#define ADC10SHT_0          (0*0x100u) /* ADC10 Sample Hold Select 0 */
#define ADC10SHT_1          (1*0x100u) /* ADC10 Sample Hold Select 1 */
#define ADC10SHT_2          (2*0x100u) /* ADC10 Sample Hold Select 2 */
#define ADC10SHT_3          (3*0x100u) /* ADC10 Sample Hold Select 3 */
#define ADC10SHT_4          (4*0x100u) /* ADC10 Sample Hold Select 4 */
#define ADC10SHT_5          (5*0x100u) /* ADC10 Sample Hold Select 5 */
#define ADC10SHT_6          (6*0x100u) /* ADC10 Sample Hold Select 6 */
#define ADC10SHT_7          (7*0x100u) /* ADC10 Sample Hold Select 7 */
#define ADC10SHT_8          (8*0x100u) /* ADC10 Sample Hold Select 8 */
#define ADC10SHT_9          (9*0x100u) /* ADC10 Sample Hold Select 9 */
#define ADC10SHT_10         (10*0x100u) /* ADC10 Sample Hold Select 10 */
#define ADC10SHT_11         (11*0x100u) /* ADC10 Sample Hold Select 11 */
#define ADC10SHT_12         (12*0x100u) /* ADC10 Sample Hold Select 12 */
#define ADC10SHT_13         (13*0x100u) /* ADC10 Sample Hold Select 13 */
#define ADC10SHT_14         (14*0x100u) /* ADC10 Sample Hold Select 14 */
#define ADC10SHT_15         (15*0x100u) /* ADC10 Sample Hold Select 15 */

/* ADC10CTL1 Control Bits */
#define ADC10BUSY           (0x0001u)    /* ADC10 Busy */
#define ADC10CONSEQ0        (0x0002u)    /* ADC10 Conversion Sequence Select 0 */
#define ADC10CONSEQ1        (0x0004u)    /* ADC10 Conversion Sequence Select 1 */
#define ADC10SSEL0          (0x0008u)    /* ADC10 Clock Source Select 0 */
#define ADC10SSEL1          (0x0010u)    /* ADC10 Clock Source Select 1 */
#define ADC10DIV0           (0x0020u)    /* ADC10 Clock Divider Select 0 */
#define ADC10DIV1           (0x0040u)    /* ADC10 Clock Divider Select 1 */
#define ADC10DIV2           (0x0080u)    /* ADC10 Clock Divider Select 2 */
#define ADC10ISSH           (0x0100u)    /* ADC10 Invert Sample Hold Signal */
#define ADC10SHP            (0x0200u)    /* ADC10 Sample/Hold Pulse Mode */
#define ADC10SHS0           (0x0400u)    /* ADC10 Sample/Hold Source 0 */
#define ADC10SHS1           (0x0800u)    /* ADC10 Sample/Hold Source 1 */

/* ADC10CTL1 Control Bits */
#define ADC10BUSY_L         (0x0001u)    /* ADC10 Busy */
#define ADC10CONSEQ0_L      (0x0002u)    /* ADC10 Conversion Sequence Select 0 */
#define ADC10CONSEQ1_L      (0x0004u)    /* ADC10 Conversion Sequence Select 1 */
#define ADC10SSEL0_L        (0x0008u)    /* ADC10 Clock Source Select 0 */
#define ADC10SSEL1_L        (0x0010u)    /* ADC10 Clock Source Select 1 */
#define ADC10DIV0_L         (0x0020u)    /* ADC10 Clock Divider Select 0 */
#define ADC10DIV1_L         (0x0040u)    /* ADC10 Clock Divider Select 1 */
#define ADC10DIV2_L         (0x0080u)    /* ADC10 Clock Divider Select 2 */

/* ADC10CTL1 Control Bits */
#define ADC10ISSH_H         (0x0001u)    /* ADC10 Invert Sample Hold Signal */
#define ADC10SHP_H          (0x0002u)    /* ADC10 Sample/Hold Pulse Mode */
#define ADC10SHS0_H         (0x0004u)    /* ADC10 Sample/Hold Source 0 */
#define ADC10SHS1_H         (0x0008u)    /* ADC10 Sample/Hold Source 1 */

#define ADC10CONSEQ_0        (0*2u)      /* ADC10 Conversion Sequence Select: 0 */
#define ADC10CONSEQ_1        (1*2u)      /* ADC10 Conversion Sequence Select: 1 */
#define ADC10CONSEQ_2        (2*2u)      /* ADC10 Conversion Sequence Select: 2 */
#define ADC10CONSEQ_3        (3*2u)      /* ADC10 Conversion Sequence Select: 3 */

#define ADC10SSEL_0          (0*8u)      /* ADC10 Clock Source Select: 0 */
#define ADC10SSEL_1          (1*8u)      /* ADC10 Clock Source Select: 1 */
#define ADC10SSEL_2          (2*8u)      /* ADC10 Clock Source Select: 2 */
#define ADC10SSEL_3          (3*8u)      /* ADC10 Clock Source Select: 3 */

#define ADC10DIV_0           (0*0x20u)   /* ADC10 Clock Divider Select: 0 */
#define ADC10DIV_1           (1*0x20u)   /* ADC10 Clock Divider Select: 1 */
#define ADC10DIV_2           (2*0x20u)   /* ADC10 Clock Divider Select: 2 */
#define ADC10DIV_3           (3*0x20u)   /* ADC10 Clock Divider Select: 3 */
#define ADC10DIV_4           (4*0x20u)   /* ADC10 Clock Divider Select: 4 */
#define ADC10DIV_5           (5*0x20u)   /* ADC10 Clock Divider Select: 5 */
#define ADC10DIV_6           (6*0x20u)   /* ADC10 Clock Divider Select: 6 */
#define ADC10DIV_7           (7*0x20u)   /* ADC10 Clock Divider Select: 7 */

#define ADC10SHS_0           (0*0x400u)  /* ADC10 Sample/Hold Source: 0 */
#define ADC10SHS_1           (1*0x400u)  /* ADC10 Sample/Hold Source: 1 */
#define ADC10SHS_2           (2*0x400u)  /* ADC10 Sample/Hold Source: 2 */
#define ADC10SHS_3           (3*0x400u)  /* ADC10 Sample/Hold Source: 3 */

/* ADC10CTL2 Control Bits */
#define ADC10REFBURST       (0x0001u)    /* ADC10 Reference Burst */
#define ADC10SR             (0x0004u)    /* ADC10 Sampling Rate */
#define ADC10DF             (0x0008u)    /* ADC10 Data Format */
#define ADC10RES            (0x0010u)    /* ADC10 Resolution Bit */
#define ADC10PDIV0          (0x0100u)    /* ADC10 predivider Bit: 0 */
#define ADC10PDIV1          (0x0200u)    /* ADC10 predivider Bit: 1 */

/* ADC10CTL2 Control Bits */
#define ADC10REFBURST_L     (0x0001u)    /* ADC10 Reference Burst */
#define ADC10SR_L           (0x0004u)    /* ADC10 Sampling Rate */
#define ADC10DF_L           (0x0008u)    /* ADC10 Data Format */
#define ADC10RES_L          (0x0010u)    /* ADC10 Resolution Bit */

/* ADC10CTL2 Control Bits */
#define ADC10PDIV0_H        (0x0001u)    /* ADC10 predivider Bit: 0 */
#define ADC10PDIV1_H        (0x0002u)    /* ADC10 predivider Bit: 1 */

#define ADC10PDIV_0         (0x0000u)    /* ADC10 predivider /1 */
#define ADC10PDIV_1         (0x0100u)    /* ADC10 predivider /2 */
#define ADC10PDIV_2         (0x0200u)    /* ADC10 predivider /64 */
#define ADC10PDIV_3         (0x0300u)    /* ADC10 predivider reserved */

#define ADC10PDIV__1        (0x0000u)    /* ADC10 predivider /1 */
#define ADC10PDIV__4        (0x0100u)    /* ADC10 predivider /2 */
#define ADC10PDIV__64       (0x0200u)    /* ADC10 predivider /64 */

/* ADC10MCTL0 Control Bits */
#define ADC10INCH0          (0x0001u)    /* ADC10 Input Channel Select Bit 0 */
#define ADC10INCH1          (0x0002u)    /* ADC10 Input Channel Select Bit 1 */
#define ADC10INCH2          (0x0004u)    /* ADC10 Input Channel Select Bit 2 */
#define ADC10INCH3          (0x0008u)    /* ADC10 Input Channel Select Bit 3 */
#define ADC10SREF0          (0x0010u)    /* ADC10 Select Reference Bit 0 */
#define ADC10SREF1          (0x0020u)    /* ADC10 Select Reference Bit 1 */
#define ADC10SREF2          (0x0040u)    /* ADC10 Select Reference Bit 2 */

/* ADC10MCTL0 Control Bits */
#define ADC10INCH0_L        (0x0001u)    /* ADC10 Input Channel Select Bit 0 */
#define ADC10INCH1_L        (0x0002u)    /* ADC10 Input Channel Select Bit 1 */
#define ADC10INCH2_L        (0x0004u)    /* ADC10 Input Channel Select Bit 2 */
#define ADC10INCH3_L        (0x0008u)    /* ADC10 Input Channel Select Bit 3 */
#define ADC10SREF0_L        (0x0010u)    /* ADC10 Select Reference Bit 0 */
#define ADC10SREF1_L        (0x0020u)    /* ADC10 Select Reference Bit 1 */
#define ADC10SREF2_L        (0x0040u)    /* ADC10 Select Reference Bit 2 */

/* ADC10MCTL0 Control Bits */

#define ADC10INCH_0         (0)         /* ADC10 Input Channel 0 */
#define ADC10INCH_1         (1)         /* ADC10 Input Channel 1 */
#define ADC10INCH_2         (2)         /* ADC10 Input Channel 2 */
#define ADC10INCH_3         (3)         /* ADC10 Input Channel 3 */
#define ADC10INCH_4         (4)         /* ADC10 Input Channel 4 */
#define ADC10INCH_5         (5)         /* ADC10 Input Channel 5 */
#define ADC10INCH_6         (6)         /* ADC10 Input Channel 6 */
#define ADC10INCH_7         (7)         /* ADC10 Input Channel 7 */
#define ADC10INCH_8         (8)         /* ADC10 Input Channel 8 */
#define ADC10INCH_9         (9)         /* ADC10 Input Channel 9 */
#define ADC10INCH_10        (10)        /* ADC10 Input Channel 10 */
#define ADC10INCH_11        (11)        /* ADC10 Input Channel 11 */
#define ADC10INCH_12        (12)        /* ADC10 Input Channel 12 */
#define ADC10INCH_13        (13)        /* ADC10 Input Channel 13 */
#define ADC10INCH_14        (14)        /* ADC10 Input Channel 14 */
#define ADC10INCH_15        (15)        /* ADC10 Input Channel 15 */

#define ADC10SREF_0         (0*0x10u)    /* ADC10 Select Reference 0 */
#define ADC10SREF_1         (1*0x10u)    /* ADC10 Select Reference 1 */
#define ADC10SREF_2         (2*0x10u)    /* ADC10 Select Reference 2 */
#define ADC10SREF_3         (3*0x10u)    /* ADC10 Select Reference 3 */
#define ADC10SREF_4         (4*0x10u)    /* ADC10 Select Reference 4 */
#define ADC10SREF_5         (5*0x10u)    /* ADC10 Select Reference 5 */
#define ADC10SREF_6         (6*0x10u)    /* ADC10 Select Reference 6 */
#define ADC10SREF_7         (7*0x10u)    /* ADC10 Select Reference 7 */

/* ADC10IE Interrupt Enable Bits */
#define ADC10IE0            (0x0001u)    /* ADC10_A Interrupt enable */
#define ADC10INIE           (0x0002u)    /* ADC10_A Interrupt enable for the inside of window of the Window comparator */
#define ADC10LOIE           (0x0004u)    /* ADC10_A Interrupt enable for lower threshold of the Window comparator */
#define ADC10HIIE           (0x0008u)    /* ADC10_A Interrupt enable for upper threshold of the Window comparator */
#define ADC10OVIE           (0x0010u)    /* ADC10_A ADC10MEM overflow Interrupt enable */
#define ADC10TOVIE          (0x0020u)    /* ADC10_A conversion-time-overflow Interrupt enable */

/* ADC10IE Interrupt Enable Bits */
#define ADC10IE0_L          (0x0001u)    /* ADC10_A Interrupt enable */
#define ADC10INIE_L         (0x0002u)    /* ADC10_A Interrupt enable for the inside of window of the Window comparator */
#define ADC10LOIE_L         (0x0004u)    /* ADC10_A Interrupt enable for lower threshold of the Window comparator */
#define ADC10HIIE_L         (0x0008u)    /* ADC10_A Interrupt enable for upper threshold of the Window comparator */
#define ADC10OVIE_L         (0x0010u)    /* ADC10_A ADC10MEM overflow Interrupt enable */
#define ADC10TOVIE_L        (0x0020u)    /* ADC10_A conversion-time-overflow Interrupt enable */

/* ADC10IE Interrupt Enable Bits */

/* ADC10IFG Interrupt Flag Bits */
#define ADC10IFG0           (0x0001u)    /* ADC10_A Interrupt Flag */
#define ADC10INIFG          (0x0002u)    /* ADC10_A Interrupt Flag for the inside of window of the Window comparator */
#define ADC10LOIFG          (0x0004u)    /* ADC10_A Interrupt Flag for lower threshold of the Window comparator */
#define ADC10HIIFG          (0x0008u)    /* ADC10_A Interrupt Flag for upper threshold of the Window comparator */
#define ADC10OVIFG          (0x0010u)    /* ADC10_A ADC10MEM overflow Interrupt Flag */
#define ADC10TOVIFG         (0x0020u)    /* ADC10_A conversion-time-overflow Interrupt Flag */

/* ADC10IFG Interrupt Flag Bits */
#define ADC10IFG0_L         (0x0001u)    /* ADC10_A Interrupt Flag */
#define ADC10INIFG_L        (0x0002u)    /* ADC10_A Interrupt Flag for the inside of window of the Window comparator */
#define ADC10LOIFG_L        (0x0004u)    /* ADC10_A Interrupt Flag for lower threshold of the Window comparator */
#define ADC10HIIFG_L        (0x0008u)    /* ADC10_A Interrupt Flag for upper threshold of the Window comparator */
#define ADC10OVIFG_L        (0x0010u)    /* ADC10_A ADC10MEM overflow Interrupt Flag */
#define ADC10TOVIFG_L       (0x0020u)    /* ADC10_A conversion-time-overflow Interrupt Flag */

/* ADC10IFG Interrupt Flag Bits */

/* ADC10IV Definitions */
#define ADC10IV_NONE        (0x0000u)    /* No Interrupt pending */
#define ADC10IV_ADC10OVIFG  (0x0002u)    /* ADC10OVIFG */
#define ADC10IV_ADC10TOVIFG (0x0004u)    /* ADC10TOVIFG */
#define ADC10IV_ADC10HIIFG  (0x0006u)    /* ADC10HIIFG */
#define ADC10IV_ADC10LOIFG  (0x0008u)    /* ADC10LOIFG */
#define ADC10IV_ADC10INIFG  (0x000Au)    /* ADC10INIFG */
#define ADC10IV_ADC10IFG    (0x000Cu)    /* ADC10IFG */

/************************************************************
* CLOCK SYSTEM
************************************************************/
#define __MSP430_HAS_CS__              /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CS__ 0x0160

#define  CSCTL0_             (0x0160u)  /* CS Control Register 0 */
DEFCW(   CSCTL0            , CSCTL0_)
#define  CSCTL1_             (0x0162u)  /* CS Control Register 1 */
DEFCW(   CSCTL1            , CSCTL1_)
#define  CSCTL2_             (0x0164u)  /* CS Control Register 2 */
DEFCW(   CSCTL2            , CSCTL2_)
#define  CSCTL3_             (0x0166u)  /* CS Control Register 3 */
DEFCW(   CSCTL3            , CSCTL3_)
#define  CSCTL4_             (0x0168u)  /* CS Control Register 4 */
DEFCW(   CSCTL4            , CSCTL4_)
#define  CSCTL5_             (0x016Au)  /* CS Control Register 5 */
DEFCW(   CSCTL5            , CSCTL5_)
#define  CSCTL6_             (0x016Cu)  /* CS Control Register 6 */
DEFCW(   CSCTL6            , CSCTL6_)

/* CSCTL0 Control Bits */

/* CSCTL0 Control Bits */

/* CSCTL0 Control Bits */
#define CSKEY                (0xA500u)    /* CS Password */

/* CSCTL1 Control Bits */
#define DCOFSEL0            (0x0002u)    /* DCO frequency select Bit: 0 */
#define DCOFSEL1            (0x0004u)    /* DCO frequency select Bit: 1 */
#define DCORSEL             (0x0080u)    /* DCO range select. */

/* CSCTL1 Control Bits */
#define DCOFSEL0_L          (0x0002u)    /* DCO frequency select Bit: 0 */
#define DCOFSEL1_L          (0x0004u)    /* DCO frequency select Bit: 1 */
#define DCORSEL_L           (0x0080u)    /* DCO range select. */

/* CSCTL1 Control Bits */

#define DCOFSEL_0           (0x0000u)    /* DCO frequency select: 0 */
#define DCOFSEL_1           (0x0002u)    /* DCO frequency select: 1 */
#define DCOFSEL_2           (0x0004u)    /* DCO frequency select: 2 */
#define DCOFSEL_3           (0x0006u)    /* DCO frequency select: 3 */

/* CSCTL2 Control Bits */
#define SELM0               (0x0001u)   /* MCLK Source Select Bit: 0 */
#define SELM1               (0x0002u)   /* MCLK Source Select Bit: 1 */
#define SELM2               (0x0004u)   /* MCLK Source Select Bit: 2 */
//#define RESERVED            (0x0004u)    /* RESERVED */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define SELS0               (0x0010u)   /* SMCLK Source Select Bit: 0 */
#define SELS1               (0x0020u)   /* SMCLK Source Select Bit: 1 */
#define SELS2               (0x0040u)   /* SMCLK Source Select Bit: 2 */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
#define SELA0               (0x0100u)   /* ACLK Source Select Bit: 0 */
#define SELA1               (0x0200u)   /* ACLK Source Select Bit: 1 */
#define SELA2               (0x0400u)   /* ACLK Source Select Bit: 2 */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* CSCTL2 Control Bits */
#define SELM0_L             (0x0001u)   /* MCLK Source Select Bit: 0 */
#define SELM1_L             (0x0002u)   /* MCLK Source Select Bit: 1 */
#define SELM2_L             (0x0004u)   /* MCLK Source Select Bit: 2 */
//#define RESERVED            (0x0004u)    /* RESERVED */
//#define RESERVED            (0x0008u)    /* RESERVED */
#define SELS0_L             (0x0010u)   /* SMCLK Source Select Bit: 0 */
#define SELS1_L             (0x0020u)   /* SMCLK Source Select Bit: 1 */
#define SELS2_L             (0x0040u)   /* SMCLK Source Select Bit: 2 */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
//#define RESERVED            (0x0400u)    /* RESERVED */
//#define RESERVED            (0x0800u)    /* RESERVED */
//#define RESERVED            (0x1000u)    /* RESERVED */
//#define RESERVED            (0x2000u)    /* RESERVED */
//#define RESERVED            (0x4000u)    /* RESERVED */
//#define RESERVED            (0x8000u)    /* RESERVED */

/* CSCTL2 Control Bits */
//#define RESERVED            (0x0004u)    /* RESERVED */
//#define RESERVED            (0x0008u)    /* RESERVED */
//#define RESERVED            (0x0040u)    /* RESERVED */
//#define RESERVED            (0x0080u)    /* RESERVED */
#define SELA0_H             (0x0001u)   /* ACLK Source Select Bit: 0 */
#define SELA1_H             (0x0002u)   /* ACLK Source Select Bit: 1 */
#define SELA2_H             (0x0004u)   /* ACLK Source Select Bit: 2 */
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
#define SELM_4              (0x0004u)   /* MCLK Source Select 4 */
#define SELM_5              (0x0005u)   /* MCLK Source Select 5 */
#define SELM_6              (0x0006u)   /* MCLK Source Select 6 */
#define SELM_7              (0x0007u)   /* MCLK Source Select 7 */
#define SELM__XT1CLK        (0x0000u)   /* MCLK Source Select XT1CLK */
#define SELM__VLOCLK        (0x0001u)   /* MCLK Source Select VLOCLK */
#define SELM__DCOCLK        (0x0003u)   /* MCLK Source Select DCOCLK */
#define SELM__XT2CLK        (0x0005u)   /* MCLK Source Select XT2CLK */

#define SELS_0              (0x0000u)   /* SMCLK Source Select 0 */
#define SELS_1              (0x0010u)   /* SMCLK Source Select 1 */
#define SELS_2              (0x0020u)   /* SMCLK Source Select 2 */
#define SELS_3              (0x0030u)   /* SMCLK Source Select 3 */
#define SELS_4              (0x0040u)   /* SMCLK Source Select 4 */
#define SELS_5              (0x0050u)   /* SMCLK Source Select 5 */
#define SELS_6              (0x0060u)   /* SMCLK Source Select 6 */
#define SELS_7              (0x0070u)   /* SMCLK Source Select 7 */
#define SELS__XT1CLK        (0x0000u)   /* SMCLK Source Select XT1CLK */
#define SELS__VLOCLK        (0x0010u)   /* SMCLK Source Select VLOCLK */
#define SELS__DCOCLK        (0x0030u)   /* SMCLK Source Select DCOCLK */
#define SELS__XT2CLK        (0x0050u)   /* SMCLK Source Select XT2CLK */

#define SELA_0              (0x0000u)   /* ACLK Source Select 0 */
#define SELA_1              (0x0100u)   /* ACLK Source Select 1 */
#define SELA_2              (0x0200u)   /* ACLK Source Select 2 */
#define SELA_3              (0x0300u)   /* ACLK Source Select 3 */
#define SELA_4              (0x0400u)   /* ACLK Source Select 4 */
#define SELA_5              (0x0500u)   /* ACLK Source Select 5 */
#define SELA_6              (0x0600u)   /* ACLK Source Select 6 */
#define SELA_7              (0x0700u)   /* ACLK Source Select 7 */
#define SELA__XT1CLK        (0x0000u)   /* ACLK Source Select XT1CLK */
#define SELA__VLOCLK        (0x0100u)   /* ACLK Source Select VLOCLK */
#define SELA__DCOCLK        (0x0300u)   /* ACLK Source Select DCOCLK */
#define SELA__XT2CLK        (0x0500u)   /* ACLK Source Select XT2CLK */

/* CSCTL3 Control Bits */
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

/* CSCTL3 Control Bits */
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

/* CSCTL3 Control Bits */
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

/* CSCTL4 Control Bits */
#define XT1OFF              (0x0001u)    /* High Frequency Oscillator 1 (XT1) disable */
#define SMCLKOFF            (0x0002u)    /* SMCLK Off */
#define XT1BYPASS           (0x0010u)    /* XT1 bypass mode : 0: internal 1:sourced from external pin */
#define XTS                 (0x0020u)    /* 1: Selects high-freq. oscillator */
#define XT1DRIVE0           (0x0040u)    /* XT1 Drive Level mode Bit 0 */
#define XT1DRIVE1           (0x0080u)    /* XT1 Drive Level mode Bit 1 */
#define XT2OFF              (0x0100u)    /* High Frequency Oscillator 2 (XT2) disable */
#define XT2BYPASS           (0x1000u)    /* XT2 bypass mode : 0: internal 1:sourced from external pin */
#define XT2DRIVE0           (0x4000u)    /* XT2 Drive Level mode Bit 0 */
#define XT2DRIVE1           (0x8000u)    /* XT2 Drive Level mode Bit 1 */

/* CSCTL4 Control Bits */
#define XT1OFF_L            (0x0001u)    /* High Frequency Oscillator 1 (XT1) disable */
#define SMCLKOFF_L          (0x0002u)    /* SMCLK Off */
#define XT1BYPASS_L         (0x0010u)    /* XT1 bypass mode : 0: internal 1:sourced from external pin */
#define XTS_L               (0x0020u)    /* 1: Selects high-freq. oscillator */
#define XT1DRIVE0_L         (0x0040u)    /* XT1 Drive Level mode Bit 0 */
#define XT1DRIVE1_L         (0x0080u)    /* XT1 Drive Level mode Bit 1 */

/* CSCTL4 Control Bits */
#define XT2OFF_H            (0x0001u)    /* High Frequency Oscillator 2 (XT2) disable */
#define XT2BYPASS_H         (0x0010u)    /* XT2 bypass mode : 0: internal 1:sourced from external pin */
#define XT2DRIVE0_H         (0x0040u)    /* XT2 Drive Level mode Bit 0 */
#define XT2DRIVE1_H         (0x0080u)    /* XT2 Drive Level mode Bit 1 */

#define XT1DRIVE_0          (0x0000u)    /* XT1 Drive Level mode: 0 */
#define XT1DRIVE_1          (0x0040u)    /* XT1 Drive Level mode: 1 */
#define XT1DRIVE_2          (0x0080u)    /* XT1 Drive Level mode: 2 */
#define XT1DRIVE_3          (0x00C0u)    /* XT1 Drive Level mode: 3 */
#define XT2DRIVE_0          (0x0000u)    /* XT2 Drive Level mode: 0 */
#define XT2DRIVE_1          (0x4000u)    /* XT2 Drive Level mode: 1 */
#define XT2DRIVE_2          (0x8000u)    /* XT2 Drive Level mode: 2 */
#define XT2DRIVE_3          (0xC000u)    /* XT2 Drive Level mode: 3 */

/* CSCTL5 Control Bits */
#define XT1OFFG             (0x0001u)    /* XT1 Low Frequency Oscillator Fault Flag */
#define XT2OFFG             (0x0002u)    /* High Frequency Oscillator 2 Fault Flag */
#define ENSTFCNT1           (0x0040u)    /* Enable start counter for XT1 */
#define ENSTFCNT2           (0x0080u)    /* Enable start counter for XT2 */

/* CSCTL5 Control Bits */
#define XT1OFFG_L           (0x0001u)    /* XT1 Low Frequency Oscillator Fault Flag */
#define XT2OFFG_L           (0x0002u)    /* High Frequency Oscillator 2 Fault Flag */
#define ENSTFCNT1_L         (0x0040u)    /* Enable start counter for XT1 */
#define ENSTFCNT2_L         (0x0080u)    /* Enable start counter for XT2 */

/* CSCTL5 Control Bits */

/* CSCTL6 Control Bits */
#define ACLKREQEN           (0x0001u)    /* ACLK Clock Request Enable */
#define MCLKREQEN           (0x0002u)    /* MCLK Clock Request Enable */
#define SMCLKREQEN          (0x0004u)    /* SMCLK Clock Request Enable */
#define MODCLKREQEN         (0x0008u)    /* MODOSC Clock Request Enable */

/* CSCTL6 Control Bits */
#define ACLKREQEN_L         (0x0001u)    /* ACLK Clock Request Enable */
#define MCLKREQEN_L         (0x0002u)    /* MCLK Clock Request Enable */
#define SMCLKREQEN_L        (0x0004u)    /* SMCLK Clock Request Enable */
#define MODCLKREQEN_L       (0x0008u)    /* MODOSC Clock Request Enable */

/* CSCTL6 Control Bits */

/************************************************************
* Comparator D
************************************************************/
#define __MSP430_HAS_COMPD__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_COMPD__ 0x08C0

#define  CDCTL0_             (0x08C0u)  /* Comparator D Control Register 0 */
DEFCW(   CDCTL0            , CDCTL0_)
#define  CDCTL1_             (0x08C2u)  /* Comparator D Control Register 1 */
DEFCW(   CDCTL1            , CDCTL1_)
#define  CDCTL2_             (0x08C4u)  /* Comparator D Control Register 2 */
DEFCW(   CDCTL2            , CDCTL2_)
#define  CDCTL3_             (0x08C6u)  /* Comparator D Control Register 3 */
DEFCW(   CDCTL3            , CDCTL3_)
#define  CDINT_              (0x08CCu)  /* Comparator D Interrupt Register */
DEFCW(   CDINT             , CDINT_)
#define CDIV_               (0x08CEu)  /* Comparator D Interrupt Vector Word */
READ_ONLY_DEFCW( CDIV           , CDIV_)

/* CDCTL0 Control Bits */
#define CDIPSEL0            (0x0001u)  /* Comp. D Pos. Channel Input Select 0 */
#define CDIPSEL1            (0x0002u)  /* Comp. D Pos. Channel Input Select 1 */
#define CDIPSEL2            (0x0004u)  /* Comp. D Pos. Channel Input Select 2 */
#define CDIPSEL3            (0x0008u)  /* Comp. D Pos. Channel Input Select 3 */
//#define RESERVED            (0x0010u)  /* Comp. D */
//#define RESERVED            (0x0020u)  /* Comp. D */
//#define RESERVED            (0x0040u)  /* Comp. D */
#define CDIPEN              (0x0080u)  /* Comp. D Pos. Channel Input Enable */
#define CDIMSEL0            (0x0100u)  /* Comp. D Neg. Channel Input Select 0 */
#define CDIMSEL1            (0x0200u)  /* Comp. D Neg. Channel Input Select 1 */
#define CDIMSEL2            (0x0400u)  /* Comp. D Neg. Channel Input Select 2 */
#define CDIMSEL3            (0x0800u)  /* Comp. D Neg. Channel Input Select 3 */
//#define RESERVED            (0x1000u)  /* Comp. D */
//#define RESERVED            (0x2000u)  /* Comp. D */
//#define RESERVED            (0x4000u)  /* Comp. D */
#define CDIMEN              (0x8000u)  /* Comp. D Neg. Channel Input Enable */

/* CDCTL0 Control Bits */
#define CDIPSEL0_L          (0x0001u)  /* Comp. D Pos. Channel Input Select 0 */
#define CDIPSEL1_L          (0x0002u)  /* Comp. D Pos. Channel Input Select 1 */
#define CDIPSEL2_L          (0x0004u)  /* Comp. D Pos. Channel Input Select 2 */
#define CDIPSEL3_L          (0x0008u)  /* Comp. D Pos. Channel Input Select 3 */
//#define RESERVED            (0x0010u)  /* Comp. D */
//#define RESERVED            (0x0020u)  /* Comp. D */
//#define RESERVED            (0x0040u)  /* Comp. D */
#define CDIPEN_L            (0x0080u)  /* Comp. D Pos. Channel Input Enable */
//#define RESERVED            (0x1000u)  /* Comp. D */
//#define RESERVED            (0x2000u)  /* Comp. D */
//#define RESERVED            (0x4000u)  /* Comp. D */

/* CDCTL0 Control Bits */
//#define RESERVED            (0x0010u)  /* Comp. D */
//#define RESERVED            (0x0020u)  /* Comp. D */
//#define RESERVED            (0x0040u)  /* Comp. D */
#define CDIMSEL0_H          (0x0001u)  /* Comp. D Neg. Channel Input Select 0 */
#define CDIMSEL1_H          (0x0002u)  /* Comp. D Neg. Channel Input Select 1 */
#define CDIMSEL2_H          (0x0004u)  /* Comp. D Neg. Channel Input Select 2 */
#define CDIMSEL3_H          (0x0008u)  /* Comp. D Neg. Channel Input Select 3 */
//#define RESERVED            (0x1000u)  /* Comp. D */
//#define RESERVED            (0x2000u)  /* Comp. D */
//#define RESERVED            (0x4000u)  /* Comp. D */
#define CDIMEN_H            (0x0080u)  /* Comp. D Neg. Channel Input Enable */

#define CDIPSEL_0           (0x0000u)  /* Comp. D V+ terminal Input Select: Channel 0 */
#define CDIPSEL_1           (0x0001u)  /* Comp. D V+ terminal Input Select: Channel 1 */
#define CDIPSEL_2           (0x0002u)  /* Comp. D V+ terminal Input Select: Channel 2 */
#define CDIPSEL_3           (0x0003u)  /* Comp. D V+ terminal Input Select: Channel 3 */
#define CDIPSEL_4           (0x0004u)  /* Comp. D V+ terminal Input Select: Channel 4 */
#define CDIPSEL_5           (0x0005u)  /* Comp. D V+ terminal Input Select: Channel 5 */
#define CDIPSEL_6           (0x0006u)  /* Comp. D V+ terminal Input Select: Channel 6 */
#define CDIPSEL_7           (0x0007u)  /* Comp. D V+ terminal Input Select: Channel 7 */
#define CDIPSEL_8           (0x0008u)  /* Comp. D V+ terminal Input Select: Channel 8 */
#define CDIPSEL_9           (0x0009u)  /* Comp. D V+ terminal Input Select: Channel 9 */
#define CDIPSEL_10          (0x000Au)  /* Comp. D V+ terminal Input Select: Channel 10 */
#define CDIPSEL_11          (0x000Bu)  /* Comp. D V+ terminal Input Select: Channel 11 */
#define CDIPSEL_12          (0x000Cu)  /* Comp. D V+ terminal Input Select: Channel 12 */
#define CDIPSEL_13          (0x000Du)  /* Comp. D V+ terminal Input Select: Channel 13 */
#define CDIPSEL_14          (0x000Eu)  /* Comp. D V+ terminal Input Select: Channel 14 */
#define CDIPSEL_15          (0x000Fu)  /* Comp. D V+ terminal Input Select: Channel 15 */

#define CDIMSEL_0           (0x0000u)  /* Comp. D V- Terminal Input Select: Channel 0 */
#define CDIMSEL_1           (0x0100u)  /* Comp. D V- Terminal Input Select: Channel 1 */
#define CDIMSEL_2           (0x0200u)  /* Comp. D V- Terminal Input Select: Channel 2 */
#define CDIMSEL_3           (0x0300u)  /* Comp. D V- Terminal Input Select: Channel 3 */
#define CDIMSEL_4           (0x0400u)  /* Comp. D V- Terminal Input Select: Channel 4 */
#define CDIMSEL_5           (0x0500u)  /* Comp. D V- Terminal Input Select: Channel 5 */
#define CDIMSEL_6           (0x0600u)  /* Comp. D V- Terminal Input Select: Channel 6 */
#define CDIMSEL_7           (0x0700u)  /* Comp. D V- Terminal Input Select: Channel 7 */
#define CDIMSEL_8           (0x0800u)  /* Comp. D V- terminal Input Select: Channel 8 */
#define CDIMSEL_9           (0x0900u)  /* Comp. D V- terminal Input Select: Channel 9 */
#define CDIMSEL_10          (0x0A00u)  /* Comp. D V- terminal Input Select: Channel 10 */
#define CDIMSEL_11          (0x0B00u)  /* Comp. D V- terminal Input Select: Channel 11 */
#define CDIMSEL_12          (0x0C00u)  /* Comp. D V- terminal Input Select: Channel 12 */
#define CDIMSEL_13          (0x0D00u)  /* Comp. D V- terminal Input Select: Channel 13 */
#define CDIMSEL_14          (0x0E00u)  /* Comp. D V- terminal Input Select: Channel 14 */
#define CDIMSEL_15          (0x0F00u)  /* Comp. D V- terminal Input Select: Channel 15 */

/* CDCTL1 Control Bits */
#define CDOUT               (0x0001u)  /* Comp. D Output */
#define CDOUTPOL            (0x0002u)  /* Comp. D Output Polarity */
#define CDF                 (0x0004u)  /* Comp. D Enable Output Filter */
#define CDIES               (0x0008u)  /* Comp. D Interrupt Edge Select */
#define CDSHORT             (0x0010u)  /* Comp. D Input Short */
#define CDEX                (0x0020u)  /* Comp. D Exchange Inputs */
#define CDFDLY0             (0x0040u)  /* Comp. D Filter delay Bit 0 */
#define CDFDLY1             (0x0080u)  /* Comp. D Filter delay Bit 1 */
//#define RESERVED            (0x0100u)  /* Comp. D */
//#define RESERVED            (0x0200u)  /* Comp. D */
#define CDON                (0x0400u)  /* Comp. D enable */
#define CDMRVL              (0x0800u)  /* Comp. D CDMRV Level */
#define CDMRVS              (0x1000u)  /* Comp. D Output selects between VREF0 or VREF1*/
//#define RESERVED            (0x2000u)  /* Comp. D */
//#define RESERVED            (0x4000u)  /* Comp. D */
//#define RESERVED            (0x8000u)  /* Comp. D */

/* CDCTL1 Control Bits */
#define CDOUT_L             (0x0001u)  /* Comp. D Output */
#define CDOUTPOL_L          (0x0002u)  /* Comp. D Output Polarity */
#define CDF_L               (0x0004u)  /* Comp. D Enable Output Filter */
#define CDIES_L             (0x0008u)  /* Comp. D Interrupt Edge Select */
#define CDSHORT_L           (0x0010u)  /* Comp. D Input Short */
#define CDEX_L              (0x0020u)  /* Comp. D Exchange Inputs */
#define CDFDLY0_L           (0x0040u)  /* Comp. D Filter delay Bit 0 */
#define CDFDLY1_L           (0x0080u)  /* Comp. D Filter delay Bit 1 */
//#define RESERVED            (0x0100u)  /* Comp. D */
//#define RESERVED            (0x0200u)  /* Comp. D */
//#define RESERVED            (0x2000u)  /* Comp. D */
//#define RESERVED            (0x4000u)  /* Comp. D */
//#define RESERVED            (0x8000u)  /* Comp. D */

/* CDCTL1 Control Bits */
//#define RESERVED            (0x0100u)  /* Comp. D */
//#define RESERVED            (0x0200u)  /* Comp. D */
#define CDON_H              (0x0004u)  /* Comp. D enable */
#define CDMRVL_H            (0x0008u)  /* Comp. D CDMRV Level */
#define CDMRVS_H            (0x0010u)  /* Comp. D Output selects between VREF0 or VREF1*/
//#define RESERVED            (0x2000u)  /* Comp. D */
//#define RESERVED            (0x4000u)  /* Comp. D */
//#define RESERVED            (0x8000u)  /* Comp. D */

#define CDFDLY_0           (0x0000u)  /* Comp. D Filter delay 0 : 450ns */
#define CDFDLY_1           (0x0040u)  /* Comp. D Filter delay 1 : 900ns */
#define CDFDLY_2           (0x0080u)  /* Comp. D Filter delay 2 : 1800ns */
#define CDFDLY_3           (0x00C0u)  /* Comp. D Filter delay 3 : 3600ns */

/* CDCTL2 Control Bits */
#define CDREF00             (0x0001u)  /* Comp. D Reference 0 Resistor Select Bit : 0 */
#define CDREF01             (0x0002u)  /* Comp. D Reference 0 Resistor Select Bit : 1 */
#define CDREF02             (0x0004u)  /* Comp. D Reference 0 Resistor Select Bit : 2 */
#define CDREF03             (0x0008u)  /* Comp. D Reference 0 Resistor Select Bit : 3 */
#define CDREF04             (0x0010u)  /* Comp. D Reference 0 Resistor Select Bit : 4 */
#define CDRSEL              (0x0020u)  /* Comp. D Reference select */
#define CDRS0               (0x0040u)  /* Comp. D Reference Source Bit : 0 */
#define CDRS1               (0x0080u)  /* Comp. D Reference Source Bit : 1 */
#define CDREF10             (0x0100u)  /* Comp. D Reference 1 Resistor Select Bit : 0 */
#define CDREF11             (0x0200u)  /* Comp. D Reference 1 Resistor Select Bit : 1 */
#define CDREF12             (0x0400u)  /* Comp. D Reference 1 Resistor Select Bit : 2 */
#define CDREF13             (0x0800u)  /* Comp. D Reference 1 Resistor Select Bit : 3 */
#define CDREF14             (0x1000u)  /* Comp. D Reference 1 Resistor Select Bit : 4 */
#define CDREFL0             (0x2000u)  /* Comp. D Reference voltage level Bit : 0 */
#define CDREFL1             (0x4000u)  /* Comp. D Reference voltage level Bit : 1 */
#define CDREFACC            (0x8000u)  /* Comp. D Reference Accuracy */

/* CDCTL2 Control Bits */
#define CDREF00_L           (0x0001u)  /* Comp. D Reference 0 Resistor Select Bit : 0 */
#define CDREF01_L           (0x0002u)  /* Comp. D Reference 0 Resistor Select Bit : 1 */
#define CDREF02_L           (0x0004u)  /* Comp. D Reference 0 Resistor Select Bit : 2 */
#define CDREF03_L           (0x0008u)  /* Comp. D Reference 0 Resistor Select Bit : 3 */
#define CDREF04_L           (0x0010u)  /* Comp. D Reference 0 Resistor Select Bit : 4 */
#define CDRSEL_L            (0x0020u)  /* Comp. D Reference select */
#define CDRS0_L             (0x0040u)  /* Comp. D Reference Source Bit : 0 */
#define CDRS1_L             (0x0080u)  /* Comp. D Reference Source Bit : 1 */

/* CDCTL2 Control Bits */
#define CDREF10_H           (0x0001u)  /* Comp. D Reference 1 Resistor Select Bit : 0 */
#define CDREF11_H           (0x0002u)  /* Comp. D Reference 1 Resistor Select Bit : 1 */
#define CDREF12_H           (0x0004u)  /* Comp. D Reference 1 Resistor Select Bit : 2 */
#define CDREF13_H           (0x0008u)  /* Comp. D Reference 1 Resistor Select Bit : 3 */
#define CDREF14_H           (0x0010u)  /* Comp. D Reference 1 Resistor Select Bit : 4 */
#define CDREFL0_H           (0x0020u)  /* Comp. D Reference voltage level Bit : 0 */
#define CDREFL1_H           (0x0040u)  /* Comp. D Reference voltage level Bit : 1 */
#define CDREFACC_H          (0x0080u)  /* Comp. D Reference Accuracy */

#define CDREF0_0            (0x0000u)  /* Comp. D Int. Ref.0 Select 0 : 1/32 */
#define CDREF0_1            (0x0001u)  /* Comp. D Int. Ref.0 Select 1 : 2/32 */
#define CDREF0_2            (0x0002u)  /* Comp. D Int. Ref.0 Select 2 : 3/32 */
#define CDREF0_3            (0x0003u)  /* Comp. D Int. Ref.0 Select 3 : 4/32 */
#define CDREF0_4            (0x0004u)  /* Comp. D Int. Ref.0 Select 4 : 5/32 */
#define CDREF0_5            (0x0005u)  /* Comp. D Int. Ref.0 Select 5 : 6/32 */
#define CDREF0_6            (0x0006u)  /* Comp. D Int. Ref.0 Select 6 : 7/32 */
#define CDREF0_7            (0x0007u)  /* Comp. D Int. Ref.0 Select 7 : 8/32 */
#define CDREF0_8            (0x0008u)  /* Comp. D Int. Ref.0 Select 0 : 9/32 */
#define CDREF0_9            (0x0009u)  /* Comp. D Int. Ref.0 Select 1 : 10/32 */
#define CDREF0_10           (0x000Au)  /* Comp. D Int. Ref.0 Select 2 : 11/32 */
#define CDREF0_11           (0x000Bu)  /* Comp. D Int. Ref.0 Select 3 : 12/32 */
#define CDREF0_12           (0x000Cu)  /* Comp. D Int. Ref.0 Select 4 : 13/32 */
#define CDREF0_13           (0x000Du)  /* Comp. D Int. Ref.0 Select 5 : 14/32 */
#define CDREF0_14           (0x000Eu)  /* Comp. D Int. Ref.0 Select 6 : 15/32 */
#define CDREF0_15           (0x000Fu)  /* Comp. D Int. Ref.0 Select 7 : 16/32 */
#define CDREF0_16           (0x0010u)  /* Comp. D Int. Ref.0 Select 0 : 17/32 */
#define CDREF0_17           (0x0011u)  /* Comp. D Int. Ref.0 Select 1 : 18/32 */
#define CDREF0_18           (0x0012u)  /* Comp. D Int. Ref.0 Select 2 : 19/32 */
#define CDREF0_19           (0x0013u)  /* Comp. D Int. Ref.0 Select 3 : 20/32 */
#define CDREF0_20           (0x0014u)  /* Comp. D Int. Ref.0 Select 4 : 21/32 */
#define CDREF0_21           (0x0015u)  /* Comp. D Int. Ref.0 Select 5 : 22/32 */
#define CDREF0_22           (0x0016u)  /* Comp. D Int. Ref.0 Select 6 : 23/32 */
#define CDREF0_23           (0x0017u)  /* Comp. D Int. Ref.0 Select 7 : 24/32 */
#define CDREF0_24           (0x0018u)  /* Comp. D Int. Ref.0 Select 0 : 25/32 */
#define CDREF0_25           (0x0019u)  /* Comp. D Int. Ref.0 Select 1 : 26/32 */
#define CDREF0_26           (0x001Au)  /* Comp. D Int. Ref.0 Select 2 : 27/32 */
#define CDREF0_27           (0x001Bu)  /* Comp. D Int. Ref.0 Select 3 : 28/32 */
#define CDREF0_28           (0x001Cu)  /* Comp. D Int. Ref.0 Select 4 : 29/32 */
#define CDREF0_29           (0x001Du)  /* Comp. D Int. Ref.0 Select 5 : 30/32 */
#define CDREF0_30           (0x001Eu)  /* Comp. D Int. Ref.0 Select 6 : 31/32 */
#define CDREF0_31           (0x001Fu)  /* Comp. D Int. Ref.0 Select 7 : 32/32 */

#define CDRS_0              (0x0000u)  /* Comp. D Reference Source 0 : Off */
#define CDRS_1              (0x0040u)  /* Comp. D Reference Source 1 : Vcc */
#define CDRS_2              (0x0080u)  /* Comp. D Reference Source 2 : Shared Ref. */
#define CDRS_3              (0x00C0u)  /* Comp. D Reference Source 3 : Shared Ref. / Off */

#define CDREF1_0            (0x0000u)  /* Comp. D Int. Ref.1 Select 0 : 1/32 */
#define CDREF1_1            (0x0100u)  /* Comp. D Int. Ref.1 Select 1 : 2/32 */
#define CDREF1_2            (0x0200u)  /* Comp. D Int. Ref.1 Select 2 : 3/32 */
#define CDREF1_3            (0x0300u)  /* Comp. D Int. Ref.1 Select 3 : 4/32 */
#define CDREF1_4            (0x0400u)  /* Comp. D Int. Ref.1 Select 4 : 5/32 */
#define CDREF1_5            (0x0500u)  /* Comp. D Int. Ref.1 Select 5 : 6/32 */
#define CDREF1_6            (0x0600u)  /* Comp. D Int. Ref.1 Select 6 : 7/32 */
#define CDREF1_7            (0x0700u)  /* Comp. D Int. Ref.1 Select 7 : 8/32 */
#define CDREF1_8            (0x0800u)  /* Comp. D Int. Ref.1 Select 0 : 9/32 */
#define CDREF1_9            (0x0900u)  /* Comp. D Int. Ref.1 Select 1 : 10/32 */
#define CDREF1_10           (0x0A00u)  /* Comp. D Int. Ref.1 Select 2 : 11/32 */
#define CDREF1_11           (0x0B00u)  /* Comp. D Int. Ref.1 Select 3 : 12/32 */
#define CDREF1_12           (0x0C00u)  /* Comp. D Int. Ref.1 Select 4 : 13/32 */
#define CDREF1_13           (0x0D00u)  /* Comp. D Int. Ref.1 Select 5 : 14/32 */
#define CDREF1_14           (0x0E00u)  /* Comp. D Int. Ref.1 Select 6 : 15/32 */
#define CDREF1_15           (0x0F00u)  /* Comp. D Int. Ref.1 Select 7 : 16/32 */
#define CDREF1_16           (0x1000u)  /* Comp. D Int. Ref.1 Select 0 : 17/32 */
#define CDREF1_17           (0x1100u)  /* Comp. D Int. Ref.1 Select 1 : 18/32 */
#define CDREF1_18           (0x1200u)  /* Comp. D Int. Ref.1 Select 2 : 19/32 */
#define CDREF1_19           (0x1300u)  /* Comp. D Int. Ref.1 Select 3 : 20/32 */
#define CDREF1_20           (0x1400u)  /* Comp. D Int. Ref.1 Select 4 : 21/32 */
#define CDREF1_21           (0x1500u)  /* Comp. D Int. Ref.1 Select 5 : 22/32 */
#define CDREF1_22           (0x1600u)  /* Comp. D Int. Ref.1 Select 6 : 23/32 */
#define CDREF1_23           (0x1700u)  /* Comp. D Int. Ref.1 Select 7 : 24/32 */
#define CDREF1_24           (0x1800u)  /* Comp. D Int. Ref.1 Select 0 : 25/32 */
#define CDREF1_25           (0x1900u)  /* Comp. D Int. Ref.1 Select 1 : 26/32 */
#define CDREF1_26           (0x1A00u)  /* Comp. D Int. Ref.1 Select 2 : 27/32 */
#define CDREF1_27           (0x1B00u)  /* Comp. D Int. Ref.1 Select 3 : 28/32 */
#define CDREF1_28           (0x1C00u)  /* Comp. D Int. Ref.1 Select 4 : 29/32 */
#define CDREF1_29           (0x1D00u)  /* Comp. D Int. Ref.1 Select 5 : 30/32 */
#define CDREF1_30           (0x1E00u)  /* Comp. D Int. Ref.1 Select 6 : 31/32 */
#define CDREF1_31           (0x1F00u)  /* Comp. D Int. Ref.1 Select 7 : 32/32 */

#define CDREFL_0            (0x0000u)  /* Comp. D Reference voltage level 0 : None */
#define CDREFL_1            (0x2000u)  /* Comp. D Reference voltage level 1 : 1.5V */
#define CDREFL_2            (0x4000u)  /* Comp. D Reference voltage level 2 : 2.0V  */
#define CDREFL_3            (0x6000u)  /* Comp. D Reference voltage level 3 : 2.5V  */

#define CDPD0               (0x0001u)  /* Comp. D Disable Input Buffer of Port Register .0 */
#define CDPD1               (0x0002u)  /* Comp. D Disable Input Buffer of Port Register .1 */
#define CDPD2               (0x0004u)  /* Comp. D Disable Input Buffer of Port Register .2 */
#define CDPD3               (0x0008u)  /* Comp. D Disable Input Buffer of Port Register .3 */
#define CDPD4               (0x0010u)  /* Comp. D Disable Input Buffer of Port Register .4 */
#define CDPD5               (0x0020u)  /* Comp. D Disable Input Buffer of Port Register .5 */
#define CDPD6               (0x0040u)  /* Comp. D Disable Input Buffer of Port Register .6 */
#define CDPD7               (0x0080u)  /* Comp. D Disable Input Buffer of Port Register .7 */
#define CDPD8               (0x0100u)  /* Comp. D Disable Input Buffer of Port Register .8 */
#define CDPD9               (0x0200u)  /* Comp. D Disable Input Buffer of Port Register .9 */
#define CDPD10              (0x0400u)  /* Comp. D Disable Input Buffer of Port Register .10 */
#define CDPD11              (0x0800u)  /* Comp. D Disable Input Buffer of Port Register .11 */
#define CDPD12              (0x1000u)  /* Comp. D Disable Input Buffer of Port Register .12 */
#define CDPD13              (0x2000u)  /* Comp. D Disable Input Buffer of Port Register .13 */
#define CDPD14              (0x4000u)  /* Comp. D Disable Input Buffer of Port Register .14 */
#define CDPD15              (0x8000u)  /* Comp. D Disable Input Buffer of Port Register .15 */

#define CDPD0_L             (0x0001u)  /* Comp. D Disable Input Buffer of Port Register .0 */
#define CDPD1_L             (0x0002u)  /* Comp. D Disable Input Buffer of Port Register .1 */
#define CDPD2_L             (0x0004u)  /* Comp. D Disable Input Buffer of Port Register .2 */
#define CDPD3_L             (0x0008u)  /* Comp. D Disable Input Buffer of Port Register .3 */
#define CDPD4_L             (0x0010u)  /* Comp. D Disable Input Buffer of Port Register .4 */
#define CDPD5_L             (0x0020u)  /* Comp. D Disable Input Buffer of Port Register .5 */
#define CDPD6_L             (0x0040u)  /* Comp. D Disable Input Buffer of Port Register .6 */
#define CDPD7_L             (0x0080u)  /* Comp. D Disable Input Buffer of Port Register .7 */

#define CDPD8_H             (0x0001u)  /* Comp. D Disable Input Buffer of Port Register .8 */
#define CDPD9_H             (0x0002u)  /* Comp. D Disable Input Buffer of Port Register .9 */
#define CDPD10_H            (0x0004u)  /* Comp. D Disable Input Buffer of Port Register .10 */
#define CDPD11_H            (0x0008u)  /* Comp. D Disable Input Buffer of Port Register .11 */
#define CDPD12_H            (0x0010u)  /* Comp. D Disable Input Buffer of Port Register .12 */
#define CDPD13_H            (0x0020u)  /* Comp. D Disable Input Buffer of Port Register .13 */
#define CDPD14_H            (0x0040u)  /* Comp. D Disable Input Buffer of Port Register .14 */
#define CDPD15_H            (0x0080u)  /* Comp. D Disable Input Buffer of Port Register .15 */

/* CDINT Control Bits */
#define CDIFG                (0x0001u)  /* Comp. D Interrupt Flag */
#define CDIIFG               (0x0002u)  /* Comp. D Interrupt Flag Inverted Polarity */
//#define RESERVED             (0x0004u)  /* Comp. D */
//#define RESERVED             (0x0008u)  /* Comp. D */
//#define RESERVED             (0x0010u)  /* Comp. D */
//#define RESERVED             (0x0020u)  /* Comp. D */
//#define RESERVED             (0x0040u)  /* Comp. D */
//#define RESERVED             (0x0080u)  /* Comp. D */
#define CDIE                 (0x0100u)  /* Comp. D Interrupt Enable */
#define CDIIE                (0x0200u)  /* Comp. D Interrupt Enable Inverted Polarity */
//#define RESERVED             (0x0400u)  /* Comp. D */
//#define RESERVED             (0x0800u)  /* Comp. D */
//#define RESERVED             (0x1000u)  /* Comp. D */
//#define RESERVED             (0x2000u)  /* Comp. D */
//#define RESERVED             (0x4000u)  /* Comp. D */
//#define RESERVED             (0x8000u)  /* Comp. D */

/* CDINT Control Bits */
#define CDIFG_L             (0x0001u)  /* Comp. D Interrupt Flag */
#define CDIIFG_L            (0x0002u)  /* Comp. D Interrupt Flag Inverted Polarity */
//#define RESERVED             (0x0004u)  /* Comp. D */
//#define RESERVED             (0x0008u)  /* Comp. D */
//#define RESERVED             (0x0010u)  /* Comp. D */
//#define RESERVED             (0x0020u)  /* Comp. D */
//#define RESERVED             (0x0040u)  /* Comp. D */
//#define RESERVED             (0x0080u)  /* Comp. D */
//#define RESERVED             (0x0400u)  /* Comp. D */
//#define RESERVED             (0x0800u)  /* Comp. D */
//#define RESERVED             (0x1000u)  /* Comp. D */
//#define RESERVED             (0x2000u)  /* Comp. D */
//#define RESERVED             (0x4000u)  /* Comp. D */
//#define RESERVED             (0x8000u)  /* Comp. D */

/* CDINT Control Bits */
//#define RESERVED             (0x0004u)  /* Comp. D */
//#define RESERVED             (0x0008u)  /* Comp. D */
//#define RESERVED             (0x0010u)  /* Comp. D */
//#define RESERVED             (0x0020u)  /* Comp. D */
//#define RESERVED             (0x0040u)  /* Comp. D */
//#define RESERVED             (0x0080u)  /* Comp. D */
#define CDIE_H              (0x0001u)  /* Comp. D Interrupt Enable */
#define CDIIE_H             (0x0002u)  /* Comp. D Interrupt Enable Inverted Polarity */
//#define RESERVED             (0x0400u)  /* Comp. D */
//#define RESERVED             (0x0800u)  /* Comp. D */
//#define RESERVED             (0x1000u)  /* Comp. D */
//#define RESERVED             (0x2000u)  /* Comp. D */
//#define RESERVED             (0x4000u)  /* Comp. D */
//#define RESERVED             (0x8000u)  /* Comp. D */

/* CDIV Definitions */
#define CDIV_NONE           (0x0000u)    /* No Interrupt pending */
#define CDIV_CDIFG          (0x0002u)    /* CDIFG */
#define CDIV_CDIIFG         (0x0004u)    /* CDIIFG */

/*************************************************************
* CRC Module
*************************************************************/
#define __MSP430_HAS_CRC__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_CRC__ 0x0150

#define  CRCDI_              (0x0150u)  /* CRC Data In Register */
DEFCW(   CRCDI             , CRCDI_)
#define  CRCDIRB_            (0x0152u)  /* CRC data in reverse byte Register */
DEFCW(   CRCDIRB           , CRCDIRB_)
#define  CRCINIRES_          (0x0154u)  /* CRC Initialisation Register and Result Register */
DEFCW(   CRCINIRES         , CRCINIRES_)
#define  CRCRESR_            (0x0156u)  /* CRC reverse result Register */
DEFCW(   CRCRESR           , CRCRESR_)

/************************************************************
* DMA_X
************************************************************/
#define __MSP430_HAS_DMAX_3__           /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_DMAX_3__ 0x0500

#define  DMACTL0_            (0x0500u)    /* DMA Module Control 0 */
DEFCW(   DMACTL0           , DMACTL0_)
#define  DMACTL1_            (0x0502u)    /* DMA Module Control 1 */
DEFCW(   DMACTL1           , DMACTL1_)
#define  DMACTL2_            (0x0504u)    /* DMA Module Control 2 */
DEFCW(   DMACTL2           , DMACTL2_)
#define  DMACTL3_            (0x0506u)    /* DMA Module Control 3 */
DEFCW(   DMACTL3           , DMACTL3_)
#define  DMACTL4_            (0x0508u)    /* DMA Module Control 4 */
DEFCW(   DMACTL4           , DMACTL4_)
#define  DMAIV_              (0x050Eu)    /* DMA Interrupt Vector Word */
DEFCW(   DMAIV             , DMAIV_)

#define  DMA0CTL_            (0x0510u)    /* DMA Channel 0 Control */
DEFCW(   DMA0CTL           , DMA0CTL_)
#define  DMA0SA_             (0x0512u)    /* DMA Channel 0 Source Address */
DEFA(    DMA0SA            , DMA0SA_)
#define  DMA0DA_             (0x0516u)    /* DMA Channel 0 Destination Address */
DEFA(    DMA0DA            , DMA0DA_)
#define  DMA0SZ_             (0x051Au)    /* DMA Channel 0 Transfer Size */
DEFW(    DMA0SZ            , DMA0SZ_)

#define  DMA1CTL_            (0x0520u)    /* DMA Channel 1 Control */
DEFCW(   DMA1CTL           , DMA1CTL_)
#define  DMA1SA_             (0x0522u)    /* DMA Channel 1 Source Address */
DEFA(    DMA1SA            , DMA1SA_)
#define  DMA1DA_             (0x0526u)    /* DMA Channel 1 Destination Address */
DEFA(    DMA1DA            , DMA1DA_)
#define  DMA1SZ_             (0x052Au)    /* DMA Channel 1 Transfer Size */
DEFW(    DMA1SZ            , DMA1SZ_)

#define  DMA2CTL_            (0x0530u)    /* DMA Channel 2 Control */
DEFCW(   DMA2CTL           , DMA2CTL_)
#define  DMA2SA_             (0x0532u)    /* DMA Channel 2 Source Address */
DEFA(    DMA2SA            , DMA2SA_)
#define  DMA2DA_             (0x0536u)    /* DMA Channel 2 Destination Address */
DEFA(    DMA2DA            , DMA2DA_)
#define  DMA2SZ_             (0x053Au)    /* DMA Channel 2 Transfer Size */
DEFW(    DMA2SZ            , DMA2SZ_)

/* DMACTL0 Control Bits */
#define DMA0TSEL0           (0x0001u)    /* DMA channel 0 transfer select bit 0 */
#define DMA0TSEL1           (0x0002u)    /* DMA channel 0 transfer select bit 1 */
#define DMA0TSEL2           (0x0004u)    /* DMA channel 0 transfer select bit 2 */
#define DMA0TSEL3           (0x0008u)    /* DMA channel 0 transfer select bit 3 */
#define DMA0TSEL4           (0x0010u)    /* DMA channel 0 transfer select bit 4 */
#define DMA1TSEL0           (0x0100u)    /* DMA channel 1 transfer select bit 0 */
#define DMA1TSEL1           (0x0200u)    /* DMA channel 1 transfer select bit 1 */
#define DMA1TSEL2           (0x0400u)    /* DMA channel 1 transfer select bit 2 */
#define DMA1TSEL3           (0x0800u)    /* DMA channel 1 transfer select bit 3 */
#define DMA1TSEL4           (0x1000u)    /* DMA channel 1 transfer select bit 4 */

/* DMACTL0 Control Bits */
#define DMA0TSEL0_L         (0x0001u)    /* DMA channel 0 transfer select bit 0 */
#define DMA0TSEL1_L         (0x0002u)    /* DMA channel 0 transfer select bit 1 */
#define DMA0TSEL2_L         (0x0004u)    /* DMA channel 0 transfer select bit 2 */
#define DMA0TSEL3_L         (0x0008u)    /* DMA channel 0 transfer select bit 3 */
#define DMA0TSEL4_L         (0x0010u)    /* DMA channel 0 transfer select bit 4 */

/* DMACTL0 Control Bits */
#define DMA1TSEL0_H         (0x0001u)    /* DMA channel 1 transfer select bit 0 */
#define DMA1TSEL1_H         (0x0002u)    /* DMA channel 1 transfer select bit 1 */
#define DMA1TSEL2_H         (0x0004u)    /* DMA channel 1 transfer select bit 2 */
#define DMA1TSEL3_H         (0x0008u)    /* DMA channel 1 transfer select bit 3 */
#define DMA1TSEL4_H         (0x0010u)    /* DMA channel 1 transfer select bit 4 */

/* DMACTL01 Control Bits */
#define DMA2TSEL0           (0x0001u)    /* DMA channel 2 transfer select bit 0 */
#define DMA2TSEL1           (0x0002u)    /* DMA channel 2 transfer select bit 1 */
#define DMA2TSEL2           (0x0004u)    /* DMA channel 2 transfer select bit 2 */
#define DMA2TSEL3           (0x0008u)    /* DMA channel 2 transfer select bit 3 */
#define DMA2TSEL4           (0x0010u)    /* DMA channel 2 transfer select bit 4 */

/* DMACTL01 Control Bits */
#define DMA2TSEL0_L         (0x0001u)    /* DMA channel 2 transfer select bit 0 */
#define DMA2TSEL1_L         (0x0002u)    /* DMA channel 2 transfer select bit 1 */
#define DMA2TSEL2_L         (0x0004u)    /* DMA channel 2 transfer select bit 2 */
#define DMA2TSEL3_L         (0x0008u)    /* DMA channel 2 transfer select bit 3 */
#define DMA2TSEL4_L         (0x0010u)    /* DMA channel 2 transfer select bit 4 */

/* DMACTL01 Control Bits */

/* DMACTL4 Control Bits */
#define ENNMI               (0x0001u)    /* Enable NMI interruption of DMA */
#define ROUNDROBIN          (0x0002u)    /* Round-Robin DMA channel priorities */
#define DMARMWDIS           (0x0004u)    /* Inhibited DMA transfers during read-modify-write CPU operations */

/* DMACTL4 Control Bits */
#define ENNMI_L             (0x0001u)    /* Enable NMI interruption of DMA */
#define ROUNDROBIN_L        (0x0002u)    /* Round-Robin DMA channel priorities */
#define DMARMWDIS_L         (0x0004u)    /* Inhibited DMA transfers during read-modify-write CPU operations */

/* DMACTL4 Control Bits */

/* DMAxCTL Control Bits */
#define DMAREQ              (0x0001u)    /* Initiate DMA transfer with DMATSEL */
#define DMAABORT            (0x0002u)    /* DMA transfer aborted by NMI */
#define DMAIE               (0x0004u)    /* DMA interrupt enable */
#define DMAIFG              (0x0008u)    /* DMA interrupt flag */
#define DMAEN               (0x0010u)    /* DMA enable */
#define DMALEVEL            (0x0020u)    /* DMA level sensitive trigger select */
#define DMASRCBYTE          (0x0040u)    /* DMA source byte */
#define DMADSTBYTE          (0x0080u)    /* DMA destination byte */
#define DMASRCINCR0         (0x0100u)    /* DMA source increment bit 0 */
#define DMASRCINCR1         (0x0200u)    /* DMA source increment bit 1 */
#define DMADSTINCR0         (0x0400u)    /* DMA destination increment bit 0 */
#define DMADSTINCR1         (0x0800u)    /* DMA destination increment bit 1 */
#define DMADT0              (0x1000u)    /* DMA transfer mode bit 0 */
#define DMADT1              (0x2000u)    /* DMA transfer mode bit 1 */
#define DMADT2              (0x4000u)    /* DMA transfer mode bit 2 */

/* DMAxCTL Control Bits */
#define DMAREQ_L            (0x0001u)    /* Initiate DMA transfer with DMATSEL */
#define DMAABORT_L          (0x0002u)    /* DMA transfer aborted by NMI */
#define DMAIE_L             (0x0004u)    /* DMA interrupt enable */
#define DMAIFG_L            (0x0008u)    /* DMA interrupt flag */
#define DMAEN_L             (0x0010u)    /* DMA enable */
#define DMALEVEL_L          (0x0020u)    /* DMA level sensitive trigger select */
#define DMASRCBYTE_L        (0x0040u)    /* DMA source byte */
#define DMADSTBYTE_L        (0x0080u)    /* DMA destination byte */

/* DMAxCTL Control Bits */
#define DMASRCINCR0_H       (0x0001u)    /* DMA source increment bit 0 */
#define DMASRCINCR1_H       (0x0002u)    /* DMA source increment bit 1 */
#define DMADSTINCR0_H       (0x0004u)    /* DMA destination increment bit 0 */
#define DMADSTINCR1_H       (0x0008u)    /* DMA destination increment bit 1 */
#define DMADT0_H            (0x0010u)    /* DMA transfer mode bit 0 */
#define DMADT1_H            (0x0020u)    /* DMA transfer mode bit 1 */
#define DMADT2_H            (0x0040u)    /* DMA transfer mode bit 2 */

#define DMASWDW             (0*0x0040u)  /* DMA transfer: source word to destination word */
#define DMASBDW             (1*0x0040u)  /* DMA transfer: source byte to destination word */
#define DMASWDB             (2*0x0040u)  /* DMA transfer: source word to destination byte */
#define DMASBDB             (3*0x0040u)  /* DMA transfer: source byte to destination byte */

#define DMASRCINCR_0        (0*0x0100u)  /* DMA source increment 0: source address unchanged */
#define DMASRCINCR_1        (1*0x0100u)  /* DMA source increment 1: source address unchanged */
#define DMASRCINCR_2        (2*0x0100u)  /* DMA source increment 2: source address decremented */
#define DMASRCINCR_3        (3*0x0100u)  /* DMA source increment 3: source address incremented */

#define DMADSTINCR_0        (0*0x0400u)  /* DMA destination increment 0: destination address unchanged */
#define DMADSTINCR_1        (1*0x0400u)  /* DMA destination increment 1: destination address unchanged */
#define DMADSTINCR_2        (2*0x0400u)  /* DMA destination increment 2: destination address decremented */
#define DMADSTINCR_3        (3*0x0400u)  /* DMA destination increment 3: destination address incremented */

#define DMADT_0             (0*0x1000u)  /* DMA transfer mode 0: Single transfer */
#define DMADT_1             (1*0x1000u)  /* DMA transfer mode 1: Block transfer */
#define DMADT_2             (2*0x1000u)  /* DMA transfer mode 2: Burst-Block transfer */
#define DMADT_3             (3*0x1000u)  /* DMA transfer mode 3: Burst-Block transfer */
#define DMADT_4             (4*0x1000u)  /* DMA transfer mode 4: Repeated Single transfer */
#define DMADT_5             (5*0x1000u)  /* DMA transfer mode 5: Repeated Block transfer */
#define DMADT_6             (6*0x1000u)  /* DMA transfer mode 6: Repeated Burst-Block transfer */
#define DMADT_7             (7*0x1000u)  /* DMA transfer mode 7: Repeated Burst-Block transfer */

/* DMAIV Definitions */
#define DMAIV_NONE           (0x0000u)    /* No Interrupt pending */
#define DMAIV_DMA0IFG        (0x0002u)    /* DMA0IFG*/
#define DMAIV_DMA1IFG        (0x0004u)    /* DMA1IFG*/
#define DMAIV_DMA2IFG        (0x0006u)    /* DMA2IFG*/

#define DMA0TSEL_0          (0*0x0001u)  /* DMA channel 0 transfer select 0:  DMA_REQ (sw) */
#define DMA0TSEL_1          (1*0x0001u)  /* DMA channel 0 transfer select 1:  */
#define DMA0TSEL_2          (2*0x0001u)  /* DMA channel 0 transfer select 2:  */
#define DMA0TSEL_3          (3*0x0001u)  /* DMA channel 0 transfer select 3:  */
#define DMA0TSEL_4          (4*0x0001u)  /* DMA channel 0 transfer select 4:  */
#define DMA0TSEL_5          (5*0x0001u)  /* DMA channel 0 transfer select 5:  */
#define DMA0TSEL_6          (6*0x0001u)  /* DMA channel 0 transfer select 6:  */
#define DMA0TSEL_7          (7*0x0001u)  /* DMA channel 0 transfer select 7:  */
#define DMA0TSEL_8          (8*0x0001u)  /* DMA channel 0 transfer select 8:  */
#define DMA0TSEL_9          (9*0x0001u)  /* DMA channel 0 transfer select 9:  */
#define DMA0TSEL_10         (10*0x0001u) /* DMA channel 0 transfer select 10: */
#define DMA0TSEL_11         (11*0x0001u) /* DMA channel 0 transfer select 11: */
#define DMA0TSEL_12         (12*0x0001u) /* DMA channel 0 transfer select 12: */
#define DMA0TSEL_13         (13*0x0001u) /* DMA channel 0 transfer select 13: */
#define DMA0TSEL_14         (14*0x0001u) /* DMA channel 0 transfer select 14: */
#define DMA0TSEL_15         (15*0x0001u) /* DMA channel 0 transfer select 15: */
#define DMA0TSEL_16         (16*0x0001u) /* DMA channel 0 transfer select 16: */
#define DMA0TSEL_17         (17*0x0001u) /* DMA channel 0 transfer select 17: */
#define DMA0TSEL_18         (18*0x0001u) /* DMA channel 0 transfer select 18: */
#define DMA0TSEL_19         (19*0x0001u) /* DMA channel 0 transfer select 19: */
#define DMA0TSEL_20         (20*0x0001u) /* DMA channel 0 transfer select 20: */
#define DMA0TSEL_21         (21*0x0001u) /* DMA channel 0 transfer select 21: */
#define DMA0TSEL_22         (22*0x0001u) /* DMA channel 0 transfer select 22: */
#define DMA0TSEL_23         (23*0x0001u) /* DMA channel 0 transfer select 23: */
#define DMA0TSEL_24         (24*0x0001u) /* DMA channel 0 transfer select 24: */
#define DMA0TSEL_25         (25*0x0001u) /* DMA channel 0 transfer select 25: */
#define DMA0TSEL_26         (26*0x0001u) /* DMA channel 0 transfer select 26: */
#define DMA0TSEL_27         (27*0x0001u) /* DMA channel 0 transfer select 27: */
#define DMA0TSEL_28         (28*0x0001u) /* DMA channel 0 transfer select 28: */
#define DMA0TSEL_29         (29*0x0001u) /* DMA channel 0 transfer select 29: */
#define DMA0TSEL_30         (30*0x0001u) /* DMA channel 0 transfer select 30: previous DMA channel DMA2IFG */
#define DMA0TSEL_31         (31*0x0001u) /* DMA channel 0 transfer select 31: ext. Trigger (DMAE0) */

#define DMA1TSEL_0          (0*0x0100u)  /* DMA channel 1 transfer select 0:  DMA_REQ (sw) */
#define DMA1TSEL_1          (1*0x0100u)  /* DMA channel 1 transfer select 1:  */
#define DMA1TSEL_2          (2*0x0100u)  /* DMA channel 1 transfer select 2:  */
#define DMA1TSEL_3          (3*0x0100u)  /* DMA channel 1 transfer select 3:  */
#define DMA1TSEL_4          (4*0x0100u)  /* DMA channel 1 transfer select 4:  */
#define DMA1TSEL_5          (5*0x0100u)  /* DMA channel 1 transfer select 5:  */
#define DMA1TSEL_6          (6*0x0100u)  /* DMA channel 1 transfer select 6:  */
#define DMA1TSEL_7          (7*0x0100u)  /* DMA channel 1 transfer select 7:  */
#define DMA1TSEL_8          (8*0x0100u)  /* DMA channel 1 transfer select 8:  */
#define DMA1TSEL_9          (9*0x0100u)  /* DMA channel 1 transfer select 9:  */
#define DMA1TSEL_10         (10*0x0100u) /* DMA channel 1 transfer select 10: */
#define DMA1TSEL_11         (11*0x0100u) /* DMA channel 1 transfer select 11: */
#define DMA1TSEL_12         (12*0x0100u) /* DMA channel 1 transfer select 12: */
#define DMA1TSEL_13         (13*0x0100u) /* DMA channel 1 transfer select 13: */
#define DMA1TSEL_14         (14*0x0100u) /* DMA channel 1 transfer select 14: */
#define DMA1TSEL_15         (15*0x0100u) /* DMA channel 1 transfer select 15: */
#define DMA1TSEL_16         (16*0x0100u) /* DMA channel 1 transfer select 16: */
#define DMA1TSEL_17         (17*0x0100u) /* DMA channel 1 transfer select 17: */
#define DMA1TSEL_18         (18*0x0100u) /* DMA channel 1 transfer select 18: */
#define DMA1TSEL_19         (19*0x0100u) /* DMA channel 1 transfer select 19: */
#define DMA1TSEL_20         (20*0x0100u) /* DMA channel 1 transfer select 20: */
#define DMA1TSEL_21         (21*0x0100u) /* DMA channel 1 transfer select 21: */
#define DMA1TSEL_22         (22*0x0100u) /* DMA channel 1 transfer select 22: */
#define DMA1TSEL_23         (23*0x0100u) /* DMA channel 1 transfer select 23: */
#define DMA1TSEL_24         (24*0x0100u) /* DMA channel 1 transfer select 24: */
#define DMA1TSEL_25         (25*0x0100u) /* DMA channel 1 transfer select 25: */
#define DMA1TSEL_26         (26*0x0100u) /* DMA channel 1 transfer select 26: */
#define DMA1TSEL_27         (27*0x0100u) /* DMA channel 1 transfer select 27: */
#define DMA1TSEL_28         (28*0x0100u) /* DMA channel 1 transfer select 28: */
#define DMA1TSEL_29         (29*0x0100u) /* DMA channel 1 transfer select 29: */
#define DMA1TSEL_30         (30*0x0100u) /* DMA channel 1 transfer select 30: previous DMA channel DMA0IFG */
#define DMA1TSEL_31         (31*0x0100u) /* DMA channel 1 transfer select 31: ext. Trigger (DMAE0) */

#define DMA2TSEL_0          (0*0x0001u)  /* DMA channel 2 transfer select 0:  DMA_REQ (sw) */
#define DMA2TSEL_1          (1*0x0001u)  /* DMA channel 2 transfer select 1:  */
#define DMA2TSEL_2          (2*0x0001u)  /* DMA channel 2 transfer select 2:  */
#define DMA2TSEL_3          (3*0x0001u)  /* DMA channel 2 transfer select 3:  */
#define DMA2TSEL_4          (4*0x0001u)  /* DMA channel 2 transfer select 4:  */
#define DMA2TSEL_5          (5*0x0001u)  /* DMA channel 2 transfer select 5:  */
#define DMA2TSEL_6          (6*0x0001u)  /* DMA channel 2 transfer select 6:  */
#define DMA2TSEL_7          (7*0x0001u)  /* DMA channel 2 transfer select 7:  */
#define DMA2TSEL_8          (8*0x0001u)  /* DMA channel 2 transfer select 8:  */
#define DMA2TSEL_9          (9*0x0001u)  /* DMA channel 2 transfer select 9:  */
#define DMA2TSEL_10         (10*0x0001u) /* DMA channel 2 transfer select 10: */
#define DMA2TSEL_11         (11*0x0001u) /* DMA channel 2 transfer select 11: */
#define DMA2TSEL_12         (12*0x0001u) /* DMA channel 2 transfer select 12: */
#define DMA2TSEL_13         (13*0x0001u) /* DMA channel 2 transfer select 13: */
#define DMA2TSEL_14         (14*0x0001u) /* DMA channel 2 transfer select 14: */
#define DMA2TSEL_15         (15*0x0001u) /* DMA channel 2 transfer select 15: */
#define DMA2TSEL_16         (16*0x0001u) /* DMA channel 2 transfer select 16: */
#define DMA2TSEL_17         (17*0x0001u) /* DMA channel 2 transfer select 17: */
#define DMA2TSEL_18         (18*0x0001u) /* DMA channel 2 transfer select 18: */
#define DMA2TSEL_19         (19*0x0001u) /* DMA channel 2 transfer select 19: */
#define DMA2TSEL_20         (20*0x0001u) /* DMA channel 2 transfer select 20: */
#define DMA2TSEL_21         (21*0x0001u) /* DMA channel 2 transfer select 21: */
#define DMA2TSEL_22         (22*0x0001u) /* DMA channel 2 transfer select 22: */
#define DMA2TSEL_23         (23*0x0001u) /* DMA channel 2 transfer select 23: */
#define DMA2TSEL_24         (24*0x0001u) /* DMA channel 2 transfer select 24: */
#define DMA2TSEL_25         (25*0x0001u) /* DMA channel 2 transfer select 25: */
#define DMA2TSEL_26         (26*0x0001u) /* DMA channel 2 transfer select 26: */
#define DMA2TSEL_27         (27*0x0001u) /* DMA channel 2 transfer select 27: */
#define DMA2TSEL_28         (28*0x0001u) /* DMA channel 2 transfer select 28: */
#define DMA2TSEL_29         (29*0x0001u) /* DMA channel 2 transfer select 29: */
#define DMA2TSEL_30         (30*0x0001u) /* DMA channel 2 transfer select 30: previous DMA channel DMA1IFG */
#define DMA2TSEL_31         (31*0x0001u) /* DMA channel 2 transfer select 31: ext. Trigger (DMAE0) */

#define DMA0TSEL__DMAREQ     (0*0x0001u)  /* DMA channel 0 transfer select 0:  DMA_REQ (sw) */
#define DMA0TSEL__TA0CCR0    (1*0x0001u)  /* DMA channel 0 transfer select 1:  TA0CCR0 */
#define DMA0TSEL__TA0CCR2    (2*0x0001u)  /* DMA channel 0 transfer select 2:  TA0CCR2 */
#define DMA0TSEL__TA1CCR0    (3*0x0001u)  /* DMA channel 0 transfer select 3:  TA1CCR0 */
#define DMA0TSEL__TA1CCR2    (4*0x0001u)  /* DMA channel 0 transfer select 4:  TA1CCR2 */
#define DMA0TSEL__RES5       (5*0x0001u)  /* DMA channel 0 transfer select 5:  RES5 */
#define DMA0TSEL__RES6       (6*0x0001u)  /* DMA channel 0 transfer select 6:  RES6 */
#define DMA0TSEL__TB0CCR0    (7*0x0001u)  /* DMA channel 0 transfer select 7:  TB0CCR0 */
#define DMA0TSEL__TB0CCR2    (8*0x0001u)  /* DMA channel 0 transfer select 8:  TB0CCR2 */
#define DMA0TSEL__TB1CCR0    (9*0x0001u)  /* DMA channel 0 transfer select 9:  TB1CCR0 */
#define DMA0TSEL__TB1CCR2    (10*0x0001u) /* DMA channel 0 transfer select 10: TB1CCR2 */
#define DMA0TSEL__TB2CCR0    (11*0x0001u) /* DMA channel 0 transfer select 11: TB2CCR0 */
#define DMA0TSEL__TB2CCR2    (12*0x0001u) /* DMA channel 0 transfer select 12: TB2CCR2 */
#define DMA0TSEL__RES13      (13*0x0001u) /* DMA channel 0 transfer select 13: RES13 */
#define DMA0TSEL__UCA0RXIFG  (14*0x0001u) /* DMA channel 0 transfer select 14: UCA0RXIFG */
#define DMA0TSEL__UCA0TXIFG  (15*0x0001u) /* DMA channel 0 transfer select 15: UCA0TXIFG */
#define DMA0TSEL__UCA1RXIFG  (16*0x0001u) /* DMA channel 0 transfer select 16: UCA1RXIFG */
#define DMA0TSEL__UCA1TXIFG  (17*0x0001u) /* DMA channel 0 transfer select 17: UCA1TXIFG */
#define DMA0TSEL__UCB0RXIFG0 (18*0x0001u) /* DMA channel 0 transfer select 18: UCB0RXIFG0 */
#define DMA0TSEL__UCB0TXIFG0 (19*0x0001u) /* DMA channel 0 transfer select 19: UCB0TXIFG0 */
#define DMA0TSEL__UCB0RXIFG1 (20*0x0001u) /* DMA channel 0 transfer select 20: UCB0RXIFG1 */
#define DMA0TSEL__UCB0TXIFG1 (21*0x0001u) /* DMA channel 0 transfer select 21: UCB0TXIFG1 */
#define DMA0TSEL__UCB0RXIFG2 (22*0x0001u) /* DMA channel 0 transfer select 22: UCB0RXIFG2 */
#define DMA0TSEL__UCB0TXIFG2 (23*0x0001u) /* DMA channel 0 transfer select 23: UCB0TXIFG2 */
#define DMA0TSEL__UCB0RXIFG3 (24*0x0001u) /* DMA channel 0 transfer select 24: UCB0RXIFG3 */
#define DMA0TSEL__UCB0TXIFG3 (25*0x0001u) /* DMA channel 0 transfer select 25: UCB0TXIFG3 */
#define DMA0TSEL__ADC10IFG   (26*0x0001u) /* DMA channel 0 transfer select 26: ADC10IFG */
#define DMA0TSEL__RES27      (27*0x0001u) /* DMA channel 0 transfer select 27: RES27 */
#define DMA0TSEL__RES28      (28*0x0001u) /* DMA channel 0 transfer select 28: RES28 */
#define DMA0TSEL__MPY        (29*0x0001u) /* DMA channel 0 transfer select 29: MPY */
#define DMA0TSEL__DMA2IFG    (30*0x0001u) /* DMA channel 0 transfer select 30: previous DMA channel DMA2IFG */
#define DMA0TSEL__DMAE0      (31*0x0001u) /* DMA channel 0 transfer select 31: ext. Trigger (DMAE0) */

#define DMA1TSEL__DMAREQ     (0*0x0100u)  /* DMA channel 1 transfer select 0:  DMA_REQ (sw) */
#define DMA1TSEL__TA0CCR0    (1*0x0100u)  /* DMA channel 1 transfer select 1:  TA0CCR0 */
#define DMA1TSEL__TA0CCR2    (2*0x0100u)  /* DMA channel 1 transfer select 2:  TA0CCR2 */
#define DMA1TSEL__TA1CCR0    (3*0x0100u)  /* DMA channel 1 transfer select 3:  TA1CCR0 */
#define DMA1TSEL__TA1CCR2    (4*0x0100u)  /* DMA channel 1 transfer select 4:  TA1CCR2 */
#define DMA1TSEL__RES5       (5*0x0100u)  /* DMA channel 1 transfer select 5:  RES5 */
#define DMA1TSEL__RES6       (6*0x0100u)  /* DMA channel 1 transfer select 6:  RES6 */
#define DMA1TSEL__TB0CCR0    (7*0x0100u)  /* DMA channel 1 transfer select 7:  TB0CCR0 */
#define DMA1TSEL__TB0CCR2    (8*0x0100u)  /* DMA channel 1 transfer select 8:  TB0CCR2 */
#define DMA1TSEL__TB1CCR0    (9*0x0100u)  /* DMA channel 1 transfer select 9:  TB1CCR0 */
#define DMA1TSEL__TB1CCR2    (10*0x0100u) /* DMA channel 1 transfer select 10: TB1CCR2 */
#define DMA1TSEL__TB2CCR0    (11*0x0100u) /* DMA channel 1 transfer select 11: TB2CCR0 */
#define DMA1TSEL__TB2CCR2    (12*0x0100u) /* DMA channel 1 transfer select 12: TB2CCR2 */
#define DMA1TSEL__RES13      (13*0x0100u) /* DMA channel 1 transfer select 13: RES13 */
#define DMA1TSEL__UCA0RXIFG  (14*0x0100u) /* DMA channel 1 transfer select 14: UCA0RXIFG */
#define DMA1TSEL__UCA0TXIFG  (15*0x0100u) /* DMA channel 1 transfer select 15: UCA0TXIFG */
#define DMA1TSEL__UCA1RXIFG  (16*0x0100u) /* DMA channel 1 transfer select 16: UCA1RXIFG */
#define DMA1TSEL__UCA1TXIFG  (17*0x0100u) /* DMA channel 1 transfer select 17: UCA1TXIFG */
#define DMA1TSEL__UCB0RXIFG0 (18*0x0100u) /* DMA channel 1 transfer select 18: UCB0RXIFG0 */
#define DMA1TSEL__UCB0TXIFG0 (19*0x0100u) /* DMA channel 1 transfer select 19: UCB0TXIFG0 */
#define DMA1TSEL__UCB0RXIFG1 (20*0x0100u) /* DMA channel 1 transfer select 20: UCB0RXIFG1 */
#define DMA1TSEL__UCB0TXIFG1 (21*0x0100u) /* DMA channel 1 transfer select 21: UCB0TXIFG1 */
#define DMA1TSEL__UCB0RXIFG2 (22*0x0100u) /* DMA channel 1 transfer select 22: UCB0RXIFG2 */
#define DMA1TSEL__UCB0TXIFG2 (23*0x0100u) /* DMA channel 1 transfer select 23: UCB0TXIFG2 */
#define DMA1TSEL__UCB0RXIFG3 (24*0x0100u) /* DMA channel 1 transfer select 24: UCB0RXIFG3 */
#define DMA1TSEL__UCB0TXIFG3 (25*0x0100u) /* DMA channel 1 transfer select 25: UCB0TXIFG3 */
#define DMA1TSEL__ADC10IFG   (26*0x0100u) /* DMA channel 1 transfer select 26: ADC10IFG */
#define DMA1TSEL__RES27      (27*0x0100u) /* DMA channel 1 transfer select 27: RES27 */
#define DMA1TSEL__RES28      (28*0x0100u) /* DMA channel 1 transfer select 28: RES28 */
#define DMA1TSEL__MPY        (29*0x0100u) /* DMA channel 1 transfer select 29: MPY */
#define DMA1TSEL__DMA0IFG    (30*0x0100u) /* DMA channel 1 transfer select 30: previous DMA channel DMA0IFG */
#define DMA1TSEL__DMAE0      (31*0x0100u) /* DMA channel 1 transfer select 31: ext. Trigger (DMAE0) */

#define DMA2TSEL__DMAREQ     (0*0x0001u)  /* DMA channel 2 transfer select 0:  DMA_REQ (sw) */
#define DMA2TSEL__TA0CCR0    (1*0x0001u)  /* DMA channel 2 transfer select 1:  TA0CCR0 */
#define DMA2TSEL__TA0CCR2    (2*0x0001u)  /* DMA channel 2 transfer select 2:  TA0CCR2 */
#define DMA2TSEL__TA1CCR0    (3*0x0001u)  /* DMA channel 2 transfer select 3:  TA1CCR0 */
#define DMA2TSEL__TA1CCR2    (4*0x0001u)  /* DMA channel 2 transfer select 4:  TA1CCR2 */
#define DMA2TSEL__RES5       (5*0x0001u)  /* DMA channel 2 transfer select 5:  RES5 */
#define DMA2TSEL__RES6       (6*0x0001u)  /* DMA channel 2 transfer select 6:  RES6 */
#define DMA2TSEL__TB0CCR0    (7*0x0001u)  /* DMA channel 2 transfer select 7:  TB0CCR0 */
#define DMA2TSEL__TB0CCR2    (8*0x0001u)  /* DMA channel 2 transfer select 8:  TB0CCR2 */
#define DMA2TSEL__TB1CCR0    (9*0x0001u)  /* DMA channel 2 transfer select 9:  TB1CCR0 */
#define DMA2TSEL__TB1CCR2    (10*0x0001u) /* DMA channel 2 transfer select 10: TB1CCR2 */
#define DMA2TSEL__TB2CCR0    (11*0x0001u) /* DMA channel 2 transfer select 11: TB2CCR0 */
#define DMA2TSEL__TB2CCR2    (12*0x0001u) /* DMA channel 2 transfer select 12: TB2CCR2 */
#define DMA2TSEL__RES13      (13*0x0001u) /* DMA channel 2 transfer select 13: RES13 */
#define DMA2TSEL__UCA0RXIFG  (14*0x0001u) /* DMA channel 2 transfer select 14: UCA0RXIFG */
#define DMA2TSEL__UCA0TXIFG  (15*0x0001u) /* DMA channel 2 transfer select 15: UCA0TXIFG */
#define DMA2TSEL__UCA1RXIFG  (16*0x0001u) /* DMA channel 2 transfer select 16: UCA1RXIFG */
#define DMA2TSEL__UCA1TXIFG  (17*0x0001u) /* DMA channel 2 transfer select 17: UCA1TXIFG */
#define DMA2TSEL__UCB0RXIFG0 (18*0x0001u) /* DMA channel 2 transfer select 18: UCB0RXIFG0 */
#define DMA2TSEL__UCB0TXIFG0 (19*0x0001u) /* DMA channel 2 transfer select 19: UCB0TXIFG0 */
#define DMA2TSEL__UCB0RXIFG1 (20*0x0001u) /* DMA channel 2 transfer select 20: UCB0RXIFG1 */
#define DMA2TSEL__UCB0TXIFG1 (21*0x0001u) /* DMA channel 2 transfer select 21: UCB0TXIFG1 */
#define DMA2TSEL__UCB0RXIFG2 (22*0x0001u) /* DMA channel 2 transfer select 22: UCB0RXIFG2 */
#define DMA2TSEL__UCB0TXIFG2 (23*0x0001u) /* DMA channel 2 transfer select 23: UCB0TXIFG2 */
#define DMA2TSEL__UCB0RXIFG3 (24*0x0001u) /* DMA channel 2 transfer select 24: UCB0RXIFG3 */
#define DMA2TSEL__UCB0TXIFG3 (25*0x0001u) /* DMA channel 2 transfer select 25: UCB0TXIFG3 */
#define DMA2TSEL__ADC10IFG   (26*0x0001u) /* DMA channel 2 transfer select 26: ADC10IFG */
#define DMA2TSEL__RES27      (27*0x0001u) /* DMA channel 2 transfer select 27: RES27 */
#define DMA2TSEL__RES28      (28*0x0001u) /* DMA channel 2 transfer select 28: RES28 */
#define DMA2TSEL__MPY        (29*0x0001u) /* DMA channel 2 transfer select 29: MPY */
#define DMA2TSEL__DMA1IFG    (30*0x0001u) /* DMA channel 2 transfer select 30: previous DMA channel DMA1IFG */
#define DMA2TSEL__DMAE0      (31*0x0001u) /* DMA channel 2 transfer select 31: ext. Trigger (DMAE0) */

/*************************************************************
* FRAM Memory
*************************************************************/
#define __MSP430_HAS_FRAM_FR5XX__     /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_FRAM_FR5XX__ 0x0140

#define  FRCTL0_            (0x0140u)  /* FRAM Controller Control 0 */
DEFCW(   FRCTL0           , FRCTL0_)
#define  GCCTL0_            (0x0144u)  /* General Control 0 */
DEFCW(   GCCTL0           , GCCTL0_)
#define  GCCTL1_            (0x0146u)  /* General Control 1 */
DEFCW(   GCCTL1           , GCCTL1_)

#define FRPW                (0x9600u)  /* FRAM password returned by read */
#define FWPW                (0xA500u)  /* FRAM password for write */
#define FXPW                (0x3300u)  /* for use with XOR instruction */

/* FRCTL0 Control Bits */
#define NPRECHG0            (0x0001u)  /* FRAM Wait state Generator Precharge Time control Bit: 0 */
#define NPRECHG1            (0x0002u)  /* FRAM Wait state Generator Precharge Time control Bit: 1 */
#define NPRECHG2            (0x0004u)  /* FRAM Wait state Generator Precharge Time control Bit: 2 */
#define NAUTO               (0x0008u)  /* FRAM Disables the wait state generator */
#define NACCESS0            (0x0010u)  /* FRAM Wait state Generator Access Time control Bit: 0 */
#define NACCESS1            (0x0020u)  /* FRAM Wait state Generator Access Time control Bit: 1 */
#define NACCESS2            (0x0040u)  /* FRAM Wait state Generator Access Time control Bit: 2 */
//#define RESERVED            (0x0080u)  /* RESERVED */

/* FRCTL0 Control Bits */
#define NPRECHG0_L          (0x0001u)  /* FRAM Wait state Generator Precharge Time control Bit: 0 */
#define NPRECHG1_L          (0x0002u)  /* FRAM Wait state Generator Precharge Time control Bit: 1 */
#define NPRECHG2_L          (0x0004u)  /* FRAM Wait state Generator Precharge Time control Bit: 2 */
#define NAUTO_L             (0x0008u)  /* FRAM Disables the wait state generator */
#define NACCESS0_L          (0x0010u)  /* FRAM Wait state Generator Access Time control Bit: 0 */
#define NACCESS1_L          (0x0020u)  /* FRAM Wait state Generator Access Time control Bit: 1 */
#define NACCESS2_L          (0x0040u)  /* FRAM Wait state Generator Access Time control Bit: 2 */
//#define RESERVED            (0x0080u)  /* RESERVED */

/* FRCTL0 Control Bits */
//#define RESERVED            (0x0080u)  /* RESERVED */

#define NPRECHG_0           (0x0000u)  /* FRAM Wait state Generator Precharge Time control: 0 */
#define NPRECHG_1           (0x0001u)  /* FRAM Wait state Generator Precharge Time control: 1 */
#define NPRECHG_2           (0x0002u)  /* FRAM Wait state Generator Precharge Time control: 2 */
#define NPRECHG_3           (0x0003u)  /* FRAM Wait state Generator Precharge Time control: 3 */
#define NPRECHG_4           (0x0004u)  /* FRAM Wait state Generator Precharge Time control: 4 */
#define NPRECHG_5           (0x0005u)  /* FRAM Wait state Generator Precharge Time control: 5 */
#define NPRECHG_6           (0x0006u)  /* FRAM Wait state Generator Precharge Time control: 6 */
#define NPRECHG_7           (0x0007u)  /* FRAM Wait state Generator Precharge Time control: 7 */

#define NACCESS_0           (0x0000u)  /* FRAM Wait state Generator Access Time control: 0 */
#define NACCESS_1           (0x0010u)  /* FRAM Wait state Generator Access Time control: 1 */
#define NACCESS_2           (0x0020u)  /* FRAM Wait state Generator Access Time control: 2 */
#define NACCESS_3           (0x0030u)  /* FRAM Wait state Generator Access Time control: 3 */
#define NACCESS_4           (0x0040u)  /* FRAM Wait state Generator Access Time control: 4 */
#define NACCESS_5           (0x0050u)  /* FRAM Wait state Generator Access Time control: 5 */
#define NACCESS_6           (0x0060u)  /* FRAM Wait state Generator Access Time control: 6 */
#define NACCESS_7           (0x0070u)  /* FRAM Wait state Generator Access Time control: 7 */

/* GCCTL0 Control Bits */
#define BUSY                (0x0001u)  /* FRAM is currently busy programming */
//#define RESERVED            (0x0002u)  /* RESERVED */
//#define RESERVED            (0x0004u)  /* RESERVED */
#define ACCTEIE             (0x0008u)  /* Enable NMI event if Access time error occurs */
#define ACCVIE              (0x0010u)  /* Enable NMI event if Access Violation occurs */
#define SBDIEN              (0x0020u)  /* Enable NMI event if single bit error detected */
#define DBDIEN              (0x0040u)  /* Enable NMI event if double bit error detected */
#define DBDRSTEN            (0x0080u)  /* Enable Power Up Clear on double bit error */

/* GCCTL0 Control Bits */
#define BUSY_L              (0x0001u)  /* FRAM is currently busy programming */
//#define RESERVED            (0x0002u)  /* RESERVED */
//#define RESERVED            (0x0004u)  /* RESERVED */
#define ACCTEIE_L           (0x0008u)  /* Enable NMI event if Access time error occurs */
#define ACCVIE_L            (0x0010u)  /* Enable NMI event if Access Violation occurs */
#define SBDIEN_L            (0x0020u)  /* Enable NMI event if single bit error detected */
#define DBDIEN_L            (0x0040u)  /* Enable NMI event if double bit error detected */
#define DBDRSTEN_L          (0x0080u)  /* Enable Power Up Clear on double bit error */

/* GCCTL0 Control Bits */
//#define RESERVED            (0x0002u)  /* RESERVED */
//#define RESERVED            (0x0004u)  /* RESERVED */

/* GCCTL1 Control Bits */
#define ACCVIFG             (0x0001u)  /* Access Violation Interrupt Flag */
#define SBDIFG              (0x0002u)  /* FRAM single bit error flag */
#define DBDIFG              (0x0004u)  /* FRAM double bit error flag */
#define ACCTEIFG            (0x0008u)  /* Access time error flag */

/* GCCTL1 Control Bits */
#define ACCVIFG_L           (0x0001u)  /* Access Violation Interrupt Flag */
#define SBDIFG_L            (0x0002u)  /* FRAM single bit error flag */
#define DBDIFG_L            (0x0004u)  /* FRAM double bit error flag */
#define ACCTEIFG_L          (0x0008u)  /* Access time error flag */

/* GCCTL1 Control Bits */

/************************************************************
* Memory Protection Unit
************************************************************/
#define __MSP430_HAS_MPU__             /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_MPU__ 0x05A0

#define  MPUCTL0_            (0x05A0u)  /* MPU Control Register 0 */
DEFCW(   MPUCTL0           , MPUCTL0_)
#define  MPUCTL1_            (0x05A2u)  /* MPU Control Register 1 */
DEFCW(   MPUCTL1           , MPUCTL1_)
#define  MPUSEG_             (0x05A4u)  /* MPU Segmentation Register */
DEFCW(   MPUSEG            , MPUSEG_)
#define  MPUSAM_             (0x05A6u)  /* MPU Access Management Register */
DEFCW(   MPUSAM            , MPUSAM_)

/* MPUCTL0 Control Bits */
#define MPUENA               (0x0001u)  /* MPU Enable */
#define MPULOCK              (0x0002u)  /* MPU Lock */
#define MPUSEGIE             (0x0010u)  /* MPU Enable NMI on Segment violation */

/* MPUCTL0 Control Bits */
#define MPUENA_L            (0x0001u)  /* MPU Enable */
#define MPULOCK_L           (0x0002u)  /* MPU Lock */
#define MPUSEGIE_L          (0x0010u)  /* MPU Enable NMI on Segment violation */

/* MPUCTL0 Control Bits */
#define MPUPW                (0xA500u)  /* MPU Access Password */
#define MPUPW_H              (0xA5)    /* MPU Access Password */

/* MPUCTL1 Control Bits */
#define MPUSEG1IFG           (0x0001u)  /* MPU Main Memory Segment 1 violation interupt flag */
#define MPUSEG2IFG           (0x0002u)  /* MPU Main Memory Segment 2 violation interupt flag */
#define MPUSEG3IFG           (0x0004u)  /* MPU Main Memory Segment 3 violation interupt flag */
#define MPUSEGIIFG           (0x0008u)  /* MPU Info Memory Segment violation interupt flag */

/* MPUCTL1 Control Bits */
#define MPUSEG1IFG_L        (0x0001u)  /* MPU Main Memory Segment 1 violation interupt flag */
#define MPUSEG2IFG_L        (0x0002u)  /* MPU Main Memory Segment 2 violation interupt flag */
#define MPUSEG3IFG_L        (0x0004u)  /* MPU Main Memory Segment 3 violation interupt flag */
#define MPUSEGIIFG_L        (0x0008u)  /* MPU Info Memory Segment violation interupt flag */

/* MPUCTL1 Control Bits */

/* MPUSEG Control Bits */
#define MPUSB10              (0x0001u)  /* MPU Segment Border 1 Bit: 0 */
#define MPUSB11              (0x0002u)  /* MPU Segment Border 1 Bit: 1 */
#define MPUSB12              (0x0004u)  /* MPU Segment Border 1 Bit: 2 */
#define MPUSB13              (0x0008u)  /* MPU Segment Border 1 Bit: 3 */
#define MPUSB14              (0x0010u)  /* MPU Segment Border 1 Bit: 4 */
#define MPUSB20              (0x0100u)  /* MPU Segment Border 2 Bit: 0 */
#define MPUSB21              (0x0200u)  /* MPU Segment Border 2 Bit: 1 */
#define MPUSB22              (0x0400u)  /* MPU Segment Border 2 Bit: 2 */
#define MPUSB23              (0x0800u)  /* MPU Segment Border 2 Bit: 3 */
#define MPUSB24              (0x1000u)  /* MPU Segment Border 2 Bit: 4 */

/* MPUSEG Control Bits */
#define MPUSB10_L           (0x0001u)  /* MPU Segment Border 1 Bit: 0 */
#define MPUSB11_L           (0x0002u)  /* MPU Segment Border 1 Bit: 1 */
#define MPUSB12_L           (0x0004u)  /* MPU Segment Border 1 Bit: 2 */
#define MPUSB13_L           (0x0008u)  /* MPU Segment Border 1 Bit: 3 */
#define MPUSB14_L           (0x0010u)  /* MPU Segment Border 1 Bit: 4 */

/* MPUSEG Control Bits */
#define MPUSB20_H           (0x0001u)  /* MPU Segment Border 2 Bit: 0 */
#define MPUSB21_H           (0x0002u)  /* MPU Segment Border 2 Bit: 1 */
#define MPUSB22_H           (0x0004u)  /* MPU Segment Border 2 Bit: 2 */
#define MPUSB23_H           (0x0008u)  /* MPU Segment Border 2 Bit: 3 */
#define MPUSB24_H           (0x0010u)  /* MPU Segment Border 2 Bit: 4 */

/* MPUSAM Control Bits */
#define MPUSEG1RE            (0x0001u)  /* MPU Main memory Segment 1 Read enable */
#define MPUSEG1WE            (0x0002u)  /* MPU Main memory Segment 1 Write enable */
#define MPUSEG1XE            (0x0004u)  /* MPU Main memory Segment 1 Execute enable */
#define MPUSEG1VS            (0x0008u)  /* MPU Main memory Segment 1 Violation select */
#define MPUSEG2RE            (0x0010u)  /* MPU Main memory Segment 2 Read enable */
#define MPUSEG2WE            (0x0020u)  /* MPU Main memory Segment 2 Write enable */
#define MPUSEG2XE            (0x0040u)  /* MPU Main memory Segment 2 Execute enable */
#define MPUSEG2VS            (0x0080u)  /* MPU Main memory Segment 2 Violation select */
#define MPUSEG3RE            (0x0100u)  /* MPU Main memory Segment 3 Read enable */
#define MPUSEG3WE            (0x0200u)  /* MPU Main memory Segment 3 Write enable */
#define MPUSEG3XE            (0x0400u)  /* MPU Main memory Segment 3 Execute enable */
#define MPUSEG3VS            (0x0800u)  /* MPU Main memory Segment 3 Violation select */
#define MPUSEGIRE            (0x1000u)  /* MPU Info memory Segment Read enable */
#define MPUSEGIWE            (0x2000u)  /* MPU Info memory Segment Write enable */
#define MPUSEGIXE            (0x4000u)  /* MPU Info memory Segment Execute enable */
#define MPUSEGIVS            (0x8000u)  /* MPU Info memory Segment Violation select */

/* MPUSAM Control Bits */
#define MPUSEG1RE_L         (0x0001u)  /* MPU Main memory Segment 1 Read enable */
#define MPUSEG1WE_L         (0x0002u)  /* MPU Main memory Segment 1 Write enable */
#define MPUSEG1XE_L         (0x0004u)  /* MPU Main memory Segment 1 Execute enable */
#define MPUSEG1VS_L         (0x0008u)  /* MPU Main memory Segment 1 Violation select */
#define MPUSEG2RE_L         (0x0010u)  /* MPU Main memory Segment 2 Read enable */
#define MPUSEG2WE_L         (0x0020u)  /* MPU Main memory Segment 2 Write enable */
#define MPUSEG2XE_L         (0x0040u)  /* MPU Main memory Segment 2 Execute enable */
#define MPUSEG2VS_L         (0x0080u)  /* MPU Main memory Segment 2 Violation select */

/* MPUSAM Control Bits */
#define MPUSEG3RE_H         (0x0001u)  /* MPU Main memory Segment 3 Read enable */
#define MPUSEG3WE_H         (0x0002u)  /* MPU Main memory Segment 3 Write enable */
#define MPUSEG3XE_H         (0x0004u)  /* MPU Main memory Segment 3 Execute enable */
#define MPUSEG3VS_H         (0x0008u)  /* MPU Main memory Segment 3 Violation select */
#define MPUSEGIRE_H         (0x0010u)  /* MPU Info memory Segment Read enable */
#define MPUSEGIWE_H         (0x0020u)  /* MPU Info memory Segment Write enable */
#define MPUSEGIXE_H         (0x0040u)  /* MPU Info memory Segment Execute enable */
#define MPUSEGIVS_H         (0x0080u)  /* MPU Info memory Segment Violation select */

/************************************************************
* HARDWARE MULTIPLIER 32Bit
************************************************************/
#define __MSP430_HAS_MPY32__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_MPY32__ 0x04C0

#define  MPY_                (0x04C0u)  /* Multiply Unsigned/Operand 1 */
DEFCW(   MPY               , MPY_)
#define  MPYS_               (0x04C2u)  /* Multiply Signed/Operand 1 */
DEFCW(   MPYS              , MPYS_)
#define  MAC_                (0x04C4u)  /* Multiply Unsigned and Accumulate/Operand 1 */
DEFCW(   MAC               , MAC_)
#define  MACS_               (0x04C6u)  /* Multiply Signed and Accumulate/Operand 1 */
DEFCW(   MACS              , MACS_)
#define  OP2_                (0x04C8u)  /* Operand 2 */
DEFCW(   OP2               , OP2_)
#define  RESLO_              (0x04CAu)  /* Result Low Word */
DEFCW(   RESLO             , RESLO_)
#define  RESHI_              (0x04CCu)  /* Result High Word */
DEFCW(   RESHI             , RESHI_)
#define SUMEXT_             (0x04CEu)  /* Sum Extend */
READ_ONLY_DEFCW( SUMEXT         , SUMEXT_)

#define  MPY32L_             (0x04D0u)  /* 32-bit operand 1 - multiply - low word */
DEFCW(   MPY32L            , MPY32L_)
#define  MPY32H_             (0x04D2u)  /* 32-bit operand 1 - multiply - high word */
DEFCW(   MPY32H            , MPY32H_)
#define  MPYS32L_            (0x04D4u)  /* 32-bit operand 1 - signed multiply - low word */
DEFCW(   MPYS32L           , MPYS32L_)
#define  MPYS32H_            (0x04D6u)  /* 32-bit operand 1 - signed multiply - high word */
DEFCW(   MPYS32H           , MPYS32H_)
#define  MAC32L_             (0x04D8u)  /* 32-bit operand 1 - multiply accumulate - low word */
DEFCW(   MAC32L            , MAC32L_)
#define  MAC32H_             (0x04DAu)  /* 32-bit operand 1 - multiply accumulate - high word */
DEFCW(   MAC32H            , MAC32H_)
#define  MACS32L_            (0x04DCu)  /* 32-bit operand 1 - signed multiply accumulate - low word */
DEFCW(   MACS32L           , MACS32L_)
#define  MACS32H_            (0x04DEu)  /* 32-bit operand 1 - signed multiply accumulate - high word */
DEFCW(   MACS32H           , MACS32H_)
#define  OP2L_               (0x04E0u)  /* 32-bit operand 2 - low word */
DEFCW(   OP2L              , OP2L_)
#define  OP2H_               (0x04E2u)  /* 32-bit operand 2 - high word */
DEFCW(   OP2H              , OP2H_)
#define  RES0_               (0x04E4u)  /* 32x32-bit result 0 - least significant word */
DEFCW(   RES0              , RES0_)
#define  RES1_               (0x04E6u)  /* 32x32-bit result 1 */
DEFCW(   RES1              , RES1_)
#define  RES2_               (0x04E8u)  /* 32x32-bit result 2 */
DEFCW(   RES2              , RES2_)
#define  RES3_               (0x04EAu)  /* 32x32-bit result 3 - most significant word */
DEFCW(   RES3              , RES3_)
#define  MPY32CTL0_          (0x04ECu)  /* MPY32 Control Register 0 */
DEFCW(   MPY32CTL0         , MPY32CTL0_)

#define MPY_B               MPY_L      /* Multiply Unsigned/Operand 1 (Byte Access) */
#define MPYS_B              MPYS_L     /* Multiply Signed/Operand 1 (Byte Access) */
#define MAC_B               MAC_L      /* Multiply Unsigned and Accumulate/Operand 1 (Byte Access) */
#define MACS_B              MACS_L     /* Multiply Signed and Accumulate/Operand 1 (Byte Access) */
#define OP2_B               OP2_L      /* Operand 2 (Byte Access) */
#define MPY32L_B            MPY32L_L   /* 32-bit operand 1 - multiply - low word (Byte Access) */
#define MPY32H_B            MPY32H_L   /* 32-bit operand 1 - multiply - high word (Byte Access) */
#define MPYS32L_B           MPYS32L_L  /* 32-bit operand 1 - signed multiply - low word (Byte Access) */
#define MPYS32H_B           MPYS32H_L  /* 32-bit operand 1 - signed multiply - high word (Byte Access) */
#define MAC32L_B            MAC32L_L   /* 32-bit operand 1 - multiply accumulate - low word (Byte Access) */
#define MAC32H_B            MAC32H_L   /* 32-bit operand 1 - multiply accumulate - high word (Byte Access) */
#define MACS32L_B           MACS32L_L  /* 32-bit operand 1 - signed multiply accumulate - low word (Byte Access) */
#define MACS32H_B           MACS32H_L  /* 32-bit operand 1 - signed multiply accumulate - high word (Byte Access) */
#define OP2L_B              OP2L_L     /* 32-bit operand 2 - low word (Byte Access) */
#define OP2H_B              OP2H_L     /* 32-bit operand 2 - high word (Byte Access) */

/* MPY32CTL0 Control Bits */
#define MPYC                (0x0001u)  /* Carry of the multiplier */
//#define RESERVED            (0x0002u)  /* Reserved */
#define MPYFRAC             (0x0004u)  /* Fractional mode */
#define MPYSAT              (0x0008u)  /* Saturation mode */
#define MPYM0               (0x0010u)  /* Multiplier mode Bit:0 */
#define MPYM1               (0x0020u)  /* Multiplier mode Bit:1 */
#define OP1_32              (0x0040u)  /* Bit-width of operand 1 0:16Bit / 1:32Bit */
#define OP2_32              (0x0080u)  /* Bit-width of operand 2 0:16Bit / 1:32Bit */
#define MPYDLYWRTEN         (0x0100u)  /* Delayed write enable */
#define MPYDLY32            (0x0200u)  /* Delayed write mode */

/* MPY32CTL0 Control Bits */
#define MPYC_L              (0x0001u)  /* Carry of the multiplier */
//#define RESERVED            (0x0002u)  /* Reserved */
#define MPYFRAC_L           (0x0004u)  /* Fractional mode */
#define MPYSAT_L            (0x0008u)  /* Saturation mode */
#define MPYM0_L             (0x0010u)  /* Multiplier mode Bit:0 */
#define MPYM1_L             (0x0020u)  /* Multiplier mode Bit:1 */
#define OP1_32_L            (0x0040u)  /* Bit-width of operand 1 0:16Bit / 1:32Bit */
#define OP2_32_L            (0x0080u)  /* Bit-width of operand 2 0:16Bit / 1:32Bit */

/* MPY32CTL0 Control Bits */
//#define RESERVED            (0x0002u)  /* Reserved */
#define MPYDLYWRTEN_H       (0x0001u)  /* Delayed write enable */
#define MPYDLY32_H          (0x0002u)  /* Delayed write mode */

#define MPYM_0              (0x0000u)  /* Multiplier mode: MPY */
#define MPYM_1              (0x0010u)  /* Multiplier mode: MPYS */
#define MPYM_2              (0x0020u)  /* Multiplier mode: MAC */
#define MPYM_3              (0x0030u)  /* Multiplier mode: MACS */
#define MPYM__MPY           (0x0000u)  /* Multiplier mode: MPY */
#define MPYM__MPYS          (0x0010u)  /* Multiplier mode: MPYS */
#define MPYM__MAC           (0x0020u)  /* Multiplier mode: MAC */
#define MPYM__MACS          (0x0030u)  /* Multiplier mode: MACS */

/************************************************************
* PMM - Power Management System
************************************************************/
#define __MSP430_HAS_PMM_FR5xx__      /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PMM_FR5xx__ 0x0120

#define  PMMCTL0_           (0x0120u)  /* PMM Control 0 */
DEFCW(   PMMCTL0          , PMMCTL0_)
#define  PMMIFG_            (0x012Au)  /* PMM Interrupt Flag */
DEFCW(   PMMIFG           , PMMIFG_)
#define  PM5CTL0_           (0x0130u)  /* PMM Power Mode 5 Control Register 0 */
DEFCW(   PM5CTL0          , PM5CTL0_)

#define PMMPW               (0xA500u)  /* PMM Register Write Password */
#define PMMPW_H             (0xA5)    /* PMM Register Write Password for high word access */

/* PMMCTL0 Control Bits */
#define PMMSWBOR            (0x0004u)  /* PMM Software BOR */
#define PMMSWPOR            (0x0008u)  /* PMM Software POR */
#define PMMREGOFF           (0x0010u)  /* PMM Turn Regulator off */
#define SVSLE               (0x0020u)  /* SVS low side enable */
#define SVSHE               (0x0040u)  /* SVS high side enable */

/* PMMCTL0 Control Bits */
#define PMMSWBOR_L          (0x0004u)  /* PMM Software BOR */
#define PMMSWPOR_L          (0x0008u)  /* PMM Software POR */
#define PMMREGOFF_L         (0x0010u)  /* PMM Turn Regulator off */
#define SVSLE_L             (0x0020u)  /* SVS low side enable */
#define SVSHE_L             (0x0040u)  /* SVS high side enable */

/* PMMCTL0 Control Bits */

/* PMMIFG Control Bits */
#define PMMBORIFG           (0x0100u)  /* PMM Software BOR interrupt flag */
#define PMMRSTIFG           (0x0200u)  /* PMM RESET pin interrupt flag */
#define PMMPORIFG           (0x0400u)  /* PMM Software POR interrupt flag */
#define SVSLIFG             (0x1000u)  /* SVS high side interrupt flag */
#define SVSHIFG             (0x2000u)  /* SVS low side interrupt flag */
#define PMMLPM5IFG          (0x8000u)  /* LPM5 indication Flag */

/* PMMIFG Control Bits */

/* PMMIFG Control Bits */
#define PMMBORIFG_H         (0x0001u)  /* PMM Software BOR interrupt flag */
#define PMMRSTIFG_H         (0x0002u)  /* PMM RESET pin interrupt flag */
#define PMMPORIFG_H         (0x0004u)  /* PMM Software POR interrupt flag */
#define SVSLIFG_H           (0x0010u)  /* SVS high side interrupt flag */
#define SVSHIFG_H           (0x0020u)  /* SVS low side interrupt flag */
#define PMMLPM5IFG_H        (0x0080u)  /* LPM5 indication Flag */

/* PM5CTL0 Power Mode 5 Control Bits */
#define LOCKLPM5            (0x0001u)  /* Lock I/O pin configuration upon entry/exit to/from LPM5 */

/* PM5CTL0 Power Mode 5 Control Bits */
#define LOCKLPM5_L          (0x0001u)  /* Lock I/O pin configuration upon entry/exit to/from LPM5 */

/* PM5CTL0 Power Mode 5 Control Bits */

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
#define  PASELC_             (0x0210u)  /* Port A Complement Selection */
DEFCW(   PASELC            , PASELC_)
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
#define P1SELC              (PASELC_L) /* Port 1 Complement Selection */
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
#define P2SELC              (PASELC_H) /* Port 2 Complement Selection */
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
* DIGITAL I/O PortJ Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORTJ_R__        /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_PORTJ_R__ 0x0320

#define PJIN_               (0x0320u)  /* Port J Input */
READ_ONLY_DEFCW( PJIN           , PJIN_)
#define  PJOUT_              (0x0322u)  /* Port J Output */
DEFCW(   PJOUT             , PJOUT_)
#define  PJDIR_              (0x0324u)  /* Port J Direction */
DEFCW(   PJDIR             , PJDIR_)
#define  PJREN_              (0x0326u)  /* Port J Resistor Enable */
DEFCW(   PJREN             , PJREN_)
#define  PJDS_               (0x0328u)  /* Port J Resistor Drive Strenght */
DEFCW(   PJDS              , PJDS_)
#define  PJSEL0_             (0x032Au)  /* Port J Selection 0 */
DEFCW(   PJSEL0            , PJSEL0_)
#define  PJSEL1_             (0x032Cu)  /* Port J Selection 1 */
DEFCW(   PJSEL1            , PJSEL1_)

/************************************************************
* Shared Reference
************************************************************/
#define __MSP430_HAS_REF__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_REF__ 0x01B0

#define  REFCTL0_            (0x01B0u)  /* REF Shared Reference control register 0 */
DEFCW(   REFCTL0           , REFCTL0_)

/* REFCTL0 Control Bits */
#define REFON               (0x0001u)  /* REF Reference On */
//#define RESERVED            (0x0002u)  /* Reserved */
//#define RESERVED            (0x0004u)  /* Reserved */
#define REFTCOFF            (0x0008u)  /* REF Temp.Sensor off */
#define REFVSEL0            (0x0010u)  /* REF Reference Voltage Level Select Bit:0 */
#define REFVSEL1            (0x0020u)  /* REF Reference Voltage Level Select Bit:1 */
//#define RESERVED            (0x0040u)  /* Reserved */
//#define RESERVED            (0x0080u)  /* Reserved */
#define REFGENACT           (0x0100u)  /* REF Reference generator active */
#define REFBGACT            (0x0200u)  /* REF Reference bandgap active */
#define REFGENBUSY          (0x0400u)  /* REF Reference generator busy */
#define BGMODE              (0x0800u)  /* REF Bandgap mode */
//#define RESERVED            (0x1000u)  /* Reserved */
//#define RESERVED            (0x2000u)  /* Reserved */
//#define RESERVED            (0x4000u)  /* Reserved */
//#define RESERVED            (0x8000u)  /* Reserved */

/* REFCTL0 Control Bits */
#define REFON_L             (0x0001u)  /* REF Reference On */
//#define RESERVED            (0x0002u)  /* Reserved */
//#define RESERVED            (0x0004u)  /* Reserved */
#define REFTCOFF_L          (0x0008u)  /* REF Temp.Sensor off */
#define REFVSEL0_L          (0x0010u)  /* REF Reference Voltage Level Select Bit:0 */
#define REFVSEL1_L          (0x0020u)  /* REF Reference Voltage Level Select Bit:1 */
//#define RESERVED            (0x0040u)  /* Reserved */
//#define RESERVED            (0x0080u)  /* Reserved */
//#define RESERVED            (0x1000u)  /* Reserved */
//#define RESERVED            (0x2000u)  /* Reserved */
//#define RESERVED            (0x4000u)  /* Reserved */
//#define RESERVED            (0x8000u)  /* Reserved */

/* REFCTL0 Control Bits */
//#define RESERVED            (0x0002u)  /* Reserved */
//#define RESERVED            (0x0004u)  /* Reserved */
//#define RESERVED            (0x0040u)  /* Reserved */
//#define RESERVED            (0x0080u)  /* Reserved */
#define REFGENACT_H         (0x0001u)  /* REF Reference generator active */
#define REFBGACT_H          (0x0002u)  /* REF Reference bandgap active */
#define REFGENBUSY_H        (0x0004u)  /* REF Reference generator busy */
#define BGMODE_H            (0x0008u)  /* REF Bandgap mode */
//#define RESERVED            (0x1000u)  /* Reserved */
//#define RESERVED            (0x2000u)  /* Reserved */
//#define RESERVED            (0x4000u)  /* Reserved */
//#define RESERVED            (0x8000u)  /* Reserved */

#define REFVSEL_0           (0x0000u)  /* REF Reference Voltage Level Select 1.5V */
#define REFVSEL_1           (0x0010u)  /* REF Reference Voltage Level Select 2.0V */
#define REFVSEL_2           (0x0020u)  /* REF Reference Voltage Level Select 2.5V */
#define REFVSEL_3           (0x0030u)  /* REF Reference Voltage Level Select 2.5V */

/************************************************************
* Real Time Clock
************************************************************/
#define __MSP430_HAS_RTC_B__          /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_RTC_B__ 0x04A0

#define RTCCTL01_           (0x04A0u)  /* Real Timer Control 0/1 */
DEFCW(  RTCCTL01          , RTCCTL01_)
#define RTCCTL23_           (0x04A2u)  /* Real Timer Control 2/3 */
DEFCW(  RTCCTL23          , RTCCTL23_)
#define RTCPS0CTL_          (0x04A8u)  /* Real Timer Prescale Timer 0 Control */
DEFCW(  RTCPS0CTL         , RTCPS0CTL_)
#define RTCPS1CTL_          (0x04AAu)  /* Real Timer Prescale Timer 1 Control */
DEFCW(  RTCPS1CTL         , RTCPS1CTL_)
#define RTCPS_              (0x04ACu)  /* Real Timer Prescale Timer Control */
DEFCW(  RTCPS             , RTCPS_)
#define RTCIV_              (0x04AEu)  /* Real Time Clock Interrupt Vector */
DEFW(   RTCIV             , RTCIV_)
#define RTCTIM0_            (0x04B0u)  /* Real Time Clock Time 0 */
DEFCW(  RTCTIM0           , RTCTIM0_)
#define RTCTIM1_            (0x04B2u)  /* Real Time Clock Time 1 */
DEFCW(  RTCTIM1           , RTCTIM1_)
#define RTCDATE_            (0x04B4u)  /* Real Time Clock Date */
DEFCW(  RTCDATE           , RTCDATE_)
#define RTCYEAR_            (0x04B6u)  /* Real Time Clock Year */
DEFCW(  RTCYEAR           , RTCYEAR_)
#define RTCAMINHR_          (0x04B8u)  /* Real Time Clock Alarm Min/Hour */
DEFCW(  RTCAMINHR         , RTCAMINHR_)
#define RTCADOWDAY_         (0x04BAu)  /* Real Time Clock Alarm day of week/day */
DEFCW(  RTCADOWDAY        , RTCADOWDAY_)
#define BIN2BCD_            (0x04BCu)  /* Real Time Binary-to-BCD conversion register */
DEFW(   BIN2BCD           , BIN2BCD_)
#define BCD2BIN_            (0x04BEu)  /* Real Time BCD-to-binary conversion register */
DEFW(   BCD2BIN           , BCD2BIN_)

#define RTCCTL0             RTCCTL01_L  /* Real Time Clock Control 0 */
#define RTCCTL1             RTCCTL01_H  /* Real Time Clock Control 1 */
#define RTCCTL2             RTCCTL23_L  /* Real Time Clock Control 2 */
#define RTCCTL3             RTCCTL23_H  /* Real Time Clock Control 3 */
#define RTCNT12             RTCTIM0
#define RTCNT34             RTCTIM1
#define RTCNT1              RTCTIM0_L
#define RTCNT2              RTCTIM0_H
#define RTCNT3              RTCTIM1_L
#define RTCNT4              RTCTIM1_H
#define RTCSEC              RTCTIM0_L
#define RTCMIN              RTCTIM0_H
#define RTCHOUR             RTCTIM1_L
#define RTCDOW              RTCTIM1_H
#define RTCDAY              RTCDATE_L
#define RTCMON              RTCDATE_H
#define RTCYEARL            RTCYEAR_L
#define RTCYEARH            RTCYEAR_H
#define RT0PS               RTCPS_L
#define RT1PS               RTCPS_H
#define RTCAMIN             RTCAMINHR_L  /* Real Time Clock Alarm Min */
#define RTCAHOUR            RTCAMINHR_H  /* Real Time Clock Alarm Hour */
#define RTCADOW             RTCADOWDAY_L /* Real Time Clock Alarm day of week */
#define RTCADAY             RTCADOWDAY_H /* Real Time Clock Alarm day */

/* RTCCTL01 Control Bits */
#define RTCBCD              (0x8000u)     /* RTC BCD  0:Binary / 1:BCD */
#define RTCHOLD             (0x4000u)     /* RTC Hold */
//#define RESERVED            (0x2000u)     /* RESERVED */
#define RTCRDY              (0x1000u)     /* RTC Ready */
//#define RESERVED            (0x0800u)     /* RESERVED */
//#define RESERVED            (0x0400u)     /* RESERVED */
#define RTCTEV1             (0x0200u)     /* RTC Time Event 1 */
#define RTCTEV0             (0x0100u)     /* RTC Time Event 0 */
#define RTCOFIE             (0x0080u)     /* RTC 32kHz cyrstal oscillator fault interrupt enable */
#define RTCTEVIE            (0x0040u)     /* RTC Time Event Interrupt Enable Flag */
#define RTCAIE              (0x0020u)     /* RTC Alarm Interrupt Enable Flag */
#define RTCRDYIE            (0x0010u)     /* RTC Ready Interrupt Enable Flag */
#define RTCOFIFG            (0x0008u)     /* RTC 32kHz cyrstal oscillator fault interrupt flag */
#define RTCTEVIFG           (0x0004u)     /* RTC Time Event Interrupt Flag */
#define RTCAIFG             (0x0002u)     /* RTC Alarm Interrupt Flag */
#define RTCRDYIFG           (0x0001u)     /* RTC Ready Interrupt Flag */

/* RTCCTL01 Control Bits */
//#define RESERVED            (0x2000u)     /* RESERVED */
//#define RESERVED            (0x0800u)     /* RESERVED */
//#define RESERVED            (0x0400u)     /* RESERVED */
#define RTCOFIE_L           (0x0080u)     /* RTC 32kHz cyrstal oscillator fault interrupt enable */
#define RTCTEVIE_L          (0x0040u)     /* RTC Time Event Interrupt Enable Flag */
#define RTCAIE_L            (0x0020u)     /* RTC Alarm Interrupt Enable Flag */
#define RTCRDYIE_L          (0x0010u)     /* RTC Ready Interrupt Enable Flag */
#define RTCOFIFG_L          (0x0008u)     /* RTC 32kHz cyrstal oscillator fault interrupt flag */
#define RTCTEVIFG_L         (0x0004u)     /* RTC Time Event Interrupt Flag */
#define RTCAIFG_L           (0x0002u)     /* RTC Alarm Interrupt Flag */
#define RTCRDYIFG_L         (0x0001u)     /* RTC Ready Interrupt Flag */

/* RTCCTL01 Control Bits */
#define RTCBCD_H            (0x0080u)     /* RTC BCD  0:Binary / 1:BCD */
#define RTCHOLD_H           (0x0040u)     /* RTC Hold */
//#define RESERVED            (0x2000u)     /* RESERVED */
#define RTCRDY_H            (0x0010u)     /* RTC Ready */
//#define RESERVED            (0x0800u)     /* RESERVED */
//#define RESERVED            (0x0400u)     /* RESERVED */
#define RTCTEV1_H           (0x0002u)     /* RTC Time Event 1 */
#define RTCTEV0_H           (0x0001u)     /* RTC Time Event 0 */

#define RTCTEV_0            (0x0000u)     /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV_1            (0x0100u)     /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV_2            (0x0200u)     /* RTC Time Event: 2 (12:00 changed) */
#define RTCTEV_3            (0x0300u)     /* RTC Time Event: 3 (00:00 changed) */
#define RTCTEV__MIN         (0x0000u)     /* RTC Time Event: 0 (Min. changed) */
#define RTCTEV__HOUR        (0x0100u)     /* RTC Time Event: 1 (Hour changed) */
#define RTCTEV__0000        (0x0200u)     /* RTC Time Event: 2 (00:00 changed) */
#define RTCTEV__1200        (0x0300u)     /* RTC Time Event: 3 (12:00 changed) */

/* RTCCTL23 Control Bits */
#define RTCCALF1            (0x0200u)     /* RTC Calibration Frequency Bit 1 */
#define RTCCALF0            (0x0100u)     /* RTC Calibration Frequency Bit 0 */
#define RTCCALS             (0x0080u)     /* RTC Calibration Sign */
//#define Reserved          (0x0040u)
#define RTCCAL5             (0x0020u)     /* RTC Calibration Bit 5 */
#define RTCCAL4             (0x0010u)     /* RTC Calibration Bit 4 */
#define RTCCAL3             (0x0008u)     /* RTC Calibration Bit 3 */
#define RTCCAL2             (0x0004u)     /* RTC Calibration Bit 2 */
#define RTCCAL1             (0x0002u)     /* RTC Calibration Bit 1 */
#define RTCCAL0             (0x0001u)     /* RTC Calibration Bit 0 */

/* RTCCTL23 Control Bits */
#define RTCCALS_L           (0x0080u)     /* RTC Calibration Sign */
//#define Reserved          (0x0040u)
#define RTCCAL5_L           (0x0020u)     /* RTC Calibration Bit 5 */
#define RTCCAL4_L           (0x0010u)     /* RTC Calibration Bit 4 */
#define RTCCAL3_L           (0x0008u)     /* RTC Calibration Bit 3 */
#define RTCCAL2_L           (0x0004u)     /* RTC Calibration Bit 2 */
#define RTCCAL1_L           (0x0002u)     /* RTC Calibration Bit 1 */
#define RTCCAL0_L           (0x0001u)     /* RTC Calibration Bit 0 */

/* RTCCTL23 Control Bits */
#define RTCCALF1_H          (0x0002u)     /* RTC Calibration Frequency Bit 1 */
#define RTCCALF0_H          (0x0001u)     /* RTC Calibration Frequency Bit 0 */
//#define Reserved          (0x0040u)

#define RTCCALF_0           (0x0000u)     /* RTC Calibration Frequency: No Output */
#define RTCCALF_1           (0x0100u)     /* RTC Calibration Frequency: 512 Hz */
#define RTCCALF_2           (0x0200u)     /* RTC Calibration Frequency: 256 Hz */
#define RTCCALF_3           (0x0300u)     /* RTC Calibration Frequency: 1 Hz */

/* RTCPS0CTL Control Bits */
//#define Reserved          (0x0080u)
//#define Reserved          (0x0040u)
//#define Reserved          (0x0020u)
#define RT0IP2              (0x0010u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 2 */
#define RT0IP1              (0x0008u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 1 */
#define RT0IP0              (0x0004u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 0 */
#define RT0PSIE             (0x0002u)     /* RTC Prescale Timer 0 Interrupt Enable Flag */
#define RT0PSIFG            (0x0001u)     /* RTC Prescale Timer 0 Interrupt Flag */

/* RTCPS0CTL Control Bits */
//#define Reserved          (0x0080u)
//#define Reserved          (0x0040u)
//#define Reserved          (0x0020u)
#define RT0IP2_L            (0x0010u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 2 */
#define RT0IP1_L            (0x0008u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 1 */
#define RT0IP0_L            (0x0004u)     /* RTC Prescale Timer 0 Interrupt Interval Bit: 0 */
#define RT0PSIE_L           (0x0002u)     /* RTC Prescale Timer 0 Interrupt Enable Flag */
#define RT0PSIFG_L          (0x0001u)     /* RTC Prescale Timer 0 Interrupt Flag */

/* RTCPS0CTL Control Bits */
//#define Reserved          (0x0080u)
//#define Reserved          (0x0040u)
//#define Reserved          (0x0020u)

#define RT0IP_0             (0x0000u)     /* RTC Prescale Timer 0 Interrupt Interval /2 */
#define RT0IP_1             (0x0004u)     /* RTC Prescale Timer 0 Interrupt Interval /4 */
#define RT0IP_2             (0x0008u)     /* RTC Prescale Timer 0 Interrupt Interval /8 */
#define RT0IP_3             (0x000Cu)     /* RTC Prescale Timer 0 Interrupt Interval /16 */
#define RT0IP_4             (0x0010u)     /* RTC Prescale Timer 0 Interrupt Interval /32 */
#define RT0IP_5             (0x0014u)     /* RTC Prescale Timer 0 Interrupt Interval /64 */
#define RT0IP_6             (0x0018u)     /* RTC Prescale Timer 0 Interrupt Interval /128 */
#define RT0IP_7             (0x001Cu)     /* RTC Prescale Timer 0 Interrupt Interval /256 */

#define RT0IP__2            (0x0000u)     /* RTC Prescale Timer 0 Interrupt Interval /2 */
#define RT0IP__4            (0x0004u)     /* RTC Prescale Timer 0 Interrupt Interval /4 */
#define RT0IP__8            (0x0008u)     /* RTC Prescale Timer 0 Interrupt Interval /8 */
#define RT0IP__16           (0x000Cu)     /* RTC Prescale Timer 0 Interrupt Interval /16 */
#define RT0IP__32           (0x0010u)     /* RTC Prescale Timer 0 Interrupt Interval /32 */
#define RT0IP__64           (0x0014u)     /* RTC Prescale Timer 0 Interrupt Interval /64 */
#define RT0IP__128          (0x0018u)     /* RTC Prescale Timer 0 Interrupt Interval /128 */
#define RT0IP__256          (0x001Cu)     /* RTC Prescale Timer 0 Interrupt Interval /256 */

/* RTCPS1CTL Control Bits */
//#define Reserved          (0x0080u)
//#define Reserved          (0x0040u)
//#define Reserved          (0x0020u)
#define RT1IP2              (0x0010u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 2 */
#define RT1IP1              (0x0008u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 1 */
#define RT1IP0              (0x0004u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 0 */
#define RT1PSIE             (0x0002u)     /* RTC Prescale Timer 1 Interrupt Enable Flag */
#define RT1PSIFG            (0x0001u)     /* RTC Prescale Timer 1 Interrupt Flag */

/* RTCPS1CTL Control Bits */
//#define Reserved          (0x0080u)
//#define Reserved          (0x0040u)
//#define Reserved          (0x0020u)
#define RT1IP2_L            (0x0010u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 2 */
#define RT1IP1_L            (0x0008u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 1 */
#define RT1IP0_L            (0x0004u)     /* RTC Prescale Timer 1 Interrupt Interval Bit: 0 */
#define RT1PSIE_L           (0x0002u)     /* RTC Prescale Timer 1 Interrupt Enable Flag */
#define RT1PSIFG_L          (0x0001u)     /* RTC Prescale Timer 1 Interrupt Flag */

/* RTCPS1CTL Control Bits */
//#define Reserved          (0x0080u)
//#define Reserved          (0x0040u)
//#define Reserved          (0x0020u)

#define RT1IP_0             (0x0000u)     /* RTC Prescale Timer 1 Interrupt Interval /2 */
#define RT1IP_1             (0x0004u)     /* RTC Prescale Timer 1 Interrupt Interval /4 */
#define RT1IP_2             (0x0008u)     /* RTC Prescale Timer 1 Interrupt Interval /8 */
#define RT1IP_3             (0x000Cu)     /* RTC Prescale Timer 1 Interrupt Interval /16 */
#define RT1IP_4             (0x0010u)     /* RTC Prescale Timer 1 Interrupt Interval /32 */
#define RT1IP_5             (0x0014u)     /* RTC Prescale Timer 1 Interrupt Interval /64 */
#define RT1IP_6             (0x0018u)     /* RTC Prescale Timer 1 Interrupt Interval /128 */
#define RT1IP_7             (0x001Cu)     /* RTC Prescale Timer 1 Interrupt Interval /256 */

#define RT1IP__2            (0x0000u)     /* RTC Prescale Timer 1 Interrupt Interval /2 */
#define RT1IP__4            (0x0004u)     /* RTC Prescale Timer 1 Interrupt Interval /4 */
#define RT1IP__8            (0x0008u)     /* RTC Prescale Timer 1 Interrupt Interval /8 */
#define RT1IP__16           (0x000Cu)     /* RTC Prescale Timer 1 Interrupt Interval /16 */
#define RT1IP__32           (0x0010u)     /* RTC Prescale Timer 1 Interrupt Interval /32 */
#define RT1IP__64           (0x0014u)     /* RTC Prescale Timer 1 Interrupt Interval /64 */
#define RT1IP__128          (0x0018u)     /* RTC Prescale Timer 1 Interrupt Interval /128 */
#define RT1IP__256          (0x001Cu)     /* RTC Prescale Timer 1 Interrupt Interval /256 */

/* RTC Definitions */
#define RTCIV_NONE           (0x0000u)    /* No Interrupt pending */
#define RTCIV_RTCRDYIFG      (0x0002u)    /* RTC ready: RTCRDYIFG */
#define RTCIV_RTCTEVIFG      (0x0004u)    /* RTC interval timer: RTCTEVIFG */
#define RTCIV_RTCAIFG        (0x0006u)    /* RTC user alarm: RTCAIFG */
#define RTCIV_RT0PSIFG       (0x0008u)    /* RTC prescaler 0: RT0PSIFG */
#define RTCIV_RT1PSIFG       (0x000Au)    /* RTC prescaler 1: RT1PSIFG */
#define RTCIV_RTCOFIFG       (0x000Cu)    /* RTC Oscillator fault */

/* Legacy Definitions */
#define RTC_NONE           (0x0000u)      /* No Interrupt pending */
#define RTC_RTCRDYIFG      (0x0002u)      /* RTC ready: RTCRDYIFG */
#define RTC_RTCTEVIFG      (0x0004u)      /* RTC interval timer: RTCTEVIFG */
#define RTC_RTCAIFG        (0x0006u)      /* RTC user alarm: RTCAIFG */
#define RTC_RT0PSIFG       (0x0008u)      /* RTC prescaler 0: RT0PSIFG */
#define RTC_RT1PSIFG       (0x000Au)      /* RTC prescaler 1: RT1PSIFG */
#define RTC_RTCOFIFG       (0x000Cu)      /* RTC Oscillator fault */

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

#define WDTIE_L             (0x0001u)  /* WDT Interrupt Enable */
#define OFIE_L              (0x0002u)  /* Osc Fault Enable */
//#define Reserved          (0x0004u)
#define VMAIE_L             (0x0008u)  /* Vacant Memory Interrupt Enable */
#define NMIIE_L             (0x0010u)  /* NMI Interrupt Enable */
#define JMBINIE_L           (0x0040u)  /* JTAG Mail Box input Interrupt Enable */
#define JMBOUTIE_L          (0x0080u)  /* JTAG Mail Box output Interrupt Enable */

//#define Reserved          (0x0004u)

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
* SYS - System Module
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

/* SYSUNIV Definitions */
#define SYSUNIV_NONE       (0x0000u)    /* No Interrupt pending */
#define SYSUNIV_NMIIFG     (0x0002u)    /* SYSUNIV : NMIIFG */
#define SYSUNIV_OFIFG      (0x0004u)    /* SYSUNIV : Osc. Fail - OFIFG */

/* SYSSNIV Definitions */
#define SYSSNIV_NONE       (0x0000u)    /* No Interrupt pending */
#define SYSSNIV_DBDIFG     (0x0002u)    /* SYSSNIV : FRAM Double bit Error */
#define SYSSNIV_ACCTIMIFG  (0x0004u)    /* SYSSNIV : Access time error */
#define SYSSNIV_MPUSEGIIFG (0x0006u)    /* SYSSNIV : MPUSEGIIFG violation */
#define SYSSNIV_MPUSEG1IFG (0x0008u)    /* SYSSNIV : MPUSEG1IFG violation */
#define SYSSNIV_MPUSEG2IFG (0x000Au)    /* SYSSNIV : MPUSEG2IFG violation */
#define SYSSNIV_MPUSEG3IFG (0x000Cu)    /* SYSSNIV : MPUSEG3IFG violation */
#define SYSSNIV_ACCVIFG    (0x000Eu)    /* SYSSNIV : Access violation */
#define SYSSNIV_VMAIFG     (0x0010u)    /* SYSSNIV : VMAIFG */
#define SYSSNIV_JMBINIFG   (0x0012u)    /* SYSSNIV : JMBINIFG */
#define SYSSNIV_JMBOUTIFG  (0x0014u)    /* SYSSNIV : JMBOUTIFG */
#define SYSSNIV_SBDIFG     (0x0016u)    /* SYSSNIV : FRAM Single Bit error */

/* SYSRSTIV Definitions */
#define SYSRSTIV_NONE      (0x0000u)    /* No Interrupt pending */
#define SYSRSTIV_BOR       (0x0002u)    /* SYSRSTIV : BOR */
#define SYSRSTIV_RSTNMI    (0x0004u)    /* SYSRSTIV : RST/NMI */
#define SYSRSTIV_DOBOR     (0x0006u)    /* SYSRSTIV : Do BOR */
#define SYSRSTIV_LPM5WU    (0x0008u)    /* SYSRSTIV : Port LPM5 Wake Up */
#define SYSRSTIV_SECYV     (0x000Au)    /* SYSRSTIV : Security violation */
#define SYSRSTIV_SVSLIFG   (0x000Cu)    /* SYSRSTIV : SVSLIFG */
#define SYSRSTIV_SVSHIFG   (0x000Eu)    /* SYSRSTIV : SVSHIFG */
#define SYSRSTIV_RES10     (0x0010u)    /* SYSRSTIV : Reserved */
#define SYSRSTIV_RES12     (0x0012u)    /* SYSRSTIV : Reserved */
#define SYSRSTIV_DOPOR     (0x0014u)    /* SYSRSTIV : Do POR */
#define SYSRSTIV_WDTTO     (0x0016u)    /* SYSRSTIV : WDT Time out */
#define SYSRSTIV_WDTKEY    (0x0018u)    /* SYSRSTIV : WDTKEY violation */
#define SYSRSTIV_FRCTLPW   (0x001Au)    /* SYSRSTIV : FRAM Key violation */
#define SYSRSTIV_DBDIFG    (0x001Cu)    /* SYSRSTIV : FRAM Double bit Error */
#define SYSRSTIV_PERF      (0x001Eu)    /* SYSRSTIV : peripheral/config area fetch */
#define SYSRSTIV_PMMKEY    (0x0020u)    /* SYSRSTIV : PMMKEY violation */
#define SYSRSTIV_MPUKEY    (0x0022u)    /* SYSRSTIV : MPUKEY violation */
#define SYSRSTIV_CSKEY     (0x0024u)    /* SYSRSTIV : CSKEY violation */
#define SYSRSTIV_MPUSEGIIFG (0x0026u)   /* SYSRSTIV : MPUSEGIIFG violation */
#define SYSRSTIV_MPUSEG1IFG (0x0028u)   /* SYSRSTIV : MPUSEG1IFG violation */
#define SYSRSTIV_MPUSEG2IFG (0x002Au)   /* SYSRSTIV : MPUSEG2IFG violation */
#define SYSRSTIV_MPUSEG3IFG (0x002Cu)   /* SYSRSTIV : MPUSEG3IFG violation */

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
* Timer0_B3
************************************************************/
#define __MSP430_HAS_T0B3__            /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_T0B3__ 0x03C0

#define  TB0CTL_             (0x03C0u)  /* Timer0_B7 Control */
DEFW(    TB0CTL            , TB0CTL_)
#define  TB0CCTL0_           (0x03C2u)  /* Timer0_B7 Capture/Compare Control 0 */
DEFW(    TB0CCTL0          , TB0CCTL0_)
#define  TB0CCTL1_           (0x03C4u)  /* Timer0_B7 Capture/Compare Control 1 */
DEFW(    TB0CCTL1          , TB0CCTL1_)
#define  TB0CCTL2_           (0x03C6u)  /* Timer0_B7 Capture/Compare Control 2 */
DEFW(    TB0CCTL2          , TB0CCTL2_)
#define  TB0R_               (0x03D0u)  /* Timer0_B7 */
DEFW(    TB0R              , TB0R_)
#define  TB0CCR0_            (0x03D2u)  /* Timer0_B7 Capture/Compare 0 */
DEFW(    TB0CCR0           , TB0CCR0_)
#define  TB0CCR1_            (0x03D4u)  /* Timer0_B7 Capture/Compare 1 */
DEFW(    TB0CCR1           , TB0CCR1_)
#define  TB0CCR2_            (0x03D6u)  /* Timer0_B7 Capture/Compare 2 */
DEFW(    TB0CCR2           , TB0CCR2_)
#define  TB0EX0_             (0x03E0u)  /* Timer0_B7 Expansion Register 0 */
DEFW(    TB0EX0            , TB0EX0_)
#define  TB0IV_              (0x03EEu)  /* Timer0_B7 Interrupt Vector Word */
DEFW(    TB0IV             , TB0IV_)

/* Legacy Type Definitions for TimerB */
#define TBCTL                TB0CTL    /* Timer0_B7 Control */
#define TBCCTL0              TB0CCTL0  /* Timer0_B7 Capture/Compare Control 0 */
#define TBCCTL1              TB0CCTL1  /* Timer0_B7 Capture/Compare Control 1 */
#define TBCCTL2              TB0CCTL2  /* Timer0_B7 Capture/Compare Control 2 */
#define TBR                  TB0R      /* Timer0_B7 */
#define TBCCR0               TB0CCR0   /* Timer0_B7 Capture/Compare 0 */
#define TBCCR1               TB0CCR1   /* Timer0_B7 Capture/Compare 1 */
#define TBCCR2               TB0CCR2   /* Timer0_B7 Capture/Compare 2 */
#define TBEX0                TB0EX0    /* Timer0_B7 Expansion Register 0 */
#define TBIV                 TB0IV     /* Timer0_B7 Interrupt Vector Word */
#define TIMERB1_VECTOR       TIMER0_B1_VECTOR /* Timer0_B7 CC1-6, TB */
#define TIMERB0_VECTOR       TIMER0_B0_VECTOR /* Timer0_B7 CC0 */

/* TBxCTL Control Bits */
#define TBCLGRP1            (0x4000u)  /* Timer0_B7 Compare latch load group 1 */
#define TBCLGRP0            (0x2000u)  /* Timer0_B7 Compare latch load group 0 */
#define CNTL1               (0x1000u)  /* Counter lenght 1 */
#define CNTL0               (0x0800u)  /* Counter lenght 0 */
#define TBSSEL1             (0x0200u)  /* Clock source 1 */
#define TBSSEL0             (0x0100u)  /* Clock source 0 */
#define TBCLR               (0x0004u)  /* Timer0_B7 counter clear */
#define TBIE                (0x0002u)  /* Timer0_B7 interrupt enable */
#define TBIFG               (0x0001u)  /* Timer0_B7 interrupt flag */

#define SHR1                (0x4000u)  /* Timer0_B7 Compare latch load group 1 */
#define SHR0                (0x2000u)  /* Timer0_B7 Compare latch load group 0 */

#define TBSSEL_0            (0*0x0100u)  /* Clock Source: TBCLK */
#define TBSSEL_1            (1*0x0100u)  /* Clock Source: ACLK  */
#define TBSSEL_2            (2*0x0100u)  /* Clock Source: SMCLK */
#define TBSSEL_3            (3*0x0100u)  /* Clock Source: INCLK */
#define CNTL_0              (0*0x0800u)  /* Counter lenght: 16 bit */
#define CNTL_1              (1*0x0800u)  /* Counter lenght: 12 bit */
#define CNTL_2              (2*0x0800u)  /* Counter lenght: 10 bit */
#define CNTL_3              (3*0x0800u)  /* Counter lenght:  8 bit */
#define SHR_0               (0*0x2000u)  /* Timer0_B7 Group: 0 - individually */
#define SHR_1               (1*0x2000u)  /* Timer0_B7 Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define SHR_2               (2*0x2000u)  /* Timer0_B7 Group: 2 - 2 groups (1-3, 4-6)*/
#define SHR_3               (3*0x2000u)  /* Timer0_B7 Group: 3 - 1 group (all) */
#define TBCLGRP_0           (0*0x2000u)  /* Timer0_B7 Group: 0 - individually */
#define TBCLGRP_1           (1*0x2000u)  /* Timer0_B7 Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define TBCLGRP_2           (2*0x2000u)  /* Timer0_B7 Group: 2 - 2 groups (1-3, 4-6)*/
#define TBCLGRP_3           (3*0x2000u)  /* Timer0_B7 Group: 3 - 1 group (all) */
#define TBSSEL__TACLK       (0*0x100u) /* Timer0_B7 clock source select: 0 - TACLK */
#define TBSSEL__ACLK        (1*0x100u) /* Timer0_B7 clock source select: 1 - ACLK  */
#define TBSSEL__SMCLK       (2*0x100u) /* Timer0_B7 clock source select: 2 - SMCLK */
#define TBSSEL__INCLK       (3*0x100u) /* Timer0_B7 clock source select: 3 - INCLK */
#define CNTL__16            (0*0x0800u)  /* Counter lenght: 16 bit */
#define CNTL__12            (1*0x0800u)  /* Counter lenght: 12 bit */
#define CNTL__10            (2*0x0800u)  /* Counter lenght: 10 bit */
#define CNTL__8             (3*0x0800u)  /* Counter lenght:  8 bit */

/* Additional Timer B Control Register bits are defined in Timer A */
/* TBxCCTLx Control Bits */
#define CLLD1               (0x0400u)  /* Compare latch load source 1 */
#define CLLD0               (0x0200u)  /* Compare latch load source 0 */

#define SLSHR1              (0x0400u)  /* Compare latch load source 1 */
#define SLSHR0              (0x0200u)  /* Compare latch load source 0 */

#define SLSHR_0             (0*0x0200u) /* Compare latch load sourec : 0 - immediate */
#define SLSHR_1             (1*0x0200u) /* Compare latch load sourec : 1 - TBR counts to 0 */
#define SLSHR_2             (2*0x0200u) /* Compare latch load sourec : 2 - up/down */
#define SLSHR_3             (3*0x0200u) /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

#define CLLD_0              (0*0x0200u) /* Compare latch load sourec : 0 - immediate */
#define CLLD_1              (1*0x0200u) /* Compare latch load sourec : 1 - TBR counts to 0 */
#define CLLD_2              (2*0x0200u) /* Compare latch load sourec : 2 - up/down */
#define CLLD_3              (3*0x0200u) /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

/* TBxEX0 Control Bits */
#define TBIDEX0             (0x0001u)   /* Timer0_B7 Input divider expansion Bit: 0 */
#define TBIDEX1             (0x0002u)   /* Timer0_B7 Input divider expansion Bit: 1 */
#define TBIDEX2             (0x0004u)   /* Timer0_B7 Input divider expansion Bit: 2 */

#define TBIDEX_0            (0*0x0001u) /* Timer0_B7 Input divider expansion : /1 */
#define TBIDEX_1            (1*0x0001u) /* Timer0_B7 Input divider expansion : /2 */
#define TBIDEX_2            (2*0x0001u) /* Timer0_B7 Input divider expansion : /3 */
#define TBIDEX_3            (3*0x0001u) /* Timer0_B7 Input divider expansion : /4 */
#define TBIDEX_4            (4*0x0001u) /* Timer0_B7 Input divider expansion : /5 */
#define TBIDEX_5            (5*0x0001u) /* Timer0_B7 Input divider expansion : /6 */
#define TBIDEX_6            (6*0x0001u) /* Timer0_B7 Input divider expansion : /7 */
#define TBIDEX_7            (7*0x0001u) /* Timer0_B7 Input divider expansion : /8 */
#define TBIDEX__1           (0*0x0001u) /* Timer0_B7 Input divider expansion : /1 */
#define TBIDEX__2           (1*0x0001u) /* Timer0_B7 Input divider expansion : /2 */
#define TBIDEX__3           (2*0x0001u) /* Timer0_B7 Input divider expansion : /3 */
#define TBIDEX__4           (3*0x0001u) /* Timer0_B7 Input divider expansion : /4 */
#define TBIDEX__5           (4*0x0001u) /* Timer0_B7 Input divider expansion : /5 */
#define TBIDEX__6           (5*0x0001u) /* Timer0_B7 Input divider expansion : /6 */
#define TBIDEX__7           (6*0x0001u) /* Timer0_B7 Input divider expansion : /7 */
#define TBIDEX__8           (7*0x0001u) /* Timer0_B7 Input divider expansion : /8 */

/* TB0IV Definitions */
#define TB0IV_NONE          (0x0000u)    /* No Interrupt pending */
#define TB0IV_TB1CCR1       (0x0002u)    /* TBCCR1_CCIFG */
#define TB0IV_TB1CCR2       (0x0004u)    /* TBCCR2_CCIFG */
#define TB0IV_3             (0x0006u)    /* Reserved */
#define TB0IV_4             (0x0008u)    /* Reserved */
#define TB0IV_5             (0x000Au)    /* Reserved */
#define TB0IV_6             (0x000Cu)    /* Reserved */
#define TB0IV_TB0IFG        (0x000Eu)    /* TBIFG */


/************************************************************
* USCI A0
************************************************************/
#define __MSP430_HAS_EUSCI_A0__      /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_EUSCI_A0__ 0x05C0

#define UCA0CTLW0_          (0x05C0u)  /* USCI A0 Control Word Register 0 */
DEFCW(  UCA0CTLW0         , UCA0CTLW0_)
#define UCA0CTL1            UCA0CTLW0_L  /* USCI A0 Control Register 1 */
#define UCA0CTL0            UCA0CTLW0_H  /* USCI A0 Control Register 0 */
#define UCA0CTLW1_          (0x05C2u)  /* USCI A0 Control Word Register 1 */
DEFCW(  UCA0CTLW1         , UCA0CTLW1_)
#define UCA0BRW_            (0x05C6u)  /* USCI A0 Baud Word Rate 0 */
DEFCW(  UCA0BRW           , UCA0BRW_)
#define UCA0BR0             UCA0BRW_L /* USCI A0 Baud Rate 0 */
#define UCA0BR1             UCA0BRW_H /* USCI A0 Baud Rate 1 */
#define UCA0MCTLW_          (0x05C8u)  /* USCI A0 Modulation Control */
DEFCW(  UCA0MCTLW         , UCA0MCTLW_)
#define UCA0STATW_          (0x05CAu)  /* USCI A0 Status Register */
DEFC(   UCA0STATW         , UCA0STATW_)
#define UCA0RXBUF_         (0x05CCu)  /* USCI A0 Receive Buffer */
READ_ONLY_DEFCW( UCA0RXBUF     , UCA0RXBUF_)
#define  UCA0TXBUF_         (0x05CEu)  /* USCI A0 Transmit Buffer */
DEFCW(   UCA0TXBUF        , UCA0TXBUF_)
#define UCA0ABCTL_          (0x05D0u)  /* USCI A0 LIN Control */
DEFC(   UCA0ABCTL         , UCA0ABCTL_)
#define UCA0IRCTL_          (0x05D2u)  /* USCI A0 IrDA Transmit Control */
DEFCW(  UCA0IRCTL         , UCA0IRCTL_)
#define UCA0IRTCTL          UCA0IRCTL_L  /* USCI A0 IrDA Transmit Control */
#define UCA0IRRCTL          UCA0IRCTL_H  /* USCI A0 IrDA Receive Control */
#define UCA0IE_             (0x05DAu)  /* USCI A0 Interrupt Enable Register */
DEFCW(  UCA0IE            , UCA0IE_)
#define UCA0IFG_            (0x05DCu)  /* USCI A0 Interrupt Flags Register */
DEFCW(  UCA0IFG           , UCA0IFG_)
#define UCA0IV_             (0x05DEu)  /* USCI A0 Interrupt Vector Register */
DEFW(   UCA0IV            , UCA0IV_)


/************************************************************
* USCI B0
************************************************************/
#define __MSP430_HAS_EUSCI_B0__       /* Definition to show that Module is available */
#define __MSP430_BASEADDRESS_EUSCI_B0__ 0x0640


#define UCB0CTLW0_          (0x0640u)  /* USCI B0 Control Word Register 0 */
DEFCW(  UCB0CTLW0         , UCB0CTLW0_)
#define UCB0CTL1            UCB0CTLW0_L  /* USCI B0 Control Register 1 */
#define UCB0CTL0            UCB0CTLW0_H  /* USCI B0 Control Register 0 */
#define UCB0CTLW1_          (0x0642u)  /* USCI B0 Control Word Register 1 */
DEFCW(  UCB0CTLW1         , UCB0CTLW1_)
#define UCB0BRW_            (0x0646u)  /* USCI B0 Baud Word Rate 0 */
DEFCW(  UCB0BRW           , UCB0BRW_)
#define UCB0BR0             UCB0BRW_L /* USCI B0 Baud Rate 0 */
#define UCB0BR1             UCB0BRW_H /* USCI B0 Baud Rate 1 */
#define UCB0STATW_          (0x0648u)  /* USCI B0 Status Word Register */
DEFCW(  UCB0STATW         , UCB0STATW_)
#define UCB0STAT            UCB0STATW_L /* USCI B0 Status Register */
#define UCB0BCNT            UCB0STATW_H /* USCI B0 Byte Counter Register */
#define UCB0TBCNT_          (0x064Au)  /* USCI B0 Byte Counter Threshold Register */
DEFCW(  UCB0TBCNT         , UCB0TBCNT_)
#define UCB0RXBUF_         (0x064Cu)  /* USCI B0 Receive Buffer */
READ_ONLY_DEFCW( UCB0RXBUF     , UCB0RXBUF_)
#define  UCB0TXBUF_         (0x064Eu)  /* USCI B0 Transmit Buffer */
DEFCW(   UCB0TXBUF        , UCB0TXBUF_)
#define UCB0I2COA0_         (0x0654u)  /* USCI B0 I2C Own Address 0 */
DEFCW(  UCB0I2COA0        , UCB0I2COA0_)
#define UCB0I2COA1_         (0x0656u)  /* USCI B0 I2C Own Address 1 */
DEFCW(  UCB0I2COA1        , UCB0I2COA1_)
#define UCB0I2COA2_         (0x0658u)  /* USCI B0 I2C Own Address 2 */
DEFCW(  UCB0I2COA2        , UCB0I2COA2_)
#define UCB0I2COA3_         (0x065Au)  /* USCI B0 I2C Own Address 3 */
DEFCW(  UCB0I2COA3        , UCB0I2COA3_)
#define UCB0ADDRX_          (0x065Cu)  /* USCI B0 Received Address Register */
DEFCW(  UCB0ADDRX         , UCB0ADDRX_)
#define UCB0ADDMASK_        (0x065Eu)  /* USCI B0 Address Mask Register */
DEFCW(  UCB0ADDMASK       , UCB0ADDMASK_)
#define UCB0I2CSA_          (0x0660u)  /* USCI B0 I2C Slave Address */
DEFCW(  UCB0I2CSA         , UCB0I2CSA_)
#define UCB0IE_             (0x066Au)  /* USCI B0 Interrupt Enable Register */
DEFCW(  UCB0IE            , UCB0IE_)
#define UCB0IFG_            (0x066Cu)  /* USCI B0 Interrupt Flags Register */
DEFCW(  UCB0IFG           , UCB0IFG_)
#define UCB0IV_             (0x066Eu)  /* USCI B0 Interrupt Vector Register */
DEFW(   UCB0IV            , UCB0IV_)

// UCAxCTLW0 UART-Mode Control Bits
#define UCPEN               (0x8000u)    /* Async. Mode: Parity enable */
#define UCPAR               (0x4000u)    /* Async. Mode: Parity     0:odd / 1:even */
#define UCMSB               (0x2000u)    /* Async. Mode: MSB first  0:LSB / 1:MSB */
#define UC7BIT              (0x1000u)    /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
#define UCSPB               (0x0800u)    /* Async. Mode: Stop Bits  0:one / 1: two */
#define UCMODE1             (0x0400u)    /* Async. Mode: USCI Mode 1 */
#define UCMODE0             (0x0200u)    /* Async. Mode: USCI Mode 0 */
#define UCSYNC              (0x0100u)    /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */
#define UCSSEL1             (0x0080u)    /* USCI 0 Clock Source Select 1 */
#define UCSSEL0             (0x0040u)    /* USCI 0 Clock Source Select 0 */
#define UCRXEIE             (0x0020u)    /* RX Error interrupt enable */
#define UCBRKIE             (0x0010u)    /* Break interrupt enable */
#define UCDORM              (0x0008u)    /* Dormant (Sleep) Mode */
#define UCTXADDR            (0x0004u)    /* Send next Data as Address */
#define UCTXBRK             (0x0002u)    /* Send next Data as Break */
#define UCSWRST             (0x0001u)    /* USCI Software Reset */

// UCAxCTLW0 UART-Mode Control Bits
#define UCSSEL1_L           (0x0080u)    /* USCI 0 Clock Source Select 1 */
#define UCSSEL0_L           (0x0040u)    /* USCI 0 Clock Source Select 0 */
#define UCRXEIE_L           (0x0020u)    /* RX Error interrupt enable */
#define UCBRKIE_L           (0x0010u)    /* Break interrupt enable */
#define UCDORM_L            (0x0008u)    /* Dormant (Sleep) Mode */
#define UCTXADDR_L          (0x0004u)    /* Send next Data as Address */
#define UCTXBRK_L           (0x0002u)    /* Send next Data as Break */
#define UCSWRST_L           (0x0001u)    /* USCI Software Reset */

// UCAxCTLW0 UART-Mode Control Bits
#define UCPEN_H             (0x0080u)    /* Async. Mode: Parity enable */
#define UCPAR_H             (0x0040u)    /* Async. Mode: Parity     0:odd / 1:even */
#define UCMSB_H             (0x0020u)    /* Async. Mode: MSB first  0:LSB / 1:MSB */
#define UC7BIT_H            (0x0010u)    /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
#define UCSPB_H             (0x0008u)    /* Async. Mode: Stop Bits  0:one / 1: two */
#define UCMODE1_H           (0x0004u)    /* Async. Mode: USCI Mode 1 */
#define UCMODE0_H           (0x0002u)    /* Async. Mode: USCI Mode 0 */
#define UCSYNC_H            (0x0001u)    /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */

// UCxxCTLW0 SPI-Mode Control Bits
#define UCCKPH              (0x8000u)    /* Sync. Mode: Clock Phase */
#define UCCKPL              (0x4000u)    /* Sync. Mode: Clock Polarity */
#define UCMST               (0x0800u)    /* Sync. Mode: Master Select */
//#define res               (0x0020u)    /* reserved */
//#define res               (0x0010u)    /* reserved */
//#define res               (0x0008u)    /* reserved */
//#define res               (0x0004u)    /* reserved */
#define UCSTEM             (0x0002u)    /* USCI STE Mode */

// UCBxCTLW0 I2C-Mode Control Bits
#define UCA10               (0x8000u)    /* 10-bit Address Mode */
#define UCSLA10             (0x4000u)    /* 10-bit Slave Address Mode */
#define UCMM                (0x2000u)    /* Multi-Master Environment */
//#define res               (0x1000u)    /* reserved */
//#define res               (0x0100u)    /* reserved */
#define UCTXACK             (0x0020u)    /* Transmit ACK */
#define UCTR                (0x0010u)    /* Transmit/Receive Select/Flag */
#define UCTXNACK            (0x0008u)    /* Transmit NACK */
#define UCTXSTP             (0x0004u)    /* Transmit STOP */
#define UCTXSTT             (0x0002u)    /* Transmit START */

// UCBxCTLW0 I2C-Mode Control Bits
//#define res               (0x1000u)    /* reserved */
//#define res               (0x0100u)    /* reserved */
#define UCTXACK_L           (0x0020u)    /* Transmit ACK */
#define UCTR_L              (0x0010u)    /* Transmit/Receive Select/Flag */
#define UCTXNACK_L          (0x0008u)    /* Transmit NACK */
#define UCTXSTP_L           (0x0004u)    /* Transmit STOP */
#define UCTXSTT_L           (0x0002u)    /* Transmit START */

// UCBxCTLW0 I2C-Mode Control Bits
#define UCA10_H             (0x0080u)    /* 10-bit Address Mode */
#define UCSLA10_H           (0x0040u)    /* 10-bit Slave Address Mode */
#define UCMM_H              (0x0020u)    /* Multi-Master Environment */
//#define res               (0x1000u)    /* reserved */
//#define res               (0x0100u)    /* reserved */

#define UCMODE_0            (0x0000u)    /* Sync. Mode: USCI Mode: 0 */
#define UCMODE_1            (0x0200u)    /* Sync. Mode: USCI Mode: 1 */
#define UCMODE_2            (0x0400u)    /* Sync. Mode: USCI Mode: 2 */
#define UCMODE_3            (0x0600u)    /* Sync. Mode: USCI Mode: 3 */

#define UCSSEL_0            (0x0000u)    /* USCI 0 Clock Source: 0 */
#define UCSSEL_1            (0x0040u)    /* USCI 0 Clock Source: 1 */
#define UCSSEL_2            (0x0080u)    /* USCI 0 Clock Source: 2 */
#define UCSSEL_3            (0x00C0u)    /* USCI 0 Clock Source: 3 */
#define UCSSEL__UCLK        (0x0000u)    /* USCI 0 Clock Source: UCLK */
#define UCSSEL__ACLK        (0x0040u)    /* USCI 0 Clock Source: ACLK */
#define UCSSEL__SMCLK       (0x0080u)    /* USCI 0 Clock Source: SMCLK */

// UCAxCTLW1 UART-Mode Control Bits
#define UCGLIT1             (0x0002u)    /* USCI Deglitch Time Bit 1 */
#define UCGLIT0             (0x0001u)    /* USCI Deglitch Time Bit 0 */

// UCAxCTLW1 UART-Mode Control Bits
#define UCGLIT1_L           (0x0002u)    /* USCI Deglitch Time Bit 1 */
#define UCGLIT0_L           (0x0001u)    /* USCI Deglitch Time Bit 0 */

// UCAxCTLW1 UART-Mode Control Bits

// UCBxCTLW1 I2C-Mode Control Bits
#define UCETXINT            (0x0100u)    /* USCI Early UCTXIFG0 */
#define UCCLTO1             (0x0080u)    /* USCI Clock low timeout Bit: 1 */
#define UCCLTO0             (0x0040u)    /* USCI Clock low timeout Bit: 0 */
#define UCSTPNACK           (0x0020u)    /* USCI Acknowledge Stop last byte */
#define UCSWACK             (0x0010u)    /* USCI Software controlled ACK */
#define UCASTP1             (0x0008u)    /* USCI Automatic Stop condition generation Bit: 1 */
#define UCASTP0             (0x0004u)    /* USCI Automatic Stop condition generation Bit: 0 */
#define UCGLIT1             (0x0002u)    /* USCI Deglitch time Bit: 1 */
#define UCGLIT0             (0x0001u)    /* USCI Deglitch time Bit: 0 */

// UCBxCTLW1 I2C-Mode Control Bits
#define UCCLTO1_L           (0x0080u)    /* USCI Clock low timeout Bit: 1 */
#define UCCLTO0_L           (0x0040u)    /* USCI Clock low timeout Bit: 0 */
#define UCSTPNACK_L         (0x0020u)    /* USCI Acknowledge Stop last byte */
#define UCSWACK_L           (0x0010u)    /* USCI Software controlled ACK */
#define UCASTP1_L           (0x0008u)    /* USCI Automatic Stop condition generation Bit: 1 */
#define UCASTP0_L           (0x0004u)    /* USCI Automatic Stop condition generation Bit: 0 */
#define UCGLIT1_L           (0x0002u)    /* USCI Deglitch time Bit: 1 */
#define UCGLIT0_L           (0x0001u)    /* USCI Deglitch time Bit: 0 */

// UCBxCTLW1 I2C-Mode Control Bits
#define UCETXINT_H          (0x0001u)    /* USCI Early UCTXIFG0 */

#define UCGLIT_0            (0x0000u)    /* USCI Deglitch time: 0 */
#define UCGLIT_1            (0x0001u)    /* USCI Deglitch time: 1 */
#define UCGLIT_2            (0x0002u)    /* USCI Deglitch time: 2 */
#define UCGLIT_3            (0x0003u)    /* USCI Deglitch time: 3 */

#define UCASTP_0            (0x0000u)    /* USCI Automatic Stop condition generation: 0 */
#define UCASTP_1            (0x0004u)    /* USCI Automatic Stop condition generation: 1 */
#define UCASTP_2            (0x0008u)    /* USCI Automatic Stop condition generation: 2 */
#define UCASTP_3            (0x000Cu)    /* USCI Automatic Stop condition generation: 3 */

#define UCCLTO_0            (0x0000u)    /* USCI Clock low timeout: 0 */
#define UCCLTO_1            (0x0040u)    /* USCI Clock low timeout: 1 */
#define UCCLTO_2            (0x0080u)    /* USCI Clock low timeout: 2 */
#define UCCLTO_3            (0x00C0u)    /* USCI Clock low timeout: 3 */

/* UCAxMCTLW Control Bits */
#define UCBRS7              (0x8000u)    /* USCI Second Stage Modulation Select 7 */
#define UCBRS6              (0x4000u)    /* USCI Second Stage Modulation Select 6 */
#define UCBRS5              (0x2000u)    /* USCI Second Stage Modulation Select 5 */
#define UCBRS4              (0x1000u)    /* USCI Second Stage Modulation Select 4 */
#define UCBRS3              (0x0800u)    /* USCI Second Stage Modulation Select 3 */
#define UCBRS2              (0x0400u)    /* USCI Second Stage Modulation Select 2 */
#define UCBRS1              (0x0200u)    /* USCI Second Stage Modulation Select 1 */
#define UCBRS0              (0x0100u)    /* USCI Second Stage Modulation Select 0 */
#define UCBRF3              (0x0080u)    /* USCI First Stage Modulation Select 3 */
#define UCBRF2              (0x0040u)    /* USCI First Stage Modulation Select 2 */
#define UCBRF1              (0x0020u)    /* USCI First Stage Modulation Select 1 */
#define UCBRF0              (0x0010u)    /* USCI First Stage Modulation Select 0 */
#define UCOS16              (0x0001u)    /* USCI 16-times Oversampling enable */

/* UCAxMCTLW Control Bits */
#define UCBRF3_L            (0x0080u)    /* USCI First Stage Modulation Select 3 */
#define UCBRF2_L            (0x0040u)    /* USCI First Stage Modulation Select 2 */
#define UCBRF1_L            (0x0020u)    /* USCI First Stage Modulation Select 1 */
#define UCBRF0_L            (0x0010u)    /* USCI First Stage Modulation Select 0 */
#define UCOS16_L            (0x0001u)    /* USCI 16-times Oversampling enable */

/* UCAxMCTLW Control Bits */
#define UCBRS7_H            (0x0080u)    /* USCI Second Stage Modulation Select 7 */
#define UCBRS6_H            (0x0040u)    /* USCI Second Stage Modulation Select 6 */
#define UCBRS5_H            (0x0020u)    /* USCI Second Stage Modulation Select 5 */
#define UCBRS4_H            (0x0010u)    /* USCI Second Stage Modulation Select 4 */
#define UCBRS3_H            (0x0008u)    /* USCI Second Stage Modulation Select 3 */
#define UCBRS2_H            (0x0004u)    /* USCI Second Stage Modulation Select 2 */
#define UCBRS1_H            (0x0002u)    /* USCI Second Stage Modulation Select 1 */
#define UCBRS0_H            (0x0001u)    /* USCI Second Stage Modulation Select 0 */

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

/* UCAxSTATW Control Bits */
#define UCLISTEN            (0x0080u)  /* USCI Listen mode */
#define UCFE                (0x0040u)  /* USCI Frame Error Flag */
#define UCOE                (0x0020u)  /* USCI Overrun Error Flag */
#define UCPE                (0x0010u)  /* USCI Parity Error Flag */
#define UCBRK               (0x0008u)  /* USCI Break received */
#define UCRXERR             (0x0004u)  /* USCI RX Error Flag */
#define UCADDR              (0x0002u)  /* USCI Address received Flag */
#define UCBUSY              (0x0001u)  /* USCI Busy Flag */
#define UCIDLE              (0x0002u)  /* USCI Idle line detected Flag */

/* UCBxSTATW I2C Control Bits */
#define UCBCNT7             (0x8000u)  /* USCI Byte Counter Bit 7 */
#define UCBCNT6             (0x4000u)  /* USCI Byte Counter Bit 6 */
#define UCBCNT5             (0x2000u)  /* USCI Byte Counter Bit 5 */
#define UCBCNT4             (0x1000u)  /* USCI Byte Counter Bit 4 */
#define UCBCNT3             (0x0800u)  /* USCI Byte Counter Bit 3 */
#define UCBCNT2             (0x0400u)  /* USCI Byte Counter Bit 2 */
#define UCBCNT1             (0x0200u)  /* USCI Byte Counter Bit 1 */
#define UCBCNT0             (0x0100u)  /* USCI Byte Counter Bit 0 */
#define UCSCLLOW            (0x0040u)  /* SCL low */
#define UCGC                (0x0020u)  /* General Call address received Flag */
#define UCBBUSY             (0x0010u)  /* Bus Busy Flag */

/* UCBxTBCNT I2C Control Bits */
#define UCTBCNT7            (0x0080u)  /* USCI Byte Counter Bit 7 */
#define UCTBCNT6            (0x0040u)  /* USCI Byte Counter Bit 6 */
#define UCTBCNT5            (0x0020u)  /* USCI Byte Counter Bit 5 */
#define UCTBCNT4            (0x0010u)  /* USCI Byte Counter Bit 4 */
#define UCTBCNT3            (0x0008u)  /* USCI Byte Counter Bit 3 */
#define UCTBCNT2            (0x0004u)  /* USCI Byte Counter Bit 2 */
#define UCTBCNT1            (0x0002u)  /* USCI Byte Counter Bit 1 */
#define UCTBCNT0            (0x0001u)  /* USCI Byte Counter Bit 0 */

/* UCAxIRCTL Control Bits */
#define UCIRRXFL5           (0x8000u)  /* IRDA Receive Filter Length 5 */
#define UCIRRXFL4           (0x4000u)  /* IRDA Receive Filter Length 4 */
#define UCIRRXFL3           (0x2000u)  /* IRDA Receive Filter Length 3 */
#define UCIRRXFL2           (0x1000u)  /* IRDA Receive Filter Length 2 */
#define UCIRRXFL1           (0x0800u)  /* IRDA Receive Filter Length 1 */
#define UCIRRXFL0           (0x0400u)  /* IRDA Receive Filter Length 0 */
#define UCIRRXPL            (0x0200u)  /* IRDA Receive Input Polarity */
#define UCIRRXFE            (0x0100u)  /* IRDA Receive Filter enable */
#define UCIRTXPL5           (0x0080u)  /* IRDA Transmit Pulse Length 5 */
#define UCIRTXPL4           (0x0040u)  /* IRDA Transmit Pulse Length 4 */
#define UCIRTXPL3           (0x0020u)  /* IRDA Transmit Pulse Length 3 */
#define UCIRTXPL2           (0x0010u)  /* IRDA Transmit Pulse Length 2 */
#define UCIRTXPL1           (0x0008u)  /* IRDA Transmit Pulse Length 1 */
#define UCIRTXPL0           (0x0004u)  /* IRDA Transmit Pulse Length 0 */
#define UCIRTXCLK           (0x0002u)  /* IRDA Transmit Pulse Clock Select */
#define UCIREN              (0x0001u)  /* IRDA Encoder/Decoder enable */

/* UCAxIRCTL Control Bits */
#define UCIRTXPL5_L         (0x0080u)  /* IRDA Transmit Pulse Length 5 */
#define UCIRTXPL4_L         (0x0040u)  /* IRDA Transmit Pulse Length 4 */
#define UCIRTXPL3_L         (0x0020u)  /* IRDA Transmit Pulse Length 3 */
#define UCIRTXPL2_L         (0x0010u)  /* IRDA Transmit Pulse Length 2 */
#define UCIRTXPL1_L         (0x0008u)  /* IRDA Transmit Pulse Length 1 */
#define UCIRTXPL0_L         (0x0004u)  /* IRDA Transmit Pulse Length 0 */
#define UCIRTXCLK_L         (0x0002u)  /* IRDA Transmit Pulse Clock Select */
#define UCIREN_L            (0x0001u)  /* IRDA Encoder/Decoder enable */

/* UCAxIRCTL Control Bits */
#define UCIRRXFL5_H         (0x0080u)  /* IRDA Receive Filter Length 5 */
#define UCIRRXFL4_H         (0x0040u)  /* IRDA Receive Filter Length 4 */
#define UCIRRXFL3_H         (0x0020u)  /* IRDA Receive Filter Length 3 */
#define UCIRRXFL2_H         (0x0010u)  /* IRDA Receive Filter Length 2 */
#define UCIRRXFL1_H         (0x0008u)  /* IRDA Receive Filter Length 1 */
#define UCIRRXFL0_H         (0x0004u)  /* IRDA Receive Filter Length 0 */
#define UCIRRXPL_H          (0x0002u)  /* IRDA Receive Input Polarity */
#define UCIRRXFE_H          (0x0001u)  /* IRDA Receive Filter enable */

/* UCAxABCTL Control Bits */
//#define res               (0x80)    /* reserved */
//#define res               (0x40)    /* reserved */
#define UCDELIM1            (0x20)    /* Break Sync Delimiter 1 */
#define UCDELIM0            (0x10)    /* Break Sync Delimiter 0 */
#define UCSTOE              (0x08)    /* Sync-Field Timeout error */
#define UCBTOE              (0x04)    /* Break Timeout error */
//#define res               (0x02)    /* reserved */
#define UCABDEN             (0x01)    /* Auto Baud Rate detect enable */

/* UCBxI2COA0 Control Bits */
#define UCGCEN              (0x8000u)  /* I2C General Call enable */
#define UCOAEN              (0x0400u)  /* I2C Own Address enable */
#define UCOA9               (0x0200u)  /* I2C Own Address Bit 9 */
#define UCOA8               (0x0100u)  /* I2C Own Address Bit 8 */
#define UCOA7               (0x0080u)  /* I2C Own Address Bit 7 */
#define UCOA6               (0x0040u)  /* I2C Own Address Bit 6 */
#define UCOA5               (0x0020u)  /* I2C Own Address Bit 5 */
#define UCOA4               (0x0010u)  /* I2C Own Address Bit 4 */
#define UCOA3               (0x0008u)  /* I2C Own Address Bit 3 */
#define UCOA2               (0x0004u)  /* I2C Own Address Bit 2 */
#define UCOA1               (0x0002u)  /* I2C Own Address Bit 1 */
#define UCOA0               (0x0001u)  /* I2C Own Address Bit 0 */

/* UCBxI2COA0 Control Bits */
#define UCOA7_L             (0x0080u)  /* I2C Own Address Bit 7 */
#define UCOA6_L             (0x0040u)  /* I2C Own Address Bit 6 */
#define UCOA5_L             (0x0020u)  /* I2C Own Address Bit 5 */
#define UCOA4_L             (0x0010u)  /* I2C Own Address Bit 4 */
#define UCOA3_L             (0x0008u)  /* I2C Own Address Bit 3 */
#define UCOA2_L             (0x0004u)  /* I2C Own Address Bit 2 */
#define UCOA1_L             (0x0002u)  /* I2C Own Address Bit 1 */
#define UCOA0_L             (0x0001u)  /* I2C Own Address Bit 0 */

/* UCBxI2COA0 Control Bits */
#define UCGCEN_H            (0x0080u)  /* I2C General Call enable */
#define UCOAEN_H            (0x0004u)  /* I2C Own Address enable */
#define UCOA9_H             (0x0002u)  /* I2C Own Address Bit 9 */
#define UCOA8_H             (0x0001u)  /* I2C Own Address Bit 8 */

/* UCBxI2COAx Control Bits */
#define UCOAEN              (0x0400u)  /* I2C Own Address enable */
#define UCOA9               (0x0200u)  /* I2C Own Address Bit 9 */
#define UCOA8               (0x0100u)  /* I2C Own Address Bit 8 */
#define UCOA7               (0x0080u)  /* I2C Own Address Bit 7 */
#define UCOA6               (0x0040u)  /* I2C Own Address Bit 6 */
#define UCOA5               (0x0020u)  /* I2C Own Address Bit 5 */
#define UCOA4               (0x0010u)  /* I2C Own Address Bit 4 */
#define UCOA3               (0x0008u)  /* I2C Own Address Bit 3 */
#define UCOA2               (0x0004u)  /* I2C Own Address Bit 2 */
#define UCOA1               (0x0002u)  /* I2C Own Address Bit 1 */
#define UCOA0               (0x0001u)  /* I2C Own Address Bit 0 */

/* UCBxI2COAx Control Bits */
#define UCOA7_L             (0x0080u)  /* I2C Own Address Bit 7 */
#define UCOA6_L             (0x0040u)  /* I2C Own Address Bit 6 */
#define UCOA5_L             (0x0020u)  /* I2C Own Address Bit 5 */
#define UCOA4_L             (0x0010u)  /* I2C Own Address Bit 4 */
#define UCOA3_L             (0x0008u)  /* I2C Own Address Bit 3 */
#define UCOA2_L             (0x0004u)  /* I2C Own Address Bit 2 */
#define UCOA1_L             (0x0002u)  /* I2C Own Address Bit 1 */
#define UCOA0_L             (0x0001u)  /* I2C Own Address Bit 0 */

/* UCBxI2COAx Control Bits */
#define UCOAEN_H            (0x0004u)  /* I2C Own Address enable */
#define UCOA9_H             (0x0002u)  /* I2C Own Address Bit 9 */
#define UCOA8_H             (0x0001u)  /* I2C Own Address Bit 8 */

/* UCBxADDRX Control Bits */
#define UCADDRX9            (0x0200u)  /* I2C Receive Address Bit 9 */
#define UCADDRX8            (0x0100u)  /* I2C Receive Address Bit 8 */
#define UCADDRX7            (0x0080u)  /* I2C Receive Address Bit 7 */
#define UCADDRX6            (0x0040u)  /* I2C Receive Address Bit 6 */
#define UCADDRX5            (0x0020u)  /* I2C Receive Address Bit 5 */
#define UCADDRX4            (0x0010u)  /* I2C Receive Address Bit 4 */
#define UCADDRX3            (0x0008u)  /* I2C Receive Address Bit 3 */
#define UCADDRX2            (0x0004u)  /* I2C Receive Address Bit 2 */
#define UCADDRX1            (0x0002u)  /* I2C Receive Address Bit 1 */
#define UCADDRX0            (0x0001u)  /* I2C Receive Address Bit 0 */

/* UCBxADDRX Control Bits */
#define UCADDRX7_L          (0x0080u)  /* I2C Receive Address Bit 7 */
#define UCADDRX6_L          (0x0040u)  /* I2C Receive Address Bit 6 */
#define UCADDRX5_L          (0x0020u)  /* I2C Receive Address Bit 5 */
#define UCADDRX4_L          (0x0010u)  /* I2C Receive Address Bit 4 */
#define UCADDRX3_L          (0x0008u)  /* I2C Receive Address Bit 3 */
#define UCADDRX2_L          (0x0004u)  /* I2C Receive Address Bit 2 */
#define UCADDRX1_L          (0x0002u)  /* I2C Receive Address Bit 1 */
#define UCADDRX0_L          (0x0001u)  /* I2C Receive Address Bit 0 */

/* UCBxADDRX Control Bits */
#define UCADDRX9_H          (0x0002u)  /* I2C Receive Address Bit 9 */
#define UCADDRX8_H          (0x0001u)  /* I2C Receive Address Bit 8 */

/* UCBxADDMASK Control Bits */
#define UCADDMASK9            (0x0200u)  /* I2C Address Mask Bit 9 */
#define UCADDMASK8            (0x0100u)  /* I2C Address Mask Bit 8 */
#define UCADDMASK7            (0x0080u)  /* I2C Address Mask Bit 7 */
#define UCADDMASK6            (0x0040u)  /* I2C Address Mask Bit 6 */
#define UCADDMASK5            (0x0020u)  /* I2C Address Mask Bit 5 */
#define UCADDMASK4            (0x0010u)  /* I2C Address Mask Bit 4 */
#define UCADDMASK3            (0x0008u)  /* I2C Address Mask Bit 3 */
#define UCADDMASK2            (0x0004u)  /* I2C Address Mask Bit 2 */
#define UCADDMASK1            (0x0002u)  /* I2C Address Mask Bit 1 */
#define UCADDMASK0            (0x0001u)  /* I2C Address Mask Bit 0 */

/* UCBxADDMASK Control Bits */
#define UCADDMASK7_L        (0x0080u)  /* I2C Address Mask Bit 7 */
#define UCADDMASK6_L        (0x0040u)  /* I2C Address Mask Bit 6 */
#define UCADDMASK5_L        (0x0020u)  /* I2C Address Mask Bit 5 */
#define UCADDMASK4_L        (0x0010u)  /* I2C Address Mask Bit 4 */
#define UCADDMASK3_L        (0x0008u)  /* I2C Address Mask Bit 3 */
#define UCADDMASK2_L        (0x0004u)  /* I2C Address Mask Bit 2 */
#define UCADDMASK1_L        (0x0002u)  /* I2C Address Mask Bit 1 */
#define UCADDMASK0_L        (0x0001u)  /* I2C Address Mask Bit 0 */

/* UCBxADDMASK Control Bits */
#define UCADDMASK9_H        (0x0002u)  /* I2C Address Mask Bit 9 */
#define UCADDMASK8_H        (0x0001u)  /* I2C Address Mask Bit 8 */

/* UCBxI2CSA Control Bits */
#define UCSA9               (0x0200u)  /* I2C Slave Address Bit 9 */
#define UCSA8               (0x0100u)  /* I2C Slave Address Bit 8 */
#define UCSA7               (0x0080u)  /* I2C Slave Address Bit 7 */
#define UCSA6               (0x0040u)  /* I2C Slave Address Bit 6 */
#define UCSA5               (0x0020u)  /* I2C Slave Address Bit 5 */
#define UCSA4               (0x0010u)  /* I2C Slave Address Bit 4 */
#define UCSA3               (0x0008u)  /* I2C Slave Address Bit 3 */
#define UCSA2               (0x0004u)  /* I2C Slave Address Bit 2 */
#define UCSA1               (0x0002u)  /* I2C Slave Address Bit 1 */
#define UCSA0               (0x0001u)  /* I2C Slave Address Bit 0 */

/* UCBxI2CSA Control Bits */
#define UCSA7_L             (0x0080u)  /* I2C Slave Address Bit 7 */
#define UCSA6_L             (0x0040u)  /* I2C Slave Address Bit 6 */
#define UCSA5_L             (0x0020u)  /* I2C Slave Address Bit 5 */
#define UCSA4_L             (0x0010u)  /* I2C Slave Address Bit 4 */
#define UCSA3_L             (0x0008u)  /* I2C Slave Address Bit 3 */
#define UCSA2_L             (0x0004u)  /* I2C Slave Address Bit 2 */
#define UCSA1_L             (0x0002u)  /* I2C Slave Address Bit 1 */
#define UCSA0_L             (0x0001u)  /* I2C Slave Address Bit 0 */

/* UCBxI2CSA Control Bits */
#define UCSA9_H             (0x0002u)  /* I2C Slave Address Bit 9 */
#define UCSA8_H             (0x0001u)  /* I2C Slave Address Bit 8 */

/* UCAxIE UART Control Bits */
#define UCTXCPTIE           (0x0008u)  /* UART Transmit Complete Interrupt Enable */
#define UCSTTIE             (0x0004u)  /* UART Start Bit Interrupt Enalble */
#define UCTXIE              (0x0002u)  /* UART Transmit Interrupt Enable */
#define UCRXIE              (0x0001u)  /* UART Receive Interrupt Enable */

/* UCAxIE/UCBxIE SPI Control Bits */

/* UCBxIE I2C Control Bits */
#define UCBIT9IE            (0x4000u)  /* I2C Bit 9 Position Interrupt Enable 3 */
#define UCTXIE3             (0x2000u)  /* I2C Transmit Interrupt Enable 3 */
#define UCRXIE3             (0x1000u)  /* I2C Receive Interrupt Enable 3 */
#define UCTXIE2             (0x0800u)  /* I2C Transmit Interrupt Enable 2 */
#define UCRXIE2             (0x0400u)  /* I2C Receive Interrupt Enable 2 */
#define UCTXIE1             (0x0200u)  /* I2C Transmit Interrupt Enable 1 */
#define UCRXIE1             (0x0100u)  /* I2C Receive Interrupt Enable 1 */
#define UCCLTOIE            (0x0080u)  /* I2C Clock Low Timeout interrupt enable */
#define UCBCNTIE            (0x0040u)  /* I2C Automatic stop assertion interrupt enable */
#define UCNACKIE            (0x0020u)  /* I2C NACK Condition interrupt enable */
#define UCALIE              (0x0010u)  /* I2C Arbitration Lost interrupt enable */
#define UCSTPIE             (0x0008u)  /* I2C STOP Condition interrupt enable */
#define UCSTTIE             (0x0004u)  /* I2C START Condition interrupt enable */
#define UCTXIE0             (0x0002u)  /* I2C Transmit Interrupt Enable 0 */
#define UCRXIE0             (0x0001u)  /* I2C Receive Interrupt Enable 0 */

/* UCAxIFG UART Control Bits */
#define UCTXCPTIFG          (0x0008u)  /* UART Transmit Complete Interrupt Flag */
#define UCSTTIFG            (0x0004u)  /* UART Start Bit Interrupt Flag */
#define UCTXIFG             (0x0002u)  /* UART Transmit Interrupt Flag */
#define UCRXIFG             (0x0001u)  /* UART Receive Interrupt Flag */

/* UCAxIFG/UCBxIFG SPI Control Bits */
#define UCTXIFG             (0x0002u)  /* SPI Transmit Interrupt Flag */
#define UCRXIFG             (0x0001u)  /* SPI Receive Interrupt Flag */

/* UCBxIFG Control Bits */
#define UCBIT9IFG           (0x4000u)  /* I2C Bit 9 Possition Interrupt Flag 3 */
#define UCTXIFG3            (0x2000u)  /* I2C Transmit Interrupt Flag 3 */
#define UCRXIFG3            (0x1000u)  /* I2C Receive Interrupt Flag 3 */
#define UCTXIFG2            (0x0800u)  /* I2C Transmit Interrupt Flag 2 */
#define UCRXIFG2            (0x0400u)  /* I2C Receive Interrupt Flag 2 */
#define UCTXIFG1            (0x0200u)  /* I2C Transmit Interrupt Flag 1 */
#define UCRXIFG1            (0x0100u)  /* I2C Receive Interrupt Flag 1 */
#define UCCLTOIFG           (0x0080u)  /* I2C Clock low Timeout interrupt Flag */
#define UCBCNTIFG           (0x0040u)  /* I2C Byte counter interrupt flag */
#define UCNACKIFG           (0x0020u)  /* I2C NACK Condition interrupt Flag */
#define UCALIFG             (0x0010u)  /* I2C Arbitration Lost interrupt Flag */
#define UCSTPIFG            (0x0008u)  /* I2C STOP Condition interrupt Flag */
#define UCSTTIFG            (0x0004u)  /* I2C START Condition interrupt Flag */
#define UCTXIFG0            (0x0002u)  /* I2C Transmit Interrupt Flag 0 */
#define UCRXIFG0            (0x0001u)  /* I2C Receive Interrupt Flag 0 */

/* USCI UART Definitions */
#define USCI_NONE            (0x0000u)   /* No Interrupt pending */
#define USCI_UART_UCRXIFG    (0x0002u)   /* USCI UCRXIFG */
#define USCI_UART_UCTXIFG    (0x0004u)   /* USCI UCTXIFG */
#define USCI_UART_UCSTTIFG   (0x0006u)   /* USCI UCSTTIFG */
#define USCI_UART_UCTXCPTIFG (0x0008u)   /* USCI UCTXCPTIFG */

/* USCI SPI Definitions */
#define USCI_SPI_UCRXIFG    (0x0002u)    /* USCI UCRXIFG */
#define USCI_SPI_UCTXIFG    (0x0004u)    /* USCI UCTXIFG */

/* USCI I2C Definitions */
#define USCI_I2C_UCALIFG    (0x0002u)    /* USCI I2C Mode: UCALIFG */
#define USCI_I2C_UCNACKIFG  (0x0004u)    /* USCI I2C Mode: UCNACKIFG */
#define USCI_I2C_UCSTTIFG   (0x0006u)    /* USCI I2C Mode: UCSTTIFG*/
#define USCI_I2C_UCSTPIFG   (0x0008u)    /* USCI I2C Mode: UCSTPIFG*/
#define USCI_I2C_UCRXIFG3   (0x000Au)    /* USCI I2C Mode: UCRXIFG3 */
#define USCI_I2C_UCTXIFG3   (0x000Cu)    /* USCI I2C Mode: UCTXIFG3 */
#define USCI_I2C_UCRXIFG2   (0x000Eu)    /* USCI I2C Mode: UCRXIFG2 */
#define USCI_I2C_UCTXIFG2   (0x0010u)    /* USCI I2C Mode: UCTXIFG2 */
#define USCI_I2C_UCRXIFG1   (0x0012u)    /* USCI I2C Mode: UCRXIFG1 */
#define USCI_I2C_UCTXIFG1   (0x0014u)    /* USCI I2C Mode: UCTXIFG1 */
#define USCI_I2C_UCRXIFG0   (0x0016u)    /* USCI I2C Mode: UCRXIFG0 */
#define USCI_I2C_UCTXIFG0   (0x0018u)    /* USCI I2C Mode: UCTXIFG0 */
#define USCI_I2C_UCBCNTIFG  (0x001Au)    /* USCI I2C Mode: UCBCNTIFG */
#define USCI_I2C_UCCLTOIFG  (0x001Cu)    /* USCI I2C Mode: UCCLTOIFG */
#define USCI_I2C_UCBIT9IFG  (0x001Eu)    /* USCI I2C Mode: UCBIT9IFG */

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
* Interrupt Vectors (offset from 0xFF80)
************************************************************/


#define RTC_VECTOR          (39 * 2u) /* 0xFFCE RTC */
#define PORT2_VECTOR        (44 * 2u) /* 0xFFD8 Port 2 */
#define PORT1_VECTOR        (47 * 2u) /* 0xFFDE Port 1 */
#define TIMER1_A1_VECTOR    (48 * 2u) /* 0xFFE0 Timer1_A3 CC1-2, TA1 */
#define TIMER1_A0_VECTOR    (49 * 2u) /* 0xFFE2 Timer1_A3 CC0 */
#define DMA_VECTOR          (50 * 2u) /* 0xFFE4 DMA */
#define TIMER0_A1_VECTOR    (52 * 2u) /* 0xFFE8 Timer0_A5 CC1-4, TA */
#define TIMER0_A0_VECTOR    (53 * 2u) /* 0xFFEA Timer0_A5 CC0 */
#define ADC10_VECTOR        (54 * 2u) /* 0xFFEC ADC */
#define USCI_B0_VECTOR      (55 * 2u) /* 0xFFEE USCI B0 Receive/Transmit */
#define USCI_A0_VECTOR      (56 * 2u) /* 0xFFF0 USCI A0 Receive/Transmit */
#define WDT_VECTOR          (57 * 2u) /* 0xFFF2 Watchdog Timer */
#define TIMER0_B1_VECTOR    (58 * 2u) /* 0xFFF4 Timer0_B3 CC1-2, TB */
#define TIMER0_B0_VECTOR    (59 * 2u) /* 0xFFF6 Timer0_B3 CC0 */
#define COMP_D_VECTOR       (60 * 2u) /* 0xFFF8 Comparator D */
#define UNMI_VECTOR         (61 * 2u) /* 0xFFFA User Non-maskable */
#define SYSNMI_VECTOR       (62 * 2u) /* 0xFFFC System Non-maskable */
#define RESET_VECTOR        (63 * 2u) /* 0xFFFE Reset [Highest Priority] */

/************************************************************
* End of Modules
************************************************************/
#pragma language=default

#endif /* #ifndef __MSP430FR5720 */

