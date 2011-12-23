;******************************************************************************
;   MSP-FET430P120 Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
;
;   Description: Buffer ACLK on P2.0, default SMCLK(DCO) on P1.4 and MCLK/10 on
;   P1.1.  To measure SMCLK on P1.4 with the FET, use "Release JTAG on run"
;   in the debugger to have access to the port. Then run the code.
;   ACLK = LFXT1 = 32768, MCLK = SMCLK = default DCO ~ 800kHz
;   //* External watch crystal on XIN XOUT is required for ACLK *//	
;
;               MSP430F123(2)
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32k
;          --|RST          XOUT|-
;            |                 |
;            |             P1.4|-->SMCLK~ 800kHz
;            |             P1.1|-->MCLK/12 = DCO/12
;            |             P2.0|-->ACLK = 32kHz
;
;   M. Buccini / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            bis.b   #012h,&P1DIR            ; P1.1,4 output direction
            bis.b   #010h,&P1SEL            ; P1.4 = SMCLK
            bis.b   #001h,&P2DIR            ; P2.0 output direction
            bis.b   #001h,&P2SEL            ; P2.0 = ACLK
                                            ;
Mainloop    bis.b   #002h,&P1OUT            ; P1.1 = 1
            bic.b   #002h,&P1OUT            ; P1.1 = 0
            jmp     Mainloop                ; Repeat
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
