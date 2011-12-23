;******************************************************************************
;   MSP430FR57xx Demo - Configure MCLK for 24MHz operation
;
;   Description: Configure ACLK = SMCLK = MCLK = 24MHz
;   IMPORTANT NOTE: While the FR5739 is capable of operation using a 24MHz 
;   MCLK; the throughput of the device is dependednt on accesses to FRAM. 
;   The maximum speed for accessing FRAM is limited to 8MHz*. 
;   Wait states are inserted automatically when the FRAM is accessed at 
;   speeds higher than 8MHz to prevent timing violations.
;   Refer to the FRAM Clock System chapter of the User's Guide.
;   * Refer device D/s for typical numbers
;
;           MSP430FR57x
;         ---------------
;     /|\|               |
;      | |               |
;      --|RST            |
;        |               |
;        |               |  
;        |          P2.0 |---> ACLK = MCLk = 24MHz
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
			mov.b	#0xA5,&CSCTL0_H
			bis.w	#DCORSEL+DCOFSEL0+DCOFSEL1,&CSCTL1 ; Set max DCO setting
			mov.w	#SELA_3+SELS_3+SELM_3,&CSCTL2 ; ACLK = MCLK = DCO
			mov.w	#DIVA_0+DIVS_0+DIVM_0,&CSCTL3 ; set all dividers

			clr.b	&P2OUT				; output ACLK
			bis.b	#BIT0,&P2DIR
			bis.b	#BIT0,&P2SEL1
			bis.b	#BIT0,&P2SEL0
			
Mainloop	jmp		Mainloop				; endless loop
			nop								; for debug
			
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
