;*******************************************************************************
;   MSP430F23x0 Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
;
;   Description: Buffer ACLK on P2.0, SMCLK(DCO) on P1.4 and MCLK/10 on
;   P2.2.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = CALxxx_8MHZ = 8MHz
;   //* External watch crystal on XIN XOUT is required for ACLK *//
;
;               MSP430F23x0
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P2.0|-->ACLK = 32kHz
;            |             P1.4|-->SMCLK = 8MHz
;            |             P2.2|-->MCLK/10 = DCO/10
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x23x0.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #450h,SP         ; Initialize stackpointer 
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
CheckCal    cmp.b   #0FFh,&CALBC1_8MHZ      ; Calibration constants erased?
            jeq     Trap
            cmp.b   #0FFh,&CALDCO_8MHZ
            jne     Load  
Trap        jmp     $                       ; Trap CPU!!
Load        mov.b   &CALBC1_8MHZ,&BCSCTL1   ; Set DCO to 8MHz
            mov.b   &CALDCO_8MHZ,&DCOCTL    ; 
SetupP1     bis.b   #010h,&P1DIR            ; P1.4 output direction
            bis.b   #010h,&P1SEL            ; P1.4 = SMCLK
SetupP2     bis.b   #005h,&P2DIR            ; P2.0,2 output direction
            bis.b   #001h,&P2SEL            ; P2.0 = ACLK
                                            ;
Mainloop    bis.b   #004h,&P2OUT            ; P2.2 = 1
            bic.b   #004h,&P2OUT            ; P2.2 = 0
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset
            .short	RESET
            .end
