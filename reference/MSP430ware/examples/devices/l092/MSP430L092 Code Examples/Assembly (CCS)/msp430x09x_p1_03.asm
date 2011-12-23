;******************************************************************************
;  MSP430x09x Demo - Poll P1 With Software with Internal Pull-up
;
;  Description: Poll P1.3 in a loop, if hi P1.0 is set, if low, P1.0 reset.
;  Internal pullup enabled on P1.3.
;  ACLK = n/a, MCLK = SMCLK = default DCO
;
;               MSP430x09x
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;     /|\   |      R          |
;      --o--| P1.3-o      P1.0|-->Output
;     \|/
;
;  D.Dang/D.Archbold/D.Szmulewicz
;  Texas Instruments Inc.
;  Built with CCS version 4.2.0
;******************************************************************************

 .cdecls C,LIST,"msp430x09x.h"
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main
RESET       mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT  
            bis.b   #BIT0,&P1DIR            ; P1.0 output, else input
            bis.b   #BIT3,&P1OUT            ; P1.3 pullup
            bis.b   #BIT3,&P1REN            ; P1.3 pullup
loop        bit.b   #BIT3,&P1IN             ; P1.3 (In) == 1?
            jnc     clear 
            bis.b   #BIT0,&P1OUT            ; Yes -> set P1.0 
            jmp     loop 
clear       bic.b   #BIT0,&P1OUT            ; No  -> reset P1.0 
            jmp     loop 
           
        
           .end