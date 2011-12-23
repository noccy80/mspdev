;******************************************************************************
;   MSP430xG461x Demo - Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
;
;   Description: This program generates six PWM outputs on P2/P3 using
;   Timer_B configured for up mode. The value in CCR0, 512-1, defines the PWM
;   period and the values in CCR1-6 the PWM duty cycles. Using ~1048kHz SMCLK
;   as TBCLK, the timer period is ~488us.
;   ACLK = 32kHz, SMCLK = MCLK = TBCLK = default DCO ~1048kHz.
;
;                MSP430FG461x
;             -----------------
;         /|\|              XIN|-
;          | |                 |  32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P2.2/TB1|--> CCR1 - 75% PWM
;            |         P2.3/TB2|--> CCR2 - 25% PWM
;            |         P3.4/TB3|--> CCR3 - 12.5% PWM
;            |         P3.5/TB4|--> CCR4 - 6.26% PWM
;            |         P3.6/TB5|--> CCR5 - 3.13% PWM
;            |         P3.7/TB6|--> CCR6 - 1.566% PWM
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps

SetupP2     bis.b   #0Ch,&P2SEL             ; P2 option select
            bis.b   #0Ch,&P2DIR             ; P2 outputs
SetupP3     bis.b   #0F0h,&P3SEL            ; P3 option select
            bis.b   #0F0h,&P3DIR            ; P3 outputs

SetupC0     mov.w   #512-1,&TBCCR0          ; PWM Period
SetupC1     mov.w   #OUTMOD_7,&TBCCTL1      ; CCR1 reset/set
            mov.w   #383,&TBCCR1            ; CCR1 PWM Duty Cycle	
SetupC2     mov.w   #OUTMOD_7,&TBCCTL2      ; CCR2 reset/set
            mov.w   #128,&TBCCR2            ; CCR2 PWM duty cycle	
SetupC3     mov.w   #OUTMOD_7,&TBCCTL3      ; CCR3 reset/set
            mov.w   #64,&TBCCR3             ; CCR3 PWM duty cycle	
SetupC4     mov.w   #OUTMOD_7,&TBCCTL4      ; CCR4 reset/set
            mov.w   #32,&TBCCR4             ; CCR4 PWM duty cycle	
SetupC5     mov.w   #OUTMOD_7,&TBCCTL5      ; CCR5 reset/set
            mov.w   #16,&TBCCR5             ; CCR5 PWM duty cycle	
SetupC6     mov.w   #OUTMOD_7,&TBCCTL6      ; CCR6 reset/set
            mov.w   #8,&TBCCR6              ; CCR6 PWM duty cycle	
SetupTB     mov.w   #TBSSEL_2+MC_1,&TBCTL   ; SMCLK, upmode
                                            ;					
Mainloop    bis.w   #CPUOFF,SR              ; CPU off
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            	;	RESET Vector
            .short   RESET					;
            .end
