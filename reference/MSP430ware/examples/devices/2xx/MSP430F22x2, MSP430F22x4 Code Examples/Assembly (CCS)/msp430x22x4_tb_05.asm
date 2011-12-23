;*******************************************************************************
;   MSP430F22x4 Demo - Timer_B, Toggle P1.0, TBCCR0 Up Mode ISR, 32kHz ACLK
;
;   Description: Toggle P1.0 using software and the TB_0 ISR. Timer_B is
;   configured for up mode, thus the timer overflows when TBR counts
;   to TBCCR0. In this example, TBCCR0 is loaded with 1000-1.
;   Toggle rate = 32768Hz/(2*1000) = 16.384Hz
;   ACLK = TBCLK = 32768Hz, MCLK = SMCLK = default DCO ~1.2MHz
;   //* An external watch crystal on XIN XOUT is required for ACLK *//
;
;                MSP430F22x4
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
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
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupC0     mov.w   #CCIE,&TBCCTL0          ; TBCCR0 interrupt enabled
            mov.w   #1000-1,&TBCCR0         ; TBCCR0 counts to 1000
SetupTB     mov.w   #TBSSEL_1+MC_1,&TBCTL   ; ACLK, upmode
                                            ;
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
TB0_ISR;    Toggle P1.0
;-------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int13"                ; Timer_B0 Vector
            .short  TB0_ISR                 ;
            .end
