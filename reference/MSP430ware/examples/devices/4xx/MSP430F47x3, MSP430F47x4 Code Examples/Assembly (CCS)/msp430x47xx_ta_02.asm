;******************************************************************************
;   MSP430x47xx Demo - Timer_A, Toggle P5.1, TACCR0 Up Mode ISR, DCO SMCLK
;
;   Description: Toggle P5.1 using software and TA_0 ISR. Timer_A is
;   configured for up mode, thus the timer overflows when TAR counts to TACCR0.
;   In this example, TACCR0 is loaded with 20000.
;   ACLK = 32.768kHz, MCLK = SMCLK = TACLK = default DCO
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
SetupC0     mov.w   #CCIE,&TACCTL0          ; TACCR0 interrupt enabled
            mov.w   #20000,&TACCR0          ;
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, up mode
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-----------------------------------------------------------------------------
TA0_ISR;    Toggle P5.1
;-----------------------------------------------------------------------------
            xor.b   #BIT1,&P5OUT            ; Toggle P5.1
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".reset"            	; RESET Vector
            .short   RESET                  ;
            .sect    ".int06"          ; Timer_A0 Vector
            .short   TA0_ISR                 ;
            .end
