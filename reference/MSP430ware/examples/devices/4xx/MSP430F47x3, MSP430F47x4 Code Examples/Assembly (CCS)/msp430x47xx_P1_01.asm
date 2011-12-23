;******************************************************************************
;   MSP430x47xx Demo - Software Poll P1.4, Set P5.1 if P1.4 = 1
;
;   Description: Poll P1.4 in a loop, if HI, P5.1 is set, if LOW, P5.1 reset.
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430x47xx
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;      /|\   |                 |
;       --o--|P1.4         P5.1|-->LED
;      \|/
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
Mainloop    bit.b   #BIT4,&P1IN             ; P1.4 hi/low?
            jc      ON                      ; jmp--> P1.4 is set
                                            ;
OFF         bic.b   #BIT1,&P5OUT            ; P5.1 = 0 / LED OFF
            jmp     Mainloop                ;
ON          bis.b   #BIT1,&P5OUT            ; P5.1 = 1 / LED ON
            jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            	; MSP430 RESET Vector
            .short  RESET                   ;
            .end
    