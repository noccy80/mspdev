;******************************************************************************
;   MSP430x47xx Demo - Timer_A, PWM TA1-2 Up Mode, DCO SMCLK
;
;   Description: This program outputs two PWM signals on P1.2 and P2.0
;   using Timer_A configured for up mode. The value in CCR0 defines the PWM
;   period and the values in CCR1 and CCR2 the PWM duty cycles. Using SMCLK
;   as TACLK, the timer period is 488us with a 75% duty cycle on P1.2 and
;   25% on P2.0.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430x47xx
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P1.2/TA1|--> CCR1 - 75% PWM
;            |         P2.0/TA2|--> CCR2 - 25% PWM
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x47x4.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
SetupP1     bis.b   #BIT2,&P1DIR            ; P1.2 output
            bis.b   #BIT2,&P1SEL            ; P1.2 TA1 option select
SetupP2     bis.b   #BIT0,&P2DIR            ; P2.0 output
            bis.b   #BIT0,&P2SEL            ; P2.0 TA2 option select
SetupC0     mov.w   #512-1,&CCR0            ; PWM Period
SetupC1     mov.w   #OUTMOD_7,&CCTL1        ; CCR1 reset/set
            mov.w   #384,&CCR1              ; CCR1 PWM Duty Cycle	
SetupC2     mov.w   #OUTMOD_7,&CCTL2        ; CCR2 reset/set
            mov.w   #128,&CCR2              ; CCR2 PWM duty cycle	
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, upmode
                                            ;					
Mainloop    bis.w   #CPUOFF,SR              ; CPU off
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".reset"            	; RESET Vector
            .short   RESET                  ;
            .end
