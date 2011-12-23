;******************************************************************************
;  MSP430F21x2 Demo - Timer1_A, Toggle P1.0, TA1CCR0 Cont. Mode ISR, DCO SMCLK
;
;  Description: Toggle P1.0 using software and Timer1_A0 ISR. Toggles every
;  50000 SMCLK cycles. SMCLK provides clock source for TA1CLK.
;  During the Timer1_A0 ISR, P1.0 is toggled and 50000 clock cycles are added to
;  TA1CCR0. Timer1_A0 ISR is triggered every 50000 cycles. CPU is normally off and
;  used only during TA_ISR.
;  ACLK = n/a, MCLK = SMCLK = TA1CLK = default DCO ~1.2MHz
;
;              MSP430F21x2
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
RESET       mov.w   #025Fh,SP         		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupC0     mov.w   #CCIE,&TA1CCTL0          ; TACCR0 interrupt enabled
            mov.w   #50000,&TA1CCR0          ;
SetupTA     mov.w   #TASSEL_2+MC_2,&TA1CTL   ; SMCLK, contmode
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;------------------------------------------------------------------------------
TA1_ISR;    Toggle P1.0
;------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            add.w   #50000,&TA1CCR0          ; Add Offset to TACCR0
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"				; MSP430 RESET Vector
            .short	RESET                   ;
            .sect	".int13"		        ; Timer1_A0 Vector
            .short	TA1_ISR                 ;
            .end

            