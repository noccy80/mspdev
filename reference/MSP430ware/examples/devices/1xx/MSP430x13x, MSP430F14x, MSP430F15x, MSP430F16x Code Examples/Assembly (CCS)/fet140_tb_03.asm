;******************************************************************************
;   MSP-FET430P140 Demo - Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
;
;   Description: Toggle P1.0 using software and Timer_B overflow ISR.
;   In this example an ISR triggers when TB overflows. Inside the TB
;   overflow ISR P1.0 is toggled. Toggle rate is approximatlely 12Hz.
;   ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~800kHz
;
;                MSP430F149
;             -----------------
;         /|\|              XIN|-
;          | |                 |
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
SetupTB     mov.w   #TBSSEL_2+MC_2+TBIE,&TBCTL  ; SMCLK, cont. mode, interrupt
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;------------------------------------------------------------------------------
TBX_ISR;    Common ISR for TBCCR1-6 and overflow
;------------------------------------------------------------------------------
            add.w   &TBIV,PC                ; Add Timer_B offset vector
            reti                            ; TBCCR0 - no source
            reti                            ; TBCCR1
            reti                            ; TBCCR2
            reti                            ; TBCCR3
            reti                            ; TBCCR4
            reti                            ; TBCCR5
            reti                            ; TBCCR6
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
