;******************************************************************************
;  MSP430F21x2 Demo - Timer_A, Toggle P1.0-3, Cont. Mode ISR, DCO SMCLK
;
;  Description: Use Timer_A CCRx units and overflow to generate four
;  independent timing intervals. For demonstration, TACCR0 and TACCR1
;  output units are optionally selected with port pins P3.6 and P3.7
;  in toggle mode. As such, these pins will toggle when respective TACCRx
;  registers match the TAR counter. Interrupts are also enabled with all
;  TACCRx units, software loads offset to next interval only - as long as
;  the interval offset is added to TACCRx, toggle rate is generated in
;  hardware. Timer_A overflow ISR is used to toggle P1.0 with software.
;  Proper use of the TAIV interrupt vector generator is demonstrated.
;  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO ~1.2MHz
;
;  As coded with TACLK ~1.2MHz DCO, toggle rates are:
;  P3.6 = TA1CCR0 = 1.2MHz/(2*200) ~3000Hz
;  P3.7 = TA1CCR1 = 1.2MHz/(2*1000) ~600Hz
;  P1.0 = overflow = 1.2MHz/(2*65536) ~9Hz
;
;              MSP430F21x2
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;           |                 |
;           |       P3.6/TA1_0|--> TA1CCR0
;           |       P3.7/TA1_1|--> TA1CCR1
;           |                 |
;           |             P1.0|--> Overflow/software
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
SetupP3     bis.b   #0C0h,&P3SEL            ; P3.6 - P3.7 option select
            bis.b   #0C0h,&P3DIR            ; P3.6 - P3.7 output
SetupP1     bis.b   #00Fh,&P1DIR            ; P1.0 output
SetupC0     mov.w   #OUTMOD_4+CCIE,&TA1CCTL0 ; TACCR0 toggle, interrupt enabled
SetupC1     mov.w   #OUTMOD_4+CCIE,&TA1CCTL1 ; TACCR1 toggle, interrupt enabled
SetupTA     mov.w   #TASSEL_2+MC_2+TAIE,&TA1CTL   ; SMCLK, contmode, interrupt
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-------------------------------------------------------------------------------
TA1_ISR;
;-------------------------------------------------------------------------------
            add.w   #200,&TA1CCR0           ; Offset until next interrupt
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR for TACCR1-2 and overflow
;-------------------------------------------------------------------------------
            add.w   &TA1IV,PC               ; Add Timer_A offset vector
            reti                            ;
            jmp     TA1CCR1_ISR             ; TACCR1
            reti
            reti                            ;
            reti                            ;
TA_over     xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR
                                            ;
TA1CCR1_ISR add.w   #1000,&TA1CCR1          ; Offset until next interrupt
            reti                            ; Return ISR
                                            ;


;-------------------------------------------------------------------------------
 ;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"				; MSP430 RESET Vector
            .short	RESET                   ;
            .sect	".int13"        		; Timer1_A0 Vector
            .short	TA1_ISR                 ;
            .sect	".int12"       			; Timer1_AX Vector
            .short	TAX_ISR                 ;
            .end

            