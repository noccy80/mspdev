;******************************************************************************
;   MSP430FG479 Demo - Software Toggle P4.6
;
;   Description: Toggle P4.6 by xor'ing P4.6 inside of a software loop.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430FG479
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P4.6|-->LED
;
;   P.Thanigai
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials Version: 3.0
;******************************************************************************
 .cdecls C,LIST, "msp430xG47x.h" 

;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP4     bis.b   #040h,&P4DIR            ; P4.6 output
                                            ;			
Mainloop    xor.b   #040h,&P4OUT            ; Toggle P4.6
Wait        mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;  
            .end
