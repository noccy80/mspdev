;******************************************************************************
;   MSP430xG46x Demo - Timer_B, Toggle P5.1, TBCCR0 Cont. Mode ISR, DCO SMCLK
;
;   Description: Toggle P5.1 using software and TB_0 ISR. Toggles every
;   50000 SMCLK cycles. SMCLK provides clock source for TACLK.
;   During the TB_0 ISR, P5.1 is toggled and 50000 clock cycles are added
;   to TBCCR0. TB_0 ISR is triggered every 50000 cycles. CPU is normally off
;   and used only during TB_ISR.
;   ACLK = 32.768kHz, MCLK = SMCLK = TACLK = default DCO
;
;                 MSP430xG461x
;             -----------------
;         /|\|              XIN|-
;          | |                 |  32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps

OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more

SetupP5     bis.b   #002h,&P5DIR            ; P5.1 output
SetupC0     mov.w   #CCIE,&TBCCTL0          ; TBCCR0 interrupt enabled
            mov.w   #50000,&TBCCR0          ;
SetupTB     mov.w   #TBSSEL_2+MC_2,&TBCTL   ; SMCLK, continuous mode
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;------------------------------------------------------------------------------
TB0_ISR;    Toggle P5.1
;------------------------------------------------------------------------------
            xor.b   #002h,&P5OUT            ; Toggle P5.1
            add.w   #50000,&TBCCR0          ; Add Offset to TBCCR0
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect	".reset"            	; MSP430 RESET Vector
            .short   RESET
            .sect	".int29"          		; Timer_B0 Vector
            .short   TB0_ISR                 ;
            .end
