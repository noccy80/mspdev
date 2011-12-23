;*******************************************************************************
;   MSP430x11x1 Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
;
;   Description: Buffer ACLK on P2.0, default SMCLK(DCO) on P1.4 and MCLK/10 on
;   P1.1. To measure SMCLK on P1.4 with the FET, use "Release JTAG on Run"
;   in the debugger to have access to the port. Then run the code.
;   ACLK = LFXT1 = 32768, MCLK = SMCLK = default DCO ~800k
;   ;* External watch crystal installed on XIN XOUT is required for ACLK *//	
;
;                MSP430F1121
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |       P1.4/SMCLK|-->SMCLK = ~800kHz
;            |             P1.1|-->MCLK/10 = DCO/10
;            |        P2.0/ACLK|-->ACLK = 32kHz
;
;   M. Buccini / Z. Albus
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"
;-------------------------------------------------------------------------------
            .text                           ; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupPx     bis.b   #012h,&P1DIR            ; P1.1,4 output direction
            bis.b   #010h,&P1SEL            ; P1.4 = SMCLK
            bis.b   #001h,&P2DIR            ; P2.0 output direction
            bis.b   #001h,&P2SEL            ; P2.0 = ACLK
                                            ;
Mainloop    bis.b   #002h,&P1OUT            ; P1.1 = 1
            bic.b   #002h,&P1OUT            ; P1.1 = 0
            jmp     Mainloop                ; Repeat
                                            ;
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
