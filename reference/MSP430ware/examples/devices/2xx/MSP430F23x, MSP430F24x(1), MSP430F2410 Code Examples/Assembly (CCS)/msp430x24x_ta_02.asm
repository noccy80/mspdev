;******************************************************************************
;   MSP430x24x Demo - Timer_A, Toggle P1.0, TACCR0 Up Mode ISR, DCO SMCLK
;
;   Description: Toggle P1.0 using software and TA_0 ISR. Timer_A is
;   configured for up mode, thus the timer overflows when TAR counts to TACCR0.
;   In this example, TACCR0 is loaded with 20000.
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
SetupC0     mov.w   #CCIE,&TACCTL0          ; TACCR0 interrupt enabled
            mov.w   #20000,&TACCR0          
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, up mode
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-----------------------------------------------------------------------------
TA0_ISR;    Toggle P1.0
;-----------------------------------------------------------------------------
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset
            .short  RESET                    ;
            .sect	".int25"          ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end
