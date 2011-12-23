;******************************************************************************
;   MSP430P430 Demo - DMA0, Repeated Block To P5OUT, CCR2IFG Trigger
;
;   Description: DMA0 is used to transfer a string byte-by-byte as a repeating
;   block to P5OUT. Timer_A operates continuously with CCR2IFG
;   triggering DMA0. The effect is P5.1/5.2 toggling at different frequencies.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430FG439
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|--> LED
;            |             P5.2|-->
;
;   M. Buccini / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;------------------------------------------------------------------------------
            .text                  ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #006h,&P5DIR            ; P5.1/5.2 output
SetupDMA0   mov.w   #DMA0TSEL_1,&DMACTL0    ; CCR2 trigger
            mov.w   #testconst,&DMA0SA      ; Source block address
            mov.w   #P5OUT,&DMA0DA          ; Destination single address
            mov.w   #06h,&DMA0SZ            ; Block size
            mov.w   #DMADT_4+DMASRCINCR_3+DMASBDB+DMAEN,&DMA0CTL; Rpt, inc src
SetupTA     mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK/4, contmode
                                            ;
Mainloop    bis.w   #CPUOFF,SR              ;
            nop                             ; Required only for debugger
                                            ;
testconst   .byte  00h,06h,04h,06h,00h,02h
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end
