;*******************************************************************************
;   MSP430F22x4 Demo - Timer_B, Toggle P1.0, TBCCR0 Cont. Mode ISR, DCO SMCLK
;
;   Description: Toggle P1.0 using software and TB_0 ISR. Toggles every
;   50000 SMCLK cycles. SMCLK provides clock source for TBCLK.
;   During the TB_0 ISR, P1.0 is toggled and 50000 clock cycles are added to
;   TBCCR0. TB_0 ISR is triggered every 50000 cycles. CPU is normally off and
;   used only during TB_ISR.
;   ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~1.2MHz
;
;                 MSP430F22x4
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
SetupC0     mov.w   #CCIE,&TBCCTL0          ; TBCCR0 interrupt enabled
            mov.w   #50000,&TBCCR0          ;
SetupTB     mov.w   #TBSSEL_2+MC_2,&TBCTL   ; SMCLK, contmode
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
TB0_ISR;    Toggle P1.0
;-------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            add.w   #50000,&TBCCR0          ; Add Offset to TBCCR0
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
