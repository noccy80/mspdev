;*******************************************************************************
;   MSP430G2x11 Demo - Comp_A, Output Reference Voltages on P1.1
;
;   Description: Output comparator_A reference levels on P1.1.  Program will
;   cycle through the on-chip comparator_A reference voltages with output on
;   P1.1. Normal mode is LPM0 with TA0 triggering interrupt for next mode.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;             MSP430G2x11
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |         CA1/P1.1|-->Vref
;            |                 |
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2211.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            mov.b   #P2CA4,&CACTL2          ; CA1
SetupC0     mov.w   #CCIE,&CCTL0            ; CCR0 interrupt enabled
SetupTA     mov.w   #TASSEL_2+ID_3+MC_2,&TACTL   ; SMCLK/8, contmode
            eint                            ; General enable interrupts
                                            ;
Mainloop    clr.b   &CACTL1                 ; No reference voltage
            bis.w   #CPUOFF,SR              ; CPU off
Ref1        mov.b   #CAREF0+CAON,&CACTL1    ; 0.25*Vcc, Comp. on
            bis.w   #CPUOFF,SR              ; CPU off
Ref2        mov.b   #CAREF1+CAON,&CACTL1    ; 0.5*Vcc, Comp. on
            bis.w   #CPUOFF,SR              ; CPU off
Ref3        mov.b   #CAREF1+CAREF0+CAON,&CACTL1     ; 0.55V on P2.3, Comp. on
            bis.w   #CPUOFF,SR              ; CPU off
            jmp     Mainloop                ;

;-------------------------------------------------------------------------------
TA0_ISR;    Exit LPM0
;-------------------------------------------------------------------------------
            bic.w   #CPUOFF,0(SP)           ; Exit LPM0 on RETI
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int09"                ; TimerA0 Vector
            .short  TA0_ISR                 ;        
            .end
