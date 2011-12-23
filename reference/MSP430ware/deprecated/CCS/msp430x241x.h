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
* MSP430x241x devices (excluding MSP430x2410).
*
* Texas Instruments, Version 1.4
*
* Rev. 1.0, Initial Version
* Rev. 1.1  added TLV in INFO Memory
* Rev. 1.2, added definitions for Interrupt Vectors xxIV
* Rev. 1.3, added missing Port7/8
* Rev. 1.4, fixed define: TAG_ADC12_1 to 0x08
*
********************************************************************/

#ifndef __msp430x241x
#define __msp430x241x

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
//#define SFR_20BIT(address)  extern volatile unsigned int address
typedef void (* __SFR_FARPTR)();
#define SFR_20BIT(address) extern __SFR_FARPTR address
#define SFR_32BIT(address)  extern volatile unsigned long address



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
* CPU
************************************************************/
#define __MSP430_HAS_MSP430X_CPU__                /* Definition to show that it has MSP430X CPU */

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

SFR_8BIT(IFG2);                               /* Interrupt Flag 2 */
#define UC0IFG                 IFG2
#define UCA0RXIFG              (0x01)
#define UCA0TXIFG              (0x02)
#define UCB0RXIFG              (0x04)
#define UCB0TXIFG              (0x08)

SFR_8BIT(UC1IE);                              /* USCI 1 Interrupt Enable */
#define UCA1RXIE               (0x01)
#define UCA1TXIE               (0x02)
#define UCB1RXIE               (0x04)
#define UCB1TXIE               (0x08)

SFR_8BIT(UC1IFG);                             /* ISCI 1 Interrupt Flags */
#define UCA1RXIFG              (0x01)
#define UCA1TXIFG              (0x02)
#define UCB1RXIFG              (0x04)
#define UCB1TXIFG              (0x08)

/************************************************************
* ADC12
************************************************************/
#define __MSP430_HAS_ADC12__                  /* Definition to show that Module is available */

SFR_16BIT(ADC12CTL0);                         /* ADC12 Control 0 */
SFR_16BIT(ADC12CTL1);                         /* ADC12 Control 1 */
SFR_16BIT(ADC12IFG);                          /* ADC12 Interrupt Flag */
SFR_16BIT(ADC12IE);                           /* ADC12 Interrupt Enable */
SFR_16BIT(ADC12IV);                           /* ADC12 Interrupt Vector Word */

#define ADC12MEM_              (0x0140)       /* ADC12 Conversion Memory */
#ifdef __ASM_HEADER__
#define ADC12MEM               (ADC12MEM_)    /* ADC12 Conversion Memory (for assembler) */
#else
#define ADC12MEM               ((int*)        ADC12MEM_) /* ADC12 Conversion Memory (for C) */
#endif
SFR_16BIT(ADC12MEM0);                         /* ADC12 Conversion Memory 0 */
SFR_16BIT(ADC12MEM1);                         /* ADC12 Conversion Memory 1 */
SFR_16BIT(ADC12MEM2);                         /* ADC12 Conversion Memory 2 */
SFR_16BIT(ADC12MEM3);                         /* ADC12 Conversion Memory 3 */
SFR_16BIT(ADC12MEM4);                         /* ADC12 Conversion Memory 4 */
SFR_16BIT(ADC12MEM5);                         /* ADC12 Conversion Memory 5 */
SFR_16BIT(ADC12MEM6);                         /* ADC12 Conversion Memory 6 */
SFR_16BIT(ADC12MEM7);                         /* ADC12 Conversion Memory 7 */
SFR_16BIT(ADC12MEM8);                         /* ADC12 Conversion Memory 8 */
SFR_16BIT(ADC12MEM9);                         /* ADC12 Conversion Memory 9 */
SFR_16BIT(ADC12MEM10);                        /* ADC12 Conversion Memory 10 */
SFR_16BIT(ADC12MEM11);                        /* ADC12 Conversion Memory 11 */
SFR_16BIT(ADC12MEM12);                        /* ADC12 Conversion Memory 12 */
SFR_16BIT(ADC12MEM13);                        /* ADC12 Conversion Memory 13 */
SFR_16BIT(ADC12MEM14);                        /* ADC12 Conversion Memory 14 */
SFR_16BIT(ADC12MEM15);                        /* ADC12 Conversion Memory 15 */

#define ADC12MCTL_             (0x0080)       /* ADC12 Memory Control */
#ifdef __ASM_HEADER__
#define ADC12MCTL              (ADC12MCTL_)   /* ADC12 Memory Control (for assembler) */
#else
#define ADC12MCTL              ((char*)       ADC12MCTL_) /* ADC12 Memory Control (for C) */
#endif
SFR_8BIT(ADC12MCTL0);                         /* ADC12 Memory Control 0 */
SFR_8BIT(ADC12MCTL1);                         /* ADC12 Memory Control 1 */
SFR_8BIT(ADC12MCTL2);                         /* ADC12 Memory Control 2 */
SFR_8BIT(ADC12MCTL3);                         /* ADC12 Memory Control 3 */
SFR_8BIT(ADC12MCTL4);                         /* ADC12 Memory Control 4 */
SFR_8BIT(ADC12MCTL5);                         /* ADC12 Memory Control 5 */
SFR_8BIT(ADC12MCTL6);                         /* ADC12 Memory Control 6 */
SFR_8BIT(ADC12MCTL7);                         /* ADC12 Memory Control 7 */
SFR_8BIT(ADC12MCTL8);                         /* ADC12 Memory Control 8 */
SFR_8BIT(ADC12MCTL9);                         /* ADC12 Memory Control 9 */
SFR_8BIT(ADC12MCTL10);                        /* ADC12 Memory Control 10 */
SFR_8BIT(ADC12MCTL11);                        /* ADC12 Memory Control 11 */
SFR_8BIT(ADC12MCTL12);                        /* ADC12 Memory Control 12 */
SFR_8BIT(ADC12MCTL13);                        /* ADC12 Memory Control 13 */
SFR_8BIT(ADC12MCTL14);                        /* ADC12 Memory Control 14 */
SFR_8BIT(ADC12MCTL15);                        /* ADC12 Memory Control 15 */

/* ADC12CTL0 */
#define ADC12SC                (0x001)        /* ADC12 Start Conversion */
#define ENC                    (0x002)        /* ADC12 Enable Conversion */
#define ADC12TOVIE             (0x004)        /* ADC12 Timer Overflow interrupt enable */
#define ADC12OVIE              (0x008)        /* ADC12 Overflow interrupt enable */
#define ADC12ON                (0x010)        /* ADC12 On/enable */
#define REFON                  (0x020)        /* ADC12 Reference on */
#define REF2_5V                (0x040)        /* ADC12 Ref 0:1.5V / 1:2.5V */
#define MSC                    (0x080)        /* ADC12 Multiple SampleConversion */
#define SHT00                  (0x0100)       /* ADC12 Sample Hold 0 Select 0 */
#define SHT01                  (0x0200)       /* ADC12 Sample Hold 0 Select 1 */
#define SHT02                  (0x0400)       /* ADC12 Sample Hold 0 Select 2 */
#define SHT03                  (0x0800)       /* ADC12 Sample Hold 0 Select 3 */
#define SHT10                  (0x1000)       /* ADC12 Sample Hold 0 Select 0 */
#define SHT11                  (0x2000)       /* ADC12 Sample Hold 1 Select 1 */
#define SHT12                  (0x4000)       /* ADC12 Sample Hold 2 Select 2 */
#define SHT13                  (0x8000)       /* ADC12 Sample Hold 3 Select 3 */
#define MSH                    (0x080)

#define SHT0_0                 (0*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 0 */
#define SHT0_1                 (1*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 1 */
#define SHT0_2                 (2*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 2 */
#define SHT0_3                 (3*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 3 */
#define SHT0_4                 (4*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 4 */
#define SHT0_5                 (5*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 5 */
#define SHT0_6                 (6*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 6 */
#define SHT0_7                 (7*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 7 */
#define SHT0_8                 (8*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 8 */
#define SHT0_9                 (9*0x100u)     /* ADC12 Sample Hold 0 Select Bit: 9 */
#define SHT0_10                (10*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 10 */
#define SHT0_11                (11*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 11 */
#define SHT0_12                (12*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 12 */
#define SHT0_13                (13*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 13 */
#define SHT0_14                (14*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 14 */
#define SHT0_15                (15*0x100u)    /* ADC12 Sample Hold 0 Select Bit: 15 */

#define SHT1_0                 (0*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 0 */
#define SHT1_1                 (1*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 1 */
#define SHT1_2                 (2*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 2 */
#define SHT1_3                 (3*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 3 */
#define SHT1_4                 (4*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 4 */
#define SHT1_5                 (5*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 5 */
#define SHT1_6                 (6*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 6 */
#define SHT1_7                 (7*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 7 */
#define SHT1_8                 (8*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 8 */
#define SHT1_9                 (9*0x1000u)    /* ADC12 Sample Hold 1 Select Bit: 9 */
#define SHT1_10                (10*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 10 */
#define SHT1_11                (11*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 11 */
#define SHT1_12                (12*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 12 */
#define SHT1_13                (13*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 13 */
#define SHT1_14                (14*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 14 */
#define SHT1_15                (15*0x1000u)   /* ADC12 Sample Hold 1 Select Bit: 15 */

/* ADC12CTL1 */
#define ADC12BUSY              (0x0001)       /* ADC12 Busy */
#define CONSEQ0                (0x0002)       /* ADC12 Conversion Sequence Select 0 */
#define CONSEQ1                (0x0004)       /* ADC12 Conversion Sequence Select 1 */
#define ADC12SSEL0             (0x0008)       /* ADC12 Clock Source Select 0 */
#define ADC12SSEL1             (0x0010)       /* ADC12 Clock Source Select 1 */
#define ADC12DIV0              (0x0020)       /* ADC12 Clock Divider Select 0 */
#define ADC12DIV1              (0x0040)       /* ADC12 Clock Divider Select 1 */
#define ADC12DIV2              (0x0080)       /* ADC12 Clock Divider Select 2 */
#define ISSH                   (0x0100)       /* ADC12 Invert Sample Hold Signal */
#define SHP                    (0x0200)       /* ADC12 Sample/Hold Pulse Mode */
#define SHS0                   (0x0400)       /* ADC12 Sample/Hold Source 0 */
#define SHS1                   (0x0800)       /* ADC12 Sample/Hold Source 1 */
#define CSTARTADD0             (0x1000)       /* ADC12 Conversion Start Address 0 */
#define CSTARTADD1             (0x2000)       /* ADC12 Conversion Start Address 1 */
#define CSTARTADD2             (0x4000)       /* ADC12 Conversion Start Address 2 */
#define CSTARTADD3             (0x8000)       /* ADC12 Conversion Start Address 3 */

#define CONSEQ_0               (0*2u)         /* ADC12 Conversion Sequence Select: 0 */
#define CONSEQ_1               (1*2u)         /* ADC12 Conversion Sequence Select: 1 */
#define CONSEQ_2               (2*2u)         /* ADC12 Conversion Sequence Select: 2 */
#define CONSEQ_3               (3*2u)         /* ADC12 Conversion Sequence Select: 3 */
#define ADC12SSEL_0            (0*8u)         /* ADC12 Clock Source Select: 0 */
#define ADC12SSEL_1            (1*8u)         /* ADC12 Clock Source Select: 1 */
#define ADC12SSEL_2            (2*8u)         /* ADC12 Clock Source Select: 2 */
#define ADC12SSEL_3            (3*8u)         /* ADC12 Clock Source Select: 3 */
#define ADC12DIV_0             (0*0x20u)      /* ADC12 Clock Divider Select: 0 */
#define ADC12DIV_1             (1*0x20u)      /* ADC12 Clock Divider Select: 1 */
#define ADC12DIV_2             (2*0x20u)      /* ADC12 Clock Divider Select: 2 */
#define ADC12DIV_3             (3*0x20u)      /* ADC12 Clock Divider Select: 3 */
#define ADC12DIV_4             (4*0x20u)      /* ADC12 Clock Divider Select: 4 */
#define ADC12DIV_5             (5*0x20u)      /* ADC12 Clock Divider Select: 5 */
#define ADC12DIV_6             (6*0x20u)      /* ADC12 Clock Divider Select: 6 */
#define ADC12DIV_7             (7*0x20u)      /* ADC12 Clock Divider Select: 7 */
#define SHS_0                  (0*0x400u)     /* ADC12 Sample/Hold Source: 0 */
#define SHS_1                  (1*0x400u)     /* ADC12 Sample/Hold Source: 1 */
#define SHS_2                  (2*0x400u)     /* ADC12 Sample/Hold Source: 2 */
#define SHS_3                  (3*0x400u)     /* ADC12 Sample/Hold Source: 3 */
#define CSTARTADD_0            (0*0x1000u)    /* ADC12 Conversion Start Address: 0 */
#define CSTARTADD_1            (1*0x1000u)    /* ADC12 Conversion Start Address: 1 */
#define CSTARTADD_2            (2*0x1000u)    /* ADC12 Conversion Start Address: 2 */
#define CSTARTADD_3            (3*0x1000u)    /* ADC12 Conversion Start Address: 3 */
#define CSTARTADD_4            (4*0x1000u)    /* ADC12 Conversion Start Address: 4 */
#define CSTARTADD_5            (5*0x1000u)    /* ADC12 Conversion Start Address: 5 */
#define CSTARTADD_6            (6*0x1000u)    /* ADC12 Conversion Start Address: 6 */
#define CSTARTADD_7            (7*0x1000u)    /* ADC12 Conversion Start Address: 7 */
#define CSTARTADD_8            (8*0x1000u)    /* ADC12 Conversion Start Address: 8 */
#define CSTARTADD_9            (9*0x1000u)    /* ADC12 Conversion Start Address: 9 */
#define CSTARTADD_10           (10*0x1000u)   /* ADC12 Conversion Start Address: 10 */
#define CSTARTADD_11           (11*0x1000u)   /* ADC12 Conversion Start Address: 11 */
#define CSTARTADD_12           (12*0x1000u)   /* ADC12 Conversion Start Address: 12 */
#define CSTARTADD_13           (13*0x1000u)   /* ADC12 Conversion Start Address: 13 */
#define CSTARTADD_14           (14*0x1000u)   /* ADC12 Conversion Start Address: 14 */
#define CSTARTADD_15           (15*0x1000u)   /* ADC12 Conversion Start Address: 15 */

/* ADC12MCTLx */
#define INCH0                  (0x0001)       /* ADC12 Input Channel Select Bit 0 */
#define INCH1                  (0x0002)       /* ADC12 Input Channel Select Bit 1 */
#define INCH2                  (0x0004)       /* ADC12 Input Channel Select Bit 2 */
#define INCH3                  (0x0008)       /* ADC12 Input Channel Select Bit 3 */
#define SREF0                  (0x0010)       /* ADC12 Select Reference Bit 0 */
#define SREF1                  (0x0020)       /* ADC12 Select Reference Bit 1 */
#define SREF2                  (0x0040)       /* ADC12 Select Reference Bit 2 */
#define EOS                    (0x0080)       /* ADC12 End of Sequence */

#define INCH_0                 (0)            /* ADC12 Input Channel 0 */
#define INCH_1                 (1)            /* ADC12 Input Channel 1 */
#define INCH_2                 (2)            /* ADC12 Input Channel 2 */
#define INCH_3                 (3)            /* ADC12 Input Channel 3 */
#define INCH_4                 (4)            /* ADC12 Input Channel 4 */
#define INCH_5                 (5)            /* ADC12 Input Channel 5 */
#define INCH_6                 (6)            /* ADC12 Input Channel 6 */
#define INCH_7                 (7)            /* ADC12 Input Channel 7 */
#define INCH_8                 (8)            /* ADC12 Input Channel 8 */
#define INCH_9                 (9)            /* ADC12 Input Channel 9 */
#define INCH_10                (10)           /* ADC12 Input Channel 10 */
#define INCH_11                (11)           /* ADC12 Input Channel 11 */
#define INCH_12                (12)           /* ADC12 Input Channel 12 */
#define INCH_13                (13)           /* ADC12 Input Channel 13 */
#define INCH_14                (14)           /* ADC12 Input Channel 14 */
#define INCH_15                (15)           /* ADC12 Input Channel 15 */

#define SREF_0                 (0*0x10u)      /* ADC12 Select Reference 0 */
#define SREF_1                 (1*0x10u)      /* ADC12 Select Reference 1 */
#define SREF_2                 (2*0x10u)      /* ADC12 Select Reference 2 */
#define SREF_3                 (3*0x10u)      /* ADC12 Select Reference 3 */
#define SREF_4                 (4*0x10u)      /* ADC12 Select Reference 4 */
#define SREF_5                 (5*0x10u)      /* ADC12 Select Reference 5 */
#define SREF_6                 (6*0x10u)      /* ADC12 Select Reference 6 */
#define SREF_7                 (7*0x10u)      /* ADC12 Select Reference 7 */

/* ADC12IV Definitions */
#define ADC12IV_NONE           (0x0000)       /* No Interrupt pending */
#define ADC12IV_ADC12OVIFG     (0x0002)       /* ADC12OVIFG */
#define ADC12IV_ADC12TOVIFG    (0x0004)       /* ADC12TOVIFG */
#define ADC12IV_ADC12IFG0      (0x0006)       /* ADC12IFG0 */
#define ADC12IV_ADC12IFG1      (0x0008)       /* ADC12IFG1 */
#define ADC12IV_ADC12IFG2      (0x000A)       /* ADC12IFG2 */
#define ADC12IV_ADC12IFG3      (0x000C)       /* ADC12IFG3 */
#define ADC12IV_ADC12IFG4      (0x000E)       /* ADC12IFG4 */
#define ADC12IV_ADC12IFG5      (0x0010)       /* ADC12IFG5 */
#define ADC12IV_ADC12IFG6      (0x0012)       /* ADC12IFG6 */
#define ADC12IV_ADC12IFG7      (0x0014)       /* ADC12IFG7 */
#define ADC12IV_ADC12IFG8      (0x0016)       /* ADC12IFG8 */
#define ADC12IV_ADC12IFG9      (0x0018)       /* ADC12IFG9 */
#define ADC12IV_ADC12IFG10     (0x001A)       /* ADC12IFG10 */
#define ADC12IV_ADC12IFG11     (0x001C)       /* ADC12IFG11 */
#define ADC12IV_ADC12IFG12     (0x001E)       /* ADC12IFG12 */
#define ADC12IV_ADC12IFG13     (0x0020)       /* ADC12IFG13 */
#define ADC12IV_ADC12IFG14     (0x0022)       /* ADC12IFG14 */
#define ADC12IV_ADC12IFG15     (0x0024)       /* ADC12IFG15 */

/************************************************************
* Basic Clock Module
************************************************************/
#define __MSP430_HAS_BC2__                    /* Definition to show that Module is available */

SFR_8BIT(DCOCTL);                             /* DCO Clock Frequency Control */
SFR_8BIT(BCSCTL1);                            /* Basic Clock System Control 1 */
SFR_8BIT(BCSCTL2);                            /* Basic Clock System Control 2 */
SFR_8BIT(BCSCTL3);                            /* Basic Clock System Control 3 */

#define MOD0                   (0x01)         /* Modulation Bit 0 */
#define MOD1                   (0x02)         /* Modulation Bit 1 */
#define MOD2                   (0x04)         /* Modulation Bit 2 */
#define MOD3                   (0x08)         /* Modulation Bit 3 */
#define MOD4                   (0x10)         /* Modulation Bit 4 */
#define DCO0                   (0x20)         /* DCO Select Bit 0 */
#define DCO1                   (0x40)         /* DCO Select Bit 1 */
#define DCO2                   (0x80)         /* DCO Select Bit 2 */

#define RSEL0                  (0x01)         /* Range Select Bit 0 */
#define RSEL1                  (0x02)         /* Range Select Bit 1 */
#define RSEL2                  (0x04)         /* Range Select Bit 2 */
#define RSEL3                  (0x08)         /* Range Select Bit 3 */
#define DIVA0                  (0x10)         /* ACLK Divider 0 */
#define DIVA1                  (0x20)         /* ACLK Divider 1 */
#define XTS                    (0x40)         /* LFXTCLK 0:Low Freq. / 1: High Freq. */
#define XT2OFF                 (0x80)         /* Enable XT2CLK */

#define DIVA_0                 (0x00)         /* ACLK Divider 0: /1 */
#define DIVA_1                 (0x10)         /* ACLK Divider 1: /2 */
#define DIVA_2                 (0x20)         /* ACLK Divider 2: /4 */
#define DIVA_3                 (0x30)         /* ACLK Divider 3: /8 */

#define DCOR                   (0x01)         /* Enable External Resistor : 1 */
#define DIVS0                  (0x02)         /* SMCLK Divider 0 */
#define DIVS1                  (0x04)         /* SMCLK Divider 1 */
#define SELS                   (0x08)         /* SMCLK Source Select 0:DCOCLK / 1:XT2CLK/LFXTCLK */
#define DIVM0                  (0x10)         /* MCLK Divider 0 */
#define DIVM1                  (0x20)         /* MCLK Divider 1 */
#define SELM0                  (0x40)         /* MCLK Source Select 0 */
#define SELM1                  (0x80)         /* MCLK Source Select 1 */

#define DIVS_0                 (0x00)         /* SMCLK Divider 0: /1 */
#define DIVS_1                 (0x02)         /* SMCLK Divider 1: /2 */
#define DIVS_2                 (0x04)         /* SMCLK Divider 2: /4 */
#define DIVS_3                 (0x06)         /* SMCLK Divider 3: /8 */

#define DIVM_0                 (0x00)         /* MCLK Divider 0: /1 */
#define DIVM_1                 (0x10)         /* MCLK Divider 1: /2 */
#define DIVM_2                 (0x20)         /* MCLK Divider 2: /4 */
#define DIVM_3                 (0x30)         /* MCLK Divider 3: /8 */

#define SELM_0                 (0x00)         /* MCLK Source Select 0: DCOCLK */
#define SELM_1                 (0x40)         /* MCLK Source Select 1: DCOCLK */
#define SELM_2                 (0x80)         /* MCLK Source Select 2: XT2CLK/LFXTCLK */
#define SELM_3                 (0xC0)         /* MCLK Source Select 3: LFXTCLK */

#define LFXT1OF                (0x01)         /* Low/high Frequency Oscillator Fault Flag */
#define XT2OF                  (0x02)         /* High frequency oscillator 2 fault flag */
#define XCAP0                  (0x04)         /* XIN/XOUT Cap 0 */
#define XCAP1                  (0x08)         /* XIN/XOUT Cap 1 */
#define LFXT1S0                (0x10)         /* Mode 0 for LFXT1 (XTS = 0) */
#define LFXT1S1                (0x20)         /* Mode 1 for LFXT1 (XTS = 0) */
#define XT2S0                  (0x40)         /* Mode 0 for XT2 */
#define XT2S1                  (0x80)         /* Mode 1 for XT2 */

#define XCAP_0                 (0x00)         /* XIN/XOUT Cap : 0 pF */
#define XCAP_1                 (0x04)         /* XIN/XOUT Cap : 6 pF */
#define XCAP_2                 (0x08)         /* XIN/XOUT Cap : 10 pF */
#define XCAP_3                 (0x0C)         /* XIN/XOUT Cap : 12.5 pF */

#define LFXT1S_0               (0x00)         /* Mode 0 for LFXT1 : Normal operation */
#define LFXT1S_1               (0x10)         /* Mode 1 for LFXT1 : Reserved */
#define LFXT1S_2               (0x20)         /* Mode 2 for LFXT1 : VLO */
#define LFXT1S_3               (0x30)         /* Mode 3 for LFXT1 : Digital input signal */

#define XT2S_0                 (0x00)         /* Mode 0 for XT2 : 0.4 - 1 MHz */
#define XT2S_1                 (0x40)         /* Mode 1 for XT2 : 1 - 4 MHz */
#define XT2S_2                 (0x80)         /* Mode 2 for XT2 : 2 - 16 MHz */
#define XT2S_3                 (0xC0)         /* Mode 3 for XT2 : Digital input signal */

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
SFR_16BIT(FCTL4);                             /* FLASH Control 4 */

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

#define MGR0                   (0x0010)       /* Marginal read 0 mode. */
#define MGR1                   (0x0020)       /* Marginal read 1 mode. */

/************************************************************
* HARDWARE MULTIPLIER
************************************************************/
#define __MSP430_HAS_MPY__                    /* Definition to show that Module is available */

SFR_16BIT(MPY);                               /* Multiply Unsigned/Operand 1 */
SFR_16BIT(MPYS);                              /* Multiply Signed/Operand 1 */
SFR_16BIT(MAC);                               /* Multiply Unsigned and Accumulate/Operand 1 */
SFR_16BIT(MACS);                              /* Multiply Signed and Accumulate/Operand 1 */
SFR_16BIT(OP2);                               /* Operand 2 */
SFR_16BIT(RESLO);                             /* Result Low Word */
SFR_16BIT(RESHI);                             /* Result High Word */
SFR_16BIT(SUMEXT);                            /* Sum Extend */

/************************************************************
* DIGITAL I/O Port1/2 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT1_R__                /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2_R__                /* Definition to show that Module is available */

SFR_8BIT(P1IN);                               /* Port 1 Input */
SFR_8BIT(P1OUT);                              /* Port 1 Output */
SFR_8BIT(P1DIR);                              /* Port 1 Direction */
SFR_8BIT(P1IFG);                              /* Port 1 Interrupt Flag */
SFR_8BIT(P1IES);                              /* Port 1 Interrupt Edge Select */
SFR_8BIT(P1IE);                               /* Port 1 Interrupt Enable */
SFR_8BIT(P1SEL);                              /* Port 1 Selection */
SFR_8BIT(P1REN);                              /* Port 1 Resistor Enable */

SFR_8BIT(P2IN);                               /* Port 2 Input */
SFR_8BIT(P2OUT);                              /* Port 2 Output */
SFR_8BIT(P2DIR);                              /* Port 2 Direction */
SFR_8BIT(P2IFG);                              /* Port 2 Interrupt Flag */
SFR_8BIT(P2IES);                              /* Port 2 Interrupt Edge Select */
SFR_8BIT(P2IE);                               /* Port 2 Interrupt Enable */
SFR_8BIT(P2SEL);                              /* Port 2 Selection */
SFR_8BIT(P2REN);                              /* Port 2 Resistor Enable */

/************************************************************
* DIGITAL I/O Port3/4 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT3_R__                /* Definition to show that Module is available */
#define __MSP430_HAS_PORT4_R__                /* Definition to show that Module is available */

SFR_8BIT(P3IN);                               /* Port 3 Input */
SFR_8BIT(P3OUT);                              /* Port 3 Output */
SFR_8BIT(P3DIR);                              /* Port 3 Direction */
SFR_8BIT(P3SEL);                              /* Port 3 Selection */
SFR_8BIT(P3REN);                              /* Port 3 Resistor Enable */

SFR_8BIT(P4IN);                               /* Port 4 Input */
SFR_8BIT(P4OUT);                              /* Port 4 Output */
SFR_8BIT(P4DIR);                              /* Port 4 Direction */
SFR_8BIT(P4SEL);                              /* Port 4 Selection */
SFR_8BIT(P4REN);                              /* Port 4 Resistor Enable */

/************************************************************
* DIGITAL I/O Port5/6 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT5_R__                /* Definition to show that Module is available */
#define __MSP430_HAS_PORT6_R__                /* Definition to show that Module is available */

SFR_8BIT(P5IN);                               /* Port 5 Input */
SFR_8BIT(P5OUT);                              /* Port 5 Output */
SFR_8BIT(P5DIR);                              /* Port 5 Direction */
SFR_8BIT(P5SEL);                              /* Port 5 Selection */
SFR_8BIT(P5REN);                              /* Port 5 Resistor Enable */

SFR_8BIT(P6IN);                               /* Port 6 Input */
SFR_8BIT(P6OUT);                              /* Port 6 Output */
SFR_8BIT(P6DIR);                              /* Port 6 Direction */
SFR_8BIT(P6SEL);                              /* Port 6 Selection */
SFR_8BIT(P6REN);                              /* Port 6 Resistor Enable */

/************************************************************
* DIGITAL I/O Port7/8 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT7_R__                /* Definition to show that Module is available */
#define __MSP430_HAS_PORT8_R__                /* Definition to show that Module is available */
#define __MSP430_HAS_PORTA_R__                /* Definition to show that Module is available */

SFR_8BIT(P7IN);                               /* Port 7 Input */
SFR_8BIT(P7OUT);                              /* Port 7 Output */
SFR_8BIT(P7DIR);                              /* Port 7 Direction */
SFR_8BIT(P7SEL);                              /* Port 7 Selection */
SFR_8BIT(P7REN);                              /* Port 7 Resistor Enable */

SFR_8BIT(P8IN);                               /* Port 8 Input */
SFR_8BIT(P8OUT);                              /* Port 8 Output */
SFR_8BIT(P8DIR);                              /* Port 8 Direction */
SFR_8BIT(P8SEL);                              /* Port 8 Selection */
SFR_8BIT(P8REN);                              /* Port 8 Resistor Enable */

SFR_16BIT(PAIN);                              /* Port A Input */
SFR_16BIT(PAOUT);                             /* Port A Output */
SFR_16BIT(PADIR);                             /* Port A Direction */
SFR_16BIT(PASEL);                             /* Port A Selection */
SFR_16BIT(PAREN);                             /* Port A Resistor Enable */

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
* Timer A3
************************************************************/
#define __MSP430_HAS_TA3__                    /* Definition to show that Module is available */

SFR_16BIT(TAIV);                              /* Timer A Interrupt Vector Word */
SFR_16BIT(TACTL);                             /* Timer A Control */
SFR_16BIT(TACCTL0);                           /* Timer A Capture/Compare Control 0 */
SFR_16BIT(TACCTL1);                           /* Timer A Capture/Compare Control 1 */
SFR_16BIT(TACCTL2);                           /* Timer A Capture/Compare Control 2 */
SFR_16BIT(TAR);                               /* Timer A Counter Register */
SFR_16BIT(TACCR0);                            /* Timer A Capture/Compare 0 */
SFR_16BIT(TACCR1);                            /* Timer A Capture/Compare 1 */
SFR_16BIT(TACCR2);                            /* Timer A Capture/Compare 2 */

/* Alternate register names */
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
/* Alternate register names - 5xx style */
#define TA0IV                  TAIV           /* Timer A Interrupt Vector Word */
#define TA0CTL                 TACTL          /* Timer A Control */
#define TA0CCTL0               TACCTL0        /* Timer A Capture/Compare Control 0 */
#define TA0CCTL1               TACCTL1        /* Timer A Capture/Compare Control 1 */
#define TA0CCTL2               TACCTL2        /* Timer A Capture/Compare Control 2 */
#define TA0R                   TAR            /* Timer A Counter Register */
#define TA0CCR0                TACCR0         /* Timer A Capture/Compare 0 */
#define TA0CCR1                TACCR1         /* Timer A Capture/Compare 1 */
#define TA0CCR2                TACCR2         /* Timer A Capture/Compare 2 */
#define TA0IV_                 TAIV_          /* Timer A Interrupt Vector Word */
#define TA0CTL_                TACTL_         /* Timer A Control */
#define TA0CCTL0_              TACCTL0_       /* Timer A Capture/Compare Control 0 */
#define TA0CCTL1_              TACCTL1_       /* Timer A Capture/Compare Control 1 */
#define TA0CCTL2_              TACCTL2_       /* Timer A Capture/Compare Control 2 */
#define TA0R_                  TAR_           /* Timer A Counter Register */
#define TA0CCR0_               TACCR0_        /* Timer A Capture/Compare 0 */
#define TA0CCR1_               TACCR1_        /* Timer A Capture/Compare 1 */
#define TA0CCR2_               TACCR2_        /* Timer A Capture/Compare 2 */

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

/* TA3IV Definitions */
#define TAIV_NONE              (0x0000)       /* No Interrupt pending */
#define TAIV_TACCR1            (0x0002)       /* TACCR1_CCIFG */
#define TAIV_TACCR2            (0x0004)       /* TACCR2_CCIFG */
#define TAIV_6                 (0x0006)       /* Reserved */
#define TAIV_8                 (0x0008)       /* Reserved */
#define TAIV_TAIFG             (0x000A)       /* TAIFG */

/************************************************************
* Timer B7
************************************************************/
#define __MSP430_HAS_TB7__                    /* Definition to show that Module is available */

SFR_16BIT(TBIV);                              /* Timer B Interrupt Vector Word */
SFR_16BIT(TBCTL);                             /* Timer B Control */
SFR_16BIT(TBCCTL0);                           /* Timer B Capture/Compare Control 0 */
SFR_16BIT(TBCCTL1);                           /* Timer B Capture/Compare Control 1 */
SFR_16BIT(TBCCTL2);                           /* Timer B Capture/Compare Control 2 */
SFR_16BIT(TBCCTL3);                           /* Timer B Capture/Compare Control 3 */
SFR_16BIT(TBCCTL4);                           /* Timer B Capture/Compare Control 4 */
SFR_16BIT(TBCCTL5);                           /* Timer B Capture/Compare Control 5 */
SFR_16BIT(TBCCTL6);                           /* Timer B Capture/Compare Control 6 */
SFR_16BIT(TBR);                               /* Timer B Counter Register */
SFR_16BIT(TBCCR0);                            /* Timer B Capture/Compare 0 */
SFR_16BIT(TBCCR1);                            /* Timer B Capture/Compare 1 */
SFR_16BIT(TBCCR2);                            /* Timer B Capture/Compare 2 */
SFR_16BIT(TBCCR3);                            /* Timer B Capture/Compare 3 */
SFR_16BIT(TBCCR4);                            /* Timer B Capture/Compare 4 */
SFR_16BIT(TBCCR5);                            /* Timer B Capture/Compare 5 */
SFR_16BIT(TBCCR6);                            /* Timer B Capture/Compare 6 */

/* Alternate register names - 5xx style */
#define TB0IV                  TBIV           /* Timer B Interrupt Vector Word */
#define TB0CTL                 TBCTL          /* Timer B Control */
#define TB0CCTL0               TBCCTL0        /* Timer B Capture/Compare Control 0 */
#define TB0CCTL1               TBCCTL1        /* Timer B Capture/Compare Control 1 */
#define TB0CCTL2               TBCCTL2        /* Timer B Capture/Compare Control 2 */
#define TB0CCTL3               TBCCTL3        /* Timer B Capture/Compare Control 3 */
#define TB0CCTL4               TBCCTL4        /* Timer B Capture/Compare Control 4 */
#define TB0CCTL5               TBCCTL5        /* Timer B Capture/Compare Control 5 */
#define TB0CCTL6               TBCCTL6        /* Timer B Capture/Compare Control 6 */
#define TB0R                   TBR            /* Timer B Counter Register */
#define TB0CCR0                TBCCR0         /* Timer B Capture/Compare 0 */
#define TB0CCR1                TBCCR1         /* Timer B Capture/Compare 1 */
#define TB0CCR2                TBCCR2         /* Timer B Capture/Compare 2 */
#define TB0CCR3                TBCCR3         /* Timer B Capture/Compare 3 */
#define TB0CCR4                TBCCR4         /* Timer B Capture/Compare 4 */
#define TB0CCR5                TBCCR5         /* Timer B Capture/Compare 5 */
#define TB0CCR6                TBCCR6         /* Timer B Capture/Compare 6 */
#define TB0IV_                 TBIV_          /* Timer B Interrupt Vector Word */
#define TB0CTL_                TBCTL_         /* Timer B Control */
#define TB0CCTL0_              TBCCTL0_       /* Timer B Capture/Compare Control 0 */
#define TB0CCTL1_              TBCCTL1_       /* Timer B Capture/Compare Control 1 */
#define TB0CCTL2_              TBCCTL2_       /* Timer B Capture/Compare Control 2 */
#define TB0CCTL3_              TBCCTL3_       /* Timer B Capture/Compare Control 3 */
#define TB0CCTL4_              TBCCTL4_       /* Timer B Capture/Compare Control 4 */
#define TB0CCTL5_              TBCCTL5_       /* Timer B Capture/Compare Control 5 */
#define TB0CCTL6_              TBCCTL6_       /* Timer B Capture/Compare Control 6 */
#define TB0R_                  TBR_           /* Timer B Counter Register */
#define TB0CCR0_               TBCCR0_        /* Timer B Capture/Compare 0 */
#define TB0CCR1_               TBCCR1_        /* Timer B Capture/Compare 1 */
#define TB0CCR2_               TBCCR2_        /* Timer B Capture/Compare 2 */
#define TB0CCR3_               TBCCR3_        /* Timer B Capture/Compare 3 */
#define TB0CCR4_               TBCCR4_        /* Timer B Capture/Compare 4 */
#define TB0CCR5_               TBCCR5_        /* Timer B Capture/Compare 5 */
#define TB0CCR6_               TBCCR6_        /* Timer B Capture/Compare 6 */

#define TBCLGRP1               (0x4000)       /* Timer B Compare latch load group 1 */
#define TBCLGRP0               (0x2000)       /* Timer B Compare latch load group 0 */
#define CNTL1                  (0x1000)       /* Counter lenght 1 */
#define CNTL0                  (0x0800)       /* Counter lenght 0 */
#define TBSSEL1                (0x0200)       /* Clock source 1 */
#define TBSSEL0                (0x0100)       /* Clock source 0 */
#define TBCLR                  (0x0004)       /* Timer B counter clear */
#define TBIE                   (0x0002)       /* Timer B interrupt enable */
#define TBIFG                  (0x0001)       /* Timer B interrupt flag */

#define SHR1                   (0x4000)       /* Timer B Compare latch load group 1 */
#define SHR0                   (0x2000)       /* Timer B Compare latch load group 0 */

#define TBSSEL_0               (0*0x0100u)    /* Clock Source: TBCLK */
#define TBSSEL_1               (1*0x0100u)    /* Clock Source: ACLK  */
#define TBSSEL_2               (2*0x0100u)    /* Clock Source: SMCLK */
#define TBSSEL_3               (3*0x0100u)    /* Clock Source: INCLK */
#define CNTL_0                 (0*0x0800u)    /* Counter lenght: 16 bit */
#define CNTL_1                 (1*0x0800u)    /* Counter lenght: 12 bit */
#define CNTL_2                 (2*0x0800u)    /* Counter lenght: 10 bit */
#define CNTL_3                 (3*0x0800u)    /* Counter lenght:  8 bit */
#define SHR_0                  (0*0x2000u)    /* Timer B Group: 0 - individually */
#define SHR_1                  (1*0x2000u)    /* Timer B Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define SHR_2                  (2*0x2000u)    /* Timer B Group: 2 - 2 groups (1-3, 4-6)*/
#define SHR_3                  (3*0x2000u)    /* Timer B Group: 3 - 1 group (all) */
#define TBCLGRP_0              (0*0x2000u)    /* Timer B Group: 0 - individually */
#define TBCLGRP_1              (1*0x2000u)    /* Timer B Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define TBCLGRP_2              (2*0x2000u)    /* Timer B Group: 2 - 2 groups (1-3, 4-6)*/
#define TBCLGRP_3              (3*0x2000u)    /* Timer B Group: 3 - 1 group (all) */

/* Additional Timer B Control Register bits are defined in Timer A */
#define CLLD1                  (0x0400)       /* Compare latch load source 1 */
#define CLLD0                  (0x0200)       /* Compare latch load source 0 */

#define SLSHR1                 (0x0400)       /* Compare latch load source 1 */
#define SLSHR0                 (0x0200)       /* Compare latch load source 0 */

#define SLSHR_0                (0*0x0200u)    /* Compare latch load sourec : 0 - immediate */
#define SLSHR_1                (1*0x0200u)    /* Compare latch load sourec : 1 - TBR counts to 0 */
#define SLSHR_2                (2*0x0200u)    /* Compare latch load sourec : 2 - up/down */
#define SLSHR_3                (3*0x0200u)    /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

#define CLLD_0                 (0*0x0200u)    /* Compare latch load sourec : 0 - immediate */
#define CLLD_1                 (1*0x0200u)    /* Compare latch load sourec : 1 - TBR counts to 0 */
#define CLLD_2                 (2*0x0200u)    /* Compare latch load sourec : 2 - up/down */
#define CLLD_3                 (3*0x0200u)    /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

/* TB7IV Definitions */
#define TBIV_NONE              (0x0000)       /* No Interrupt pending */
#define TBIV_TBCCR1            (0x0002)       /* TBCCR1_CCIFG */
#define TBIV_TBCCR2            (0x0004)       /* TBCCR2_CCIFG */
#define TBIV_TBCCR3            (0x0006)       /* TBCCR3_CCIFG */
#define TBIV_TBCCR4            (0x0008)       /* TBCCR4_CCIFG */
#define TBIV_TBCCR5            (0x000A)       /* TBCCR3_CCIFG */
#define TBIV_TBCCR6            (0x000C)       /* TBCCR4_CCIFG */
#define TBIV_TBIFG             (0x000E)       /* TBIFG */

/************************************************************
* USCI
************************************************************/
#define __MSP430_HAS_USCI__                   /* Definition to show that Module is available */
#define __MSP430_HAS_USCI_AB0__                /* Definition to show that Module is available */
#define __MSP430_HAS_USCI_AB1__                /* Definition to show that Module is available */

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

SFR_8BIT(UCA1CTL0);                           /* USCI A1 Control Register 0 */
SFR_8BIT(UCA1CTL1);                           /* USCI A1 Control Register 1 */
SFR_8BIT(UCA1BR0);                            /* USCI A1 Baud Rate 0 */
SFR_8BIT(UCA1BR1);                            /* USCI A1 Baud Rate 1 */
SFR_8BIT(UCA1MCTL);                           /* USCI A1 Modulation Control */
SFR_8BIT(UCA1STAT);                           /* USCI A1 Status Register */
SFR_8BIT(UCA1RXBUF);                          /* USCI A1 Receive Buffer */
SFR_8BIT(UCA1TXBUF);                          /* USCI A1 Transmit Buffer */
SFR_8BIT(UCA1ABCTL);                          /* USCI A1 LIN Control */
SFR_8BIT(UCA1IRTCTL);                         /* USCI A1 IrDA Transmit Control */
SFR_8BIT(UCA1IRRCTL);                         /* USCI A1 IrDA Receive Control */



SFR_8BIT(UCB1CTL0);                           /* USCI B1 Control Register 0 */
SFR_8BIT(UCB1CTL1);                           /* USCI B1 Control Register 1 */
SFR_8BIT(UCB1BR0);                            /* USCI B1 Baud Rate 0 */
SFR_8BIT(UCB1BR1);                            /* USCI B1 Baud Rate 1 */
SFR_8BIT(UCB1I2CIE);                          /* USCI B1 I2C Interrupt Enable Register */
SFR_8BIT(UCB1STAT);                           /* USCI B1 Status Register */
SFR_8BIT(UCB1RXBUF);                          /* USCI B1 Receive Buffer */
SFR_8BIT(UCB1TXBUF);                          /* USCI B1 Transmit Buffer */
SFR_16BIT(UCB1I2COA);                         /* USCI B1 I2C Own Address */
SFR_16BIT(UCB1I2CSA);                         /* USCI B1 I2C Slave Address */

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
* Calibration Data in Info Mem
************************************************************/

/* TLV Calibration Data Structure */
#define TAG_DCO_30             (0x01)         /* Tag for DCO30  Calibration Data */
#define TAG_ADC12_1            (0x08)         /* Tag for ADC12_1 Calibration Data */
#define TAG_EMPTY              (0xFE)         /* Tag for Empty Data Field in Calibration Data */

#ifndef __DisableCalData
SFR_16BIT(TLV_CHECKSUM);                      /* TLV CHECK SUM */
SFR_8BIT(TLV_DCO_30_TAG);                     /* TLV TAG_DCO30 TAG */
SFR_8BIT(TLV_DCO_30_LEN);                     /* TLV TAG_DCO30 LEN */
SFR_8BIT(TLV_ADC12_1_TAG);                    /* TLV ADC12_1 TAG */
SFR_8BIT(TLV_ADC12_1_LEN);                    /* TLV ADC12_1 LEN */
#endif

#define CAL_ADC_25T85          (0x0007)       /* Index for 2.5V/85Deg Cal. Value */
#define CAL_ADC_25T30          (0x0006)       /* Index for 2.5V/30Deg Cal. Value */
#define CAL_ADC_25VREF_FACTOR  (0x0005)       /* Index for 2.5V Ref. Factor */
#define CAL_ADC_15T85          (0x0004)       /* Index for 1.5V/85Deg Cal. Value */
#define CAL_ADC_15T30          (0x0003)       /* Index for 1.5V/30Deg Cal. Value */
#define CAL_ADC_15VREF_FACTOR  (0x0002)       /* Index for ADC 1.5V Ref. Factor */
#define CAL_ADC_OFFSET         (0x0001)       /* Index for ADC Offset */
#define CAL_ADC_GAIN_FACTOR    (0x0000)       /* Index for ADC Gain Factor */

#define CAL_DCO_16MHZ          (0x0000)       /* Index for DCOCTL  Calibration Data for 16MHz */
#define CAL_BC1_16MHZ          (0x0001)       /* Index for BCSCTL1 Calibration Data for 16MHz */
#define CAL_DCO_12MHZ          (0x0002)       /* Index for DCOCTL  Calibration Data for 12MHz */
#define CAL_BC1_12MHZ          (0x0003)       /* Index for BCSCTL1 Calibration Data for 12MHz */
#define CAL_DCO_8MHZ           (0x0004)       /* Index for DCOCTL  Calibration Data for 8MHz */
#define CAL_BC1_8MHZ           (0x0005)       /* Index for BCSCTL1 Calibration Data for 8MHz */
#define CAL_DCO_1MHZ           (0x0006)       /* Index for DCOCTL  Calibration Data for 1MHz */
#define CAL_BC1_1MHZ           (0x0007)       /* Index for BCSCTL1 Calibration Data for 1MHz */


/************************************************************
* Calibration Data in Info Mem
************************************************************/

#ifndef __DisableCalData

SFR_8BIT(CALDCO_16MHZ);                       /* DCOCTL  Calibration Data for 16MHz */
SFR_8BIT(CALBC1_16MHZ);                       /* BCSCTL1 Calibration Data for 16MHz */
SFR_8BIT(CALDCO_12MHZ);                       /* DCOCTL  Calibration Data for 12MHz */
SFR_8BIT(CALBC1_12MHZ);                       /* BCSCTL1 Calibration Data for 12MHz */
SFR_8BIT(CALDCO_8MHZ);                        /* DCOCTL  Calibration Data for 8MHz */
SFR_8BIT(CALBC1_8MHZ);                        /* BCSCTL1 Calibration Data for 8MHz */
SFR_8BIT(CALDCO_1MHZ);                        /* DCOCTL  Calibration Data for 1MHz */
SFR_8BIT(CALBC1_1MHZ);                        /* BCSCTL1 Calibration Data for 1MHz */

#endif /* #ifndef __DisableCalData */

/************************************************************
* Interrupt Vectors (offset from 0xFFC0)
************************************************************/

#pragma diag_suppress 1107
#define VECTOR_NAME(name)             name##_ptr
#define EMIT_PRAGMA(x)                _Pragma(#x)
#define CREATE_VECTOR(name)           void * const VECTOR_NAME(name) = (void *)(long)&name
#define PLACE_VECTOR(vector,section)  EMIT_PRAGMA(DATA_SECTION(vector,section))
#define PLACE_INTERRUPT(func)         EMIT_PRAGMA(CODE_SECTION(func,".text:_isr"))
#define ISR_VECTOR(func,offset)       CREATE_VECTOR(func); \
                                      PLACE_VECTOR(VECTOR_NAME(func), offset) \
                                      PLACE_INTERRUPT(func)

#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED0_VECTOR        ".int00"                    /* 0xFFC0 Reserved Int. Vector 0 */
#else
#define RESERVED0_VECTOR        (0 * 1u)                     /* 0xFFC0 Reserved Int. Vector 0 */
/*#define RESERVED0_ISR(func)     ISR_VECTOR(func, ".int00")  */ /* 0xFFC0 Reserved Int. Vector 0 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED1_VECTOR        ".int01"                    /* 0xFFC2 Reserved Int. Vector 1 */
#else
#define RESERVED1_VECTOR        (1 * 1u)                     /* 0xFFC2 Reserved Int. Vector 1 */
/*#define RESERVED1_ISR(func)     ISR_VECTOR(func, ".int01")  */ /* 0xFFC2 Reserved Int. Vector 1 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED2_VECTOR        ".int02"                    /* 0xFFC4 Reserved Int. Vector 2 */
#else
#define RESERVED2_VECTOR        (2 * 1u)                     /* 0xFFC4 Reserved Int. Vector 2 */
/*#define RESERVED2_ISR(func)     ISR_VECTOR(func, ".int02")  */ /* 0xFFC4 Reserved Int. Vector 2 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED3_VECTOR        ".int03"                    /* 0xFFC6 Reserved Int. Vector 3 */
#else
#define RESERVED3_VECTOR        (3 * 1u)                     /* 0xFFC6 Reserved Int. Vector 3 */
/*#define RESERVED3_ISR(func)     ISR_VECTOR(func, ".int03")  */ /* 0xFFC6 Reserved Int. Vector 3 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED4_VECTOR        ".int04"                    /* 0xFFC8 Reserved Int. Vector 4 */
#else
#define RESERVED4_VECTOR        (4 * 1u)                     /* 0xFFC8 Reserved Int. Vector 4 */
/*#define RESERVED4_ISR(func)     ISR_VECTOR(func, ".int04")  */ /* 0xFFC8 Reserved Int. Vector 4 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED5_VECTOR        ".int05"                    /* 0xFFCA Reserved Int. Vector 5 */
#else
#define RESERVED5_VECTOR        (5 * 1u)                     /* 0xFFCA Reserved Int. Vector 5 */
/*#define RESERVED5_ISR(func)     ISR_VECTOR(func, ".int05")  */ /* 0xFFCA Reserved Int. Vector 5 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED6_VECTOR        ".int06"                    /* 0xFFCC Reserved Int. Vector 6 */
#else
#define RESERVED6_VECTOR        (6 * 1u)                     /* 0xFFCC Reserved Int. Vector 6 */
/*#define RESERVED6_ISR(func)     ISR_VECTOR(func, ".int06")  */ /* 0xFFCC Reserved Int. Vector 6 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED7_VECTOR        ".int07"                    /* 0xFFCE Reserved Int. Vector 7 */
#else
#define RESERVED7_VECTOR        (7 * 1u)                     /* 0xFFCE Reserved Int. Vector 7 */
/*#define RESERVED7_ISR(func)     ISR_VECTOR(func, ".int07")  */ /* 0xFFCE Reserved Int. Vector 7 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED8_VECTOR        ".int08"                    /* 0xFFD0 Reserved Int. Vector 8 */
#else
#define RESERVED8_VECTOR        (8 * 1u)                     /* 0xFFD0 Reserved Int. Vector 8 */
/*#define RESERVED8_ISR(func)     ISR_VECTOR(func, ".int08")  */ /* 0xFFD0 Reserved Int. Vector 8 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED9_VECTOR        ".int09"                    /* 0xFFD2 Reserved Int. Vector 9 */
#else
#define RESERVED9_VECTOR        (9 * 1u)                     /* 0xFFD2 Reserved Int. Vector 9 */
/*#define RESERVED9_ISR(func)     ISR_VECTOR(func, ".int09")  */ /* 0xFFD2 Reserved Int. Vector 9 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED10_VECTOR       ".int10"                    /* 0xFFD4 Reserved Int. Vector 10 */
#else
#define RESERVED10_VECTOR       (10 * 1u)                    /* 0xFFD4 Reserved Int. Vector 10 */
/*#define RESERVED10_ISR(func)    ISR_VECTOR(func, ".int10")  */ /* 0xFFD4 Reserved Int. Vector 10 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED11_VECTOR       ".int11"                    /* 0xFFD6 Reserved Int. Vector 11 */
#else
#define RESERVED11_VECTOR       (11 * 1u)                    /* 0xFFD6 Reserved Int. Vector 11 */
/*#define RESERVED11_ISR(func)    ISR_VECTOR(func, ".int11")  */ /* 0xFFD6 Reserved Int. Vector 11 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED12_VECTOR       ".int12"                    /* 0xFFD8 Reserved Int. Vector 12 */
#else
#define RESERVED12_VECTOR       (12 * 1u)                    /* 0xFFD8 Reserved Int. Vector 12 */
/*#define RESERVED12_ISR(func)    ISR_VECTOR(func, ".int12")  */ /* 0xFFD8 Reserved Int. Vector 12 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED13_VECTOR       ".int13"                    /* 0xFFDA Reserved Int. Vector 13 */
#else
#define RESERVED13_VECTOR       (13 * 1u)                    /* 0xFFDA Reserved Int. Vector 13 */
/*#define RESERVED13_ISR(func)    ISR_VECTOR(func, ".int13")  */ /* 0xFFDA Reserved Int. Vector 13 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED14_VECTOR       ".int14"                    /* 0xFFDC Reserved Int. Vector 14 */
#else
#define RESERVED14_VECTOR       (14 * 1u)                    /* 0xFFDC Reserved Int. Vector 14 */
/*#define RESERVED14_ISR(func)    ISR_VECTOR(func, ".int14")  */ /* 0xFFDC Reserved Int. Vector 14 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED15_VECTOR       ".int15"                    /* 0xFFDE Reserved Int. Vector 15 */
#else
#define RESERVED15_VECTOR       (15 * 1u)                    /* 0xFFDE Reserved Int. Vector 15 */
/*#define RESERVED15_ISR(func)    ISR_VECTOR(func, ".int15")  */ /* 0xFFDE Reserved Int. Vector 15 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USCIAB1TX_VECTOR        ".int16"                    /* 0xFFE0 USCI A1/B1 Transmit */
#else
#define USCIAB1TX_VECTOR        (16 * 1u)                    /* 0xFFE0 USCI A1/B1 Transmit */
/*#define USCIAB1TX_ISR(func)     ISR_VECTOR(func, ".int16")  */ /* 0xFFE0 USCI A1/B1 Transmit */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USCIAB1RX_VECTOR        ".int17"                    /* 0xFFE2 USCI A1/B1 Receive */
#else
#define USCIAB1RX_VECTOR        (17 * 1u)                    /* 0xFFE2 USCI A1/B1 Receive */
/*#define USCIAB1RX_ISR(func)     ISR_VECTOR(func, ".int17")  */ /* 0xFFE2 USCI A1/B1 Receive */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT1_VECTOR            ".int18"                    /* 0xFFE4 Port 1 */
#else
#define PORT1_VECTOR            (18 * 1u)                    /* 0xFFE4 Port 1 */
/*#define PORT1_ISR(func)         ISR_VECTOR(func, ".int18")  */ /* 0xFFE4 Port 1 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT2_VECTOR            ".int19"                    /* 0xFFE6 Port 2 */
#else
#define PORT2_VECTOR            (19 * 1u)                    /* 0xFFE6 Port 2 */
/*#define PORT2_ISR(func)         ISR_VECTOR(func, ".int19")  */ /* 0xFFE6 Port 2 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESERVED20_VECTOR       ".int20"                    /* 0xFFE8 Reserved Int. Vector 20 */
#else
#define RESERVED20_VECTOR       (20 * 1u)                    /* 0xFFE8 Reserved Int. Vector 20 */
/*#define RESERVED20_ISR(func)    ISR_VECTOR(func, ".int20")  */ /* 0xFFE8 Reserved Int. Vector 20 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define ADC12_VECTOR            ".int21"                    /* 0xFFEA ADC */
#else
#define ADC12_VECTOR            (21 * 1u)                    /* 0xFFEA ADC */
/*#define ADC12_ISR(func)         ISR_VECTOR(func, ".int21")  */ /* 0xFFEA ADC */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USCIAB0TX_VECTOR        ".int22"                    /* 0xFFEC USCI A0/B0 Transmit */
#else
#define USCIAB0TX_VECTOR        (22 * 1u)                    /* 0xFFEC USCI A0/B0 Transmit */
/*#define USCIAB0TX_ISR(func)     ISR_VECTOR(func, ".int22")  */ /* 0xFFEC USCI A0/B0 Transmit */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USCIAB0RX_VECTOR        ".int23"                    /* 0xFFEE USCI A0/B0 Receive */
#else
#define USCIAB0RX_VECTOR        (23 * 1u)                    /* 0xFFEE USCI A0/B0 Receive */
/*#define USCIAB0RX_ISR(func)     ISR_VECTOR(func, ".int23")  */ /* 0xFFEE USCI A0/B0 Receive */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERA1_VECTOR          ".int24"                    /* 0xFFF0 Timer A CC1-2, TA */
#else
#define TIMERA1_VECTOR          (24 * 1u)                    /* 0xFFF0 Timer A CC1-2, TA */
/*#define TIMERA1_ISR(func)       ISR_VECTOR(func, ".int24")  */ /* 0xFFF0 Timer A CC1-2, TA */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERA0_VECTOR          ".int25"                    /* 0xFFF2 Timer A CC0 */
#else
#define TIMERA0_VECTOR          (25 * 1u)                    /* 0xFFF2 Timer A CC0 */
/*#define TIMERA0_ISR(func)       ISR_VECTOR(func, ".int25")  */ /* 0xFFF2 Timer A CC0 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define WDT_VECTOR              ".int26"                    /* 0xFFF4 Watchdog Timer */
#else
#define WDT_VECTOR              (26 * 1u)                    /* 0xFFF4 Watchdog Timer */
/*#define WDT_ISR(func)           ISR_VECTOR(func, ".int26")  */ /* 0xFFF4 Watchdog Timer */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define COMPARATORA_VECTOR      ".int27"                    /* 0xFFF6 Comparator A */
#else
#define COMPARATORA_VECTOR      (27 * 1u)                    /* 0xFFF6 Comparator A */
/*#define COMPARATORA_ISR(func)   ISR_VECTOR(func, ".int27")  */ /* 0xFFF6 Comparator A */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERB1_VECTOR          ".int28"                    /* 0xFFF8 Timer B CC1-6, TB */
#else
#define TIMERB1_VECTOR          (28 * 1u)                    /* 0xFFF8 Timer B CC1-6, TB */
/*#define TIMERB1_ISR(func)       ISR_VECTOR(func, ".int28")  */ /* 0xFFF8 Timer B CC1-6, TB */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERB0_VECTOR          ".int29"                    /* 0xFFFA Timer B CC0 */
#else
#define TIMERB0_VECTOR          (29 * 1u)                    /* 0xFFFA Timer B CC0 */
/*#define TIMERB0_ISR(func)       ISR_VECTOR(func, ".int29")  */ /* 0xFFFA Timer B CC0 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define NMI_VECTOR              ".int30"                    /* 0xFFFC Non-maskable */
#else
#define NMI_VECTOR              (30 * 1u)                    /* 0xFFFC Non-maskable */
/*#define NMI_ISR(func)           ISR_VECTOR(func, ".int30")  */ /* 0xFFFC Non-maskable */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define RESET_VECTOR            ".reset"                    /* 0xFFFE Reset [Highest Priority] */
#else
#define RESET_VECTOR            (31 * 1u)                    /* 0xFFFE Reset [Highest Priority] */
/*#define RESET_ISR(func)         ISR_VECTOR(func, ".int31")  */ /* 0xFFFE Reset [Highest Priority] */ /* CCE V2 Style */
#endif

/************************************************************
* End of Modules
************************************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* #ifndef __msp430x241x */

