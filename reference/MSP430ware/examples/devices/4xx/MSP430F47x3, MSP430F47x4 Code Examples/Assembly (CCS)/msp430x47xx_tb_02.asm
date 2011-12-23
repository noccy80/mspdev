;******************************************************************************
;   MSP430x47xx Demo - Timer_B, Toggle P5.1, TBCCR0 Up Mode ISR, DCO SMCLK
;
;   Description: Toggle P5.1 using software and TB_0 ISR. Timer_B is
;   configured for up mode, thus the timer overflows when TBR counts to TBCCR0.
;   In this example, TBCCR0 is loaded with 20000.
;   ACLK = 32.768kHz, MCLK = SMCLK = TBCLK = default DCO
;
;                 MSP430x47xx
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
 .cdecls C,LIST, "msp430x47x4.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps

OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more

SetupP5     bis.b   #BIT1,&P5DIR            ; P5.1 output
SetupC0     mov.w   #CCIE,&TBCCTL0          ; TBCCR0 interrupt enabled
            mov.w   #20000,&TBCCR0          ;
SetupTB     mov.w   #TBSSEL_2+MC_1,&TBCTL   ; SMCLK, up mode
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-----------------------------------------------------------------------------
TB0_ISR;    Toggle P5.1
;-----------------------------------------------------------------------------
            xor.b   #BIT1,&P5OUT            ; Toggle P5.1
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect     ".reset"            	; RESET Vector
            .short   RESET                  ;
            .sect    ".int13"          		; Timer_B0 Vector
            .short   TB0_ISR                ;
            .end
