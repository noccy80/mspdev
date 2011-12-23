;******************************************************************************
;   MSP430x47xx Demo - Software Toggle P5.1
;
;   Description: Toggle P5.1 by xor'ing P5.1 inside of a software loop.
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                 MSP430x47xx
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;            |             P5.1|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x47x4.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP5     bis.b   #BIT1,&P5DIR            ; P5.1 output
                                            ;			
Mainloop    xor.b   #BIT1,&P5OUT            ; Toggle P5.1
Wait        mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            ; RESET Vector
            .short  RESET                   ;
            .end
