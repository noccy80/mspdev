;******************************************************************************
;  MSP430FR57xx Demo - Software Port Interrupt Service on P1.4 from LPM4
;
;  Description: A Lo/Hi transition on P1.4 will trigger P1ISR the first time. 
;  On hitting the P1ISR, device exits LPM4 mode and executes section of code in
;  main() which includes toggling an LED and the P1.4IES bit which switches between 
;  Lo/Hi and Hi/Lo trigger transitions to alternatively enter the P1ISR. 
;  ACLK = n/a, MCLK = SMCLK = default DCO
;
;               MSP430FR5739
;            -----------------
;        /|\|                 |-
;         | |                 |
;         --|RST              |-
;     /|\   |                 |
;      --o--|P1.4         P1.0|-->LED
;     \|/
;
;   Tyler Witt
;   Texas Instruments Inc.
;   September 2011
;   Built with Code Composer Studio V4.2
;******************************************************************************
 .cdecls C,LIST,  "msp430fr5739.h"

;------------------------------------------------------------------------------
			.global _main
            .text                  			; Program reset
;------------------------------------------------------------------------------
_main
RESET       mov.w   #1DFEh,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
			bis.b	#BIT0,&P1DIR			; Set P1.0 to output direction
			bic.b	#BIT0,&P1OUT
			bic.b	#BIT4,&P1OUT
			bic.b	#BIT4,&P1IES			; P1.4 Lo/Hi edge
			mov.b	#BIT4,&P1IE				; P1.4 interrupt enabled
			clr.b	&P1IFG			    	; P1.4 IFG cleared

Mainloop	bis.w	#LPM4+GIE,SR			; Enter LPM4 w/ interrupt
			nop								; for debug
			xor.b	#BIT0,&P1OUT			; P1.0 = toggle
			jmp		Mainloop
			nop								; for debug
			
;------------------------------------------------------------------------------
P1_ISR ;	Port 1 Interrupt
;------------------------------------------------------------------------------
			xor.b	#BIT4,&P1IES
			bic.b	#BIT4,&P1IFG			; Clear P1.4 IFG
			bic.w	#LPM4,0(SP)
			reti
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect	".int47"				; Port 1 Vector
            .short	P1_ISR					;
            .end
 