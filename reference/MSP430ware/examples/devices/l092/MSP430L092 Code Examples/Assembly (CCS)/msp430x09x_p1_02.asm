;******************************************************************************
; MSP430x09x Demo - Software Port Interrupt Service on P1.3 from LPM4
;
;  Description: A hi/low transition on P1.3 will trigger P1_ISR which,
;  toggles P1.0. LPM4 current can be measured
;  with all unused Px.x configured as output or inputs
;  pulled high or low, and ensure the P1.3 interrupt input does not float.
;  ACLK = n/a, MCLK = SMCLK = default DCO
;
;               MSP430x09x
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;     /|\   |                 |
;      --o--|P1.3         P1.0|-->Output
;     \|/
;
;  D.Dang/D.Archbold/D.Szmulewicz
;  Texas Instruments Inc.
;  Built with CCS version 4.2.0
;******************************************************************************

 .cdecls C,LIST,"msp430x09x.h"
;-------------------------------------------------------------------------------
            .global main
            .text                           ; Assemble to memory
;-------------------------------------------------------------------------------
main 
            mov.w   #WDTPW + WDTHOLD,&WDTCTL ; Stop WDT  
            bis.b   #BIT0,&P1DIR            ; Set P1.0 to output direction
            bis.b   #BIT3,&P1IE             ; P1.3 interrupt enabled
            bis.b   #BIT3,&P1IES            ; P1.3 Hi/lo edge
            bic.b   #BIT3,&P1IFG            ; P1.3 IFG cleared
            bis.w   #LPM4+GIE,SR            ; LPM4, enable interrupts
            nop                             ; Required only for debugger

;-------------------------------------------------------------------------------
P1_ISR                                      ; Toggle P1.0 Output
;-------------------------------------------------------------------------------
            xor.b   #BIT0,&P1OUT            ; P1.0 = toggle
            bic.b   #BIT3,&P1IFG            ; P1.3 IFG cleared
            reti  
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".int08"                ; Port1_vector
            .short  P1_ISR                  ; P1.x Vector
            .end