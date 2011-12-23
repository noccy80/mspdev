;******************************************************************************
;   MSP-FET430P140 Demo - Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
;
;   Description: Toggle P1.0 using software and the Timer_B overflow ISR.
;   In this example an ISR triggers when TB overflows. Inside the ISR P1.0
;   is toggled. Toggle rate is exactly 0.5Hz.
;   ACLK = TBCLK = 32768Hz, MCLK = SMCLK = default DCO ~800kHz
;   //* An external watch crystal on XIN XOUT is required for ACLK *//	
;
;                 MSP430F149
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;   M. Buccini / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupTB     mov.w   #TBSSEL_1+MC_2+TBIE,&TBCTL  ; ACLK, cont. mode, interrupt
                                            ;													
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
TBX_ISR;    Common ISR for TBCCR1-4 and overflow
;------------------------------------------------------------------------------
            add.w   &TBIV,PC                ; Add Timer_B offset vector
            reti                            ; CCR0 - no source
            reti                            ; CCR1
            reti                            ; CCR2
            reti                            ; CCR3
            reti                            ; CCR4
            reti                            ; CCR5
            reti                            ; CCR6
TB_over     xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int12"                ; Timer_BX Vector
            .short  TBX_ISR                 ;
            .end
