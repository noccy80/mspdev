;******************************************************************************
;   MSP-FET430P430 Demo - SVS, POR @ 2.5V Vcc
;
;   Description: The SVS POR feature is used to disable normal operation that
;   toggles P5.1 by xor'ing P5.1 inside of a software loop.
;   In the example, when VCC is above 2.5V, the MSP430 toggles P5.1. When VCC is
;   below 2.5V, the SVS resets the MSP430, and no toggle is seen.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                 MSP430FG439
;              -----------------
;          /|\|              XIN|-
;           | |                 |
;           --|RST          XOUT|-
;             |                 |
;             |             P5.1|-->LED
;
;   M. Buccini / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;------------------------------------------------------------------------------
            .text                  ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP5     bis.b   #002h,&P5DIR            ; P5.1  output
            mov.b   #060h+PORON,&SVSCTL     ; SVS POR enabled @ 2.5V
                                            ;
Mainloop    mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            xor.b   #002h,&P5OUT            ; Toggle P5.1
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end
