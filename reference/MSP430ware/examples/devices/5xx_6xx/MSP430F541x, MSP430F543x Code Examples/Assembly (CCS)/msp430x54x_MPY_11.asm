;******************************************************************************
;  MSP430F54x Demo - 32x32 Signed Multiply Accumalate
;
;  Description: Hardware multiplier is used to multiply-accumalate a set of
;  numbers. The first calculation is automatically initiated after the second
;  operand is loaded. A second multiply-accumulate operation is performed next.
;  Results are stored in RES0, RES1, RES2 and RES3.
;  SUMEXT contains the extended sign of the result.
;
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430F5438
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

                                            ; unsigned multiply
            mov.w   #0x1234,&MPY32L         ; Load lower 16 bits of operand 1
            mov.w   #0x1234,&MPY32H         ; Load upper 16 bits of operand 1
            
            mov.w   #0x5678,&OP2L           ; Load lower 16 bits of operand 2
            mov.w   #0x5678,&OP2H           ; Load lower 16 bits of operand 2

            ; signed MAC
            mov.w   #0x1234,&MACS32L        ; Load lower 16 bits of operand 1
            mov.w   #0x1234,&MACS32H        ; Load upper 16 bits of operand 1
            
            mov.w   #0x5678,&OP2L           ; Load lower 16 bits of operand 2
            mov.w   #0x5678,&OP2H           ; Load lower 16 bits of operand 2
                          
            bis.w   #LPM4,SR                ; Enter LPM4
            nop                             ; For debugger

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end