;******************************************************************************
;   MSP430x47xx Demo - 32x32 Unsigned Multiply
;
;   Description: Hardware multiplier is used to multiply two numbers.
;   The calculation is automatically initiated after the second operand is
;   loaded. Results are stored in RES0, RES1, RES2 and RES3.
;
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430x47xx
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
 .cdecls C,LIST, "msp430x47x4.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
            mov.w   #01234h,&MPY32L         ; Load lower 16 bits of operand 1
            mov.w   #01234h,&MPY32H         ; Load upper 16 bits of operand 1
            mov.w   #05678h,&OP2L           ; Load lower 16 bits of operand 2
            mov.w   #05678h,&OP2H           ; Load upper 16 bits of operand 2
            bis.w   #LPM4,SR                ; LPM4
            nop                             ; set BREAKPOINT here

;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            	; RESET Vector
            .short  RESET                   ;
            .end
            