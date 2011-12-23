/********************************************************************
*
* Standard register and bit definitions for the Texas Instruments
* MSP430 microcontroller.
*
* This file supports assembler and C development for
* MSP430xW42x devices.
*
* Texas Instruments, Version 2.8
*
* Rev. 2.1,  Alignment of defintions in Users Guide and of version numbers
* Rev. 2.11, Added SIFDACR
*            Added unsigned to SIFTSM definition
* Rev. 2.2,  Alignment of defintions in Users Guide and of version numbers
* Rev. 2.21, Changed Bitname form SIFLCOFF to SIFLCEN
*            Removed definition of LCDLOWR (not available at 4xx devices)
* Rev. 2.30, fixed Register name type from SIFTPSMV to SIFPSMV
* Rev. 2.31, fixed Register name for SIFDIV3_x (Dividor is *2)
* Rev. 2.4, Removed unused def of TASSEL2 / TBSSEL2
* Rev. 2.5, Added VLD bits in SVS module
* Rev. 2.6, Removed definitions for BTRESET
* Rev. 2.7, Fixed some errors in SIFDIV3_xx definitions
* Rev. 2.8, added definitions for Interrupt Vectors xxIV
*
********************************************************************/

#ifndef __msp430xW42x
#define __msp430xW42x

#define __MSP430_HEADER_VERSION__ 1059

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error msp430fw428.h file for use with ICC430/A430 only
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
#define WDTIE               (0x01)
#define OFIE                (0x02)
#define NMIIE               (0x10)
#define ACCVIE              (0x20)

#define IFG1_               (0x0002u)  /* Interrupt Flag 1 */
DEFC(   IFG1              , IFG1_)
#define WDTIFG              (0x01)
#define OFIFG               (0x02)
#define NMIIFG              (0x10)

#define IE2_                (0x0001u)  /* Interrupt Enable 2 */
DEFC(   IE2               , IE2_)
#define BTIE                (0x80)

#define IFG2_               (0x0003u)  /* Interrupt Flag 2 */
DEFC(   IFG2              , IFG2_)
#define BTIFG               (0x80)

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
* BASIC TIMER
************************************************************/
#define __MSP430_HAS_BT__             /* Definition to show that Module is available */

#define BTCTL_              (0x0040u)  /* Basic Timer Control */
DEFC(   BTCTL             , BTCTL_)
/* The bit names have been prefixed with "BT" */
#define BTIP0               (0x01)
#define BTIP1               (0x02)
#define BTIP2               (0x04)
#define BTFRFQ0             (0x08)
#define BTFRFQ1             (0x10)
#define BTDIV               (0x20)                     /* fCLK2 = ACLK:256 */
#define BTHOLD              (0x40)                     /* BT1 is held if this bit is set */
#define BTSSEL              (0x80)                     /* fBT = fMCLK (main clock) */

#define BTCNT1_             (0x0046u)  /* Basic Timer Count 1 */
DEFC(   BTCNT1            , BTCNT1_)
#define BTCNT2_             (0x0047u)  /* Basic Timer Count 2 */
DEFC(   BTCNT2            , BTCNT2_)

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
/* Frequency of LCD coded with Bits 3-4 */
#define BT_fLCD_DIV32       (0x00)                    /* fLCD = fACLK:32 (default) */
#define BT_fLCD_DIV64       (BTFRFQ0)                 /* fLCD = fACLK:64 */
#define BT_fLCD_DIV128      (BTFRFQ1)                 /* fLCD = fACLK:128 */
#define BT_fLCD_DIV256      (BTFRFQ1+BTFRFQ0)         /* fLCD = fACLK:256 */
/* LCD frequency values with fBT=fACLK */
#define BT_fLCD_1K          (0x00)                    /* fACLK:32 (default) */
#define BT_fLCD_512         (BTFRFQ0)                 /* fACLK:64 */
#define BT_fLCD_256         (BTFRFQ1)                 /* fACLK:128 */
#define BT_fLCD_128         (BTFRFQ1+BTFRFQ0)         /* fACLK:256 */
/* LCD frequency values with fBT=fMCLK */
#define BT_fLCD_31K         (BTSSEL)                  /* fMCLK:32 */
#define BT_fLCD_15_5K       (BTSSEL+BTFRFQ0)          /* fMCLK:64 */
#define BT_fLCD_7_8K        (BTSSEL+BTFRFQ1+BTFRFQ0)  /* fMCLK:256 */
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

/* Reset/Hold coded with Bits 6-7 in BT(1)CTL */
/* this is for BT */
//#define BTRESET_CNT1        (BTRESET)           /* BTCNT1 is reset while BTRESET is set */
//#define BTRESET_CNT1_2      (BTRESET+BTDIV)     /* BTCNT1 .AND. BTCNT2 are reset while ~ is set */
/* this is for BT1 */
#define BTHOLD_CNT1         (BTHOLD)            /* BTCNT1 is held while BTHOLD is set */
#define BTHOLD_CNT1_2       (BTHOLD+BTDIV)      /* BT1CNT1 .AND. BT1CNT2 are held while ~ is set */

/* INTERRUPT CONTROL BITS */
/* #define BTIE                0x80 */
/* #define BTIFG               0x80 */

/************************************************************
* SYSTEM CLOCK, FLL+ (x41x)
************************************************************/
#define __MSP430_HAS_FLLPLUS_SMALL__  /* Definition to show that Module is available */

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
#define XT1OF               (0x04)                     /* High Frequency Oscillator Fault Flag */
#define OSCCAP0             (0x10)                     /* XIN/XOUT Cap 0 */
#define OSCCAP1             (0x20)                     /* XIN/XOUT Cap 1 */
#define XTS_FLL             (0x40)                     /* 1: Selects high-freq. oscillator */
#define DCOPLUS             (0x80)                     /* DCO+ Enable */

#define XCAP0PF             (0x00)                     /* XIN Cap = XOUT Cap = 0pf */
#define XCAP10PF            (0x10)                     /* XIN Cap = XOUT Cap = 10pf */
#define XCAP14PF            (0x20)                     /* XIN Cap = XOUT Cap = 14pf */
#define XCAP18PF            (0x30)                     /* XIN Cap = XOUT Cap = 18pf */
#define OSCCAP_0            (0x00)                     /* XIN Cap = XOUT Cap = 0pf */
#define OSCCAP_1            (0x10)                     /* XIN Cap = XOUT Cap = 10pf */
#define OSCCAP_2            (0x20)                     /* XIN Cap = XOUT Cap = 14pf */
#define OSCCAP_3            (0x30)                     /* XIN Cap = XOUT Cap = 18pf */

#define FLL_CTL1_           (0x0054u)  /* FLL+ Control 1 */
DEFC(   FLL_CTL1          , FLL_CTL1_)
#define FLL_DIV0            (0x01)                     /* FLL+ Divide Px.x/ACLK 0 */
#define FLL_DIV1            (0x02)                     /* FLL+ Divide Px.x/ACLK 1 */

#define FLL_DIV_1           (0x00)                     /* FLL+ Divide Px.x/ACLK By 1 */
#define FLL_DIV_2           (0x01)                     /* FLL+ Divide Px.x/ACLK By 2 */
#define FLL_DIV_4           (0x02)                     /* FLL+ Divide Px.x/ACLK By 4 */
#define FLL_DIV_8           (0x03)                     /* FLL+ Divide Px.x/ACLK By 8 */

/* INTERRUPT CONTROL BITS */
/* These two bits are defined in the Special Function Registers */
/* #define OFIFG               0x02 */
/* #define OFIE                0x02 */

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
* LCD
************************************************************/
#define __MSP430_HAS_LCD4__           /* Definition to show that Module is available */

#define LCDCTL_             (0x0090u)  /* LCD Control */
DEFC(   LCDCTL            , LCDCTL_)
/* the names of the mode bits are different from the spec */
#define LCDON               (0x01)
//#define LCDLOWR             (0x02)
#define LCDSON              (0x04)
#define LCDMX0              (0x08)
#define LCDMX1              (0x10)
#define LCDP0               (0x20)
#define LCDP1               (0x40)
#define LCDP2               (0x80)
/* Display modes coded with Bits 2-4 */
#define LCDSTATIC           (LCDSON)
#define LCD2MUX             (LCDMX0+LCDSON)
#define LCD3MUX             (LCDMX1+LCDSON)
#define LCD4MUX             (LCDMX1+LCDMX0+LCDSON)
/* Group select code with Bits 5-7                     Seg.lines   Dig.output */
#define LCDSG0              (0x00)                    /* ---------   Port Only (default) */
#define LCDSG0_1            (LCDP0)                   /* S0  - S15   see Datasheet */
#define LCDSG0_2            (LCDP1)                   /* S0  - S19   see Datasheet */
#define LCDSG0_3            (LCDP1+LCDP0)             /* S0  - S23   see Datasheet */
#define LCDSG0_4            (LCDP2)                   /* S0  - S27   see Datasheet */
#define LCDSG0_5            (LCDP2+LCDP0)             /* S0  - S31   see Datasheet */
#define LCDSG0_6            (LCDP2+LCDP1)             /* S0  - S35   see Datasheet */
#define LCDSG0_7            (LCDP2+LCDP1+LCDP0)       /* S0  - S39   see Datasheet */
/* NOTE: YOU CAN ONLY USE THE 'S' OR 'G' DECLARATIONS FOR A COMMAND */
/* MOV  #LCDSG0_3+LCDOG2_7,&LCDCTL ACTUALY MEANS MOV  #LCDP1,&LCDCTL! */
#define LCDOG1_7            (0x00)                    /* ---------   Port Only (default) */
#define LCDOG2_7            (LCDP0)                   /* S0  - S15   see Datasheet */
#define LCDOG3_7            (LCDP1)                   /* S0  - S19   see Datasheet */
#define LCDOG4_7            (LCDP1+LCDP0)             /* S0  - S23   see Datasheet */
#define LCDOG5_7            (LCDP2)                   /* S0  - S27   see Datasheet */
#define LCDOG6_7            (LCDP2+LCDP0)             /* S0  - S31   see Datasheet */
#define LCDOG7              (LCDP2+LCDP1)             /* S0  - S35   see Datasheet */
#define LCDOGOFF            (LCDP2+LCDP1+LCDP0)       /* S0  - S39   see Datasheet */

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

/*************************************************************
* Flash Memory
*************************************************************/
#define __MSP430_HAS_FLASH__          /* Definition to show that Module is available */

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

/************************************************************
* Comparator A
************************************************************/
#define __MSP430_HAS_COMPA__          /* Definition to show that Module is available */

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
#define P2CA0               (0x04)    /* Comp. A Connect External Signal to CA0 : 1 */
#define P2CA1               (0x08)    /* Comp. A Connect External Signal to CA1 : 1 */
#define CACTL24             (0x10)
#define CACTL25             (0x20)
#define CACTL26             (0x40)
#define CACTL27             (0x80)

#define CAPD0               (0x01)    /* Comp. A Disable Input Buffer of Port Register .0 */
#define CAPD1               (0x02)    /* Comp. A Disable Input Buffer of Port Register .1 */
#define CAPD2               (0x04)    /* Comp. A Disable Input Buffer of Port Register .2 */
#define CAPD3               (0x08)    /* Comp. A Disable Input Buffer of Port Register .3 */
#define CAPD4               (0x10)    /* Comp. A Disable Input Buffer of Port Register .4 */
#define CAPD5               (0x20)    /* Comp. A Disable Input Buffer of Port Register .5 */
#define CAPD6               (0x40)    /* Comp. A Disable Input Buffer of Port Register .6 */
#define CAPD7               (0x80)    /* Comp. A Disable Input Buffer of Port Register .7 */

/************************************************************
* Scan-I/F
************************************************************/
#define __MSP430_HAS_SCANIF__         /* Definition to show that Module is available */

#define SIFDEBUG_           (0x01B0u)  /* SIF, Debug Register */
DEFW(   SIFDEBUG          , SIFDEBUG_)
#define SIFCNT_             (0x01B2u)  /* SIF, Counter1/2 */
DEFW(   SIFCNT            , SIFCNT_)
#define SIFPSMV_            (0x01B4u)  /* SIF, Processing State Machine */
DEFW(   SIFPSMV           , SIFPSMV_)
#define SIFCTL1_            (0x01B6u)  /* SIF, Control Register 1 */
DEFW(   SIFCTL1           , SIFCTL1_)
#define SIFCTL2_            (0x01B8u)  /* SIF, Control Register 2 */
DEFW(   SIFCTL2           , SIFCTL2_)
#define SIFCTL3_            (0x01BAu)  /* SIF, Control Register 3 */
DEFW(   SIFCTL3           , SIFCTL3_)
#define SIFCTL4_            (0x01BCu)  /* SIF, Control Register 4 */
DEFW(   SIFCTL4           , SIFCTL4_)
#define SIFCTL5_            (0x01BEu)  /* SIF, Control Register 5 */
DEFW(   SIFCTL5           , SIFCTL5_)
#define SIFDACR_            (0x01C0u)  /* SIF, Digital to Analog Conv. 0 */
#ifndef __IAR_SYSTEMS_ICC__
#define SIFDACR             (SIFDACR_) /* SIF, Digital to Analog Conv. Memory (for assembler) */
#else
#define SIFDACR             ((unsigned int*) SIFDACR_) /* SIF, Digital to Analog Conv. Memory (for C) */
#endif
#define SIFDACR0_           (0x01C0u)  /* SIF, Digital to Analog Conv. 0 */
DEFW(   SIFDACR0          , SIFDACR0_)
#define SIFDACR1_           (0x01C2u)  /* SIF, Digital to Analog Conv. 1 */
DEFW(   SIFDACR1          , SIFDACR1_)
#define SIFDACR2_           (0x01C4u)  /* SIF, Digital to Analog Conv. 2 */
DEFW(   SIFDACR2          , SIFDACR2_)
#define SIFDACR3_           (0x01C6u)  /* SIF, Digital to Analog Conv. 3 */
DEFW(   SIFDACR3          , SIFDACR3_)
#define SIFDACR4_           (0x01C8u)  /* SIF, Digital to Analog Conv. 4 */
DEFW(   SIFDACR4          , SIFDACR4_)
#define SIFDACR5_           (0x01CAu)  /* SIF, Digital to Analog Conv. 5 */
DEFW(   SIFDACR5          , SIFDACR5_)
#define SIFDACR6_           (0x01CCu)  /* SIF, Digital to Analog Conv. 6 */
DEFW(   SIFDACR6          , SIFDACR6_)
#define SIFDACR7_           (0x01CEu)  /* SIF, Digital to Analog Conv. 7 */
DEFW(   SIFDACR7          , SIFDACR7_)
#define SIFTSM_             (0x01D0u)  /* SIF, Timing State Machine 0 */
#ifndef __IAR_SYSTEMS_ICC__
#define SIFTSM              (SIFTSM_) /* SIF, Timing State Machine (for assembler) */
#else
#define SIFTSM              ((unsigned int*) SIFTSM_) /* SIF, Timing State Machine (for C) */
#endif
#define SIFTSM0_            (0x01D0u)  /* SIF, Timing State Machine 0 */
DEFW(   SIFTSM0           , SIFTSM0_)
#define SIFTSM1_            (0x01D2u)  /* SIF, Timing State Machine 1 */
DEFW(   SIFTSM1           , SIFTSM1_)
#define SIFTSM2_            (0x01D4u)  /* SIF, Timing State Machine 2 */
DEFW(   SIFTSM2           , SIFTSM2_)
#define SIFTSM3_            (0x01D6u)  /* SIF, Timing State Machine 3 */
DEFW(   SIFTSM3           , SIFTSM3_)
#define SIFTSM4_            (0x01D8u)  /* SIF, Timing State Machine 4 */
DEFW(   SIFTSM4           , SIFTSM4_)
#define SIFTSM5_            (0x01DAu)  /* SIF, Timing State Machine 5 */
DEFW(   SIFTSM5           , SIFTSM5_)
#define SIFTSM6_            (0x01DCu)  /* SIF, Timing State Machine 6 */
DEFW(   SIFTSM6           , SIFTSM6_)
#define SIFTSM7_            (0x01DEu)  /* SIF, Timing State Machine 7 */
DEFW(   SIFTSM7           , SIFTSM7_)
#define SIFTSM8_            (0x01E0u)  /* SIF, Timing State Machine 8 */
DEFW(   SIFTSM8           , SIFTSM8_)
#define SIFTSM9_            (0x01E2u)  /* SIF, Timing State Machine 9 */
DEFW(   SIFTSM9           , SIFTSM9_)
#define SIFTSM10_           (0x01E4u)  /* SIF, Timing State Machine 10 */
DEFW(   SIFTSM10          , SIFTSM10_)
#define SIFTSM11_           (0x01E6u)  /* SIF, Timing State Machine 11 */
DEFW(   SIFTSM11          , SIFTSM11_)
#define SIFTSM12_           (0x01E8u)  /* SIF, Timing State Machine 12 */
DEFW(   SIFTSM12          , SIFTSM12_)
#define SIFTSM13_           (0x01EAu)  /* SIF, Timing State Machine 13 */
DEFW(   SIFTSM13          , SIFTSM13_)
#define SIFTSM14_           (0x01ECu)  /* SIF, Timing State Machine 14 */
DEFW(   SIFTSM14          , SIFTSM14_)
#define SIFTSM15_           (0x01EEu)  /* SIF, Timing State Machine 15 */
DEFW(   SIFTSM15          , SIFTSM15_)
#define SIFTSM16_           (0x01F0u)  /* SIF, Timing State Machine 16 */
DEFW(   SIFTSM16          , SIFTSM16_)
#define SIFTSM17_           (0x01F2u)  /* SIF, Timing State Machine 17 */
DEFW(   SIFTSM17          , SIFTSM17_)
#define SIFTSM18_           (0x01F4u)  /* SIF, Timing State Machine 18 */
DEFW(   SIFTSM18          , SIFTSM18_)
#define SIFTSM19_           (0x01F6u)  /* SIF, Timing State Machine 19 */
DEFW(   SIFTSM19          , SIFTSM19_)
#define SIFTSM20_           (0x01F8u)  /* SIF, Timing State Machine 20 */
DEFW(   SIFTSM20          , SIFTSM20_)
#define SIFTSM21_           (0x01FAu)  /* SIF, Timing State Machine 21 */
DEFW(   SIFTSM21          , SIFTSM21_)
#define SIFTSM22_           (0x01FCu)  /* SIF, Timing State Machine 22 */
DEFW(   SIFTSM22          , SIFTSM22_)
#define SIFTSM23_           (0x01FEu)  /* SIF, Timing State Machine 23 */
DEFW(   SIFTSM23          , SIFTSM23_)

/* SIFCTL1 */
#define SIFEN               (0x0001u)    /* SIF Enable */
#define SIFTESTD            (0x0002u)    /* SIF 0:Normal / 1:Test Mode */
#define SIFIFG0             (0x0004u)    /* SIF Interrupt Flag 0 */
#define SIFIFG1             (0x0008u)    /* SIF Interrupt Flag 1 */
#define SIFIFG2             (0x0010u)    /* SIF Interrupt Flag 2 */
#define SIFIFG3             (0x0020u)    /* SIF Interrupt Flag 3 */
#define SIFIFG4             (0x0040u)    /* SIF Interrupt Flag 4 */
#define SIFIFG5             (0x0080u)    /* SIF Interrupt Flag 5 */
#define SIFIFG6             (0x0100u)    /* SIF Interrupt Flag 6 */
#define SIFIE0              (0x0200u)    /* SIF Interrupt Enable 0 */
#define SIFIE1              (0x0400u)    /* SIF Interrupt Enable 1 */
#define SIFIE2              (0x0800u)    /* SIF Interrupt Enable 2 */
#define SIFIE3              (0x1000u)    /* SIF Interrupt Enable 3 */
#define SIFIE4              (0x2000u)    /* SIF Interrupt Enable 4 */
#define SIFIE5              (0x4000u)    /* SIF Interrupt Enable 5 */
#define SIFIE6              (0x8000u)    /* SIF Interrupt Enable 6 */

/* SIFCTL2 */
#define SIFTCH0OUT          (0x0001u)    /* SIF TCH0 result */
#define SIFTCH1OUT          (0x0002u)    /* SIF TCH1 result */
#define SIFTCH00            (0x0004u)    /* SIF 1. Channel select 0 */
#define SIFTCH01            (0x0008u)    /* SIF 1. Channel select 1 */
#define SIFTCH10            (0x0010u)    /* SIF 2. Channel select 0 */
#define SIFTCH11            (0x0020u)    /* SIF 2. Channel select 1 */
#define SIFTEN              (0x0040u)    /* SIF Enable Transistors */
#define SIFSH               (0x0080u)    /* SIF Sample on/off */
#define SIFVCC2             (0x0100u)    /* SIF VCC/2 Generator off/on */
#define SIFVSS              (0x0200u)    /* SIF Select Terminal for sample Cap. */
#define SIFCACI3            (0x0400u)    /* SIF Selection of SIFCI3 */
#define SIFCISEL            (0x0800u)    /* SIF Comparator Input Select */
#define SIFCAX              (0x1000u)    /* SIF Select CA Source */
#define SIFCAINV            (0x2000u)    /* SIF Invert CA Output 0:off/1:on */
#define SIFCAON             (0x4000u)    /* SIF Switch CA on */
#define SIFDACON            (0x8000u)    /* SIF Switch DAC on */

/* SIFCTL3 */
#define SIF0OUT             (0x0001u)    /* SIF Sensor 0 Out */
#define SIF1OUT             (0x0002u)    /* SIF Sensor 1 Out */
#define SIF2OUT             (0x0004u)    /* SIF Sensor 2 Out */
#define SIF3OUT             (0x0008u)    /* SIF Sensor 3 Out */
#define SIFIFGSET0          (0x0010u)    /* SIF SIFIFG0 level select */
#define SIFIFGSET1          (0x0020u)    /* SIF SIFIFG1 level select */
#define SIFIFGSET2          (0x0040u)    /* SIF SIFIFG2 level select */
#define SIFCS               (0x0080u)    /* SIF Capture Select */
#define SIFIS10             (0x0100u)    /* SIF SIFIFG3 Int.Flag Source 0 */
#define SIFIS11             (0x0200u)    /* SIF SIFIFG3 Int.Flag Source 1 */
#define SIFIS20             (0x0400u)    /* SIF SIFIFG4 Int.Flag Source 0 */
#define SIFIS21             (0x0800u)    /* SIF SIFIFG4 Int.Flag Source 1 */
#define SIFS10              (0x1000u)    /* SIF S1 Source Select 0 */
#define SIFS11              (0x2000u)    /* SIF S1 Source Select 1 */
#define SIFS20              (0x4000u)    /* SIF S2 Source Select 0 */
#define SIFS21              (0x8000u)    /* SIF S2 Source Select 1 */

#define SIFIS1_0            (0x0000u)    /* SIF SIFIFG3 set with each count of SIFCNT1 */
#define SIFIS1_1            (0x0100u)    /* SIF SIFIFG3 set if (SIFCNT1 mod  4)=0 */
#define SIFIS1_2            (0x0200u)    /* SIF SIFIFG3 set if (SIFCNT1 mod 64)=0 */
#define SIFIS1_3            (0x0300u)    /* SIF SIFIFG3 set if SIFCNT1 rolls over */
#define SIFIS2_0            (0x0000u)    /* SIF SIFIFG4 set with each count of SIFCNT2 */
#define SIFIS2_1            (0x0400u)    /* SIF SIFIFG4 set if (SIFCNT2 mod  4)=0 */
#define SIFIS2_2            (0x0800u)    /* SIF SIFIFG4 set if (SIFCNT2 mod 64)=0 */
#define SIFIS2_3            (0x0C00u)    /* SIF SIFIFG4 set if SIFCNT2 rolls over */
#define SIFS1_0             (0x0000u)    /* SIF S1 Source : SIF0OUT */
#define SIFS1_1             (0x1000u)    /* SIF S1 Source : SIF1OUT */
#define SIFS1_2             (0x2000u)    /* SIF S1 Source : SIF2OUT */
#define SIFS1_3             (0x3000u)    /* SIF S1 Source : SIF3OUT */
#define SIFS2_0             (0x0000u)    /* SIF S2 Source : SIF0OUT */
#define SIFS2_1             (0x4000u)    /* SIF S2 Source : SIF1OUT */
#define SIFS2_2             (0x8000u)    /* SIF S2 Source : SIF2OUT */
#define SIFS2_3             (0xC000u)    /* SIF S2 Source : SIF3OUT */

/* SIFCTL4 */
#define SIFDIV10            (0x0001u)    /* SIF Clock Divider 1.0 */
#define SIFDIV11            (0x0002u)    /* SIF Clock Divider 1.1 */
#define SIFDIV20            (0x0004u)    /* SIF Clock Divider 2.0 */
#define SIFDIV21            (0x0008u)    /* SIF Clock Divider 2.1 */
#define SIFDIV3A0           (0x0010u)    /* SIF Clock Divider 3.0 */
#define SIFDIV3A1           (0x0020u)    /* SIF Clock Divider 3.1 */
#define SIFDIV3A2           (0x0040u)    /* SIF Clock Divider 3.2 */
#define SIFDIV3B0           (0x0080u)    /* SIF Clock Divider 3.3 */
#define SIFDIV3B1           (0x0100u)    /* SIF Clock Divider 3.4 */
#define SIFDIV3B2           (0x0200u)    /* SIF Clock Divider 3.5 */
#define SIFQ6EN             (0x0400u)    /* SIF Feedback 6 Enable */
#define SIFQ7EN             (0x0800u)    /* SIF Feedback 7 Enable */
#define SIFCNT1ENP          (0x1000u)    /* SIF Enable SIFCNT1 up count */
#define SIFCNT1ENM          (0x2000u)    /* SIF Enable SIFCNT1 down count */
#define SIFCNT2EN           (0x4000u)    /* SIF Enable SIFCNT2 count */
#define SIFCNTRST           (0x8000u)    /* SIF Enable Counter Reset on Read */

#define SIFDIV1_1           (0x0000u)    /* SIF Clock Divider 1: /1 */
#define SIFDIV1_2           (0x0001u)    /* SIF Clock Divider 1: /2 */
#define SIFDIV1_4           (0x0002u)    /* SIF Clock Divider 1: /4 */
#define SIFDIV1_8           (0x0003u)    /* SIF Clock Divider 1: /8 */
#define SIFDIV2_1           (0x0000u)    /* SIF Clock Divider 2: /1 */
#define SIFDIV2_2           (0x0004u)    /* SIF Clock Divider 2: /2 */
#define SIFDIV2_4           (0x0008u)    /* SIF Clock Divider 2: /4 */
#define SIFDIV2_8           (0x000Cu)    /* SIF Clock Divider 2: /8 */

#define SIFDIV3_2           (0x0000u)    /* SIF Clock Divider 3: /2 */
#define SIFDIV3_6           (0x0010u)    /* SIF Clock Divider 3: /6 */
#define SIFDIV3_10          (0x0020u)    /* SIF Clock Divider 3: /10 */
#define SIFDIV3_14          (0x0030u)    /* SIF Clock Divider 3: /14 */
#define SIFDIV3_18          (0x0040u)    /* SIF Clock Divider 3: /18 */
#define SIFDIV3_22          (0x0050u)    /* SIF Clock Divider 3: /22 */
#define SIFDIV3_26          (0x0060u)    /* SIF Clock Divider 3: /26 */
#define SIFDIV3_30          (0x0070u)    /* SIF Clock Divider 3: /30 */
#define SIFDIV3_42          (0x00B0u)    /* SIF Clock Divider 3: /42 */
#define SIFDIV3_50          (0x0120u)    /* SIF Clock Divider 3: /50 */
#define SIFDIV3_54          (0x00C0u)    /* SIF Clock Divider 3: /54 */
#define SIFDIV3_66          (0x00D0u)    /* SIF Clock Divider 3: /66 */
#define SIFDIV3_70          (0x0130u)    /* SIF Clock Divider 3: /70 */
#define SIFDIV3_78          (0x00E0u)    /* SIF Clock Divider 3: /78 */
#define SIFDIV3_90          (0x00F0u)    /* SIF Clock Divider 3: /90 */
#define SIFDIV3_98          (0x01B0u)    /* SIF Clock Divider 3: /98 */
#define SIFDIV3_110         (0x0150u)    /* SIF Clock Divider 3: /110 */
#define SIFDIV3_126         (0x01C0u)    /* SIF Clock Divider 3: /126 */
#define SIFDIV3_130         (0x0160u)    /* SIF Clock Divider 3: /130 */
#define SIFDIV3_150         (0x0170u)    /* SIF Clock Divider 3: /150 */
#define SIFDIV3_154         (0x01D0u)    /* SIF Clock Divider 3: /154 */
#define SIFDIV3_162         (0x0240u)    /* SIF Clock Divider 3: /162 */
#define SIFDIV3_182         (0x01E0u)    /* SIF Clock Divider 3: /182 */
#define SIFDIV3_198         (0x0250u)    /* SIF Clock Divider 3: /198 */
#define SIFDIV3_210         (0x01F0u)    /* SIF Clock Divider 3: /210 */
#define SIFDIV3_234         (0x0260u)    /* SIF Clock Divider 3: /234 */
#define SIFDIV3_242         (0x02D0u)    /* SIF Clock Divider 3: /242 */
#define SIFDIV3_270         (0x0270u)    /* SIF Clock Divider 3: /270 */
#define SIFDIV3_286         (0x02E0u)    /* SIF Clock Divider 3: /286 */
#define SIFDIV3_330         (0x02F0u)    /* SIF Clock Divider 3: /330 */
#define SIFDIV3_338         (0x0360u)    /* SIF Clock Divider 3: /338 */
#define SIFDIV3_390         (0x0370u)    /* SIF Clock Divider 3: /390 */
#define SIFDIV3_450         (0x03F0u)    /* SIF Clock Divider 3: /450 */

/* SIFCTL5 */
#define SIFCLKEN            (0x0001u)    /* SIF 0:SMCLK for SIFCLK / 1:SIFCLKG for SIFCLK */
#define SIFCLKGON           (0x0002u)    /* SIF Switch SIFCLKG on */
#define SIFFNOM             (0x0004u)    /* SIF Select Nominal Frequ. 0:4MHz / 1:1MHz */
#define SIFCLKFQ0           (0x0008u)    /* SIF Clock Generator frequency adjust 0 */
#define SIFCLKFQ1           (0x0010u)    /* SIF Clock Generator frequency adjust 1 */
#define SIFCLKFQ2           (0x0020u)    /* SIF Clock Generator frequency adjust 2 */
#define SIFCLKFQ3           (0x0040u)    /* SIF Clock Generator frequency adjust 3 */
#define SIFTSMRP            (0x0080u)    /* SIF Timing State Machine Repeat mode */
#define SIFCNT30            (0x0100u)    /* SIF Counter 3.0 */
#define SIFCNT31            (0x0200u)    /* SIF Counter 3.1 */
#define SIFCNT32            (0x0400u)    /* SIF Counter 3.2 */
#define SIFCNT33            (0x0800u)    /* SIF Counter 3.3 */
#define SIFCNT34            (0x1000u)    /* SIF Counter 3.4 */
#define SIFCNT35            (0x2000u)    /* SIF Counter 3.5 */
#define SIFCNT36            (0x4000u)    /* SIF Counter 3.6 */
#define SIFCNT37            (0x8000u)    /* SIF Counter 3.7 */

/* SIFTSM */
#define SIFCH0              (0x0001u)    /* SIF Select channel for tsm: 0 */
#define SIFCH1              (0x0002u)    /* SIF Select channel for tsm: 1 */
#define SIFLCEN             (0x0004u)    /* SIF LC enable */
#define SIFEX               (0x0008u)    /* SIF  */
#define SIFCA               (0x0010u)    /* SIF  */
#define SIFCLKON            (0x0020u)    /* SIF  */
#define SIFRSON             (0x0040u)    /* SIF  */
#define SIFTESTS1           (0x0080u)    /* SIF  */
#define SIFDAC              (0x0100u)    /* SIF  */
#define SIFSTOP             (0x0200u)    /* SIF  */
#define SIFACLK             (0x0400u)    /* SIF  */
#define SIFREPEAT0          (0x0800u)    /* SIF  */
#define SIFREPEAT1          (0x1000u)    /* SIF  */
#define SIFREPEAT2          (0x2000u)    /* SIF  */
#define SIFREPEAT3          (0x4000u)    /* SIF  */
#define SIFREPEAT4          (0x8000u)    /* SIF  */

/************************************************************
* Interrupt Vectors (offset from 0xFFE0)
************************************************************/

#define BASICTIMER_VECTOR   (0 * 2u)  /* 0xFFE0 Basic Timer */
#define PORT2_VECTOR        (1 * 2u)  /* 0xFFE2 Port 2 */
#define PORT1_VECTOR        (4 * 2u)  /* 0xFFE8 Port 1 */
#define TIMER0_A1_VECTOR    (5 * 2u)  /* 0xFFEA Timer0_A CC1-2, TA0 */
#define TIMER0_A0_VECTOR    (6 * 2u)  /* 0xFFEC Timer0_A CC0 */
#define SCANIF_VECTOR       (9 * 2u)  /* 0xFFF2 Scan Inteface */
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

#endif /* #ifndef __msp430xW42x */

