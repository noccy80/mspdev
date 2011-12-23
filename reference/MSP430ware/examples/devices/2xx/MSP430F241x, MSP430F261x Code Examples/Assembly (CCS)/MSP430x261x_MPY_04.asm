;******************************************************************************
;   MSP430x261x Demo - 8x8 Signed Multiply
;
;   Description: Hardware multiplier is used to multiply two numbers.
;   The calculation is automatically initiated after the second operand is
;   loaded. Results are stored in RESLO, RESHI and SUMEXT = FFFF if result is
;   negative, SUMEXT = 0 otherwise. (In this eg: 0x04*0x84 = FFFFFE10)
;
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430F241x
;                MSP430F261x
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
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            mov.b   #004h,&0132h            ; Load first operand -signed mult
            sxt     &0132h                  ; Extend sign
            mov.b   #084h,&0138h            ; Load second operand
            sxt     &0138h                  ; Extend sign
            bis.w   #LPM4,SR                ; LPM4
            nop                             ; set BREAKPOINT here

;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .end
            