;******************************************************************************
;  MSP430F66xx Demo - WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
;
;  Description: Toggle P1.0 using software timed by the WDT ISR. Toggle rate
;  is approximately 30ms = {(default DCO 1.045MHz) / 32768} based on default
;  DCO/SMCLK clock source used in this example for the WDT.
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
            mov.w   #WDT_MDLY_32,&WDTCTL    ; WDT 32ms, SMCLK, interval timer
            bis.w   #WDTIE,&SFRIE1          ; Enable WDT interrupt
            bis.b   #BIT0,&P1DIR            ; Set P1.0 to output direction

            bis.w   #LPM0 + GIE,SR          ; Enter LPM0, enable interrupts 
            nop                             ; For debugger

;-------------------------------------------------------------------------------
WDT_ISR
;-------------------------------------------------------------------------------
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0 (LED)
            nop                             ; Set breakpoint here 
            reti                            ; Return from interrupt 

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int57"                ; ADC12 isr vector
            .short  WDT_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
            
