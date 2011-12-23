;******************************************************************************
;   MSP430x24x Demo - Timer_B, Toggle P1.0, TBCCR0 Cont. Mode ISR, DCO SMCLK
;
;   Description: Toggle P1.0 using software and TB_0 ISR. Toggles every
;   50000 SMCLK cycles. SMCLK provides clock source for TACLK.
;   During the TB_0 ISR, P1.0 is toggled and 50000 clock cycles are added
;   to TBCCR0. TB_0 ISR is triggered every 50000 cycles. CPU is normally off
;   and used only during TB_ISR.
;   ACLK = 32.768kHz, MCLK = SMCLK = TACLK = default DCO
;
;                 MSP430x249
;             -----------------
;         /|\|              XIN|-
;          | |                 |  32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more

SetupP5     bis.b   #BIT0,&P1DIR            ; P1.0 output
SetupC0     mov.w   #CCIE,&TBCCTL0          ; TBCCR0 interrupt enabled
            mov.w   #50000,&TBCCR0          ;
SetupTB     mov.w   #TBSSEL_2+MC_2,&TBCTL   ; SMCLK, continuous mode
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;------------------------------------------------------------------------------
TB0_ISR;    Toggle F249
;------------------------------------------------------------------------------
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0
            add.w   #50000,&TBCCR0          ; Add Offset to TBCCR0
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ;  MSP430 RESET Vector
            .short  RESET                    ;
            .sect     ".int29"          ; Timer_B0 Vector
            .short   TB0_ISR                 ;
            .end
