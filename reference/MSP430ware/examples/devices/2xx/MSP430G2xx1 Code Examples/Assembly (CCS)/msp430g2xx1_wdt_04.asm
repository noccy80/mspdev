;*******************************************************************************
;   MSP430G2xx1 Demo - WDT+ Failsafe Clock, DCO SMCLK
;
;   Description; Allow WDT+ in watchdog to timeout. Toggle P1.0 in main
;   funnction. LPM4 is entered, this example will demonstrate WDT+ feature
;   of preventing WDT+ clock to be disabled.
;   The WD+ will not allow active WDT+ to be disabled by software, the
;   The WDT+ will not allow active WDT+ to be disabled by software even though
;   the LED continues to Flash because the WDT times out normally even though
;   software has attempted to disable WDT+ clock source.
;   The MSP430F1xx will stop code execution when software disables WDT+ clock
;   source.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430G2xx1
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
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
            bis.b   #001h,&P1DIR            ; P1.0 output
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            bis.w   #LPM4,SR                ; Disable all clocks
Mainloop    jmp     $
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;     
            .end
