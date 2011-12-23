;******************************************************************************
;  MSP430F21x2 Demo - Timer1_A, Toggle P3.6/TA0_1, Up Mode, 32kHz ACLK
;
;  Description: Toggle P3.6 using hardware TA0_1 output. Timer_A is configured
;  for up mode with TA1CCR0 defining period. In this
;  example, TA1CCR0 is loaded with 10-1 and TA0_1 will toggle P3.6 at TA1CLK/10.
;  Thus the output frequency on P3.6 will be the TA1CLK/20. No CPU or software
;  resources required. Normal operating mode is LPM3.
;  ACLK = TA1CLK = 32kHz, MCLK = default DCO ~1.2MHz
;  ;* External watch crystal installed on XIN XOUT is required for ACLK *;
;  As coded with TA1CLK = ACLK, P1.1 output frequency = 32768/20 = 1.6384kHz
;
;           MSP430F21x2
;         -----------------
;     /|\|              XIN|-
;      | |                 | 32kHz
;      --|RST          XOUT|-
;        |                 |
;        |       P3.6/TA0_1|--> ACLK/20
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
SetupP1     bis.b   #040h,&P3DIR            ; P1.1 output
            bis.b   #040h,&P3SEL            ; P1.1 option slect
SetupC0     mov.w   #OUTMOD_4,&TA1CCTL0      ; TACCR0 toggle mode
            mov.w   #10-1,&TA1CCR0           ;
SetupTA     mov.w   #TASSEL_1+MC_1,&TA1CTL   ; ACLK, upmode
                                            ;
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"				; MSP430 RESET Vector
            .short	RESET                   ;
            .end
            