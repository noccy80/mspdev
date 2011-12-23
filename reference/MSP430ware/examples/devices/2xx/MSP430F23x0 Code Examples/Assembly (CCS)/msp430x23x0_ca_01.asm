;*******************************************************************************
;   MSP430F23x0 Demo - Comp_A+, Output Reference Voltages on P2.4
;
;   Description: Output Comparator_A+ reference levels on P2.4. Program will
;   cycle through the on-chip Comparator_A+ reference voltages with output on
;   P2.4. Normal mode is LPM0, Timer_A0 will interrupt LPM0.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
;
;                 MSP430F23x0
;              -----------------
;          /|\|              XIN|-
;           | |                 |
;           --|RST          XOUT|-
;             |                 |
;             |         P2.4/CA1|-->Vref
;             |                 |
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
            mov.b   #P2CA4,&CACTL2          ; P2.4/CA1 = +Comp
SetupCC0    mov.w   #CCIE,&TACCTL0          ; TACCR0 interrupt enabled
SetupTA     mov.w   #TASSEL_2+ID_3+MC_2,&TACTL  ; SMCLK/8, cont-mode
                                            ;
Mainloop    clr.b   &CACTL1                 ; No reference voltage
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
Ref1        mov.b   #CAREF0+CAON,&CACTL1    ; 0.25*Vcc, Comp. on
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
Ref2        mov.b   #CAREF1+CAON,&CACTL1    ; 0.5*Vcc, Comp. on
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
Ref3        mov.b   #CAREF1+CAREF0+CAON,&CACTL1  ; 0.55V, Comp. on
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            jmp     Mainloop                ; Loop
                                            ;
;-------------------------------------------------------------------------------
TA0_ISR;    Exit LPM0
;-------------------------------------------------------------------------------
            bic.w   #LPM0,0(SP)             ; Clear LPM0 bits from 0(SR)
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".rest"            ; MSP430 RESET Vector
            .short	RESET                   ;
            .sect	".int09"          ; Timer_A0 Vector
            .short	TA0_ISR                 ;
            .end
