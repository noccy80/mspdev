;******************************************************************************
;  MSP430F54x Demo - Timer_B, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
;
;  Description: Toggle P1.0 using software and TB_1 ISR. Timer_B is
;  configured for up mode, thus the timer overflows when TBR counts
;  to CCR0. In this example, CCR0 is loaded with 50000.
;  ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~1.045MHz
;
;           MSP430F5438
;         ---------------
;     /|\|               |
;      | |               |
;      --|RST            |
;        |               |
;        |           P1.0|-->LED
;
;   M. Morales
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials v3.x
;******************************************************************************

    .cdecls C,LIST,"msp430x54x.h"

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            bis.b   #0x01,&P1DIR            ; P1.0 output
            mov.w   #CCIE,&TBCCTL0          ; CCR0 interrupt enabled
            mov.w   #50000,&TBCCR0
            mov.w   #TBSSEL_2 + MC_1 + TBCLR,&TBCTL
                                            ; SMCLK, upmode, clear TBR
            bis.w   #LPM0 + GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; For debugger

;-------------------------------------------------------------------------------
TIMERB0_ISR
;-------------------------------------------------------------------------------
            xor.b   #0x01,&P1OUT            ; Toggle P1.0
            reti                            ; Return from interrupt 

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int60"     
            .short  TIMERB0_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end