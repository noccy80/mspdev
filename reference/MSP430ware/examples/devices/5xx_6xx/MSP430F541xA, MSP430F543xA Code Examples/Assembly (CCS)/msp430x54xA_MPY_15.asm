;******************************************************************************
;   MSP430F54xA Demo - Fractional mode, Q15 multiplication
;
;   Description: The example illustrates multiplication of 2 Q15 numbers in
;   fractional mode. The result is a Q15 (15 bit) number stored in the RES1
;   register. It can be viewed in the debugger window.
;
;
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430F5438A
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
            .bss    result_Q15,2 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT      

            mov.w   #MPYFRAC,&MPY32CTL0     ; Set fractional mode

            mov.w   #0x7D70,&MPYS           ; Load first operand
            mov.w   #0x1000,&OP2            ; Load second operand
    		mov.w   &RESHI,result_Q15       ; Q15 result
            bic.w   #MPYFRAC,&MPY32CTL0 
            
            bis.w   #LPM4,SR                ; Enter LPM4
            nop                             ; For debugger

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end           