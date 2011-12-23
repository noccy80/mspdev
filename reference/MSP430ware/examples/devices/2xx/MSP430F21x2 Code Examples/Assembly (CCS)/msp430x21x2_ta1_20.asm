;*******************************************************************************
;   MSP430F21x2 Demo - Timer1_A, PWM TA1_1, Up/Down Mode, 32kHz ACLK
;
;   Description: This program generates one PWM outputs on P3.7 using
;   Timer1_A configured for up/down mode. The value in TA1CCR0, 128, defines the
;   PWM period/2 and the values in TA1CCR1 and TA1CCR2 the PWM duty cycles. Using
;   32kHz ACLK as TA1CLK, the timer period is 7.8ms with a 75% duty cycle on
;   P3.7. Normal operating mode is LPM3.
;   ACLK = TA1CLK = LFXT1 = 32768Hz, MCLK = default DCO ~1.2MHz
;   //* External watch crystal on XIN XOUT is required for ACLK *//
;
;                MSP430F21x2
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |       P3.7/TA1_1|--> TAC1CCR1 - 75% PWM
;            |                 |
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
SetupP3     bis.b   #080h,&P3DIR            ; P3.7 output
            bis.b   #080h,&P3SEL            ; P3.7 TA1_2 otion
SetupC0     mov.w   #128,&TA1CCR0           ; PWM Period/2
SetupC1     mov.w   #OUTMOD_6,&TA1CCTL1     ; TACCR1 toggle/set
            mov.w   #32,&TA1CCR1            ; TACCR1 PWM Duty Cycle
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
