;******************************************************************************
;   MSP430x24x Demo - SVS, POR @ 2.5V Vcc
;
;   Description: The SVS POR feature is used to disable normal operation that
;   toggles P1.0 by xor'ing P1.0 inside of a software loop.
;   In the example, when VCC is above 2.5V, the MSP430 toggles P1.0. When VCC is
;   below 2.5V, the SVS resets the MSP430, and no toggle is seen.
;   ACLK= n/a, MCLK= SMCLK= default DCO ~ 1.045MHz
;
;                 MSP430x24x
;              -----------------
;          /|\|              XIN|-
;           | |                 |
;           --|RST          XOUT|-
;             |                 |
;             |             P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0  output
            mov.b   #060h+PORON,&SVSCTL     ; SVS POR enabled @ 2.5V
                                            ;
Mainloop    mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset
            .short    RESET
            .end

