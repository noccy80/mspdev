;******************************************************************************
;   MSP430FG479 Demo - Timer_B, Toggle P4.6, CCR0 Cont. Mode ISR, DCO SMCLK
;
;   Description: Toggle P4.6 using software and TB_0 ISR. Toggles every
;   50000 SMCLK cycles. SMCLK provides clock source for TBCLK. During the
;   TB_0 ISR, P4.6 is toggled and 50000 additional cycles are added
;   to CCR0. TB_0 ISR is triggered every 50000 cycles. CPU is used only
;   during TB_ISR.
;   ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO
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
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP4     bis.b   #040h,&P4DIR            ; P4.6 output
SetupC0     mov.w   #CCIE,&TBCCTL0          ; CCR0 interrupt enabled
            mov.w   #50000,&TBCCR0          ;
SetupTB     mov.w   #TBSSEL_2+MC_2,&TBCTL   ; SMCLK, continuous mode
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
TB0_ISR;    Toggle P4.6
;------------------------------------------------------------------------------
            xor.b   #040h,&P4OUT            ; Toggle P4.6
            add.w   #50000,&TBCCR0          ; Add Offset to CCR0
            reti                            ;		
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect    ".reset"            	; RESET Vector
            .short   RESET                  ;
            .sect    ".int13"          ; Timer_A0 Vector
            .short   TB0_ISR                 ;
            .end