;******************************************************************************
;   MSP-FET430P140 Demo - Timer_A, PWM TA1-2, Up Mode, XT2 HF XTAL SMCLK
;
;   Description: This program generates two PWM outputs on P1.2,3 using
;   Timer_A configured for up mode. The value in CCR0, 512-1, defines the PWM
;   period and the values in CCR1 and CCR2 the PWM duty cycles.
;   ACLK = n/a, MCLK = SMCLK = TACLK = XT2 = HF XTAL
;   //* External crystal installed on XT2IN XT2OUT is required for SMCLK *//	
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
;
;                MSP430F149
;             -----------------
;         /|\|            XT2IN|-
;          | |                 | HF XTAL (455k - 8MHz)
;          --|RST        XT2OUT|-
;            |                 |
;            |         P1.2/TA1|--> CCR1 - 75% PWM
;            |         P1.3/TA2|--> CCR2 - 25% PWM
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
SetupP1     bis.b   #00Ch,&P1DIR            ; P1.2 and P1.3 outputs
            bis.b   #00Ch,&P1SEL            ; P1.2 and P1.3 TA1/2 option
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
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
