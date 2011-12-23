;*******************************************************************************
;   MSP430F22x4 Demo - Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
;
;   Description: This program generates two PWM outputs on P1.2,3 using
;   Timer_A configured for up mode. The value in TACCR0, 512-1, defines the PWM
;   period and the values in TACCR1 and TACCR2 the PWM duty cycles. Using 32kHz
;   ACLK as TACLK, the timer period is 15.6ms with a 75% duty cycle on P1.2
;   and 25% on P1.3. Normal operating mode is LPM3.
;   ACLK = TACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO ~1.2MHz
;   //* External watch crystal on XIN XOUT is required for ACLK *//
;
;                MSP430F22x4
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P1.2/TA1|--> TACCR1 - 75% PWM
;            |         P1.3/TA2|--> TACCR2 - 25% PWM
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
                              
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #00Ch,&P1DIR            ; P1.2 and P1.3 outputs
            bis.b   #00Ch,&P1SEL            ; P1.2 and P1.3 TA1/2 option
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
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
