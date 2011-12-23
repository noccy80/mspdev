;******************************************************************************
;   MSP430F54x Demo - WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
;
;  Description: Toggle P1.0 using software timed by WDT ISR. Toggle rate is
;  exactly 250ms based on 32kHz ACLK WDT clock source. In this example the
;  WDT is configured to divide 32768 watch-crystal(2^15) by 2^13 with an ISR
;  triggered @ 4Hz = [WDT CLK source/32768].
;  ACLK = REFO , MCLK = SMCLK = default DCO ~1.045MHz
;
;
;                MSP430F5438
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;            |             P1.0|-->LED
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
            mov.w   #WDT_ADLY_250,&WDTCTL   ; WDT 250ms, ACLK, interval timer
            bis.w   #WDTIE,&SFRIE1          ; Enable WDT interrupt
            bis.b   #BIT0,&P1DIR            ; Set P1.0 to output direction

            bis.w   #LPM3 + GIE,SR          ; Enter LPM3 w/interrupts enabled
            nop                             ; For debugger
            
;-------------------------------------------------------------------------------
WDT_ISR
;-------------------------------------------------------------------------------
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0 using exclusive-OR
            nop                             ; Set breakpoint here 
            reti                            ; Return from interrupt 

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int58"    
            .short  WDT_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end

