;*******************************************************************************
;   MSP430F23x0 Demo - WDT+ Failsafe Clock, DCO SMCLK
;
;   Description; Allow WDT+ in watchdog to timeout. Toggle P1.0 in main
;   function. LPM4 is entered, this example will demonstrate WDT+ feature
;   of preventing WDT+ clock to be disabled.
;   The WDT+ will not allow active WDT+ clock to be disabled by software, the
;   LED continues to Flash because the WDT times out normally even though
;   software has attempted to disable WDT+ clock source.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
;
;                MSP430F23x0
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x23x0.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #450h,SP         ; Initialize stackpointer
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
            xor.b   #001h,&P1OUT            ; Toggle P1.0
Mainloop    bis.w   #LPM4+GIE,SR            ; Disable all clocks
            nop                             ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; RESET Vector
            .short  RESET                   ;
            .end
