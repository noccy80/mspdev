;*******************************************************************************
;   MSP430F22x4 Demo - Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
;
;   Description: Toggle P1.0 using software and the Timer_B overflow ISR.
;   In this example an ISR triggers when TB overflows. Inside the ISR P1.0
;   is toggled. Toggle rate is exactly 0.5Hz. Proper use of the TBIV
;   interrupt vector generator is demonstrated.
;   ACLK = TBCLK = 32kHz, MCLK = SMCLK = default DCO ~1.2MHz
;   //* An external watch crystal on XIN XOUT is required for ACLK *//
;
;                 MSP430F22x4
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
SetupTB     mov.w   #TBSSEL_1+MC_2+TBIE,&TBCTL  ; ACLK, contmode, interrupt
                                            ;
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
TBX_ISR;    Common ISR for overflow
;-------------------------------------------------------------------------------
            add.w   &TBIV,PC                ; Add Timer_B offset vector
            reti                            ;
            reti                            ; TBCCR1 not used
            reti                            ; TBCCR2 not used
            reti                            ;
            reti                            ;
            reti                            ;
            reti                            ;
TB_over     xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int12"                ; Timer_B1 Vector
            .short  TBX_ISR                 ;
            .end
