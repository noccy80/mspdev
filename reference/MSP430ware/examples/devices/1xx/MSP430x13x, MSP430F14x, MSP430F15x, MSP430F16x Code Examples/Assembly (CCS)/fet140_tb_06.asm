;******************************************************************************
;   MSP-FET430P140 Demo - Timer_B, Toggle P1.0, CCR1 Cont. Mode ISR, DCO SMCLK
;
;   Description: Toggle P1.0 using software and TB_1 ISR. Toggles every
;   50000 SMCLK cycles. SMCLK provides clock source for TBCLK.
;   During the TB_01 ISR, P1.0 is toggled and 50000 clock cycles are added to
;   CCR0. TB_1 ISR is triggered every 50000 cycles. CPU is normally off and
;   used only during TB_ISR. Proper use of the TBIV interrupt vector generator
;   is demonstrated.
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
;-----------------------------------------------------------------------------
            .text                           ; Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupC1     mov.w   #CCIE,&TBCCTL1          ; CCR1 interrupt enabled
            mov.w   #50000,&TBCCR1          ;
SetupTA     mov.w   #TBSSEL_2+MC_2,&TBCTL   ; SMCLK, contmode
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;------------------------------------------------------------------------------
TBX_ISR;    Common ISR for TBCCR1-6 and overflow
;------------------------------------------------------------------------------
            add.w   &TBIV,PC                ; Add Timer_B offset vector
            reti                            ; TBCCR0 - no source
            jmp     TBCCR1_ISR              ; TBCCR1
            reti                            ; TBCCR2
            reti                            ; TBCCR3
            reti                            ; TBCCR4
            reti                            ; TBCCR5
            reti                            ; TBCCR6
TB_over     reti                            ; Return from overflow ISR		
                                            ;
TBCCR1_ISR  add.w   #50000,&TBCCR1          ; Offset until next interrupt
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR		
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int12"                ; Timer_BX Vector
            .short  TBX_ISR                 ;
            .end
