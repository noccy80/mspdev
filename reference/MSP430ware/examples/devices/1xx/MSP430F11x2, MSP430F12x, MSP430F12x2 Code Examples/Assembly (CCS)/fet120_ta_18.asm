;******************************************************************************
;   MSP-FET430P120 Demo - Timer_A, PWM TA1-2, Up Mode, HF XTAL ACLK
;
;   Description: This program generates two PWM outputs on P1.2,3 using
;   Timer_A configured for up mode. The value in CCR0, 512-1, defines the PWM
;   period and the values in CCR1 and CCR2 the PWM duty cycles. Using HF XTAL
;   ACLK as TACLK, the timer period is HF XTAL/512 with a 75% duty cycle on
;   P1.2 and 25% on P1.3.
;   ACLK = MCLK = TACLK = HF XTAL
;   //* HF XTAL REQUIRED AND NOT INSTALLED ON FET *//
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
;
;                MSP430F123(2)
;             -----------------
;         /|\|              XIN|-
;          | |                 | HF XTAL (455k - 8MHz)
;          --|RST          XOUT|-
;            |                 |
;            |         P1.2/TA1|--> CCR1 - 75% PWM
;            |         P1.3/TA2|--> CCR2 - 25% PWM
;
;   M. Buccini / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #00Ch,&P1DIR            ; P1.2 and P1.3 output
            bis.b   #00Ch,&P1SEL            ; P1.2 and P1.3 TA1/2 otions
SetupBC     bis.b   #XTS,&BCSCTL1           ; LFXT1 = HF XTAL
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_3,&BCSCTL2        ; MCLK = LFXT1
SetupC0     mov.w   #512-1,&CCR0            ; PWM Period
SetupC1     mov.w   #OUTMOD_7,&CCTL1        ; CCR1 reset/set
            mov.w   #384,&CCR1              ; CCR1 PWM Duty Cycle	
SetupC2     mov.w   #OUTMOD_7,&CCTL2        ; CCR2 reset/set
            mov.w   #128,&CCR2              ; CCR2 PWM duty cycle	
SetupTA     mov.w   #TASSEL_1+MC_1,&TACTL   ; ACLK, upmode
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
