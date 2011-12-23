;******************************************************************************
;   MSP430x24x Demo - 16x16 Unsigned Multiply Accumulate
;
;   Description: Hardware multiplier is used to multiply two numbers.
;   The calculation is automatically initiated after the second operand is
;   loaded. A second multiply accumulate operation is performed after that.
;   Results are stored in RESLO and RESHI. SUMEXT contains the carry of the
;   result.
;
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                 MSP430x249
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;            |                 |
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            mov.w   #1234h,&MPY             ; Load first operand - unsigned mult
            mov.w   #5678h,&OP2             ; Load second operand

            mov.w   #1234h,&MAC             ; Load first operand - unsigned MAC
            mov.w   #5678h,&OP2             ; Load second operand

            bis.w   #LPM4,SR                ; LPM4
            nop                             ; set breakpoint here

;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset
            .short    RESET
            .end
            