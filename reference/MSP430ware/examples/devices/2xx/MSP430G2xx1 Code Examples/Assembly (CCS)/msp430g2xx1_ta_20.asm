;*******************************************************************************
;   MSP430G2xx1 Demo - Timer_A, PWM TA1-2, Up/Down Mode, 32kHz ACLK
;
;   Description: This program generates one PWM output on P1.2 using
;   Timer_A configured for up/down mode. The value in CCR0, 128, defines
;   the PWM period/2 and the value in CCR1 the PWM duty cycle.
;   Using 32kHz ACLK as TACLK, the timer period is 7.8ms with a 75% duty
;   cycle on P1.2. Normal operating mode is LPM3.
;   ACLK = TACLK = LFXT1 = 32768Hz, MCLK = default DCO.
;   //* External watch crystal on XIN XOUT is required for ACLK *//	
;
;                MSP430G2xx1
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P1.2/TA1|--> CCR1 - 75% PWM
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2231.h"

;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #00Ch,&P1DIR            ; P1.2 and P1.3 output
            bis.b   #00Ch,&P1SEL            ; P1.2 and P1.3 TA1/2 otions
SetupC0     mov.w   #128,&CCR0              ; PWM Period/2
SetupC1     mov.w   #OUTMOD_6,&CCTL1        ; CCR1 toggle/set
            mov.w   #32,&CCR1               ; CCR1 PWM Duty Cycle	
SetupTA     mov.w   #TASSEL_1+MC_3,&TACTL   ; ACLK, updown mode
                                            ;					
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
