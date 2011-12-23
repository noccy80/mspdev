;*******************************************************************************
;   MSP430x261x Demo - DMA0, Repeated Burst to-from RAM, Software Trigger
;
;   Description: A 16 word block from 1400-141fh is transfered to 1420h-143fh
;   using DMA0 in a burst block using software DMAREQ trigger.
;   After each transfer, source, destination and DMA size are
;   reset to inital software setting because DMA transfer mode 5 is used.
;   P1.0 is toggled durring DMA transfer only for demonstration purposes.
;   ** RAM location 0x1400 - 0x143f used - make sure no compiler conflict **
;   ACLK = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
;
;                MSP430x2619
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
	.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #BIT0,&P1DIR            ; P1.0  output
SetupDMA0   movx.a  #1400h,&DMA0SA          ; Start block address
            movx.a  #1420h,&DMA0DA          ; Destination block address
            mov.w   #0010h,&DMA0SZ          ; Block size
            mov.w   #DMADT_5+DMASRCINCR_3+DMADSTINCR_3,&DMA0CTL; Rpt, inc
            bis.w   #DMAEN,&DMA0CTL         ; Enable DMA0
                                            ;
Mainloop    bis.b   #BIT0,&P1OUT            ; P1.0 = 1, LED on
            bis.w   #DMAREQ,&DMA0CTL        ; Trigger block transfer
            bic.b   #BIT0,&P1OUT            ; P1.0 = 0, LED off
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .end
