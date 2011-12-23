;******************************************************************************
;   MSP430F54x Demo - 8x8 Signed Multiply
;
;   Description: Hardware multiplier is used to multiply two numbers.
;   The calculation is automatically initiated after the second operand is
;   loaded. Results are stored in RESLO, RESHI and SUMEXT = FFFF if result is
;   negative, SUMEXT = 0 otherwise.
;
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
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

value1    .equ    R4 
value2    .equ    R5 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    

            mov.b   #0x04,value1            ; Assign operands for signed mult
            mov.b   #0x84,value2

            mov.b   value1,&MPYS_B          ; Load MPYS to denote signed operation
            mov.b   value2,&OP2_B           ; Load OP2 with byte access to avoid
                                            ; ... the need for sign extension
            
            bis.w   #LPM4,SR                ; Enter LPM4
            nop                             ; For debugger 

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end