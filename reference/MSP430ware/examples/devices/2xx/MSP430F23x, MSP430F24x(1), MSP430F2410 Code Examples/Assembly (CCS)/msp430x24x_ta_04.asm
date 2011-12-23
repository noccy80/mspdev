;******************************************************************************
;   MSP430x24x Demo - Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK
;
;   Description: Toggle P1.0 using software and the Timer_A overflow ISR.
;   In this example an ISR triggers when TA overflows. Inside the ISR P1.0
;   is toggled. P1.0 toggles every 2sec.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                 MSP430x249
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
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

SetupP5     bis.b   #BIT0,&P1DIR            ; F249 output
SetupTA     mov.w   #TASSEL_1+MC_2+TAIE,&TACTL  ; ACLK, cont. mode, interrupt
                                            ;													
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
TAX_ISR;    Common ISR for TACCR1-4 and overflow
;------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti                            ; Vector 0 - no interrupt
            reti                            ; Vector 1 - TACCR1
            reti                            ; Vector 2 - TACCR2
            reti                            ; Vector 3 - CCR3
            reti                            ; Vector 4 - CCR4
TA_over     xor.b   #BIT0,&P1OUT            ; Vector 5 - overflow (Toggle P1.0)
            reti                            ; Return from overflow ISR		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset
            .short  RESET                   ;
            .sect   ".int24"          ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end
