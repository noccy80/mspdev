;******************************************************************************
;   MSP430F41x2 Demo - Timer_A, Toggle P5.1, CCR0 Cont. Mode ISR, DCO SMCLK
;
;   Description: Toggle P5.1 using software and TA_0 ISR. Toggles every
;   50000 SMCLK cycles. SMCLK provides clock source for TACLK.
;   During the TA_0 ISR, P5.1 is toggled and 50000 clock cycles are added to
;   CCR0. TA_0 ISR is triggered every 50000 cycles. CPU is normally off and
;   used only during TA_ISR.
;   ACLK = n/a, MCLK = SMCLK = TACLK = default DCO
;
;                MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;  P. Thanigai
;  Texas Instruments Inc.
;  January 2009
;  Built with CCE Version: 3.1   
;******************************************************************************
 .cdecls C,LIST, "msp430x41x2.h" 

            .global _main
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
_main
RESET       mov.w   #0400h,SP               ; Initialize stack pointer
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
            add.w   #50000,&CCR0            ; Add Offset to CCR0
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".reset"            	; RESET Vector
            .short   RESET                  ;
            .sect    ".int06"               ; Timer_A0 Vector
            .short   TA0_ISR                ;
            .end
