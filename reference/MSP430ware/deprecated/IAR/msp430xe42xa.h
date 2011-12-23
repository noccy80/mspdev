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
* MSP430xE42xA devices.
*
* Texas Instruments, Version 1.2
*
*
* Rev. 1.0,  Initial Version
* Rev. 1.1,  Definition of CAPIND removed
* Rev. 1.2, added definitions for Interrupt Vectors xxIV
*
********************************************************************/

#ifndef __msp430xE42x
#define __msp430xE42x

#define __MSP430_HEADER_VERSION__ 1059

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error msp430xe42xa.h file for use with ICC430/A430 only
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
#define U0IE                IE1       /* UART0 Interrupt Enable Register */
#define WDTIE               (0x01)
#define OFIE                (0x02)
#define NMIIE               (0x10)
#define ACCVIE              (0x20)
#define URXIE0              (0x40)
#define UTXIE0              (0x80)

#define IFG1_               (0x0002u)  /* Interrupt Flag 1 */
DEFC(   IFG1              , IFG1_)
#define U0IFG               IFG1      /* UART0 Interrupt Flag Register */
#define WDTIFG              (0x01)
#define OFIFG               (0x02)
#define NMIIFG              (0x10)
#define URXIFG0             (0x40)
#define UTXIFG0             (0x80)

#define ME1_                (0x0004u)  /* Module Enable 1 */
DEFC(   ME1               , ME1_)
#define U0ME                ME1       /* UART0 Module Enable Register */
#define URXE0               (0x40)
#define UTXE0               (0x80)
#define USPIE0              (0x40)

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
* USART
************************************************************/

/* UxCTL */
#define PENA                (0x80)        /* Parity enable */
#define PEV                 (0x40)        /* Parity 0:odd / 1:even */
#define SPB                 (0x20)        /* Stop Bits 0:one / 1: two */
#define CHAR                (0x10)        /* Data 0:7-bits / 1:8-bits */
#define LISTEN              (0x08)        /* Listen mode */
#define SYNC                (0x04)        /* UART / SPI mode */
#define MM                  (0x02)        /* Master Mode off/on */
#define SWRST               (0x01)        /* USART Software Reset */

/* UxTCTL */
#define CKPH                (0x80)        /* SPI: Clock Phase */
#define CKPL                (0x40)        /* Clock Polarity */
#define SSEL1               (0x20)        /* Clock Source Select 1 */
#define SSEL0               (0x10)        /* Clock Source Select 0 */
#define URXSE               (0x08)        /* Receive Start edge select */
#define TXWAKE              (0x04)        /* TX Wake up mode */
#define STC                 (0x02)        /* SPI: STC enable 0:on / 1:off */
#define TXEPT               (0x01)        /* TX Buffer empty */

/* UxRCTL */
#define FE                  (0x80)        /* Frame Error */
#define PE                  (0x40)        /* Parity Error */
#define OE                  (0x20)        /* Overrun Error */
#define BRK                 (0x10)        /* Break detected */
#define URXEIE              (0x08)        /* RX Error interrupt enable */
#define URXWIE              (0x04)        /* RX Wake up interrupt enable */
#define RXWAKE              (0x02)        /* RX Wake up detect */
#define RXERR               (0x01)        /* RX Error Error */

/************************************************************
* USART 0
************************************************************/
#define __MSP430_HAS_UART0__          /* Definition to show that Module is available */

#define U0CTL_              (0x0070u)  /* USART 0 Control */
DEFC(   U0CTL             , U0CTL_)
#define U0TCTL_             (0x0071u)  /* USART 0 Transmit Control */
DEFC(   U0TCTL            , U0TCTL_)
#define U0RCTL_             (0x0072u)  /* USART 0 Receive Control */
DEFC(   U0RCTL            , U0RCTL_)
#define U0MCTL_             (0x0073u)  /* USART 0 Modulation Control */
DEFC(   U0MCTL            , U0MCTL_)
#define U0BR0_              (0x0074u)  /* USART 0 Baud Rate 0 */
DEFC(   U0BR0             , U0BR0_)
#define U0BR1_              (0x0075u)  /* USART 0 Baud Rate 1 */
DEFC(   U0BR1             , U0BR1_)
#define U0RXBUF_            (0x0076u)  /* USART 0 Receive Buffer */
READ_ONLY DEFC( U0RXBUF        , U0RXBUF_)
#define U0TXBUF_            (0x0077u)  /* USART 0 Transmit Buffer */
DEFC(   U0TXBUF           , U0TXBUF_)

/* Alternate register names */

#define UCTL0               U0CTL     /* USART 0 Control */
#define UTCTL0              U0TCTL    /* USART 0 Transmit Control */
#define URCTL0              U0RCTL    /* USART 0 Receive Control */
#define UMCTL0              U0MCTL    /* USART 0 Modulation Control */
#define UBR00               U0BR0     /* USART 0 Baud Rate 0 */
#define UBR10               U0BR1     /* USART 0 Baud Rate 1 */
#define RXBUF0              U0RXBUF   /* USART 0 Receive Buffer */
#define TXBUF0              U0TXBUF   /* USART 0 Transmit Buffer */
#define UCTL0_              U0CTL_    /* USART 0 Control */
#define UTCTL0_             U0TCTL_   /* USART 0 Transmit Control */
#define URCTL0_             U0RCTL_   /* USART 0 Receive Control */
#define UMCTL0_             U0MCTL_   /* USART 0 Modulation Control */
#define UBR00_              U0BR0_    /* USART 0 Baud Rate 0 */
#define UBR10_              U0BR1_    /* USART 0 Baud Rate 1 */
#define RXBUF0_             U0RXBUF_  /* USART 0 Receive Buffer */
#define TXBUF0_             U0TXBUF_  /* USART 0 Transmit Buffer */
#define UCTL_0              U0CTL     /* USART 0 Control */
#define UTCTL_0             U0TCTL    /* USART 0 Transmit Control */
#define URCTL_0             U0RCTL    /* USART 0 Receive Control */
#define UMCTL_0             U0MCTL    /* USART 0 Modulation Control */
#define UBR0_0              U0BR0     /* USART 0 Baud Rate 0 */
#define UBR1_0              U0BR1     /* USART 0 Baud Rate 1 */
#define RXBUF_0             U0RXBUF   /* USART 0 Receive Buffer */
#define TXBUF_0             U0TXBUF   /* USART 0 Transmit Buffer */
#define UCTL_0_             U0CTL_    /* USART 0 Control */
#define UTCTL_0_            U0TCTL_   /* USART 0 Transmit Control */
#define URCTL_0_            U0RCTL_   /* USART 0 Receive Control */
#define UMCTL_0_            U0MCTL_   /* USART 0 Modulation Control */
#define UBR0_0_             U0BR0_    /* USART 0 Baud Rate 0 */
#define UBR1_0_             U0BR1_    /* USART 0 Baud Rate 1 */
#define RXBUF_0_            U0RXBUF_  /* USART 0 Receive Buffer */
#define TXBUF_0_            U0TXBUF_  /* USART 0 Transmit Buffer */

/************************************************************
* Timer A3
************************************************************/
#define __MSP430_HAS_TA3__            /* Definition to show that Module is available */

#define TAIV_               (0x012Eu)  /* Timer A Interrupt Vector Word */
READ_ONLY DEFW( TAIV           , TAIV_)
#define TACTL_              (0x0160u)  /* Timer A Control */
DEFW(   TACTL             , TACTL_)
#define TACCTL0_            (0x0162u)  /* Timer A Capture/Compare Control 0 */
DEFW(   TACCTL0           , TACCTL0_)
#define TACCTL1_            (0x0164u)  /* Timer A Capture/Compare Control 1 */
DEFW(   TACCTL1           , TACCTL1_)
#define TACCTL2_            (0x0166u)  /* Timer A Capture/Compare Control 2 */
DEFW(   TACCTL2           , TACCTL2_)
#define TAR_                (0x0170u)  /* Timer A Counter Register */
DEFW(   TAR               , TAR_)
#define TACCR0_             (0x0172u)  /* Timer A Capture/Compare 0 */
DEFW(   TACCR0            , TACCR0_)
#define TACCR1_             (0x0174u)  /* Timer A Capture/Compare 1 */
DEFW(   TACCR1            , TACCR1_)
#define TACCR2_             (0x0176u)  /* Timer A Capture/Compare 2 */
DEFW(   TACCR2            , TACCR2_)

/* Alternate register names */
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
/* Alternate register names - 5xx style */
#define TA0IV               TAIV      /* Timer A Interrupt Vector Word */
#define TA0CTL              TACTL     /* Timer A Control */
#define TA0CCTL0            TACCTL0   /* Timer A Capture/Compare Control 0 */
#define TA0CCTL1            TACCTL1   /* Timer A Capture/Compare Control 1 */
#define TA0CCTL2            TACCTL2   /* Timer A Capture/Compare Control 2 */
#define TA0R                TAR       /* Timer A Counter Register */
#define TA0CCR0             TACCR0    /* Timer A Capture/Compare 0 */
#define TA0CCR1             TACCR1    /* Timer A Capture/Compare 1 */
#define TA0CCR2             TACCR2    /* Timer A Capture/Compare 2 */
#define TA0IV_              TAIV_     /* Timer A Interrupt Vector Word */
#define TA0CTL_             TACTL_    /* Timer A Control */
#define TA0CCTL0_           TACCTL0_  /* Timer A Capture/Compare Control 0 */
#define TA0CCTL1_           TACCTL1_  /* Timer A Capture/Compare Control 1 */
#define TA0CCTL2_           TACCTL2_  /* Timer A Capture/Compare Control 2 */
#define TA0R_               TAR_      /* Timer A Counter Register */
#define TA0CCR0_            TACCR0_   /* Timer A Capture/Compare 0 */
#define TA0CCR1_            TACCR1_   /* Timer A Capture/Compare 1 */
#define TA0CCR2_            TACCR2_   /* Timer A Capture/Compare 2 */

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

/* TA3IV Definitions */
#define TAIV_NONE           (0x0000u)    /* No Interrupt pending */
#define TAIV_TACCR1         (0x0002u)    /* TACCR1_CCIFG */
#define TAIV_TACCR2         (0x0004u)    /* TACCR2_CCIFG */
#define TAIV_6              (0x0006u)    /* Reserved */
#define TAIV_8              (0x0008u)    /* Reserved */
#define TAIV_TAIFG          (0x000Au)    /* TAIFG */

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
* HARDWARE MULTIPLIER
************************************************************/
#define __MSP430_HAS_MPY__            /* Definition to show that Module is available */

#define MPY_                (0x0130u)  /* Multiply Unsigned/Operand 1 */
DEFW(   MPY               , MPY_)
#define MPYS_               (0x0132u)  /* Multiply Signed/Operand 1 */
DEFW(   MPYS              , MPYS_)
#define MAC_                (0x0134u)  /* Multiply Unsigned and Accumulate/Operand 1 */
DEFW(   MAC               , MAC_)
#define MACS_               (0x0136u)  /* Multiply Signed and Accumulate/Operand 1 */
DEFW(   MACS              , MACS_)
#define OP2_                (0x0138u)  /* Operand 2 */
DEFW(   OP2               , OP2_)
#define RESLO_              (0x013Au)  /* Result Low Word */
DEFW(   RESLO             , RESLO_)
#define RESHI_              (0x013Cu)  /* Result High Word */
DEFW(   RESHI             , RESHI_)
#define SUMEXT_             (0x013Eu)  /* Sum Extend */
READ_ONLY DEFW( SUMEXT         , SUMEXT_)

/************************************************************
* SD16 - Sigma Delta 16 Bit
************************************************************/
#define __MSP430_HAS_SD16_3__         /* Definition to show that Module is available */

#define SD16INCTL0_         (0x00B0u)  /* SD16 Input Control Register Channel 0 */
DEFC(   SD16INCTL0        , SD16INCTL0_)
#define SD16INCTL1_         (0x00B1u)  /* SD16 Input Control Register Channel 1 */
DEFC(   SD16INCTL1        , SD16INCTL1_)
#define SD16INCTL2_         (0x00B2u)  /* SD16 Input Control Register Channel 2 */
DEFC(   SD16INCTL2        , SD16INCTL2_)
#define SD16PRE0_           (0x00B8u)  /* SD16 Preload Register Channel 0 */
DEFC(   SD16PRE0          , SD16PRE0_)
#define SD16PRE1_           (0x00B9u)  /* SD16 Preload Register Channel 1 */
DEFC(   SD16PRE1          , SD16PRE1_)
#define SD16PRE2_           (0x00BAu)  /* SD16 Preload Register Channel 2 */
DEFC(   SD16PRE2          , SD16PRE2_)
#define SD16CONF0_          (0x00B7u)  /* SD16 Internal Configuration Register 0 */
DEFC(   SD16CONF0         , SD16CONF0_)
#define SD16CONF1_          (0x00BFu)  /* SD16 Internal Configuration Register 1 */
DEFC(   SD16CONF1         , SD16CONF1_)
                                      /* Please use only the recommended settings */

#define SD16CTL_            (0x0100u)  /* Sigma Delta ADC 16 Control Register */
DEFW(   SD16CTL           , SD16CTL_)
#define SD16CCTL0_          (0x0102u)  /* SD16 Channel 0 Control Register */
DEFW(   SD16CCTL0         , SD16CCTL0_)
#define SD16CCTL1_          (0x0104u)  /* SD16 Channel 1 Control Register */
DEFW(   SD16CCTL1         , SD16CCTL1_)
#define SD16CCTL2_          (0x0106u)  /* SD16 Channel 2 Control Register */
DEFW(   SD16CCTL2         , SD16CCTL2_)
#define SD16IV_             (0x0110u)  /* SD16 Interrupt Vector Register */
DEFW(   SD16IV            , SD16IV_)
#define SD16MEM0_           (0x0112u)  /* SD16 Channel 0 Conversion Memory */
DEFW(   SD16MEM0          , SD16MEM0_)
#define SD16MEM1_           (0x0114u)  /* SD16 Channel 1 Conversion Memory */
DEFW(   SD16MEM1          , SD16MEM1_)
#define SD16MEM2_           (0x0116u)  /* SD16 Channel 2 Conversion Memory */
DEFW(   SD16MEM2          , SD16MEM2_)

/* SD16INCTLx - AFEINCTLx */
#define SD16INCH0           (0x0001u)  /* SD16 Input Channel select 0 */
#define SD16INCH1           (0x0002u)  /* SD16 Input Channel select 1 */
#define SD16INCH2           (0x0004u)  /* SD16 Input Channel select 2 */
#define SD16GAIN0           (0x0008u)  /* SD16 Input Pre-Amplifier Gain Select 0 */
#define SD16GAIN1           (0x0010u)  /* SD16 Input Pre-Amplifier Gain Select 1 */
#define SD16GAIN2           (0x0020u)  /* SD16 Input Pre-Amplifier Gain Select 2 */
#define SD16INTDLY0         (0x0040u)  /* SD16 Interrupt Delay after 1.Conversion 0 */
#define SD16INTDLY1         (0x0080u)  /* SD16 Interrupt Delay after 1.Conversion 1 */

#define SD16GAIN_1          (0x0000u)  /* SD16 Input Pre-Amplifier Gain Select *1  */
#define SD16GAIN_2          (0x0008u)  /* SD16 Input Pre-Amplifier Gain Select *2  */
#define SD16GAIN_4          (0x0010u)  /* SD16 Input Pre-Amplifier Gain Select *4  */
#define SD16GAIN_8          (0x0018u)  /* SD16 Input Pre-Amplifier Gain Select *8  */
#define SD16GAIN_16         (0x0020u)  /* SD16 Input Pre-Amplifier Gain Select *16 */
#define SD16GAIN_32         (0x0028u)  /* SD16 Input Pre-Amplifier Gain Select *32 */

#define SD16INCH_0          (0x0000u)  /* SD16 Input Channel select input */
#define SD16INCH_1          (0x0001u)  /* SD16 Input Channel select input */
#define SD16INCH_2          (0x0002u)  /* SD16 Input Channel select input */
#define SD16INCH_3          (0x0003u)  /* SD16 Input Channel select input */
#define SD16INCH_4          (0x0004u)  /* SD16 Input Channel select input */
#define SD16INCH_5          (0x0005u)  /* SD16 Input Channel select input */
#define SD16INCH_6          (0x0006u)  /* SD16 Input Channel select Temp */
#define SD16INCH_7          (0x0007u)  /* SD16 Input Channel select Offset */

#define SD16INTDLY_0        (0x0000u)  /* SD16 Interrupt Delay: Int. after 4.Conversion  */
#define SD16INTDLY_1        (0x0040u)  /* SD16 Interrupt Delay: Int. after 3.Conversion  */
#define SD16INTDLY_2        (0x0080u)  /* SD16 Interrupt Delay: Int. after 2.Conversion  */
#define SD16INTDLY_3        (0x00C0u)  /* SD16 Interrupt Delay: Int. after 1.Conversion  */

/* SD16CTL - AFECTL */
#define SD16OVIE            (0x0002u)  /* SD16 Overflow Interupt Enable */
#define SD16REFON           (0x0004u)  /* SD16 Switch internal Reference on */
#define SD16VMIDON          (0x0008u)  /* SD16 Switch Vmid Buffer on */
#define SD16SSEL0           (0x0010u)  /* SD16 Clock Source Select 0 */
#define SD16SSEL1           (0x0020u)  /* SD16 Clock Source Select 1 */
#define SD16DIV0            (0x0040u)  /* SD16 Clock Divider Select 0 */
#define SD16DIV1            (0x0080u)  /* SD16 Clock Divider Select 1 */
#define SD16LP              (0x0100u)  /* SD16 Low Power Mode Enable */

#define SD16DIV_0            (0x0000u)               /* SD16 Clock Divider Select /1 */
#define SD16DIV_1            (SD16DIV0)             /* SD16 Clock Divider Select /2 */
#define SD16DIV_2            (SD16DIV1)             /* SD16 Clock Divider Select /4 */
#define SD16DIV_3            (SD16DIV0+SD16DIV1)    /* SD16 Clock Divider Select /8 */

#define SD16SSEL_0           (0x0000u)               /* SD16 Clock Source Select MCLK  */
#define SD16SSEL_1           (SD16SSEL0)            /* SD16 Clock Source Select SMCLK */
#define SD16SSEL_2           (SD16SSEL1)            /* SD16 Clock Source Select ACLK  */
#define SD16SSEL_3           (SD16SSEL0+SD16SSEL1)  /* SD16 Clock Source Select TACLK */

/* SD16CCTLx - AFECCTLx */
#define SD16GRP             (0x0001u)  /* SD16 Grouping of Channels: 0:Off/1:On */
#define SD16SC              (0x0002u)  /* SD16 Start Conversion */
#define SD16IFG             (0x0004u)  /* SD16 Channel x Interrupt Flag */
#define SD16IE              (0x0008u)  /* SD16 Channel x Interrupt Enable */
#define SD16DF              (0x0010u)  /* SD16 Channel x Data Format: 0:Unipolar/1:Bipolar */
#define SD16OVIFG           (0x0020u)  /* SD16 Channel x Overflow Interrupt Flag */
#define SD16LSBACC          (0x0040u)  /* SD16 Channel x Access LSB of ADC */
#define SD16LSBTOG          (0x0080u)  /* SD16 Channel x Toggle LSB Output of ADC */
#define SD16OSR0            (0x0100u)  /* SD16 Channel x OverSampling Ratio 0 */
#define SD16OSR1            (0x0200u)  /* SD16 Channel x OverSampling Ratio 1 */
#define SD16SNGL            (0x0400u)  /* SD16 Channel x Single Conversion On/Off */

#define SD16OSR_256         (0x0000u)  /* SD16 Channel x OverSampling Ratio 256 */
#define SD16OSR_128         (0x0100u)  /* SD16 Channel x OverSampling Ratio 128 */
#define SD16OSR_64          (0x0200u)  /* SD16 Channel x OverSampling Ratio  64 */
#define SD16OSR_32          (0x0300u)  /* SD16 Channel x OverSampling Ratio  32 */

/* SD16IV Definitions */
#define SD16IV_NONE         (0x0000u)    /* No Interrupt pending */
#define SD16IV_SD16OVIFG    (0x0002u)    /* SD16OVIFG */
#define SD16IV_SD16MEM0     (0x0004u)    /* SD16MEM0 SD16IFG */
#define SD16IV_SD16MEM1     (0x0006u)    /* SD16MEM1 SD16IFG */
#define SD16IV_SD16MEM2     (0x0008u)    /* SD16MEM2 SD16IFG */

/************************************************************
* ESP430E
************************************************************/
#define __MSP430_HAS_ESP430E__         /* Definition to show that Module is available */

#define AFEINCTL0           SD16INCTL0 /* AFE Input Control Register Channel 0 */
#define AFEINCTL1           SD16INCTL1 /* AFE Input Control Register Channel 1 */
#define AFEINCTL2           SD16INCTL2 /* AFE Input Control Register Channel 2 */
#define AFECTL              SD16CTL    /* Analog Front End Control Register */
#define AFECCTL0            SD16CCTL0  /* AFE Channel 0 Control Register */
#define AFECCTL1            SD16CCTL1  /* AFE Channel 1 Control Register */
#define AFECCTL2            SD16CCTL2  /* AFE Channel 2 Control Register */

#define ESPCTL_             (0x0150u)  /* ESP430 Control Register */
DEFW(   ESPCTL            , ESPCTL_)
#define MBCTL_              (0x0152u)  /* Mailbox Control Register */
DEFW(   MBCTL             , MBCTL_)
#define MBIN0_              (0x0154u)  /* Incoming Mailbox 0 Register */
DEFW(   MBIN0             , MBIN0_)
#define MBIN1_              (0x0156u)  /* Incoming Mailbox 1 Register */
DEFW(   MBIN1             , MBIN1_)
#define MBOUT0_             (0x0158u)  /* Outgoing Mailbox 0 Register */
DEFW(   MBOUT0            , MBOUT0_)
#define MBOUT1_             (0x015Au)  /* Outgoing Mailbox 1 Register */
DEFW(   MBOUT1            , MBOUT1_)

#define ESP430_STAT0_       (0x01C0u)  /* ESP430 Return Value 0 */
READ_ONLY DEFW( ESP430_STAT0   , ESP430_STAT0_)
#define ESP430_STAT1_       (0x01C2u)  /* ESP430 Return Value 1 */
READ_ONLY DEFW( ESP430_STAT1   , ESP430_STAT1_)
#define WAVEFSV1_           (0x01C4u)  /* ESP430 Return Value 2 */
READ_ONLY DEFW( WAVEFSV1       , WAVEFSV1_)
#define RET3_               (0x01C6u)  /* ESP430 Return Value 3 */
READ_ONLY DEFW( RET3           , RET3_)
#define RET4_               (0x01C8u)  /* ESP430 Return Value 4 */
READ_ONLY DEFW( RET4           , RET4_)
#define WAVEFSI1_           (0x01CAu)  /* ESP430 Return Value 5 */
READ_ONLY DEFW( WAVEFSI1       , WAVEFSI1_)
#define WAVEFSI2_           (0x01CCu)  /* ESP430 Return Value 6 */
READ_ONLY DEFW( WAVEFSI2       , WAVEFSI2_)
#define RET7_               (0x01CEu)  /* ESP430 Return Value 7 */
READ_ONLY DEFW( RET7           , RET7_)
#define ACTENERGY1_LO_      (0x01D0u)  /* ESP430 Return Value 8 */
READ_ONLY DEFW( ACTENERGY1_LO  , ACTENERGY1_LO_)
#define ACTENERGY1_HI_      (0x01D2u)  /* ESP430 Return Value 9 */
READ_ONLY DEFW( ACTENERGY1_HI  , ACTENERGY1_HI_)
#define ACTENERGY2_LO_      (0x01D4u)  /* ESP430 Return Value 10 */
READ_ONLY DEFW( ACTENERGY2_LO  , ACTENERGY2_LO_)
#define ACTENERGY2_HI_      (0x01D6u)  /* ESP430 Return Value 11 */
READ_ONLY DEFW( ACTENERGY2_HI  , ACTENERGY2_HI_)
#define REACTENERGY_LO_     (0x01D8u)  /* ESP430 Return Value 12 */
READ_ONLY DEFW( REACTENERGY_LO , REACTENERGY_LO_)
#define REACTENERGY_HI_     (0x01DAu)  /* ESP430 Return Value 13 */
READ_ONLY DEFW( REACTENERGY_HI , REACTENERGY_HI_)
#define APPENERGY_LO_       (0x01DCu)  /* ESP430 Return Value 14 */
READ_ONLY DEFW( APPENERGY_LO   , APPENERGY_LO_)
#define APPENERGY_HI_       (0x01DEu)  /* ESP430 Return Value 15 */
READ_ONLY DEFW( APPENERGY_HI   , APPENERGY_HI_)
#define ACTENSPER1_LO_      (0x01E0u)  /* ESP430 Return Value 16 */
READ_ONLY DEFW( ACTENSPER1_LO  , ACTENSPER1_LO_)
#define ACTENSPER1_HI_      (0x01E2u)  /* ESP430 Return Value 17 */
READ_ONLY DEFW( ACTENSPER1_HI  , ACTENSPER1_HI_)
#define ACTENSPER2_LO_      (0x01E4u)  /* ESP430 Return Value 18 */
READ_ONLY DEFW( ACTENSPER2_LO  , ACTENSPER2_LO_)
#define ACTENSPER2_HI_      (0x01E6u)  /* ESP430 Return Value 19 */
READ_ONLY DEFW( ACTENSPER2_HI  , ACTENSPER2_HI_)
#define POWERFCT_           (0x01E8u)  /* ESP430 Return Value 20 */
READ_ONLY DEFW( POWERFCT       , POWERFCT_)
//const sfrw RESERVED         (0x01EA)  /* ESP430 Return Value 21 */
#define MAINSPERIOD_        (0x01ECu)  /* ESP430 Return Value 22 */
READ_ONLY DEFW( MAINSPERIOD    , MAINSPERIOD_)
#define V1RMS_              (0x01EEu)  /* ESP430 Return Value 23 */
READ_ONLY DEFW( V1RMS          , V1RMS_)
#define IRMS_LO_            (0x01F0u)  /* ESP430 Return Value 24 */
READ_ONLY DEFW( IRMS_LO        , IRMS_LO_)
#define IRMS_HI_            (0x01F2u)  /* ESP430 Return Value 25 */
READ_ONLY DEFW( IRMS_HI        , IRMS_HI_)
#define VPEAK_              (0x01F4u)  /* ESP430 Return Value 26 */
READ_ONLY DEFW( VPEAK          , VPEAK_)
#define IPEAK_              (0x01F6u)  /* ESP430 Return Value 27 */
READ_ONLY DEFW( IPEAK          , IPEAK_)
#define LINECYCLCNT_LO_     (0x01F8u)  /* ESP430 Return Value 28 */
READ_ONLY DEFW( LINECYCLCNT_LO , LINECYCLCNT_LO_)
#define LINECYCLCNT_HI_     (0x01FAu)  /* ESP430 Return Value 29 */
READ_ONLY DEFW( LINECYCLCNT_HI , LINECYCLCNT_HI_)
#define NMBMEAS_LO_         (0x01FCu)  /* ESP430 Return Value 30 */
READ_ONLY DEFW( NMBMEAS_LO     , NMBMEAS_LO_)
#define NMBMEAS_HI_         (0x01FEu)  /* ESP430 Return Value 31 */
READ_ONLY DEFW( NMBMEAS_HI     , NMBMEAS_HI_)

#define RET0           ESP430_STAT0   /* STATUS0 of ESP430 */
#define RET1           ESP430_STAT1   /* STATUS1 of ESP430 */
#define RET2           WAVEFSV1       /* Waveform Sample V1 offset corrected*/
#define RET5           WAVEFSI1       /* Waveform Sample I1 offset corrected*/
#define RET6           WAVEFSI2       /* Waveform Sample I2 offset corrected*/
#define RET8           ACTENERGY1_LO  /* Active energy I1 Low Word */
#define RET9           ACTENERGY1_HI  /* Active energy I1 High Word */
#define RET10          ACTENERGY2_LO  /* Active energy I2 Low Word */
#define RET11          ACTENERGY2_HI  /* Active energy I2 High Word*/
#define RET12          REACTENERGY_LO /* Reactive energy Low Word */
#define RET13          REACTENERGY_HI /* Reactive energy High Word */
#define RET14          APPENERGY_LO   /* Apparent energy Low Word */
#define RET15          APPENERGY_HI   /* Apparent energy High Word */
#define RET16          ACTENSPER1_LO  /* Active energy I1 for last mains period Low Word */
#define RET17          ACTENSPER1_HI  /* Active energy I1 for last mains period High Word */
#define RET18          ACTENSPER2_LO  /* Active energy I2 for last mains period Low Word */
#define RET19          ACTENSPER2_HI  /* Active energy I2 for last mains period High Word */
#define RET20          POWERFCT       /* Power factor */
//#define RET21          RESERVED       /* Reserved */
#define RET22          MAINSPERIOD    /* Mains period */
#define RET23          V1RMS          /* Voltage RMS V1 value last second */
#define RET24          IRMS_LO        /* Current RMS value last second I1 I2 Low Word */
#define RET25          IRMS_HI        /* Current RMS value last second I1 I2 High Word */
#define RET26          VPEAK          /* Voltage V1 absolute peak value */
#define RET27          IPEAK          /* Current absolute peak value I1 I2 */
#define RET28          LINECYCLCNT_LO /* Line cycle counter Low Word */
#define RET29          LINECYCLCNT_HI /* Line cycle counter High Word */
#define RET30          NMBMEAS_LO     /* Number of Measurements for CPU signal Low Word */
#define RET31          NMBMEAS_HI     /* Number of Measurements for CPU signal High Word */

/* ESPCTL */
#define ESPEN               (0x0001u)  /* ESP430 Module enable */
#define ESPSUSP             (0x0002u)  /* ESP430 Module suspend */
#define IREQ                (0x0004u)  /* NOT supported by current ESP430 Software */

/* RET0 - Status0 Flags */
#define WFSRDYFG            (0x0001u)  /* New waveform Samples ready Flag */
#define I2GTI1FG            (0x0002u)  /* Current I2 greater then I1 Flag */
#define ILREACHEDFG         (0x0004u)  /* Interrupt level reached Flag */
#define ENRDYFG             (0x0008u)  /* New Energy values ready Flag */
#define ZXLDFG              (0x0010u)  /* Zero Crossing of V1 Flag (leading edge) */
#define ZXTRFG              (0x0020u)  /* Zero Crossing of V1 Flag (trailing edge) */
#define CALRDYFG            (0x0040u)  /* Calibration values ready Flag */
#define TAMPFG              (0x0080u)  /* Tampering Occured Flag */
#define NEGENFG             (0x0100u)  /* Negativ Energy Flag */
#define VDROPFG             (0x0200u)  /* Voltage drop occured Flag */
#define VPEAKFG             (0x0400u)  /* Voltage exceed VPeak level Flag */
#define I1PEAKFG            (0x0800u)  /* Current exceed I1Peak level Flag */
#define I2PEAKFG            (0x1000u)  /* Current exceed I2Peak level Flag */
//#define RESERVED          (0x8000u)  /* Reserved */
//#define RESERVED          (0x8000u)  /* Reserved */
#define ACTIVEFG            (0x8000u)  /* Measurement or Calibration running Flag */

/* RET1 - Status1 Flags */
#define ILNEGFG             (0x0004u)  /* Negative Interrupt level reached Flag */
#define VPEAKNEGFG          (0x0400u)  /* Negative Voltage exceed VPeak level Flag */
#define I1PEAKNEGFG         (0x0800u)  /* Negative Current exceed I1Peak level Flag */
#define I2PEAKNEGFG         (0x1000u)  /* Negative Current exceed I2Peak level Flag */

/* MBCTL */
#define IN0IFG              (0x0001u)  /* Incoming Mail 0 Interrupt Flag */
#define IN1IFG              (0x0002u)  /* Incoming Mail 1 Interrupt Flag */
#define OUT0FG              (0x0004u)  /* Outgoing Mail 0 Flag */
#define OUT1FG              (0x0008u)  /* Outgoing Mail 1 Flag */
#define IN0IE               (0x0010u)  /* Incoming Mail 0 Interrupt Enable */
#define IN1IE               (0x0020u)  /* Incoming Mail 1 Interrupt Enable */
#define CLR0OFF             (0x0040u)  /* Switch off automatic clear of IN0IFG */
#define CLR1OFF             (0x0080u)  /* Switch off automatic clear of IN1IFG */
#define OUT0IFG             (0x0100u)  /* Outgoing Mail 0 Interrupt Flag */
#define OUT1IFG             (0x0200u)  /* Outgoing Mail 1 Interrupt Flag */
#define OUT0IE              (0x0400u)  /* Outgoing Mail 0 Interrupt Enable */
#define OUT1IE              (0x0800u)  /* Outgoing Mail 1 Interrupt Enable */

/* Messages to ESP */
#define mRESET              (0x0001u)  /* Restart ESP430 Software */
#define mSET_MODE           (0x0003u)  /* Set Operation Mode for ESP430 Software */
#define mCLR_EVENT          (0x0005u)  /* Clear Flags for ESP430 Software */
#define mINIT               (0x0007u)  /* Initialize ESP430 Software */
#define mTEMP               (0x0009u)  /* Request Temp. Measurement from ESP430 Software */
#define mSWVERSION          (0x000Bu)  /* Request software version of ESP430 */
#define mREAD_PARAM         (0x000Du)  /* Request to read the parameter with no. “Parameter No.” */
#define mREAD_I2            (0x000Fu)  /* Request to read the I2 Channel (only if not used) */
#define mREAD_I2_CONT       (0x0011u)  /* Request to read the I2 Channel in continues mode (only if not used) */
#define mCMD_SET_RES_SC     (0x0015u)  /* Request to Reset and Set the SD16SC bit at the next zero crossing */

#define mSET_CTRL0          (0x0200u)  /* Set Control Register 0 */
#define mSET_CTRL1          (0x0202u)  /* Set Control Register 1 */
#define mSET_EVENT          (0x0204u)  /* Set which Evenets should cause an message */
#define mSET_PHASECORR1     (0x0206u)  /* Set Phase Correction fo I1 */
#define mSET_PHASECORR2     (0x0208u)  /* Set Phase Correction fo I2 */
#define mSET_V1OFFSET       (0x020Au)  /* Set Offset for V1 */
#define mSET_I1OFFSET       (0x020Cu)  /* Set Offset for I1 */
#define mSET_I2OFFSET       (0x020Eu)  /* Set Offset for I2 */
#define mSET_ADAPTI1        (0x0210u)  /* Set Adaption factor for I1 */
#define mSET_ADAPTI2        (0x0212u)  /* Set Adaption factor for I2 */
#define mSET_GAINCORR1      (0x0214u)  /* Set Gain Correction for Power P1 */
#define mSET_POFFSET1_LO    (0x0216u)  /* Set Power Offset for Power P1 */
#define mSET_POFFSET1_HI    (0x0218u)  /* Set Power Offset for Power P1 */
#define mSET_GAINCORR2      (0x021Au)  /* Set Gain Correction for Power P2 */
#define mSET_POFFSET2_LO    (0x021Cu)  /* Set Power Offset for Power P2 */
#define mSET_POFFSET2_HI    (0x021Eu)  /* Set Power Offset for Power P2 */
#define mSET_INTRPTLEVL_LO  (0x0220u)  /* Set Interrupt Level */
#define mSET_INTRPTLEVL_HI  (0x0222u)  /* Set Interrupt Level */
#define mSET_CALCYCLCNT     (0x0224u)  /* Set number of main cycles for calibration */
#define mSET_STARTCURR_FRAC (0x0226u)  /* Set start current fractional Part*/
#define mSET_STARTCURR_INT  (0x0228u)  /* Set start current integer Part*/
#define mSET_NOMFREQ        (0x022Au)  /* Set nominal main frequency */
#define mSET_VDROPCYCLS     (0x022Cu)  /* Set cylces for VDrop detection */
#define mSET_RATIOTAMP      (0x022Eu)  /* Set ratio for tamper detection */
#define mSET_ITAMP          (0x0230u)  /* Set minimum current for tamper detection */
#define mSET_VDROPLEVEL     (0x0232u)  /* Set level for VDrop detection */
#define mSET_VPEAKLEVEL     (0x0234u)  /* Set level for VPeak detection */
#define mSET_IPEAKLEVEL     (0x0236u)  /* Set level for IPeak detection */
#define mSET_DCREMPER       (0x0238u)  /* Set number of periods for DC-removal */

#define mSET_DELTAV1MAX     (0x023Au)  /* Set max. change of V1 if V1FILTER =1  */
#define mSET_CORRCOMP       (0x023Cu)  /* Set Common Mode Rejection ratio */
#define mSET_FADCU          (0x023Eu)  /* Set ADC sampling frequency fADC */

/* Flags for mSET_CTRL0 */
#define CURR_I2             (0x0001u)  /* 0: No I2 path, only I1 path is used */
                                      /* 1: I2 path implemented (CT, dc-tol CT or shunt) */
#define CURR_I1             (0x0002u)  /* 0: Current transformer, dc-tol CT or shunt */
                                      /* 1: Rogowski coil (not yet implemented) */
#define MB                  (0x0004u)  /* Intrpt to CPU: 0: energy level  1: #measurements */
#define NE0                 (0x0008u)  /* Neg. energy treatment:      00: clear neg. energy */
#define NE1                 (0x0010u)  /* 01: use absolute energy   10: use energy as it is */
#define DCREM_V1            (0x0020u)  /* DC removal for V1:  0: off  1: on */
#define DCREM_I1            (0x0040u)  /* DC removal for I1:  0: off  1: on */
#define DCREM_I2            (0x0080u)  /* DC removal for I2:  0: off  1: on */
#define V1FILTER            (0x0100u)  /* Enable on V1 Spike Filter:  0: off  1: on */
#define I2CMRR              (0x0200u)  /* Enable CMRR for I2:  0: off  1: on */

/* Messages from ESP */
#define mEVENT              (0x0001u)  /* Event Status Flag for ESP430 Software */
#define mTEMPRDY            (0x0003u)  /* Temperature measurement completed and in MBIN1 */
#define mSWRDY              (0x0005u)  /* Software version in MBIN1 */
#define mPARAMRDY           (0x0007u)  /* Parameter requested by mREAD_PARAM returned in MBIN1  */
#define mPARAMSET           (0x0009u)  /* Parameter has been set */
#define mI2RDY              (0x000Bu)  /* I2 value ready */

/* EVENT: Event Message Enable Bits */
#define WFSRDYME            (0x0001u)  /* New waveform Samples ready */
#define I2GTI1ME            (0x0002u)  /* Current I2 greater then I1 */
#define ILREACHEDME         (0x0004u)  /* Interrupt level reached */
#define ENRDYME             (0x0008u)  /* New Energy values ready */
#define ZXLDME              (0x0010u)  /* Zero Crossing of V1 (leading edge) */
#define ZXTRME              (0x0020u)  /* Zero Crossing of V1 (trailing edge) */
#define CALRDYME            (0x0040u)  /* Calibration values ready */
#define TAMPME              (0x0080u)  /* Tampering Occured */
#define NEGENME             (0x0100u)  /* Negativ Energy */
#define VDROPME             (0x0200u)  /* Voltage drop occured */
#define VPEAKME             (0x0400u)  /* Voltage exceed VPeak level */
#define I1PEAKME            (0x0800u)  /* Current exceed I1Peak level */
#define I2PEAKME            (0x1000u)  /* Current exceed I2Peak level */
//#define RESERVED            (0x8000u)  /* Reserved */
//#define RESERVED            (0x8000u)  /* Reserved */
#define ACTIVEME            (0x8000u)  /* Measurement of Calibration running */

/* ESP Modes */
#define modeIDLE            (0x0000u)  /* Set Mode: Idle Mode */
#define modeCALIBRATION     (0x0002u)  /* Set Mode: Calibration Mode */
#define modeMEASURE         (0x0004u)  /* Set Mode: Measure Mode */
#define modeRESET           (0x0006u)  /* Set Mode: Reset and Restart the ESP430 module */
#define modeINIT            (0x0008u)  /* Set Mode: Initialize ESP430 module */

/************************************************************
* Interrupt Vectors (offset from 0xFFE0)
************************************************************/

#define BASICTIMER_VECTOR   (0 * 2u)  /* 0xFFE0 Basic Timer */
#define PORT2_VECTOR        (1 * 2u)  /* 0xFFE2 Port 2 */
#define PORT1_VECTOR        (4 * 2u)  /* 0xFFE8 Port 1 */
#define TIMERA1_VECTOR      (5 * 2u)  /* 0xFFEA Timer A CC1-2, TA */
#define TIMERA0_VECTOR      (6 * 2u)  /* 0xFFEC Timer A CC0 */
#define USART0TX_VECTOR     (8 * 2u)  /* 0xFFF0 USART 0 Transmit */
#define USART0RX_VECTOR     (9 * 2u)  /* 0xFFF2 USART 0 Receive */
#define WDT_VECTOR          (10 * 2u) /* 0xFFF4 Watchdog Timer */

#define SD16_VECTOR         (12 * 2u) /* 0xFFF8 Sigma Delta ADC */
#define ESP430_VECTOR       (13 * 2u) /* 0xFFFA ESP430 Mailbox */

#define NMI_VECTOR          (14 * 2u) /* 0xFFFC Non-maskable */
#define RESET_VECTOR        (15 * 2u) /* 0xFFFE Reset [Highest Priority] */

#define UART0TX_VECTOR      USART0TX_VECTOR
#define UART0RX_VECTOR      USART0RX_VECTOR

/************************************************************
* End of Modules
************************************************************/
#pragma language=default

#endif /* #ifndef __msp430xE42x */

