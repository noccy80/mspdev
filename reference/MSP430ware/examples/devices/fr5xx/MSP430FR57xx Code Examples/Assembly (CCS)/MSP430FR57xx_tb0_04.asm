;******************************************************************************
;  MSP430FR57x Demo - TimerB, Toggle P1.0, Overflow ISR, 32kHz ACLK
;
;  Description: Toggle P1.0 using software and the TimerB overflow ISR.
;  In this example an ISR triggers when TB overflows. Inside the ISR P1.0
;  is toggled. Toggle rate is exactly 62.5mHz. Proper use of the TBIV interrupt
;  vector generator is demonstrated.
;  
;  ACLK = TACLK = 32768Hz, MCLK = SMCLK = 4MHz
;
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
			bis.w	#BIT4+BIT5,&PJSEL0		; Setup XT1
			mov.b	#0xA5,&CSCTL0_H
			bis.w	#DCOFSEL0+DCOFSEL1,&CSCTL1 ; set max DCO setting
			mov.w	#SELA_0+SELS_3+SELM_3,&CSCTL2 ; ACLK = XT1; MCLK = DCO
			mov.w	#DIVA_0+DIVS_1+DIVM_1,&CSCTL3 ; set all dividers
			bis.w	#XT1DRIVE_0,&CSCTL4
			bic.w	#XT1OFF,&CSCTL4
OSCFlag		bic.w	#XT1OFFG,&CSCTL5		; Clear XT1 fault flag
			bic.w	#OFIFG,&SFRIFG1
			cmp.w	#001h,&OFIFG			; Test oscillator fault flag
			jz		OSCFlag

			bis.b	#BIT0,&P1DIR			; Set P1.0 to output direction
			bis.b	#BIT0,&P1OUT
			mov.w	#TBSSEL_1+MC_2+TBCLR+TBIE,&TB0CTL ; ACLK, cont mode, clear TBR
											; enable interrupt

Mainloop	bis.w	#LPM3+GIE,SR			; Enter LPM3 w/ interrupt
			nop								; for debug
			
;-------------------------------------------------------------------------------
TB0_ISR;    ISR for TB0CCR0
;-------------------------------------------------------------------------------
			add.w	&TB0IV,PC
			reti							; No interrupt
			reti							; CCR1 not used
			reti							; CCR2 not used
			reti							; reserved
			reti							; reserved
			reti							; reserved
			reti							; reserved
			xor.b	#BIT0,&P1OUT			; overflow
			reti
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int58"                ; Timer_B0 Vector
            .short  TB0_ISR                 ;
            .end
