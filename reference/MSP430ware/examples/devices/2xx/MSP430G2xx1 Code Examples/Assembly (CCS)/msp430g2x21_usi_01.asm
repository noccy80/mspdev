;*******************************************************************************
;   MSP430G2x21/G2x31 Demo - USICNT Used as a One-Shot Timer Function, DCO SMCLK
;
;   Description: USI conunter is used as a one-shot timer. The USI
;   conunter ISR toggles P1.0 using software. As coded ACLK is pre-divided by
;   128 and the USICNT loaded with 32, for a total divided of 4096 or
;   12-bits. USICNT must be reloaded after each interrupt which also clears
;   interrupt flag.
;   ACLK = VLO, MCLK = SMCLK = default DCO
;
; 		         MSP430G2x21/G2x31
;              -----------------
;          /|\|              XIN|-
;           | |                 |
;           --|RST          XOUT|-
;             |                 |
;             |             P1.0|-->LED
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
SetupP1     bis.b   #01h,&P1DIR             ; P1.1 output direction

SetupBC     bis.b   #LFXT1S_2,&BCSCTL1      ; ACLK = VL0
SetupUSI    bis.b   #USIMST,&USICTL0        ; SPI master
            bis.b   #USIIE,&USICTL1         ; Counter interrupt, flag remains
            mov.b   #USIDIV_7+USISSEL_1,&USICKCTL    ; /128 ACLK
            bic.b   #USISWRST,&USICTL0      ; Enable USI
            mov.b   #08h,&USICNT            ; init-load counter
                                            ;
Mainloop    bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
USI_ISR  ;
;-------------------------------------------------------------------------------
            xor.b   #01h,&P1OUT             ; Toggle P1.0
            bis.b   #01Fh,&USICNT           ; re-load counter
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