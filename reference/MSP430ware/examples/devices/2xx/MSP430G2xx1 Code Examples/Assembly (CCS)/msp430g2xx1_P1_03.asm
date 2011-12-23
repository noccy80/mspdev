;*******************************************************************************
;   MSP430G2xx1 Demo - Poll P1 With Software with Internal Pull-up
;
;   Description: Poll P1.4 in a loop, if hi P1.0 is set, if low, P1.0 reset.
;   Internal pullup enabled on P1.4.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430G2xx1
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;      /|\   |      R          |
;       --o--| P1.4-o      P1.0|-->LED
;      \|/
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2231.h"

;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     mov.b   #001h,&P1DIR            ; P1.0 output, else input
            mov.b   #010h,&P1OUT            ; P1.4 set, else reset
            bis.b   #010h,&P1REN            ; P1.4 pullup

Mainloop    bit.b   #010h,&P1IN             ; P1.4 hi/low?
            jc      ON                      ; jmp--> P1.4 is set
                                            ;
OFF         bic.b   #001h,&P1OUT            ; P1.0 = 0 / LED OFF
            jmp     Mainloop                ;
ON          bis.b   #001h,&P1OUT            ; P1.0 = 1 / LED ON
            jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end

