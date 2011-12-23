;******************************************************************************
;  MSP430FR57xx Demo - DMA0, Repeated Block to-from RAM, Software Trigger
;
;  Description: A 16 word block from 1C20-1C2Fh is transfered to 1C40h-1C4fh
;  using DMA0 in a burst block using software DMAREQ trigger.
;  After each transfer, source, destination and DMA size are
;  reset to inital software setting because DMA transfer mode 5 is used.
;  P1.0 is toggled durring DMA transfer only for demonstration purposes.
;  ** RAM location 0x1C00 - 0x1C3F used - make sure no compiler conflict **
;   MCLK = SMCLK = default DCO 
; 
;
;                 MSP430FR5739
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
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
RESET       mov.w   #1DFEh,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
			bis.b	#001h,&P1DIR			; P1.0 Output
			mov.w	#DMA0SA,R15				; Source address
			movx.a	#1C20h,0x0(R15)
			mov.w	#DMA0DA,R15				; Destination address
			movx.a	#1C40h,0x0(R15)
			mov.w	#16,&DMA0SZ				; Block size
			mov.w	#DMADT_5+DMASRCINCR_3+DMADSTINCR_3,&DMA0CTL	; Rpt, inc
			bis.w	#DMAEN,&DMA0CTL			; enable DMA0

Mainloop	bis.b	#01h,&P1OUT				; P1.0 = 1, LED on
			bis.w	#DMAREQ,&DMA0CTL		; Trigger transfer
			bic.b	#01h,&P1OUT				; P1.0 = 0, LED off
			jmp		Mainloop
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
 