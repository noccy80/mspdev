;*******************************************************************************
;    MSP430x47xx - WDT+ Failsafe Clock, DCO SMCLK
;
;   Description; Allow WDT+ in watchdog to timeout. Toggle P5.1 in main
;   funnction. LPM4 is entered, this example will demonstrate WDT+ feature
;   of preventing WDT+ clock to be disabled.
;   The WDT+ will not allow active WDT+ to be disabled by software even though
;   the LED continues to Flash because the WDT times out normally even though
;   software has attempted to disable WDT+ clock source.
;   The MSP430x47xx will stop code execution when software disables WDT+ clock
;   source.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                 MSP430x47xx
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x47x4.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900h,SP         ; Initialize stackpointer
            bis.b   #BIT1,&P5DIR            ; P5.1 output
            xor.b   #BIT1,&P5OUT            ; Toggle P5.1
            bis.w   #LPM4,SR                ; Disable all clocks
            jmp     $
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"            	; MSP430 RESET Vector
            .short  RESET                   ;       
            .end
