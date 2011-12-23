;*******************************************************************************
;   MSP430F41x2 Demo - WDT+ Failsafe Clock, DCO SMCLK
;
;   Description; Allow WDT+ in watchdog to timeout. Toggle P5.1 in main
;   function. LPM4 is entered, this example will demonstrate WDT+ feature
;   of preventing WDT+ clock to be disabled.
;   The WDT+ will not allow active WDT+ clock to be disabled by software, the
;   LED continues to Flash because the WDT times out normally even though
;   software has attempted to disable WDT+ clock source.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~1.045MHz
;
;              MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
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
SetupP1     bis.b   #002h,&P5DIR            ; P5.1 output
            xor.b   #002h,&P5OUT            ; Toggle P5.1
Mainloop    bis.w   #LPM4+GIE,SR            ; Disable all clocks
            nop                             ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	            ; MSP430 RESET Vector
            .short  RESET					;
            .end
