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
* MSP430x31x devices.
*
* Texas Instruments, Version 2.2
*
* Rev. 1.1, Changed definition of LPM4 bits (device effect not changed)
*           Corrected LPMx_EXIT to reference new intrinsic    _bic_SR_register_on_exit
*           The file contents were reordered
* Rev. 1.2, Enclose all #define statements with parentheses
* Rev. 1.3, Added sfrb for TCDAT and TCPLD
* Rev. 1.4, Removed incorrect label 'BTRESET'
* Rev. 2.1, Alignment of defintions in Users Guide and of version numbers
* Rev. 2.2, Removed definitions for BTRESET
*
********************************************************************/

#ifndef __msp430x31x
#define __msp430x31x

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
#define P0IE_0                 (0x04)
#define P0IE_1                 (0x08)

SFR_8BIT(IFG1);                               /* Interrupt Flag 1 */
#define WDTIFG                 (0x01)
#define OFIFG                  (0x02)
#define P0IFG_0                (0x04)
#define P0IFG_1                (0x08)
#define NMIIFG                 (0x10)

SFR_8BIT(IE2);                                /* Interrupt Enable 2 */
#define TPIE                   (0x04)
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
* DIGITAL I/O PORT0
************************************************************/
#define __MSP430_HAS_PORT0__                  /* Definition to show that Module is available */

SFR_8BIT(P0IN);                               /* Port 0 Input */
#define P0IN_0                 (0x01)
#define P0IN_1                 (0x02)
#define P0IN_2                 (0x04)
#define P0IN_3                 (0x08)
#define P0IN_4                 (0x10)
#define P0IN_5                 (0x20)
#define P0IN_6                 (0x40)
#define P0IN_7                 (0x80)

SFR_8BIT(P0OUT);                              /* Port 0 Output */
#define P0OUT_0                (0x01)
#define P0OUT_1                (0x02)
#define P0OUT_2                (0x04)
#define P0OUT_3                (0x08)
#define P0OUT_4                (0x10)
#define P0OUT_5                (0x20)
#define P0OUT_6                (0x40)
#define P0OUT_7                (0x80)

SFR_8BIT(P0DIR);                              /* Port 0 Direction */
#define P0DIR_0                (0x01)
#define P0DIR_1                (0x02)
#define P0DIR_2                (0x04)
#define P0DIR_3                (0x08)
#define P0DIR_4                (0x10)
#define P0DIR_5                (0x20)
#define P0DIR_6                (0x40)
#define P0DIR_7                (0x80)

SFR_8BIT(P0IFG);                              /* Port 0 Interrupt Flag */
/* These two bits are defined in Interrupt Flag 1 */
/* #define P0IFG_0             0x01 */
/* #define P0IFG_1             0x02 */
#define P0IFG_2                (0x04)
#define P0IFG_3                (0x08)
#define P0IFG_4                (0x10)
#define P0IFG_5                (0x20)
#define P0IFG_6                (0x40)
#define P0IFG_7                (0x80)

SFR_8BIT(P0IES);                              /* Port 0 Interrupt Edge Select */
#define P0IES_0                (0x01)
#define P0IES_1                (0x02)
#define P0IES_2                (0x04)
#define P0IES_3                (0x08)
#define P0IES_4                (0x10)
#define P0IES_5                (0x20)
#define P0IES_6                (0x40)
#define P0IES_7                (0x80)

SFR_8BIT(P0IE);                               /* Port 0 Interrupt Enable */
/* These two bits are defined in Interrupt Enable 1 */
/* #define P0IE_0              0x01 */
/* #define P0IE_1              0x02 */
#define P0IE_2                 (0x04)
#define P0IE_3                 (0x08)
#define P0IE_4                 (0x10)
#define P0IE_5                 (0x20)
#define P0IE_6                 (0x40)
#define P0IE_7                 (0x80)

/************************************************************
* LCD REGISTER
************************************************************/
#define __MSP430_HAS_LCD__                    /* Definition to show that Module is available */

SFR_8BIT(LCDCTL);                             /* LCD Control */
/* the names of the mode bits are different from the spec */
#define LCDON                  (0x01)
#define LCDLOWR                (0x02)
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
#define LCDSG0                 (0x00)         /* S0  - S1    O2  - O29 (default) */
#define LCDSG0_1               (LCDP0)        /* S0  - S5    O6  - O29 */
#define LCDSG0_2               (LCDP1)        /* S0  - S9    O10 - O29 */
#define LCDSG0_3               (LCDP1+LCDP0)  /* S0  - S13   O14 - O29 */
#define LCDSG0_4               (LCDP2)        /* S0  - S17   O18 - O29 */
#define LCDSG0_5               (LCDP2+LCDP0)  /* S0  - S21   O22 - O29 */
#define LCDSG0_6               (LCDP2+LCDP1)  /* S0  - S25   O26 - O29 */
#define LCDSG0_7            (LCDP2+LCDP1+LCDP0)       /* S0  - S29   --------- */
/* NOTE: YOU CAN ONLY USE THE 'S' OR 'G' DECLARATIONS FOR A COMMAND */
/* MOV  #LCDSG0_3+LCDOG2_7,&LCDCTL ACTUALY MEANS MOV  #LCDP1,&LCDCTL! */
#define LCDOG1_7               (0x00)         /* S0  - S1    O2  - O29 (default) */
#define LCDOG2_7               (LCDP0)        /* S0  - S5    O6  - O29 */
#define LCDOG3_7               (LCDP1)        /* S0  - S9    O10 - O29 */
#define LCDOG4_7               (LCDP1+LCDP0)  /* S0  - S13   O14 - O29 */
#define LCDOG5_7               (LCDP2)        /* S0  - S17   O18 - O29 */
#define LCDOG6_7               (LCDP2+LCDP0)  /* S0  - S21   O22 - O29 */
#define LCDOG7                 (LCDP2+LCDP1)  /* S0  - S25   O26 - O29 */
#define LCDOGOFF            (LCDP2+LCDP1+LCDP0)       /* S0  - S29   --------- */

#define LCDMEM_                (0x0031)       /* LCD Memory */
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

#define LCDMA                  (LCDM10)       /* LCD Memory A */
#define LCDMB                  (LCDM11)       /* LCD Memory B */
#define LCDMC                  (LCDM12)       /* LCD Memory C */
#define LCDMD                  (LCDM13)       /* LCD Memory D */
#define LCDME                  (LCDM14)       /* LCD Memory E */
#define LCDMF                  (LCDM15)       /* LCD Memory F */

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
* SYSTEM CLOCK GENERATOR
************************************************************/
#define __MSP430_HAS_FLL__                    /* Definition to show that Module is available */

SFR_8BIT(SCFI0);                              /* System Clock Frequency Integrator 0 */
#define FN_2                   (0x04)
#define FN_3                   (0x08)
#define FN_4                   (0x10)

SFR_8BIT(SCFI1);                              /* System Clock Frequency Integrator 1 */
SFR_8BIT(SCFQCTL);                            /* System Clock Frequency Control */
/* System clock frequency values fMCLK coded with Bits 0-6 in SCFQCTL */
/* #define SCFQ_32K            0x00                        fMCLK=1*fACLK          only a range from */
/* #define SCFQ_64K            0x01                        fMCLK=2*fACLK          3+1 to 127+1 is possible */
#define SCFQ_128K              (0x03)         /* fMCLK=4*fACLK */
#define SCFQ_256K              (0x07)         /* fMCLK=8*fACLK */
#define SCFQ_512K              (0x0F)         /* fMCLK=16*fACLK */
#define SCFQ_1M                (0x1F)         /* fMCLK=32*fACLK */
#define SCFQ_2M                (0x3F)         /* fMCLK=64*fACLK */
#define SCFQ_4M                (0x7F)         /* fMCLK=128*fACLK        not possible for ICE */

SFR_8BIT(CBCTL);                              /* Crystal Buffer Control *** WRITE-ONLY *** */
#define CBE                    (0x01)
#define CBSEL0                 (0x02)
#define CBSEL1                 (0x04)
/* Source select of frequency at output pin XBUF coded with Bits 1-2 in CBCTL */
#define CBSEL_ACLK             (0x00)         /* source is ACLK         (default after POR) */
#define CBSEL_ACLK_DIV2        (CBSEL0)       /* source is ACLK/2 */
#define CBSEL_ACLK_DIV4        (CBSEL1)       /* source is ACLK/4 */
#define CBSEL_MCLK          (CBSEL1+CBSEL0)           /* source is MCLK */

/* INTERRUPT CONTROL BITS */
/* These two bits are defined in the Special Function Registers */
/* #define OFIFG               0x02 */
/* #define OFIE                0x02 */

/************************************************************
* 8BIT TIMER/COUNTER
************************************************************/
#define __MSP430_HAS_8BTC__                   /* Definition to show that Module is available */

SFR_8BIT(TCCTL);                              /* Timer/Counter Control */
/* The bit names have been prefixed with "TC" */
#define TCRXD                  (0x01)
#define TCTXD                  (0x02)
#define TCRXACT                (0x04)
#define TCENCNT                (0x08)
#define TCTXE                  (0x10)
#define TCISCTL                (0x20)
#define TCSSEL0                (0x40)
#define TCSSEL1                (0x80)
/* Source select of clock input coded with Bits 6-7 */
#define TCSSEL_P01             (0x00)         /* source is signal at pin P0.1 (default) */
#define TCSSEL_ACLK            (TCSSEL0)      /* source is ACLK */
#define TCSSEL_MCLK            (TCSSEL1)      /* source is MCLK */
#define TCSSEL_P01_MCLK     (TCSSEL1+TCSSEL0)         /* source is signal pin P0.1 .AND. MCLK */

SFR_8BIT(TCPLD);                              /* Timer/Counter Preload */
SFR_8BIT(TCDAT);                              /* Timer/Counter Data */

/************************************************************
* TIMER/PORT
************************************************************/
#define __MSP430_HAS_TP__                     /* Definition to show that Module is available */

SFR_8BIT(TPCTL);                              /* Timer/Port Control */
#define EN1FG                  (0x01)
#define RC1FG                  (0x02)
#define RC2FG                  (0x04)
#define EN1                    (0x08)
#define ENA                    (0x10)
#define ENB                    (0x20)
#define TPSSEL0                (0x40)
#define TPSSEL1                (0x80)
/* The EN1 signal of TPCNT1 is coded with with Bits 3-5 in TPCTL */
#define TPCNT1_EN_OFF          (0x00)         /* TPCNT1 is disabled */
#define TPCNT1_EN_ON           (ENA)          /*   "    is enabled */
#define TPCNT1_EN_nTPIN5       (ENB)          /*   "    is enabled with ~TPIN.5 */
#define TPCNT1_EN_TPIN5        (TPSSEL0+ENB)  /*   "    is enabled with TPIN.5 */
#define TPCNT1_EN_nCIN         (ENB+ENA)      /*   "    is enabled with ~CIN */
#define TPCNT1_EN_CIN        (TPSSEL0+ENB+ENA)       /*   "    is enabled with CIN */

/* Source select of clock input coded with Bits 6-7 in TPCTL */
#define TPSSEL_CLK1_CIN        (0x00)         /* CLK1 source is signal at CIN   (default) */
#define TPSSEL_CLK1_ACLK       (TPSSEL0)      /* CLK1 source is ACLK */
#define TPSSEL_CLK1_MCLK       (TPSSEL1)      /* CLK1 source is MCLK */

/* DATA REGISTER ADDRESSES */
SFR_8BIT(TPCNT1);                             /* Timer/Port Counter 1 */
SFR_8BIT(TPCNT2);                             /* Timer/Port Counter 2 */

SFR_8BIT(TPD);                                /* Timer/Port Data */
#define TPD_0                  (0x01)
#define TPD_1                  (0x02)
#define TPD_2                  (0x04)
#define TPD_3                  (0x08)
#define TPD_4                  (0x10)
#define TPD_5                  (0x20)
#define CPON                   (0x40)
#define B16                    (0x80)

SFR_8BIT(TPE);                                /* Timer/Port Enable */
#define TPE_0                  (0x01)
#define TPE_1                  (0x02)
#define TPE_2                  (0x04)
#define TPE_3                  (0x08)
#define TPE_4                  (0x10)
#define TPE_5                  (0x20)
#define TPSSEL2                (0x40)
#define TPSSEL3                (0x80)
/* Source select of clock input coded with Bits 6-7 in TPE
   NOTE: If the control bit B16 in TPD is set, TPSSEL2/3
         are 'don't care' and the clock source of counter
         TPCNT2 is the same as of the counter TPCNT1. */
#define TPSSEL_CLK2_TPIN5      (0x00)         /* CLK2 source is signal TPIN.5 (default) */
#define TPSSEL_CLK2_ACLK       (TPSSEL2)      /* CLK2 source is ACLK */
#define TPSSEL_CLK2_MCLK       (TPSSEL3)      /* CLK2 source is MCLK */
#define TPSSEL_CLK2_OFF     (TPSSEL3+TPSSEL2)/* CLK2 source is disabled  */

/************************************************************
* EPROM CONTROL
************************************************************/
#define __MSP430_HAS_EPROM__                  /* Definition to show that Module is available */

SFR_8BIT(EPCTL);                              /* EPROM Control */
#define EPEXE                  (0x01)
#define EPVPPS                 (0x02)

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
#define PORT0_VECTOR            ".int00"                    /* 0xFFE0 Port 0 Bits 2-7 [Lowest Priority] */
#else
#define PORT0_VECTOR            (0 * 1u)                     /* 0xFFE0 Port 0 Bits 2-7 [Lowest Priority] */
/*#define PORT0_ISR(func)         ISR_VECTOR(func, ".int00")  */ /* 0xFFE0 Port 0 Bits 2-7 [Lowest Priority] */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define BASICTIMER_VECTOR       ".int01"                    /* 0xFFE2 Basic Timer */
#else
#define BASICTIMER_VECTOR       (1 * 1u)                     /* 0xFFE2 Basic Timer */
/*#define BASICTIMER_ISR(func)    ISR_VECTOR(func, ".int01")  */ /* 0xFFE2 Basic Timer */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERPORT_VECTOR        ".int05"                    /* 0xFFE8 Timer/Port */
#else
#define TIMERPORT_VECTOR        (5 * 1u)                     /* 0xFFE8 Timer/Port */
/*#define TIMERPORT_ISR(func)     ISR_VECTOR(func, ".int05")  */ /* 0xFFE8 Timer/Port */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define WDT_VECTOR              ".int10"                    /* 0xFFF4 Watchdog Timer */
#else
#define WDT_VECTOR              (10 * 1u)                    /* 0xFFF4 Watchdog Timer */
/*#define WDT_ISR(func)           ISR_VECTOR(func, ".int10")  */ /* 0xFFF4 Watchdog Timer */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define IO1_VECTOR              ".int12"                    /* 0xFFF8 Dedicated IO (P0.1) */
#else
#define IO1_VECTOR              (12 * 1u)                    /* 0xFFF8 Dedicated IO (P0.1) */
/*#define IO1_ISR(func)           ISR_VECTOR(func, ".int12")  */ /* 0xFFF8 Dedicated IO (P0.1) */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define IO0_VECTOR              ".int13"                    /* 0xFFFA Dedicated IO (P0.0) */
#else
#define IO0_VECTOR              (13 * 1u)                    /* 0xFFFA Dedicated IO (P0.0) */
/*#define IO0_ISR(func)           ISR_VECTOR(func, ".int13")  */ /* 0xFFFA Dedicated IO (P0.0) */ /* CCE V2 Style */
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

/************************************************************
* End of Modules
************************************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* #ifndef __msp430x31x */

