;*******************************************************************************
;   MSP430F23x0 Demo - WDT+ Failsafe Clock, 32kHz ACLK
;
;   Description; Allow WDT+ in watchdog to timeout sourced by ACLK. LPM3 is
;   entered, this example will demonstrate WDT+ feature by automatically
;   re-enabling WDT+ clock source as DCO if external XTAL fails. This can be
;   seen as a continued, though faster as clocked by DCO, watchdog timeout
;   which will toggle on P1.0 in main function.
;   ACLK = 32kHz, MCLK = SMCLK = default DCO ~1.2MHz
;
;                 MSP430F23x0
;              -----------------
;          /|\|              XIN|-
;           | |                 | 32kHz
;           --|RST          XOUT|-
;             |                 |
;             |             P1.0|-->LED
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
SetupWDT    mov.w   #WDT_ARST_1000,&WDTCTL  ; Set Watchdog Timer timeout 1s
            bis.b   #001h,&P1DIR            ; P1.0 output
            xor.b   #001h,&P1OUT            ; Toggle P1.0
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3
            nop                             ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; RESET Vector
            .short  RESET                   ;
            .end
