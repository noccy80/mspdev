;******************************************************************************
;   MSP430FG479 Demo - Timer_B, PWM TB1-2 Up Mode, 32kHz ACLK
;
;   Description: This program outputs two PWM signals on P2.2 and P2.3
;   using Timer_B configured for up mode. The value in CCR0 defines the PWM
;   period and the values in CCR1 and CCR2 the PWM duty cycles. Using 32kHz
;   ACLK as TBCLK, the timer period is 15.6ms. Normal operating mode is LPM3.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430FG479
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P2.2/TB1|--> CCR1 - 75% PWM
;            |         P2.3/TB2|--> CCR2 - 25% PWM
;
;   P.Thanigai
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials Version: 3.0
;******************************************************************************
 .cdecls C,LIST, "msp430xG47x.h" 
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
SetupPx     bis.b   #0ch,&P2DIR             ; P2.2,3 as outputs
            bis.b   #0ch,&P2SEL             ; P2.2,3 TB1-2 options
SetupC0     mov.w   #512-1,&TBCCR0          ; PWM Period
SetupC1     mov.w   #OUTMOD_7,&TBCCTL1      ; CCR1 reset/set
            mov.w   #384,&TBCCR1            ; CCR1 PWM Duty Cycle	
SetupC2     mov.w   #OUTMOD_7,&TBCCTL2      ; CCR2 reset/set
            mov.w   #128,&TBCCR2            ; CCR2 PWM duty cycle	
SetupTB     mov.w   #TBSSEL_1+MC_1,&TBCTL   ; ACLK, up mode
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
