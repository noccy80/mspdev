;*******************************************************************************
;  MSP430x24x Demo - Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
;
;  Description: Toggle P1.0 using software and Timer_B overflow ISR.
;  In this example an ISR triggers when TB overflows.  TB overflow has the 
;  lowest priority. Inside the TB overflow ISR P1.0 is toggled. Toggle rate is 
;  approximatlely ~ [1.04MHz/FFFFh]/2. Proper use of TBIV interrupt vector 
;  generator is shown.
;  ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~1.045MHz.
;
;           MSP430F249
;         ---------------
;     /|\|            XIN|-
;      | |               |
;      --|RST        XOUT|-
;        |               |
;        |           P1.0|-->LED
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
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupP1     bis.b   #01h, &P1DIR            ; Set P1.0 to output direction
            mov.w   #TBSSEL_2 + MC_2 + TBIE, &TBCTL ;SMCLK, contmode, interrupt
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-------------------------------------------------------------------------------
TBX_ISR;    Common ISR for overflow
;-------------------------------------------------------------------------------
            add.w   &TBIV,PC                ; Add Timer_B offset vector
            reti                            ;
            reti                            ; TBCCR1 not used
            reti                            ; TBCCR2 not used
            reti                            ;
            reti                            ;
            reti                            ;
            reti                            ;
TB_over     xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset
            .short  RESET                   ;
            .sect   ".int28"          ; Timer_BX Vector
            .short  TBX_ISR                 ;
            .end
