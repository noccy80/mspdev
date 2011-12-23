;*******************************************************************************
;   MSP430x24x Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
;
;   Description: Buffer ACLK on P2.0, SMCLK(DCO) on P2.1 and MCLK/10 on
;   P2.2.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = CALxxx_8MHZ = 8MHz
;   //* External watch crystal on XIN XOUT is required for ACLK *//
;
;               MSP430F249
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P5.6|-->ACLK = 32kHz
;            |             P5.5|-->SMCLK = 8MHz
;            |             P5.4|-->MCLK = DCO
;            |             P5.3|-->MCLK/10
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
CheckCal    cmp.b   #0FFh,&CALBC1_8MHZ      ; Calibration constants erased?
            jeq     Trap
            cmp.b   #0FFh,&CALDCO_8MHZ
            jne     Load  
Trap        jmp     $                       ; Trap CPU!!
Load        mov.b   &CALBC1_8MHZ,&BCSCTL1   ; Set DCO to 8MHz
            mov.b   &CALDCO_8MHZ,&DCOCTL    ; 
SetupP5     bis.b   #078h,&P5DIR            ; P5.6,5,4,3 outputs
            bis.b   #070h,&P5SEL            ; P5.6,5,4 options
                                            ;
Mainloop    bis.b   #008h,&P5OUT            ; P5.3 = 1
            bic.b   #008h,&P5OUT            ; P5.3 = 0
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"            ; POR, ext. Reset
            .short  RESET
            .end
