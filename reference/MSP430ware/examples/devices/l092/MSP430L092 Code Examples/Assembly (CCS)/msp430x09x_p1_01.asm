;******************************************************************************
;  MSP430x09x Demo - Software Poll P1.3, Set P1.0 if P1.3 = 1
;
;  Description: Poll P1.3 in a loop, if hi P1.0 is set, if low, P1.0 reset.
;  ACLK = n/a, MCLK = SMCLK = default DCO
;
;               MSP430x09x
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;     /|\   |                 |
;      --o--|P1.3         P1.0|-->Output
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
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT  
            bis.b   #BIT0,&P1DIR            ; Set P1.0 to output direction
while_loop  bit.b   #BIT3,&P1IN             ; P1.3 (In) == 1?
            jnc     turn_off
            bis.b   #BIT0,&P1OUT            ; Yes -> set P1.0 
            jmp     while_loop 
turn_off    bic.b   #BIT0,&P1OUT            ; No  -> reset P1.0 
            jmp     while_loop 

           .end