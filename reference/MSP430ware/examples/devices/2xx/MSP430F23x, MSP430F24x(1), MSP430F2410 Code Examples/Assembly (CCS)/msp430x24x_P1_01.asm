;******************************************************************************
;   MSP430x24x Demo - Software Poll P1.4, Set P1.0 if P1.4 = 1
;
;   Description: Poll P1.4 in a loop, if HI, P1.0 is set, if LOW, P1.0 reset.
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430x249
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;      /|\   |                 |
;       --o--|P1.4         P1.0|-->LED
;      \|/
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
SetupP5     bis.b   #BIT0,&P1DIR            ; P1.0 output
                                            ;				          			
Mainloop    bit.b   #010h,&P1IN             ; P1.4 hi/low?
            jc      ON                      ; jmp--> P1.4 is set
                                            ;
OFF         bic.b   #BIT0,&P1OUT            ; P1.0 = 0 / LED OFF
            jmp     Mainloop                ;
ON          bis.b   #BIT0,&P1OUT            ; P1.0 = 1 / LED ON
            jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset
            .short    RESET
            .end