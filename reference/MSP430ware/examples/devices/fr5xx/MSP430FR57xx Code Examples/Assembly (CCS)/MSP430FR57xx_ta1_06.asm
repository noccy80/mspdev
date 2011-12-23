;******************************************************************************
;  MSP430FR57x Demo - Timer1_A3, Toggle P1.0, CCR0 UP Mode ISR, 32KHz ACLK 
;
;  Description: Toggle P1.0 using software and TA1_0 ISR. Timer1_A is
;  configured for UP mode, thus the timer overflows when TAR counts
;  to CCR0.
;  ACLK = TACLK = 32768Hz, MCLK = SMCLK  = default DCO = ~666KHz
;
;           MSP430FR5739
;         ---------------
;     /|\|               |
;      | |               |
;      --|RST            |
;        |               |
;        |           P1.0|-->LED
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

			mov.w	#BIT4+BIT5,&PJSEL0
			mov.b	#0xA5,&CSCTL0_H
			mov.w	#SELA_0+SELS_3+SELM_3,&CSCTL2 ; ACLK = XT1; MCLK = DCO
			mov.w	#DIVA_0+DIVS_3+DIVM_3,&CSCTL3 ; set all dividers
			bis.w	#XT1DRIVE_0,&CSCTL4
			bic.w	#XT1OFF,&CSCTL4
OSCFlag		bic.w	#XT1OFFG,&CSCTL5			; Clear XT1 fault flag
			bic.w	#OFIFG,&SFRIFG1
			cmp.w	#001h,&OFIFG			; Test oscillator fault flag
			jz		OSCFlag

			bis.b	#BIT0,&P1DIR			; Set P1.0 to output direction
			bis.b	#BIT0,&P1OUT
			
			mov.w	#CCIE,&TA1CCTL0			; TACCR0 interrupt enabled
			mov.w	#50000,&TA1CCR0
			mov.w	#TASSEL_1+MC_1,&TA1CTL	; ACLK, UP mode

Mainloop	bis.w	#LPM3+GIE,SR			; Enter LPM3 w/ interrupt
			nop								; for debug
			
;-------------------------------------------------------------------------------
TA1_ISR;    ISR for TA1CCR0
;-------------------------------------------------------------------------------
			xor.b	#BIT0,&P1OUT			; Toggle LED
			reti
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int49"                ; Timer_A1 Vector
            .short  TA1_ISR                 ;
            .end
