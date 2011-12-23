;******************************************************************************
;   MSP430x261x Demo - Timer_B, Toggle P1.0, TBCCR0 Up Mode ISR, DCO SMCLK
;
;   Description: Toggle P1.0 using software and TB_0 ISR. Timer_B is
;   configured for up mode, thus the timer overflows when TBR counts to TBCCR0.
;   In this example, TBCCR0 is loaded with 20000.
;   ACLK = 32.768kHz, MCLK = SMCLK = TACLK = default DCO
;
;                MSP430F241x
;                MSP430F261x
;             -----------------
;         /|\|              XIN|-
;          | |                 |  32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more

SetupP5     bis.b   #BIT0,&P1DIR            ; P1.0 output
SetupC0     mov.w   #CCIE,&TBCCTL0          ; TBCCR0 interrupt enabled
            mov.w   #20000,&TBCCR0          ;
SetupTB     mov.w   #TBSSEL_2+MC_1,&TBCTL   ; SMCLK, up mode
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-----------------------------------------------------------------------------
TB0_ISR;    Toggle P1.0
;-----------------------------------------------------------------------------
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; MSP430 RESET Vector
            .short  RESET
            .sect   ".int29"          ; Timer_B0 Vector
            .short  TB0_ISR                 ;
            .end
            