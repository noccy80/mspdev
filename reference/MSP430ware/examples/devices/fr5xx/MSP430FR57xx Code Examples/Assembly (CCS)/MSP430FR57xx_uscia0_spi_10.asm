;******************************************************************************
;   MSP430F54x Demo - USCI_A0, SPI 3-Wire Slave Data Echo
;
;   Description: SPI slave talks to SPI master using 3-wire mode. Data received
;   from master is echoed back.  
;   ACLK = 32.768kHz, MCLK = SMCLK = DCO ~ 1MHz
;   Note: Ensure slave is powered up before master to prevent delays due to 
;   slave init.
;
;
;                   MSP430FR5739
;                 -----------------
;            /|\ |                 |
;             |  |                 |
;            -+->|                 |
;                |                 |
;                |             P2.0|-> Data Out (UCA0SOMI)
;                |                 |
;                |             P2.1|<- Data In (UCA0SIMO)
;                |                 |
;                |             P1.5|-> Serial Clock Out (UCA0CLK)
;
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
			
			bis.b	#BIT5,&P1SEL1
			bis.b	#BIT0+BIT1,&P2SEL1
			bis.w	#UCSWRST,&UCA0CTLW0		; **Put state machine in reset**
			bis.w	#UCSYNC+UCCKPL+UCMSB,&UCA0CTLW0 ; 3-pin, 8-bit SPI slave
													; Clock polarity high, MSB
			bis.w	#UCSSEL_2,&UCA0CTLW0	; SMCLK
			mov.b	#0x02,&UCA0BR0			; /2
			clr.b	&UCA0BR1
			clr.w	&UCA0MCTLW				; No modulation
			bic.w	#UCSWRST,&UCA0CTLW0		; **Initialize USCI state machine**
			bis.w	#UCRXIE,&UCA0IE			; Enable USCI_A0 RX interrupt
			
Mainloop	bis.w	#LPM0+GIE,SR			; Enter LPM0 w/ interrupt
			nop								; remain in LPM0
			
;------------------------------------------------------------------------------
USCI_ISR ;	USCI Interrupt Service Routine
;------------------------------------------------------------------------------
Again		cmp.w	#0x1,&UCTXIFG			; USCI_A0 TX buffer ready?
			jz		Again					; No, wait
			mov.w	&UCA0RXBUF,&UCA0TXBUF	; Yes, echo received data
			reti
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect	".int56"				; USCI_A0_VECTOR
            .short	USCI_ISR				;
            .end
