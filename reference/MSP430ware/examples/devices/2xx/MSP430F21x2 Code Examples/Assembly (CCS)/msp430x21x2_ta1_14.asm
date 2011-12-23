;******************************************************************************
;  MSP430F21x2 Demo - Timer1_A, Toggle P3.6/TA0_1, Up/Down Mode, 32kHz ACLK
;
;  Description: Toggle P1.1 using hardware TA0_1 output. Timer1_A is configured
;  for up/down mode with TA1CCR0 defining period, Timer1_A also output on P3.6. In
;  this example, TA1CCR0 is loaded with 5 and TA1 will toggle P3.6 at TA1CLK/2*5.
;  Thus the output frequency on P1.1 will be the TA1CLK/20. No CPU or software
;  resources required. Normal operating mode is LPM3.
;  ACLK = TA1CLK = 32kHz, MCLK = default DCO ~1.2MHz
;  ;* External watch crystal installed on XIN XOUT is required for ACLK *;
;  As coded with TA1CLK = ACLK, P3.6 output frequency = 32768/20 = 1.6384kHz.
;
;           MSP430F21x2
;         -----------------
;     /|\|              XIN|-
;      | |                 | 32kHz
;      --|RST          XOUT|-
;        |                 |
;        |         P1.1/TA1|--> ACLK/20
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
            mov.w   #5,&TA1CCR0              ;
SetupTA     mov.w   #TASSEL_1+MC_3,&TA1CTL   ; ACLK, updown mode
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
            
