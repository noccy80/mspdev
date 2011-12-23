;******************************************************************************
;  MSP430FR57xx Demo - USCI_A0 External Loopback test
;
;  Description: This demo connects TX to RX of the MSP430 UART 
;  The example code shows proper initialization of registers 
;  and interrupts to receive and transmit data.
;  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1MHz
;
;                                
;                MSP430FR5739 
;                       
;             -----------------   
;       RST -|     P2.0/UCA0TXD|----|
;            |                 |    |
;           -|                 |    |
;            |     P2.1/UCA0RXD|----|
;            |                 |  
;
;   Tyler Witt
;   Texas Instruments Inc.
;   September 2011
;   Built with Code Composer Studio V4.2
;******************************************************************************
 .cdecls C,LIST,  "msp430fr5739.h"
i			.set	R5
RXData		.set	R6
TXData		.set	R7
check		.set	R8
;------------------------------------------------------------------------------
			.global _main
            .text                  			; Program reset
;------------------------------------------------------------------------------
_main
RESET       mov.w   #1DFEh,SP               ; Initialize stack pointer
			mov.w	#WDTPW+WDTHOLD,&WDTCTL	; Stop WDT
			bis.b	#BIT4+BIT5,&PJSEL0
			mov.b	#0xA5,&CSCTL0_H
			bis.w	#DCOFSEL0+DCOFSEL1,&CSCTL1 ; Set max DCO setting
			mov.w	#SELA_0+SELS_3+SELM_3,&CSCTL2 ; ACLK = XT1; MCLK = DCO
			mov.w	#DIVA_0+DIVS_3+DIVM_3,&CSCTL3 ; set all dividers
			bis.w	#XT1DRIVE_0,&CSCTL4
			bic.w	#XT1OFF,&CSCTL4
OSCFlag		bic.w	#XT1OFFG,&CSCTL5			; Clear XT1 fault flag
			bic.w	#OFIFG,&SFRIFG1
			cmp.w	#001h,&OFIFG			; Test oscillator fault flag
			jz		OSCFlag
			
			clr.w	RXData					; Initialize variables
			clr.w	TXData
			clr.w	check
			bis.b	#BIT0+BIT1,&P2SEL1		; Configure UART pins
			bic.b	#BIT0+BIT1,&P2SEL0
			bis.w	#UCSWRST,&UCA0CTL1		; Configure UART 0
			mov.w	#UCSSEL_1,&UCA0CTL1		; Set ACLK = 32768 as UCBRCLK
			mov.b	#3,&UCA0BR0				; 9600 baud
			bis.w	#0x5300,&UCA0MCTLW		; 32768/9600 - INT(32768/9600)= 0.41
											; UCBRSx value = 0x53 (See UG)
			clr.b	&UCA0BR1
			bic.w	#UCSWRST,&UCA0CTL1		; release from reset
			bis.w	#UCRXIE,&UCA0IE			; enable RX interrupt
			bis.w	#GIE,SR					; Enable interrupt
						
Mainloop	inc.w	TXData					; increment TX data
			mov.w	TXData,&UCA0TXBUF		; Load data onto buffer
Wait		cmp.b	#0x1,check
			jnz		Wait
			clr.w	check
			jmp		Mainloop
			nop								; remain in LPM0
			
;------------------------------------------------------------------------------
USCI_ISR ;	USCI Interrupt Service Routine
;------------------------------------------------------------------------------
			bic.w	#UCRXIFG,&UCA0IFG		; Clear interrupt
			mov.w	&UCA0RXBUF,RXData		; Clear buffer
Compare		cmp.w	TXData,RXData			; Check value
			jnz		Compare
			mov.w	#1,check		
			reti
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect	".int56"				; USCI_A0_VECTOR
            .short	USCI_ISR				;
            .end
