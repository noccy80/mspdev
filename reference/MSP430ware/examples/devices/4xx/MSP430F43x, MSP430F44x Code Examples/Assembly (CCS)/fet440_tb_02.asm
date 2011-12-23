;******************************************************************************
;   MSP-FET430P440 Demo - Timer_B, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
;
;   Description: This program toggles P5.1 using software and TB_0 ISR.
;   Timer_B is configured for up mode, thus the timer overflows when
;   TBR counts to TBCCR0.  In this example, TBCCR0 is loaded with 20000.
;   ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO
;
;                MSP430F449
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;   M. Buccini / A. Dannenberg
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST, "msp430x44x.h"
;------------------------------------------------------------------------------
            .text                  			; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP5     bis.b   #002h,&P5DIR            ; P5.1 output
SetupC0     mov.w   #CCIE,&TBCCTL0          ; TBCCR0 interrupt enabled
            mov.w   #20000,&TBCCR0          ;
SetupTB     mov.w   #TBSSEL_2+MC_1,&TBCTL   ; SMCLK, upmode
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
TB0_ISR;    Toggle P5.1
;------------------------------------------------------------------------------
            xor.b   #002h,&P5OUT            ; Toggle P5.1
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .sect   ".int13"                ; Timer_B0 Vector
            .short  TB0_ISR                 ;
            .end
