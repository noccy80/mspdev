;******************************************************************************
;   MSP430FR57xx Demo - Enters LPM3 with ACLK = LFXT1
;
;   Description: Configure ACLK = LFXT1 and enters LPM3. 
;   Note: On the FET board P1.0 drives an LED that can show high power numbers 
;   when turned ON. Measure current with LED jumper JP3 disconnected.
;   LED jumper disconnected.
;   ACLK = LFXT1 = 32kHz, MCLK = SMCLK = 4MHz
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
		    mov.w   #WDTPW+WDTTMSEL+WDTSSEL_1+WDTIS_4,&WDTCTL  ; ACLK, 1s interrupts
			mov.w	#WDTIE,&SFRIE1			; enable WDT interrupt
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
			
			mov.w	#0xFF,&PJDIR				; XT1 Setup
			clr.w	&PJOUT

			mov.w	#0x30,&PJSEL0
			mov.b	#0xA5,&CSCTL0_H
			bis.w	#DCOFSEL0+DCOFSEL1,&CSCTL1
			mov.w	#SELA_0+SELS_3+SELM_3,&CSCTL2
			mov.w	#DIVA_0+DIVS_1+DIVM_1,&CSCTL3
			bis.w	#XT1DRIVE_0,&CSCTL4
			bic.w	#XT1OFF,&CSCTL4
OSCFlag		bic.w	#XT1OFFG,CSCTL5			; Clear XT1 fault flag
			bic.w	#OFIFG,&SFRIFG1
			cmp.w	#0x01,&OFIFG			; Test oscillator fault flag
			jz		OSCFlag
			
			bis.w	#REFTCOFF,&REFCTL0		; Turn off Temp sensor
			bic.w	#REFON,&REFCTL0

Mainloop	bis.b	#0x01,&P1DIR			; Turn on LED
			bis.w	#LPM3+GIE,SR			; Go into LPM3 w/ interrupts
			
;-------------------------------------------------------------------------------
WDT_ISR;    ISR for WDT
;-------------------------------------------------------------------------------
			xor.b	#0x01,&P1OUT			; Toggle P1.0
            reti                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect	".int57"				; WDT Interrupt
            .short	WDT_ISR
            .end
 
