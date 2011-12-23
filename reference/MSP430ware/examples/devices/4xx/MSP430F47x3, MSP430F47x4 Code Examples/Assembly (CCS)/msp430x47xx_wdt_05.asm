;*******************************************************************************
;    MSP430x47xx Demo - Reset on Invalid Address fetch, Toggle P5.1
;
;   Description: Toggle P5.1 by xor'ing P5.1 inside of a software loop that
;   ends with TAR loaded with 3FFFh - op-code for "jmp $" This simulates a code
;   error.  MSP430x47xx will force a reset because it will not allow a fetch
;   from within the address range of the peripheral memory, as is seen by
;   return to the mainloop and LED flash.
;
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                 MSP430x47xx
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
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
SetupP1     bis.b   #BIT1,&P5DIR            ; P5.1 output
            mov.w   #03FFFh,&TAR            ; "jmp $"
                                            ;				
Mainloop    xor.b   #BIT1,&P5OUT            ; Toggle P5.1
Wait        mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            mov     #0170h,PC               ; Invalid fetch
            jmp     $                       ; Program end                                         
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"            	; MSP430 RESET Vector
            .short  RESET                   ;       
            .end
