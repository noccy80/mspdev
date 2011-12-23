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

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------------------------------------------------------*/
/* PERIPHERAL FILE MAP                                                        */
/*----------------------------------------------------------------------------*/

/* External references resolved by a device-specific linker command file */
#define SFR_8BIT(address)   extern volatile unsigned char address
#define SFR_16BIT(address)  extern volatile unsigned int address


/************************************************************
* STANDARD BITS
************************************************************/

#define BIT0                   (0x0001)
#define BIT1                   (0x0002)
#define BIT2                   (0x0004)
#define BIT3                   (0x0008)
#define BIT4                   (0x0010)
#define BIT5                   (0x0020)
#define BIT6                   (0x0040)
#define BIT7                   (0x0080)
#define BIT8                   (0x0100)
#define BIT9                   (0x0200)
#define BITA                   (0x0400)
#define BITB                   (0x0800)
#define BITC                   (0x1000)
#define BITD                   (0x2000)
#define BITE                   (0x4000)
#define BITF                   (0x8000)

/************************************************************
* STATUS REGISTER BITS
************************************************************/

#define C                      (0x0001)
#define Z                      (0x0002)
#define N                      (0x0004)
#define V                      (0x0100)
#define GIE                    (0x0008)
#define CPUOFF                 (0x0010)
#define OSCOFF                 (0x0020)
#define SCG0                   (0x0040)
#define SCG1                   (0x0080)

/* Low Power Modes coded with Bits 4-7 in SR */

#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define LPM0                   (CPUOFF)
#define LPM1                   (SCG0+CPUOFF)
#define LPM2                   (SCG1+CPUOFF)
#define LPM3                   (SCG1+SCG0+CPUOFF)
#define LPM4                   (SCG1+SCG0+OSCOFF+CPUOFF)
/* End #defines for assembler */

#else /* Begin #defines for C */
#define LPM0_bits              (CPUOFF)
#define LPM1_bits              (SCG0+CPUOFF)
#define LPM2_bits              (SCG1+CPUOFF)
#define LPM3_bits              (SCG1+SCG0+CPUOFF)
#define LPM4_bits              (SCG1+SCG0+OSCOFF+CPUOFF)

#include "in430.h"

#define LPM0         _bis_SR_register(LPM0_bits)         /* Enter Low Power Mode 0 */
#define LPM0_EXIT    _bic_SR_register_on_exit(LPM0_bits) /* Exit Low Power Mode 0 */
#define LPM1         _bis_SR_register(LPM1_bits)         /* Enter Low Power Mode 1 */
#define LPM1_EXIT    _bic_SR_register_on_exit(LPM1_bits) /* Exit Low Power Mode 1 */
#define LPM2         _bis_SR_register(LPM2_bits)         /* Enter Low Power Mode 2 */
#define LPM2_EXIT    _bic_SR_register_on_exit(LPM2_bits) /* Exit Low Power Mode 2 */
#define LPM3         _bis_SR_register(LPM3_bits)         /* Enter Low Power Mode 3 */
#define LPM3_EXIT    _bic_SR_register_on_exit(LPM3_bits) /* Exit Low Power Mode 3 */
#define LPM4         _bis_SR_register(LPM4_bits)         /* Enter Low Power Mode 4 */
#define LPM4_EXIT    _bic_SR_register_on_exit(LPM4_bits) /* Exit Low Power Mode 4 */
#endif /* End #defines for C */

/************************************************************
* PERIPHERAL FILE MAP
************************************************************/

/************************************************************
* SPECIAL FUNCTION REGISTER ADDRESSES + CONTROL BITS
************************************************************/

SFR_8BIT(IE1);                                /* Interrupt Enable 1 */
#define WDTIE                  (0x01)         /* Watchdog Interrupt Enable */
#define OFIE                   (0x02)         /* Osc. Fault  Interrupt Enable */
#define NMIIE                  (0x10)         /* NMI Interrupt Enable */
#define ACCVIE                 (0x20)         /* Flash Access Violation Interrupt Enable */

SFR_8BIT(IFG1);                               /* Interrupt Flag 1 */
#define WDTIFG                 (0x01)         /* Watchdog Interrupt Flag */
#define OFIFG                  (0x02)         /* Osc. Fault Interrupt Flag */
#define PORIFG                 (0x04)         /* Power On Interrupt Flag */
#define RSTIFG                 (0x08)         /* Reset Interrupt Flag */
#define NMIIFG                 (0x10)         /* NMI Interrupt Flag */

SFR_8BIT(IE2);                                /* Interrupt Enable 2 */
#define UC0IE                  IE2
#define UCA0RXIE               (0x01)
#define UCA0TXIE               (0x02)
#define UCB0RXIE               (0x04)
#define UCB0TXIE               (0x08)
#define BTIE                   (0x80)

SFR_8BIT(IFG2);                               /* Interrupt Flag 2 */
#define UC0IFG                 IFG2
#define UCA0RXIFG              (0x01)
#define UCA0TXIFG              (0x02)
#define UCB0RXIFG              (0x04)
#define UCB0TXIFG              (0x08)
#define BTIFG                  (0x80)

/************************************************************
* ADC10
************************************************************/
#define __MSP430_HAS_ADC10__                  /* Definition to show that Module is available */

SFR_8BIT(ADC10DTC0);                          /* ADC10 Data Transfer Control 0 */
SFR_8BIT(ADC10DTC1);                          /* ADC10 Data Transfer Control 1 */
SFR_8BIT(ADC10AE0);                           /* ADC10 Analog Enable 0 */
SFR_8BIT(ADC10AE1);                           /* ADC10 Analog Enable 1 */

SFR_16BIT(ADC10CTL0);                         /* ADC10 Control 0 */
SFR_16BIT(ADC10CTL1);                         /* ADC10 Control 1 */
SFR_16BIT(ADC10MEM);                          /* ADC10 Memory */
SFR_16BIT(ADC10SA);                           /* ADC10 Data Transfer Start Address */

/* ADC10CTL0 */
#define ADC10SC                (0x001)        /* ADC10 Start Conversion */
#define ENC                    (0x002)        /* ADC10 Enable Conversion */
#define ADC10IFG               (0x004)        /* ADC10 Interrupt Flag */
#define ADC10IE                (0x008)        /* ADC10 Interrupt Enalbe */
#define ADC10ON                (0x010)        /* ADC10 On/Enable */
#define REFON                  (0x020)        /* ADC10 Reference on */
#define REF2_5V                (0x040)        /* ADC10 Ref 0:1.5V / 1:2.5V */
#define MSC                    (0x080)        /* ADC10 Multiple SampleConversion */
#define REFBURST               (0x100)        /* ADC10 Reference Burst Mode */
#define REFOUT                 (0x200)        /* ADC10 Enalbe output of Ref. */
#define ADC10SR                (0x400)        /* ADC10 Sampling Rate 0:200ksps / 1:50ksps */
#define ADC10SHT0              (0x800)        /* ADC10 Sample Hold Select Bit: 0 */
#define ADC10SHT1              (0x1000)       /* ADC10 Sample Hold Select Bit: 1 */
#define SREF0                  (0x2000)       /* ADC10 Reference Select Bit: 0 */
#define SREF1                  (0x4000)       /* ADC10 Reference Select Bit: 1 */
#define SREF2                  (0x8000)       /* ADC10 Reference Select Bit: 2 */
#define ADC10SHT_0             (0*0x800u)     /* 4 x ADC10CLKs */
#define ADC10SHT_1             (1*0x800u)     /* 8 x ADC10CLKs */
#define ADC10SHT_2             (2*0x800u)     /* 16 x ADC10CLKs */
#define ADC10SHT_3             (3*0x800u)     /* 64 x ADC10CLKs */

#define SREF_0                 (0*0x2000u)    /* VR+ = AVCC and VR- = AVSS */
#define SREF_1                 (1*0x2000u)    /* VR+ = VREF+ and VR- = AVSS */
#define SREF_2                 (2*0x2000u)    /* VR+ = VEREF+ and VR- = AVSS */
#define SREF_3                 (3*0x2000u)    /* VR+ = VEREF+ and VR- = AVSS */
#define SREF_4                 (4*0x2000u)    /* VR+ = AVCC and VR- = VREF-/VEREF- */
#define SREF_5                 (5*0x2000u)    /* VR+ = VREF+ and VR- = VREF-/VEREF- */
#define SREF_6                 (6*0x2000u)    /* VR+ = VEREF+ and VR- = VREF-/VEREF- */
#define SREF_7                 (7*0x2000u)    /* VR+ = VEREF+ and VR- = VREF-/VEREF- */

/* ADC10CTL1 */
#define ADC10BUSY              (0x0001)       /* ADC10 BUSY */
#define CONSEQ0                (0x0002)       /* ADC10 Conversion Sequence Select 0 */
#define CONSEQ1                (0x0004)       /* ADC10 Conversion Sequence Select 1 */
#define ADC10SSEL0             (0x0008)       /* ADC10 Clock Source Select Bit: 0 */
#define ADC10SSEL1             (0x0010)       /* ADC10 Clock Source Select Bit: 1 */
#define ADC10DIV0              (0x0020)       /* ADC10 Clock Divider Select Bit: 0 */
#define ADC10DIV1              (0x0040)       /* ADC10 Clock Divider Select Bit: 1 */
#define ADC10DIV2              (0x0080)       /* ADC10 Clock Divider Select Bit: 2 */
#define ISSH                   (0x0100)       /* ADC10 Invert Sample Hold Signal */
#define ADC10DF                (0x0200)       /* ADC10 Data Format 0:binary 1:2's complement */
#define SHS0                   (0x0400)       /* ADC10 Sample/Hold Source Bit: 0 */
#define SHS1                   (0x0800)       /* ADC10 Sample/Hold Source Bit: 1 */
#define INCH0                  (0x1000)       /* ADC10 Input Channel Select Bit: 0 */
#define INCH1                  (0x2000)       /* ADC10 Input Channel Select Bit: 1 */
#define INCH2                  (0x4000)       /* ADC10 Input Channel Select Bit: 2 */
#define INCH3                  (0x8000)       /* ADC10 Input Channel Select Bit: 3 */

#define CONSEQ_0               (0*2u)         /* Single channel single conversion */
#define CONSEQ_1               (1*2u)         /* Sequence of channels */
#define CONSEQ_2               (2*2u)         /* Repeat single channel */
#define CONSEQ_3               (3*2u)         /* Repeat sequence of channels */

#define ADC10SSEL_0            (0*8u)         /* ADC10OSC */
#define ADC10SSEL_1            (1*8u)         /* ACLK */
#define ADC10SSEL_2            (2*8u)         /* MCLK */
#define ADC10SSEL_3            (3*8u)         /* SMCLK */

#define ADC10DIV_0             (0*0x20u)      /* ADC10 Clock Divider Select 0 */
#define ADC10DIV_1             (1*0x20u)      /* ADC10 Clock Divider Select 1 */
#define ADC10DIV_2             (2*0x20u)      /* ADC10 Clock Divider Select 2 */
#define ADC10DIV_3             (3*0x20u)      /* ADC10 Clock Divider Select 3 */
#define ADC10DIV_4             (4*0x20u)      /* ADC10 Clock Divider Select 4 */
#define ADC10DIV_5             (5*0x20u)      /* ADC10 Clock Divider Select 5 */
#define ADC10DIV_6             (6*0x20u)      /* ADC10 Clock Divider Select 6 */
#define ADC10DIV_7             (7*0x20u)      /* ADC10 Clock Divider Select 7 */

#define SHS_0                  (0*0x400u)     /* ADC10SC */
#define SHS_1                  (1*0x400u)     /* Ext. SC Trigger 1 */
#define SHS_2                  (2*0x400u)     /* Ext. SC Trigger 2 */
#define SHS_3                  (3*0x400u)     /* Ext. SC Trigger 3 */

#define INCH_0                 (0*0x1000u)    /* Selects Channel 0 */
#define INCH_1                 (1*0x1000u)    /* Selects Channel 1 */
#define INCH_2                 (2*0x1000u)    /* Selects Channel 2 */
#define INCH_3                 (3*0x1000u)    /* Selects Channel 3 */
#define INCH_4                 (4*0x1000u)    /* Selects Channel 4 */
#define INCH_5                 (5*0x1000u)    /* Selects Channel 5 */
#define INCH_6                 (6*0x1000u)    /* Selects Channel 6 */
#define INCH_7                 (7*0x1000u)    /* Selects Channel 7 */
#define INCH_8                 (8*0x1000u)    /* Selects Channel 8 */
#define INCH_9                 (9*0x1000u)    /* Selects Channel 9 */
#define INCH_10                (10*0x1000u)   /* Selects Channel 10 */
#define INCH_11                (11*0x1000u)   /* Selects Channel 11 */
#define INCH_12                (12*0x1000u)   /* Selects Channel 12 */
#define INCH_13                (13*0x1000u)   /* Selects Channel 13 */
#define INCH_14                (14*0x1000u)   /* Selects Channel 14 */
#define INCH_15                (15*0x1000u)   /* Selects Channel 15 */

/* ADC10DTC0 */
#define ADC10FETCH             (0x001)        /* This bit should normally be reset */
#define ADC10B1                (0x002)        /* ADC10 block one */
#define ADC10CT                (0x004)        /* ADC10 continuous transfer */
#define ADC10TB                (0x008)        /* ADC10 two-block mode */
#define ADC10DISABLE           (0x000)        /* ADC10DTC1 */

/************************************************************
* BASIC TIMER with Real Time Clock
************************************************************/
#define __MSP430_HAS_BT_RTC__                 /* Definition to show that Module is available */

SFR_8BIT(BTCTL);                              /* Basic Timer Control */
SFR_8BIT(RTCCTL);                             /* Real Time Clock Control */
SFR_8BIT(RTCNT1);                             /* Real Time Counter 1 */
SFR_8BIT(RTCNT2);                             /* Real Time Counter 2 */
SFR_8BIT(RTCNT3);                             /* Real Time Counter 3 */
SFR_8BIT(RTCNT4);                             /* Real Time Counter 4 */
SFR_8BIT(BTCNT1);                             /* Basic Timer Count 1 */
SFR_8BIT(BTCNT2);                             /* Basic Timer Count 2 */
SFR_8BIT(RTCDAY);                             /* Real Time Clock Day */
SFR_8BIT(RTCMON);                             /* Real Time Clock Month */
SFR_8BIT(RTCYEARL);                           /* Real Time Clock Year (Low Byte) */
SFR_8BIT(RTCYEARH);                           /* Real Time Clock Year (High Byte) */
#define RTCSEC                 RTCNT1
#define RTCMIN                 RTCNT2
#define RTCHOUR                RTCNT3
#define RTCDOW                 RTCNT4

SFR_16BIT(RTCTL);                             /* Basic/Real Timer Control */
SFR_16BIT(RTCTIM0);                           /* Real Time Clock Time 0 */
SFR_16BIT(RTCTIM1);                           /* Real Time Clock Time 1 */
SFR_16BIT(BTCNT12);                           /* Basic Timer Count 1/2 */
SFR_16BIT(RTCDATE);                           /* Real Time Clock Date */
SFR_16BIT(RTCYEAR);                           /* Real Time Clock Year */
#define RTCNT12                RTCTIM0
#define RTCNT34                RTCTIM1

#define BTSSEL                 (0x80)         /* fBT = fMCLK (main clock) */
#define BTHOLD                 (0x40)         /* BT1 is held if this bit is set */
#define BTDIV                  (0x20)         /* fCLK2 = ACLK:256 */
//#define res               (0x10)
//#define res               (0x08)
#define BTIP2                  (0x04)
#define BTIP1                  (0x02)
#define BTIP0                  (0x01)

#define RTCBCD                 (0x80)         /* RTC BCD Select */
#define RTCHOLD                (0x40)         /* RTC Hold */
#define RTCMODE1               (0x20)         /* RTC Mode 1 */
#define RTCMODE0               (0x10)         /* RTC Mode 0 */
#define RTCTEV1                (0x08)         /* RTC Time Event 1 */
#define RTCTEV0                (0x04)         /* RTC Time Event 0 */
#define RTCIE                  (0x02)         /* RTC Interrupt Enable */
#define RTCFG                  (0x01)         /* RTC Event Flag */

#define RTCTEV_0               (0x00)         /* RTC Time Event: 0 */
#define RTCTEV_1               (0x04)         /* RTC Time Event: 1 */
#define RTCTEV_2               (0x08)         /* RTC Time Event: 2 */
#define RTCTEV_3               (0x0C)         /* RTC Time Event: 3 */
#define RTCMODE_0              (0x00)         /* RTC Mode: 0 */
#define RTCMODE_1              (0x10)         /* RTC Mode: 1 */
#define RTCMODE_2              (0x20)         /* RTC Mode: 2 */
#define RTCMODE_3              (0x30)         /* RTC Mode: 3 */

/* Frequency of the BTCNT2 coded with Bit 5 and 7 in BTCTL */
#define BT_fCLK2_ACLK          (0x00)
#define BT_fCLK2_ACLK_DIV256   (BTDIV)
#define BT_fCLK2_MCLK          (BTSSEL)

/* Interrupt interval time fINT coded with Bits 0-2 in BTCTL */
#define BT_fCLK2_DIV2          (0x00)         /* fINT = fCLK2:2 (default) */
#define BT_fCLK2_DIV4          (BTIP0)        /* fINT = fCLK2:4 */
#define BT_fCLK2_DIV8          (BTIP1)        /* fINT = fCLK2:8 */
#define BT_fCLK2_DIV16         (BTIP1+BTIP0)  /* fINT = fCLK2:16 */
#define BT_fCLK2_DIV32         (BTIP2)        /* fINT = fCLK2:32 */
#define BT_fCLK2_DIV64         (BTIP2+BTIP0)  /* fINT = fCLK2:64 */
#define BT_fCLK2_DIV128        (BTIP2+BTIP1)  /* fINT = fCLK2:128 */
#define BT_fCLK2_DIV256     (BTIP2+BTIP1+BTIP0)       /* fINT = fCLK2:256 */

/* with assumed vlues of fACLK=32KHz, fMCLK=1MHz */
/* fBT=fACLK is thought for longer interval times */
#define BT_ADLY_0_064          (0x00)         /* 0.064ms interval (default) */
#define BT_ADLY_0_125          (BTIP0)        /* 0.125ms    " */
#define BT_ADLY_0_25           (BTIP1)        /* 0.25ms     " */
#define BT_ADLY_0_5            (BTIP1+BTIP0)  /* 0.5ms      " */
#define BT_ADLY_1              (BTIP2)        /* 1ms        " */
#define BT_ADLY_2              (BTIP2+BTIP0)  /* 2ms        " */
#define BT_ADLY_4              (BTIP2+BTIP1)  /* 4ms        " */
#define BT_ADLY_8           (BTIP2+BTIP1+BTIP0)       /* 8ms        " */
#define BT_ADLY_16             (BTDIV)        /* 16ms       " */
#define BT_ADLY_32             (BTDIV+BTIP0)  /* 32ms       " */
#define BT_ADLY_64             (BTDIV+BTIP1)  /* 64ms       " */
#define BT_ADLY_125         (BTDIV+BTIP1+BTIP0)       /* 125ms      " */
#define BT_ADLY_250            (BTDIV+BTIP2)  /* 250ms      " */
#define BT_ADLY_500         (BTDIV+BTIP2+BTIP0)       /* 500ms      " */
#define BT_ADLY_1000        (BTDIV+BTIP2+BTIP1)       /* 1000ms     " */
#define BT_ADLY_2000        (BTDIV+BTIP2+BTIP1+BTIP0) /* 2000ms     " */
/* fCLK2=fMCLK (1MHz) is thought for short interval times */
/* the timing for short intervals is more precise than ACLK */
/* NOTE */
/* Be sure that the SCFQCTL-Register is set to 01Fh so that fMCLK=1MHz */
/* Too low interval time results in interrupts too frequent for the processor to handle! */
#define BT_MDLY_0_002          (BTSSEL)       /* 0.002ms interval       *** interval times */
#define BT_MDLY_0_004          (BTSSEL+BTIP0) /* 0.004ms    "           *** too short for */
#define BT_MDLY_0_008          (BTSSEL+BTIP1) /* 0.008ms    "           *** interrupt */
#define BT_MDLY_0_016       (BTSSEL+BTIP1+BTIP0)      /* 0.016ms    "           *** handling */
#define BT_MDLY_0_032          (BTSSEL+BTIP2) /* 0.032ms    " */
#define BT_MDLY_0_064       (BTSSEL+BTIP2+BTIP0)      /* 0.064ms    " */
#define BT_MDLY_0_125       (BTSSEL+BTIP2+BTIP1)      /* 0.125ms    " */
#define BT_MDLY_0_25        (BTSSEL+BTIP2+BTIP1+BTIP0)/* 0.25ms     " */

/* Hold coded with Bits 6-7 in BT(1)CTL */
/* this is for BT */
#define BTHOLD_CNT1            (BTHOLD)       /* BTCNT1 is held while BTHOLD is set */
#define BTHOLD_CNT1_2          (BTHOLD+BTDIV) /* BT1CNT1 .AND. BT1CNT2 are held while ~ is set */

/* INTERRUPT CONTROL BITS */
/* #define BTIE                0x80 */
/* #define BTIFG               0x80 */

/************************************************************
* Comparator A
************************************************************/
#define __MSP430_HAS_CAPLUS__                 /* Definition to show that Module is available */

SFR_8BIT(CACTL1);                             /* Comparator A Control 1 */
SFR_8BIT(CACTL2);                             /* Comparator A Control 2 */
SFR_8BIT(CAPD);                               /* Comparator A Port Disable */

#define CAIFG                  (0x01)         /* Comp. A Interrupt Flag */
#define CAIE                   (0x02)         /* Comp. A Interrupt Enable */
#define CAIES                  (0x04)         /* Comp. A Int. Edge Select: 0:rising / 1:falling */
#define CAON                   (0x08)         /* Comp. A enable */
#define CAREF0                 (0x10)         /* Comp. A Internal Reference Select 0 */
#define CAREF1                 (0x20)         /* Comp. A Internal Reference Select 1 */
#define CARSEL                 (0x40)         /* Comp. A Internal Reference Enable */
#define CAEX                   (0x80)         /* Comp. A Exchange Inputs */

#define CAREF_0                (0x00)         /* Comp. A Int. Ref. Select 0 : Off */
#define CAREF_1                (0x10)         /* Comp. A Int. Ref. Select 1 : 0.25*Vcc */
#define CAREF_2                (0x20)         /* Comp. A Int. Ref. Select 2 : 0.5*Vcc */
#define CAREF_3                (0x30)         /* Comp. A Int. Ref. Select 3 : Vt*/

#define CAOUT                  (0x01)         /* Comp. A Output */
#define CAF                    (0x02)         /* Comp. A Enable Output Filter */
#define P2CA0                  (0x04)         /* Comp. A +Terminal Multiplexer */
#define P2CA1                  (0x08)         /* Comp. A -Terminal Multiplexer */
#define P2CA2                  (0x10)         /* Comp. A -Terminal Multiplexer */
#define P2CA3                  (0x20)         /* Comp. A -Terminal Multiplexer */
#define P2CA4                  (0x40)         /* Comp. A +Terminal Multiplexer */
#define CASHORT                (0x80)         /* Comp. A Short + and - Terminals */

#define CAPD0                  (0x01)         /* Comp. A Disable Input Buffer of Port Register .0 */
#define CAPD1                  (0x02)         /* Comp. A Disable Input Buffer of Port Register .1 */
#define CAPD2                  (0x04)         /* Comp. A Disable Input Buffer of Port Register .2 */
#define CAPD3                  (0x08)         /* Comp. A Disable Input Buffer of Port Register .3 */
#define CAPD4                  (0x10)         /* Comp. A Disable Input Buffer of Port Register .4 */
#define CAPD5                  (0x20)         /* Comp. A Disable Input Buffer of Port Register .5 */
#define CAPD6                  (0x40)         /* Comp. A Disable Input Buffer of Port Register .6 */
#define CAPD7                  (0x80)         /* Comp. A Disable Input Buffer of Port Register .7 */

/*************************************************************
* Flash Memory
*************************************************************/
#define __MSP430_HAS_FLASH2__                 /* Definition to show that Module is available */

SFR_16BIT(FCTL1);                             /* FLASH Control 1 */
SFR_16BIT(FCTL2);                             /* FLASH Control 2 */
SFR_16BIT(FCTL3);                             /* FLASH Control 3 */

#define FRKEY                  (0x9600)       /* Flash key returned by read */
#define FWKEY                  (0xA500)       /* Flash key for write */
#define FXKEY                  (0x3300)       /* for use with XOR instruction */

#define ERASE                  (0x0002)       /* Enable bit for Flash segment erase */
#define MERAS                  (0x0004)       /* Enable bit for Flash mass erase */
#define EEI                    (0x0008)       /* Enable Erase Interrupts */
#define EEIEX                  (0x0010)       /* Enable Emergency Interrupt Exit */
#define WRT                    (0x0040)       /* Enable bit for Flash write */
#define BLKWRT                 (0x0080)       /* Enable bit for Flash segment write */
#define SEGWRT                 (0x0080)       /* old definition */ /* Enable bit for Flash segment write */

#define FN0                    (0x0001)       /* Divide Flash clock by 1 to 64 using FN0 to FN5 according to: */
#define FN1                    (0x0002)       /*  32*FN5 + 16*FN4 + 8*FN3 + 4*FN2 + 2*FN1 + FN0 + 1 */
#ifndef FN2
#define FN2                    (0x0004)
#endif
#ifndef FN3
#define FN3                    (0x0008)
#endif
#ifndef FN4
#define FN4                    (0x0010)
#endif
#define FN5                    (0x0020)
#define FSSEL0                 (0x0040)       /* Flash clock select 0 */        /* to distinguish from USART SSELx */
#define FSSEL1                 (0x0080)       /* Flash clock select 1 */

#define FSSEL_0                (0x0000)       /* Flash clock select: 0 - ACLK */
#define FSSEL_1                (0x0040)       /* Flash clock select: 1 - MCLK */
#define FSSEL_2                (0x0080)       /* Flash clock select: 2 - SMCLK */
#define FSSEL_3                (0x00C0)       /* Flash clock select: 3 - SMCLK */

#define BUSY                   (0x0001)       /* Flash busy: 1 */
#define KEYV                   (0x0002)       /* Flash Key violation flag */
#define ACCVIFG                (0x0004)       /* Flash Access violation flag */
#define WAIT                   (0x0008)       /* Wait flag for segment write */
#define LOCK                   (0x0010)       /* Lock bit: 1 - Flash is locked (read only) */
#define EMEX                   (0x0020)       /* Flash Emergency Exit */
#define LOCKA                  (0x0040)       /* Segment A Lock bit: read = 1 - Segment is locked (read only) */
#define FAIL                   (0x0080)       /* Last Program or Erase failed */

/************************************************************
* SYSTEM CLOCK, FLL+
************************************************************/
#define __MSP430_HAS_FLLPLUS__                /* Definition to show that Module is available */

SFR_8BIT(SCFI0);                              /* System Clock Frequency Integrator 0 */
#define FN_2                   (0x04)         /* fDCOCLK =   1.4-12MHz*/
#define FN_3                   (0x08)         /* fDCOCLK =   2.2-17Mhz*/
#define FN_4                   (0x10)         /* fDCOCLK =   3.2-25Mhz*/
#define FN_8                   (0x20)         /* fDCOCLK =     5-40Mhz*/
#define FLLD0                  (0x40)         /* Loop Divider Bit : 0 */
#define FLLD1                  (0x80)         /* Loop Divider Bit : 1 */

#define FLLD_1                 (0x00)         /* Multiply Selected Loop Freq. By 1 */
#define FLLD_2                 (0x40)         /* Multiply Selected Loop Freq. By 2 */
#define FLLD_4                 (0x80)         /* Multiply Selected Loop Freq. By 4 */
#define FLLD_8                 (0xC0)         /* Multiply Selected Loop Freq. By 8 */

SFR_8BIT(SCFI1);                              /* System Clock Frequency Integrator 1 */
SFR_8BIT(SCFQCTL);                            /* System Clock Frequency Control */
/* System clock frequency values fMCLK coded with Bits 0-6 in SCFQCTL */
/* #define SCFQ_32K            0x00                        fMCLK=1*fACLK       only a range from */
#define SCFQ_64K               (0x01)         /* fMCLK=2*fACLK          1+1 to 127+1 is possible */
#define SCFQ_128K              (0x03)         /* fMCLK=4*fACLK */
#define SCFQ_256K              (0x07)         /* fMCLK=8*fACLK */
#define SCFQ_512K              (0x0F)         /* fMCLK=16*fACLK */
#define SCFQ_1M                (0x1F)         /* fMCLK=32*fACLK */
#define SCFQ_2M                (0x3F)         /* fMCLK=64*fACLK */
#define SCFQ_4M                (0x7F)         /* fMCLK=128*fACLK */
#define SCFQ_M                 (0x80)         /* Modulation Disable */

SFR_8BIT(FLL_CTL0);                           /* FLL+ Control 0 */
#define DCOF                   (0x01)         /* DCO Fault Flag */
#define LFOF                   (0x02)         /* Low Frequency Oscillator Fault Flag */
#define XT1OF                  (0x04)         /* High Frequency Oscillator 1 Fault Flag */
#define OSCCAP0                (0x10)         /* XIN/XOUT Cap 0 */
#define OSCCAP1                (0x20)         /* XIN/XOUT Cap 1 */
#define XTS_FLL                (0x40)         /* 1: Selects high-freq. oscillator */
#define DCOPLUS                (0x80)         /* DCO+ Enable */

#define XCAP0PF                (0x00)         /* XIN Cap = XOUT Cap = 0pf */
#define XCAP5_5F               (0x10)         /* XIN Cap = XOUT Cap = 5.5pf */
#define XCAP8_5PF              (0x20)         /* XIN Cap = XOUT Cap = 8.5pf */
#define XCAP11PF               (0x30)         /* XIN Cap = XOUT Cap = 11pf */
#define OSCCAP_0               (0x00)         /* XIN Cap = XOUT Cap: 0 */
#define OSCCAP_1               (0x10)         /* XIN Cap = XOUT Cap: 1 */
#define OSCCAP_2               (0x20)         /* XIN Cap = XOUT Cap: 2 */
#define OSCCAP_3               (0x30)         /* XIN Cap = XOUT Cap: 3 */

SFR_8BIT(FLL_CTL1);                           /* FLL+ Control 1 */
#define FLL_DIV0               (0x01)         /* FLL+ Divide Px.x/ACLK 0 */
#define FLL_DIV1               (0x02)         /* FLL+ Divide Px.x/ACLK 1 */
#define SELM0                  (0x08)         /* MCLK Source Select 0 */
#define SELM1                  (0x10)         /* MCLK Source Select 1 */
#define SMCLKOFF               (0x40)         /* Peripheral Module Clock (SMCLK) disable */

#define FLL_DIV_1              (0x00)         /* FLL+ Divide Px.x/ACLK By 1 */
#define FLL_DIV_2              (0x01)         /* FLL+ Divide Px.x/ACLK By 2 */
#define FLL_DIV_4              (0x02)         /* FLL+ Divide Px.x/ACLK By 4 */
#define FLL_DIV_8              (0x03)         /* FLL+ Divide Px.x/ACLK By 8 */

#define SELM_DCO               (0x00)         /* Select DCO for CPU MCLK */
#define SELM_A                 (0x18)         /* Select A (from LFXT1) for CPU MCLK */

SFR_8BIT(FLL_CTL2);                           /* FLL+ Control 2 */

#define LF1XT1S0               (0x10)         /* Mode 0 for LFXT1 */
#define LF1XT1S1               (0x20)         /* Mode 0 for LFXT1 */

#define LF1XT1S_0              (0x00)         /* Mode 0 for LF : 32kHz */
#define LF1XT1S_1              (0x10)         /* Mode 1 for LF : reserved */
#define LF1XT1S_2              (0x20)         /* Mode 2 for LF : VLO */
#define LF1XT1S_3              (0x30)         /* Mode 3 for LF : Digital input signal */

/* INTERRUPT CONTROL BITS */
/* These two bits are defined in the Special Function Registers */
/* #define OFIFG               0x02 */
/* #define OFIE                0x02 */

/************************************************************
* LCD_A
************************************************************/
#define __MSP430_HAS_LCD_A__                  /* Definition to show that Module is available */

SFR_8BIT(LCDACTL);                            /* LCD_A Control Register */
#define LCDON                  (0x01)
#define LCDSON                 (0x04)
#define LCDMX0                 (0x08)
#define LCDMX1                 (0x10)
#define LCDFREQ0               (0x20)
#define LCDFREQ1               (0x40)
#define LCDFREQ2               (0x80)
/* Display modes coded with Bits 2-4 */
#define LCDSTATIC              (LCDSON)
#define LCD2MUX                (LCDMX0+LCDSON)
#define LCD3MUX                (LCDMX1+LCDSON)
#define LCD4MUX                (LCDMX1+LCDMX0+LCDSON)
/* Frequency select code with Bits 5-7 */
#define LCDFREQ_32             (0x00)         /* LCD Freq: ACLK divided by 32 */
#define LCDFREQ_64             (0x20)         /* LCD Freq: ACLK divided by 64 */
#define LCDFREQ_96             (0x40)         /* LCD Freq: ACLK divided by 96 */
#define LCDFREQ_128            (0x60)         /* LCD Freq: ACLK divided by 128 */
#define LCDFREQ_192            (0x80)         /* LCD Freq: ACLK divided by 192 */
#define LCDFREQ_256            (0xA0)         /* LCD Freq: ACLK divided by 256 */
#define LCDFREQ_384            (0xC0)         /* LCD Freq: ACLK divided by 384 */
#define LCDFREQ_512            (0xE0)         /* LCD Freq: ACLK divided by 512 */

SFR_8BIT(LCDAPCTL0);                          /* LCD_A Port Control Register 0 */
#define LCDS0                  (0x01)         /* LCD Segment  0 to  3 Enable. */
#define LCDS4                  (0x02)         /* LCD Segment  4 to  7 Enable. */
#define LCDS8                  (0x04)         /* LCD Segment  8 to 11 Enable. */
#define LCDS12                 (0x08)         /* LCD Segment 12 to 15 Enable. */
#define LCDS16                 (0x10)         /* LCD Segment 16 to 19 Enable. */
#define LCDS20                 (0x20)         /* LCD Segment 20 to 23 Enable. */
#define LCDS24                 (0x40)         /* LCD Segment 24 to 27 Enable. */
#define LCDS28                 (0x80)         /* LCD Segment 28 to 31 Enable. */

SFR_8BIT(LCDAPCTL1);                          /* LCD_A Port Control Register 1 */
#define LCDS32                 (0x01)         /* LCD Segment 32 to 35 Enable. */
#define LCDS36                 (0x02)         /* LCD Segment 36 to 39 Enable. */

SFR_8BIT(LCDAVCTL0);                          /* LCD_A Voltage Control Register 0 */
#define LCD2B                  (0x01)         /* Selects 1/2 bias. */
#define VLCDREF0               (0x02)         /* Selects reference voltage for regulated charge pump: 0 */
#define VLCDREF1               (0x04)         /* Selects reference voltage for regulated charge pump: 1 */
#define LCDCPEN                (0x08)         /* LCD Voltage Charge Pump Enable. */
#define VLCDEXT                (0x10)         /* Select external source for VLCD. */
#define LCDREXT                (0x20)         /* Selects external connections for LCD mid voltages. */
#define LCDR03EXT              (0x40)         /* Selects external connection for lowest LCD voltage. */

/* Reference voltage source select for the regulated charge pump */
#define VLCDREF_0              (0<<1)         /* Internal */
#define VLCDREF_1              (1<<1)         /* External */
#define VLCDREF_2              (2<<1)         /* Reserved */
#define VLCDREF_3              (3<<1)         /* Reserved */

SFR_8BIT(LCDAVCTL1);                          /* LCD_A Voltage Control Register 1 */
#define VLCD0                  (0x02)         /* VLCD select: 0 */
#define VLCD1                  (0x04)         /* VLCD select: 1 */
#define VLCD2                  (0x08)         /* VLCD select: 2 */
#define VLCD3                  (0x10)         /* VLCD select: 3 */

/* Charge pump voltage selections */
#define VLCD_0                 (0<<1)         /* Charge pump disabled */
#define VLCD_1                 (1<<1)         /* VLCD = 2.60V */
#define VLCD_2                 (2<<1)         /* VLCD = 2.66V */
#define VLCD_3                 (3<<1)         /* VLCD = 2.72V */
#define VLCD_4                 (4<<1)         /* VLCD = 2.78V */
#define VLCD_5                 (5<<1)         /* VLCD = 2.84V */
#define VLCD_6                 (6<<1)         /* VLCD = 2.90V */
#define VLCD_7                 (7<<1)         /* VLCD = 2.96V */
#define VLCD_8                 (8<<1)         /* VLCD = 3.02V */
#define VLCD_9                 (9<<1)         /* VLCD = 3.08V */
#define VLCD_10                (10<<1)        /* VLCD = 3.14V */
#define VLCD_11                (11<<1)        /* VLCD = 3.20V */
#define VLCD_12                (12<<1)        /* VLCD = 3.26V */
#define VLCD_13                (12<<1)        /* VLCD = 3.32V */
#define VLCD_14                (13<<1)        /* VLCD = 3.38V */
#define VLCD_15                (15<<1)        /* VLCD = 3.44V */

#define VLCD_DISABLED          (0<<1)         /* Charge pump disabled */
#define VLCD_2_60              (1<<1)         /* VLCD = 2.60V */
#define VLCD_2_66              (2<<1)         /* VLCD = 2.66V */
#define VLCD_2_72              (3<<1)         /* VLCD = 2.72V */
#define VLCD_2_78              (4<<1)         /* VLCD = 2.78V */
#define VLCD_2_84              (5<<1)         /* VLCD = 2.84V */
#define VLCD_2_90              (6<<1)         /* VLCD = 2.90V */
#define VLCD_2_96              (7<<1)         /* VLCD = 2.96V */
#define VLCD_3_02              (8<<1)         /* VLCD = 3.02V */
#define VLCD_3_08              (9<<1)         /* VLCD = 3.08V */
#define VLCD_3_14              (10<<1)        /* VLCD = 3.14V */
#define VLCD_3_20              (11<<1)        /* VLCD = 3.20V */
#define VLCD_3_26              (12<<1)        /* VLCD = 3.26V */
#define VLCD_3_32              (12<<1)        /* VLCD = 3.32V */
#define VLCD_3_38              (13<<1)        /* VLCD = 3.38V */
#define VLCD_3_44              (15<<1)        /* VLCD = 3.44V */

#define LCDMEM_                (0x0091)       /* LCD Memory */
#ifdef __ASM_HEADER__
#define LCDMEM                 (LCDMEM_)      /* LCD Memory (for assembler) */
#else
#define LCDMEM                 ((char*)       LCDMEM_) /* LCD Memory (for C) */
#endif
SFR_8BIT(LCDM1);                              /* LCD Memory 1 */
SFR_8BIT(LCDM2);                              /* LCD Memory 2 */
SFR_8BIT(LCDM3);                              /* LCD Memory 3 */
SFR_8BIT(LCDM4);                              /* LCD Memory 4 */
SFR_8BIT(LCDM5);                              /* LCD Memory 5 */
SFR_8BIT(LCDM6);                              /* LCD Memory 6 */
SFR_8BIT(LCDM7);                              /* LCD Memory 7 */
SFR_8BIT(LCDM8);                              /* LCD Memory 8 */
SFR_8BIT(LCDM9);                              /* LCD Memory 9 */
SFR_8BIT(LCDM10);                             /* LCD Memory 10 */
SFR_8BIT(LCDM11);                             /* LCD Memory 11 */
SFR_8BIT(LCDM12);                             /* LCD Memory 12 */
SFR_8BIT(LCDM13);                             /* LCD Memory 13 */
SFR_8BIT(LCDM14);                             /* LCD Memory 14 */
SFR_8BIT(LCDM15);                             /* LCD Memory 15 */
SFR_8BIT(LCDM16);                             /* LCD Memory 16 */
SFR_8BIT(LCDM17);                             /* LCD Memory 17 */
SFR_8BIT(LCDM18);                             /* LCD Memory 18 */
SFR_8BIT(LCDM19);                             /* LCD Memory 19 */
SFR_8BIT(LCDM20);                             /* LCD Memory 20 */

#define LCDMA                  (LCDM10)       /* LCD Memory A */
#define LCDMB                  (LCDM11)       /* LCD Memory B */
#define LCDMC                  (LCDM12)       /* LCD Memory C */
#define LCDMD                  (LCDM13)       /* LCD Memory D */
#define LCDME                  (LCDM14)       /* LCD Memory E */
#define LCDMF                  (LCDM15)       /* LCD Memory F */

/************************************************************
* DIGITAL I/O Port1/2
************************************************************/
#define __MSP430_HAS_PORT1__                  /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2__                  /* Definition to show that Module is available */

SFR_8BIT(P1IN);                               /* Port 1 Input */
SFR_8BIT(P1OUT);                              /* Port 1 Output */
SFR_8BIT(P1DIR);                              /* Port 1 Direction */
SFR_8BIT(P1IFG);                              /* Port 1 Interrupt Flag */
SFR_8BIT(P1IES);                              /* Port 1 Interrupt Edge Select */
SFR_8BIT(P1IE);                               /* Port 1 Interrupt Enable */
SFR_8BIT(P1SEL);                              /* Port 1 Selection */

SFR_8BIT(P2IN);                               /* Port 2 Input */
SFR_8BIT(P2OUT);                              /* Port 2 Output */
SFR_8BIT(P2DIR);                              /* Port 2 Direction */
SFR_8BIT(P2IFG);                              /* Port 2 Interrupt Flag */
SFR_8BIT(P2IES);                              /* Port 2 Interrupt Edge Select */
SFR_8BIT(P2IE);                               /* Port 2 Interrupt Enable */
SFR_8BIT(P2SEL);                              /* Port 2 Selection */

/************************************************************
* DIGITAL I/O Port3/4
************************************************************/
#define __MSP430_HAS_PORT3__                  /* Definition to show that Module is available */
#define __MSP430_HAS_PORT4__                  /* Definition to show that Module is available */

SFR_8BIT(P3IN);                               /* Port 3 Input */
SFR_8BIT(P3OUT);                              /* Port 3 Output */
SFR_8BIT(P3DIR);                              /* Port 3 Direction */
SFR_8BIT(P3SEL);                              /* Port 3 Selection */

SFR_8BIT(P4IN);                               /* Port 4 Input */
SFR_8BIT(P4OUT);                              /* Port 4 Output */
SFR_8BIT(P4DIR);                              /* Port 4 Direction */
SFR_8BIT(P4SEL);                              /* Port 4 Selection */

/************************************************************
* DIGITAL I/O Port5/6
************************************************************/
#define __MSP430_HAS_PORT5__                  /* Definition to show that Module is available */
#define __MSP430_HAS_PORT6__                  /* Definition to show that Module is available */

SFR_8BIT(P5IN);                               /* Port 5 Input */
SFR_8BIT(P5OUT);                              /* Port 5 Output */
SFR_8BIT(P5DIR);                              /* Port 5 Direction */
SFR_8BIT(P5SEL);                              /* Port 5 Selection */

SFR_8BIT(P6IN);                               /* Port 6 Input */
SFR_8BIT(P6OUT);                              /* Port 6 Output */
SFR_8BIT(P6DIR);                              /* Port 6 Direction */
SFR_8BIT(P6SEL);                              /* Port 6 Selection */

/************************************************************
* DIGITAL I/O Port7
************************************************************/
#define __MSP430_HAS_PORT7__                  /* Definition to show that Module is available */

SFR_8BIT(P7IN);                               /* Port 7 Input */
SFR_8BIT(P7OUT);                              /* Port 7 Output */
SFR_8BIT(P7DIR);                              /* Port 7 Direction */
SFR_8BIT(P7SEL);                              /* Port 7 Selection */

/************************************************************
* Brown-Out, Supply Voltage Supervision (SVS)
************************************************************/
#define __MSP430_HAS_SVS__                    /* Definition to show that Module is available */

SFR_8BIT(SVSCTL);                             /* SVS Control */
#define SVSFG                  (0x01)         /* SVS Flag */
#define SVSOP                  (0x02)         /* SVS output (read only) */
#define SVSON                  (0x04)         /* Switches the SVS on/off */
#define PORON                  (0x08)         /* Enable POR Generation if Low Voltage */
#define VLD0                   (0x10)
#define VLD1                   (0x20)
#define VLD2                   (0x40)
#define VLD3                   (0x80)

#define VLDON                  (0x10)
#define VLDOFF                 (0x00)
#define VLD_1_8V               (0x10)

/************************************************************
* Timer0_A3
************************************************************/
#define __MSP430_HAS_TA3__                    /* Definition to show that Module is available */

SFR_16BIT(TA0IV);                             /* Timer0_A3 Interrupt Vector Word */
SFR_16BIT(TA0CTL);                            /* Timer0_A3 Control */
SFR_16BIT(TA0CCTL0);                          /* Timer0_A3 Capture/Compare Control 0 */
SFR_16BIT(TA0CCTL1);                          /* Timer0_A3 Capture/Compare Control 1 */
SFR_16BIT(TA0CCTL2);                          /* Timer0_A3 Capture/Compare Control 2 */
SFR_16BIT(TA0R);                              /* Timer0_A3 */
SFR_16BIT(TA0CCR0);                           /* Timer0_A3 Capture/Compare 0 */
SFR_16BIT(TA0CCR1);                           /* Timer0_A3 Capture/Compare 1 */
SFR_16BIT(TA0CCR2);                           /* Timer0_A3 Capture/Compare 2 */

/* Alternate register names */
#define TAIV                   TA0IV          /* Timer A Interrupt Vector Word */
#define TACTL                  TA0CTL         /* Timer A Control */
#define TACCTL0                TA0CCTL0       /* Timer A Capture/Compare Control 0 */
#define TACCTL1                TA0CCTL1       /* Timer A Capture/Compare Control 1 */
#define TACCTL2                TA0CCTL2       /* Timer A Capture/Compare Control 2 */
#define TAR                    TA0R           /* Timer A */
#define TACCR0                 TA0CCR0        /* Timer A Capture/Compare 0 */
#define TACCR1                 TA0CCR1        /* Timer A Capture/Compare 1 */
#define TACCR2                 TA0CCR2        /* Timer A Capture/Compare 2 */
#define TAIV_                  TA0IV_         /* Timer A Interrupt Vector Word */
#define TACTL_                 TA0CTL_        /* Timer A Control */
#define TACCTL0_               TA0CCTL0_      /* Timer A Capture/Compare Control 0 */
#define TACCTL1_               TA0CCTL1_      /* Timer A Capture/Compare Control 1 */
#define TACCTL2_               TA0CCTL2_      /* Timer A Capture/Compare Control 2 */
#define TAR_                   TA0R_          /* Timer A */
#define TACCR0_                TA0CCR0_       /* Timer A Capture/Compare 0 */
#define TACCR1_                TA0CCR1_       /* Timer A Capture/Compare 1 */
#define TACCR2_                TA0CCR2_       /* Timer A Capture/Compare 2 */

/* Alternate register names 2 */
#define CCTL0                  TACCTL0        /* Timer A Capture/Compare Control 0 */
#define CCTL1                  TACCTL1        /* Timer A Capture/Compare Control 1 */
#define CCTL2                  TACCTL2        /* Timer A Capture/Compare Control 2 */
#define CCR0                   TACCR0         /* Timer A Capture/Compare 0 */
#define CCR1                   TACCR1         /* Timer A Capture/Compare 1 */
#define CCR2                   TACCR2         /* Timer A Capture/Compare 2 */
#define CCTL0_                 TACCTL0_       /* Timer A Capture/Compare Control 0 */
#define CCTL1_                 TACCTL1_       /* Timer A Capture/Compare Control 1 */
#define CCTL2_                 TACCTL2_       /* Timer A Capture/Compare Control 2 */
#define CCR0_                  TACCR0_        /* Timer A Capture/Compare 0 */
#define CCR1_                  TACCR1_        /* Timer A Capture/Compare 1 */
#define CCR2_                  TACCR2_        /* Timer A Capture/Compare 2 */

#define TASSEL1                (0x0200)       /* Timer A clock source select 1 */
#define TASSEL0                (0x0100)       /* Timer A clock source select 0 */
#define ID1                    (0x0080)       /* Timer A clock input divider 1 */
#define ID0                    (0x0040)       /* Timer A clock input divider 0 */
#define MC1                    (0x0020)       /* Timer A mode control 1 */
#define MC0                    (0x0010)       /* Timer A mode control 0 */
#define TACLR                  (0x0004)       /* Timer A counter clear */
#define TAIE                   (0x0002)       /* Timer A counter interrupt enable */
#define TAIFG                  (0x0001)       /* Timer A counter interrupt flag */

#define MC_0                   (0*0x10u)      /* Timer A mode control: 0 - Stop */
#define MC_1                   (1*0x10u)      /* Timer A mode control: 1 - Up to CCR0 */
#define MC_2                   (2*0x10u)      /* Timer A mode control: 2 - Continous up */
#define MC_3                   (3*0x10u)      /* Timer A mode control: 3 - Up/Down */
#define ID_0                   (0*0x40u)      /* Timer A input divider: 0 - /1 */
#define ID_1                   (1*0x40u)      /* Timer A input divider: 1 - /2 */
#define ID_2                   (2*0x40u)      /* Timer A input divider: 2 - /4 */
#define ID_3                   (3*0x40u)      /* Timer A input divider: 3 - /8 */
#define TASSEL_0               (0*0x100u)     /* Timer A clock source select: 0 - TACLK */
#define TASSEL_1               (1*0x100u)     /* Timer A clock source select: 1 - ACLK  */
#define TASSEL_2               (2*0x100u)     /* Timer A clock source select: 2 - SMCLK */
#define TASSEL_3               (3*0x100u)     /* Timer A clock source select: 3 - INCLK */

#define CM1                    (0x8000)       /* Capture mode 1 */
#define CM0                    (0x4000)       /* Capture mode 0 */
#define CCIS1                  (0x2000)       /* Capture input select 1 */
#define CCIS0                  (0x1000)       /* Capture input select 0 */
#define SCS                    (0x0800)       /* Capture sychronize */
#define SCCI                   (0x0400)       /* Latched capture signal (read) */
#define CAP                    (0x0100)       /* Capture mode: 1 /Compare mode : 0 */
#define OUTMOD2                (0x0080)       /* Output mode 2 */
#define OUTMOD1                (0x0040)       /* Output mode 1 */
#define OUTMOD0                (0x0020)       /* Output mode 0 */
#define CCIE                   (0x0010)       /* Capture/compare interrupt enable */
#define CCI                    (0x0008)       /* Capture input signal (read) */
#define OUT                    (0x0004)       /* PWM Output signal if output mode 0 */
#define COV                    (0x0002)       /* Capture/compare overflow flag */
#define CCIFG                  (0x0001)       /* Capture/compare interrupt flag */

#define OUTMOD_0               (0*0x20u)      /* PWM output mode: 0 - output only */
#define OUTMOD_1               (1*0x20u)      /* PWM output mode: 1 - set */
#define OUTMOD_2               (2*0x20u)      /* PWM output mode: 2 - PWM toggle/reset */
#define OUTMOD_3               (3*0x20u)      /* PWM output mode: 3 - PWM set/reset */
#define OUTMOD_4               (4*0x20u)      /* PWM output mode: 4 - toggle */
#define OUTMOD_5               (5*0x20u)      /* PWM output mode: 5 - Reset */
#define OUTMOD_6               (6*0x20u)      /* PWM output mode: 6 - PWM toggle/set */
#define OUTMOD_7               (7*0x20u)      /* PWM output mode: 7 - PWM reset/set */
#define CCIS_0                 (0*0x1000u)    /* Capture input select: 0 - CCIxA */
#define CCIS_1                 (1*0x1000u)    /* Capture input select: 1 - CCIxB */
#define CCIS_2                 (2*0x1000u)    /* Capture input select: 2 - GND */
#define CCIS_3                 (3*0x1000u)    /* Capture input select: 3 - Vcc */
#define CM_0                   (0*0x4000u)    /* Capture mode: 0 - disabled */
#define CM_1                   (1*0x4000u)    /* Capture mode: 1 - pos. edge */
#define CM_2                   (2*0x4000u)    /* Capture mode: 1 - neg. edge */
#define CM_3                   (3*0x4000u)    /* Capture mode: 1 - both edges */

/* T0_A3IV Definitions */
#define TA0IV_NONE             (0x0000)       /* No Interrupt pending */
#define TA0IV_TACCR1           (0x0002)       /* TA0CCR1_CCIFG */
#define TA0IV_TACCR2           (0x0004)       /* TA0CCR2_CCIFG */
#define TA0IV_6                (0x0006)       /* Reserved */
#define TA0IV_8                (0x0008)       /* Reserved */
#define TA0IV_TAIFG            (0x000A)       /* TA0IFG */

/************************************************************
* Timer1_A5
************************************************************/
#define __MSP430_HAS_T1A5__                   /* Definition to show that Module is available */

SFR_16BIT(TA1IV);                             /* Timer1_A5 Interrupt Vector Word */
SFR_16BIT(TA1CTL);                            /* Timer1_A5 Control */
SFR_16BIT(TA1CCTL0);                          /* Timer1_A5 Capture/Compare Control 0 */
SFR_16BIT(TA1CCTL1);                          /* Timer1_A5 Capture/Compare Control 1 */
SFR_16BIT(TA1CCTL2);                          /* Timer1_A5 Capture/Compare Control 2 */
SFR_16BIT(TA1CCTL3);                          /* Timer1_A5 Capture/Compare Control 3 */
SFR_16BIT(TA1CCTL4);                          /* Timer1_A5 Capture/Compare Control 4 */
SFR_16BIT(TA1R);                              /* Timer1_A5 */
SFR_16BIT(TA1CCR0);                           /* Timer1_A5 Capture/Compare 0 */
SFR_16BIT(TA1CCR1);                           /* Timer1_A5 Capture/Compare 1 */
SFR_16BIT(TA1CCR2);                           /* Timer1_A5 Capture/Compare 2 */
SFR_16BIT(TA1CCR3);                           /* Timer1_A5 Capture/Compare 3 */
SFR_16BIT(TA1CCR4);                           /* Timer1_A5 Capture/Compare 4 */

/* Bits are already defined within the Timer0_Ax */

/* T1_A5IV Definitions */
#define TA1IV_NONE             (0x0000)       /* No Interrupt pending */
#define TA1IV_TACCR1           (0x0002)       /* TA1CCR1_CCIFG */
#define TA1IV_TACCR2           (0x0004)       /* TA1CCR2_CCIFG */
#define TA1IV_TACCR3           (0x0006)       /* TA1CCR3_CCIFG */
#define TA1IV_TACCR4           (0x0008)       /* TA1CCR4_CCIFG */
#define TA1IV_TAIFG            (0x000A)       /* TA1IFG */

/************************************************************
* USCI
************************************************************/
#define __MSP430_HAS_USCI__                   /* Definition to show that Module is available */

SFR_8BIT(UCA0CTL0);                           /* USCI A0 Control Register 0 */
SFR_8BIT(UCA0CTL1);                           /* USCI A0 Control Register 1 */
SFR_8BIT(UCA0BR0);                            /* USCI A0 Baud Rate 0 */
SFR_8BIT(UCA0BR1);                            /* USCI A0 Baud Rate 1 */
SFR_8BIT(UCA0MCTL);                           /* USCI A0 Modulation Control */
SFR_8BIT(UCA0STAT);                           /* USCI A0 Status Register */
SFR_8BIT(UCA0RXBUF);                          /* USCI A0 Receive Buffer */
SFR_8BIT(UCA0TXBUF);                          /* USCI A0 Transmit Buffer */
SFR_8BIT(UCA0ABCTL);                          /* USCI A0 LIN Control */
SFR_8BIT(UCA0IRTCTL);                         /* USCI A0 IrDA Transmit Control */
SFR_8BIT(UCA0IRRCTL);                         /* USCI A0 IrDA Receive Control */



SFR_8BIT(UCB0CTL0);                           /* USCI B0 Control Register 0 */
SFR_8BIT(UCB0CTL1);                           /* USCI B0 Control Register 1 */
SFR_8BIT(UCB0BR0);                            /* USCI B0 Baud Rate 0 */
SFR_8BIT(UCB0BR1);                            /* USCI B0 Baud Rate 1 */
SFR_8BIT(UCB0I2CIE);                          /* USCI B0 I2C Interrupt Enable Register */
SFR_8BIT(UCB0STAT);                           /* USCI B0 Status Register */
SFR_8BIT(UCB0RXBUF);                          /* USCI B0 Receive Buffer */
SFR_8BIT(UCB0TXBUF);                          /* USCI B0 Transmit Buffer */
SFR_16BIT(UCB0I2COA);                         /* USCI B0 I2C Own Address */
SFR_16BIT(UCB0I2CSA);                         /* USCI B0 I2C Slave Address */

// UART-Mode Bits
#define UCPEN                  (0x80)         /* Async. Mode: Parity enable */
#define UCPAR                  (0x40)         /* Async. Mode: Parity     0:odd / 1:even */
#define UCMSB                  (0x20)         /* Async. Mode: MSB first  0:LSB / 1:MSB */
#define UC7BIT                 (0x10)         /* Async. Mode: Data Bits  0:8-bits / 1:7-bits */
#define UCSPB                  (0x08)         /* Async. Mode: Stop Bits  0:one / 1: two */
#define UCMODE1                (0x04)         /* Async. Mode: USCI Mode 1 */
#define UCMODE0                (0x02)         /* Async. Mode: USCI Mode 0 */
#define UCSYNC                 (0x01)         /* Sync-Mode  0:UART-Mode / 1:SPI-Mode */

// SPI-Mode Bits
#define UCCKPH                 (0x80)         /* Sync. Mode: Clock Phase */
#define UCCKPL                 (0x40)         /* Sync. Mode: Clock Polarity */
#define UCMST                  (0x08)         /* Sync. Mode: Master Select */

// I2C-Mode Bits
#define UCA10                  (0x80)         /* 10-bit Address Mode */
#define UCSLA10                (0x40)         /* 10-bit Slave Address Mode */
#define UCMM                   (0x20)         /* Multi-Master Environment */
//#define res               (0x10)    /* reserved */
#define UCMODE_0               (0x00)         /* Sync. Mode: USCI Mode: 0 */
#define UCMODE_1               (0x02)         /* Sync. Mode: USCI Mode: 1 */
#define UCMODE_2               (0x04)         /* Sync. Mode: USCI Mode: 2 */
#define UCMODE_3               (0x06)         /* Sync. Mode: USCI Mode: 3 */

// UART-Mode Bits
#define UCSSEL1                (0x80)         /* USCI 0 Clock Source Select 1 */
#define UCSSEL0                (0x40)         /* USCI 0 Clock Source Select 0 */
#define UCRXEIE                (0x20)         /* RX Error interrupt enable */
#define UCBRKIE                (0x10)         /* Break interrupt enable */
#define UCDORM                 (0x08)         /* Dormant (Sleep) Mode */
#define UCTXADDR               (0x04)         /* Send next Data as Address */
#define UCTXBRK                (0x02)         /* Send next Data as Break */
#define UCSWRST                (0x01)         /* USCI Software Reset */

// SPI-Mode Bits
//#define res               (0x20)    /* reserved */
//#define res               (0x10)    /* reserved */
//#define res               (0x08)    /* reserved */
//#define res               (0x04)    /* reserved */
//#define res               (0x02)    /* reserved */

// I2C-Mode Bits
//#define res               (0x20)    /* reserved */
#define UCTR                   (0x10)         /* Transmit/Receive Select/Flag */
#define UCTXNACK               (0x08)         /* Transmit NACK */
#define UCTXSTP                (0x04)         /* Transmit STOP */
#define UCTXSTT                (0x02)         /* Transmit START */
#define UCSSEL_0               (0x00)         /* USCI 0 Clock Source: 0 */
#define UCSSEL_1               (0x40)         /* USCI 0 Clock Source: 1 */
#define UCSSEL_2               (0x80)         /* USCI 0 Clock Source: 2 */
#define UCSSEL_3               (0xC0)         /* USCI 0 Clock Source: 3 */

#define UCBRF3                 (0x80)         /* USCI First Stage Modulation Select 3 */
#define UCBRF2                 (0x40)         /* USCI First Stage Modulation Select 2 */
#define UCBRF1                 (0x20)         /* USCI First Stage Modulation Select 1 */
#define UCBRF0                 (0x10)         /* USCI First Stage Modulation Select 0 */
#define UCBRS2                 (0x08)         /* USCI Second Stage Modulation Select 2 */
#define UCBRS1                 (0x04)         /* USCI Second Stage Modulation Select 1 */
#define UCBRS0                 (0x02)         /* USCI Second Stage Modulation Select 0 */
#define UCOS16                 (0x01)         /* USCI 16-times Oversampling enable */

#define UCBRF_0                (0x00)         /* USCI First Stage Modulation: 0 */
#define UCBRF_1                (0x10)         /* USCI First Stage Modulation: 1 */
#define UCBRF_2                (0x20)         /* USCI First Stage Modulation: 2 */
#define UCBRF_3                (0x30)         /* USCI First Stage Modulation: 3 */
#define UCBRF_4                (0x40)         /* USCI First Stage Modulation: 4 */
#define UCBRF_5                (0x50)         /* USCI First Stage Modulation: 5 */
#define UCBRF_6                (0x60)         /* USCI First Stage Modulation: 6 */
#define UCBRF_7                (0x70)         /* USCI First Stage Modulation: 7 */
#define UCBRF_8                (0x80)         /* USCI First Stage Modulation: 8 */
#define UCBRF_9                (0x90)         /* USCI First Stage Modulation: 9 */
#define UCBRF_10               (0xA0)         /* USCI First Stage Modulation: A */
#define UCBRF_11               (0xB0)         /* USCI First Stage Modulation: B */
#define UCBRF_12               (0xC0)         /* USCI First Stage Modulation: C */
#define UCBRF_13               (0xD0)         /* USCI First Stage Modulation: D */
#define UCBRF_14               (0xE0)         /* USCI First Stage Modulation: E */
#define UCBRF_15               (0xF0)         /* USCI First Stage Modulation: F */

#define UCBRS_0                (0x00)         /* USCI Second Stage Modulation: 0 */
#define UCBRS_1                (0x02)         /* USCI Second Stage Modulation: 1 */
#define UCBRS_2                (0x04)         /* USCI Second Stage Modulation: 2 */
#define UCBRS_3                (0x06)         /* USCI Second Stage Modulation: 3 */
#define UCBRS_4                (0x08)         /* USCI Second Stage Modulation: 4 */
#define UCBRS_5                (0x0A)         /* USCI Second Stage Modulation: 5 */
#define UCBRS_6                (0x0C)         /* USCI Second Stage Modulation: 6 */
#define UCBRS_7                (0x0E)         /* USCI Second Stage Modulation: 7 */

#define UCLISTEN               (0x80)         /* USCI Listen mode */
#define UCFE                   (0x40)         /* USCI Frame Error Flag */
#define UCOE                   (0x20)         /* USCI Overrun Error Flag */
#define UCPE                   (0x10)         /* USCI Parity Error Flag */
#define UCBRK                  (0x08)         /* USCI Break received */
#define UCRXERR                (0x04)         /* USCI RX Error Flag */
#define UCADDR                 (0x02)         /* USCI Address received Flag */
#define UCBUSY                 (0x01)         /* USCI Busy Flag */
#define UCIDLE                 (0x02)         /* USCI Idle line detected Flag */

//#define res               (0x80)    /* reserved */
//#define res               (0x40)    /* reserved */
//#define res               (0x20)    /* reserved */
//#define res               (0x10)    /* reserved */
#define UCNACKIE               (0x08)         /* NACK Condition interrupt enable */
#define UCSTPIE                (0x04)         /* STOP Condition interrupt enable */
#define UCSTTIE                (0x02)         /* START Condition interrupt enable */
#define UCALIE                 (0x01)         /* Arbitration Lost interrupt enable */

#define UCSCLLOW               (0x40)         /* SCL low */
#define UCGC                   (0x20)         /* General Call address received Flag */
#define UCBBUSY                (0x10)         /* Bus Busy Flag */
#define UCNACKIFG              (0x08)         /* NAK Condition interrupt Flag */
#define UCSTPIFG               (0x04)         /* STOP Condition interrupt Flag */
#define UCSTTIFG               (0x02)         /* START Condition interrupt Flag */
#define UCALIFG                (0x01)         /* Arbitration Lost interrupt Flag */

#define UCIRTXPL5              (0x80)         /* IRDA Transmit Pulse Length 5 */
#define UCIRTXPL4              (0x40)         /* IRDA Transmit Pulse Length 4 */
#define UCIRTXPL3              (0x20)         /* IRDA Transmit Pulse Length 3 */
#define UCIRTXPL2              (0x10)         /* IRDA Transmit Pulse Length 2 */
#define UCIRTXPL1              (0x08)         /* IRDA Transmit Pulse Length 1 */
#define UCIRTXPL0              (0x04)         /* IRDA Transmit Pulse Length 0 */
#define UCIRTXCLK              (0x02)         /* IRDA Transmit Pulse Clock Select */
#define UCIREN                 (0x01)         /* IRDA Encoder/Decoder enable */

#define UCIRRXFL5              (0x80)         /* IRDA Receive Filter Length 5 */
#define UCIRRXFL4              (0x40)         /* IRDA Receive Filter Length 4 */
#define UCIRRXFL3              (0x20)         /* IRDA Receive Filter Length 3 */
#define UCIRRXFL2              (0x10)         /* IRDA Receive Filter Length 2 */
#define UCIRRXFL1              (0x08)         /* IRDA Receive Filter Length 1 */
#define UCIRRXFL0              (0x04)         /* IRDA Receive Filter Length 0 */
#define UCIRRXPL               (0x02)         /* IRDA Receive Input Polarity */
#define UCIRRXFE               (0x01)         /* IRDA Receive Filter enable */

//#define res               (0x80)    /* reserved */
//#define res               (0x40)    /* reserved */
#define UCDELIM1               (0x20)         /* Break Sync Delimiter 1 */
#define UCDELIM0               (0x10)         /* Break Sync Delimiter 0 */
#define UCSTOE                 (0x08)         /* Sync-Field Timeout error */
#define UCBTOE                 (0x04)         /* Break Timeout error */
//#define res               (0x02)    /* reserved */
#define UCABDEN                (0x01)         /* Auto Baud Rate detect enable */

#define UCGCEN                 (0x8000)       /* I2C General Call enable */
#define UCOA9                  (0x0200)       /* I2C Own Address 9 */
#define UCOA8                  (0x0100)       /* I2C Own Address 8 */
#define UCOA7                  (0x0080)       /* I2C Own Address 7 */
#define UCOA6                  (0x0040)       /* I2C Own Address 6 */
#define UCOA5                  (0x0020)       /* I2C Own Address 5 */
#define UCOA4                  (0x0010)       /* I2C Own Address 4 */
#define UCOA3                  (0x0008)       /* I2C Own Address 3 */
#define UCOA2                  (0x0004)       /* I2C Own Address 2 */
#define UCOA1                  (0x0002)       /* I2C Own Address 1 */
#define UCOA0                  (0x0001)       /* I2C Own Address 0 */

#define UCSA9                  (0x0200)       /* I2C Slave Address 9 */
#define UCSA8                  (0x0100)       /* I2C Slave Address 8 */
#define UCSA7                  (0x0080)       /* I2C Slave Address 7 */
#define UCSA6                  (0x0040)       /* I2C Slave Address 6 */
#define UCSA5                  (0x0020)       /* I2C Slave Address 5 */
#define UCSA4                  (0x0010)       /* I2C Slave Address 4 */
#define UCSA3                  (0x0008)       /* I2C Slave Address 3 */
#define UCSA2                  (0x0004)       /* I2C Slave Address 2 */
#define UCSA1                  (0x0002)       /* I2C Slave Address 1 */
#define UCSA0                  (0x0001)       /* I2C Slave Address 0 */

/************************************************************
* WATCHDOG TIMER
************************************************************/
#define __MSP430_HAS_WDT__                    /* Definition to show that Module is available */

SFR_16BIT(WDTCTL);                            /* Watchdog Timer Control */
/* The bit names have been prefixed with "WDT" */
#define WDTIS0                 (0x0001)
#define WDTIS1                 (0x0002)
#define WDTSSEL                (0x0004)
#define WDTCNTCL               (0x0008)
#define WDTTMSEL               (0x0010)
#define WDTNMI                 (0x0020)
#define WDTNMIES               (0x0040)
#define WDTHOLD                (0x0080)

#define WDTPW                  (0x5A00)

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

#define VECTOR_NAME(name)       name##_ptr
#define EMIT_PRAGMA(x)          _Pragma(#x)
#define CREATE_VECTOR(name)     void (* const VECTOR_NAME(name))(void) = &name
#define PLACE_VECTOR(vector,section) EMIT_PRAGMA(DATA_SECTION(vector,section))
#define ISR_VECTOR(func,offset) CREATE_VECTOR(func); \
                                PLACE_VECTOR(VECTOR_NAME(func), offset)

#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define BASICTIMER_VECTOR       ".int00"                    /* 0xFFE0 Basic Timer */
#else
#define BASICTIMER_VECTOR       (0 * 1u)                     /* 0xFFE0 Basic Timer */
/*#define BASICTIMER_ISR(func)    ISR_VECTOR(func, ".int00")  */ /* 0xFFE0 Basic Timer */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT2_VECTOR            ".int01"                    /* 0xFFE2 Port 2 */
#else
#define PORT2_VECTOR            (1 * 1u)                     /* 0xFFE2 Port 2 */
/*#define PORT2_ISR(func)         ISR_VECTOR(func, ".int01")  */ /* 0xFFE2 Port 2 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT1_VECTOR            ".int04"                    /* 0xFFE8 Port 1 */
#else
#define PORT1_VECTOR            (4 * 1u)                     /* 0xFFE8 Port 1 */
/*#define PORT1_ISR(func)         ISR_VECTOR(func, ".int04")  */ /* 0xFFE8 Port 1 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMER0_A1_VECTOR        ".int05"                    /* 0xFFEA Timer0_A CC1-2, TA0 */
#else
#define TIMER0_A1_VECTOR        (5 * 1u)                     /* 0xFFEA Timer0_A CC1-2, TA0 */
/*#define TIMER0_A1_ISR(func)     ISR_VECTOR(func, ".int05")  */ /* 0xFFEA Timer0_A CC1-2, TA0 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMER0_A0_VECTOR        ".int06"                    /* 0xFFEC Timer0_A CC0 */
#else
#define TIMER0_A0_VECTOR        (6 * 1u)                     /* 0xFFEC Timer0_A CC0 */
/*#define TIMER0_A0_ISR(func)     ISR_VECTOR(func, ".int06")  */ /* 0xFFEC Timer0_A CC0 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define ADC10_VECTOR            ".int07"                    /* 0xFFEE ADC10 */
#else
#define ADC10_VECTOR            (7 * 1u)                     /* 0xFFEE ADC10 */
/*#define ADC10_ISR(func)         ISR_VECTOR(func, ".int07")  */ /* 0xFFEE ADC10 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USCIAB0TX_VECTOR        ".int08"                    /* 0xFFF0 USCI A0/B0 Transmit */
#else
#define USCIAB0TX_VECTOR        (8 * 1u)                     /* 0xFFF0 USCI A0/B0 Transmit */
/*#define USCIAB0TX_ISR(func)     ISR_VECTOR(func, ".int08")  */ /* 0xFFF0 USCI A0/B0 Transmit */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USCIAB0RX_VECTOR        ".int09"                    /* 0xFFF2 USCI A0/B0 Receive */
#else
#define USCIAB0RX_VECTOR        (9 * 1u)                     /* 0xFFF2 USCI A0/B0 Receive */
/*#define USCIAB0RX_ISR(func)     ISR_VECTOR(func, ".int09")  */ /* 0xFFF2 USCI A0/B0 Receive */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define WDT_VECTOR              ".int10"                    /* 0xFFF4 Watchdog Timer */
#else
#define WDT_VECTOR              (10 * 1u)                    /* 0xFFF4 Watchdog Timer */
/*#define WDT_ISR(func)           ISR_VECTOR(func, ".int10")  */ /* 0xFFF4 Watchdog Timer */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define COMPARATORA_VECTOR      ".int11"                    /* 0xFFF6 Comparator A */
#else
#define COMPARATORA_VECTOR      (11 * 1u)                    /* 0xFFF6 Comparator A */
/*#define COMPARATORA_ISR(func)   ISR_VECTOR(func, ".int11")  */ /* 0xFFF6 Comparator A */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMER1_A1_VECTOR        ".int12"                    /* 0xFFF8 Timer1_A CC1-4, TA1 */
#else
#define TIMER1_A1_VECTOR        (12 * 1u)                    /* 0xFFF8 Timer1_A CC1-4, TA1 */
/*#define TIMER1_A1_ISR(func)     ISR_VECTOR(func, ".int12")  */ /* 0xFFF8 Timer1_A CC1-4, TA1 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMER1_A0_VECTOR        ".int13"                    /* 0xFFFA Timer1_A CC0 */
#else
#define TIMER1_A0_VECTOR        (13 * 1u)                    /* 0xFFFA Timer1_A CC0 */
/*#define TIMER1_A0_ISR(func)     ISR_VECTOR(func, ".int13")  */ /* 0xFFFA Timer1_A CC0 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define NMI_VECTOR              ".int14"                    /* 0xFFFC Non-maskable */
#else
#define NMI_VECTOR              (14 * 1u)                    /* 0xFFFC Non-maskable */
/*#define NMI_ISR(func)           ISR_VECTOR(func, ".int14")  */ /* 0xFFFC Non-maskable */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESET_VECTOR            ".reset"                    /* 0xFFFE Reset [Highest Priority] */
#else
#define RESET_VECTOR            (15 * 1u)                    /* 0xFFFE Reset [Highest Priority] */
/*#define RESET_ISR(func)         ISR_VECTOR(func, ".int15")  */ /* 0xFFFE Reset [Highest Priority] */ /* CCE V2 Style */
#endif

/* Alternate Names */

/************************************************************
* End of Modules
************************************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* #ifndef __msp430x41x2 */

