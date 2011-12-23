;******************************************************************************
;   MSP430FR57xx Demo - Enters LPM4
;
;   Description: Device enters LPM4
; 
;           MSP430FR57x
;         ---------------
;     /|\|               |
;      | |               |
;      --|RST            |
;        |               |
;        |               |  
;        |          P1.0 |---> Disconnect JP3 for power meas.
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
			clr.b	&P1DIR
			clr.b	&P1OUT
			mov.b	#0xFF,&P1REN
			
			clr.b	&P2DIR
			clr.b	&P2OUT
			mov.b	#0xFF,&P2REN
			
			clr.b	&P3DIR
			clr.b	&P3OUT
			mov.b	#0xFF,&P3REN
			
			clr.b	&P4DIR
			clr.b	&P4OUT
			mov.b	#0xFF,&P4REN
			
			mov.b	#0xA5,&CSCTL0_H
			bis.w	#DCOFSEL0+DCOFSEL1,&CSCTL1 ; Set max DCO setting
			mov.w	#SELA_1+SELS_3+SELM_3,&CSCTL2 ; set ACLK = VLO; MCLK = DCO
			mov.w	#DIVA_0+DIVS_1+DIVM_1,&CSCTL3 ; set all dividers
			mov.w	#XT1OFF+XT2OFF,&CSCTL4
			bic.w	#XT1OFFG+XT2OFFG,&CSCTL5	
			
			clr.w	&PJDIR
			clr.w	&PJOUT
			mov.w	#0xFF,&PJREN
			
			bis.w	#REFTCOFF,&REFCTL0		; Turn off Temp sensor
			bic.w	#REFON,&REFCTL0

Mainloop	bis.w	#LPM4,SR				; Go into LPM3 w/ interrupts
			
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
 
