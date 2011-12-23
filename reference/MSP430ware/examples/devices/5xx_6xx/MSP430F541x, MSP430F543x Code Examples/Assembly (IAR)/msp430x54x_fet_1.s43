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
;   W. Goh
;   Texas Instruments, Inc
;   July 2009
;   Built with IAR Embedded Workbench Version: 4.20
;*******************************************************************************
#include  "msp430x54x.h"
;-------------------------------------------------------------------------------
            ORG     0FC00h                  ; Progam Start (1K Flash device)
;-------------------------------------------------------------------------------
RESET       mov.w   #05C00h,SP              ; Set stackpointer (128B RAM device)
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
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
            ORG     0FFFEh                  ; MSP430 RESET Vector
            DW      RESET                   ;
            END
