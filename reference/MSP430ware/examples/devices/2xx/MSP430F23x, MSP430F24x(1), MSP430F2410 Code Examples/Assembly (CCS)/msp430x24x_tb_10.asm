;******************************************************************************
;  MSP430F249 Demo - Timer_B, PWM TB1-6, Up Mode, 32kHz ACLK
;
;  Description: This program generates six PWM outputs on P4.1-6 using
;  Timer_B configured for up/down mode. The value in CCR0, 256, defines the
;  PWM period/2 and values in CCR1-6 the PWM duty cycles. Using 32kHz ACLK as 
;  TBCLK, the timer period is ~ 15.6ms.  Normal operating mode: LPM3.
;  ACLK = TBCLK = LFXT1 = 32768Hz, MCLK = default DCO ~1.045MHz.
;  //* External watch crystal installed on XIN XOUT is required for ACLK *//
;
;               MSP430F249
;            -----------------
;        /|\|              XIN|-
;         | |                 |  32KHz
;         --|RST          XOUT|-
;           |                 |
;           |         P4.1/TB1|--> CCR1 - 75% PWM
;           |         P4.2/TB2|--> CCR2 - 25% PWM
;           |         P4.3/TB3|--> CCR3 - 12.5% PWM
;           |         P4.4/TB4|--> CCR4 - 6.25% PWM
;           |         P4.5/TB5|--> CCR5 - 3.125% PWM
;           |         P4.6/TB6|--> CCR6 - 1.5625% PWM
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP4     mov.b   #07Eh, &P4DIR           ; P4.1 - P4.6 output
            mov.b   #07Eh, &P4SEL           ; P4.1 - P4.6 TBx options
SetupTA     mov.w   #256,&TBCCR0            ;PWM period
            mov.w   #OUTMOD_6, &TBCCTL1     ; CCR1 toggle/set
            mov.w   #064, &TBCCR1           ; CCR1 PWM duty cycle
            mov.w   #OUTMOD_6, &TBCCTL2     
            mov.w   #0192h, &TBCCR2          
            mov.w   #OUTMOD_6, &TBCCTL3     
            mov.w   #0224, &TBCCR3          
            mov.w   #OUTMOD_6, &TBCCTL4      
            mov.w   #0240, &TBCCR4          
            mov.w   #OUTMOD_6, &TBCCTL5      
            mov.w   #0248h, &TBCCR5           
            mov.w   #OUTMOD_6, &TBCCTL6      
            mov.w   #0252, &TBCCR6
            
            mov.w   #TBSSEL_1 + MC_3, &TBCTL  ;ACLK, up-down mode
                                            						
Mainloop    bis.w   #LPM3,SR                ; LPM3
            nop                             ; Required for debugger
                                                                        
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ;  MSP430 RESET Vector
            .short  RESET                    ;
            .end
