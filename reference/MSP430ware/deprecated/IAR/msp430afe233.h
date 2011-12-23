/********************************************************************
*
* Standard register and bit definitions for the Texas Instruments
* MSP430 microcontroller.
*
* This file supports assembler and C development for
* MSP430AFE233 devices.
*
* Texas Instruments, Version 1.0
*
* Rev. 1.0, Setup
*
********************************************************************/

#ifndef __MSP430AFE233
#define __MSP430AFE233

#define __MSP430_HEADER_VERSION__ 1059

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error msp430afe233.h file for use with ICC430/A430 only
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
#define WDTIE               (0x01)    /* Watchdog Interrupt Enable */
#define OFIE                (0x02)    /* Osc. Fault  Interrupt Enable */
#define NMIIE               (0x10)    /* NMI Interrupt Enable */
#define ACCVIE              (0x20)    /* Flash Access Violation Interrupt Enable */
#define URXIE0              (0x40)
#define UTXIE0              (0x80)

#define IFG1_               (0x0002u)  /* Interrupt Flag 1 */
DEFC(   IFG1              , IFG1_)
#define U0IFG               IFG1      /* UART0 Interrupt Flag Register */
#define WDTIFG              (0x01)    /* Watchdog Interrupt Flag */
#define OFIFG               (0x02)    /* Osc. Fault Interrupt Flag */
#define PORIFG              (0x04)    /* Power On Interrupt Flag */
#define RSTIFG              (0x08)    /* Reset Interrupt Flag */
#define NMIIFG              (0x10)    /* NMI Interrupt Flag */
#define URXIFG0             (0x40)
#define UTXIFG0             (0x80)

#define ME1_                (0x0004u)  /* Module Enable 1 */
DEFC(   ME1               , ME1_)
#define U0ME                ME1       /* UART0 Module Enable Register */
#define URXE0               (0x40)
#define UTXE0               (0x80)
#define USPIE0              (0x40)

/************************************************************
* Basic Clock Module
************************************************************/
#define __MSP430_HAS_BC2__            /* Definition to show that Module is available */

#define DCOCTL_             (0x0056u)  /* DCO Clock Frequency Control */
DEFC(   DCOCTL            , DCOCTL_)
#define BCSCTL1_            (0x0057u)  /* Basic Clock System Control 1 */
DEFC(   BCSCTL1           , BCSCTL1_)
#define BCSCTL2_            (0x0058u)  /* Basic Clock System Control 2 */
DEFC(   BCSCTL2           , BCSCTL2_)
#define BCSCTL3_            (0x0053u)  /* Basic Clock System Control 3 */
DEFC(   BCSCTL3           , BCSCTL3_)

#define MOD0                (0x01)   /* Modulation Bit 0 */
#define MOD1                (0x02)   /* Modulation Bit 1 */
#define MOD2                (0x04)   /* Modulation Bit 2 */
#define MOD3                (0x08)   /* Modulation Bit 3 */
#define MOD4                (0x10)   /* Modulation Bit 4 */
#define DCO0                (0x20)   /* DCO Select Bit 0 */
#define DCO1                (0x40)   /* DCO Select Bit 1 */
#define DCO2                (0x80)   /* DCO Select Bit 2 */

#define RSEL0               (0x01)   /* Range Select Bit 0 */
#define RSEL1               (0x02)   /* Range Select Bit 1 */
#define RSEL2               (0x04)   /* Range Select Bit 2 */
#define RSEL3               (0x08)   /* Range Select Bit 3 */
#define DIVA0               (0x10)   /* ACLK Divider 0 */
#define DIVA1               (0x20)   /* ACLK Divider 1 */
#define XTS                 (0x40)   /* LFXTCLK 0:Low Freq. / 1: High Freq. */
#define XT2OFF              (0x80)   /* Enable XT2CLK */

#define DIVA_0              (0x00)   /* ACLK Divider 0: /1 */
#define DIVA_1              (0x10)   /* ACLK Divider 1: /2 */
#define DIVA_2              (0x20)   /* ACLK Divider 2: /4 */
#define DIVA_3              (0x30)   /* ACLK Divider 3: /8 */

#define DIVS0               (0x02)   /* SMCLK Divider 0 */
#define DIVS1               (0x04)   /* SMCLK Divider 1 */
#define SELS                (0x08)   /* SMCLK Source Select 0:DCOCLK / 1:XT2CLK/LFXTCLK */
#define DIVM0               (0x10)   /* MCLK Divider 0 */
#define DIVM1               (0x20)   /* MCLK Divider 1 */
#define SELM0               (0x40)   /* MCLK Source Select 0 */
#define SELM1               (0x80)   /* MCLK Source Select 1 */

#define DIVS_0              (0x00)   /* SMCLK Divider 0: /1 */
#define DIVS_1              (0x02)   /* SMCLK Divider 1: /2 */
#define DIVS_2              (0x04)   /* SMCLK Divider 2: /4 */
#define DIVS_3              (0x06)   /* SMCLK Divider 3: /8 */

#define DIVM_0              (0x00)   /* MCLK Divider 0: /1 */
#define DIVM_1              (0x10)   /* MCLK Divider 1: /2 */
#define DIVM_2              (0x20)   /* MCLK Divider 2: /4 */
#define DIVM_3              (0x30)   /* MCLK Divider 3: /8 */

#define SELM_0              (0x00)   /* MCLK Source Select 0: DCOCLK */
#define SELM_1              (0x40)   /* MCLK Source Select 1: DCOCLK */
#define SELM_2              (0x80)   /* MCLK Source Select 2: XT2CLK/LFXTCLK */
#define SELM_3              (0xC0)   /* MCLK Source Select 3: LFXTCLK */

#define LFXT1OF             (0x01)   /* Low/high Frequency Oscillator Fault Flag */
#define XT2OF               (0x02)   /* High frequency oscillator 2 fault flag */
#define XCAP0               (0x04)   /* XIN/XOUT Cap 0 */
#define XCAP1               (0x08)   /* XIN/XOUT Cap 1 */
#define LFXT1S0             (0x10)   /* Mode 0 for LFXT1 (XTS = 0) */
#define LFXT1S1             (0x20)   /* Mode 1 for LFXT1 (XTS = 0) */
#define XT2S0               (0x40)   /* Mode 0 for XT2 */
#define XT2S1               (0x80)   /* Mode 1 for XT2 */

#define XCAP_0              (0x00)   /* XIN/XOUT Cap : 0 pF */
#define XCAP_1              (0x04)   /* XIN/XOUT Cap : 6 pF */
#define XCAP_2              (0x08)   /* XIN/XOUT Cap : 10 pF */
#define XCAP_3              (0x0C)   /* XIN/XOUT Cap : 12.5 pF */

#define LFXT1S_0            (0x00)   /* Mode 0 for LFXT1 : Normal operation */
#define LFXT1S_1            (0x10)   /* Mode 1 for LFXT1 : Reserved */
#define LFXT1S_2            (0x20)   /* Mode 2 for LFXT1 : VLO */
#define LFXT1S_3            (0x30)   /* Mode 3 for LFXT1 : Digital input signal */

#define XT2S_0              (0x00)   /* Mode 0 for XT2 : 0.4 - 1 MHz */
#define XT2S_1              (0x40)   /* Mode 1 for XT2 : 1 - 4 MHz */
#define XT2S_2              (0x80)   /* Mode 2 for XT2 : 2 - 16 MHz */
#define XT2S_3              (0xC0)   /* Mode 3 for XT2 : Digital input signal */

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
* DIGITAL I/O Port1/2 Pull up / Pull down Resistors
************************************************************/
#define __MSP430_HAS_PORT1_R__        /* Definition to show that Module is available */
#define __MSP430_HAS_PORT2_R__        /* Definition to show that Module is available */

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
#define P1SEL2_             (0x0041u)  /* Port 1 Selection 2 */
DEFC(   P1SEL2            , P1SEL2_)
#define P1REN_              (0x0027u)  /* Port 1 Resistor Enable */
DEFC(   P1REN             , P1REN_)

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
#define P2SEL2_             (0x0042u)  /* Port 2 Selection 2 */
DEFC(   P2SEL2            , P2SEL2_)
#define P2REN_              (0x002Fu)  /* Port 2 Resistor Enable */
DEFC(   P2REN             , P2REN_)

/************************************************************
* SD24_A3 - Sigma Delta 24 Bit
************************************************************/
#define __MSP430_HAS_SD24_A3__        /* Definition to show that Module is available */

#define SD24INCTL0_         (0x00B0u)  /* SD24 Input Control Register Channel 0 */
DEFC(   SD24INCTL0        , SD24INCTL0_)
#define SD24INCTL1_         (0x00B1u)  /* SD24 Input Control Register Channel 1 */
DEFC(   SD24INCTL1        , SD24INCTL1_)
#define SD24INCTL2_         (0x00B2u)  /* SD24 Input Control Register Channel 2 */
DEFC(   SD24INCTL2        , SD24INCTL2_)
#define SD24PRE0_           (0x00B8u)  /* SD24 Preload Register Channel 0 */
DEFC(   SD24PRE0          , SD24PRE0_)
#define SD24PRE1_           (0x00B9u)  /* SD24 Preload Register Channel 1 */
DEFC(   SD24PRE1          , SD24PRE1_)
#define SD24PRE2_           (0x00BAu)  /* SD24 Preload Register Channel 2 */
DEFC(   SD24PRE2          , SD24PRE2_)
#define SD24CONF1_          (0x00BFu)  /* SD24 Internal Configuration Register 1 */
DEFC(   SD24CONF1         , SD24CONF1_)
                                      /* Please use only the recommended settings */

#define SD24CTL_            (0x0100u)  /* Sigma Delta ADC 24 Control Register */
DEFW(   SD24CTL           , SD24CTL_)
#define SD24CCTL0_          (0x0102u)  /* SD24 Channel 0 Control Register */
DEFW(   SD24CCTL0         , SD24CCTL0_)
#define SD24CCTL1_          (0x0104u)  /* SD24 Channel 1 Control Register */
DEFW(   SD24CCTL1         , SD24CCTL1_)
#define SD24CCTL2_          (0x0106u)  /* SD24 Channel 2 Control Register */
DEFW(   SD24CCTL2         , SD24CCTL2_)
#define SD24MEM0_           (0x0110u)  /* SD24 Channel 0 Conversion Memory */
DEFW(   SD24MEM0          , SD24MEM0_)
#define SD24MEM1_           (0x0112u)  /* SD24 Channel 1 Conversion Memory */
DEFW(   SD24MEM1          , SD24MEM1_)
#define SD24MEM2_           (0x0114u)  /* SD24 Channel 2 Conversion Memory */
DEFW(   SD24MEM2          , SD24MEM2_)
#define SD24IV_             (0x01AEu)  /* SD24 Interrupt Vector Register */
DEFW(   SD24IV            , SD24IV_)

/* SD24INCTLx */
#define SD24INCH0           (0x0001u)  /* SD24 Input Channel select 0 */
#define SD24INCH1           (0x0002u)  /* SD24 Input Channel select 1 */
#define SD24INCH2           (0x0004u)  /* SD24 Input Channel select 2 */
#define SD24GAIN0           (0x0008u)  /* SD24 Input Pre-Amplifier Gain Select 0 */
#define SD24GAIN1           (0x0010u)  /* SD24 Input Pre-Amplifier Gain Select 1 */
#define SD24GAIN2           (0x0020u)  /* SD24 Input Pre-Amplifier Gain Select 2 */
#define SD24INTDLY0         (0x0040u)  /* SD24 Interrupt Delay after 1.Conversion 0 */
#define SD24INTDLY1         (0x0080u)  /* SD24 Interrupt Delay after 1.Conversion 1 */

#define SD24GAIN_1          (0x0000u)  /* SD24 Input Pre-Amplifier Gain Select *1  */
#define SD24GAIN_2          (0x0008u)  /* SD24 Input Pre-Amplifier Gain Select *2  */
#define SD24GAIN_4          (0x0010u)  /* SD24 Input Pre-Amplifier Gain Select *4  */
#define SD24GAIN_8          (0x0018u)  /* SD24 Input Pre-Amplifier Gain Select *8  */
#define SD24GAIN_16         (0x0020u)  /* SD24 Input Pre-Amplifier Gain Select *16 */
#define SD24GAIN_32         (0x0028u)  /* SD24 Input Pre-Amplifier Gain Select *32 */

#define SD24INCH_0          (0x0000u)  /* SD24 Input Channel select input */
#define SD24INCH_1          (0x0001u)  /* SD24 Input Channel select input */
#define SD24INCH_2          (0x0002u)  /* SD24 Input Channel select input */
#define SD24INCH_3          (0x0003u)  /* SD24 Input Channel select input */
#define SD24INCH_4          (0x0004u)  /* SD24 Input Channel select input */
#define SD24INCH_5          (0x0005u)  /* SD24 Input Channel select Vcc divider */
#define SD24INCH_6          (0x0006u)  /* SD24 Input Channel select Temp */
#define SD24INCH_7          (0x0007u)  /* SD24 Input Channel select Offset */

#define SD24INTDLY_0        (0x0000u)  /* SD24 Interrupt Delay: Int. after 4.Conversion  */
#define SD24INTDLY_1        (0x0040u)  /* SD24 Interrupt Delay: Int. after 3.Conversion  */
#define SD24INTDLY_2        (0x0080u)  /* SD24 Interrupt Delay: Int. after 2.Conversion  */
#define SD24INTDLY_3        (0x00C0u)  /* SD24 Interrupt Delay: Int. after 1.Conversion  */

/* SD24CTL */
#define SD24OVIE            (0x0002u)  /* SD24 Overflow Interupt Enable */
#define SD24REFON           (0x0004u)  /* SD24 Switch internal Reference on */
#define SD24VMIDON          (0x0008u)  /* SD24 Switch Vmid Buffer on */
#define SD24SSEL0           (0x0010u)  /* SD24 Clock Source Select 0 */
#define SD24SSEL1           (0x0020u)  /* SD24 Clock Source Select 1 */
#define SD24DIV0            (0x0040u)  /* SD24 Clock Divider Select 0 */
#define SD24DIV1            (0x0080u)  /* SD24 Clock Divider Select 1 */
#define SD24LP              (0x0100u)  /* SD24 Low Power Mode Enable */
#define SD24XDIV0           (0x0200u)  /* SD24 2.Clock Divider Select 0 */
#define SD24XDIV1           (0x0400u)  /* SD24 2.Clock Divider Select 1 */
//#define SD24XDIV2           (0x0800u)  /* SD24 2.Clock Divider Select 2 */

#define SD24DIV_0            (0x0000u)               /* SD24 Clock Divider Select /1 */
#define SD24DIV_1            (SD24DIV0)             /* SD24 Clock Divider Select /2 */
#define SD24DIV_2            (SD24DIV1)             /* SD24 Clock Divider Select /4 */
#define SD24DIV_3            (SD24DIV0+SD24DIV1)    /* SD24 Clock Divider Select /8 */

#define SD24XDIV_0          (0x0000u)               /* SD24 2.Clock Divider Select /1 */
#define SD24XDIV_1          (SD24XDIV0)            /* SD24 2.Clock Divider Select /3 */
#define SD24XDIV_2          (SD24XDIV1)            /* SD24 2.Clock Divider Select /16 */
#define SD24XDIV_3          (SD24XDIV0+SD24XDIV1)  /* SD24 2.Clock Divider Select /48 */

#define SD24SSEL_0           (0x0000u)               /* SD24 Clock Source Select MCLK  */
#define SD24SSEL_1           (SD24SSEL0)            /* SD24 Clock Source Select SMCLK */
#define SD24SSEL_2           (SD24SSEL1)            /* SD24 Clock Source Select ACLK  */
#define SD24SSEL_3           (SD24SSEL0+SD24SSEL1)  /* SD24 Clock Source Select TACLK */

/* SD24CCTLx */
#define SD24GRP             (0x0001u)  /* SD24 Grouping of Channels: 0:Off/1:On */
#define SD24SC              (0x0002u)  /* SD24 Start Conversion */
#define SD24IFG             (0x0004u)  /* SD24 Channel x Interrupt Flag */
#define SD24IE              (0x0008u)  /* SD24 Channel x Interrupt Enable */
#define SD24DF              (0x0010u)  /* SD24 Channel x Data Format: 0:Unipolar/1:Bipolar */
#define SD24OVIFG           (0x0020u)  /* SD24 Channel x Overflow Interrupt Flag */
#define SD24LSBACC          (0x0040u)  /* SD24 Channel x Access LSB of ADC */
#define SD24LSBTOG          (0x0080u)  /* SD24 Channel x Toggle LSB Output of ADC */
#define SD24OSR0            (0x0100u)  /* SD24 Channel x OverSampling Ratio 0 */
#define SD24OSR1            (0x0200u)  /* SD24 Channel x OverSampling Ratio 1 */
#define SD24SNGL            (0x0400u)  /* SD24 Channel x Single Conversion On/Off */
#define SD24XOSR            (0x0800u)  /* SD24 Channel x Extended OverSampling Ratio */
#define SD24UNI             (0x1000u)  /* SD24 Channel x Bipolar(0) / Unipolar(1) Mode */

#define SD24OSR_1024        (SD24OSR0+SD24XOSR)     /* SD24 Channel x OverSampling Ratio 1024 */
#define SD24OSR_512         (SD24XOSR)              /* SD24 Channel x OverSampling Ratio 512 */
#define SD24OSR_256         (0x0000u)  /* SD24 Channel x OverSampling Ratio 256 */
#define SD24OSR_128         (0x0100u)  /* SD24 Channel x OverSampling Ratio 128 */
#define SD24OSR_64          (0x0200u)  /* SD24 Channel x OverSampling Ratio  64 */
#define SD24OSR_32          (0x0300u)  /* SD24 Channel x OverSampling Ratio  32 */

/* SD24IV Definitions */
#define SD24IV_NONE         (0x0000u)    /* No Interrupt pending */
#define SD24IV_SD24OVIFG    (0x0002u)    /* SD24OVIFG */
#define SD24IV_SD24MEM0     (0x0004u)    /* SD24MEM0 SD24IFG */
#define SD24IV_SD24MEM1     (0x0006u)    /* SD24MEM1 SD24IFG */
#define SD24IV_SD24MEM2     (0x0008u)    /* SD24MEM2 SD24IFG */

/************************************************************
* Brown-Out, Supply Voltage Supervision (SVS)
************************************************************/
#define __MSP430_HAS_SVS__            /* Definition to show that Module is available */

#define SVSCTL_             (0x0055u)  /* SVS Control */
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
* Calibration Data in Info Mem
************************************************************/

#ifndef __DisableCalData

#define CALDCO_12MHZ_         (0x10FAu)  /* DCOCTL  Calibration Data for 12MHz */
READ_ONLY DEFC( CALDCO_12MHZ     , CALDCO_12MHZ_)
#define CALBC1_12MHZ_         (0x10FBu)  /* BCSCTL1 Calibration Data for 12MHz */
READ_ONLY DEFC( CALBC1_12MHZ     , CALBC1_12MHZ_)
#define CALDCO_8MHZ_          (0x10FCu)  /* DCOCTL  Calibration Data for 8MHz */
READ_ONLY DEFC( CALDCO_8MHZ      , CALDCO_8MHZ_)
#define CALBC1_8MHZ_          (0x10FDu)  /* BCSCTL1 Calibration Data for 8MHz */
READ_ONLY DEFC( CALBC1_8MHZ      , CALBC1_8MHZ_)

#endif /* #ifndef __DisableCalData */

/************************************************************
* Interrupt Vectors (offset from 0xFFE0)
************************************************************/

#define PORT2_VECTOR        (1 * 2u)  /* 0xFFE2 Port 2 */
#define PORT1_VECTOR        (4 * 2u)  /* 0xFFE8 Port 1 */
#define TIMERA1_VECTOR      (5 * 2u)  /* 0xFFEA Timer A CC1, TA */
#define TIMERA0_VECTOR      (6 * 2u)  /* 0xFFEC Timer A CC0 */
#define USART0TX_VECTOR     (8 * 2u)  /* 0xFFF0 USART 0 Transmit */
#define USART0RX_VECTOR     (9 * 2u)  /* 0xFFF2 USART 0 Receive */
#define WDT_VECTOR          (10 * 2u) /* 0xFFF4 Watchdog Timer */
#define SD24_VECTOR         (12 * 2u) /* 0xFFF8 Sigma Delta ADC */
#define NMI_VECTOR          (14 * 2u) /* 0xFFFC Non-maskable */
#define RESET_VECTOR        (15 * 2u) /* 0xFFFE Reset [Highest Priority] */

/************************************************************
* End of Modules
************************************************************/
#pragma language=default

#endif /* #ifndef __MSP430AFE233 */
