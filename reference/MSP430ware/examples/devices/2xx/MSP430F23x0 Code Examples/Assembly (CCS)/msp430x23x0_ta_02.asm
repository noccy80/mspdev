;*******************************************************************************
;   MSP430F23x0 Demo - Timer_A, Toggle P1.0, TACCR0 Up Mode ISR, DCO SMCLK
;
;   Description: Toggle P1.0 using software and TA_0 ISR. Timer_A is
;   configured for up mode, thus the timer overflows when TAR counts to
;   TACCR0. In this example, TACCR0 is loaded with 20000.
;   ACLK = n/a, MCLK = SMCLK = TACLK = default DCO ~1.2MHz
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
SetupC0     mov.w   #CCIE,&TACCTL0          ; TACCR0 interrupt enabled
            mov.w   #20000,&TACCR0          ;
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, upmode
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
            .sect	".reset"            ; MSP430 RESET Vector
            .short   RESET                   ;
            .sect  ".int09"          ; Timer_A0 Vector
            .short   TA0_ISR                 ;
            .end