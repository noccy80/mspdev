;******************************************************************************
;  MSP430F21x2 Demo - Timer1_A, Toggle P1.0 3.6,3.7, Cont. Mode ISR, 32kHz ACLK
;
;  Description: Use Timer1_A CCRx units and overflow to generate four
;  independent timing intervals. For demonstration, TA1CCR0, TA1CCR1 and TA1CCR2
;  output units are optionally selected with port pins P3.6 and P3.7
;  in toggle mode. As such, these pins will toggle when respective TA1CCRx
;  registers match the T1AR counter. Interrupts are also enabled with all
;  TA1CCRx units, software loads offset to next interval only - as long as the
;  interval offset is added to TA1CCRx, toggle rate is generated in hardware.
;  Timer1_A1 overflow ISR is used to toggle P1.0 with software. Proper use
;  of the TA1IV interrupt vector generator is demonstrated.
;  ACLK = TA1CLK = 32kHz, MCLK = SMCLK = default DCO ~1.2MHz
;  ;* An external watch crystal on XIN XOUT is required for ACLK *;
;
;  As coded and with TA1CLK = 32768Hz, toggle rates are:
;  P3.6 = TA1CCR0 = 32768/(2*4) = 4096Hz
;  P3.7 = TA1CCR1 = 32768/(2*16) = 1024Hz
;  P1.0 = overflow = 32768/(2*65536) = 0.25Hz
;
;              MSP430F21x2
;            -----------------
;        /|\|              XIN|-
;         | |                 | 32kHz
;         --|RST          XOUT|-
;           |                 |
;           |       P3.6/TA0_1|--> TA1CCR0
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
SetupC0     mov.w   #OUTMOD_4 +CCIE,&TA1CCTL0; TACCR0 toggle, interrupt enabled
SetupC1     mov.w   #OUTMOD_4 +CCIE,&TA1CCTL1; TACCR1 toggle, interrupt enabled
SetupTA     mov.w   #TASSEL_1+MC_2+TAIE,&TA1CTL   ; ACLK, contmode, interrupt
                                            ;
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required for debug
                                            ;
;-------------------------------------------------------------------------------
TA1_ISR;
;-------------------------------------------------------------------------------
            add.w   #4,&TA1CCR0             ; Offset until next interrupt
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR for TA1CCR1-2 and overflow
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
TA1CCR1_ISR add.w   #16,&TA1CCR1           ; Offset until next interrupt
            reti                            ; Return ISR


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

            