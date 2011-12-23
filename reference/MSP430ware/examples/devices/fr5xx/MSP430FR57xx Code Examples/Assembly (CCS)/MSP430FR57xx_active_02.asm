;******************************************************************************
;   MSP430FR57xx Demo - Stay in active mode with MCLK = 8MHz
;
;   Description: Configure ACLK = VLO and enters LPM3. 
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
			
			mov.b	#0xFF,&PJDIR
			clr.b	&PJOUT
			
			mov.b	#0xA5,&CSCTL0_H
			bis.w	#DCOFSEL0+DCOFSEL1,&CSCTL1 ; Set max DCO setting
			mov.w	#SELA_1+SELS_3+SELM_3,&CSCTL2 ; set ACLK = VLO
			mov.w	#DIVA_0+DIVS_1+DIVM_1,&CSCTL3 ; MCLK = SMCLK = DCO/2
			
			bis.w	#REFTCOFF,&REFCTL0		; Turn off Temp sensor
			bic.w	#REFON,&REFCTL0

Mainloop	bis.b	#0x01,&P1DIR			; Turn on LED
			bis.w	#GIE,SR
ACTIVE_TEST MOV     #0x2000, R4             ;      1  | 2      | 0      | 0     |       
            MOV     #0x4, 0(R4)             ;      1  | 2      | 0      | 1     | 
            MOV     &0x2000, &0x2002        ;      1  | 3      | 1      | 1     | 
            ADD     @R4, 2(R4)              ;      1  | 2      | 1      | 1     |
            SWPB    @R4+                    ;      2  | 1      | 1      | 1     |
            MOV     @R4, R5                 ;      1  | 1      | 1      | 0     |                               

IDD_AM_L1   ; run 8 times
            XOR     @R4+, &0x2020           ;      1  | 2      | 1      | 1     |
            DEC     R5                      ;     E1  | 1      | 0      | 0     | 
            JNZ     IDD_AM_L1               ;     JMP | 1      | 0      | 0     | 
            xor.b   #BIT0,&P1OUT            ; show output
            JMP		ACTIVE_TEST
            nop								; for debug
			
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
 