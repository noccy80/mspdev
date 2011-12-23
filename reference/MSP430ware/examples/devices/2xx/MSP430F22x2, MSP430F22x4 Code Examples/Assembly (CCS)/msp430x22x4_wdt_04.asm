;*******************************************************************************
;   MSP430F22x4 Demo - WDT+ Failsafe Clock, DCO SMCLK
;
;   Description; Allow WDT+ in watchdog to timeout. Toggle P1.0 in main
;   function. LPM4 is entered, this example will demonstrate WDT+ feature
;   of preventing WDT+ clock to be disabled.
;   The WDT+ will not allow active WDT+ clock to be disabled by software, the
;   LED continues to Flash because the WDT times out normally even though
;   software has attempted to disable WDT+ clock source.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
;
;                MSP430F22x4  
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
                              
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
            xor.b   #001h,&P1OUT            ; Toggle P1.0
Mainloop    bis.w   #LPM4+GIE,SR            ; Disable all clocks
            jmp     $                       ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ; 
            .end
