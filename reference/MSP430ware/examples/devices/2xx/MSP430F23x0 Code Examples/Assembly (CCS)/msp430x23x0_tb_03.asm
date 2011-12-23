;*******************************************************************************
;   MSP430F23x0 Demo - Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
;
;   Description: Toggle P1.0 using software and Timer_B overflow ISR.
;   In this example an ISR triggers when TB overflows. Inside the TB
;   overflow ISR P1.0 is toggled. Toggle rate is approximatlely 18Hz.
;   Proper use of the TBIV interrupt vector generator is demonstrated.
;   ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~1.2MHz
;
;                MSP430F23x0
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x23x0.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #450h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupTB     mov.w   #TBSSEL_2+MC_2+TBIE,&TBCTL  ; SMCLK, contmode, interrupt
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-------------------------------------------------------------------------------
TBX_ISR;    Common ISR for overflow
;-------------------------------------------------------------------------------
            add.w   &TBIV,PC                ; Add Timer_B offset vector
            reti                            ;
            reti                            ; TBCCR1 not used
            reti                            ; TBCCR2 not used
            reti                            ;
            reti                            ;
            reti                            ;
            reti                            ;
TB_over     xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short	RESET                   ;
            .sect	".int12"          ; Timer_BX Vector
            .short	TBX_ISR                 ;
            .end
