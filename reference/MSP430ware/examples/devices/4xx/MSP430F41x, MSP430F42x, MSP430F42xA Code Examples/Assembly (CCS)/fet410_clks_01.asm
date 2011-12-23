;******************************************************************************
;   MSP-FET430P410 Demo - FLL+, Output MCLK, ACLK Using 32kHz XTAL and DCO
;
;   Description: This program outputs buffered MCLK and ACLK on port pins
;   P1.1 and P1.5.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   ;* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                 MSP430F413
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |        P1.1/MCLK|-->MCLK = 1048576Hz
;            |        P1.5/ACLK|-->ACLK = 32768Hz
;
;   M. Buccini / S. Karthikeyan
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials  Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x41x.h"
;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
SetupP1     bis.b   #022h,&P1DIR            ; P1.1 and P1.5 output direction
            bis.b   #022h,&P1SEL            ; P1.1 and P1.5 option select
                                            ;				          							
Mainloop    jmp     Mainloop                ;
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect     ".reset"                  ; RESET Vector
            .short  RESET                   ;
            .end
