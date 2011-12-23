;*******************************************************************************
;   MSP430x11x1 Demo - Timer_A, PWM TA1-2, Up Mode, 32kHz ACLK
;
;   Description: This program generates two PWM outputs on P1.2,3 using
;   Timer_A configured for up mode. The value in CCR0, 512-1, defines the PWM
;   period and the values in CCR1 and CCR2 the PWM duty cycles. Using 32kHz
;   ACLK as TACLK, the timer period is 15.6ms with a 75% duty cycle on P1.2
;   and 25% on P1.3. Normal operating mode is LPM3.
;   ACLK = TACLK = LFXT1 = 32768Hz, MCLK = default DCO ~800kHz.
;   ;* External watch crystal on XIN XOUT is required for ACLK *//	
;
;                MSP430F1121
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P1.2/TA1|--> CCR1 - 75% PWM
;            |         P1.3/TA2|--> CCR2 - 25% PWM
;
;   M. Buccini / Z. Albus
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"
;-------------------------------------------------------------------------------
            .text                           ; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #00Ch,&P1DIR            ; P1.2 and P1.3 outputs
            bis.b   #00Ch,&P1SEL            ; P1.2 and P1.3 TA1/2 option
SetupC0     mov.w   #512-1,&CCR0            ; PWM Period
SetupC1     mov.w   #OUTMOD_7,&CCTL1        ; CCR1 reset/set
            mov.w   #384,&CCR1              ; CCR1 PWM Duty Cycle	
SetupC2     mov.w   #OUTMOD_7,&CCTL2        ; CCR2 reset/set
            mov.w   #128,&CCR2              ; CCR2 PWM duty cycle	
SetupTA     mov.w   #TASSEL_1+MC_1,&TACTL   ; ACLK, upmode
                                            ;					
Mainloop    bis.w   #LPM3,SR                ; Remain in LPM3
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
