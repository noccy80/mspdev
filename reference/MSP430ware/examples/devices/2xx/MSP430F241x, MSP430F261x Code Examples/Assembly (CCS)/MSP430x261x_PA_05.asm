;******************************************************************************
;   MSP430x261x Demo - Write a Word to Port A (Port7+Port8)
;
;   Description: Writes a Word(FFFFh) to Port A and stays in LPM4
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
SetupPA     bis.w   #0FFFFh,&PADIR          ; PA.x output
            bis.w   #0FFFFh,&PAOUT          ; Set all PA pins HI
                                            ;
Mainloop    bis.w   #LPM4,SR                ; LPM4
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .end
            