;******************************************************************************
;   MSP430x47xx Demo - Timer_B, Toggle P5.1, Overflow ISR, DCO SMCLK
;
;   Description: This program toggles P5.1 using software and the Timer_B
;   overflow ISR. In this example an ISR triggers when TB overflows.
;   Inside the ISR P5.1 is toggled. Toggle rate is 16Hz when using default
;   FLL+ register settings and an external 32kHz watch crystal.	
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430x47xx
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
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
SetupP5     bis.b   #BIT1,&P5DIR            ; P5.1 output
SetupTB     mov.w   #TBSSEL_2+MC_2+TBIE,&TBCTL  ; SMCLK, cont. mode, interrupt
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
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
TB_over     xor.b   #BIT1,&P5OUT            ; Vector 14 - overflow (Toggle P5.1)
            reti                            ; Return from overflow ISR		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"            	; RESET Vector
            .short  RESET                  ;
            .sect     ".int12"                  ; Timer_BX Vector
            .short   TBX_ISR                 ;
            .end
