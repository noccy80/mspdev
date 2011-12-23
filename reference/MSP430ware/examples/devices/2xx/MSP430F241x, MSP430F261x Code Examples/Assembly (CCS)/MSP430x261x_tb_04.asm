;******************************************************************************
;   MSP430x261x Demo - Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
;
;   Description: Toggle P1.0 using software and the Timer_B overflow ISR.
;   In this example an ISR triggers when TA overflows. Inside the ISR P1.0
;   is toggled. Toggle rate is exactly 0.5Hz.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430F241x
;                MSP430F261x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
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
SetupTB     mov.w   #TBSSEL_1+MC_2+TBIE,&TBCTL; ACLK, cont. mode, interrupt
                                            ;													
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
TBX_ISR;    Common ISR for TBCCR1-4 and overflow
;------------------------------------------------------------------------------
            add.w   &TBIV,PC                ; Add Timer_B offset vector
            reti                            ; Vector 0 - no interrupt
            reti                            ; Vector 1 - TBCCR1
            reti                            ; Vector 2 - TBCCR2
            reti                            ; Vector 3 - CCR3
            reti                            ; Vector 4 - CCR4
            reti                            ; Vector 5 - CCR5
            reti                            ; Vector 6 - CCR6
TB_over     bic.w   #TBIFG,&TBCTL           ; Done to counter bug
            xor.b   #BIT0,&P1OUT            ; Vector 7 - overflow (Toggle P1.0)
            reti                            ; Return from overflow ISR		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; MSP430 RESET Vector
            .short  RESET                  ;
            .sect	".int28"          ; Timer_BX Vector
            .short  TBX_ISR                 ;
            .end
            