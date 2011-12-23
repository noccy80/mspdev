;******************************************************************************
;   MSP430FG479 Demo - Timer_A, Toggle P4.6, CCR0 Up Mode ISR, DCO SMCLK
;
;   Description: Toggle P4.6 using software and TA_0 ISR. Timer_A is
;   configured for up mode, thus the timer overflows when TAR counts to CCR0.
;   In this example, CCR0 is loaded with 20000.
;   ACLK = n/a, MCLK = SMCLK = TACLK = default DCO
;
;                MSP430FG479
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P4.6|-->LED
;
;   P.Thanigai
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials Version: 3.0
;******************************************************************************
 .cdecls C,LIST, "msp430xG47x.h" 
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
SetupWDT    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP4     bis.b   #040h,&P4DIR            ; P4.6 output
SetupC0     mov.w   #CCIE,&CCTL0            ; CCR0 interrupt enabled
            mov.w   #20000,&CCR0            ;
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, up mode
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-----------------------------------------------------------------------------
TA0_ISR;    Toggle P4.6
;-----------------------------------------------------------------------------
            xor.b   #040h,&P4OUT            ; Toggle P4.6
            reti                            ;		
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect    ".reset"            	; RESET Vector
            .short   RESET                  ;
            .sect    ".int06"          ; Timer_A0 Vector
            .short   TA0_ISR                 ;
            .end
