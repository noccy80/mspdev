/********************************************************************
*
* Standard register and bit definitions for the Texas Instruments
* MSP430 microcontroller.
*
* This file supports assembler and C development for
* MSP430x14x devices.
*
* Texas Instruments, Version 2.4
*
* Rev. 1.2, Additional Timer B bit definitions.
*           Renamed XTOFF to XT2OFF.
* Rev. 1.3, Removed leading 0 to aviod interpretation as octal
*            values under C
* Rev. 1.4, Corrected LPMx_EXIT to reference new intrinsic _BIC_SR_IRQ
*           Changed TAIV and TBIV to be read-only
* Rev. 1.5, Enclose all #define statements with parentheses
* Rev. 1.6, Defined vectors for USART (in addition to UART)
* Rev. 1.7, Added USART special function labels (UxME, UxIE, UxIFG)
* Rev. 2.1, Alignment of defintions in Users Guide and of version numbers
* Rev. 2.2, Fixed type in ADC12 bit definitions (replaced ADC10 with ADC12)
* Rev. 2.3, Removed unused def of TASSEL2 / TBSSEL2
* Rev. 2.4, added definitions for Interrupt Vectors xxIV
*
********************************************************************/

#ifndef __msp430x14x
#define __msp430x14x

#define __MSP430_HEADER_VERSION__ 1059

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#if (((__TID__ >> 8) & 0x7F) != 0x2b)     /* 0x2b = 43 dec */
#error msp430f149.h file for use with ICC430/A430 only
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
#define U0ME                ME1      /* UART0 Module Enable Register */
#define URXE0               (0x40)
#define UTXE0               (0x80)
#define USPIE0              (0x40)

#define IE2_                (0x0001u)  /* Interrupt Enable 2 */
DEFC(   IE2               , IE2_)
#define U1IE                IE2       /* UART1 Interrupt Enable Register */
#define URXIE1              (0x10)
#define UTXIE1              (0x20)

#define IFG2_               (0x0003u)  /* Interrupt Flag 2 */
DEFC(   IFG2              , IFG2_)
#define U1IFG               IFG2      /* UART1 Interrupt Flag Register */
#define URXIFG1             (0x10)
#define UTXIFG1             (0x20)

#define ME2_                (0x0005u)  /* Module Enable 2 */
DEFC(   ME2               , ME2_)
#define U1ME                ME2       /* UART1 Module Enable Register */
#define URXE1               (0x10)
#define UTXE1               (0x20)
#define USPIE1              (0x10)

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
* USART 1
************************************************************/
#define __MSP430_HAS_UART1__          /* Definition to show that Module is available */

#define U1CTL_              (0x0078u)  /* USART 1 Control */
DEFC(   U1CTL             , U1CTL_)
#define U1TCTL_             (0x0079u)  /* USART 1 Transmit Control */
DEFC(   U1TCTL            , U1TCTL_)
#define U1RCTL_             (0x007Au)  /* USART 1 Receive Control */
DEFC(   U1RCTL            , U1RCTL_)
#define U1MCTL_             (0x007Bu)  /* USART 1 Modulation Control */
DEFC(   U1MCTL            , U1MCTL_)
#define U1BR0_              (0x007Cu)  /* USART 1 Baud Rate 0 */
DEFC(   U1BR0             , U1BR0_)
#define U1BR1_              (0x007Du)  /* USART 1 Baud Rate 1 */
DEFC(   U1BR1             , U1BR1_)
#define U1RXBUF_            (0x007Eu)  /* USART 1 Receive Buffer */
READ_ONLY DEFC( U1RXBUF        , U1RXBUF_)
#define U1TXBUF_            (0x007Fu)  /* USART 1 Transmit Buffer */
DEFC(   U1TXBUF           , U1TXBUF_)

/* Alternate register names */

#define UCTL1               U1CTL     /* USART 1 Control */
#define UTCTL1              U1TCTL    /* USART 1 Transmit Control */
#define URCTL1              U1RCTL    /* USART 1 Receive Control */
#define UMCTL1              U1MCTL    /* USART 1 Modulation Control */
#define UBR01               U1BR0     /* USART 1 Baud Rate 0 */
#define UBR11               U1BR1     /* USART 1 Baud Rate 1 */
#define RXBUF1              U1RXBUF   /* USART 1 Receive Buffer */
#define TXBUF1              U1TXBUF   /* USART 1 Transmit Buffer */
#define UCTL1_              U1CTL_    /* USART 1 Control */
#define UTCTL1_             U1TCTL_   /* USART 1 Transmit Control */
#define URCTL1_             U1RCTL_   /* USART 1 Receive Control */
#define UMCTL1_             U1MCTL_   /* USART 1 Modulation Control */
#define UBR01_              U1BR0_    /* USART 1 Baud Rate 0 */
#define UBR11_              U1BR1_    /* USART 1 Baud Rate 1 */
#define RXBUF1_             U1RXBUF_  /* USART 1 Receive Buffer */
#define TXBUF1_             U1TXBUF_  /* USART 1 Transmit Buffer */
#define UCTL_1              U1CTL     /* USART 1 Control */
#define UTCTL_1             U1TCTL    /* USART 1 Transmit Control */
#define URCTL_1             U1RCTL    /* USART 1 Receive Control */
#define UMCTL_1             U1MCTL    /* USART 1 Modulation Control */
#define UBR0_1              U1BR0     /* USART 1 Baud Rate 0 */
#define UBR1_1              U1BR1     /* USART 1 Baud Rate 1 */
#define RXBUF_1             U1RXBUF   /* USART 1 Receive Buffer */
#define TXBUF_1             U1TXBUF   /* USART 1 Transmit Buffer */
#define UCTL_1_             U1CTL_    /* USART 1 Control */
#define UTCTL_1_            U1TCTL_   /* USART 1 Transmit Control */
#define URCTL_1_            U1RCTL_   /* USART 1 Receive Control */
#define UMCTL_1_            U1MCTL_   /* USART 1 Modulation Control */
#define UBR0_1_             U1BR0_    /* USART 1 Baud Rate 0 */
#define UBR1_1_             U1BR1_    /* USART 1 Baud Rate 1 */
#define RXBUF_1_            U1RXBUF_  /* USART 1 Receive Buffer */
#define TXBUF_1_            U1TXBUF_  /* USART 1 Transmit Buffer */

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
* Timer B7
************************************************************/
#define __MSP430_HAS_TB7__            /* Definition to show that Module is available */

#define TBIV_               (0x011Eu)  /* Timer B Interrupt Vector Word */
READ_ONLY DEFW( TBIV           , TBIV_)
#define TBCTL_              (0x0180u)  /* Timer B Control */
DEFW(   TBCTL             , TBCTL_)
#define TBCCTL0_            (0x0182u)  /* Timer B Capture/Compare Control 0 */
DEFW(   TBCCTL0           , TBCCTL0_)
#define TBCCTL1_            (0x0184u)  /* Timer B Capture/Compare Control 1 */
DEFW(   TBCCTL1           , TBCCTL1_)
#define TBCCTL2_            (0x0186u)  /* Timer B Capture/Compare Control 2 */
DEFW(   TBCCTL2           , TBCCTL2_)
#define TBCCTL3_            (0x0188u)  /* Timer B Capture/Compare Control 3 */
DEFW(   TBCCTL3           , TBCCTL3_)
#define TBCCTL4_            (0x018Au)  /* Timer B Capture/Compare Control 4 */
DEFW(   TBCCTL4           , TBCCTL4_)
#define TBCCTL5_            (0x018Cu)  /* Timer B Capture/Compare Control 5 */
DEFW(   TBCCTL5           , TBCCTL5_)
#define TBCCTL6_            (0x018Eu)  /* Timer B Capture/Compare Control 6 */
DEFW(   TBCCTL6           , TBCCTL6_)
#define TBR_                (0x0190u)  /* Timer B Counter Register */
DEFW(   TBR               , TBR_)
#define TBCCR0_             (0x0192u)  /* Timer B Capture/Compare 0 */
DEFW(   TBCCR0            , TBCCR0_)
#define TBCCR1_             (0x0194u)  /* Timer B Capture/Compare 1 */
DEFW(   TBCCR1            , TBCCR1_)
#define TBCCR2_             (0x0196u)  /* Timer B Capture/Compare 2 */
DEFW(   TBCCR2            , TBCCR2_)
#define TBCCR3_             (0x0198u)  /* Timer B Capture/Compare 3 */
DEFW(   TBCCR3            , TBCCR3_)
#define TBCCR4_             (0x019Au)  /* Timer B Capture/Compare 4 */
DEFW(   TBCCR4            , TBCCR4_)
#define TBCCR5_             (0x019Cu)  /* Timer B Capture/Compare 5 */
DEFW(   TBCCR5            , TBCCR5_)
#define TBCCR6_             (0x019Eu)  /* Timer B Capture/Compare 6 */
DEFW(   TBCCR6            , TBCCR6_)

/* Alternate register names - 5xx style */
#define TB0IV               TBIV      /* Timer B Interrupt Vector Word */
#define TB0CTL              TBCTL     /* Timer B Control */
#define TB0CCTL0            TBCCTL0   /* Timer B Capture/Compare Control 0 */
#define TB0CCTL1            TBCCTL1   /* Timer B Capture/Compare Control 1 */
#define TB0CCTL2            TBCCTL2   /* Timer B Capture/Compare Control 2 */
#define TB0CCTL3            TBCCTL3   /* Timer B Capture/Compare Control 3 */
#define TB0CCTL4            TBCCTL4   /* Timer B Capture/Compare Control 4 */
#define TB0CCTL5            TBCCTL5   /* Timer B Capture/Compare Control 5 */
#define TB0CCTL6            TBCCTL6   /* Timer B Capture/Compare Control 6 */
#define TB0R                TBR       /* Timer B Counter Register */
#define TB0CCR0             TBCCR0    /* Timer B Capture/Compare 0 */
#define TB0CCR1             TBCCR1    /* Timer B Capture/Compare 1 */
#define TB0CCR2             TBCCR2    /* Timer B Capture/Compare 2 */
#define TB0CCR3             TBCCR3    /* Timer B Capture/Compare 3 */
#define TB0CCR4             TBCCR4    /* Timer B Capture/Compare 4 */
#define TB0CCR5             TBCCR5    /* Timer B Capture/Compare 5 */
#define TB0CCR6             TBCCR6    /* Timer B Capture/Compare 6 */
#define TB0IV_              TBIV_     /* Timer B Interrupt Vector Word */
#define TB0CTL_             TBCTL_    /* Timer B Control */
#define TB0CCTL0_           TBCCTL0_  /* Timer B Capture/Compare Control 0 */
#define TB0CCTL1_           TBCCTL1_  /* Timer B Capture/Compare Control 1 */
#define TB0CCTL2_           TBCCTL2_  /* Timer B Capture/Compare Control 2 */
#define TB0CCTL3_           TBCCTL3_  /* Timer B Capture/Compare Control 3 */
#define TB0CCTL4_           TBCCTL4_  /* Timer B Capture/Compare Control 4 */
#define TB0CCTL5_           TBCCTL5_  /* Timer B Capture/Compare Control 5 */
#define TB0CCTL6_           TBCCTL6_  /* Timer B Capture/Compare Control 6 */
#define TB0R_               TBR_      /* Timer B Counter Register */
#define TB0CCR0_            TBCCR0_   /* Timer B Capture/Compare 0 */
#define TB0CCR1_            TBCCR1_   /* Timer B Capture/Compare 1 */
#define TB0CCR2_            TBCCR2_   /* Timer B Capture/Compare 2 */
#define TB0CCR3_            TBCCR3_   /* Timer B Capture/Compare 3 */
#define TB0CCR4_            TBCCR4_   /* Timer B Capture/Compare 4 */
#define TB0CCR5_            TBCCR5_   /* Timer B Capture/Compare 5 */
#define TB0CCR6_            TBCCR6_   /* Timer B Capture/Compare 6 */

#define TBCLGRP1            (0x4000u)  /* Timer B Compare latch load group 1 */
#define TBCLGRP0            (0x2000u)  /* Timer B Compare latch load group 0 */
#define CNTL1               (0x1000u)  /* Counter lenght 1 */
#define CNTL0               (0x0800u)  /* Counter lenght 0 */
#define TBSSEL1             (0x0200u)  /* Clock source 1 */
#define TBSSEL0             (0x0100u)  /* Clock source 0 */
#define TBCLR               (0x0004u)  /* Timer B counter clear */
#define TBIE                (0x0002u)  /* Timer B interrupt enable */
#define TBIFG               (0x0001u)  /* Timer B interrupt flag */

#define SHR1                (0x4000u)  /* Timer B Compare latch load group 1 */
#define SHR0                (0x2000u)  /* Timer B Compare latch load group 0 */

#define TBSSEL_0            (0*0x0100u)  /* Clock Source: TBCLK */
#define TBSSEL_1            (1*0x0100u)  /* Clock Source: ACLK  */
#define TBSSEL_2            (2*0x0100u)  /* Clock Source: SMCLK */
#define TBSSEL_3            (3*0x0100u)  /* Clock Source: INCLK */
#define CNTL_0              (0*0x0800u)  /* Counter lenght: 16 bit */
#define CNTL_1              (1*0x0800u)  /* Counter lenght: 12 bit */
#define CNTL_2              (2*0x0800u)  /* Counter lenght: 10 bit */
#define CNTL_3              (3*0x0800u)  /* Counter lenght:  8 bit */
#define SHR_0               (0*0x2000u)  /* Timer B Group: 0 - individually */
#define SHR_1               (1*0x2000u)  /* Timer B Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define SHR_2               (2*0x2000u)  /* Timer B Group: 2 - 2 groups (1-3, 4-6)*/
#define SHR_3               (3*0x2000u)  /* Timer B Group: 3 - 1 group (all) */
#define TBCLGRP_0           (0*0x2000u)  /* Timer B Group: 0 - individually */
#define TBCLGRP_1           (1*0x2000u)  /* Timer B Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define TBCLGRP_2           (2*0x2000u)  /* Timer B Group: 2 - 2 groups (1-3, 4-6)*/
#define TBCLGRP_3           (3*0x2000u)  /* Timer B Group: 3 - 1 group (all) */

/* Additional Timer B Control Register bits are defined in Timer A */
#define CLLD1               (0x0400u)  /* Compare latch load source 1 */
#define CLLD0               (0x0200u)  /* Compare latch load source 0 */

#define SLSHR1              (0x0400u)  /* Compare latch load source 1 */
#define SLSHR0              (0x0200u)  /* Compare latch load source 0 */

#define SLSHR_0             (0*0x0200u)  /* Compare latch load sourec : 0 - immediate */
#define SLSHR_1             (1*0x0200u)  /* Compare latch load sourec : 1 - TBR counts to 0 */
#define SLSHR_2             (2*0x0200u)  /* Compare latch load sourec : 2 - up/down */
#define SLSHR_3             (3*0x0200u)  /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

#define CLLD_0              (0*0x0200u)  /* Compare latch load sourec : 0 - immediate */
#define CLLD_1              (1*0x0200u)  /* Compare latch load sourec : 1 - TBR counts to 0 */
#define CLLD_2              (2*0x0200u)  /* Compare latch load sourec : 2 - up/down */
#define CLLD_3              (3*0x0200u)  /* Compare latch load sourec : 3 - TBR counts to TBCTL0 */

/* TB7IV Definitions */
#define TBIV_NONE           (0x0000u)    /* No Interrupt pending */
#define TBIV_TBCCR1         (0x0002u)    /* TBCCR1_CCIFG */
#define TBIV_TBCCR2         (0x0004u)    /* TBCCR2_CCIFG */
#define TBIV_TBCCR3         (0x0006u)    /* TBCCR3_CCIFG */
#define TBIV_TBCCR4         (0x0008u)    /* TBCCR4_CCIFG */
#define TBIV_TBCCR5         (0x000Au)    /* TBCCR3_CCIFG */
#define TBIV_TBCCR6         (0x000Cu)    /* TBCCR4_CCIFG */
#define TBIV_TBIFG          (0x000Eu)    /* TBIFG */

/************************************************************
* Basic Clock Module
************************************************************/
#define __MSP430_HAS_BASIC_CLOCK__    /* Definition to show that Module is available */

#define DCOCTL_             (0x0056u)  /* DCO Clock Frequency Control */
DEFC(   DCOCTL            , DCOCTL_)
#define BCSCTL1_            (0x0057u)  /* Basic Clock System Control 1 */
DEFC(   BCSCTL1           , BCSCTL1_)
#define BCSCTL2_            (0x0058u)  /* Basic Clock System Control 2 */
DEFC(   BCSCTL2           , BCSCTL2_)

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
#define XT5V                (0x08)   /* XT5V should always be reset */
#define DIVA0               (0x10)   /* ACLK Divider 0 */
#define DIVA1               (0x20)   /* ACLK Divider 1 */
#define XTS                 (0x40)   /* LFXTCLK 0:Low Freq. / 1: High Freq. */
#define XT2OFF              (0x80)   /* Enable XT2CLK */

#define DIVA_0              (0x00)   /* ACLK Divider 0: /1 */
#define DIVA_1              (0x10)   /* ACLK Divider 1: /2 */
#define DIVA_2              (0x20)   /* ACLK Divider 2: /4 */
#define DIVA_3              (0x30)   /* ACLK Divider 3: /8 */

#define DCOR                (0x01)   /* Enable External Resistor : 1 */
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
* ADC12
************************************************************/
#define __MSP430_HAS_ADC12__          /* Definition to show that Module is available */

#define ADC12CTL0_          (0x01A0u)  /* ADC12 Control 0 */
DEFW(   ADC12CTL0         , ADC12CTL0_)
#define ADC12CTL1_          (0x01A2u)  /* ADC12 Control 1 */
DEFW(   ADC12CTL1         , ADC12CTL1_)
#define ADC12IFG_           (0x01A4u)  /* ADC12 Interrupt Flag */
DEFW(   ADC12IFG          , ADC12IFG_)
#define ADC12IE_            (0x01A6u)  /* ADC12 Interrupt Enable */
DEFW(   ADC12IE           , ADC12IE_)
#define ADC12IV_            (0x01A8u)  /* ADC12 Interrupt Vector Word */
DEFW(   ADC12IV           , ADC12IV_)

#define ADC12MEM_           (0x0140u)  /* ADC12 Conversion Memory */
#ifndef __IAR_SYSTEMS_ICC__
#define ADC12MEM            (ADC12MEM_) /* ADC12 Conversion Memory (for assembler) */
#else
#define ADC12MEM            ((int*) ADC12MEM_) /* ADC12 Conversion Memory (for C) */
#endif
#define ADC12MEM0_          (0x0140u)  /* ADC12 Conversion Memory 0 */
DEFW(   ADC12MEM0         , ADC12MEM0_)
#define ADC12MEM1_          (0x0142u)  /* ADC12 Conversion Memory 1 */
DEFW(   ADC12MEM1         , ADC12MEM1_)
#define ADC12MEM2_          (0x0144u)  /* ADC12 Conversion Memory 2 */
DEFW(   ADC12MEM2         , ADC12MEM2_)
#define ADC12MEM3_          (0x0146u)  /* ADC12 Conversion Memory 3 */
DEFW(   ADC12MEM3         , ADC12MEM3_)
#define ADC12MEM4_          (0x0148u)  /* ADC12 Conversion Memory 4 */
DEFW(   ADC12MEM4         , ADC12MEM4_)
#define ADC12MEM5_          (0x014Au)  /* ADC12 Conversion Memory 5 */
DEFW(   ADC12MEM5         , ADC12MEM5_)
#define ADC12MEM6_          (0x014Cu)  /* ADC12 Conversion Memory 6 */
DEFW(   ADC12MEM6         , ADC12MEM6_)
#define ADC12MEM7_          (0x014Eu)  /* ADC12 Conversion Memory 7 */
DEFW(   ADC12MEM7         , ADC12MEM7_)
#define ADC12MEM8_          (0x0150u)  /* ADC12 Conversion Memory 8 */
DEFW(   ADC12MEM8         , ADC12MEM8_)
#define ADC12MEM9_          (0x0152u)  /* ADC12 Conversion Memory 9 */
DEFW(   ADC12MEM9         , ADC12MEM9_)
#define ADC12MEM10_         (0x0154u)  /* ADC12 Conversion Memory 10 */
DEFW(   ADC12MEM10        , ADC12MEM10_)
#define ADC12MEM11_         (0x0156u)  /* ADC12 Conversion Memory 11 */
DEFW(   ADC12MEM11        , ADC12MEM11_)
#define ADC12MEM12_         (0x0158u)  /* ADC12 Conversion Memory 12 */
DEFW(   ADC12MEM12        , ADC12MEM12_)
#define ADC12MEM13_         (0x015Au)  /* ADC12 Conversion Memory 13 */
DEFW(   ADC12MEM13        , ADC12MEM13_)
#define ADC12MEM14_         (0x015Cu)  /* ADC12 Conversion Memory 14 */
DEFW(   ADC12MEM14        , ADC12MEM14_)
#define ADC12MEM15_         (0x015Eu)  /* ADC12 Conversion Memory 15 */
DEFW(   ADC12MEM15        , ADC12MEM15_)

#define ADC12MCTL_          (0x0080u)  /* ADC12 Memory Control */
#ifndef __IAR_SYSTEMS_ICC__
#define ADC12MCTL           (ADC12MCTL_) /* ADC12 Memory Control (for assembler) */
#else
#define ADC12MCTL           ((char*) ADC12MCTL_) /* ADC12 Memory Control (for C) */
#endif
#define ADC12MCTL0_         (0x0080u)  /* ADC12 Memory Control 0 */
DEFC(   ADC12MCTL0        , ADC12MCTL0_)
#define ADC12MCTL1_         (0x0081u)  /* ADC12 Memory Control 1 */
DEFC(   ADC12MCTL1        , ADC12MCTL1_)
#define ADC12MCTL2_         (0x0082u)  /* ADC12 Memory Control 2 */
DEFC(   ADC12MCTL2        , ADC12MCTL2_)
#define ADC12MCTL3_         (0x0083u)  /* ADC12 Memory Control 3 */
DEFC(   ADC12MCTL3        , ADC12MCTL3_)
#define ADC12MCTL4_         (0x0084u)  /* ADC12 Memory Control 4 */
DEFC(   ADC12MCTL4        , ADC12MCTL4_)
#define ADC12MCTL5_         (0x0085u)  /* ADC12 Memory Control 5 */
DEFC(   ADC12MCTL5        , ADC12MCTL5_)
#define ADC12MCTL6_         (0x0086u)  /* ADC12 Memory Control 6 */
DEFC(   ADC12MCTL6        , ADC12MCTL6_)
#define ADC12MCTL7_         (0x0087u)  /* ADC12 Memory Control 7 */
DEFC(   ADC12MCTL7        , ADC12MCTL7_)
#define ADC12MCTL8_         (0x0088u)  /* ADC12 Memory Control 8 */
DEFC(   ADC12MCTL8        , ADC12MCTL8_)
#define ADC12MCTL9_         (0x0089u)  /* ADC12 Memory Control 9 */
DEFC(   ADC12MCTL9        , ADC12MCTL9_)
#define ADC12MCTL10_        (0x008Au)  /* ADC12 Memory Control 10 */
DEFC(   ADC12MCTL10       , ADC12MCTL10_)
#define ADC12MCTL11_        (0x008Bu)  /* ADC12 Memory Control 11 */
DEFC(   ADC12MCTL11       , ADC12MCTL11_)
#define ADC12MCTL12_        (0x008Cu)  /* ADC12 Memory Control 12 */
DEFC(   ADC12MCTL12       , ADC12MCTL12_)
#define ADC12MCTL13_        (0x008Du)  /* ADC12 Memory Control 13 */
DEFC(   ADC12MCTL13       , ADC12MCTL13_)
#define ADC12MCTL14_        (0x008Eu)  /* ADC12 Memory Control 14 */
DEFC(   ADC12MCTL14       , ADC12MCTL14_)
#define ADC12MCTL15_        (0x008Fu)  /* ADC12 Memory Control 15 */
DEFC(   ADC12MCTL15       , ADC12MCTL15_)

/* ADC12CTL0 */
#define ADC12SC             (0x001)   /* ADC12 Start Conversion */
#define ENC                 (0x002)   /* ADC12 Enable Conversion */
#define ADC12TOVIE          (0x004)   /* ADC12 Timer Overflow interrupt enable */
#define ADC12OVIE           (0x008)   /* ADC12 Overflow interrupt enable */
#define ADC12ON             (0x010)   /* ADC12 On/enable */
#define REFON               (0x020)   /* ADC12 Reference on */
#define REF2_5V             (0x040)   /* ADC12 Ref 0:1.5V / 1:2.5V */
#define MSC                 (0x080)   /* ADC12 Multiple SampleConversion */
#define SHT00               (0x0100u)  /* ADC12 Sample Hold 0 Select 0 */
#define SHT01               (0x0200u)  /* ADC12 Sample Hold 0 Select 1 */
#define SHT02               (0x0400u)  /* ADC12 Sample Hold 0 Select 2 */
#define SHT03               (0x0800u)  /* ADC12 Sample Hold 0 Select 3 */
#define SHT10               (0x1000u)  /* ADC12 Sample Hold 0 Select 0 */
#define SHT11               (0x2000u)  /* ADC12 Sample Hold 1 Select 1 */
#define SHT12               (0x4000u)  /* ADC12 Sample Hold 2 Select 2 */
#define SHT13               (0x8000u)  /* ADC12 Sample Hold 3 Select 3 */
#define MSH                 (0x080)

#define SHT0_0               (0*0x100u) /* ADC12 Sample Hold 0 Select Bit: 0 */
#define SHT0_1               (1*0x100u) /* ADC12 Sample Hold 0 Select Bit: 1 */
#define SHT0_2               (2*0x100u) /* ADC12 Sample Hold 0 Select Bit: 2 */
#define SHT0_3               (3*0x100u) /* ADC12 Sample Hold 0 Select Bit: 3 */
#define SHT0_4               (4*0x100u) /* ADC12 Sample Hold 0 Select Bit: 4 */
#define SHT0_5               (5*0x100u) /* ADC12 Sample Hold 0 Select Bit: 5 */
#define SHT0_6               (6*0x100u) /* ADC12 Sample Hold 0 Select Bit: 6 */
#define SHT0_7               (7*0x100u) /* ADC12 Sample Hold 0 Select Bit: 7 */
#define SHT0_8               (8*0x100u) /* ADC12 Sample Hold 0 Select Bit: 8 */
#define SHT0_9               (9*0x100u) /* ADC12 Sample Hold 0 Select Bit: 9 */
#define SHT0_10             (10*0x100u) /* ADC12 Sample Hold 0 Select Bit: 10 */
#define SHT0_11             (11*0x100u) /* ADC12 Sample Hold 0 Select Bit: 11 */
#define SHT0_12             (12*0x100u) /* ADC12 Sample Hold 0 Select Bit: 12 */
#define SHT0_13             (13*0x100u) /* ADC12 Sample Hold 0 Select Bit: 13 */
#define SHT0_14             (14*0x100u) /* ADC12 Sample Hold 0 Select Bit: 14 */
#define SHT0_15             (15*0x100u) /* ADC12 Sample Hold 0 Select Bit: 15 */

#define SHT1_0               (0*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 0 */
#define SHT1_1               (1*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 1 */
#define SHT1_2               (2*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 2 */
#define SHT1_3               (3*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 3 */
#define SHT1_4               (4*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 4 */
#define SHT1_5               (5*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 5 */
#define SHT1_6               (6*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 6 */
#define SHT1_7               (7*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 7 */
#define SHT1_8               (8*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 8 */
#define SHT1_9               (9*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 9 */
#define SHT1_10             (10*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 10 */
#define SHT1_11             (11*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 11 */
#define SHT1_12             (12*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 12 */
#define SHT1_13             (13*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 13 */
#define SHT1_14             (14*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 14 */
#define SHT1_15             (15*0x1000u) /* ADC12 Sample Hold 1 Select Bit: 15 */

/* ADC12CTL1 */
#define ADC12BUSY           (0x0001u)    /* ADC12 Busy */
#define CONSEQ0             (0x0002u)    /* ADC12 Conversion Sequence Select 0 */
#define CONSEQ1             (0x0004u)    /* ADC12 Conversion Sequence Select 1 */
#define ADC12SSEL0          (0x0008u)    /* ADC12 Clock Source Select 0 */
#define ADC12SSEL1          (0x0010u)    /* ADC12 Clock Source Select 1 */
#define ADC12DIV0           (0x0020u)    /* ADC12 Clock Divider Select 0 */
#define ADC12DIV1           (0x0040u)    /* ADC12 Clock Divider Select 1 */
#define ADC12DIV2           (0x0080u)    /* ADC12 Clock Divider Select 2 */
#define ISSH                (0x0100u)    /* ADC12 Invert Sample Hold Signal */
#define SHP                 (0x0200u)    /* ADC12 Sample/Hold Pulse Mode */
#define SHS0                (0x0400u)    /* ADC12 Sample/Hold Source 0 */
#define SHS1                (0x0800u)    /* ADC12 Sample/Hold Source 1 */
#define CSTARTADD0          (0x1000u)    /* ADC12 Conversion Start Address 0 */
#define CSTARTADD1          (0x2000u)    /* ADC12 Conversion Start Address 1 */
#define CSTARTADD2          (0x4000u)    /* ADC12 Conversion Start Address 2 */
#define CSTARTADD3          (0x8000u)    /* ADC12 Conversion Start Address 3 */

#define CONSEQ_0             (0*2u)      /* ADC12 Conversion Sequence Select: 0 */
#define CONSEQ_1             (1*2u)      /* ADC12 Conversion Sequence Select: 1 */
#define CONSEQ_2             (2*2u)      /* ADC12 Conversion Sequence Select: 2 */
#define CONSEQ_3             (3*2u)      /* ADC12 Conversion Sequence Select: 3 */
#define ADC12SSEL_0          (0*8u)      /* ADC12 Clock Source Select: 0 */
#define ADC12SSEL_1          (1*8u)      /* ADC12 Clock Source Select: 1 */
#define ADC12SSEL_2          (2*8u)      /* ADC12 Clock Source Select: 2 */
#define ADC12SSEL_3          (3*8u)      /* ADC12 Clock Source Select: 3 */
#define ADC12DIV_0           (0*0x20u)   /* ADC12 Clock Divider Select: 0 */
#define ADC12DIV_1           (1*0x20u)   /* ADC12 Clock Divider Select: 1 */
#define ADC12DIV_2           (2*0x20u)   /* ADC12 Clock Divider Select: 2 */
#define ADC12DIV_3           (3*0x20u)   /* ADC12 Clock Divider Select: 3 */
#define ADC12DIV_4           (4*0x20u)   /* ADC12 Clock Divider Select: 4 */
#define ADC12DIV_5           (5*0x20u)   /* ADC12 Clock Divider Select: 5 */
#define ADC12DIV_6           (6*0x20u)   /* ADC12 Clock Divider Select: 6 */
#define ADC12DIV_7           (7*0x20u)   /* ADC12 Clock Divider Select: 7 */
#define SHS_0                (0*0x400u)  /* ADC12 Sample/Hold Source: 0 */
#define SHS_1                (1*0x400u)  /* ADC12 Sample/Hold Source: 1 */
#define SHS_2                (2*0x400u)  /* ADC12 Sample/Hold Source: 2 */
#define SHS_3                (3*0x400u)  /* ADC12 Sample/Hold Source: 3 */
#define CSTARTADD_0          (0*0x1000u) /* ADC12 Conversion Start Address: 0 */
#define CSTARTADD_1          (1*0x1000u) /* ADC12 Conversion Start Address: 1 */
#define CSTARTADD_2          (2*0x1000u) /* ADC12 Conversion Start Address: 2 */
#define CSTARTADD_3          (3*0x1000u) /* ADC12 Conversion Start Address: 3 */
#define CSTARTADD_4          (4*0x1000u) /* ADC12 Conversion Start Address: 4 */
#define CSTARTADD_5          (5*0x1000u) /* ADC12 Conversion Start Address: 5 */
#define CSTARTADD_6          (6*0x1000u) /* ADC12 Conversion Start Address: 6 */
#define CSTARTADD_7          (7*0x1000u) /* ADC12 Conversion Start Address: 7 */
#define CSTARTADD_8          (8*0x1000u) /* ADC12 Conversion Start Address: 8 */
#define CSTARTADD_9          (9*0x1000u) /* ADC12 Conversion Start Address: 9 */
#define CSTARTADD_10        (10*0x1000u) /* ADC12 Conversion Start Address: 10 */
#define CSTARTADD_11        (11*0x1000u) /* ADC12 Conversion Start Address: 11 */
#define CSTARTADD_12        (12*0x1000u) /* ADC12 Conversion Start Address: 12 */
#define CSTARTADD_13        (13*0x1000u) /* ADC12 Conversion Start Address: 13 */
#define CSTARTADD_14        (14*0x1000u) /* ADC12 Conversion Start Address: 14 */
#define CSTARTADD_15        (15*0x1000u) /* ADC12 Conversion Start Address: 15 */

/* ADC12MCTLx */
#define INCH0               (0x0001u)    /* ADC12 Input Channel Select Bit 0 */
#define INCH1               (0x0002u)    /* ADC12 Input Channel Select Bit 1 */
#define INCH2               (0x0004u)    /* ADC12 Input Channel Select Bit 2 */
#define INCH3               (0x0008u)    /* ADC12 Input Channel Select Bit 3 */
#define SREF0               (0x0010u)    /* ADC12 Select Reference Bit 0 */
#define SREF1               (0x0020u)    /* ADC12 Select Reference Bit 1 */
#define SREF2               (0x0040u)    /* ADC12 Select Reference Bit 2 */
#define EOS                 (0x0080u)    /* ADC12 End of Sequence */

#define INCH_0               (0)        /* ADC12 Input Channel 0 */
#define INCH_1               (1)        /* ADC12 Input Channel 1 */
#define INCH_2               (2)        /* ADC12 Input Channel 2 */
#define INCH_3               (3)        /* ADC12 Input Channel 3 */
#define INCH_4               (4)        /* ADC12 Input Channel 4 */
#define INCH_5               (5)        /* ADC12 Input Channel 5 */
#define INCH_6               (6)        /* ADC12 Input Channel 6 */
#define INCH_7               (7)        /* ADC12 Input Channel 7 */
#define INCH_8               (8)        /* ADC12 Input Channel 8 */
#define INCH_9               (9)        /* ADC12 Input Channel 9 */
#define INCH_10             (10)        /* ADC12 Input Channel 10 */
#define INCH_11             (11)        /* ADC12 Input Channel 11 */
#define INCH_12             (12)        /* ADC12 Input Channel 12 */
#define INCH_13             (13)        /* ADC12 Input Channel 13 */
#define INCH_14             (14)        /* ADC12 Input Channel 14 */
#define INCH_15             (15)        /* ADC12 Input Channel 15 */

#define SREF_0               (0*0x10u)   /* ADC12 Select Reference 0 */
#define SREF_1               (1*0x10u)   /* ADC12 Select Reference 1 */
#define SREF_2               (2*0x10u)   /* ADC12 Select Reference 2 */
#define SREF_3               (3*0x10u)   /* ADC12 Select Reference 3 */
#define SREF_4               (4*0x10u)   /* ADC12 Select Reference 4 */
#define SREF_5               (5*0x10u)   /* ADC12 Select Reference 5 */
#define SREF_6               (6*0x10u)   /* ADC12 Select Reference 6 */
#define SREF_7               (7*0x10u)   /* ADC12 Select Reference 7 */

/* ADC12IV Definitions */
#define ADC12IV_NONE        (0x0000u)    /* No Interrupt pending */
#define ADC12IV_ADC12OVIFG  (0x0002u)    /* ADC12OVIFG */
#define ADC12IV_ADC12TOVIFG (0x0004u)    /* ADC12TOVIFG */
#define ADC12IV_ADC12IFG0   (0x0006u)    /* ADC12IFG0 */
#define ADC12IV_ADC12IFG1   (0x0008u)    /* ADC12IFG1 */
#define ADC12IV_ADC12IFG2   (0x000Au)    /* ADC12IFG2 */
#define ADC12IV_ADC12IFG3   (0x000Cu)    /* ADC12IFG3 */
#define ADC12IV_ADC12IFG4   (0x000Eu)    /* ADC12IFG4 */
#define ADC12IV_ADC12IFG5   (0x0010u)    /* ADC12IFG5 */
#define ADC12IV_ADC12IFG6   (0x0012u)    /* ADC12IFG6 */
#define ADC12IV_ADC12IFG7   (0x0014u)    /* ADC12IFG7 */
#define ADC12IV_ADC12IFG8   (0x0016u)    /* ADC12IFG8 */
#define ADC12IV_ADC12IFG9   (0x0018u)    /* ADC12IFG9 */
#define ADC12IV_ADC12IFG10  (0x001Au)    /* ADC12IFG10 */
#define ADC12IV_ADC12IFG11  (0x001Cu)    /* ADC12IFG11 */
#define ADC12IV_ADC12IFG12  (0x001Eu)    /* ADC12IFG12 */
#define ADC12IV_ADC12IFG13  (0x0020u)    /* ADC12IFG13 */
#define ADC12IV_ADC12IFG14  (0x0022u)    /* ADC12IFG14 */
#define ADC12IV_ADC12IFG15  (0x0024u)    /* ADC12IFG15 */

/************************************************************
* Interrupt Vectors (offset from 0xFFE0)
************************************************************/

#define PORT2_VECTOR        (1 * 2u)  /* 0xFFE2 Port 2 */
#define USART1TX_VECTOR     (2 * 2u)  /* 0xFFE4 USART 1 Transmit */
#define USART1RX_VECTOR     (3 * 2u)  /* 0xFFE6 USART 1 Receive */
#define PORT1_VECTOR        (4 * 2u)  /* 0xFFE8 Port 1 */
#define TIMERA1_VECTOR      (5 * 2u)  /* 0xFFEA Timer A CC1-2, TA */
#define TIMERA0_VECTOR      (6 * 2u)  /* 0xFFEC Timer A CC0 */
#define ADC12_VECTOR          (7 * 2u)  /* 0xFFEE ADC */
#define USART0TX_VECTOR     (8 * 2u)  /* 0xFFF0 USART 0 Transmit */
#define USART0RX_VECTOR     (9 * 2u)  /* 0xFFF2 USART 0 Receive */
#define WDT_VECTOR          (10 * 2u) /* 0xFFF4 Watchdog Timer */
#define COMPARATORA_VECTOR  (11 * 2u) /* 0xFFF6 Comparator A */
#define TIMERB1_VECTOR      (12 * 2u) /* 0xFFF8 Timer B CC1-6, TB */
#define TIMERB0_VECTOR      (13 * 2u) /* 0xFFFA Timer B CC0 */
#define NMI_VECTOR          (14 * 2u) /* 0xFFFC Non-maskable */
#define RESET_VECTOR        (15 * 2u) /* 0xFFFE Reset [Highest Priority] */

#define UART1TX_VECTOR      USART1TX_VECTOR
#define UART1RX_VECTOR      USART1RX_VECTOR
#define UART0TX_VECTOR      USART0TX_VECTOR
#define UART0RX_VECTOR      USART0RX_VECTOR
#define ADC_VECTOR          ADC12_VECTOR

/************************************************************
* End of Modules
************************************************************/
#pragma language=default

#endif /* #ifndef __msp430x14x */

