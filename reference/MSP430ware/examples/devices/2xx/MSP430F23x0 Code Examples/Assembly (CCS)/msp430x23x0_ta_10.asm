;*******************************************************************************
;   MSP430F23x0 Demo - Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
;
;   Description: Toggle P1.1 using hardware TA0 output. Timer_A is configured
;   for up mode with TACCR0 defining period, TA0 also output on P1.1. In this
;   example, TACCR0 is loaded with 500-1 and TA0 will toggle P1.1 at TACLK/500.
;   Thus the output frequency on P1.1 will be TACLK/1000. No CPU or software
;   resources required.
;   As coded with TACLK = SMCLK, P1.1 output frequency is ~1200000/1000.
;   SMCLK = MCLK = TACLK = default DCO ~1.2MHz
;
;               MSP430F23x0
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |         P1.1/TA0|--> SMCLK/1000
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
SetupP1     bis.b   #002h,&P1DIR            ; P1.1 output
            bis.b   #002h,&P1SEL            ; P1.1 option slect
SetupC0     mov.w   #OUTMOD_4,&TACCTL0      ; TACCR0 toggle, upmode
            mov.w   #500-1,&TACCR0          ;
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, clear TAR
                                            ;
Mainloop    bis.w   #CPUOFF,SR              ; CPU off
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short	RESET                   ;
            .end
