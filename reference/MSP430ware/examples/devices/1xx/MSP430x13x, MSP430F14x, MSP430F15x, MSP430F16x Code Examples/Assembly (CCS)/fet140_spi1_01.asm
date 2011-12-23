;******************************************************************************
;   MSP-FET430P140 Demo - USART1, SPI Interface to TLC549 8-Bit ADC
;
;   Description: This program demonstrate a USART1 in SPI mode interface to a
;   TLC549 8-bit ADC. If AIN > 0.5(REF+ - REF-), P1.0 set, else reset.
;   R15 = 8-bit ADC code.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~ 800k, UCLK1 = SMCLK/2
;   //* VCC must be at least 3v for TLC549 *//
;
;                             MSP430F149
;                         -----------------
;                     /|\|              XIN|-
;          TLC549      | |                 |
;      -------------   --|RST          XOUT|-
;     |           CS|<---|P5.0             |
;     |      DATAOUT|--->|P5.2/SOMI        |
;   ~>| IN+  I/O CLK|<---|P5.3/UCLK1       |
;
;   M. Buccini / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupP5     bis.b   #0Ch,&P5SEL             ; P5.2,3 SPI option select
            bis.b   #09h,&P5DIR             ; P5.3,0 output direction
SetupSPI1   bis.b   #USPIE1,&ME2            ; Enable USART1 SPI
            bis.b   #CKPH+SSEL1+SSEL0+STC,&UTCTL1 ; SMCLK, 3-pin
            bis.b   #CHAR+SYNC+MM,&UCTL1    ; 8-bit SPI Master
            mov.b   #02h,&UBR01             ; SMCLK/2 for baud rate
            clr.b   &UBR11                  ; SMCLK/2 for baud rate
            clr.b   &UMCTL1                 ; Clear modulation
            bic.b   #SWRST,&UCTL1           ; **Initialize USART state machine**
                                            ;
Mainloop    bic.b   #01h,&P5OUT             ; Enable TLC549, /CS reset
            mov.b   #00h,&TXBUF1            ; Dummy write to start SPI
L1          bit.b   #URXIFG1,&IFG2          ; RXBUF ready?
            jnc     L1                      ; 1 = ready
            mov.b   &RXBUF1,R15             ; R15 = 00|DATA
            bis.b   #01h,&P5OUT             ; Disable TLC549, /CS .set
            bic.b   #01h,&P1OUT             ; P1.0 = 0
            cmp.b   #07Fh,R15               ; R15 = AIN > 0.5(REF+ - REF-)?
            jlo     Mainloop                ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Mainloop                ; Again
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
             .sect   ".reset"                ; POR, ext. Reset, Watchdog, Flash
             .short  RESET                   ;
             .end

