;*******************************************************************************
;   MSP430F21x2 Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
;
;   Description: Buffer ACLK on P2.0, SMCLK(DCO) on P2.1 and MCLK/10 on
;   P2.2.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = CALxxx_8MHZ = 8MHz
;   //* External watch crystal on XIN XOUT is required for ACLK *//
;
;               MSP430F21x2
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P2.0|-->ACLK = 32kHz
;            |             P2.1|-->SMCLK = 8MHz
;            |             P2.2|-->MCLK/10 = DCO/10
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
 			.text							;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupDCO    mov.b   &CALBC1_8MHZ,&BCSCTL1   ; Set DCO to 8MHz
            mov.b   &CALDCO_8MHZ,&DCOCTL    ;
SetupP2     bis.b   #007h,&P2DIR            ; P2.0,1,2 output direction
            bis.b   #003h,&P2SEL            ; P2.0 = ACLK, P2.1 = SMCLK
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
