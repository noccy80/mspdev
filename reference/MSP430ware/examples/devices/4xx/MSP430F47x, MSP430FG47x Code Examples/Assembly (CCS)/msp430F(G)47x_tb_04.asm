;******************************************************************************
;   MSP430FG479 Demo - Timer_B, Toggle P4.6, Overflow ISR, 32kHz ACLK
;
;   Description: This program toggles P4.6 using software and Timer_B
;   overflow ISR. In this example an ISR triggers when TB overflows.
;   Inside the TBX_ISR, P4.6 is toggled. Toggle rate is exactly 0.5Hz.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                 MSP430FG479
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
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
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
SetupP4     bis.b   #040h,&P4DIR            ; P4.6 output
SetupTB     mov.w   #TBSSEL_1+MC_2+TBIE,&TBCTL  ; ACLK, cont. mode, interrupt
                                            ;													
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
TBX_ISR;    Common ISR for TBCCR1-6 and overflow
;------------------------------------------------------------------------------
            add.w   &TBIV,PC                ; Add Timer_B offset vector
            reti                            ; Vector 0 - no interrupt
            reti                            ; Vector 2 - CCR1
            reti                            ; Vector 4 - CCR2
            reti                            ; Vector 6 - CCR3
            reti                            ; Vector 8 - CCR4
            reti                            ; Vector 10 - CCR5
            reti                            ; Vector 12 - CCR6
TB_over     xor.b   #040h,&P4OUT            ; Vector 14 - overflow (Toggle P4.6)
            reti                            ; Return from overflow ISR		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"            	; RESET Vector
            .short  RESET                  ;
            .sect     ".int12"                  ; Timer_BX Vector
            .short   TBX_ISR                 ;
            .end
