;******************************************************************************
;   MSP430x21x1 Demo - WDT+ Failsafe Clock, DCO SMCLK
;
;   Description: Allow WDT+ in watchdog mode to timeout. Toggle P1.0 in main
;   function. LPM4 is entered, this example will demonstrate WDT+ feature
;   of preventing WDT+ clock from being disabled. The MSP430F2xx will not
;   allow active WDT+ clock to be disabled by software. The LED continues to
;   Flash even though software has attempted to disable WDT+ clock source.
;   In contrast, an MSP430F1xx device will stop code execution when software
;   disables WDT clock source.
;   ACLK = n/a, MCLK = SMCLK = default DCO~ 1.16MHz
;
;                 MSP430F21x1
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;   M. Buccini / A. Dannenberg
;   Texas Instruments, Inc
;   July 2004
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x21x1.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       bis.b   #001h,&P1DIR            ; P1.0 output
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            bis.w   #LPM4,SR                ; Disable all clocks
Mainloop    jmp     Mainloop
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect ".reset"                  ; MSP430 RESET Vector
            .short  RESET
            .end
