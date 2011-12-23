;******************************************************************************
;  MSP430FR57x Demo - TimerB, Toggle P1.0, CCR0 UP Mode ISR, 32KHz ACLK 
;
;  Description: Toggle P1.0 using software and TB ISR. TimerB is
;  configured for UP mode, thus the timer overflows when TBR counts
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
;   August 2011
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
			bis.w	#BIT4+BIT5,&PJSEL0		; Setup XT1
			mov.b	#0xA5,&CSCTL0_H
			mov.w	#SELA_0+SELS_3+SELM_3,&CSCTL2 ; ACLK = XT1; MCLK = DCO
			mov.w	#DIVA_0+DIVS_0+DIVM_0,&CSCTL3 ; set all dividers
			bis.w	#XT1DRIVE_0,&CSCTL4
			bic.w	#XT1OFF,&CSCTL4
OSCFlag		bic.w	#XT1OFFG,&CSCTL5			; Clear XT1 fault flag
			bic.w	#OFIFG,&SFRIFG1
			cmp.w	#001h,&OFIFG			; Test oscillator fault flag
			jz		OSCFlag

			bis.b	#BIT0,&P1DIR			; Set P1.0 to output direction
			bis.b	#BIT0,&P1OUT
			
			mov.w	#CCIE,&TB1CCTL0
			mov.w	#12500,&TB1CCR0
			mov.w	#TBSSEL_1+MC_1,&TB1CTL ; ACLK, UP mode, clear TBR
											; enable interrupt

Mainloop	bis.w	#LPM3+GIE,SR			; Enter LPM3 w/ interrupt
			nop								; for debug
			
;-------------------------------------------------------------------------------
TB1_ISR;    ISR for Timer B1
;-------------------------------------------------------------------------------
			xor.b	#BIT0,&P1OUT
			reti
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int46"                ; Timer_B1 Vector
            .short  TB1_ISR                 ;
            .end
