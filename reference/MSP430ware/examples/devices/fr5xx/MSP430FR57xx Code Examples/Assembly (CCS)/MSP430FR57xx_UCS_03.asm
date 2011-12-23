;******************************************************************************
;   MSP430FR57xx Demo - Output 32768Hz crystal on XT1 and observe failsafe 
;
;   Description: Configure ACLK = LFXT1 and enter LPM3. 
;   To observe failsafe behavior short the crytsal briefly on the target board.
;   This will cause an NMI to occur. P1.0 is toggled inside the NMI ISR. 
;   Once the fault flag is cleared XT1 operation continues from 32768Hz crystal
;   Otherwise ACLK defaults to VLO (~8KHz).
;   ACLK = LFXT1 = 32kHz, MCLK = SMCLK = 4MHz
; 
;           MSP430FR57x
;         ---------------
;     /|\|               |
;      | |               |
;      --|RST            |
;        |               |
;        |          P2.0 |--->ACLK  
;        |          P1.0 |--->LED
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
			clr.b	&P1OUT					; LED Setup
			bis.b	#BIT0,&P1DIR
			bis.b	#BIT4+BIT5,&PJSEL0		; XT1 Setup
			mov.b	#0xA5,&CSCTL0_H
			bis.w	#DCOFSEL0+DCOFSEL1,&CSCTL1 ; Set max DCO setting
			mov.w	#SELA_0+SELS_3+SELM_3,&CSCTL2 ; ACLK = XT1; MCLK = DCO
			mov.w	#DIVA_0+DIVS_1+DIVM_1,&CSCTL3 ; set all dividers
			bis.w	#XT1DRIVE_0,&CSCTL4
			bic.w	#XT1OFF,&CSCTL4
OSCFlag		bic.w	#XT1OFFG,&CSCTL5		; Clear XT1 fault flag
			bic.w	#OFIFG,&SFRIFG1
			cmp.w	#0x1,&OFIFG				; Test oscillator fault flag
			jz		OSCFlag

			bis.w	#OFIE,&SFRIE1			; now that osc is running enable fault interrupt
			clr.b	&P2OUT					; output ACLK
			bis.b	#BIT0,&P2DIR
			bis.b	#BIT0,&P2SEL1
			bis.b	#BIT0,&P2SEL0
			
Mainloop	bis.w	#LPM3+GIE,SR			; Enter LPM3 w/ interrupt
			nop								; for debug
			
;------------------------------------------------------------------------------
UNMI_ISR;	UNMI Interrupt Service Routine
;------------------------------------------------------------------------------
			; Set a break point on the line below to observe XT1 operating from
			; VLO when the breakpoint is hit during a crystal fault
Again		bic.w	#XT1OFFG,&CSCTL5		; Clear XT1 fault flag
			bic.w	#OFIFG,&SFRIFG1
			bis.b	#BIT0,&P1OUT
			mov.w	#12500,R15				; time for flag to get set again
Wait		dec.w	R15
			jnz		Wait
			cmp.w	#0x1,&OFIFG				; Test oscillator fault flag
			jz		Again
			bic.b	#BIT0,&P1OUT
			reti
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int61"                ; UNMI Vector
            .short  UNMI_ISR;
            .end
