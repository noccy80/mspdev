;******************************************************************************
;   MSP430xG46x Demo - Software Port Interrupt on P1.4 from LPM4
;
;   Description: A hi/low transition on P1.4 will trigger P1_ISR which,
;   toggles P5.1. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
;   with the LED removed, all unused P1.x/P2.x configured as output or inputs
;   pulled high or low, and ensure the P2.0 interrupt input does not float.
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430xG461x
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;      /|\   |                 |
;       --o--|P1.4         P5.1|-->LED
;      \|/
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
SetupP5     bis.b   #002h,&P5DIR            ; P5.1 output
            bis.b   #010h,&P1IE             ; P1.4 Interrupt enabled
            bis.b   #010h,&P1IES            ; P1.4 hi/low edge
            bic.b   #010h,&P1IFG            ; P1.4 IFG Cleared
                                            ;
Mainloop    bis.w   #LPM4+GIE,SR            ; LPM4, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;-----------------------------------------------------------------------------
P1_ISR;     Toggle P1.0 Output
;-----------------------------------------------------------------------------
            xor.b   #002h,&P5OUT            ; P5.1 = toggle
            bic.b   #010h,&P1IFG            ; P1.4 IFG Cleared
            reti                            ; Return from ISR
                                            ;
;-----------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short   RESET
            .sect	".int20"            ; P1.x Vector
            .short   P1_ISR                  ;
            .end
