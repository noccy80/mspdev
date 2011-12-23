;******************************************************************************
;  MSP430FR57xx Demo - USCI_B0 I2C Slave TX single bytes to MSP430 Master
;
;  Description: This demo connects two MSP430's via the I2C bus. The master
;  reads from the slave. This is the SLAVE code. The TX data begins at 0
;  and is incremented each time it is sent. A stop condition
;  is used as a trigger to increment the outgoing data. 
;  The USCI_B0 TX interrupt is used to know
;  when to TX.
;  ACLK = n/a, MCLK = SMCLK = DCO = 1MHz
;
;                                /|\  /|\
;               MSP430FR5739      10k  10k     MSP430FR5739
;                   slave         |    |        master
;             -----------------   |    |   -----------------
;           -|XIN  P1.6/UCB0SDA|<-|----+->|P1.6/UCB0SDA  XIN|-
;            |                 |  |       |                 |
;           -|XOUT             |  |       |             XOUT|-
;            |     P1.7/UCB0SCL|<-+------>|P1.7/UCB0SCL     |
;            |                 |          |                 |
;
;   Tyler Witt
;   Texas Instruments Inc.
;   September 2011
;   Built with Code Composer Studio V4.2
;******************************************************************************
 .cdecls C,LIST,  "msp430fr5739.h"
TXData		.set	R5
;------------------------------------------------------------------------------
			.global _main
            .text                  			; Program reset
;------------------------------------------------------------------------------
_main
RESET       mov.w   #1DFEh,SP               ; Initialize stack pointer
			mov.w	#WDTPW+WDTHOLD,&WDTCTL	; Stop WDT
			mov.b	#0xA5,&CSCTL0_H
			bis.w	#DCOFSEL0+DCOFSEL1,&CSCTL1 ; Set max DCO setting
			mov.w	#SELA_3+SELS_3+SELM_3,&CSCTL2 ; ACLK = MCLK = DCO
			mov.w	#DIVA_3+DIVS_3+DIVM_3,&CSCTL3 ; set all dividers to 1MHz
			bis.b	#BIT6+BIT7,&P1SEL1		; Configure pins
			clr.w	TXData					; Start TXData at 0
			
			bis.w	#UCSWRST,&UCB0CTLW0		; Software reset enabled
			bis.w	#UCMODE_3+UCSYNC,&UCB0CTLW0 ; I2C mode, sync
			mov.w	#0x48+UCOAEN,&UCB0I2COA0 ; own address is 0x48 + enable
			bic.w	#UCSWRST,&UCB0CTLW0		; Software reset cleared
			bis.w	#UCTXIE0+UCSTPIE,&UCB0IE
			bis.b	#BIT0,&P1DIR

Mainloop	bis.w	#LPM0+GIE,SR			; Enter LPM0 w/ interrupt
			nop								; remain in LPM0
			
;------------------------------------------------------------------------------
USCI_ISR ;	USCI Interrupt Service Routine
;------------------------------------------------------------------------------
			add		&UCB0IV,PC				; Add offset to PC
			reti							; No interrupt
			reti							; ALIFG break
			reti							; NACKIFG break
			reti							; STTIFG break
			jmp		Stop					; STPIFG break
			reti							; RXIFG3 break
			reti							; TXIFG3 break
			reti							; RXIFG2 break
			reti							; TXIFG2 break
			reti							; RXIFG1 break
			reti							; TXIFG1 break
			reti							; RXIFG0 break
			jmp		GetTX					; TXIFG0 break
			reti							; BCNTIFG break
			reti							; clock low timeout break
			reti							; 9th bit break
Stop		inc.w	TXData
			bic.w	#UCSTPIFG,&UCB0IFG		; Clear stop condition int flag
			reti
GetTX		mov.w	TXData,&UCB0TXBUF
			reti
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect	".int55"				; USCI_B0_VECTOR
            .short	USCI_ISR				;
            .end
