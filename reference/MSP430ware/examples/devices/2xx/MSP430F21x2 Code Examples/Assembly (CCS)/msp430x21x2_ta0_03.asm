;******************************************************************************
;  MSP430F21x2 Demo - Timer0_A3, Toggle P1.0, Overflow ISR, DCO SMCLK
;
;  Description: Toggle P1.0 using software and Timer0_A1 overflow ISR.
;  In this example an ISR triggers when TA0 overflows. Inside the TA
;  overflow ISR P1.0 is toggled. Toggle rate is approximately 18Hz.
;  Proper use of the TA0IV interrupt vector generator is demonstrated.
;  ACLK = n/a, MCLK = SMCLK = TA0CLK = default DCO ~1.2MHz
;
;               MSP430F21x2
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;           |                 |
;           |             P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
 			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupTA     mov.w   #TASSEL_2+MC_2+TAIE,&TA0CTL  ; SMCLK, contmode interrupt
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
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
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"				; MSP430 RESET Vector
            .short	RESET                   ;
            .sect	".int08"        		; Timer_AX Vector
            .short	TAX_ISR                 ;
            .end