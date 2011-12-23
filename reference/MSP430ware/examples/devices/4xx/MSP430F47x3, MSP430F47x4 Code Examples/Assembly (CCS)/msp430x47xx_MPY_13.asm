;******************************************************************************
;   MSP430x47xx Demo - Saturation mode overflow test
;
;   Description: The example illustrates a special case showing overflow.
;   The addition result of 2 positive numbers may exceed the highest positive 
;   number (0x7FFF FFFF for 32 bit result) due to overflow indicaing a negative
;   result. By having the saturation mode enabled, this result can be truncated 
;   off to this highest positive number. Results with and without saturation mode 
;   are shown. 
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
SetupMPY    bis.w   #MPYSAT,&MPY32CTL0      ; Enable saturation mode
            clr.w   &RES3 
            clr.w   &RES2
;-------32-bit Result of a multiply operation (not shown) in RES0 and RES1------
            mov.w   #07FFFh,&RES1           ; Load upper 16 bits of operand 1
            mov.w   #0FFFDh,&RES0           ; Load lower 16 bits of operand 1
;----------second multiply operation-------------------------------------------
            mov.w   #05h,&MACS              ; Add 5 to result
            mov.w   #01h,&OP2      
            mov.w   &RESHI,R5               ; R5 = 0x7FFF
            mov.w   &RESLO,R6               ; R6 = 0xFFFF
            bic.w   #MPYSAT,&MPY32CTL0      ; Disable saturation mode                    
            bis.w   #LPM4,SR                ; LPM4
            nop                             ; set BREAKPOINT here

;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            	; RESET Vector
            .short  RESET                   ;
            .end
            