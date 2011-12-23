;*******************************************************************************
;   MSP430F22x4 Demo - Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK
;
;   Description: Toggle P1.0 using software and Timer_A overflow ISR.
;   In this example an ISR triggers when TA overflows. Inside the TA
;   overflow ISR P1.0 is toggled. Toggle rate is approximately 18Hz.
;   Proper use of the TAIV interrupt vector generator is demonstrated.
;   ACLK = n/a, MCLK = SMCLK = TACLK = default DCO ~1.2MHz
;
;                MSP430F22x4
;             -----------------
;         /|\|              XIN|-
;          | |                 |
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
SetupTA     mov.w   #TASSEL_2+MC_2+TAIE,&TACTL  ; SMCLK, contmode interrupt
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR for overflow
;-------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti
            reti                            ; TACCR1 not used
            reti                            ; TACCR2 not used
            reti
            reti
TA_over     xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end