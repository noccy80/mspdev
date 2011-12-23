;******************************************************************************
;   MSP430F54xA Demo - 16x16 Signed Multiply
;
;   Description: Hardware multiplier is used to multiply two numbers.
;   The calculation is automatically initiated after the second operand is
;   loaded. Results are stored in RESLO, RESHI and SUMEXT = FFFF if result is
;   negative, SUMEXT = 0 otherwise. Result is also stored as Result variable.
;
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;               MSP430F5438A
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
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
;-------------------------------------------------------------------------------
            .bss    multiplier,2 
            .bss    operand,2 
            .bss    result,4 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            mov.w   #0x1234,&multiplier     ; Initialize program variables
            mov.w   #-6578,&operand 
            mov.w   &multiplier,&MPYS       ; Load first operand -signed mult
            mov.w   &operand,&OP2           ; Load second operand
            mov.w   #result,R4              ; Move base address of result into R4
            mov.w   &RESHI,2(R4)            ; Move RESHI into upper word of result
            mov.w   &RESLO,0(R4)            ; Move RESLO into lower word of result
           
            bis.w   #LPM4,SR                ; Enter LPM4
            nop                             ; For debugger

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end


