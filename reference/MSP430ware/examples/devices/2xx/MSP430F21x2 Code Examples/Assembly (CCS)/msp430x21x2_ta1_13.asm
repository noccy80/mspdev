;******************************************************************************
;  MSP430F21x2 Demo - Timer1_A, Toggle P3.6/TA0_1, Up/Down Mode, DCO SMCLK
;
;  Description: Toggle P3.6 using hardware TA0_1 output. Timer1_A is configured
;  for up/down mode with TA1CCR0 defining period. In
;  this example, TA1CCR0 is loaded with 250 and TA0_1 will toggle P3.6 at
;  TA1CLK/2*250. Thus the output frequency on P3.6 will be the TA1CLK/1000.
;  No CPU or software resources required.
;  ACLK = n/a, SMCLK = MCLK = TA1CLK = default DCO ~1.2MHz
;  As coded with TACLK = SMCLK, P3.6 output frequency is ~1200000/1000
;
;           MSP430F21x2
;         -----------------
;     /|\|              XIN|-
;      | |                 |
;      --|RST          XOUT|-
;        |                 |
;        |       P3.6/TA0_1|--> SMCLK/1000
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
SetupP3     bis.b   #040h,&P3DIR            ; P1.1 output
            bis.b   #040h,&P3SEL            ; P1.1 option slect
SetupC0     mov.w   #OUTMOD_4,&TA1CCTL0      ; TACCR0 toggle mode
            mov.w   #250,&TA1CCR0            ;
SetupTA     mov.w   #TASSEL_2+MC_3,&TA1CTL   ; SMCLK, updown mode
                                            ;
Mainloop    bis.w   #CPUOFF,SR              ; CPU off
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"				; MSP430 RESET Vector
            .short	RESET                   ;
            .end
            