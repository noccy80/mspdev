;******************************************************************************
;   MSP430F54xA Demo - Software Toggle P1.0 at Default DCO
;
;   Description: Toggle P1.0 by xor'ing P1.0 inside of a software loop.
;   ACLK is rought out on pin P11.0, SMCLK is brought out on P11.2, and MCLK
;   is brought out on pin P11.1.
;   ACLK = REFO = 32.768kHz, MCLK = SMCLK = (Default DCO)/2 = (2MHz/2) = 1MHz
;
;                 MSP430F5438A
;             -----------------
;         /|\|                 |
;          | |            P11.0|-->ACLK
;          --|RST         P11.1|-->MCLK
;            |            P11.2|-->SMCLK
;            |                 |
;            |             P1.0|-->LED
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
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            bis.b   #BIT0,&P1DIR            ; P1.0 output
            bis.b   #0x07,&P11DIR           ; ACLK, MCLK, SMCLK set out to pins
            bis.b   #0x07,&P11SEL           ; P11.0, 1, 2 for debugging purposes

while_loop  xor.b   #BIT0,&P1OUT            ; Flash the LED
            mov.w   #50000,R4               ; Initialize loop counter R4 = 50,000
delay_loop  dec.w   R4                      ; Decrement loop counter
            jne     delay_loop              ; Loop if loop counter > 0        
            jmp     while_loop              ; Infinite while loop
            
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
