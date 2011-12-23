;******************************************************************************
;   MSP430xG46x Demo - Write a byte to Port 8
;
;   Description: Writes a byte(FFh) to Port 8 and stays in LPM4
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430xG46x
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
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
;-------------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP7     bis.b   #0FFh,&P8DIR            ; P8.x output
            bis.b   #0FFh,&P8OUT            ; Set all P8 pins HI
                                            ;
Mainloop    bis.w   #LPM4,SR                ; LPM4
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short   RESET
            .end