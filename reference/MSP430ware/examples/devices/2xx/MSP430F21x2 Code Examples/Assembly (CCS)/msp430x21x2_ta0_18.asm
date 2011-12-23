;******************************************************************************
;  MSP430F21x2 Demo - Timer0_A3, PWM TA0_1 - TA0_2, Up Mode, HF XTAL ACLK
;
;  Description: This program generates two PWM outputs on P1.2,3 using
;  Timer0_A3 configured for up mode. The value in TA0CCR0, 512-1, defines the
;  period and the values in TA0CCR1 and TA0CCR2 the PWM duty cycles. Using
;  HF XTAL ACLK as TA0CLK, the timer period is HF XTAL/512 with a 75% duty
;  cycle on P1.2 and 25% on P1.3.
;  ACLK = MCLK = TA0CLK = HF XTAL
;  ;* HF XTAL REQUIRED AND NOT INSTALLED ON FET *;
;  ;* Min Vcc required varies with MCLK frequency - refer to datasheet *;
;
;               MSP430F21x2
;            -----------------
;        /|\|              XIN|-
;         | |                 | HF XTAL (3  16MHz crystal or resonator)
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
SetupBC     bis.b   #XTS,&BCSCTL1           ; LFXT1 = HF XTAL
            mov.b   #LFXT1S1,&BCSCTL3       ; LFXT1S1 = 3-16Mhz
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_3,&BCSCTL2        ; MCLK = LFXT1
SetupC0     mov.w   #512-1,&TA0CCR0          ; PWM Period
SetupC1     mov.w   #OUTMOD_7,&TA0CCTL1      ; TACCR1 reset/set
            mov.w   #384,&TA0CCR1            ; TACCR1 PWM Duty Cycle
SetupC2     mov.w   #OUTMOD_7,&TA0CCTL2      ; TACCR2 reset/set
            mov.w   #128,&TA0CCR2            ; TACCR2 PWM duty cycle
SetupTA     mov.w   #TASSEL_1+MC_1,&TA0CTL   ; ACLK, upmode
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
