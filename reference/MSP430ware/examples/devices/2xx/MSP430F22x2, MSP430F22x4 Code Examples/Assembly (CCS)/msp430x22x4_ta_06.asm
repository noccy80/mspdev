;*******************************************************************************
;   MSP430F22x4 Demo - Timer_A, Toggle P1.0, TACCR1 Cont. Mode ISR, DCO SMCLK
;
;   Description: Toggle P1.0 using software and TA_1 ISR. Toggles every
;   50000 SMCLK cycles. SMCLK provides clock source for TACLK.
;   During the TA_1 ISR, P1.0 is toggled and 50000 clock cycles are added to
;   TACCR0. TA_1 ISR is triggered every 50000 cycles. CPU is normally off and
;   used only during TA_ISR. Proper use of the TAIV interrupt vector generator
;   is demonstrated.
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
SetupC1     mov.w   #CCIE,&TACCTL1          ; TACCR1 interrupt enabled
            mov.w   #50000,&TACCR1          ;
SetupTA     mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, contmode
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR for TACCR1 and overflow
;-------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti                            ;
            jmp     TACCR1_ISR              ; TACCR1
            reti                            ; TACCR2 not used
            reti                            ;
            reti                            ;
            reti                            ; Overflow not used
                                            ;
TACCR1_ISR  add.w   #50000,&TACCR1          ; Offset until next interrupt
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from TACCR1 ISR
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end
