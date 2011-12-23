;******************************************************************************
;   MSP-FET430P430 Demo - Software Toggle P5.1
;
;   Description: Toggle P5.1 by xor'ing P5.1 inside of a software loop.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430FG439
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;   M. Buccini / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Esssentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;-----------------------------------------------------------------------------
            .text                  ; Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #002h,&P5DIR            ; P5.1 output
                                            ;			
Mainloop    xor.b   #002h,&P5OUT            ; Toggle P5.1
Wait        mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect     ".reset"              ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
