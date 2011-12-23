;******************************************************************************
;   MSP430F54xA Demo - Timer_B, PWM TB1-6, Up Mode, DCO SMCLK
;
;   Description: This program generates six PWM outputs on P4 using
;   Timer_B configured for up mode. The value in CCR0, 512-1, defines the PWM
;   period and the values in CCR1-6 the PWM duty cycles. Using ~1048kHz SMCLK
;   as TBCLK, the timer period is ~488us.
;   ACLK = 32kHz, SMCLK = MCLK = TBCLK = default DCO ~1048kHz.
;
;                MSP430F5438A
;             -----------------
;         /|\|              XIN|-
;          | |                 |  32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P4.1/TB1|--> CCR1 - 75% PWM
;            |         P4.2/TB2|--> CCR2 - 25% PWM
;            |         P4.3/TB3|--> CCR3 - 12.5% PWM
;            |         P4.4/TB4|--> CCR4 - 6.26% PWM
;            |         P4.5/TB5|--> CCR5 - 3.13% PWM
;            |         P4.6/TB6|--> CCR6 - 1.566% PWM
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 
;******************************************************************************

    .cdecls C,LIST,"msp430x54xA.h"

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            bis.b   #0x7E,&P4SEL            ; P4 option select
            bis.b   #0x7E,&P4DIR            ; P4 outputs

            mov.w   #512-1,&TBCCR0          ; PWM Period
            mov.w   #OUTMOD_7,&TBCCTL1      ; CCR1 reset/set
            mov.w   #383,&TBCCR1            ; CCR1 PWM Duty Cycle	
            mov.w   #OUTMOD_7,&TBCCTL2      ; CCR2 reset/set
            mov.w   #128,&TBCCR2            ; CCR2 PWM duty cycle	
            mov.w   #OUTMOD_7,&TBCCTL3      ; CCR3 reset/set
            mov.w   #64,&TBCCR3             ; CCR3 PWM duty cycle	
            mov.w   #OUTMOD_7,&TBCCTL4      ; CCR4 reset/set
            mov.w   #32,&TBCCR4             ; CCR4 PWM duty cycle	
            mov.w   #OUTMOD_7,&TBCCTL5      ; CCR5 reset/set
            mov.w   #16,&TBCCR5             ; CCR5 PWM duty cycle	
            mov.w   #OUTMOD_7,&TBCCTL6      ; CCR6 reset/set
            mov.w   #8,&TBCCR6              ; CCR6 PWM duty cycle	
            mov.w   #TBSSEL_2 + MC_1 + TBCLR,&TBCTL
                                            ; SMCLK, upmode, clear TBR

            bis.w   #LPM0 + GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; For debugger

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
