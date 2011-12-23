;*******************************************************************************
;   MSP430G2xx1 Demo - Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK
;
;   Description: Toggle P1.1 using hardware TA0 output. Timer_A is configured
;   for up mode with CCR0 defining period, TA0 also output on P1.1. In this
;   example, CCR0 is loaded with 500 and TA0 will toggle P1.1 at TACLK/500.
;   Thus the output frequency on P1.1 will be the TACLK/1000. No CPU or
;   software resources required.
;   As coded with TACLK = SMCLK, P1.1 output frequency is ~1000000/1000.
;   SMCLK = MCLK = TACLK = default DCO
;
;                MSP430G2xx1
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |         P1.1/TA0|--> SMCLK/1000
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
SetupP1     bis.b   #002h,&P1DIR            ; P1.1 output
            bis.b   #002h,&P1SEL            ; P1.1 option slect
SetupC0     mov.w   #OUTMOD_4,&CCTL0        ; CCR0 toggle, upmode
            mov.w   #500-1,&CCR0            ;
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, clear TAR
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

