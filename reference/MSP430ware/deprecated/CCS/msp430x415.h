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
* MSP430x415 and MSP430x417 devices.
*
* Texas Instruments, Version 1.4
*
* Rev. 1.0, -
* Rev. 1.1, Removed unused def of TASSEL2
* Rev. 1.2, Added VLD bits in SVS module
* Rev. 1.3, Removed definitions for BTRESET
* Rev. 1.4, added definitions for Interrupt Vectors xxIV
*
********************************************************************/

#ifndef __msp430x41x
#define __msp430x41x

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
#define WDTIE                  (0x01)
#define OFIE                   (0x02)
#define NMIIE                  (0x10)
#define ACCVIE                 (0x20)

SFR_8BIT(IFG1);                               /* Interrupt Flag 1 */
#define WDTIFG                 (0x01)
#define OFIFG                  (0x02)
#define NMIIFG                 (0x10)

SFR_8BIT(IE2);                                /* Interrupt Enable 2 */
#define BTIE                   (0x80)

SFR_8BIT(IFG2);                               /* Interrupt Flag 2 */
#define BTIFG                  (0x80)

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
* BASIC TIMER
************************************************************/
#define __MSP430_HAS_BT__                     /* Definition to show that Module is available */

SFR_8BIT(BTCTL);                              /* Basic Timer Control */
/* The bit names have been prefixed with "BT" */
#define BTIP0                  (0x01)
#define BTIP1                  (0x02)
#define BTIP2                  (0x04)
#define BTFRFQ0                (0x08)
#define BTFRFQ1                (0x10)
#define BTDIV                  (0x20)         /* fCLK2 = ACLK:256 */
#define BTHOLD                 (0x40)         /* BT1 is held if this bit is set */
#define BTSSEL                 (0x80)         /* fBT = fMCLK (main clock) */

SFR_8BIT(BTCNT1);                             /* Basic Timer Count 1 */
SFR_8BIT(BTCNT2);                             /* Basic Timer Count 2 */

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
/* Frequency of LCD coded with Bits 3-4 */
#define BT_fLCD_DIV32          (0x00)         /* fLCD = fACLK:32 (default) */
#define BT_fLCD_DIV64          (BTFRFQ0)      /* fLCD = fACLK:64 */
#define BT_fLCD_DIV128         (BTFRFQ1)      /* fLCD = fACLK:128 */
#define BT_fLCD_DIV256      (BTFRFQ1+BTFRFQ0)         /* fLCD = fACLK:256 */
/* LCD frequency values with fBT=fACLK */
#define BT_fLCD_1K             (0x00)         /* fACLK:32 (default) */
#define BT_fLCD_512            (BTFRFQ0)      /* fACLK:64 */
#define BT_fLCD_256            (BTFRFQ1)      /* fACLK:128 */
#define BT_fLCD_128         (BTFRFQ1+BTFRFQ0)         /* fACLK:256 */
/* LCD frequency values with fBT=fMCLK */
#define BT_fLCD_31K            (BTSSEL)       /* fMCLK:32 */
#define BT_fLCD_15_5K       (BTSSEL+BTFRFQ0)          /* fMCLK:64 */
#define BT_fLCD_7_8K        (BTSSEL+BTFRFQ1+BTFRFQ0)  /* fMCLK:256 */
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

/* Reset/Hold coded with Bits 6-7 in BT(1)CTL */
/* this is for BT */
//#define BTRESET_CNT1        (BTRESET)           /* BTCNT1 is reset while BTRESET is set */
//#define BTRESET_CNT1_2      (BTRESET+BTDIV)     /* BTCNT1 .AND. BTCNT2 are reset while ~ is set */
/* this is for BT1 */
#define BTHOLD_CNT1            (BTHOLD)       /* BTCNT1 is held while BTHOLD is set */
#define BTHOLD_CNT1_2          (BTHOLD+BTDIV) /* BT1CNT1 .AND. BT1CNT2 are held while ~ is set */

/* INTERRUPT CONTROL BITS */
/* #define BTIE                0x80 */
/* #define BTIFG               0x80 */

/************************************************************
* SYSTEM CLOCK, FLL+ (x41x)
************************************************************/
#define __MSP430_HAS_FLLPLUS_SMALL__                /* Definition to show that Module is available */

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
#define XT1OF                  (0x04)         /* High Frequency Oscillator Fault Flag */
#define OSCCAP0                (0x10)         /* XIN/XOUT Cap 0 */
#define OSCCAP1                (0x20)         /* XIN/XOUT Cap 1 */
#define XTS_FLL                (0x40)         /* 1: Selects high-freq. oscillator */
#define DCOPLUS                (0x80)         /* DCO+ Enable */

#define XCAP0PF                (0x00)         /* XIN Cap = XOUT Cap = 0pf */
#define XCAP10PF               (0x10)         /* XIN Cap = XOUT Cap = 10pf */
#define XCAP14PF               (0x20)         /* XIN Cap = XOUT Cap = 14pf */
#define XCAP18PF               (0x30)         /* XIN Cap = XOUT Cap = 18pf */
#define OSCCAP_0               (0x00)         /* XIN Cap = XOUT Cap = 0pf */
#define OSCCAP_1               (0x10)         /* XIN Cap = XOUT Cap = 10pf */
#define OSCCAP_2               (0x20)         /* XIN Cap = XOUT Cap = 14pf */
#define OSCCAP_3               (0x30)         /* XIN Cap = XOUT Cap = 18pf */

SFR_8BIT(FLL_CTL1);                           /* FLL+ Control 1 */
#define FLL_DIV0               (0x01)         /* FLL+ Divide Px.x/ACLK 0 */
#define FLL_DIV1               (0x02)         /* FLL+ Divide Px.x/ACLK 1 */

#define FLL_DIV_1              (0x00)         /* FLL+ Divide Px.x/ACLK By 1 */
#define FLL_DIV_2              (0x01)         /* FLL+ Divide Px.x/ACLK By 2 */
#define FLL_DIV_4              (0x02)         /* FLL+ Divide Px.x/ACLK By 4 */
#define FLL_DIV_8              (0x03)         /* FLL+ Divide Px.x/ACLK By 8 */

/* INTERRUPT CONTROL BITS */
/* These two bits are defined in the Special Function Registers */
/* #define OFIFG               0x02 */
/* #define OFIE                0x02 */

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
* LCD
************************************************************/
#define __MSP430_HAS_LCD4__                   /* Definition to show that Module is available */

SFR_8BIT(LCDCTL);                             /* LCD Control */
/* the names of the mode bits are different from the spec */
#define LCDON                  (0x01)
//#define LCDLOWR             (0x02)
#define LCDSON                 (0x04)
#define LCDMX0                 (0x08)
#define LCDMX1                 (0x10)
#define LCDP0                  (0x20)
#define LCDP1                  (0x40)
#define LCDP2                  (0x80)
/* Display modes coded with Bits 2-4 */
#define LCDSTATIC              (LCDSON)
#define LCD2MUX                (LCDMX0+LCDSON)
#define LCD3MUX                (LCDMX1+LCDSON)
#define LCD4MUX                (LCDMX1+LCDMX0+LCDSON)
/* Group select code with Bits 5-7                     Seg.lines   Dig.output */
#define LCDSG0                 (0x00)         /* ---------   Port Only (default) */
#define LCDSG0_1               (LCDP0)        /* S0  - S15   see Datasheet */
#define LCDSG0_2               (LCDP1)        /* S0  - S19   see Datasheet */
#define LCDSG0_3               (LCDP1+LCDP0)  /* S0  - S23   see Datasheet */
#define LCDSG0_4               (LCDP2)        /* S0  - S27   see Datasheet */
#define LCDSG0_5               (LCDP2+LCDP0)  /* S0  - S31   see Datasheet */
#define LCDSG0_6               (LCDP2+LCDP1)  /* S0  - S35   see Datasheet */
#define LCDSG0_7            (LCDP2+LCDP1+LCDP0)       /* S0  - S39   see Datasheet */
/* NOTE: YOU CAN ONLY USE THE 'S' OR 'G' DECLARATIONS FOR A COMMAND */
/* MOV  #LCDSG0_3+LCDOG2_7,&LCDCTL ACTUALY MEANS MOV  #LCDP1,&LCDCTL! */
#define LCDOG1_7               (0x00)         /* ---------   Port Only (default) */
#define LCDOG2_7               (LCDP0)        /* S0  - S15   see Datasheet */
#define LCDOG3_7               (LCDP1)        /* S0  - S19   see Datasheet */
#define LCDOG4_7               (LCDP1+LCDP0)  /* S0  - S23   see Datasheet */
#define LCDOG5_7               (LCDP2)        /* S0  - S27   see Datasheet */
#define LCDOG6_7               (LCDP2+LCDP0)  /* S0  - S31   see Datasheet */
#define LCDOG7                 (LCDP2+LCDP1)  /* S0  - S35   see Datasheet */
#define LCDOGOFF            (LCDP2+LCDP1+LCDP0)       /* S0  - S39   see Datasheet */

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

/*************************************************************
* Flash Memory
*************************************************************/
#define __MSP430_HAS_FLASH__                  /* Definition to show that Module is available */

SFR_16BIT(FCTL1);                             /* FLASH Control 1 */
SFR_16BIT(FCTL2);                             /* FLASH Control 2 */
SFR_16BIT(FCTL3);                             /* FLASH Control 3 */

#define FRKEY                  (0x9600)       /* Flash key returned by read */
#define FWKEY                  (0xA500)       /* Flash key for write */
#define FXKEY                  (0x3300)       /* for use with XOR instruction */

#define ERASE                  (0x0002)       /* Enable bit for Flash segment erase */
#define MERAS                  (0x0004)       /* Enable bit for Flash mass erase */
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

/************************************************************
* Comparator A
************************************************************/
#define __MSP430_HAS_COMPA__                  /* Definition to show that Module is available */

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
#define P2CA0                  (0x04)         /* Comp. A Connect External Signal to CA0 : 1 */
#define P2CA1                  (0x08)         /* Comp. A Connect External Signal to CA1 : 1 */
#define CACTL24                (0x10)
#define CACTL25                (0x20)
#define CACTL26                (0x40)
#define CACTL27                (0x80)

#define CAPD0                  (0x01)         /* Comp. A Disable Input Buffer of Port Register .0 */
#define CAPD1                  (0x02)         /* Comp. A Disable Input Buffer of Port Register .1 */
#define CAPD2                  (0x04)         /* Comp. A Disable Input Buffer of Port Register .2 */
#define CAPD3                  (0x08)         /* Comp. A Disable Input Buffer of Port Register .3 */
#define CAPD4                  (0x10)         /* Comp. A Disable Input Buffer of Port Register .4 */
#define CAPD5                  (0x20)         /* Comp. A Disable Input Buffer of Port Register .5 */
#define CAPD6                  (0x40)         /* Comp. A Disable Input Buffer of Port Register .6 */
#define CAPD7                  (0x80)         /* Comp. A Disable Input Buffer of Port Register .7 */

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

#endif /* #ifndef __msp430x41x */

