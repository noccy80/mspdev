;******************************************************************************
;   MSP430F66xx Demo - 32x32 Signed Multiply
;
;   Description: Hardware multiplier is used to multiply two numbers.
;   The calculation is automatically initiated after the second operand is
;   loaded. Results are stored in RES0, RES1, RES2 and RES3.
;
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430x6638
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;           |                 |
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
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    

            mov.w   #0x1234,&MPYS32L        ; Load lower 16 bits of operand 1
            mov.w   #0x1234,&MPYS32H        ; Load upper 16 bits of operand 1
            
            mov.w   #0x5678,&OP2L           ; Load lower 16 bits of operand 2
            mov.w   #0x5678,&OP2H           ; Load lower 16 bits of operand 2
            nop								; Wait for the result to become available
            nop
            nop
            nop
            nop              
            bis.w   #LPM4,SR                ; Enter LPM4
            nop                             ; For debugger

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
