;*******************************************************************************
;   MSP430G2xx1 Demo - Reset on Invalid Address fetch, Toggle P1.0
;
;   Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop that
;   ends with TAR loaded with 3FFFh - op-code for "jmp $" This simulates a code
;   error. The MSP430F2xx will force a reset because it will not allow a fetch
;   from within the address range of the peripheral memory, as is seen by
;   return to the mainloop and LED flash.
;   In contrast, an MSP430F1xx device will "jmp $" stopping code execution with
;   no LED flash.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430G2xx1
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2231.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
            mov.w   #03FFFh,&TAR            ; "jmp $"
                                            ;				
Mainloop    xor.b   #001h,&P1OUT            ; Toggle P1.0
Wait        mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            mov     #0170h,PC               ; Invalid fetch
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;        
            .end
