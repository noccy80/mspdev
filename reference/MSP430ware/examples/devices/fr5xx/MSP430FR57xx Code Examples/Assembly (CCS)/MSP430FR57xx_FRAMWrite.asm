;******************************************************************************
;   MSP430FR57xx Demo - Long word writes to FRAM
;
;   Description: Use long word write to write to 512 byte blocks of FRAM.
;   Toggle LED after every 100 writes.
;   NOTE: Running this example for extended periods will impact the FRAM
;   endurance. 
;   ACLK = VLO, MCLK = SMCLK = 4MHz
; 
;           MSP430FR57x
;         ---------------
;     /|\|               |
;      | |               |
;      --|RST            |
;        |               |
;        |               |  
;        |          P1.0 |---> LED
;
;   Tyler Witt
;   Texas Instruments Inc.
;   September 2011
;   Built with Code Composer Studio V4.2
;******************************************************************************
 .cdecls C,LIST,  "msp430fr5739.h"
FRAM_write_ptr	.set	R5
data			.set	R6
count			.set	R7
FRAM_TEST_START	.set	0xCA00
;------------------------------------------------------------------------------
			.global _main
            .text                  			; Program reset
;------------------------------------------------------------------------------
_main
RESET       mov.w   #1DFEh,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
			mov.b	#0xA5,&CSCTL0_H
			bis.w	#DCOFSEL0+DCOFSEL1,&CSCTL1 ; Set max DCO setting
			mov.w	#SELA_0+SELS_3+SELM_3,&CSCTL2 ; ACLK = VLO
			mov.w	#DIVA_0+DIVS_3+DIVM_3,&CSCTL3 ; MCLK = SMCLK = DCO/2
			bis.w	#REFTCOFF,&REFCTL0		; Turn off temp sensor
			bic.w	#REFON,&REFCTL0
			bis.b	#BIT0,&P1DIR			; Turn on LED
			mov.w	#0x1111,data			; Initialize dummy data
			mov.w	#00h,count				; Initialize counter

Mainloop	inc.w	data
			mov.w	#FRAM_TEST_START,FRAM_write_ptr
			call	#FRAMWrite				; Endless loop
			inc.w	count					; Use R14 as counter
			cmp.w	#101,count
			jnz		Mainloop
			xor.b	#01h,&P1OUT				; Toggle LED to show 512K bytes
			clr.w	count					; ...have been written
			mov.w	#0x1111,data			; After 100 times, reset dummy data
			jmp		Mainloop
			
;------------------------------------------------------------------------------
FRAMWrite 	; Write to the FRAM
;------------------------------------------------------------------------------
			clr.w	R15						; Use gen purpose register as index
Start		inc.w	R15
			cmp.w	#101h,R15				; for 128 blocks...
			jhs		Exit
			mov.w	data,0x0(FRAM_write_ptr) ; write to FRAM
			incd.w	FRAM_write_ptr
			jmp		Start
Exit		ret
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
 