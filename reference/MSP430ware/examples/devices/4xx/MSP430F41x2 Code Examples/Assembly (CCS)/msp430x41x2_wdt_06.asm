;*******************************************************************************
;   MSP430x41x2 Demo - WDT+ Failsafe Clock, 32kHz ACLK
;
;   Description; Allow WDT+ in watchdog to timeout sourced by ACLK. LPM3 is
;   entered, this example will demonstrate WDT+ feature by automatically
;   re-enabling WDT+ clock source as DCO if external XTAL fails. This can be
;   seen as a continued, though faster as clocked by DCO, watchdog timeout
;   which will toggle on P1.0 in main function.
;   ACLK = 32kHz, MCLK = SMCLK = default DCO ~1.045MHz
;
;              MSP430F41x2
;              -----------------
;          /|\|              XIN|-
;           | |                 | 32kHz
;           --|RST          XOUT|-
;             |                 |
;             |             P5.1|-->LED
;
;  P. Thanigai
;  Texas Instruments Inc.
;  January 2009
;  Built with CCE Version: 3.1   
;******************************************************************************
 .cdecls C,LIST, "msp430x41x2.h" 
 
            .global _main
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
_main
RESET       mov.w   #0400h,SP               ; Initialize stack pointer
SetupWDT    mov.w   #WDT_ARST_1000,&WDTCTL  ; Set Watchdog Timer timeout 1s
            bis.b   #002h,&P5DIR            ; P5.1 output
            xor.b   #002h,&P5OUT            ; Toggle P5.1
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3
            nop                             ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	            ; MSP430 RESET Vector
            .short  RESET					;
            .end
