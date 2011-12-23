;******************************************************************************
;   MSP430x261x Demo - Timer_A, PWM TA1-2 Up Mode, 32kHz ACLK
;
;   Description: This program generates two PWM outputs on P1.2 and P1.3
;   using Timer_A in an upmode. The value in TACCR0 defines the period and the
;   values in TACCR1 and TACCR2 the PWM duty cycles. Using 32kHz ACLK as TACLK,
;   the timer period is 15.6ms with a 75% duty cycle on P1.2 and 25% on P1.3.
;   Normal operating mode is LPM3.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430F241x
;                MSP430F261x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P1.2/TA1|--> TACCR1 - 75% PWM
;            |         P1.3/TA2|--> TACCR2 - 25% PWM
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more

SetupP1     bis.b   #BIT2+BIT3,&P1DIR       ; P1.2, P1.3 output
            bis.b   #BIT2+BIT3,&P1SEL       ; P1.2, P1.3 TA1, TA2 option select
SetupC0     mov.w   #512-1,&TACCR0          ; PWM Period
SetupC1     mov.w   #OUTMOD_7,&TACCTL1      ; TACCR1 reset/set
            mov.w   #384,&TACCR1            ; TACCR1 PWM Duty Cycle	
SetupC2     mov.w   #OUTMOD_7,&TACCTL2      ; TACCR2 reset/set
            mov.w   #128,&TACCR2            ; TACCR2 PWM duty cycle	
SetupTA     mov.w   #TASSEL_1+MC_1,&TACTL   ; ACLK, upmode
                                            ;					
Mainloop    bis.w   #LPM3,SR                ; Remain in LPM3
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .end
