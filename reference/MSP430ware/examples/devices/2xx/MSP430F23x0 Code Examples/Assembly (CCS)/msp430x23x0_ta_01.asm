;*******************************************************************************
;   MSP430F23x0 Demo - Timer_A, Toggle P1.0, TACCR0 Cont. Mode ISR, DCO SMCLK
;
;   Description: Toggle P1.0 using software and TA_0 ISR. Toggles every
;   50000 SMCLK cycles. SMCLK provides clock source for TACLK.
;   During the TA_0 ISR, P1.0 is toggled and 50000 clock cycles are added to
;   TACCR0. TA_0 ISR is triggered every 50000 cycles. CPU is normally off and
;   used only during TA_ISR.
;   ACLK = n/a, MCLK = SMCLK = TACLK = default DCO ~1.2MHz
;
;               MSP430F23x0
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
SetupC0     mov.w   #CCIE,&TACCTL0          ; TACCR0 interrupt enabled
            mov.w   #50000,&TACCR0          ;
SetupTA     mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, contmode
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;    Toggle P1.0
;------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            add.w   #50000,&TACCR0          ; Add Offset to TACCR0
            reti                            ;
                                            ;
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short      RESET                   ;
            .sect     ".int09"          ; Timer_A0 Vector
            .short      TA0_ISR                 ;
            .end
