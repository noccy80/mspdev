;******************************************************************************
;  MSP430F21x2 Demo - Timer0_A3, PWM TA0_1 - TA0_2, Up/Down Mode, DCO SMCLK
;
;  Description: This program generates two PWM outputs on P1.2,3 using
;  Timer0_A3 configured for up/down mode. The value in TA0CCR0, 128, defines the
;  PWM period/2 and the values in TA0CCR1 and TA0CCR2 the PWM duty cycles. Using
;  ~1.2MHz SMCLK as TA0CLK, the timer period is ~212us with a 75% duty cycle
;  on P1.2 and 25% on P1.3.
;  SMCLK = MCLK = TA0CLK = default DCO ~1.2MHz
;
;               MSP430F21x2
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;           |                 |
;           |       P1.2/TA0_1|--> TA0CCR1 - 75% PWM
;           |       P1.3/TA0_2|--> TA0CCR2 - 25% PWM
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
SetupP1     bis.b   #00Ch,&P1DIR            ; P1.2 and P1.3 output
            bis.b   #00Ch,&P1SEL            ; P1.2 and P1.3 TA1/2 otions
SetupC0     mov.w   #128,&TA0CCR0            ; PWM Period/2
SetupC1     mov.w   #OUTMOD_6,&TA0CCTL1      ; TACCR1 toggle/set
            mov.w   #32,&TA0CCR1             ; TACCR1 PWM Duty Cycle
SetupC2     mov.w   #OUTMOD_6,&TA0CCTL2      ; TACCR2 toggle/set
            mov.w   #96,&TA0CCR2             ; TACCR2 PWM duty cycle
SetupTA     mov.w   #TASSEL_2+MC_3,&TA0CTL   ; SMCLK, updown mode
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
