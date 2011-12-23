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
* MSP430x12x2 devices.
*
* Texas Instruments, Version 2.4
*
* Rev. 1.1, Defined vectors for USART (in addition to UART)
* Rev. 1.2, Added USART special function labels (UxME, UxIE, UxIFG)
* Rev. 2.1, Alignment of defintions in Users Guide and of version numbers
* Rev. 2.2, Removed unused def of TASSEL2
* Rev. 2.3, added definitions for Interrupt Vectors xxIV
* Rev. 2.4, Fixed typo in ADC10: SREF3 -> SREF2
*
********************************************************************/

#ifndef __msp430x12x2
#define __msp430x12x2

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
#define U0IE                   IE2            /* UART0 Interrupt Enable Register */
#define URXIE0                 (0x01)
#define UTXIE0                 (0x02)

SFR_8BIT(IFG2);                               /* Interrupt Flag 2 */
#define U0IFG                  IFG2           /* UART0 Interrupt Flag Register */
#define URXIFG0                (0x01)
#define UTXIFG0                (0x02)

SFR_8BIT(ME2);                                /* Module Enable 2 */
#define U0ME                   ME2            /* UART0 Module Enable Register */
#define URXE0                  (0x01)
#define UTXE0                  (0x02)
#define USPIE0                 (0x01)

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
* DIGITAL I/O Port3
************************************************************/
#define __MSP430_HAS_PORT3__                  /* Definition to show that Module is available */

SFR_8BIT(P3IN);                               /* Port 3 Input */
SFR_8BIT(P3OUT);                              /* Port 3 Output */
SFR_8BIT(P3DIR);                              /* Port 3 Direction */
SFR_8BIT(P3SEL);                              /* Port 3 Selection */

/************************************************************
* USART
************************************************************/

/* UxCTL */
#define PENA                   (0x80)         /* Parity enable */
#define PEV                    (0x40)         /* Parity 0:odd / 1:even */
#define SPB                    (0x20)         /* Stop Bits 0:one / 1: two */
#define CHAR                   (0x10)         /* Data 0:7-bits / 1:8-bits */
#define LISTEN                 (0x08)         /* Listen mode */
#define SYNC                   (0x04)         /* UART / SPI mode */
#define MM                     (0x02)         /* Master Mode off/on */
#define SWRST                  (0x01)         /* USART Software Reset */

/* UxTCTL */
#define CKPH                   (0x80)         /* SPI: Clock Phase */
#define CKPL                   (0x40)         /* Clock Polarity */
#define SSEL1                  (0x20)         /* Clock Source Select 1 */
#define SSEL0                  (0x10)         /* Clock Source Select 0 */
#define URXSE                  (0x08)         /* Receive Start edge select */
#define TXWAKE                 (0x04)         /* TX Wake up mode */
#define STC                    (0x02)         /* SPI: STC enable 0:on / 1:off */
#define TXEPT                  (0x01)         /* TX Buffer empty */

/* UxRCTL */
#define FE                     (0x80)         /* Frame Error */
#define PE                     (0x40)         /* Parity Error */
#define OE                     (0x20)         /* Overrun Error */
#define BRK                    (0x10)         /* Break detected */
#define URXEIE                 (0x08)         /* RX Error interrupt enable */
#define URXWIE                 (0x04)         /* RX Wake up interrupt enable */
#define RXWAKE                 (0x02)         /* RX Wake up detect */
#define RXERR                  (0x01)         /* RX Error Error */

/************************************************************
* USART 0
************************************************************/
#define __MSP430_HAS_UART0__                  /* Definition to show that Module is available */

SFR_8BIT(U0CTL);                              /* USART 0 Control */
SFR_8BIT(U0TCTL);                             /* USART 0 Transmit Control */
SFR_8BIT(U0RCTL);                             /* USART 0 Receive Control */
SFR_8BIT(U0MCTL);                             /* USART 0 Modulation Control */
SFR_8BIT(U0BR0);                              /* USART 0 Baud Rate 0 */
SFR_8BIT(U0BR1);                              /* USART 0 Baud Rate 1 */
SFR_8BIT(U0RXBUF);                            /* USART 0 Receive Buffer */
SFR_8BIT(U0TXBUF);                            /* USART 0 Transmit Buffer */

/* Alternate register names */

#define UCTL0                  U0CTL          /* USART 0 Control */
#define UTCTL0                 U0TCTL         /* USART 0 Transmit Control */
#define URCTL0                 U0RCTL         /* USART 0 Receive Control */
#define UMCTL0                 U0MCTL         /* USART 0 Modulation Control */
#define UBR00                  U0BR0          /* USART 0 Baud Rate 0 */
#define UBR10                  U0BR1          /* USART 0 Baud Rate 1 */
#define RXBUF0                 U0RXBUF        /* USART 0 Receive Buffer */
#define TXBUF0                 U0TXBUF        /* USART 0 Transmit Buffer */
#define UCTL0_                 U0CTL_         /* USART 0 Control */
#define UTCTL0_                U0TCTL_        /* USART 0 Transmit Control */
#define URCTL0_                U0RCTL_        /* USART 0 Receive Control */
#define UMCTL0_                U0MCTL_        /* USART 0 Modulation Control */
#define UBR00_                 U0BR0_         /* USART 0 Baud Rate 0 */
#define UBR10_                 U0BR1_         /* USART 0 Baud Rate 1 */
#define RXBUF0_                U0RXBUF_       /* USART 0 Receive Buffer */
#define TXBUF0_                U0TXBUF_       /* USART 0 Transmit Buffer */
#define UCTL_0                 U0CTL          /* USART 0 Control */
#define UTCTL_0                U0TCTL         /* USART 0 Transmit Control */
#define URCTL_0                U0RCTL         /* USART 0 Receive Control */
#define UMCTL_0                U0MCTL         /* USART 0 Modulation Control */
#define UBR0_0                 U0BR0          /* USART 0 Baud Rate 0 */
#define UBR1_0                 U0BR1          /* USART 0 Baud Rate 1 */
#define RXBUF_0                U0RXBUF        /* USART 0 Receive Buffer */
#define TXBUF_0                U0TXBUF        /* USART 0 Transmit Buffer */
#define UCTL_0_                U0CTL_         /* USART 0 Control */
#define UTCTL_0_               U0TCTL_        /* USART 0 Transmit Control */
#define URCTL_0_               U0RCTL_        /* USART 0 Receive Control */
#define UMCTL_0_               U0MCTL_        /* USART 0 Modulation Control */
#define UBR0_0_                U0BR0_         /* USART 0 Baud Rate 0 */
#define UBR1_0_                U0BR1_         /* USART 0 Baud Rate 1 */
#define RXBUF_0_               U0RXBUF_       /* USART 0 Receive Buffer */
#define TXBUF_0_               U0TXBUF_       /* USART 0 Transmit Buffer */

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
* Basic Clock Module
************************************************************/
#define __MSP430_HAS_BASIC_CLOCK__                /* Definition to show that Module is available */

SFR_8BIT(DCOCTL);                             /* DCO Clock Frequency Control */
SFR_8BIT(BCSCTL1);                            /* Basic Clock System Control 1 */
SFR_8BIT(BCSCTL2);                            /* Basic Clock System Control 2 */

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
#define XT5V                   (0x08)         /* XT5V should always be reset */
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
* ADC10
************************************************************/
#define __MSP430_HAS_ADC10__                  /* Definition to show that Module is available */

SFR_8BIT(ADC10DTC0);                          /* ADC10 Data Transfer Control 0 */
SFR_8BIT(ADC10DTC1);                          /* ADC10 Data Transfer Control 1 */
SFR_8BIT(ADC10AE);                            /* ADC10 Analog Enable */

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
#define SHS_1                  (1*0x400u)     /* TA3 OUT1 */
#define SHS_2                  (2*0x400u)     /* TA3 OUT0 */
#define SHS_3                  (3*0x400u)     /* TA3 OUT2 */

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

/* ADC10AE */
#define ADC10AE0               (0x0001)       /* ADC10 External Input Enable 0 */
#define ADC10AE1               (0x0002)       /* ADC10 External Input Enable 1 */
#define ADC10AE2               (0x0004)       /* ADC10 External Input Enable 2 */
#define ADC10AE3               (0x0008)       /* ADC10 External Input Enable 3 */
#define ADC10AE4               (0x0010)       /* ADC10 External Input Enable 4 */
#define ADC10AE5               (0x0020)       /* ADC10 External Input Enable 5 */
#define ADC10AE6               (0x0040)       /* ADC10 External Input Enable 6 */
#define ADC10AE7               (0x0080)       /* ADC10 External Input Enable 7 */

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
#define PORT1_VECTOR            ".int02"                    /* 0xFFE4 Port 1 */
#else
#define PORT1_VECTOR            (2 * 1u)                     /* 0xFFE4 Port 1 */
/*#define PORT1_ISR(func)         ISR_VECTOR(func, ".int02")  */ /* 0xFFE4 Port 1 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define PORT2_VECTOR            ".int03"                    /* 0xFFE6 Port 2 */
#else
#define PORT2_VECTOR            (3 * 1u)                     /* 0xFFE6 Port 2 */
/*#define PORT2_ISR(func)         ISR_VECTOR(func, ".int03")  */ /* 0xFFE6 Port 2 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define ADC10_VECTOR            ".int05"                    /* 0xFFEA ADC10 */
#else
#define ADC10_VECTOR            (5 * 1u)                     /* 0xFFEA ADC10 */
/*#define ADC10_ISR(func)         ISR_VECTOR(func, ".int05")  */ /* 0xFFEA ADC10 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USART0TX_VECTOR         ".int06"                    /* 0xFFEC USART 0 Transmit */
#else
#define USART0TX_VECTOR         (6 * 1u)                     /* 0xFFEC USART 0 Transmit */
/*#define USART0TX_ISR(func)      ISR_VECTOR(func, ".int06")  */ /* 0xFFEC USART 0 Transmit */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define USART0RX_VECTOR         ".int07"                    /* 0xFFEE USART 0 Receive */
#else
#define USART0RX_VECTOR         (7 * 1u)                     /* 0xFFEE USART 0 Receive */
/*#define USART0RX_ISR(func)      ISR_VECTOR(func, ".int07")  */ /* 0xFFEE USART 0 Receive */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERA1_VECTOR          ".int08"                    /* 0xFFF0 Timer A CC1-2, TA */
#else
#define TIMERA1_VECTOR          (8 * 1u)                     /* 0xFFF0 Timer A CC1-2, TA */
/*#define TIMERA1_ISR(func)       ISR_VECTOR(func, ".int08")  */ /* 0xFFF0 Timer A CC1-2, TA */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define TIMERA0_VECTOR          ".int09"                    /* 0xFFF2 Timer A CC0 */
#else
#define TIMERA0_VECTOR          (9 * 1u)                     /* 0xFFF2 Timer A CC0 */
/*#define TIMERA0_ISR(func)       ISR_VECTOR(func, ".int09")  */ /* 0xFFF2 Timer A CC0 */ /* CCE V2 Style */
#endif
#ifdef __ASM_HEADER__ /* Begin #defines for assembler */
#define WDT_VECTOR              ".int10"                    /* 0xFFF4 Watchdog Timer */
#else
#define WDT_VECTOR              (10 * 1u)                    /* 0xFFF4 Watchdog Timer */
/*#define WDT_ISR(func)           ISR_VECTOR(func, ".int10")  */ /* 0xFFF4 Watchdog Timer */ /* CCE V2 Style */
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

#endif /* #ifndef __msp430x12x2 */

