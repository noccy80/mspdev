;*******************************************************************************
;   MSP430x54x Demo - Software Toggle P1.0
;
;   Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                 MSP430F5438
;              -----------------
;          /|\|              XIN|-
;           | |                 |
;           --|RST          XOUT|-
;             |                 |
;             |             P1.0|-->LED
;
;   M. Morales
;   Texas Instruments, Inc
;   July 2009
;   Built with IAR Embedded Workbench Version: 4.20
;*******************************************************************************
    
    .cdecls C,LIST,"msp430x54x.h"

;-------------------------------------------------------------------------------
value       .equ    R4 
;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; Set P1.0 to output direction
                                            ;
Mainloop    xor.b   #001h,&P1OUT            ; Toggle P1.0
Wait        mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
