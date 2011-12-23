;******************************************************************************
;  MSP430F21x2 Demo - Timer0_A3, Toggle P1.0, TA0CCR0 Up Mode ISR, DCO SMCLK
;
;  Description: Toggle P1.0 using software and Timer0_A0 ISR. Timer0_A is
;  configured for up mode, thus the timer overflows when TA0R counts to
;  TA0CCR0. In this example, TA0CCR0 is loaded with 20000.
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
SetupC0     mov.w   #CCIE,&TA0CCTL0          ; TACCR0 interrupt enabled
            mov.w   #20000,&TA0CCR0          ;
SetupTA     mov.w   #TASSEL_2+MC_1,&TA0CTL   ; SMCLK, upmode
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-------------------------------------------------------------------------------
TA0_ISR;    Toggle P1.0
;-------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	            ; MSP430 RESET Vector
            .short	RESET                   ;
            .sect	".int09"			    ; Timer_A0 Vector
            .short	TA0_ISR                 ;
            .end
