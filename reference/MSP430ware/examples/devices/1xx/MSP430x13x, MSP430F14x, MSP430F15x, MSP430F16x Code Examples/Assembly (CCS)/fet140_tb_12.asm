;******************************************************************************
;   MSP-FET430P140 Demo - Timer_A, PWM TB1-2, Up Mode, HF XTAL ACLK
;
;   Description: This program generates two PWM outputs on P4.1,2 using
;   Timer_B configured for up mode. The value in CCR0, 512-1, defines the PWM
;   period and the values in CCR1-2 the PWM duty cycles. Using HF XTAL ACLK
;   as TBCLK, the timer period is HF XTAL/512 with a 75% duty cycle on P4.1
;   and 25% on P4.2.
;   ACLK = MCLK = TBCLK = HF XTAL
;   //* HF XTAL REQUIRED AND NOT INSTALLED ON FET *//
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
;
;                MSP430F149
;             -----------------
;         /|\|              XIN|-
;          | |                 | HF XTAL (455k - 8MHz)
;          --|RST          XOUT|-
;            |                 |
;            |         P4.1/TB1|--> CCR1 - 75% PWM
;            |         P4.2/TB2|--> CCR2 - 25% PWM
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
SetupP4     bis.b   #006h,&P4DIR            ; P4.1 and P4.2 output
            bis.b   #006h,&P4SEL            ; P4.1 and P4.2 TB1/2 otions
SetupBC     bis.b   #XTS,&BCSCTL1           ; LFXT1 = HF XTAL
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_3,&BCSCTL2        ; MCLK = LFXT1
SetupC0     mov.w   #512-1,&TBCCR0          ; PWM Period
SetupC1     mov.w   #OUTMOD_7,&TBCCTL1      ; CCR1 reset/set
            mov.w   #384,&TBCCR1            ; CCR1 PWM Duty Cycle	
SetupC2     mov.w   #OUTMOD_7,&TBCCTL2      ; CCR2 reset/set
            mov.w   #128,&TBCCR2            ; CCR2 PWM duty cycle	
SetupTB     mov.w   #TBSSEL_1+MC_1,&TBCTL   ; ACLK, upmode
                                            ;					
Mainloop    bis.w   #CPUOFF,SR              ; CPU off
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
