;******************************************************************************
;   MSP-FET430P430 Demo - Timer_A, Toggle P5.1, CCR0 Up Mode ISR, DCO SMCLK
;
;   Description: Toggle P5.1 using software and TA_0 ISR. Timer_A is
;   configured for up mode, thus the timer overflows when TAR counts to CCR0.
;   In this example, CCR0 is loaded with 20000.
;   ACLK = n/a, MCLK = SMCLK = TACLK = default DCO
;
;                MSP430FG439
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;   M. Buccini / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;------------------------------------------------------------------------------
            .text                  ;
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
SetupWDT    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP5     bis.b   #002h,&P5DIR            ; P5.1 output
SetupC0     mov.w   #CCIE,&CCTL0            ; CCR0 interrupt enabled
            mov.w   #20000,&CCR0            ;
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, up mode
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-----------------------------------------------------------------------------
TA0_ISR;    Toggle P5.1
;-----------------------------------------------------------------------------
            xor.b   #002h,&P5OUT            ; Toggle P5.1
            reti                            ;		
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .sect   ".int06"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end
