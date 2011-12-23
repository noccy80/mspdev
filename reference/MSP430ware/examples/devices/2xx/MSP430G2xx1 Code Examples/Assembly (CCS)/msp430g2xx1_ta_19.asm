;*******************************************************************************
;   MSP430G2xx1 Demo - Timer_A, PWM TA1, Up/Down Mode, DCO SMCLK
;
;   Description: This program generates one PWM output on P1.1 using
;   Timer_A configured for up/down mode. The value in CCR0, 128, defines
;   the PWM period/2 and the value in CCR1 the PWM duty cycle.
;   A 75% duty cycle is on P1.2.
;   SMCLK = MCLK = TACLK = default DCO .
;
;                MSP430G2xx1
;             -----------------
;         /|\|              XIN|-
;          | |                 |
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
SetupTA     mov.w   #TASSEL_2+MC_3,&TACTL   ; SMCLK, updown mode
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
