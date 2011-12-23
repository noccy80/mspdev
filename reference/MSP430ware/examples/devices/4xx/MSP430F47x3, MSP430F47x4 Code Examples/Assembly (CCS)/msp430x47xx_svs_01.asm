;******************************************************************************
;   MSP430x47xx Demo - SVS, POR @ 2.5V Vcc
;
;   Description: The SVS POR feature is used to disable normal operation that
;   toggles P5.1 by xor'ing P5.1 inside of a software loop.
;   In the example, when VCC is above 2.5V, the MSP430 toggles P5.1. When VCC is
;   below 2.5V, the SVS resets the MSP430, and no toggle is seen.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430x47xx
;              -----------------
;          /|\|              XIN|-
;           | |                 |
;           --|RST          XOUT|-
;             |                 |
;             |             P5.1|-->LED
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
RESET       mov.w   #850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP5     bis.b   #BIT1,&P5DIR            ; P5.1  output
            mov.b   #060h+PORON,&SVSCTL     ; SVS POR enabled @ 2.5V
                                            ;
Mainloop    mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            xor.b   #BIT1,&P5OUT            ; Toggle P5.1
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect     ".reset"            	; RESET Vector
            .short   RESET                  ;
            .end