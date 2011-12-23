;******************************************************************************
;  MSP430F54xA Demo - Timer_A3, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
;
;  Description: Toggle P1.0 using software and the TA_1 ISR. Timer1_A is
;  configured for up mode, thus the timer overflows when TAR counts
;  to CCR0. In this example, CCR0 is loaded with 1000-1.
;  Toggle rate = 32768/(2*1000) = 16.384
;  ACLK = TACLK = 32768Hz, MCLK = SMCLK = default DCO ~1.045MHz
;
;           MSP430F5438A
;         ---------------
;     /|\|               |
;      | |               |
;      --|RST            |
;        |               |
;        |           P1.0|-->LED
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
            bis.b   #BIT0,&P1DIR            ; P1.0 output
            mov.w   #CCIE,&TA1CCTL0         ; CCR0 interrupt enabled
            mov.w   #1000-1,&TA1CCR0
            mov.w   #TASSEL_1 + MC_1 + TACLR,&TA1CTL
                                            ; ACLK, upmode, clear TAR

            bis.w   #LPM3 + GIE,SR          ; Enter LPM3, enable interrupts
            nop
            
;-------------------------------------------------------------------------------
TIMER1_A0_ISR
;-------------------------------------------------------------------------------
            xor.b   #0x01,&P1OUT            ; Toggle P1.0
            nop                              ; Set breakpoint here 
            reti                            ; Return from interrupt 

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int49"    
            .short  TIMER1_A0_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end