;*******************************************************************************
;  MSP430FR57x Demo - Timer1_A3, PWM TA1.1-2, Up Mode, 32KHz ACLK
;
;  Description: This program generates two PWM outputs on P1.2,P1.3 using
;  Timer1_A configured for up mode. The value in CCR0 defines the PWM
;  period and the values in CCR1 and CCR2 the PWM duty cycles. Using 32768Hz
;  ACLK as TACLK, the timer period is ~3ms with a 75% duty cycle on P1.2
;  and 25% on P1.3.
;  ACLK = TACLK =32768Hz, SMCLK = MCLK = 4MHz
;
;
;           MSP430FR5739
;         ---------------
;     /|\|               |
;      | |               |
;      --|RST            |
;        |               |
;        |     P1.2/TA0.1|--> CCR1 - 75% PWM
;        |     P1.3/TA0.2|--> CCR2 - 25% PWM
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
			mov.w	#DCOFSEL0+DCOFSEL1,&CSCTL1 ; Set max DCO setting
			mov.w	#SELA_0+SELS_3+SELM_3,&CSCTL2 ; ACLK = XT1; MCLK = DCO
			mov.w	#DIVA_0+DIVS_3+DIVM_3,&CSCTL3 ; set all dividers
			bis.w	#XT1DRIVE_0,&CSCTL4
			bic.w	#XT1OFF,&CSCTL4
OSCFlag		bic.w	#XT1OFFG,&CSCTL5			; Clear XT1 fault flag
			bic.w	#OFIFG,&SFRIFG1
			cmp.w	#001h,&OFIFG			; Test oscillator fault flag
			jz		OSCFlag
			
			bis.b	#BIT2+BIT3,&P1DIR		; P1.0 and P1.1 output
			bis.b	#BIT2+BIT3,&P1SEL0		; P1.0 and P1.1 options select
			mov.w	#25-1,&TA1CCR0			; PWM period
			mov.w	#OUTMOD_7,&TA1CCTL1		; CCR1 reset/set
			mov.w	#18,&TA1CCR1			; CCR1 PWM duty cycle
			mov.w	#OUTMOD_7,&TA1CCTL2		; CCR2 reset/set
			mov.w	#6,&TA1CCR2			; CCR2 PWM duty cycle
			mov.w	#TASSEL_1+MC_1+TACLR,&TA1CTL ; ACLK, up mode, clear TAR

Mainloop	bis.w	#LPM3,SR				; Enter LPM3
			nop								; for debug
			
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
