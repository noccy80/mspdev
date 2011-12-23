;*******************************************************************************
;   MSP430F23x0 Demo - Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
;
;   Description: Toggle P1.0 using software and the Timer_A overflow ISR.
;   In this example an ISR triggers when TA overflows. Inside the ISR P1.0
;   is toggled. Toggle rate is exactly 0.5Hz.
;   Proper use of the TAIV interrupt vector generator is demonstrated.
;   ACLK = TACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO ~1.2MHz
;   //* An external watch crystal on XIN XOUT is required for ACLK *//
;
;               MSP430F23x0
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
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
SetupTA     mov.w   #TASSEL_1+MC_2+TAIE,&TACTL  ; ACLK, contmode interrupt
                                            ;
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR for overflow
;-------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti
            reti                            ; TACCR1 not used
            reti                            ; TACCR2 not used
            reti
            reti
TA_over     xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR
                                            ;
;-------------------------------------------------------------------------------
; 			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short   RESET                   ;
            .sect   ".int08"          ; Timer_AX Vector
            .short   TAX_ISR                 ;
            .end
