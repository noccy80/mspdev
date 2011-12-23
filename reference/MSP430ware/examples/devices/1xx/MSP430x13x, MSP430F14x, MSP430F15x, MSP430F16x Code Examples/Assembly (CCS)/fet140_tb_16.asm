;******************************************************************************
;   MSP-FET430P140 Demo - Timer_B, PWM TB1-6, Up Mode, XT2 HF XTAL SMCLK
;
;   Description: This program generates six PWM outputs on P4.1-6 using
;   Timer_B configured for up mode. The value in CCR0, 512-1, defines the PWM
;   period and the values in CCR1-6 the PWM duty cycles.
;   ACLK = n/a, MCLK = SMCLK = TBCLK = XT2 = HF XTAL
;   //* External crystal installed on XT2IN XT2OUT is required for SMCLK *//	
;
;                MSP430F149
;             -----------------
;         /|\|            XT2IN|-
;          | |                 | HF XTAL (455k - 8MHz)
;          --|RST        XT2OUT|-
;            |                 |
;            |         P4.1/TB1|--> CCR1 - 75% PWM
;            |         P4.2/TB2|--> CCR2 - 25% PWM
;            |         P4.3/TB3|--> CCR3 - 12.5% PWM
;            |         P4.4/TB4|--> CCR4 - 6.25% PWM
;            |         P4.5/TB5|--> CCR5 - 3.125% PWM
;            |         P4.6/TB6|--> CCR6 - 1.5625% PWM
;
;   M. Buccini / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBC     bic.b   #XT2OFF,&BCSCTL1        ; XT2on
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_2+SELS,BCSCTL2    ; MCLK = SMCLK = XT2
SetupP4     bis.b   #007Eh,&P4DIR           ; P4.1-P4.6 output
            bis.b   #007Eh,&P4SEL           ; P4.1-P4.6 TB1-62 otions
SetupC0     mov.w   #512-1,&TBCCR0          ; PWM Period
SetupC1     mov.w   #OUTMOD_7,&TBCCTL1      ; CCR1 reset/set
            mov.w   #384,&TBCCR1            ; CCR1 PWM Duty Cycle	
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
;           Interrupt Vectors Used MSP430x13x/14x/15x/16x
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
