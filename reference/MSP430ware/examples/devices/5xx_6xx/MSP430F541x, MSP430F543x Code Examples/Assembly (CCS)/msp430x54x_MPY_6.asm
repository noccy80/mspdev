;******************************************************************************
;   MSP430F54x Demo - 8x8 Unsigned Multiply Accumulate
;
;   Description: Hardware multiplier is used to multiply two numbers.
;   The calculation is automatically initiated after the second operand is
;   loaded. A second multiply accumulate operation is performed after that.
;   Results are stored in RESLO and RESHI. SUMEXT contains the carry of the
;   result.
;
;               MSP430F5438
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;            |                 |
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

            mov.w   #0x12,&MPY              ; Load first operand -unsigned mult
            mov.w   #0x56,&OP2              ; Load second operand

            mov.w   #0x12,&MAC              ; Load first operand -unsigned MAC
            mov.w   #0x56,&OP2              ; Load second operand

            bis.w   #LPM4,SR                ; Enter LPM4
            nop

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end