;******************************************************************************
;   MSP430F54xA Demo - 8x8 Signed Multiply Accumulate
;
;   Description: Hardware multiplier is used to multiply two numbers.
;   The calculation is automatically initiated after the second operand is
;   loaded.  A second multiply accumulate operation is performed after that.
;   Results are stored in RESLO and RESHI.  SUMEXT contains the extended sign of
;   result.
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

value1    .equ    R4 
value2    .equ    R5 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT

            mov.w   #0x1234,&MPY            ; Load 1st operand - unsigned mult
            mov.w   #0x5678,&OP2            ; Load second operand

            mov.b   #0x12,value1            ; Load first operand - signed MAC
            mov.b   #0x96,value2            ; Load second operand

            mov.b   value1,&MACS_B          ; Signed multiplication
            mov.b   value2,&OP2_B           ; Byte access removes the need for
                                            ; ... sign extension
            bis.w   #LPM4,SR                ; Enter LPM4
            nop                             ; For debugger

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end