;******************************************************************************
;    MSP430x47xx Demo - Saturation mode underflow test
;
;   Description: The example illustrates a special case showing underflow.
;   The addition result of 2 negative numbers may exceed the highest negative 
;   number (0x8000 0000 for 32 bit result) due to undeflow indicaing a positive
;   result. By having the saturation mode enabled, this result can be truncated 
;   off to this highest negative number. Results with and without saturation mode 
;   are shown. 
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
            mov.w   #00000h,&RES1           ; Pre-load first negative result
            mov.w   #08000h,&RES0           
;----------second multiply operation-------------------------------------------
            mov.w   #08000h,&MACS           ; Add to second negative result
            mov.w   #05h,&OP2      
            mov.w   &RESHI,R5               ; R5 = 0x8000
            mov.w   &RESLO,R6               ; R6 = 0xFFFF
            bic.w   #MPYSAT,&MPY32CTL0      ; Disable saturation mode                    
            bis.w   #LPM4,SR                ; LPM4
            nop                             ; set BREAKPOINT here

;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            	; MSP430 RESET Vector
            .short  RESET                   ;
            .end
    