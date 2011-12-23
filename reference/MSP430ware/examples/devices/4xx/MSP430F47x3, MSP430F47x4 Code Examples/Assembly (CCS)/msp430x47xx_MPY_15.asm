;******************************************************************************
;    MSP430x47xx Demo - Fractional mode, Q15 multiplication
;
;   Description: The example illustrates multiplication of 2 Q15 numbers in
;   fractional mode. The result is a Q15 (15 bit) number stored in the RES1
;   register. It can be viewed in the debugger window. 
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
SetupMPY    bis.w   #MPYFRAC,&MPY32CTL0     ; Enable fractional mode
            mov.w   #07D70h,&MPYS           ; Load first operand
            mov.w   #01000h,&OP2            ; Load second operand      
            mov.w   &RESHI,R5               ; R5 = Q15 result
            bic.w   #MPYFRAC,&MPY32CTL0     ; Disable fractional mode                    
            bis.w   #LPM4,SR                ; LPM4
            nop                             ; set BREAKPOINT here
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            	; MSP430 RESET Vector
            .short  RESET                   ;
            .end
    