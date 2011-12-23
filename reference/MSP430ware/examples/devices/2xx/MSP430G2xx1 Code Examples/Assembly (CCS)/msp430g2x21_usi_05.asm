;*******************************************************************************
;   MSP430G2x21/G2x31 Demo - USI SPI Interface to TLC549 8-bit ADC
;
;   Description: This program demonstrate a USI in SPI mode interface to a
;   TLC549 8-bit ADC. If AIN > 0.5(REF+ - REF-), P1.0 set, else reset.
;   ACLK = n/a, MCLK = SMCLK = default DCO, UCICLK = SMCLK/4
;   //** VCC must be at least 3v for TLC549 **//
;
;                          MSP430G2x21/G2x31
;                       -----------------
;                   /|\|              XIN|-
;        TLC549      | |                 |
;    -------------   --|RST          XOUT|-
;   |           CS|<---|P1.1             |
;   |      DATAOUT|--->|P1.7/SOMI    P1.0|-->LED
; ~>|AIN   I/O CLK|<---|P1.5/UCLK0       |
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2221.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP1     clr.b   &P1OUT                  ;
            bis.b   #03h,&P1DIR             ; P1.0/1 output direction

SetupUSI    bis.b   #USIPE7+USIPE5+USIMST+USIOE,&USICTL0; Port, SPI master
            bis.b   #USIIE,&USICTL1         ; Counter interrupt, flag remains
            mov.b   #USIDIV_2+USISSEL_2,&USICKCTL    ; /4 SMCLK
            bic.b   #USISWRST,&USICTL0      ; Enable USI
            mov.b   #08h,&USICNT            ; init-load counter, clears flag
                                            ;
Mainloop    bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
USI_ISR  ;
;-------------------------------------------------------------------------------
            bis.b   #02h,&P1OUT             ; Disable TLC549
            cmp.b   #07Fh,&USISRL           ;
            bic.b   #01h,&P1OUT             ;
            jlo     USI_ISR1                ;
            bis.b   #01h,&P1OUT             ;
USI_ISR1    bic.b   #02h,&P1OUT             ; Enable TLC549
            mov.b   #08h,&USICNT            ; re-load counter
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int04"                ; USI Vector
            .short  USI_ISR                 ;        
            .end