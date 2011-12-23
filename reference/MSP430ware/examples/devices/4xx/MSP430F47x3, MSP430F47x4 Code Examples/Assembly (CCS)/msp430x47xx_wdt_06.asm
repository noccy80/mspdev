;*******************************************************************************
;   MSP430x47xx Demo - WDT+ Failsafe Clock, 32kHz ACLK
;
;   Description; Allow WDT+ in watchdog to timeout sourced by ACLK. LPM3 is
;   entered, this example will demonstrate WDT+ feature by automatically
;   re-enabling WDT+ clock source as DCO if external XTAL fails. This can be
;   seen as a continued, though faster as clocked by DCO, watchdog timeout
;   which will toggle on P5.1 in main function.
;   ACLK = 32kHz, MCLK = SMCLK = default DCO
;
; 		  MSP430x47xx
;              -----------------
;          /|\|              XIN|-
;           | |                 | 32kHz
;           --|RST          XOUT|-
;             |                 |
;             |             P5.1|-->LED
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
SetupWDT    mov.w   #WDT_ARST_1000,&WDTCTL  ; Set Watchdog Timer timeout 1s
            bis.b   #BIT1,&P5DIR            ; P5.1 output
            xor.b   #BIT1,&P5OUT            ; Toggle P5.1
            bis.w   #LPM3,SR                ;
Mainloop    jmp     $
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"            	; MSP430 RESET Vector
            .short  RESET                   ;       
            .end

