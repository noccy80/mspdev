;*******************************************************************************
;   MSP430F23x0 Demo - Timer_B, Toggle P4.0-2, Cont. Mode ISR, 32kHz ACLK
;
;   Description: Use Timer_B CCRx units and overflow to generate four
;   independent timing intervals. For demonstration, TBCCR0-2 output
;   units are optionally selected with P4.0-2 respectively in toggle
;   mode. As such, these pins will toggle when respective TBCCRx registers
;   match the TBR counter. Interrupts are also enabled with all TBCCRx units,
;   software only adds offset to next interval - as long as the interval
;   offset is aded to TBCCRx, toggle rate is generated in hardware. Timer_B
;   overflow ISR is used to toggle P1.0 with software. Proper use of the
;   TBIV interrupt vector generator is demonstrated.
;   ACLK = TBCLK = 32kHz, MCLK = SMCLK = DCO ~1.2MHz
;   //* An external watch crystal on XIN XOUT is required for ACLK *//
;
;   As coded and with TBCLK = 32768Hz, toggle rates are:
;   P4.0 = TBCCR0 = 32768/(2*4) = 4096Hz
;   P4.1 = TBCCR1 = 32768/(2*8) = 2048Hz
;   P4.2 = TBCCR2 = 32768/(2*16) = 1024Hz
;   P1.0 = overflow = 32768/(2*65536) = 0.25Hz
;
;                MSP430F23x0
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P4.0/TB0|--> TBCCR0
;            |         P4.1/TB1|--> TBCCR1
;            |         P4.2/TB2|--> TBCCR2
;            |             P1.0|--> Overflow/software
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
SetupP4     bis.b   #07h,&P4SEL             ; P4.x - P4.2 option select
            bis.b   #07h,&P4DIR             ; P4.x = outputs
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 = output
SetupCx     mov.w   #OUTMOD_4+CCIE,&TBCCTL0 ; TBCCR0 interrupt enabled
            mov.w   #OUTMOD_4+CCIE,&TBCCTL1 ; TBCCR1 interrupt enabled
            mov.w   #OUTMOD_4+CCIE,&TBCCTL2 ; TBCCR2 interrupt enabled
SetupTB     mov.w   #TBSSEL_1+MC_2+TBIE,&TBCTL   ; ACLK, contmode, interrupt
                                            ;
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
TB0_ISR;    ISR for TBCCR0
;-------------------------------------------------------------------------------
            add.w   #4,&TBCCR0              ; Offset until next interrupt
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
TBX_ISR;    Common ISR for TBCCR1-6 and overflow
;-------------------------------------------------------------------------------
            add.w   &TBIV,PC                ; Add Timer_B offset vector
            reti                            ;
            jmp     TBCCR1_ISR              ; TBCCR1
            jmp     TBCCR2_ISR              ; TBCCR2
            nop                             ;
            nop                             ;
            nop                             ;
            nop                             ;
TB_over     xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR
                                            ;
TBCCR1_ISR  add.w   #8,&TBCCR1              ; Offset until next interrupt
            jmp     TBX_ISR                 ;
                                            ;
TBCCR2_ISR  add.w   #16,&TBCCR2             ; Offset until next interrupt
            jmp     TBX_ISR                 ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short	RESET                   ;
            .sect	".int13"			; Timer_B0 Vector
            .short  TB0_ISR                 ;
            .sect	".int12"    	      ; Timer_BX Vector
            .short	TBX_ISR                 ;
            .end
