;******************************************************************************
;  MSP430F54xA Demo - Software Poll P1.4, Set P1.0 if P1.4 = 1
;
;  Description: Poll P1.4 in a loop, if hi P1.0 is set, if low, P1.0 reset.
;  ACLK = n/a, MCLK = SMCLK = default DCO
;
;              MSP430F5438A
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;     /|\   |                 |
;      --o--|P1.4         P1.0|-->LED
;     \|/
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 
;******************************************************************************

    .cdecls C,LIST,"msp430x54xA.h"

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            bis.b   #BIT0,&P1DIR            ; Set P1.0 to output direction

while_loop  bit.b   #BIT4,&P1IN             ; P1.4 (In) == 1?
            jnc     turn_off_LED
turn_on_LED bis.b   #BIT0,&P1OUT            ; Yes -> set P1.0 (LED)
            jmp     while_loop 
turn_off_LED 
            bic.b   #BIT0,&P1OUT            ; No  -> reset P1.0 (LED)
            jmp     while_loop 

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
