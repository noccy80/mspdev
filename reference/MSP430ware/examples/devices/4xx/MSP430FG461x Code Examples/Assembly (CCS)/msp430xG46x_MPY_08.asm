;******************************************************************************
;   MSP430xG46x Demo - 8x8 Signed Multiply Accumulate
;
;   Description: Hardware multiplier is used to multiply two numbers.
;   The calculation is automatically initiated after the second operand is
;   loaded.  A second multiply accumulate operation is performed after that.
;   Results are stored in RESLO and RESHI.  SUMEXT contains the extended sign of
;   result.
;
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                 MSP430xG461x
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;            |                 |
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
            mov.w   #1234h,&MPY             ; Load first operand - unsigned mult
            mov.w   #5678h,&OP2             ; Load second operand

            mov.w   #12h,&MACS              ; Load first operand - signed MAC
            sxt     &MACS                   ; Extend sign
            mov.w   #96h,R15                ; Move to register to accomodate SXT
            sxt     R15                     ; Extend sign
            mov.w   R15,&OP2                ; Load second operand

            bis.w   #LPM4,SR                ; LPM4
            nop                             ; Set breakpoint here

;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset, Watchdog
            .short   RESET
            .end
          