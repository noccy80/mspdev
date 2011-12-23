;*******************************************************************************
;   MSP430G2xx1 Demo - WDT+ Failsafe Clock, 32kHz ACLK
;
;   Description; Allow WDT+ in watchdog to timeout sourced by ACLK. LPM3 is
;   entered, this example will demonstrate WDT+ feature by automatically
;   re-enabling WDT+ clock source as DCO if external XTAL fails. This can be
;   seen as a continued, though faster as clocked by DCO, watchdog timeout
;   which will toggle on P1.0 in main function.
;   ACLK = 32kHz, MCLK = SMCLK = default DCO
;
; 		            MSP430G2xx1
;              -----------------
;          /|\|              XIN|-
;           | |                 | 32kHz
;           --|RST          XOUT|-
;             |                 |
;             |             P1.0|-->LED
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2231.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
SetupWDT    mov.w   #WDT_ARST_1000,&WDTCTL  ; Set Watchdog Timer timeout 1s
            bis.b   #001h,&P1DIR            ; P1.0 output
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            bis.w   #LPM3,SR                ;
Mainloop    jmp     $
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;       
            .end
