;******************************************************************************
;  MSP430F66xx Demo - WDT+ Failsafe Clock, WDT mode, DCO SMCLK
;
;  Description; Allow WDT+ in watchdog mode to timeout. Toggle P1.0 in main
;  function. LPM4 is entered, this example will demonstrate WDT+ feature
;  of preventing WDT+ clock to be disabled.
;  The WDT+ will not allow active WDT+ clock to be disabled by software, the
;  LED continues to Flash because the WDT times out normally (in 32768 DCOCLK
;  cycles) even though software has attempted to disable WDT+ clock source.
;  ACLK = n/a, MCLK = SMCLK = default DCO ~1.045MHz
;
;                MSP430F6638
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;            |             P1.0|-->LED
;
;   Priya Thanigai
;   Texas Instruments Inc.
;   August 2011
;   Built with CCS V5
;******************************************************************************
            .cdecls C,LIST,"msp430f6638.h"

;-------------------------------------------------------------------------------
            .global _main
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x63FE,SP              ; Initialize stackpointer
            bis.b   #BIT0,&P1DIR            ; Set P1.0 to output - SET BREAKPOINT HERE
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0
            
            bis.w   #LPM4 + GIE,SR          ; Stop all clocks
            nop                             ; For debugger
            
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
            
