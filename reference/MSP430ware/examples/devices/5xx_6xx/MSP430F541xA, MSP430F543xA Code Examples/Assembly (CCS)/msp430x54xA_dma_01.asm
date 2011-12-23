;******************************************************************************
;  MSP430F543xA Demo - DMA0, Repeated Block to-from RAM, Software Trigger
;
;  Description: A 16 word block from 1C00-1C1Fh is transfered to 1C20h-1C3fh
;  using DMA0 in a burst block using software DMAREQ trigger.
;  After each transfer, source, destination and DMA size are
;  reset to inital software setting because DMA transfer mode 5 is used.
;  P1.0 is toggled durring DMA transfer only for demonstration purposes.
;  ** RAM location 0x1C00 - 0x1C3F used - make sure no compiler conflict **
;  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
;
;                 MSP430F5438A
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 and IAR Embedded Workbench Version: 4.11B
;******************************************************************************

    .cdecls C,LIST,"msp430x54xA.h"

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #0x01,&P1DIR            ; P1.0 output
SetupDMA0   movx.a  #0x1C00,&DMA0SA         ; Start block address
            movx.a  #0x1C20,&DMA0DA         ; Destination block address
            mov.w   #0010h,&DMA0SZ          ; Block size
            mov.w   #DMADT_5+DMASRCINCR_3+DMADSTINCR_3,&DMA0CTL ; Rpt, inc 
            bis.w   #DMAEN,&DMA0CTL         ; Enable DMA0
                                            ;
Mainloop    bis.b   #0x01,&P1OUT            ; P1.0 = 1, LED on
            bis.w   #DMAREQ,&DMA0CTL        ; Trigger block transfer
            bic.b   #0x01,&P1OUT            ; P1.0 = 0, LED off
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
