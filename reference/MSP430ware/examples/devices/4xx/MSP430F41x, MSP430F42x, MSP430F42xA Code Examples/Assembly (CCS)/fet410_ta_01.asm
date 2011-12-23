;******************************************************************************
;   MSP-FET430P410 Demo - Timer_A, Toggle P5.1, CCR0 Cont. Mode ISR, DCO SMCLK
;
;   Description: Toggle P5.1 using software and TA_0 ISR. Toggles every
;   50000 SMCLK cycles. SMCLK provides clock source for TACLK.
;   During the TA_0 ISR P5.1 is toggled and 50000 clock cycles are added to
;   CCR0. TA_0 ISR is triggered every 50000 cycles. CPU is normally off and
;   used only during TA_ISR.
;   ACLK = n/a, MCLK = SMCLK = TACLK = default DCO
;
;                MSP430F413
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;   M. Buccini / S. Karthikeyan
;   Texas Instruments
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x41x.h"
;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP5     bis.b   #002h,&P5DIR            ; P5.1 output
SetupC0     mov.w   #CCIE,&CCTL0            ; CCR0 interrupt enabled
            mov.w   #50000,&CCR0            ;
SetupTA     mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, continuous mode
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;    Toggle P5.1
;------------------------------------------------------------------------------
            xor.b   #002h,&P5OUT            ; Toggle P5.1
            add.w   #50000,&CCR0            ; Add offset to CCR0
            reti                            ;		
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect     ".reset"                  ; RESET Vector
            .short  RESET                   ;
            .sect   ".int06"                  ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end
