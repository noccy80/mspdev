;******************************************************************************
;   MSP430x261x Demo - Timer_B, Toggle P4.0-6, Cont. Mode ISR, DCO SMCLK
;
;   Description:  Use Timer_B CCRx units and overflow to generate eight
;   independent timing intervals.  For demonstration, TBCCR0-6 output
;   units are optionally selected with P4 in toggle mode.
;   As such, these pins will toggle when respective TBCCRx registers
;   match the TBR counter.  Interrupts are also enabled with all TBCCRx units,
;   software only adds offset to next interval - as long as the interval
;   offset is aded to TBCCRx, toggle rate is generated in hardware.  Timer_B
;   overflow is used to toggle P1.0 with software. Proper use of the TBIV
;   interrupt vector generator is demonstrated.
;   MCLK = SMCLK = TBCLK = DCO 8MHz
;
;   As coded with TBCLK 8MHz DCO, toggle rates are:
;   P4.0 = TBCCR0 = 8000000/(2*200) = 20KHz
;   P4.1 = TBCCR1 = 8000000/(2*400) = 10KHz
;   P4.2 = TBCCR2 = 8000000/(2*600) = 6.67KHz
;   P4.3 = TBCCR3 = 8000000/(2*800) = 5KHz
;   P4.4 = TBCCR4 = 8000000/(2*1000) = 4KHz
;   P4.5 = TBCCR5 = 8000000/(2*2000) = 2KHz
;   P4.6 = TBCCR6 = 8000000/(2*10000) = 400Hz
;   P1.0 = overflow = 8000000/(2*65536) = 61Hz
;
;                MSP430F241x
;                MSP430F261x
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |         P4.0/TB0|--> TBCCR0
;            |         P4.1/TB1|--> TBCCR1
;            |         P4.2/TB2|--> TBCCR2
;            |         P4.3/TB3|--> TBCCR3
;            |         P4.4/TB4|--> TBCCR4
;            |         P4.5/TB5|--> TBCCR5
;            |         P4.6/TB6|--> TBCCR6
;            |             P1.0|--> Overflow/software
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
CheckCal    cmp.b   #0FFh,&CALBC1_8MHZ      ; Calibration constants erased?
            jeq     Trap
            cmp.b   #0FFh,&CALDCO_8MHZ
            jne     Load  
Trap        jmp     $                       ; Trap CPU!!
Load        mov.b   &CALBC1_8MHZ,&BCSCTL1   ; Set DCO to 8MHz
            mov.b   &CALDCO_8MHZ,&DCOCTL    ; 

SetupP2     bis.b   #7Fh,&P4SEL             ; P2 option select
            bis.b   #7Fh,&P4DIR             ; P2 outputs
SetupP1     bis.b   #BIT0,&P1DIR            ; P1.0 = output

SetupCx     mov.w   #OUTMOD_4+CCIE,&TBCCTL0 ; TBCCR0 interrupt enabled
            mov.w   #OUTMOD_4+CCIE,&TBCCTL1 ; TBCCR1 interrupt enabled
            mov.w   #OUTMOD_4+CCIE,&TBCCTL2 ; TBCCR2 interrupt enabled
            mov.w   #OUTMOD_4+CCIE,&TBCCTL3 ; TBCCR3 interrupt enabled
            mov.w   #OUTMOD_4+CCIE,&TBCCTL4 ; TBCCR4 interrupt enabled
            mov.w   #OUTMOD_4+CCIE,&TBCCTL5 ; TBCCR5 interrupt enabled
            mov.w   #OUTMOD_4+CCIE,&TBCCTL6 ; TBCCR6 interrupt enabled
SetupTB     mov.w   #TBSSEL_2+MC_2+TBIE,&TBCTL ; SMCLK, contmode, interrupt
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enalbled
            nop                             ; Required for debugger
                                            ;
;------------------------------------------------------------------------------
TB0_ISR;    Toggle P1.0
;------------------------------------------------------------------------------
            add.w   #200,&TBCCR0            ; Offset until next interrupt
            reti                            ;		
;
;------------------------------------------------------------------------------
TBX_ISR;    Common ISR for TBCCR1-6 and overflow
;------------------------------------------------------------------------------
            add.w   &TBIV,PC                ; Add Timer_B offset vector
            reti                            ; CCR0 - no source
            jmp     TBCCR1_ISR              ; TBCCR1
            jmp     TBCCR2_ISR              ; TBCCR2
            jmp     TBCCR3_ISR              ; TBCCR3
            jmp     TBCCR4_ISR              ; TBCCR4
            jmp     TBCCR5_ISR              ; TBCCR5
            jmp     TBCCR6_ISR              ; TBCCR6
TB_over     bic.w   #TBIFG, &TBCTL
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR		
                                            ;
TBCCR1_ISR  bic.w   #CCIFG, &TBCCTL1
            add.w   #400,&TBCCR1            ; Offset until next interrupt
            jmp     TBX_ISR                 ;
                                            ;
TBCCR2_ISR  bic.w   #CCIFG, &TBCCTL2
            add.w   #600,&TBCCR2            ; Offset until next interrupt
            jmp     TBX_ISR                 ;
                                            ;
TBCCR3_ISR  bic.w   #CCIFG, &TBCCTL3
            add.w   #800,&TBCCR3            ; Offset until next interrupt
            jmp     TBX_ISR                 ;
                                            ;
TBCCR4_ISR  bic.w   #CCIFG, &TBCCTL4
            add.w   #1000,&TBCCR4           ; Offset until next interrupt
            jmp     TBX_ISR                 ;
                                            ;
TBCCR5_ISR  bic.w   #CCIFG, &TBCCTL5
            add.w   #2000,&TBCCR5           ; Offset until next interrupt
            jmp     TBX_ISR                 ;
                                            ;
TBCCR6_ISR  bic.w   #CCIFG, &TBCCTL6
            add.w   #10000,&TBCCR6          ; Offset until next interrupt
            jmp     TBX_ISR                 ;
                                            ;

;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; MSP430 RESET Vector
            .short  RESET                  ;
            .sect	".int29"          		; Timer_B0 Vector
            .short  TB0_ISR                 ;
            .sect	".int28"				; Timer_BX Vector
            .short	TBX_ISR					
            .end
            