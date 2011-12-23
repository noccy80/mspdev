;******************************************************************************
;   MSP430F54xA Demo - Write a byte to Port 1
;
;   Description: Writes a byte(0xFF) to Port 1 and stays in LPM4 mode
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430F5438A
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |             P1.x|-->HI
;            |                 |
;            |                 |
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
            mov.b   #0xFF,&P1DIR            ; Set P1.x to output direction
            mov.b   #0xFF,&P1OUT            ; Set all P1 pins HI

            bis.w   #LPM4 + GIE,SR          ; Enter LPM4, enable interrupts
            nop                             ; For debugger
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end


