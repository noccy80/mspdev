;******************************************************************************
;   MSP-FET430P430 Demo - Timer_A, PWM TA1-2 Up Mode, 32kHz ACLK
;
;   Description: This program outputs two PWM signals on P1.2 and P2.0
;   using Timer_A configured for up mode. The value in CCR0 defines the PWM
;   period and the values in CCR1 and CCR2 the PWM duty cycles. Using 32kHz
;   ACLK as TACLK, the timer period is 15.6ms with a 75% duty cycle on P1.2
;   and 25% on P2.0. Normal operating mode is LPM3.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   ;* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430FG439
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P1.2/TA1|--> CCR1 - 75% PWM
;            |         P2.0/TA2|--> CCR2 - 25% PWM
;
;   M. Buccini / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with IAR Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
SetupP1     bis.b   #004h,&P1DIR            ; P1.2 output
            bis.b   #004h,&P1SEL            ; P1.2 TA1 option select
SetupP2     bis.b   #001h,&P2DIR            ; P2.0 output
            bis.b   #001h,&P2SEL            ; P2.0 TA2 option select
SetupC0     mov.w   #512-1,&CCR0            ; PWM Period
SetupC1     mov.w   #OUTMOD_7,&CCTL1        ; CCR1 reset/set
            mov.w   #384,&CCR1              ; CCR1 PWM Duty Cycle	
SetupC2     mov.w   #OUTMOD_7,&CCTL2        ; CCR2 reset/set
            mov.w   #128,&CCR2              ; CCR2 PWM duty cycle	
SetupTA     mov.w   #TASSEL_1+MC_1,&TACTL   ; ACLK, up mode
                                            ;					
Mainloop    bis.w   #LPM3,SR                ; Remain in LPM3
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end
