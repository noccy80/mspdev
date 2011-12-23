;*******************************************************************************
;   MSP430F21x2 Demo - Software Poll P1.3, Set P1.0 if P1.3 = 1
;
;   Description: Poll P1.3 in a loop, if hi P1.0 is set, if low, P1.0 reset.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430F21x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;      /|\   |                 |
;       --o--|P1.3         P1.0|-->LED
;      \|/
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
 			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP      		    ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
                                            ;
Mainloop    bit.b   #008h,&P1IN             ; P1.3 hi/low?
            jc      ON                      ; jmp--> P1.3 is set
                                            ;
OFF         bic.b   #001h,&P1OUT            ; P1.0 = 0 / LED OFF
            jmp     Mainloop                ;
ON          bis.b   #001h,&P1OUT            ; P1.0 = 1 / LED ON
            jmp     Mainloop                ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	            ; MSP430 RESET Vector
            .short	RESET                   ;
            .end  
