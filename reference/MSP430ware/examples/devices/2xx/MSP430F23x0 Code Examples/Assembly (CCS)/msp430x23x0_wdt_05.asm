;*******************************************************************************
;   MSP430F23x0 Demo - Reset on Invalid Address fetch, Toggle P1.0
;
;   Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop that
;   ends with TAR loaded with 3FFFh - op-code for "jmp $" This simulates a code
;   error. The MSP430F23x0 will force a reset because it will not allow a fetch
;   from within the address range of the peripheral memory, as is seen by
;   return to the mainloop and LED flash.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
;
;                MSP430F23x0
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x23x0.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #450h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
            mov.w   #03FFFh,&TAR            ; "jmp $"
                                            ;
Mainloop    xor.b   #001h,&P1OUT            ; Toggle P1.0
Wait        mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            mov.w   #0170h,PC               ; Invalid fetch
            jmp     Mainloop                ; ** Should never get here **
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; RESET Vector
            .short  RESET                   ;
            .end
